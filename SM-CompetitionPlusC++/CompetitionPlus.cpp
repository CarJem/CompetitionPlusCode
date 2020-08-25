#include "stdafx.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "CompPlusSettings.h"

#include "SonicMania.h"
#include "ManiaLevelSelect.h"
#include "EncoreLevelSelect.h"
#include "CustomLevelSelect.h"
#include "ChaotixLevelSelect.h"
#include "PhantomLevelSelect.h"
#include "CompetitionManiaMenu.h"
#include "Common.h"
#include "HubWorld.h"
#include "SettingsMenu.h"
#include "GenericLogos.h"

#include "CompPlus_Announcers.h"

#include "IZAPI.h"


namespace CompetitionPlus
{
	using namespace SonicMania;

	bool StartupStageEnabled = false;


	bool StageRefresh = true;
	bool HasStartupInit = false;
	int IdleTime = 0;
	HMODULE InfinityZoneDLL = nullptr;
	IZAPI::StageInfo CurrentStage = {};

	void IZChangeStage(const char* key)
	{
		IZAPI::ChangeStage(key);
	}

	void StartupStage()
	{
		if (!HasStartupInit)
		{
			if (StartupStageEnabled) CompPlus_Common::LoadLevel_IZ("CPLOGOS4");
			HasStartupInit = true;
		}
	}

	void DrawTest()
	{
		if (!strcmp(CurrentStage.StageKey, "CPSW")) CompPlus_Settings_Base::CanDraw = true;
		else CompPlus_Settings_Base::CanDraw = false;
	}

	void LogoLinking() 
	{
		if (CurrentSceneInt == 0) CompPlus_Common::LoadLevel_IZ("CPLOGOS");

		if (CurrentSceneInt == 1) 
		{
			SetUIBG_BGColor(199, 235, 255);
			SetUIBG_FGLowColor(247, 146, 24);
			SetUIBG_FGHighColor(57, 178, 206);
		}
	}

	void ManiaMenuLinking() 
	{
		if (CurrentSceneInt == 0 || CurrentSceneInt == 1) LogoLinking();
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
			else if (!strcmp(CurrentStage.StageKey, "CPCXLS")) CompPlus_ChaotixLevelSelect::UpdateChaotixLSelect();
			else if (!strcmp(CurrentStage.StageKey, "CPPLS")) CompPlus_PhantomLevelSelect::UpdatePhantomLSelect();
			else if (!strcmp(CurrentStage.StageKey, "CPSW")) CompPlus_Settings_Base::UpdateSettingsMenu();
			else if (!strcmp(CurrentStage.StageKey, "CPHW")) CompPlus_HubWorld::UpdateHUBWorld();
			else if (!strcmp(CurrentStage.StageKey, "CPLOGOS2")) CompPlus_GenericLogos::UpdateATGLogos();
			else if (!strcmp(CurrentStage.StageKey, "CPLOGOS3")) CompPlus_GenericLogos::UpdateCJLogos();
			else if (!strcmp(CurrentStage.StageKey, "CPLOGOS4")) CompPlus_GenericLogos::UpdateIZLogos();
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
			CompPlus_ChaotixLevelSelect::CheckForPointRefresh();
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

	void __cdecl OnStageLoad(IZAPI::StageInfo info, IZAPI::StageLoadPhase phase)
	{
		printf("StageLoad: %s\n", info.StageName);
		CurrentStage = info;
		StageRefresh = true;
		IdleTime = 10;
    }

	void __cdecl OnStageUnload(IZAPI::StageInfo info, IZAPI::StageLoadPhase phase)
	{		
		printf("StageUnload: %s\n", info.StageName);
		CurrentStage = { };
		StageRefresh = true;
		IdleTime = 10;
		if (!strcmp(info.StageKey, "CPLOGOS") && (CurrentSceneInt == 1 || CurrentSceneInt == 4)) CompPlus_Common::LoadLevel(142);
    }

	extern void InitMod()
	{
		CompPlus_Announcers::LoadAnnouncerFX();
	}

	extern void InitSettings(const char* path) 
	{
		CompPlusSettings::Settings_FilePath = path;
		CompPlusSettings::LoadSettings();
	}
};

