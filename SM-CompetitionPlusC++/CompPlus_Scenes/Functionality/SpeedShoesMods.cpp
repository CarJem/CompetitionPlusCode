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
            IZAPI::SetGlobalAsset("Data/Objects/Static/36D61A3DE508B500AE0ECF8D33F32943.bin", nullptr);
            IZAPI::SetGlobalAsset("Data/Sprites/Global/ItemBox.bin", "Data/Sprites/SMCP_ItemMods/ItemBox_Normal.bin");
           
        }
        else if (CurrentModification == CompPlus_Settings::SpeedShoesModification_HighJump)
        {
            IZAPI::SetGlobalAsset("Data/Objects/Static/36D61A3DE508B500AE0ECF8D33F32943.bin", "Data/Objects/CompPlus_SpeedShoesAbility/JumpBoost.bin");
            IZAPI::SetGlobalAsset("Data/Sprites/Global/ItemBox.bin", "Data/Sprites/SMCP_ItemMods/ItemBox_JumpBoost.bin");
        }
        else if (CurrentModification == CompPlus_Settings::SpeedShoesModification_Freeze)
        {
            IZAPI::SetGlobalAsset("Data/Objects/Static/36D61A3DE508B500AE0ECF8D33F32943.bin", "Data/Objects/CompPlus_SpeedShoesAbility/Freeze.bin");
            IZAPI::SetGlobalAsset("Data/Sprites/Global/ItemBox.bin", "Data/Sprites/SMCP_ItemMods/ItemBox_Freeze.bin");
        }
        else if (CurrentModification == CompPlus_Settings::SpeedShoesModification_SpeedDown)
        {
            IZAPI::SetGlobalAsset("Data/Objects/Static/36D61A3DE508B500AE0ECF8D33F32943.bin", "Data/Objects/CompPlus_SpeedShoesAbility/SpeedDown.bin");
            IZAPI::SetGlobalAsset("Data/Sprites/Global/ItemBox.bin", "Data/Sprites/SMCP_ItemMods/ItemBox_SpeedDown.bin");
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