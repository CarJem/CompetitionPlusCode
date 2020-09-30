#include "stdafx.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "SonicMania.h"
#include "CompPlus_Core.h"
#include "CompPlus_Settings.h"
#include "CompPlus_Scoring.h"

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

    void LoadHUBWorld()
    {
        LoadLevel_IZ("CPHW");
    }

    void LoadLevel_IZ_CompPlus(const char* key)
    {
        LoadLevel_IZ(key);
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

    void DisableVSPointAddingAddress()
    {
        void* vs_incrementing_address = (void*)(baseAddress + 0xE35C);
        char nops[2];
        memset(nops, 0x90, sizeof nops);
        WriteData(vs_incrementing_address, nops, 0x02);
    }

    void FixUnmatchingVSPlayers()
    {
        SonicMania::Character P1_Char = (SonicMania::Character)(SonicMania::Options->CompetitionSession.CharacterFlags[0]);
        SonicMania::Character P2_Char = (SonicMania::Character)(SonicMania::Options->CompetitionSession.CharacterFlags[1]);
        SonicMania::Character P3_Char = (SonicMania::Character)(SonicMania::Options->CompetitionSession.CharacterFlags[2]);
        SonicMania::Character P4_Char = (SonicMania::Character)(SonicMania::Options->CompetitionSession.CharacterFlags[3]);

        CompPlus_Settings::UpdatePlayer(1, P1_Char, false);
        CompPlus_Settings::UpdatePlayer(2, P2_Char, false);
        CompPlus_Settings::UpdatePlayer(3, P3_Char, false);
        CompPlus_Settings::UpdatePlayer(4, P4_Char, false);
    }

    void FixRayAndMighty2P()
    {
        int PatchP2Ray[] = { 0xE9, 0xC4, 0x01, 0x00, 0x00, 0x90 };
        int i;
        int OffsetNormal = 0xC31E5;
        for (i = 0; i < 6; i++)
        {
            WriteData<1>((void*)(baseAddress + OffsetNormal), PatchP2Ray[i]); //put data back.
            OffsetNormal++;

        }
    }
};
