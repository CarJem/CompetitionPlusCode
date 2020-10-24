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

    char* CurrentScene_IZ;
    int CurrentScene_SM;


    #pragma region Presets

    void DefaultPreset() 
    {
        CompPlus_Status::EnableHUBSpecialRingFunctionality = false;
        CompPlus_Status::isVSControllerInputUnlocked = false;
        CompPlus_Status::DisableDynCam = false;
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
        CompPlus_Status::DisableDynCam = true;
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
        CompPlus_Status::DisableDynCam = true;
        CurrentSpecific = 4;
    }

    void SetEXELevelSpecifics()
    {
        ResetSpecifics();
        CompPlus_Status::IsExecutorStage = true;
        CompPlus_Status::UseEXETitleCard = true;
        CurrentSpecific = 5;
    }

    void SetChaotixLevelSpecifics()
    {
        ResetSpecifics();
        CompPlus_Status::IsChaotixStage = true;
        CurrentSpecific = 6;
    }

    void SetChaotixEncoreLevelSpecifics()
    {
        ResetSpecifics();
        CompPlus_Status::IsChaotixStageEncore = true;
        CurrentSpecific = 7;
    }

    bool IsInternalStage(const char* CurrentScene)
    {
        if (!strcmp(CurrentScene, CompPlus_Common::HUBWorld)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::HUBRanking)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::HUBSettings)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::HUBWorld_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_Credits)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::LSelect_Mania)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::LSelect_Encore)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::LSelect_Custom)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::LSelect_Chaotix)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::LSelect_Exe)) return true;
        else return false;
    }

    bool IsManiaStage(const char* CurrentScene)
    {
        if (!strcmp(CurrentScene, CompPlus_Common::SMCP_GHZ1)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_GHZ2)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CPZ1)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CPZ2)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SPZ1)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SPZ2)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_FBZ1)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_FBZ2)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_PGZ1)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_PGZ2)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SSZ1)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SSZ2)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_HCZ1)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_HCZ2)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MSZ1K)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MSZ2)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_OOZ1)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_OOZ2)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_LRZ1)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_LRZ2)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MMZ1)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MMZ2)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_TMZ1)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_TMZ2)) return true;
        else return false;
    }

    bool IsEncoreStage(const char* CurrentScene)
    {
        if (!strcmp(CurrentScene, CompPlus_Common::SMCP_GHZ1E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_GHZ2E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CPZ1E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CPZ2E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SPZ1E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SPZ2E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_FBZ1E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_FBZ2E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_PGZ1E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_PGZ2E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SSZ1E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SSZ2E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_HCZ1E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_HCZ2E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MSZ1E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MSZ2E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_OOZ1E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_OOZ2E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_LRZ1E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_LRZ2E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MMZ1E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MMZ2E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_TMZ1E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_TMZ2E)) return true;
        else return false;
    }

    bool IsCustomStage(const char* CurrentScene)
    {
        if (!strcmp(CurrentScene, CompPlus_Common::SMCP_AIZ_EXT)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_DHZ)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_DHZE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SZ)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SZE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_GPZ1)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_GPZ1E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_TSZ)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_LHPZ1)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_LHPZ1E)) return true;
        else return false;
    }
    
    bool IsExecutorStage(const char* CurrentScene)
    {
        if (!strcmp(CurrentScene, CompPlus_Common::SMCP_GHZ1_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_GHZ2_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CPZ1_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CPZ2_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SPZ1_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SPZ2_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_FBZ1_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_FBZ2_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_PGZ1_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_PGZ2_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SSZ1_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SSZ2_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_HCZ1_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_HCZ2_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MSZ1_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MSZ2_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_OOZ1_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_OOZ2_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_LRZ1_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_LRZ2_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MMZ1_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MMZ2_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_TMZ1_EXE)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_TMZ2_EXE)) return true;
        else return false;
    }

    bool IsChaotixStage(const char* CurrentScene)
    {
        if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_AAZ1)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_BBZ1)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_IIZ1)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_MMZ1)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_SSZ1)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_TTZ1)) return true;
        else return false;
    }

    bool IsChaotixEncoreStage(const char* CurrentScene)
    {
        if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_AAZ1E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_BBZ1E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_IIZ1E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_MMZ1E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_SSZ1E)) return true;
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CXM_TTZ1E)) return true;
        else return false;
    }

    void UpdateSpecifics(const char* CurrentSceneIZ, int LevelID)
    {
        CurrentScene_IZ = (char*)CurrentSceneIZ;
        CurrentScene_SM = LevelID;

        if (!strcmp(CurrentScene_IZ, CompPlus_Common::HUBWorld)) SetHUBSpecifics();
        else if (!strcmp(CurrentScene_IZ, CompPlus_Common::HUBWorld_EXE)) SetHauntedHUBSpecifics();
        else if (!strcmp(CurrentScene_IZ, CompPlus_Common::HUBRanking)) SetHUBSpecifics();
        else if (!strcmp(CurrentScene_IZ, CompPlus_Common::HUBSettings)) SetHUBSpecifics();
        else if (!strcmp(CurrentScene_IZ, CompPlus_Common::SMCP_Credits)) SetCreditsSpecifics();
        else if (!strcmp(CurrentScene_IZ, CompPlus_Common::LSelect_Mania)) SetLevelSelectSpecifics();
        else if (!strcmp(CurrentScene_IZ, CompPlus_Common::LSelect_Encore)) SetLevelSelectSpecifics();
        else if (!strcmp(CurrentScene_IZ, CompPlus_Common::LSelect_Custom)) SetLevelSelectSpecifics();
        else if (!strcmp(CurrentScene_IZ, CompPlus_Common::LSelect_Chaotix)) SetLevelSelectSpecifics();
        else if (!strcmp(CurrentScene_IZ, CompPlus_Common::LSelect_Exe)) SetLevelSelectSpecifics();
        else if (IsExecutorStage(CurrentScene_IZ)) SetEXELevelSpecifics();
        else if (IsChaotixStage(CurrentScene_IZ)) SetChaotixLevelSpecifics();
        else if (IsChaotixEncoreStage(CurrentScene_IZ)) SetChaotixEncoreLevelSpecifics();
        else SetDefaultSpecifics();
    }

    #pragma endregion

}