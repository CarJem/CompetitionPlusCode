#include "SpeedShoesMods.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/ManiaExt.h"

#include "SonicMania.h"
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

    void OnFrame() 
    {
        if (CompPlus_Settings::SpeedShoesMode != CompPlus_Settings::SpeedShoesModification_Random) SetSpeedShoes();
    }
}