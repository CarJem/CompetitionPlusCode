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
#include "LevelSelectCore.h"
#include "Common.h"
#include "HubWorld.h"
#include "SettingsMenu.h"
#include "GenericLogos.h"
#include "GeneralTweaks.h"
#include "CreditsScene.h"
#include "CompPlus_Scoring.h"

#include "CompPlus_Announcers.h"

#include "IZAPI.h"

#include <iostream>
#include <fstream>


namespace CompetitionPlus
{
	using namespace SonicMania;

    #pragma region Variables

    bool HasStartupInit = false;
	bool StartupStageEnabled = false;

	bool StageRefresh = true;
    int LastSceneID = 0;
	int IdleTime = 0;
	HMODULE InfinityZoneDLL = nullptr;
	IZAPI::StageInfo CurrentStage = {};

    #pragma endregion

    #pragma region Init Calls

    extern void InitMod()
    {
        CompPlus_LevelSelectCore::Init();
        CompPlus_HubWorld::Init();
    }

    extern void InitAnnouncerFX()
    {
        CompPlus_Announcers::LoadAnnouncerFX();
    }

    extern void InitSettings(const char* path)
    {
        CompPlusSettings::Settings_FilePath = path;
        CompPlusSettings::LoadSettings();
    }

    void FrameInit()
    {
        if (!HasStartupInit)
        {
            if (StartupStageEnabled) CompPlus_Common::LoadLevel_IZ("CPCREDITS");
            HasStartupInit = true;
        }
    }

    #pragma endregion

    #pragma region General Methods

    void OnLegacySceneChange()
    {
        if (LastSceneID == CurrentSceneInt)
        {
            LastSceneID = CurrentSceneInt;
            StageRefresh = true;
        }
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
		else if (CurrentSceneInt == 141) CompPlus_Common::LoadLastLevelSelect();
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
            else if (!strcmp(CurrentStage.StageKey, "CPHW")) CompPlus_HubWorld::OnFrame();
            else if (!strcmp(CurrentStage.StageKey, "CPLOGOS2")) CompPlus_GenericLogos::UpdateATGLogos();
            else if (!strcmp(CurrentStage.StageKey, "CPLOGOS3")) CompPlus_GenericLogos::UpdateCJLogos();
            else if (!strcmp(CurrentStage.StageKey, "CPLOGOS4")) CompPlus_GenericLogos::UpdateIZLogos();
            else if (!strcmp(CurrentStage.StageKey, "CPCREDITS")) CompPlus_Credits::OnFrame();
            CompPlus_GeneralTweaks::UpdateScenes(CurrentStage.StageKey);
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

	void CheckForStageRefresh() 
	{
		if (StageRefresh)
		{
			CompPlus_ManiaLevelSelect::CheckForPointRefresh();
			CompPlus_EncoreLevelSelect::CheckForPointRefresh();
			CompPlus_CustomLevelSelect::CheckForPointRefresh();
			CompPlus_ChaotixLevelSelect::CheckForPointRefresh();
            CompPlusSettings::RefreshSettings();
            CompPlusSettings::SaveSettings();
			StageRefresh = false;
		}
	}

	void UpdateMenus()
	{
        FrameInit();
        OnLegacySceneChange();
		CompPlusSettings::OnFrame();
		ManiaMenuLinking();
		CheckForStageRefresh();
        CompPlus_Scoring::OnFrame();

		if (CurrentStage.StageKey) InfinityZoneLoop();
		else GenericZoneLoop();
	}

    void OnSceneReset() 
    {
        CompPlus_HubWorld::isRestart = true;
    }

	void DrawHook() 
	{
		CompPlus_Settings_Base::DoMenuOnScreenDraw();
	}

    #pragma endregion

    #pragma region InfinityZone Calls

    void IZChangeStage(const char* key)
    {
        IZAPI::ChangeStage(key);
    }

	void __cdecl OnStageLoad(IZAPI::StageInfo info, IZAPI::StageLoadPhase phase)
	{
		printf("StageLoad: %s\n", info.StageName);
		CurrentStage = info;
		StageRefresh = true;
		IdleTime = 10;
        CompPlus_Announcers::ChangeAnnouncer();
    }

	void __cdecl OnStageUnload(IZAPI::StageInfo info, IZAPI::StageLoadPhase phase)
	{		
		printf("StageUnload: %s\n", info.StageName);
		CurrentStage = { };
		StageRefresh = true;
		IdleTime = 10;
		if (!strcmp(info.StageKey, "CPLOGOS") && (CurrentSceneInt == 1 || CurrentSceneInt == 4)) CompPlus_Common::LoadLevel(142);
    }

    #pragma endregion

};

