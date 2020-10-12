#include "stdafx.h"
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
	using namespace SonicMania;
	using namespace CompPlus_Core;

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
            LoadLevel_IZ("SMCP_HUB2");
        }
        else 
        {
            CompPlus_HubCore::ReturnDestination = 0;
            //LoadLevel_IZ("SMCP_HUB1");
            LoadLevel_IZ("SMCP_HUB1HWN");
        }

    }

    void LoadHUBWorld()
    {
        LoadHUBWorld(false);
    }

	void PlayMenuMoveSoundFX(bool isClassic)
	{
		if (isClassic)
		{
			PlaySoundFXS("CompPlus/MenuBleepClassic.wav");
		}
		else
		{
			PlaySoundFXS("Global/MenuBleep.wav");
		}
	}

	void PlayMenuAcceptSoundFX(bool isClassic)
	{
		if (isClassic)
		{
			PlaySoundFXS("CompPlus/MenuAcceptClassic.wav");
		}
		else
		{
			PlaySoundFXS("Global/MenuAccept.wav");
		}

	}

    void LoadLastLevelSelect() 
    {
        if (CompPlus_Status::CurrentLevelSelect == 0) LoadLevel_IZ("CPMLS");
        else if (CompPlus_Status::CurrentLevelSelect == 1) LoadLevel_IZ("CPELS");
        else if (CompPlus_Status::CurrentLevelSelect == 2) LoadLevel_IZ("CPCLS");
        else if (CompPlus_Status::CurrentLevelSelect == 3) LoadLevel_IZ("CPCXLS");
    }

    void SetLastLevelSelect(int Value) 
    {
        if (CompPlus_Status::CurrentLevelSelect != Value) CompPlus_Settings::SetCurrentLSelect(Value);
    }
};
