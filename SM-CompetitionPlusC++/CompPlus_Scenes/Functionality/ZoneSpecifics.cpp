#include "ZoneSpecifics.h"
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

namespace CompPlus_ZoneSpecifics
{
    int CurrentSpecific = 0;
    int LastSpecific = 0;

    char* SceneDirectory = (char*)(baseAddress + 0xA5359C);

    char* CurrentScene_IZ;
    int CurrentScene_SM;

    #pragma region DynCam Validation

    bool IsValidDynCamScene()
    {
        if (strcmp(SceneDirectory, "Pinball") == 0) return false;
        if (strcmp(SceneDirectory, "SpecialBS") == 0) return false;
        if (strcmp(SceneDirectory, "UFO1") == 0) return false;
        if (strcmp(SceneDirectory, "UFO2") == 0) return false;
        if (strcmp(SceneDirectory, "UFO3") == 0) return false;
        if (strcmp(SceneDirectory, "UFO4") == 0) return false;
        if (strcmp(SceneDirectory, "UFO5") == 0) return false;
        if (strcmp(SceneDirectory, "UFO6") == 0) return false;
        if (strcmp(SceneDirectory, "UFO7") == 0) return false;
        return true;
    }

    void SetDynamicCameraDisabledState(bool State)
    {
        if (!IsValidDynCamScene())
        {
            if (CompPlus_Status::DisableDynCam == false) CompPlus_Status::DisableDynCam = true;
            return;
        }
        else
        {
            CompPlus_Status::DisableDynCam = State;
        }
    }

    #pragma endregion

    #pragma region Presets

    void HubLikePreset()
    {
        CompPlus_Status::isVSControllerInputUnlocked = true;
        CompPlus_Status::EnableHUBSpecialRingFunctionality = true;
        CompPlus_Status::DisablePlayerDying = true;

        CompPlus_Status::ReplaceSpecialRings = false;
    }

    #pragma endregion

    #pragma region Specifics

    void ResetSpecifics()
    {
        if (LastSpecific != CurrentSpecific)
        {
            CompPlus_Status::EnableHUBSpecialRingFunctionality = false;
            CompPlus_Status::isVSControllerInputUnlocked = false;
            SetDynamicCameraDisabledState(false);
            CompPlus_Status::DisablePlayerDying = false;
            CompPlus_Status::InHolloweenHUB = false;
            CompPlus_Status::UseEXETitleCard = false;

            CompPlus_Status::ReplaceSpecialRings = true;

            LastSpecific = CurrentSpecific;
        }
    }

    void SetDefaultSpecifics()
    {
        ResetSpecifics();
        CompPlus_Status::EnableHUBSpecialRingFunctionality = false;
        CompPlus_Status::isVSControllerInputUnlocked = false;
        SetDynamicCameraDisabledState(false);
        CompPlus_Status::DisablePlayerDying = false;
        CompPlus_Status::InHolloweenHUB = false;
        CompPlus_Status::UseEXETitleCard = false;

        CompPlus_Status::ReplaceSpecialRings = true;

        CurrentSpecific = 0;
    }

    void SetCreditsSpecifics()
    {
        ResetSpecifics();
        HubLikePreset();
        SetDynamicCameraDisabledState(true);
        CurrentSpecific = 1;
    }

    void SetHUBSpecifics()
    {
        ResetSpecifics();
        HubLikePreset();
        CurrentSpecific = 2;
    }

    void SetHauntedHUBSpecifics()
    {
        ResetSpecifics();
        HubLikePreset();
        CompPlus_Status::InHolloweenHUB = true;
        CompPlus_Status::UseEXETitleCard = true;
        CurrentSpecific = 3;
    }

    void UpdateSpecifics(const char* CurrentScene, int LevelID)
    {
        CurrentScene_IZ = (char*)CurrentScene;
        CurrentScene_SM = LevelID;

        if (!strcmp(CurrentScene, "SMCP_HUB1")) SetHUBSpecifics();
        else if (!strcmp(CurrentScene, "SMCP_HUB1HWN")) SetHauntedHUBSpecifics();
        else if (!strcmp(CurrentScene, "SMCP_HUB2")) SetHUBSpecifics();
        else if (!strcmp(CurrentScene, "SMCP_HUB3")) SetHUBSpecifics();
        else if (!strcmp(CurrentScene, "CPCREDITS")) SetCreditsSpecifics();
        else SetDefaultSpecifics();
    }

    #pragma endregion







}