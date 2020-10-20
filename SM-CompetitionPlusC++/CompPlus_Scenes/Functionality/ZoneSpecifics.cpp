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

    void DefaultPreset() 
    {
        CompPlus_Status::EnableHUBSpecialRingFunctionality = false;
        CompPlus_Status::isVSControllerInputUnlocked = false;
        SetDynamicCameraDisabledState(false);
        CompPlus_Status::DisablePlayerDying = false;
        CompPlus_Status::InHolloweenHUB = false;
        CompPlus_Status::UseEXETitleCard = false;
        CompPlus_Status::DisableWorldPositionWrite = false;
        CompPlus_Status::ForceLoadChibiSprites = false;
        CompPlus_Status::IsExecutorStage = false;
        CompPlus_Status::IsChaotixStage = false;
        CompPlus_Status::IsChaotixStageEncore = false;

        CompPlus_Status::ReplaceSpecialRings = true;
    }

    void HubLikePreset()
    {
        CompPlus_Status::isVSControllerInputUnlocked = true;
        CompPlus_Status::EnableHUBSpecialRingFunctionality = true;
        CompPlus_Status::DisablePlayerDying = true;

        CompPlus_Status::ReplaceSpecialRings = false;
    }

    void LevelSelectLikePreset() 
    {
        CompPlus_Status::DisableWorldPositionWrite = true;
    }

    #pragma endregion

    #pragma region Specifics

    void ResetSpecifics()
    {
        if (LastSpecific != CurrentSpecific)
        {
            DefaultPreset();
            LastSpecific = CurrentSpecific;
        }
    }

    void SetDefaultSpecifics()
    {
        ResetSpecifics();
        DefaultPreset();
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

    void SetLevelSelectSpecifics()
    {
        ResetSpecifics();

        LevelSelectLikePreset();
        SetDynamicCameraDisabledState(true);
        CurrentSpecific = 4;
    }

    void SetMMZ2LevelSpecifics() 
    {
        ResetSpecifics();

        CompPlus_Status::ForceLoadChibiSprites = true;
        CurrentSpecific = 5;
    }

    void SetEXELevelSpecifics()
    {
        ResetSpecifics();
        CompPlus_Status::IsExecutorStage = true;
        CompPlus_Status::UseEXETitleCard = true;
        CurrentSpecific = 6;
    }

    void SetMMZ2EXELevelSpecifics()
    {
        ResetSpecifics();
        CompPlus_Status::IsExecutorStage = true;
        CompPlus_Status::UseEXETitleCard = true;
        CompPlus_Status::ForceLoadChibiSprites = true;
        CurrentSpecific = 7;
    }

    void SetChaotixLevelSpecifics()
    {
        ResetSpecifics();
        CompPlus_Status::IsChaotixStage = true;
        CurrentSpecific = 8;
    }

    void SetChaotixEncoreLevelSpecifics()
    {
        ResetSpecifics();
        CompPlus_Status::IsChaotixStageEncore = true;
        CurrentSpecific = 9;
    }
    
    bool IsExecutorStage(const char* CurrentScene)
    {
        if (!strcmp(CurrentScene, CompPlus_Common::SMCP_GHZ1_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_GHZ2_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CPZ1_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CPZ2_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SPZ1_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SPZ2_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_FBZ1_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_FBZ2_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_PGZ1_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_PGZ2_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SSZ1_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SSZ2_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_HCZ1_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_HCZ2_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MSZ1_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MSZ2_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_OOZ1_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_OOZ2_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_LRZ1_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_LRZ2_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MMZ1_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MMZ2_EXE)) SetMMZ2EXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_TMZ1_EXE)) SetEXELevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_TMZ2_EXE)) SetEXELevelSpecifics();
        else return false;

        return true;
    }

    bool IsChaotixStage(const char* CurrentScene)
    {
        if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_AAZ1)) SetChaotixLevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_AAZ1E)) SetChaotixEncoreLevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_BBZ1)) SetChaotixLevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_BBZ1E)) SetChaotixEncoreLevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_IIZ1)) SetChaotixLevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_IIZ1E)) SetChaotixEncoreLevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_MMZ1)) SetChaotixLevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_MMZ1E)) SetChaotixEncoreLevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_SSZ1)) SetChaotixLevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_SSZ1E)) SetChaotixEncoreLevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_TTZ1)) SetChaotixLevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_TTZ1E)) SetChaotixEncoreLevelSpecifics();
        else return false;
        
        return true;
    }


    void UpdateSpecifics(const char* CurrentScene, int LevelID)
    {
        CurrentScene_IZ = (char*)CurrentScene;
        CurrentScene_SM = LevelID;

        if (!strcmp(CurrentScene, CompPlus_Common::HUBWorld)) SetHUBSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::HUBWorld_EXE)) SetHauntedHUBSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::HUBRanking)) SetHUBSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::HUBSettings)) SetHUBSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_Credits)) SetCreditsSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::LSelect_Mania)) SetLevelSelectSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::LSelect_Encore)) SetLevelSelectSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::LSelect_Custom)) SetLevelSelectSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::LSelect_Chaotix)) SetLevelSelectSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::LSelect_Exe)) SetLevelSelectSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MMZ2)) SetMMZ2LevelSpecifics();
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MMZ2E)) SetMMZ2LevelSpecifics();
        else if (IsExecutorStage(CurrentScene)) return;
        else if (IsChaotixStage(CurrentScene)) return;
        else SetDefaultSpecifics();
    }

    #pragma endregion







}