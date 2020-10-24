#include "stdafx.h"
#include "CompPlus_Common.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/PointScrolling.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "SonicMania.h"
#include "Base.h"
#include "CompPlus_Settings.h"
#include "CompPlus_Status.h"
#include "CompPlus_Scoring.h"
#include "CompPlus_Scenes/HUB World/HubCore.h"

namespace CompPlus_Common
{
    const char* Internal_VersionNumber = "5.0";
    const char* Internal_VersionNumberAlt = "5.0.EXE";
    const char* Internal_VersionName = "HALLOWEEN DEMO";
    const char* Internal_VersionNameShort = "DEMO";


    const char* SFX_MenuBleep = "Global/MenuBleep.wav";
    const char* SFX_MenuAccept = "Global/MenuAccept.wav";
    const char* SFX_SpecialWarp = "Global/SpecialWarp.wav";

    const char* SFX_MenuBleepClassic = "CompPlus/MenuBleepClassic.wav";
    const char* SFX_MenuAcceptClassic = "CompPlus/MenuAcceptClassic.wav";
    const char* SFX_LHPZSecret = "CompPlus/LHPZSecret.wav";
    const char* SFX_GPZButton = "CompPlus/GPZ_Button.wav";

    const char* SFX_EXE_KYS = "SMCP_Executor/KYS.wav";
    const char* SFX_EXE_Laugh = "SMCP_Executor/Laugh.wav";

    const char* Act_LSelect = "/Data/Palettes/SMCP_LSelect/LSelect.act";

    const char* Anim_LSelectIcons_Mania = "SMCP_LSelect/Icons.bin";
    const char* Anim_LSelectIcons_Encore = "SMCP_LSelect/Icons_Encore.bin";
    const char* Anim_LSelectIcons_Custom = "SMCP_LSelect/Icons_Custom.bin";
    const char* Anim_LSelectIcons_Chaotix = "SMCP_LSelect/Icons_Chaotix.bin";
    const char* Anim_LSelectIcons_Exe = "SMCP_LSelect/Icons_Exe.bin";

    const char* Anim_HubCrown = "HUB/Crown.bin";

    const char* Anim_EXE_Sprites = "SMCP_Executor/Explosions.bin";

    const char* Anim_UISmallFont = "UI/SmallFont.bin";
    const char* Anim_LSelectText = "LSelect/Text.bin";
    const char* Anim_LSelectText_Exe = "SMCP_LSelect/Text_EXE.bin";
    const char* Anim_Cred_UISmallFont = "SMCP_Cred/SmallFont.bin";

    const char* SMCP_Unused_SettingsWorld = "SMCP_SW";
    const char* SMCP_Credits = "SMCP_CREDITS";

    const char* SMCP_DAGarden = "SMCP_DAGARDEN_1";
    const char* SMCP_DAGarden_Mania = "SMCP_DAGARDEN_2";
    const char* SMCP_DAGarden_Encore = "SMCP_DAGARDEN_3";
    const char* SMCP_DAGarden_Custom = "SMCP_DAGARDEN_4";
    const char* SMCP_DAGarden_Chaotix = "SMCP_DAGARDEN_5";


    const char* SceneID_MMZ = "MMZ";

    const char* SMCP_GHZ1 = "SMCP_GHZ1";
    const char* SMCP_GHZ2 = "SMCP_GHZ2";
    const char* SMCP_CPZ1 = "SMCP_CPZ1";
    const char* SMCP_CPZ2 = "SMCP_CPZ2";
    const char* SMCP_SPZ1 = "SMCP_SPZ1";
    const char* SMCP_SPZ2 = "SMCP_SPZ2";
    const char* SMCP_FBZ1 = "SMCP_FBZ1";
    const char* SMCP_FBZ2 = "SMCP_FBZ2";
    const char* SMCP_PGZ1 = "SMCP_PGZ1";
    const char* SMCP_PGZ2 = "SMCP_PGZ2";
    const char* SMCP_SSZ1 = "SMCP_SSZ1";
    const char* SMCP_SSZ2 = "SMCP_SSZ2";
    const char* SMCP_HCZ1 = "SMCP_HCZ1";
    const char* SMCP_HCZ2 = "SMCP_HCZ2";
    const char* SMCP_MSZ1K = "SMCP_MSZ1K";
    const char* SMCP_MSZ2 = "SMCP_MSZ2";
    const char* SMCP_OOZ1 = "SMCP_OOZ1";
    const char* SMCP_OOZ2 = "SMCP_OOZ2";
    const char* SMCP_LRZ1 = "SMCP_LRZ1";
    const char* SMCP_LRZ2 = "SMCP_LRZ2";
    const char* SMCP_MMZ1 = "SMCP_MMZ1";
    const char* SMCP_MMZ2 = "SMCP_MMZ2";
    const char* SMCP_TMZ1 = "SMCP_TMZ1";
    const char* SMCP_TMZ2 = "SMCP_TMZ2";

    const char* SMCP_GHZ1E = "SMCP_GHZ1E";
    const char* SMCP_GHZ2E = "SMCP_GHZ2E";
    const char* SMCP_CPZ1E = "SMCP_CPZ1E";
    const char* SMCP_CPZ2E = "SMCP_CPZ2E";
    const char* SMCP_SPZ1E = "SMCP_SPZ1E";
    const char* SMCP_SPZ2E = "SMCP_SPZ2E";
    const char* SMCP_FBZ1E = "SMCP_FBZ1E";
    const char* SMCP_FBZ2E = "SMCP_FBZ2E";
    const char* SMCP_PGZ1E = "SMCP_PGZ1E";
    const char* SMCP_PGZ2E = "SMCP_PGZ2E";
    const char* SMCP_SSZ1E = "SMCP_SSZ1E";
    const char* SMCP_SSZ2E = "SMCP_SSZ2E";
    const char* SMCP_HCZ1E = "SMCP_HCZ1E";
    const char* SMCP_HCZ2E = "SMCP_HCZ2E";
    const char* SMCP_MSZ1E = "SMCP_MSZ1E";
    const char* SMCP_MSZ2E = "SMCP_MSZ2E";
    const char* SMCP_OOZ1E = "SMCP_OOZ1E";
    const char* SMCP_OOZ2E = "SMCP_OOZ2E";
    const char* SMCP_LRZ1E = "SMCP_LRZ1E";
    const char* SMCP_LRZ2E = "SMCP_LRZ2E";
    const char* SMCP_MMZ1E = "SMCP_MMZ1E";
    const char* SMCP_MMZ2E = "SMCP_MMZ2E";
    const char* SMCP_TMZ1E = "SMCP_TMZ1E";
    const char* SMCP_TMZ2E = "SMCP_TMZ2E";

    const char* SMCP_GHZ1_EXE = "SMCP_GHZ1_EXE";
    const char* SMCP_GHZ2_EXE = "SMCP_GHZ2_EXE";
    const char* SMCP_CPZ1_EXE = "SMCP_CPZ1_EXE";
    const char* SMCP_CPZ2_EXE = "SMCP_CPZ2_EXE";
    const char* SMCP_SPZ1_EXE = "SMCP_SPZ1_EXE";
    const char* SMCP_SPZ2_EXE = "SMCP_SPZ2_EXE";
    const char* SMCP_FBZ1_EXE = "SMCP_FBZ1_EXE";
    const char* SMCP_FBZ2_EXE = "SMCP_FBZ2_EXE";
    const char* SMCP_PGZ1_EXE = "SMCP_PGZ1_EXE";
    const char* SMCP_PGZ2_EXE = "SMCP_PGZ2_EXE";
    const char* SMCP_SSZ1_EXE = "SMCP_SSZ1_EXE";
    const char* SMCP_SSZ2_EXE = "SMCP_SSZ2_EXE";
    const char* SMCP_HCZ1_EXE = "SMCP_HCZ1_EXE";
    const char* SMCP_HCZ2_EXE = "SMCP_HCZ2_EXE";
    const char* SMCP_MSZ1_EXE = "SMCP_MSZ1_EXE";
    const char* SMCP_MSZ2_EXE = "SMCP_MSZ2_EXE";
    const char* SMCP_OOZ1_EXE = "SMCP_OOZ1_EXE";
    const char* SMCP_OOZ2_EXE = "SMCP_OOZ2_EXE";
    const char* SMCP_LRZ1_EXE = "SMCP_LRZ1_EXE";
    const char* SMCP_LRZ2_EXE = "SMCP_LRZ2_EXE";
    const char* SMCP_MMZ1_EXE = "SMCP_MMZ1_EXE";
    const char* SMCP_MMZ2_EXE = "SMCP_MMZ2_EXE";
    const char* SMCP_TMZ1_EXE = "SMCP_TMZ1_EXE";
    const char* SMCP_TMZ2_EXE = "SMCP_TMZ2_EXE";

    const char* SMCP_AIZ_EXT = "SMCP_AIZ_EX";

    const char* SMCP_CXM_IIZ1 = "SMCP_CXM_IIZ1";
    const char* SMCP_CXM_AAZ1 = "SMCP_CXM_AAZ";
    const char* SMCP_CXM_SSZ1 = "SMCP_CXM_SSZ1";
    const char* SMCP_CXM_BBZ1 = "SMCP_CXM_BBZ";
    const char* SMCP_CXM_MMZ1 = "SMCP_CXM_MMZ1";
    const char* SMCP_CXM_TTZ1 = "SMCP_CXM_TTZ1";

    const char* SMCP_CXM_IIZ1E = "SMCP_CXM_IIZ1E";
    const char* SMCP_CXM_AAZ1E = "SMCP_CXM_AAZE";
    const char* SMCP_CXM_SSZ1E = "SMCP_CXM_SSZ1E";
    const char* SMCP_CXM_BBZ1E = "SMCP_CXM_BBZE";
    const char* SMCP_CXM_MMZ1E = "SMCP_CXM_MMZ1E";
    const char* SMCP_CXM_TTZ1E = "SMCP_CXM_TTZ1E";

    const char* SMCP_TSZ = "SMCP_TSZ";

    const char* SMCP_DHZ = "SMCP_DHZ";
    const char* SMCP_DHZE = "SMCP_DHZE";

    const char* SMCP_SZ = "SMCP_SZ";
    const char* SMCP_SZE = "SMCP_SZE";

    const char* SMCP_GPZ1 = "SMCP_GPZ";
    const char* SMCP_GPZ1E = "SMCP_GPZE";

    const char* SMCP_LHPZ1 = "SMCP_LHPZ1";
    const char* SMCP_LHPZ1E = "SMCP_LHPZ1E";

    const char* SMCP_STHZ1 = "SMCP_STHZ1";
    const char* SMCP_STHZ2 = "SMCP_STHZ1";

    const char* SMCP_MBZ1 = "SMCP_MBZ1";
    const char* SMCP_MBZ2 = "SMCP_MBZ1";

    const char* SMCP_GGZ1 = "SMCP_GGZ1";
    const char* SMCP_GGZ2 = "SMCP_GGZ2";

    const char* SMCP_Logos1 = "SMCP_LOGOS";
    const char* SMCP_Logos2 = "SMCP_LOGOS2";
    const char* SMCP_Logos3 = "SMCP_LOGOS3";
    const char* SMCP_Logos4 = "SMCP_LOGOS4";

    const char* HUBWorld = "SMCP_HUB1";
    const char* HUBWorld_EXE = "SMCP_HUB1HWN";
    const char* HUBSettings = "SMCP_HUB3";
    const char* HUBRanking = "SMCP_HUB2";

    const char* LSelect_Mania = "SMCP_M_LS";
    const char* LSelect_Encore = "SMCP_E_LS";
    const char* LSelect_Custom = "SMCP_C_LS";
    const char* LSelect_Chaotix = "SMCP_CX_LS";
    const char* LSelect_Phantom = "SMCP_P_LS";
    const char* LSelect_Exe = "SMCP_EXE_LS";

	void LoadLevel_IZ(const char* key)
	{
        IZAPI::ChangeScene(key);
		GameState = GameStates::GameState_NotRunning;
		CompPlus_Core::StageRefresh = true;
		CompPlus_Core::IZ_SceneChangeIdleTime = 10;
	}

	void LoadLevel(int LevelID)
	{
		SonicMania::CurrentSceneInt = LevelID;
		GameState = GameStates::GameState_NotRunning;
		CompPlus_Core::StageRefresh = true;
		CompPlus_Core::IZ_SceneChangeIdleTime = 10;
	}

    void LoadHUBWorld(bool ForcedOverworld = false)
    {
        if (CompPlus_Scoring::PodeiumSpawnActive && !ForcedOverworld)
        {
            CompPlus_HubCore::ReturnDestination = 2;
            LoadLevel_IZ(HUBRanking);
        }
        else 
        {
            CompPlus_HubCore::ReturnDestination = 0;
            if (CompPlus_Settings::CurrentSeason == CompPlus_Settings::Season_EXE) LoadLevel_IZ(HUBWorld_EXE);
            else LoadLevel_IZ(HUBWorld);
        }

    }

    void LoadHUBWorld()
    {
        LoadHUBWorld(false);
    }

	void PlayMenuMoveSoundFX(bool isClassic)
	{
		if (isClassic) PlaySoundFXS(SFX_MenuBleepClassic);
		else PlaySoundFXS(SFX_MenuBleep);
	}

	void PlayMenuAcceptSoundFX(bool isClassic)
	{    
		if (isClassic) PlaySoundFXS(SFX_MenuAccept);
        else PlaySoundFXS(SFX_MenuAcceptClassic);
	}

    void LoadLastLevelSelect() 
    {
        if (CompPlus_Status::CurrentLevelSelect == 0) LoadLevel_IZ(LSelect_Mania);
        else if (CompPlus_Status::CurrentLevelSelect == 1) LoadLevel_IZ(LSelect_Encore);
        else if (CompPlus_Status::CurrentLevelSelect == 2) LoadLevel_IZ(LSelect_Custom);
        else if (CompPlus_Status::CurrentLevelSelect == 3) LoadLevel_IZ(LSelect_Chaotix);
        else if (CompPlus_Status::CurrentLevelSelect == 4) LoadLevel_IZ(LSelect_Exe);
    }

    void SetLastLevelSelect(int Value) 
    {
        if (CompPlus_Status::CurrentLevelSelect != Value) CompPlus_Settings::SetCurrentLSelect(Value);
    }
};