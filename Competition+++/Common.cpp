#include "stdafx.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "SonicMania.h"
#include "CompetitionPlus.h"

namespace CompPlus_Common
{
	using namespace SonicMania;
	using namespace CompetitionPlus;


	void LoadLevel_IZ(const char* key)
	{
		CompetitionPlus::IZChangeStage(key);
		GameState = GameStates::GameState_NotRunning;
		CompetitionPlus::RequirePointRefresh = true;
		CompetitionPlus::IdleTime = 10;
	}

	void LoadLevel(int LevelID)
	{
		LoadScene(LevelID);
		CurrentSceneInt = LevelID;
		GameState = GameStates::GameState_NotRunning;
		CompetitionPlus::RequirePointRefresh = true;
		CompetitionPlus::IdleTime = 10;
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
};
