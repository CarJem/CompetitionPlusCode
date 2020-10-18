#include "stdafx.h"
#include "ManiaModLoader.h"
#include "SonicMania.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "CompPlus_Extensions/IZAPI.h"
#include "CompPlus_Extensions/Helpers.h"
#include "CompPlus_Extensions/TitleCardColors.h"

#include "CompPlus_Scenes/Custom Scenes/GustPlanet.h"
#include "CompPlus_Scenes/Custom Scenes/LHPZ.h"

#include "CompPlus_Scenes/General Scenes/SceneTweaks.h"
#include "CompPlus_Scenes/General Scenes/ManiaMenu.h"
#include "CompPlus_Scenes/General Scenes/CreditsScene.h"
#include "CompPlus_Scenes/General Scenes/SettingsMenu.h"
#include "CompPlus_Scenes/General Scenes/GenericLogos.h"

#include "CompPlus_Scenes/Functionality/ZoneSpecifics.h"
#include "CompPlus_Scenes/Functionality/SpecialRings.h"
#include "CompPlus_Scenes/Functionality/EntityLoop.h"
#include "CompPlus_Scenes/Functionality/SizeLazer.h"

#include "CompPlus_Scenes/Level Select/ManiaLevelSelect.h"
#include "CompPlus_Scenes/Level Select/EncoreLevelSelect.h"
#include "CompPlus_Scenes/Level Select/CustomLevelSelect.h"
#include "CompPlus_Scenes/Level Select/ChaotixLevelSelect.h"
#include "CompPlus_Scenes/Level Select/ExeLevelSelect.h"
#include "CompPlus_Scenes/Level Select/PhantomLevelSelect.h"
#include "CompPlus_Scenes/Level Select/NextGenerationLevelSelectCore.h"

#include "Base.h"
#include "CompPlus_Core/CompPlus_Scoring.h"
#include "CompPlus_Core/CompPlus_Announcers.h"
#include "CompPlus_Core/CompPlus_Controllers.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_DevMenu.h"
#include "CompPlus_Core/CompPlus_Status.h"

#include "CompPlus_Scenes/HUB World/HubWorld.h"
#include "CompPlus_Scenes/HUB World/HubRanking.h"
#include "CompPlus_Scenes/HUB World/HubSettings.h"
#include "CompPlus_Scenes/HUB World/HubText.h"

#include <iostream>
#include <fstream>

extern "C"
{
    using namespace SonicMania;

    namespace CompPlus_Internal
    {
        const char* FullPath;

        bool LoadedSounds = false;

        #pragma region One Time Patches

        void DoMenuOnScreenDraw()
        {
            if (SonicMania::GameState & SonicMania::GameState_Running)
            {
                CompPlus_Core::OnDraw();
            }
        }

        static int OnScreenDrawReturn = baseAddress + 0x53600;
        static __declspec(naked) void OnScreenDrawHook()
        {
            __asm
            {
                pushad;
            }
            DoMenuOnScreenDraw();
            __asm
            {
                popad;
                cmp dword ptr[edi + 0x00000154], 0x00
                    jmp OnScreenDrawReturn
            }
        }
        void PatchOnScreenDrawHook()
        {
            WriteData<7>((void*)(baseAddress + 0x535FA), 0x90);
            WriteJump((void*)(baseAddress + 0x535FA), OnScreenDrawHook);
        }

        static int OnMenuScreenDrawReturn = baseAddress + 0x7FFE;
        static __declspec(naked) void OnMenuScreenDrawHook()
        {
            __asm
            {
                pushad;
            }
            DoMenuOnScreenDraw();
            __asm
            {
                popad;
                mov edi, ecx
                    mov[ebp - 0x10], eax
                    jmp OnMenuScreenDrawReturn
            }
        }
        void PatchMenuOnScreenDrawHook()
        {
            WriteData<5>((void*)(baseAddress + 0x7FF9), 0x90);
            WriteJump((void*)(baseAddress + 0x7FF9), OnMenuScreenDrawHook);
        }

        SonicMania::GameStates ActComplete_hook()
        {
            CompPlus_Core::OnActClear();
            return SonicMania::GameState;
        }

        #pragma endregion

        #pragma region Dynamic Patches

        bool HasCopiedOriginalTimeCode = false;
        bool HasCopiedOriginalPlayerKillCode = false;
        bool HasCopiedOriginalHurryTimerCode = false;
        bool InitalInputCollected = false;
        bool HasCopiedOriginalControlUnlockCode = false;
        bool HasCopiedSpecialRingWarpCode = false;
        bool HasCopiedWorldPositionWriteCode = false;

        bool isUnlockWriten = false;
        bool isLockWriten = false;
        bool IsLimitedWriten = false;
        bool IsUnlimitedWriten = false;
        bool PlayerKillCodeWriten = false;
        bool IsHurryTimerOffWriten = false;
        bool IsHurryTimerOnWriten = false;
        bool IsDisableSpecialRingWarpWritten = false;
        bool IsWorldPositionWriteDisableWritten = false;

        char PlayerKill_OriginalCode[0x02];
        char ControlLock_OriginalCode[0x06];
        char ControlLock_OriginalSoundCode3[0x06];
        char ControlLock_OriginalSoundCode2[0x06];
        char ControlLock_OriginalSoundCode1[0x06];
        char ControlLock_OriginalSoundCodeGO[0x06];
        char HurryUpTimer_Code[0x03];
        char ExtendedTime_Code[0x02];
        char TimeLimit_Kill_Code[0x06];
        char TimeLimit_VS_Kill_Code[0x07];
        char TimeLimit_VS_TimeLock1_Code[0x04];
        char TimeLimit_VS_TimeLock2_Code[0x06];
        char TimeLimit_VS_TimeLock3_Code[0x07];
        char TimeLimit_VS_MaxTime1_Code[0x0A];
        char TimeLimit_VS_MaxTime2_Code[0x0B];
        char TimeLimit_VS_MaxTime3_Code[0x0A];
        char SpecialRingWarp_Code[0x02];
        char SpecialRingWarp2_Code[0x06];
        char worldX_write1_Code[0x07];
        char worldX_write2_Code[0x07];
        char worldX_write3_Code[0x07];
        char worldY_write1_Code[0x07];
        char worldY_write2_Code[0x07];
        char worldY_write3_Code[0x07];

        void UpdateWorldPositionWriteDisable()
        {
            void* worldX_write_address_1 = (void*)(baseAddress + 0x1FC4);
            void* worldX_write_address_2 = (void*)(baseAddress + 0x1F05);
            void* worldX_write_address_3 = (void*)(baseAddress + 0x1F42);
            void* worldY_write_address_1 = (void*)(baseAddress + 0x1F25);
            void* worldY_write_address_2 = (void*)(baseAddress + 0x1FD8);
            void* worldY_write_address_3 = (void*)(baseAddress + 0x1F89);

            // NOP bytes
            char nops[7];
            memset(nops, 0x90, sizeof nops);


            if (!HasCopiedWorldPositionWriteCode)
            {
                memcpy(worldX_write1_Code, worldX_write_address_1, 0x07);
                memcpy(worldX_write2_Code, worldX_write_address_2, 0x07);
                memcpy(worldX_write3_Code, worldX_write_address_3, 0x07);
                memcpy(worldY_write1_Code, worldY_write_address_1, 0x07);
                memcpy(worldY_write2_Code, worldY_write_address_2, 0x07);
                memcpy(worldY_write3_Code, worldY_write_address_3, 0x07);
                HasCopiedWorldPositionWriteCode = true;
            }

            if (CompPlus_Status::DisableWorldPositionWrite)
            {
                if (!IsWorldPositionWriteDisableWritten)
                {
                    WriteData(worldX_write_address_1, nops, 0x07);
                    WriteData(worldX_write_address_2, nops, 0x07);
                    WriteData(worldX_write_address_3, nops, 0x07);
                    WriteData(worldY_write_address_1, nops, 0x07);
                    WriteData(worldY_write_address_2, nops, 0x07);
                    WriteData(worldY_write_address_3, nops, 0x07);
                    IsWorldPositionWriteDisableWritten = true;
                }
            }
            else
            {
                if (IsWorldPositionWriteDisableWritten)
                {
                    WriteData(worldX_write_address_1, worldX_write1_Code, 0x07);
                    WriteData(worldX_write_address_2, worldX_write2_Code, 0x07);
                    WriteData(worldX_write_address_3, worldX_write3_Code, 0x07);
                    WriteData(worldY_write_address_1, worldY_write1_Code, 0x07);
                    WriteData(worldY_write_address_2, worldY_write2_Code, 0x07);
                    WriteData(worldY_write_address_3, worldY_write3_Code, 0x07);
                    IsWorldPositionWriteDisableWritten = false;
                }
            }
        }

        void UpdateDisableSpecialRingWarp()
        {
            void* special_ring_jmp = (void*)(baseAddress + 0x2285F);
            void* special_ring_nop = (void*)(baseAddress + 0x2246C);

            // NOP bytes
            char jmp[0x02];
            jmp[0] = 0xEB;
            jmp[1] = 0x30;

            char nops[0x06];
            memset(nops, 0x90, sizeof nops);

            if (!HasCopiedSpecialRingWarpCode)
            {
                memcpy(SpecialRingWarp_Code, special_ring_jmp, 0x02);
                memcpy(SpecialRingWarp2_Code, special_ring_nop, 0x06);
                HasCopiedSpecialRingWarpCode = true;
            }

            if (CompPlus_Status::EnableHUBSpecialRingFunctionality)
            {
                if (!IsDisableSpecialRingWarpWritten)
                {
                    WriteData(special_ring_jmp, jmp, 0x02);
                    WriteData(special_ring_nop, nops, 0x06);
                    IsDisableSpecialRingWarpWritten = true;
                }
            }
            else
            {
                if (IsDisableSpecialRingWarpWritten)
                {
                    WriteData(special_ring_jmp, SpecialRingWarp_Code, 0x02);
                    WriteData(special_ring_nop, SpecialRingWarp2_Code, 0x06);
                    IsDisableSpecialRingWarpWritten = false;
                }
            }
        }

        void UpdatePlayerKillAbility()
        {
            void* player_kill_jmp = (void*)(baseAddress + 0xC5A43);

            // NOP bytes
            char jmp[0x02];
            jmp[0] = 0xEB;
            jmp[1] = 0x12;


            if (!HasCopiedOriginalPlayerKillCode)
            {
                memcpy(PlayerKill_OriginalCode, player_kill_jmp, 0x02);
                HasCopiedOriginalPlayerKillCode = true;
            }

            if (CompPlus_Status::DisablePlayerDying)
            {
                if (!PlayerKillCodeWriten)
                {
                    WriteData(player_kill_jmp, jmp, 0x02);
                    PlayerKillCodeWriten = true;
                }
            }
            else
            {
                if (PlayerKillCodeWriten)
                {
                    WriteData(player_kill_jmp, PlayerKill_OriginalCode, 0x02);
                    PlayerKillCodeWriten = false;
                }
            }
        }

        void UpdateVSControlLockState()
        {
            void* vs_player_freeze_address = (void*)(baseAddress + 0xC3E2B);
            void* vs_announcer_three_address = (void*)(baseAddress + 0x135A8);
            void* vs_announcer_two_address = (void*)(baseAddress + 0x135C3);
            void* vs_announcer_one_address = (void*)(baseAddress + 0x135DE);
            void* vs_announcer_go_address = (void*)(baseAddress + 0x13682);

            // NOP bytes
            char nops[6];
            char nops2[6];
            char nops3[6];
            char nops4[6];
            char nops5[6];
            memset(nops, 0x90, sizeof nops);
            memset(nops2, 0x90, sizeof nops2);
            memset(nops3, 0x90, sizeof nops3);
            memset(nops4, 0x90, sizeof nops4);
            memset(nops5, 0x90, sizeof nops5);


            if (!HasCopiedOriginalControlUnlockCode)
            {
                memcpy(ControlLock_OriginalCode, vs_player_freeze_address, 0x06);
                memcpy(ControlLock_OriginalSoundCode3, vs_announcer_three_address, 0x06);
                memcpy(ControlLock_OriginalSoundCode2, vs_announcer_two_address, 0x06);
                memcpy(ControlLock_OriginalSoundCode1, vs_announcer_one_address, 0x06);
                memcpy(ControlLock_OriginalSoundCodeGO, vs_announcer_go_address, 0x06);
                HasCopiedOriginalControlUnlockCode = true;
            }

            if (!CompPlus_Status::isVSControllerInputUnlocked)
            {
                if (!isLockWriten)
                {
                    WriteData(vs_player_freeze_address, ControlLock_OriginalCode, 0x06);
                    WriteData(vs_announcer_three_address, ControlLock_OriginalSoundCode3, 0x06);
                    WriteData(vs_announcer_two_address, ControlLock_OriginalSoundCode2, 0x06);
                    WriteData(vs_announcer_one_address, ControlLock_OriginalSoundCode1, 0x06);
                    WriteData(vs_announcer_go_address, ControlLock_OriginalSoundCodeGO, 0x06);
                    isUnlockWriten = false;
                    isLockWriten = true;
                }
            }
            else
            {
                if (!isUnlockWriten)
                {
                    WriteData(vs_player_freeze_address, nops, 0x06);
                    WriteData(vs_announcer_three_address, nops2, 0x06);
                    WriteData(vs_announcer_two_address, nops3, 0x06);
                    WriteData(vs_announcer_one_address, nops4, 0x06);
                    WriteData(vs_announcer_go_address, nops5, 0x06);
                    isLockWriten = false;
                    isUnlockWriten = true;
                }
            }
        }

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

        void DisableVSPointAddingAddress()
        {
            void* vs_incrementing_address = (void*)(baseAddress + 0xE35C);
            char nops[2];
            memset(nops, 0x90, sizeof nops);
            WriteData(vs_incrementing_address, nops, 0x02);
        }

        void FixRayAndMighty2P()
        {
            int PatchP2Ray[] = { 0xE9, 0xC4, 0x01, 0x00, 0x00, 0x90 };
            int i;
            int OffsetNormal = 0xC31E5;
            for (i = 0; i < 6; i++)
            {
                WriteData<1>((void*)(baseAddress + OffsetNormal), PatchP2Ray[i]); //put data back.
                OffsetNormal++;

            }
        }

        void FixSummary()
        {
            //Remove A/Start from the Game Summary
            WriteData((BYTE*)(baseAddress + 0x00190618), (BYTE)0xEB);
        }

        #pragma endregion

        #pragma region Initilization

        extern void InitMod()
        {
            CompPlus_HubText::Init();
            CompPlus_ManiaMenu::Init();
            CompPlus_Credits::Init();
        }

        extern void InitAnnouncerFX()
        {
            CompPlus_Announcers::LoadAnnouncerFX();
        }

        extern void InitSettings(const char* path)
        {
            CompPlus_Settings::Settings_FilePath = path;
            CompPlus_Settings::LoadSettings();
        }

        #pragma endregion

        #pragma region Normal Defines

        void LoadSounds()
        {
            if (!LoadedSounds)
            {
                //Load Sounds on First Run. //Global Scope fine for most things
                SonicMania::LoadSoundFX(CompPlus_Common::SFX_MenuBleepClassic, SonicMania::Scope_Global);
                SonicMania::LoadSoundFX(CompPlus_Common::SFX_MenuAcceptClassic, SonicMania::Scope_Global);
                SonicMania::LoadSoundFX(CompPlus_Common::SFX_GPZButton, SonicMania::Scope_Global);
                SonicMania::LoadSoundFX(CompPlus_Common::SFX_LHPZSecret, SonicMania::Scope_Global);
                LoadedSounds = true;
            }
        }

        void OnReset() 
        {
            CompPlus_Settings::UpdateStrechScreen();
            CompPlus_Core::OnSceneReset();
        }

        void DynamicPatchesOnFrame()
        {
            UpdateDisableSpecialRingWarp();
            UpdateHurryUpTimer();
            UpdateTimer();
            UpdateVSControlLockState();
            UpdatePlayerKillAbility();
            UpdateWorldPositionWriteDisable();
        }

        void OnFrame_Running() 
        {
            LoadSounds();
            if (!(SonicMania::GameState & SonicMania::GameState_SoftPause)) CompPlus_Core::OnRunning();
            CompPlus_Settings::UpdateStrechScreen();
            UpdateCompPlusDevMenu();
        }

        void OnFrame_NotRunning()
        {
            OnReset();
        }

        void OnFrame_SoftPause()
        {
            OnReset();
        }

        void OnFrame_Always() 
        {
            if (!(SonicMania::GameState & SonicMania::GameState & SonicMania::GameState_NotRunning)) 
            {
                CompPlus_Core::OnConstantFrame();
            }
        }

        __declspec(dllexport) void OnScreenUpdate()
        {
            //Code Here Runs when the Game Updates the Screen Position.
        }

        __declspec(dllexport) void OnFrame()
        {
            int multiplier = FrameMultiplier;
            for (int i = 0; i < multiplier; i++)
            {
                OnFrame_Always();
                if (SonicMania::GameState & SonicMania::GameState_Running) OnFrame_Running();
                else if (SonicMania::GameState & SonicMania::GameState_NotRunning) OnFrame_NotRunning();
                else if (SonicMania::GameState & SonicMania::GameState_SoftPause) OnFrame_SoftPause();
            }
        }

        __declspec(dllexport) void Init(const char* path)
        {
            char buffer[MAX_PATH];
            GetCurrentDirectoryA(MAX_PATH, buffer);
            FullPath = buffer;
            SetCurrentDirectoryA(path);
            // Load files here
            SetCurrentDirectoryA(buffer);
            PatchOnScreenDrawHook();
            //PatchMenuOnScreenDrawHook();
            InitMod();
            TileCardColors::Init();
            CompPlus_NextGenerationLevelSelectCore::Init(path);
        }

        __declspec(dllexport) void PostInit(const char* path)
        {
            WriteJump((void*)(baseAddress + 0x001EF0B2), ActComplete_hook);
            const std::string path_cpp = path;
            IZAPI::IZInit();
            InitSettings((path_cpp + "\\Settings.xml").c_str());
            IZAPI::LoadStagesFile((path_cpp + "\\Stages.xml").c_str());
            IZAPI::RegisterStageLoadEvent(CompPlus_Core::OnStageLoad);
            IZAPI::RegisterStageUnloadEvent(CompPlus_Core::OnStageUnload);
            InitAnnouncerFX();

        }

        __declspec(dllexport) ModInfo ManiaModInfo = { ModLoaderVer, GameVer };

        #pragma endregion
    }

    namespace CompPlus_Core 
    {
        #pragma region Variables

        char* SceneDirectory = (char*)(baseAddress + 0xA5359C);

        //Internal Paramater Variables
        bool StartupStageEnabled = false;

        //Status Variables
        bool HasStartupInit = false;
        bool StageRefresh = true;
        int LastSceneID = 0;
        int IZ_SceneChangeIdleTime = 0;
        HMODULE InfinityZoneDLL = nullptr;
        IZAPI::StageInfo CurrentStage = {};

        #pragma endregion

        #pragma region Zone Loops

        void IZRunningLoop()
        {
            if (IZ_SceneChangeIdleTime == 0)
            {
                if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Mania)) CompPlus_ManiaLevelSelect::OnFrame();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Encore)) CompPlus_EncoreLevelSelect::OnFrame();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Custom)) CompPlus_CustomLevelSelect::OnFrame();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Chaotix)) CompPlus_ChaotixLevelSelect::OnFrame();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Phantom)) CompPlus_PhantomLevelSelect::OnFrame();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Exe)) CompPlus_ExeLevelSelect::OnFrame();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_Unused_SettingsWorld)) CompPlus_Settings_Base::OnFrame();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_Logos2)) CompPlus_GenericLogos::UpdateATGLogos();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_Logos3)) CompPlus_GenericLogos::UpdateCJLogos();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_Logos4)) CompPlus_GenericLogos::UpdateIZLogos();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_GPZ1)) CompPlus_Scene_GustPlanet::OnFrame();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_GPZ1E)) CompPlus_Scene_GustPlanet::OnFrame();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_LHPZ1)) CompPlus_Scene_LHPZ::OnFrame();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_LHPZ1E)) CompPlus_Scene_LHPZ::OnFrame();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBWorld)) CompPlus_HubWorld::OnFrame();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBWorld_EXE)) CompPlus_HubWorld::OnFrame();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBRanking)) CompPlus_HubRanking::OnFrame();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBSettings)) CompPlus_HubSettings::OnFrame();
                CompPlus_Credits::OnFrame(!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_Credits));
                CompPlus_SceneTweaks::UpdateScenes(CurrentStage.SceneKey);
            }
            else
            {
                IZ_SceneChangeIdleTime = IZ_SceneChangeIdleTime - 1;
            }
        }

        void NormalRunningLoop()
        {
            if (CurrentSceneInt == 0) CompPlus_SceneTweaks::UpdateScenes("1");
            else if (CurrentSceneInt == 1) CompPlus_SceneTweaks::UpdateScenes("0");
            else if (CurrentSceneInt == 65) CompPlus_Common::LoadHUBWorld();
            else if (CurrentSceneInt == 66) CompPlus_Common::LoadLastLevelSelect();
            else if (CurrentSceneInt == 123) CompPlus_Common::LoadLevel_IZ(CompPlus_Common::SMCP_Logos2);
            else if (CurrentSceneInt == 2) CompPlus_ManiaMenu::UpdateManiaMenu();
            else if (CurrentSceneInt == SceneExt::Scene_Credits) CompPlus_Common::LoadLevel_IZ(CompPlus_Common::HUBSettings);
            else if (CurrentSceneInt == SceneExt::Scene_PuyoPuyo) CompPlus_Scoring::ApplyPoyoPoyoRuleset();
        }

        void RunningSceneLoop() 
        {
            if (CurrentStage.StageKey) IZRunningLoop();
            else NormalRunningLoop();
        }

        #pragma endregion

        #pragma region General Methods

        void OnConstantFrame() 
        {
            if (CurrentStage.SceneKey)
            {
                if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Mania)) CompPlus_ManiaLevelSelect::OnPreload();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Encore)) CompPlus_EncoreLevelSelect::OnPreload();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Custom)) CompPlus_CustomLevelSelect::OnPreload();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Chaotix)) CompPlus_ChaotixLevelSelect::OnPreload();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Exe)) CompPlus_ExeLevelSelect::OnPreload();
                CompPlus_ZoneSpecifics::UpdateSpecifics(CurrentStage.SceneKey, -1);
            }
            else CompPlus_ZoneSpecifics::UpdateSpecifics("", CurrentSceneInt);
        }

        void OnInit()
        {
            if (StartupStageEnabled)
            {
                CompPlus_Common::LoadLevel(2);
            }
            HasStartupInit = true;
        }

        void ResetLSelects()
        {
            CompPlus_ManiaLevelSelect::CheckForPointRefresh();
            CompPlus_EncoreLevelSelect::CheckForPointRefresh();
            CompPlus_CustomLevelSelect::CheckForPointRefresh();
            CompPlus_ChaotixLevelSelect::CheckForPointRefresh();
            CompPlus_ExeLevelSelect::CheckForPointRefresh();
        }

        void OnStageRefresh()
        {
            CompPlus_Announcers::ReloadAnnouncerFX();
            CompPlus_Settings::RefreshSettings();
            CompPlus_Scoring::OnSceneReset();
            ResetLSelects();
            StageRefresh = false;
        }

        void OnLegacySceneChange()
        {
            LastSceneID = CurrentSceneInt;
            StageRefresh = true;
        }

        void OnSceneReset()
        {
            if (!(GameState & GameState_NotRunning)) CompPlus_HubWorld::isRestart = true;
            if (!(GameState & GameState_NotRunning)) CompPlus_HubCore::isRestart = true;
            ResetLSelects();
            CompPlus_Status::SpecialRingsNeedRefresh = true;
            CompPlus_Credits::ResetScene();
            CompPlus_Settings::RefreshSettings();
            CompPlus_Scene_GustPlanet::OnReset();
            CompPlus_SizeLazer::RefreshChibiSprites = true;
        }

        void OnRunning()
        {
            if (!HasStartupInit) OnInit();
            if (StageRefresh) OnStageRefresh();
            if (LastSceneID != CurrentSceneInt) OnLegacySceneChange();
            CompPlus_Settings::OnFrame();
            CompPlus_Scoring::OnFrame();
            CompPlus_Controllers::OnFrame();
            CompPlus_Internal::DynamicPatchesOnFrame();
            CompPlus_SpecialRings::UpdateSpecialRings();
            CompPlus_EntityLoop::OnFrame();
            RunningSceneLoop();
        }

        void OnDraw()
        {
            CompPlus_Settings_Base::DoMenuOnScreenDraw();

            if (CurrentStage.SceneKey) 
            {
                if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Mania)) CompPlus_ManiaLevelSelect::OnDraw();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Encore)) CompPlus_EncoreLevelSelect::OnDraw();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Custom)) CompPlus_CustomLevelSelect::OnDraw();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Chaotix)) CompPlus_ChaotixLevelSelect::OnDraw();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Exe)) CompPlus_ExeLevelSelect::OnDraw();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBWorld)) CompPlus_HubCore::OnDraw();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBWorld_EXE)) CompPlus_HubCore::OnDraw();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBRanking)) CompPlus_HubCore::OnDraw();
                else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBSettings)) CompPlus_HubCore::OnDraw();
            }
        }

        void OnActClear()
        {

        }

        #pragma endregion

        #pragma region InfinityZone Calls

        void __cdecl OnStageLoad(IZAPI::StageInfo info, IZAPI::StageLoadPhase phase)
        {
            printf("StageLoad: %s\n", info.StageName);
            CurrentStage = info;
            StageRefresh = true;
            IZ_SceneChangeIdleTime = 10;
            CompPlus_ZoneSpecifics::UpdateSpecifics(CurrentStage.SceneKey, CurrentSceneInt);
            OnSceneReset();
        }

        void __cdecl OnStageUnload(IZAPI::StageInfo info, IZAPI::StageLoadPhase phase)
        {
            printf("StageUnload: %s\n", info.StageName);
            CurrentStage = { };
            StageRefresh = true;
            IZ_SceneChangeIdleTime = 10;
            if (!strcmp(info.StageKey, CompPlus_Common::SMCP_Logos1) && (CurrentSceneInt == 1 || CurrentSceneInt == 4)) CompPlus_Common::LoadLevel(123);
            CompPlus_ZoneSpecifics::UpdateSpecifics("", CurrentSceneInt);
            OnSceneReset();
        }

        #pragma endregion
    }
}

