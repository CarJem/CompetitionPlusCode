#include "stdafx.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "CompPlusSettings.h"

#include "SonicMania.h"
#include "ManiaLevelSelect.h"
#include "EncoreLevelSelect.h"
#include "CustomLevelSelect.h"
#include "PhantomLevelSelect.h"
#include "CompetitionManiaMenu.h"
#include "Common.h"
#include "HubWorld.h"
#include "SettingsMenu.h"

#include "IZAPI.h"


namespace CompetitionPlus
{
	using namespace SonicMania;

	bool StageRefresh = true;
	bool StartupStageEnabled = false;
	bool HasStartupInit = false;
	int IdleTime = 0;
	HMODULE InfinityZoneDLL = nullptr;
	IZAPI::StageInfo CurrentStage = {};
	bool NextTitleSequence = false;

	void IZChangeStage(const char* key)
	{
		IZAPI::ChangeStage(key);
	}

	void StartupStage()
	{
		if (!HasStartupInit)
		{
			if (StartupStageEnabled)
			{
				CompPlus_Common::LoadLevel_IZ("CPHW");
			}
			HasStartupInit = true;
		}

	}

	void DrawTest()
	{
		if (!strcmp(CurrentStage.StageKey, "CPSW")) CompPlus_Settings_Base::CanDraw = true;
		else CompPlus_Settings_Base::CanDraw = false;
	}

	void ManiaMenuLinking() 
	{
		if (CurrentSceneInt == 0) CompPlus_Common::LoadLevel_IZ("CPLOGOS");
		else if (CurrentSceneInt == 140) CompPlus_Common::LoadLevel_IZ("CPHW");
		else if (CurrentSceneInt == 141) CompPlus_HubWorld::LoadLevelSelect();
		else if (CurrentSceneInt == 142) CompPlus_Common::LoadLevel_IZ("CPLOGOS2");
	}

	void InfinityZoneLoop() 
	{
		if (IdleTime == 0)
		{
			if (!strcmp(CurrentStage.StageKey, "CPMLS")) CompPlus_ManiaLevelSelect::UpdateManiaLSelect();
			else if (!strcmp(CurrentStage.StageKey, "CPELS")) CompPlus_EncoreLevelSelect::UpdateEncoreLSelect();
			else if (!strcmp(CurrentStage.StageKey, "CPCLS")) CompPlus_CustomLevelSelect::UpdateCustomLSelect();
			else if (!strcmp(CurrentStage.StageKey, "CPPLS")) CompPlus_PhantomLevelSelect::UpdatePhantomLSelect();
			else if (!strcmp(CurrentStage.StageKey, "CPSW")) CompPlus_Settings_Base::UpdateSettingsMenu();
			else if (!strcmp(CurrentStage.StageKey, "CPHW")) CompPlus_HubWorld::UpdateHUBWorld();
		}
		else
		{
			IdleTime = IdleTime - 1;
		}
	}

	void GenericZoneLoop() 
	{
		if (CurrentSceneInt == 2) CompPlus_CompetitionMenu::UpdateManiaMenu();
	}

	void RequirePointRefreshCheck() 
	{
		if (StageRefresh)
		{
			CompPlus_ManiaLevelSelect::CheckForPointRefresh();
			CompPlus_EncoreLevelSelect::CheckForPointRefresh();
			CompPlus_CustomLevelSelect::CheckForPointRefresh();
			CompPlusSettings::StageLoadApplyConfig();
			StageRefresh = false;
		}
	}

	void UpdateMenus()
	{
		CompPlusSettings::UpdateSettingsLoop();
		StartupStage();
		ManiaMenuLinking();
		RequirePointRefreshCheck();

		if (CurrentStage.StageKey) InfinityZoneLoop();
		else GenericZoneLoop();
	}

	void DrawHook() 
	{
		CompPlus_Settings_Base::DoMenuOnScreenDraw();
	}

	void __cdecl OnStageLoad(IZAPI::StageInfo info)
	{
		printf("StageLoad: %s\n", info.StageName);
		CurrentStage = info;
		StageRefresh = true;
		IdleTime = 10;
    }

	void __cdecl OnStageUnload(IZAPI::StageInfo info)
	{		
		printf("StageUnload: %s\n", info.StageName);
		CurrentStage = { };
		StageRefresh = true;
		IdleTime = 10;

		BYTE* Pointer = *(BYTE**)((baseAddress + 0xAA763C));
		WriteData((BYTE*)(Pointer + 0x410B4), (BYTE)13);

		if (!strcmp(info.StageKey, "CPLOGOS")) CompPlus_Common::LoadLevel(142);
		else if (!strcmp(info.StageKey, "CPLOGOS2")) CompPlus_Common::LoadLevel(1);
    }
};

