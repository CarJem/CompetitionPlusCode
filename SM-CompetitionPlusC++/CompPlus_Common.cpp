#include "stdafx.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "SonicMania.h"
#include "CompPlus_Core.h"
#include "CompPlus_Settings.h"

namespace CompPlus_Common
{
	using namespace SonicMania;
	using namespace CompPlus_Core;


	void LoadLevel_IZ(const char* key)
	{
		CompPlus_Core::IZChangeStage(key);
		GameState = GameStates::GameState_NotRunning;
		CompPlus_Core::StageRefresh = true;
		CompPlus_Core::IdleTime = 10;
	}

	void LoadLevel(int LevelID)
	{
		SonicMania::CurrentSceneInt = LevelID;
		GameState = GameStates::GameState_NotRunning;
		CompPlus_Core::StageRefresh = true;
		CompPlus_Core::IdleTime = 10;
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

	void FixSummary()
	{
		//Remove A/Start from the Game Summary
		WriteData((BYTE*)(baseAddress + 0x00190618), (BYTE)0xEB);
	}

    void LoadLastLevelSelect() 
    {
        if (CompPlus_Settings::CurrentLevelSelect == 0) LoadLevel_IZ("CPMLS");
        else if (CompPlus_Settings::CurrentLevelSelect == 1) LoadLevel_IZ("CPELS");
        else if (CompPlus_Settings::CurrentLevelSelect == 2) LoadLevel_IZ("CPCLS");
        else if (CompPlus_Settings::CurrentLevelSelect == 3) LoadLevel_IZ("CPCXLS");
    }

    void SetLastLevelSelect(int Value) 
    {
        if (CompPlus_Settings::CurrentLevelSelect != Value) CompPlus_Settings::SetCurrentLSelect(Value);
    }
};
