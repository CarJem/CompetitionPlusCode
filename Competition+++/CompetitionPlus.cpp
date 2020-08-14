#include "stdafx.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"

#include "SonicMania.h"
#include "ManiaLevelSelect.h"
#include "EncoreLevelSelect.h"
#include "CustomLevelSelect.h"
#include "PhantomLevelSelect.h"
#include "CompetitionManiaMenu.h"
#include "HubWorld.h"
#include "SettingsMenu.h"

#include "IZAPI.h"


namespace CompetitionPlus
{
	using namespace SonicMania;

	bool RequirePointRefresh = true;
	int IdleTime = 0;
	HMODULE InfinityZoneDLL = nullptr;
	IZAPI::StageInfo CurrentStage = {};

	void IZChangeStage(const char* key)
	{
		IZAPI::ChangeStage(key);
    }

	void MultiColorMods()
	{
		if (Player1.Character != SonicMania::Character_Sonic)
		{
			FastChangeCharacter(&Player1, SonicMania::Character_Sonic);
		}
		if (Player2.Character != SonicMania::Character_Sonic)
		{
			FastChangeCharacter(&Player2, SonicMania::Character_Sonic);
		}
		if (Player3.Character != SonicMania::Character_Sonic)
		{
			FastChangeCharacter(&Player3, SonicMania::Character_Sonic);
		}
		if (Player4.Character != SonicMania::Character_Sonic)
		{
			FastChangeCharacter(&Player4, SonicMania::Character_Sonic);
		}
	}

	void UpdateMenus()
	{

		if (RequirePointRefresh) 
		{
			CompPlus_ManiaLevelSelect::CheckForPointRefresh();
			CompPlus_EncoreLevelSelect::CheckForPointRefresh();
			CompPlus_CustomLevelSelect::CheckForPointRefresh();
			RequirePointRefresh = false;
		}

		if (CurrentStage.StageKey)
		{
			if (IdleTime == 0) 
			{
				if (!strcmp(CurrentStage.StageKey, "CPMM")) CompPlus_CompetitionMenu::UpdateManiaMenu();
				else if (!strcmp(CurrentStage.StageKey, "CPMLS")) CompPlus_ManiaLevelSelect::UpdateManiaLSelect();
				else if (!strcmp(CurrentStage.StageKey, "CPELS")) CompPlus_EncoreLevelSelect::UpdateEncoreLSelect();
				else if (!strcmp(CurrentStage.StageKey, "CPCLS")) CompPlus_CustomLevelSelect::UpdateCustomLSelect();
				else if (!strcmp(CurrentStage.StageKey, "CPPLS")) CompPlus_PhantomLevelSelect::UpdatePhantomLSelect();
				else if (!strcmp(CurrentStage.StageKey, "CPHW")) CompPlus_HubWorld::UpdateHUBWorld();
			}
			else 
			{
				IdleTime = IdleTime - 1;
			}
		}
	}

	void __cdecl OnStageLoad(IZAPI::StageInfo info)
	{
		printf("StageLoad: %s\n", info.StageName);
		CurrentStage = info;
		RequirePointRefresh = true;
		IdleTime = 10;
    }

	void __cdecl OnStageUnload(IZAPI::StageInfo info)
	{		
		printf("StageUnload: %s\n", info.StageName);
		CurrentStage = { };
		RequirePointRefresh = true;
		IdleTime = 10;
    }
};

