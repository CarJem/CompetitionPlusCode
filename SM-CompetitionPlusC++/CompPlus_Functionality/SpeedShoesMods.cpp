#include "SpeedShoesMods.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/ManiaExt.h"

#include "include/ManiaAPI/SonicMania.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "CompPlus_Extensions/Helpers.h"

#include "CompPlus_Core/CompPlus_Scoring.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Status.h"

namespace CompPlus_SpeedShoesMods
{
    int RandomNumber(int min, int max)
    {
        return rand() % (max - min) + min;
    }

    CompPlus_Settings::SpeedShoesModification CurrentModification;

    const char* Music_SpeedShoes_Stock = "Sneakers.ogg";
    const char* Music_SpeedShoes_Default = "SMCP_Shoes/SpeedSneakers.ogg";
    const char* Music_SpeedShoes_Freeze = "SMCP_Shoes/FreezeSneakers.ogg";
    const char* Music_SpeedShoes_HighJump = "SMCP_Shoes/JumpSneakers.ogg";
    const char* Music_SpeedShoes_SpeedDown = "SMCP_Shoes/SlowSneakers.ogg";

    int Music_SpeedShoes_Default_LoopPoint = 120960;
    int Music_SpeedShoes_Freeze_LoopPoint = 120960;
    int Music_SpeedShoes_HighJump_LoopPoint = 120960;
    int Music_SpeedShoes_SpeedDown_LoopPoint = 120960;

    void SetSpeedShoes() 
    {
        if (CurrentModification == CompPlus_Settings::SpeedShoesModification_Default)
        {
            IZAPI::SetGlobalAsset(CompPlus_Common::Obj_SpeedShoes_Original, nullptr);
            IZAPI::SetGlobalAsset(CompPlus_Common::Anim_ItemBox_Original, CompPlus_Common::Anim_ItemBox_Stock);        
        }
        else if (CurrentModification == CompPlus_Settings::SpeedShoesModification_HighJump)
        {
            IZAPI::SetGlobalAsset(CompPlus_Common::Obj_SpeedShoes_Original, CompPlus_Common::Obj_SpeedShoes_JumpUp);
            IZAPI::SetGlobalAsset(CompPlus_Common::Anim_ItemBox_Original, CompPlus_Common::Anim_ItemBox_JumpUp);
        }
        else if (CurrentModification == CompPlus_Settings::SpeedShoesModification_Freeze)
        {
            IZAPI::SetGlobalAsset(CompPlus_Common::Obj_SpeedShoes_Original, CompPlus_Common::Obj_SpeedShoes_Freeze);
            IZAPI::SetGlobalAsset(CompPlus_Common::Anim_ItemBox_Original, CompPlus_Common::Anim_ItemBox_Freeze);
        }
        else if (CurrentModification == CompPlus_Settings::SpeedShoesModification_SpeedDown)
        {
            IZAPI::SetGlobalAsset(CompPlus_Common::Obj_SpeedShoes_Original, CompPlus_Common::Obj_SpeedShoes_Slowdown);
            IZAPI::SetGlobalAsset(CompPlus_Common::Anim_ItemBox_Original, CompPlus_Common::Anim_ItemBox_Slowdown);
        }
    }
    

    void OnSceneReset() 
    {
        if (CompPlus_Settings::SpeedShoesMode == CompPlus_Settings::SpeedShoesModification_Random)
        {
            int outcome = RandomNumber(0, 3);

            if (outcome == 0) CurrentModification = CompPlus_Settings::SpeedShoesModification_Default;
            else if (outcome == 1) CurrentModification = CompPlus_Settings::SpeedShoesModification_HighJump;
            else if (outcome == 2) CurrentModification = CompPlus_Settings::SpeedShoesModification_Freeze;
            else if (outcome == 3) CurrentModification = CompPlus_Settings::SpeedShoesModification_SpeedDown;
            else CurrentModification = CompPlus_Settings::SpeedShoesModification_Default;
        }
        else 
        {
            CurrentModification = CompPlus_Settings::SpeedShoesMode;
        }
        SetSpeedShoes();
    }

    void SetMusic(const char* NormalPath, int NormalLoop, const char*& name, unsigned int& a2, int& a3, unsigned int& loopstart, int& a5)
    {
        if (a2 == 0)
        {
            name = NormalPath;
            loopstart = NormalLoop;
        }
    }

    void OnMusicLoad(char* CurrentScene, const char*& name, unsigned int& a2, int& a3, unsigned int& loopstart, int& a5)
    {
        if (name == Music_SpeedShoes_Stock)
        {
            if (CurrentModification == CompPlus_Settings::SpeedShoesModification_Default)
            {
                SetMusic(Music_SpeedShoes_Default, Music_SpeedShoes_Default_LoopPoint, name, a2, a3, loopstart, a5);
            }
            else if (CurrentModification == CompPlus_Settings::SpeedShoesModification_HighJump)
            {
                SetMusic(Music_SpeedShoes_HighJump, Music_SpeedShoes_HighJump_LoopPoint, name, a2, a3, loopstart, a5);
            }
            else if (CurrentModification == CompPlus_Settings::SpeedShoesModification_Freeze)
            {
                SetMusic(Music_SpeedShoes_Freeze, Music_SpeedShoes_Freeze_LoopPoint, name, a2, a3, loopstart, a5);
            }
            else if (CurrentModification == CompPlus_Settings::SpeedShoesModification_SpeedDown)
            {
                SetMusic(Music_SpeedShoes_SpeedDown, Music_SpeedShoes_SpeedDown_LoopPoint, name, a2, a3, loopstart, a5);
            }
        }
    }

    void OnFrame() 
    {
        if (CompPlus_Settings::SpeedShoesMode != CompPlus_Settings::SpeedShoesModification_Random) SetSpeedShoes();
    }
}