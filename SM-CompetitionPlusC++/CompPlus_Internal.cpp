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
    char ETA_OriginalCode[0x02];
    char TLK_OriginalCode[0x06];

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

    void UpdateTimer()
    {
        if (SonicMania::Timer.Enabled == false) return;
        void* extended_time_address = (void*)(baseAddress + 0x535BD);
        void* time_limit_kill_jne_address = (void*)(baseAddress + 0xADD03);
        void* time_limit_skip_jne_adderss = (void*)(baseAddress + 0x00ADDE7);
        void* time_limit_kill_jmp_nop_address = (void*)(baseAddress + 0xADD03 + 0x5);
        // NOP bytes
        char nops1[4];
        char nops2[8];
        memset(nops1, 0x90, sizeof nops1);
        memset(nops2, 0x90, sizeof nops2);

        if (!HasCopiedOriginalTimeCode)
        {
            memcpy(ETA_OriginalCode, extended_time_address, 0x02);
            memcpy(TLK_OriginalCode, time_limit_kill_jne_address, 0x06);
            HasCopiedOriginalTimeCode = true;
        }

        if (!CompPlus_Settings::TimeLimit)
        {
            if (!IsUnlimitedWriten)
            {
                WriteData(extended_time_address, nops2, 0x02);
                ReplaceJNEwithJump(time_limit_kill_jne_address, time_limit_skip_jne_adderss);
                WriteData(time_limit_kill_jmp_nop_address, nops1, 0x01);
                IsUnlimitedWriten = true;
                IsLimitedWriten = false;
            }
        }
        else
        {
            if (!IsLimitedWriten)
            {
                WriteData(extended_time_address, ETA_OriginalCode, 0x02);
                WriteData(time_limit_kill_jne_address, TLK_OriginalCode, 0x06);
                IsLimitedWriten = true;
                IsUnlimitedWriten = false;
            }
        }
    }

    void OnFrame() 
    {
        UpdateTimer();
    }
}