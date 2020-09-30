#include "stdafx.h"
#include "CompPlus_Settings.h"
#include "IZAPI.h"
#include "CompPlus_Core.h"
#include "SonicMania.h"
#include "ManiaExt.h"
#include "CompPlus_Settings.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "Helpers.h"

namespace CompPlus_Internal 
{
    bool HasCopiedOriginalTimeCode = false;
    bool IsLimitedWriten = false;
    bool IsUnlimitedWriten = false;

    bool HasCopiedOriginalHurryTimerCode = false;
    bool IsHurryTimerOffWriten = false;
    bool IsHurryTimerOnWriten = false;

    bool isUnlockWriten = false;
    bool isLockWriten = false;
    bool HasCopiedOriginalControlUnlockCode = false;
    char ControlLock_OriginalCode[0x06];

    bool InitalInputCollected = false;

    void UpdateVSControlLockState()
    {
        void* vs_player_freeze_address = (void*)(baseAddress + 0xC3E2B);
        // NOP bytes
        char nops[6];
        memset(nops, 0x90, sizeof nops);


        if (!HasCopiedOriginalControlUnlockCode)
        {
            memcpy(ControlLock_OriginalCode, vs_player_freeze_address, 0x06);
            HasCopiedOriginalControlUnlockCode = true;
        }

        if (!CompPlus_Settings::isVSControllerInputUnlocked)
        {
            if (!isLockWriten)
            {
                WriteData(vs_player_freeze_address, ControlLock_OriginalCode, 0x06);
                isUnlockWriten = false;
                isLockWriten = true;
            }
        }
        else
        {
            if (!isUnlockWriten)
            {
                WriteData(vs_player_freeze_address, nops, 0x06);
                isLockWriten = false;
                isUnlockWriten = true;
            }
        }
    }

    char HurryUpTimer_Code[0x03];
    char ExtendedTime_Code[0x02];
    char TimeLimit_Kill_Code[0x06];

    char TimeLimit_VS_Kill_Code[7];
    char TimeLimit_VS_TimeLock1_Code[4];
    char TimeLimit_VS_TimeLock2_Code[6];
    char TimeLimit_VS_TimeLock3_Code[7];

    char TimeLimit_VS_MaxTime1_Code[10];
    char TimeLimit_VS_MaxTime2_Code[11];
    char TimeLimit_VS_MaxTime3_Code[10];

    void WriteUnlimitedTimeMovs(void* Min_Addr, void* Sec_Addr, void* Centi_Addr, int Mins, int Secs, int Centis)
    {
        uint8_t Min_Data[0x0A];
        Min_Data[0] = 0xC7;
        Min_Data[1] = 0x81;
        Min_Data[2] = 0xEC;
        Min_Data[3] = 0x00;
        Min_Data[4] = 0x00; 
        Min_Data[5] = 0x00;
        *(int32_t*)(Min_Data + 6) = Mins;
        WriteData(Min_Addr, Min_Data);
        //SonicMania.exe+E0D1 - C7 81 EC000000 09000000

        uint8_t Sec_Data[0x0B];
        Sec_Data[0] = 0xC7;
        Sec_Data[1] = 0x84;
        Sec_Data[2] = 0x86;
        Sec_Data[3] = 0xF0;
        Sec_Data[4] = 0x00;
        Sec_Data[5] = 0x00;
        Sec_Data[6] = 0x00;
        *(int32_t*)(Sec_Data + 7) = Secs;
        WriteData(Sec_Addr, Sec_Data);
        //SonicMania.exe+E0DB - C7 84 86 F0000000 3B000000

        uint8_t Centi_Data[0x0A];
        Centi_Data[0] = 0xC7;
        Centi_Data[1] = 0x81;
        Centi_Data[2] = 0xF4;
        Centi_Data[3] = 0x00; 
        Centi_Data[4] = 0x00;
        Centi_Data[5] = 0x00;
        *(int32_t*)(Centi_Data + 6) = Centis;
        WriteData(Centi_Addr, Centi_Data);
        //SonicMania.exe+E0E6 - C7 81 F4000000 63000000
    }

    void UpdateHurryUpTimer() 
    {
        if (SonicMania::Timer.Enabled == false) return;

        void* HurryTimer_Addr = (void*)(baseAddress + 0xDE46);
        // NOP bytes
        char HurryTimer_NOPS[3];
        // NOP Memset
        memset(HurryTimer_NOPS, 0x90, sizeof HurryTimer_NOPS);

        if (!HasCopiedOriginalHurryTimerCode)
        {
            // Copy Original Unmodified Code
            memcpy(HurryUpTimer_Code, HurryTimer_Addr, 0x03);
            HasCopiedOriginalHurryTimerCode = true;
        }

        if (CompPlus_Settings::NoHurryUpTimer)
        {
            if (!IsHurryTimerOffWriten)
            {
                //Disable The Hurry Up Timer
                WriteData(HurryTimer_Addr, HurryTimer_NOPS, 0x03);
                IsHurryTimerOffWriten = true;
                IsHurryTimerOnWriten = false;
            }
        }
        else
        {
            if (!IsHurryTimerOnWriten)
            {
                //Enable The Hurry Up Timer
                WriteData(HurryTimer_Addr, HurryUpTimer_Code, 0x03);
                IsHurryTimerOnWriten = true;
                IsHurryTimerOffWriten = false;
            }
        }
    }

    void UpdateTimer()
    {
        if (SonicMania::Timer.Enabled == false) return;

        void* ExtendedTime_Addr = (void*)(baseAddress + 0x535BD);
        void* TimeLimit_Kill_Addr = (void*)(baseAddress + 0xADD03);
        void* TimeLimit_Skip_JNE_Addr = (void*)(baseAddress + 0x00ADDE7);
        void* TimeLimit_Kill_JMP_Addr = (void*)(baseAddress + 0xADD03 + 0x5);

        void* TimeLimit_VS_Kill_Adrr = (void*)(baseAddress + 0xADD9F);
        void* TimeLimit_VS_TimeLock1_Adrr = (void*)(baseAddress + 0xADD21);
        void* TimeLimit_VS_TimeLock2_Adrr = (void*)(baseAddress + 0xADD1B); 
        void* TimeLimit_VS_TimeLock3_Adrr = (void*)(baseAddress + 0xADD25);

        void* TimeLimit_VS_MaxTime1_Adrr = (void*)(baseAddress + 0xE0D1);
        void* TimeLimit_VS_MaxTime2_Adrr = (void*)(baseAddress + 0xE0DB);
        void* TimeLimit_VS_MaxTime3_Adrr = (void*)(baseAddress + 0xE0E6);

        // NOP bytes
        char ExtendedTime_NOPS[8];
        char TimeLimit_VS_Kill_NOPS[7];
        char TimeLimit_VS_TimeLock1_NOPS[4];
        char TimeLimit_VS_TimeLock2_NOPS[6];
        char TimeLimit_VS_TimeLock3_NOPS[7];

        // NOP Memset
        memset(ExtendedTime_NOPS, 0x90, sizeof ExtendedTime_NOPS);
        memset(TimeLimit_VS_Kill_NOPS, 0x90, sizeof TimeLimit_VS_Kill_NOPS);
        memset(TimeLimit_VS_TimeLock1_NOPS, 0x90, sizeof TimeLimit_VS_TimeLock1_NOPS);
        memset(TimeLimit_VS_TimeLock2_NOPS, 0x90, sizeof TimeLimit_VS_TimeLock2_NOPS);
        memset(TimeLimit_VS_TimeLock3_NOPS, 0x90, sizeof TimeLimit_VS_TimeLock3_NOPS);

        if (!HasCopiedOriginalTimeCode)
        {
            // Copy Original Unmodified Code
            memcpy(ExtendedTime_Code, ExtendedTime_Addr, 0x02);
            memcpy(TimeLimit_Kill_Code, TimeLimit_Kill_Addr, 0x06);
            memcpy(TimeLimit_VS_Kill_Code, TimeLimit_VS_Kill_Adrr, 0x07);
            memcpy(TimeLimit_VS_TimeLock1_Code, TimeLimit_VS_TimeLock1_Adrr, 0x04);
            memcpy(TimeLimit_VS_TimeLock2_Code, TimeLimit_VS_TimeLock2_Adrr, 0x06);
            memcpy(TimeLimit_VS_TimeLock3_Code, TimeLimit_VS_TimeLock3_Adrr, 0x07);
            memcpy(TimeLimit_VS_MaxTime1_Code, TimeLimit_VS_MaxTime1_Adrr, 0x0A);
            memcpy(TimeLimit_VS_MaxTime2_Code, TimeLimit_VS_MaxTime2_Adrr, 0x0B);
            memcpy(TimeLimit_VS_MaxTime3_Code, TimeLimit_VS_MaxTime3_Adrr, 0x0A);
            HasCopiedOriginalTimeCode = true;
        }

        if (!CompPlus_Settings::TimeLimit)
        {
            if (!IsUnlimitedWriten)
            {
                //Disable The Time Limit
                WriteData(ExtendedTime_Addr, ExtendedTime_NOPS, 0x02);
                ReplaceJNEwithJump(TimeLimit_Kill_Addr, TimeLimit_Skip_JNE_Addr);
                WriteData(TimeLimit_VS_Kill_Adrr, TimeLimit_VS_Kill_NOPS, 0x07);
                WriteData(TimeLimit_VS_TimeLock1_Adrr, TimeLimit_VS_TimeLock1_NOPS, 0x04);
                WriteData(TimeLimit_VS_TimeLock2_Adrr, TimeLimit_VS_TimeLock2_NOPS, 0x06);
                WriteData(TimeLimit_VS_TimeLock3_Adrr, TimeLimit_VS_TimeLock3_NOPS, 0x07);
                WriteUnlimitedTimeMovs(TimeLimit_VS_MaxTime1_Adrr, TimeLimit_VS_MaxTime2_Adrr, TimeLimit_VS_MaxTime3_Adrr, 99, 99, 99);
                IsUnlimitedWriten = true;
                IsLimitedWriten = false;
            }
        }
        else
        {
            if (!IsLimitedWriten)
            {
                //Enable The Time Limit
                WriteData(ExtendedTime_Addr, ExtendedTime_Code, 0x02);
                WriteData(TimeLimit_Kill_Addr, TimeLimit_Kill_Code, 0x06);
                WriteData(TimeLimit_VS_Kill_Adrr, TimeLimit_VS_Kill_Code, 0x07);
                WriteData(TimeLimit_VS_TimeLock1_Adrr, TimeLimit_VS_TimeLock1_Code, 0x04);
                WriteData(TimeLimit_VS_TimeLock2_Adrr, TimeLimit_VS_TimeLock2_Code, 0x06);
                WriteData(TimeLimit_VS_TimeLock3_Adrr, TimeLimit_VS_TimeLock3_Code, 0x07);
                WriteData(TimeLimit_VS_MaxTime1_Adrr, TimeLimit_VS_MaxTime1_Code, 0x0A);
                WriteData(TimeLimit_VS_MaxTime2_Adrr, TimeLimit_VS_MaxTime2_Code, 0x0B);
                WriteData(TimeLimit_VS_MaxTime3_Adrr, TimeLimit_VS_MaxTime3_Code, 0x0A);
                IsLimitedWriten = true;
                IsUnlimitedWriten = false;
            }
        }
    }

    void OnFrame() 
    {
        UpdateHurryUpTimer();
        UpdateTimer();
        UpdateVSControlLockState();
    }
}