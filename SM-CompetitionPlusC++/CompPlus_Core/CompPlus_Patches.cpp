#include "CompPlus_Patches.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "include/ManiaAPI/SonicMania.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "CompPlus_Extensions/IZAPI.h"
#include "CompPlus_Extensions/Helpers.h"

#include "CompPlus_Scenes/Custom Scenes/GustPlanet.h"
#include "CompPlus_Scenes/Custom Scenes/LHPZ.h"

#include "CompPlus_Core/CompPlus_Scenes.h"
#include "CompPlus_Scenes/General Scenes/ManiaMenu.h"
#include "CompPlus_Scenes/General Scenes/CreditsScene.h"
#include "CompPlus_Scenes/General Scenes/PlayerSettings.h"
#include "CompPlus_Scenes/General Scenes/GenericLogos.h"
#include "CompPlus_Scenes/General Scenes/TitleScreen.h"

#include "CompPlus_Functionality/ZoneSpecifics.h"
#include "CompPlus_Functionality/SpecialRings.h"
#include "CompPlus_Functionality/EntityLoop.h"
#include "CompPlus_Functionality/SizeLazer.h"
#include "CompPlus_Functionality/Halloween2018.h"
#include "CompPlus_Functionality/VapeMusic.h"
#include "CompPlus_Functionality/DynCam.h"
#include "CompPlus_Functionality/PlayerSkins.h"
#include "CompPlus_Functionality/SpeedShoesMods.h"

#include "CompPlus_Scenes/Level Select/ManiaLevelSelect.h"
#include "CompPlus_Scenes/Level Select/EncoreLevelSelect.h"
#include "CompPlus_Scenes/Level Select/CustomLevelSelect.h"
#include "CompPlus_Scenes/Level Select/ChaotixLevelSelect.h"
#include "CompPlus_Scenes/Level Select/ExeLevelSelect.h"
#include "CompPlus_Scenes/Level Select/PhantomLevelSelect.h"
#include "CompPlus_Scenes/Level Select/CoreLevelSelect.h"

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

namespace CompPlus_Patches 
{

    #pragma region On Round Clear Patch

    void OnRoundClear()
    {
        CompPlus_Scoring::SetRoundEndWinner();
    }
    static int OnRoundClearRET = baseAddress + 0xAF594;
    static int OnRoundClearJMP = baseAddress + 0xAF58E;
    static __declspec(naked) void OnRoundClearHook()
    {
        __asm
        {
            pushad;
        }
        OnRoundClear();
        __asm
        {
            popad;
            mov[ecx + 0x00031120], eax;
            jmp OnRoundClearRET;
        }
    }

    static int OnRoundClearUnfinishedRET = baseAddress + 0xF6EE;
    static int OnRoundClearUnfinishedJMP = baseAddress + 0xF6E8;
    static __declspec(naked) void OnRoundClearUnfinishedHook()
    {
        __asm
        {
            pushad;
        }
        OnRoundClear();
        __asm
        {
            popad;
            mov eax, [edx + 00031114];
            jmp OnRoundClearUnfinishedRET;
        }
    }
    void PatchOnRoundClearHook()
    {
        WriteData<5>((void*)(OnRoundClearJMP), 0x90);
        WriteJump((void*)(OnRoundClearJMP), OnRoundClearHook);

        WriteData<6>((void*)(OnRoundClearUnfinishedJMP), 0x90);
        WriteJump((void*)(OnRoundClearUnfinishedJMP), OnRoundClearUnfinishedHook);
    }

    #pragma endregion

    #pragma region On Play Music Patch

    typedef int(__cdecl PlayMusicFile_BASS_type)(const char* name, unsigned int slot, int a3, unsigned int loopstart, int a5);
    PlayMusicFile_BASS_type* PlayMusicFile_BASS = nullptr;
    int __cdecl PlayMusicFile_BASS_r(const char* name, unsigned int a2, int a3, unsigned int loopstart, int a5)
    {
        CompPlus_VapeMusic::OnLoad((char*)CompPlus_Core::CurrentStage.SceneKey, name, a2, a3, loopstart, a5);
        CompPlus_SpeedShoesMods::OnMusicLoad((char*)CompPlus_Core::CurrentStage.SceneKey, name, a2, a3, loopstart, a5);
        return PlayMusicFile_BASS(name, a2, a3, loopstart, a5);
    }

    void PatchPlaySongBass()
    {
        DWORD Bassreturn;
        int BassLocation = baseAddress + 0x001BC600;
        VirtualProtect((void*)BassLocation, 0x00178000, PAGE_EXECUTE_READWRITE, &Bassreturn);

        PlayMusicFile_BASS = (PlayMusicFile_BASS_type*)GetAddressFromJump(baseAddress + 0x001BC640);
        WriteJump((void*)(baseAddress + 0x001BC640), PlayMusicFile_BASS_r);
    }

    #pragma endregion

    #pragma region Draw Water Patch

    static int OnWaterDrawReturn = baseAddress + 0x19B9D;

    int DrawWater(EntityAnimationData* AnimData, Vector2* Position, BOOL ScreenRelative)
    {
        ushort pointer = GetSpritePointer(0xAA7634, 0x14);
        int screen = 0;

        if (pointer == 0) screen = 0;
        else if (pointer == 1) screen = 1;
        else if (pointer == 2) screen = 2;
        else if (pointer == 3) screen = 3;

        int offset = 0x96030 * screen;

        int x = 0 - GetPointer(0xAA7628, 0x96000 + offset);
        int y = Position->Y - GetPointer(0xAA7628, 0x96004 + offset);

        auto color1 = CompPlus_Scenes::OnWaterColorDraw();
        DrawRect(x, y, 32000, 32000, color1.Color.ToRGB888(), color1.Alpha, color1.InkEffect, true);
        int ReturnVal = DrawSprite(AnimData, Position, ScreenRelative);
        return ReturnVal;
    }

    static __declspec(naked) void OnWaterDrawHook()
    {
        __asm
        {
            call DrawWater
            jmp OnWaterDrawReturn
        }
    }

    void PatchWaterDrawHook()
    {
        WriteData<6>((void*)(baseAddress + 0x19B97), 0x90);
        WriteJump((void*)(baseAddress + 0x19B97), OnWaterDrawHook);
    }

    #pragma endregion

    #pragma region HUB World Object Colors Patch

    void OnHUBWorldPreDraw()
    {
        CompPlus_Scenes::OnObjectPreDraw("HUBWorld");
    }

    void OnHUBWorldPostDraw()
    {
        CompPlus_Scenes::OnObjectPostDraw("HUBWorld");
    }

    static int OnDecorationDrawReturn = baseAddress + 0x673ED;
    static int OnStickyPlatformDrawReturn = baseAddress + 0x18F9C7;
    static int OnControlPanelADrawReturn = baseAddress + 0x16EF19;
    static int OnControlPanelBDrawReturn = baseAddress + 0x16EF2A;
    static int OnButtonDrawReturn = baseAddress + 0x864D0;

    static __declspec(naked) void OnDecorationDrawHook()
    {
        __asm
        {
            pushad;
        }
        OnHUBWorldPreDraw();
        __asm
        {
            popad;
            call DrawSprite;
            pushad;
        }
        OnHUBWorldPostDraw();
        __asm
        {
            popad;
            jmp OnDecorationDrawReturn;
        }
    }
    static __declspec(naked) void OnStickyPlatformDrawHook()
    {
        __asm
        {
            pushad;
        }
        OnHUBWorldPreDraw();
        __asm
        {
            popad;
            call DrawSprite;
            pushad;
        }
        OnHUBWorldPostDraw();
        __asm
        {
            popad;
            jmp OnStickyPlatformDrawReturn;
        }
    }
    static __declspec(naked) void OnButtonDrawHook()
    {
        __asm
        {
            pushad;
        }
        OnHUBWorldPreDraw();
        __asm
        {
            popad;
            call DrawSprite;
            pushad;
        }
        OnHUBWorldPostDraw();
        __asm
        {
            popad;
            jmp OnButtonDrawReturn;
        }
    }
    static __declspec(naked) void OnControlPanelADrawHook()
    {
        __asm
        {
            pushad;
        }
        OnHUBWorldPreDraw();
        __asm
        {
            popad;
            call DrawSprite;
            pushad;
        }
        OnHUBWorldPostDraw();
        __asm
        {
            popad;
            jmp OnControlPanelADrawReturn;
        }
    }
    static __declspec(naked) void OnControlPanelBDrawHook()
    {
        __asm
        {
            pushad;
        }
        OnHUBWorldPreDraw();
        __asm
        {
            popad;
            call DrawSprite
                pushad;
        }
        OnHUBWorldPostDraw();
        __asm
        {
            popad;
            jmp OnControlPanelBDrawReturn
        }
    }
    static __declspec(naked) void OnSetSpriteTest()
    {
        __asm
        {
            pushad;
        }
        OnHUBWorldPreDraw();
        __asm
        {
            popad;
            call DrawSprite
                pushad;
        }
        OnHUBWorldPostDraw();
        __asm
        {
            popad;
            jmp OnControlPanelBDrawReturn
        }
    }

    void PatchOnHUBDecorationScreenDrawHook()
    {
        //Decoration
        WriteData<6>((void*)(baseAddress + 0x673E7), 0x90);
        WriteJump((void*)(baseAddress + 0x673E7), OnDecorationDrawHook);

        //Button
        WriteData<6>((void*)(baseAddress + 0x864CA), 0x90);
        WriteJump((void*)(baseAddress + 0x864CA), OnButtonDrawHook);

        //StickyPlatform
        WriteData<6>((void*)(baseAddress + 0x18F9C1), 0x90);
        WriteJump((void*)(baseAddress + 0x18F9C1), OnStickyPlatformDrawHook);

        //Control Panel A
        WriteData<6>((void*)(baseAddress + 0x16EF13), 0x90);
        WriteJump((void*)(baseAddress + 0x16EF13), OnControlPanelADrawHook);

        //Control Panel B
        WriteData<6>((void*)(baseAddress + 0x16EF24), 0x90);
        WriteJump((void*)(baseAddress + 0x16EF24), OnControlPanelBDrawHook);
    }

    #pragma endregion

    #pragma region On Title Screen Patches

    int DrawTitleSprite(EntityAnimationData* AnimData, Vector2* Position, BOOL ScreenRelative)
    {
        int Result = CompPlus_TitleScreen::OnPlusLogoDraw(AnimData, Position, ScreenRelative);
        return Result;
    }

    static int OnTitlePlusDrawReturn = baseAddress + 0x10AC89;
    static __declspec(naked) void OnTitlePlusDrawHook()
    {
        __asm
        {
            call DrawTitleSprite
            jmp OnTitlePlusDrawReturn
        }
    }

    static int OnTitlePlusShineDrawReturn = baseAddress + 0x10AC9A;
    static __declspec(naked) void OnTitlePlusShineDrawHook()
    {
        __asm
        {
            pushad;
        }
        __asm
        {
            popad;
            call DrawTitleSprite
                jmp OnTitlePlusShineDrawReturn
        }
    }

    void PatchOnTitlePlusLogoDrawHook()
    {
        WriteData<6>((void*)(baseAddress + 0x10AC83), 0x90);
        WriteJump((void*)(baseAddress + 0x10AC83), OnTitlePlusDrawHook);

        WriteData<6>((void*)(baseAddress + 0x10AC94), 0x90);
        WriteJump((void*)(baseAddress + 0x10AC94), OnTitlePlusShineDrawHook);
    }

    #pragma endregion

    #pragma region On Timer Start Patch

    void DoOnStartTimer()
    {
        CompPlus_Halloween2018::OnStartTimer();
        CompPlus_DynCam::OnStartTimer();
    }

    static int HookStartTimerAddyJMPBACK = baseAddress + 0x016046;
    static __declspec(naked) void HookTimer()
    {
        __asm
        {
            mov[eax + 0x18], 0x00000000
            pushad;
        }
        DoOnStartTimer();
        __asm
        {
            popad;
            jmp HookStartTimerAddyJMPBACK
        }
    }

    void PatchHookOnStartTimer()
    {
        DWORD PatchOnTimerStart;
        int PatchOnTimerCode = baseAddress + 0x16000;
        VirtualProtect((void*)PatchOnTimerCode, 0x00178000, PAGE_EXECUTE_READWRITE, &PatchOnTimerStart);

        WriteData<7>((void*)(baseAddress + 0x01603F), 0x90);
        WriteJump((void*)(baseAddress + 0x01603F), HookTimer);
    }

    #pragma endregion

    #pragma region Load Sounds Patches

    bool SoundsLoaded = false;

    void LoadSounds()
    {
        if (!SoundsLoaded)
        {
            // Load Sounds on First Run. 
            // Global Scope fine for most things
            SonicMania::LoadSoundFX(CompPlus_Common::SFX_MenuBleepClassic, SonicMania::Scope_Global);
            SonicMania::LoadSoundFX(CompPlus_Common::SFX_MenuAcceptClassic, SonicMania::Scope_Global);
            SonicMania::LoadSoundFX(CompPlus_Common::SFX_GPZButton, SonicMania::Scope_Global);
            SonicMania::LoadSoundFX(CompPlus_Common::SFX_LHPZSecret, SonicMania::Scope_Global);
            LoadSoundFX(CompPlus_Common::SFX_EXE_KYS, Scope_Global);
            LoadSoundFX(CompPlus_Common::SFX_EXE_Laugh, Scope_Global);
            SonicMania::LoadSoundFX(CompPlus_Common::SFX_FBZ_Rain, SonicMania::Scope_Global);
            SonicMania::LoadSoundFX(CompPlus_Common::SFX_FBZ_Thunder, SonicMania::Scope_Global);
            CompPlus_Announcers::LoadAnnouncerFX();
            SoundsLoaded = true;
        }
    }

    #pragma endregion

    #pragma region Disable Player Swap Item Box Patch

    static __declspec(naked) void DisableSwapBoxFunction()
    {
        SonicMania::PlaySoundFXS("Global/SwapFail.wav");
        __asm
        {
            ret
        }
    }

    void DisableSwapBox()
    {
        WriteData<5>((void*)(baseAddress + 0xA8A0C), 0x90);
        WriteData<5>((void*)(baseAddress + 0xA8A1D), 0x90);
        WriteData<5>((void*)(baseAddress + 0xA8A2E), 0x90);
        WriteData<5>((void*)(baseAddress + 0xA8A3F), 0x90);
        WriteData<5>((void*)(baseAddress + 0xA8A50), 0x90);

        WriteCall((void*)(baseAddress + 0xA8A0C), DisableSwapBoxFunction);
        WriteCall((void*)(baseAddress + 0xA8A1D), DisableSwapBoxFunction);
        WriteCall((void*)(baseAddress + 0xA8A2E), DisableSwapBoxFunction);
        WriteCall((void*)(baseAddress + 0xA8A3F), DisableSwapBoxFunction);
        WriteCall((void*)(baseAddress + 0xA8A50), DisableSwapBoxFunction);
    }

    #pragma endregion

    #pragma region TMZ2 Competition Specific Patches

    void PatchCompetitionPlusTMZ()
    {
        //TMZ2: CrashTest
        WriteData<2>((void*)(baseAddress + 0x100E0A), 0x90); //Instant Respawn
        //WriteData((void*)(baseAddress + 0x100A00), { (byte)0x7E, (byte)0x09 }); //Instant Launch
        WriteData((void*)(baseAddress + 0x1009AE), { (byte)0xF6, (byte)0x46, (byte)0x64, (byte)0x0F }); //Remove Player 1 Requirement

        //TMZ2: MetalArm
        WriteData((void*)(baseAddress + 0x159C47), { (byte)0xF6, (byte)0x80, (byte)0x80, (byte)0x00, (byte)0x00, (byte)0x00, (byte)0x0F }); //Remove Player 1 Requirement 
        WriteData((void*)(baseAddress + 0x159CB7), { (byte)0xF6, (byte)0x81, (byte)0x80, (byte)0x00, (byte)0x00, (byte)0x00, (byte)0x0F }); //Remove Player 1 Requirement (Return Trip)
    }

    #pragma endregion

    #pragma region SetSpriteAnimation Patch

    static int SetSpriteAnimationJMPBACK = baseAddress + 0x1B35E7;
    int SetSpriteAnimation(int spriteIndex)
    {
        spriteIndex = CompPlus_PlayerSkins::OnSetSpriteAnimation(spriteIndex);
        return spriteIndex;
    }
    static __declspec(naked) void OverrideSetSpriteAnimation()
    {
        static int  spriteIndex = 0;
        static int  animationID = 0;
        static int animationData = 0;
        static int forceApply = 0;
        static int  frameID = 0;

        __asm
        {
            mov spriteIndex, EAX;
            mov animationID, EBX;
            mov animationData, ECX;
            mov forceApply, EDX;
            mov frameID, ESI;
            pushad;
        }

        spriteIndex = SetSpriteAnimation(spriteIndex);
        __asm
        {
            popad;
            mov EAX, spriteIndex;
            mov EBX, animationID;
            mov ECX, animationData;
            mov EDX, forceApply;
            mov ESI, frameID;
            push ebp;
            mov ebp, esp;
            mov ax, [ebp + 0x08];
            jmp SetSpriteAnimationJMPBACK;
        }
    }

    void PatchSetSpriteAnimation()
    {
        WriteData<7>((void*)(baseAddress + 0x001B35E0), 0x90);
        WriteJump((void*)(baseAddress + 0x001B35E0), OverrideSetSpriteAnimation);
    }

    #pragma endregion

    #pragma region Unlimited Time Patch (VS)

    bool HasCopiedOriginalTimeCode = false;
    bool IsLimitedWriten = false;
    bool IsUnlimitedWriten = false;

    char ExtendedTime_Code[0x02];
    char TimeLimit_Kill_Code[0x06];
    char TimeLimit_VS_Kill_Code[0x07];
    char TimeLimit_VS_TimeLock1_Code[0x04];
    char TimeLimit_VS_TimeLock2_Code[0x06];
    char TimeLimit_VS_TimeLock3_Code[0x07];
    char TimeLimit_VS_MaxTime1_Code[0x0A];
    char TimeLimit_VS_MaxTime2_Code[0x0B];
    char TimeLimit_VS_MaxTime3_Code[0x0A];

    void WriteVSUnlimitedTimeMovs(void* Min_Addr, void* Sec_Addr, void* Centi_Addr, int Mins, int Secs, int Centis)
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

    void UpdateExtendedTimerVSPatch()
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
                WriteVSUnlimitedTimeMovs(TimeLimit_VS_MaxTime1_Adrr, TimeLimit_VS_MaxTime2_Adrr, TimeLimit_VS_MaxTime3_Adrr, 99, 99, 99);
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

    #pragma endregion

    #pragma region World Position Patch (World Player)

    bool IsWorldPositionWriteDisableWritten = false;
    bool HasCopiedWorldPositionWriteCode = false;

    char worldX_write1_Code[0x07];
    char worldX_write2_Code[0x07];
    char worldX_write3_Code[0x07];
    char worldY_write1_Code[0x07];
    char worldY_write2_Code[0x07];
    char worldY_write3_Code[0x07];

    void UpdateWorldPositionPatch()
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

    #pragma endregion

    #pragma region Special Ring Warp Patch

    bool HasCopiedSpecialRingWarpCode = false;
    bool IsDisableSpecialRingWarpWritten = false;

    char SpecialRingWarp_Code[0x02];
    char SpecialRingWarp2_Code[0x06];

    void UpdateSpecialRingWarpPatch()
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

    #pragma endregion

    #pragma region Hurry Up Timer Patch (VS)

    bool HasCopiedOriginalHurryTimerCode = false;
    bool IsHurryTimerOffWriten = false;
    bool IsHurryTimerOnWriten = false;

    char HurryUpTimer_Code[0x03];

    void UpdateVSHurryUpTimerPatch()
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

    #pragma endregion

    #pragma region Player Killable Patch

    bool HasCopiedOriginalPlayerKillCode = false;
    bool PlayerKillCodeWriten = false;
    char PlayerKill_OriginalCode[0x02];

    void UpdatePlayerKillablePatch()
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

    #pragma endregion

    #pragma region VS Timer Lock Patch

    bool InitalInputCollected = false;
    bool HasCopiedOriginalControlUnlockCode = false;
    bool isUnlockWriten = false;
    bool isLockWriten = false;
    char ControlLock_OriginalCode[0x06];
    char ControlLock_OriginalSoundCode3[0x06];
    char ControlLock_OriginalSoundCode2[0x06];
    char ControlLock_OriginalSoundCode1[0x06];
    char ControlLock_OriginalSoundCodeGO[0x06];

    void UpdateVSTimerLockPatch()
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

    #pragma endregion

    #pragma region Misc. Patches

    void PatchDisableVSPointIncrement()
    {
        void* vs_incrementing_address = (void*)(baseAddress + 0xE35C);
        char nops[2];
        memset(nops, 0x90, sizeof nops);
        WriteData(vs_incrementing_address, nops, 0x02);
    }

    void PatchRayAndMightyVSFix()
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

    void PatchSummaryFix()
    {
        //Remove A/Start from the Game Summary
        WriteData((BYTE*)(baseAddress + 0x00190618), (BYTE)0xEB);
    }

    #pragma endregion

    void DynamicPatchesOnFrame()
    {
        UpdateSpecialRingWarpPatch();
        UpdateVSHurryUpTimerPatch();
        UpdateExtendedTimerVSPatch();
        UpdateVSTimerLockPatch();
        UpdatePlayerKillablePatch();
        UpdateWorldPositionPatch();
    }

    void InitPatches() 
    {
        SonicMania::BindLBAndRB();
        PatchOnTitlePlusLogoDrawHook();
        PatchOnHUBDecorationScreenDrawHook();
        PatchWaterDrawHook();
        PatchCompetitionPlusTMZ();
        PatchPlaySongBass();
        PatchHookOnStartTimer();
        PatchOnRoundClearHook();
        PatchDisableVSPointIncrement();
    }
}