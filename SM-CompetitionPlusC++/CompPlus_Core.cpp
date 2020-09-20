#include "stdafx.h"
#include "ManiaModLoader.h"
#include "SonicMania.h"
#include "ManiaExt.h"

#include "ManiaMenu.h"
#include "SceneTweaks.h"
#include "GustPlanet.h"
#include "LHPZ.h"

#include "HubWorld.h"
#include "CreditsScene.h"
#include "SettingsMenu.h"
#include "GenericLogos.h"

#include "ManiaLevelSelect.h"
#include "EncoreLevelSelect.h"
#include "CustomLevelSelect.h"
#include "ChaotixLevelSelect.h"
#include "PhantomLevelSelect.h"
#include "LevelSelectCore.h"

#include "CompPlus_Scoring.h"
#include "CompPlus_Announcers.h"
#include "CompPlus_Controllers.h"
#include "CompPlus_Internal.h"
#include "CompPlus_Common.h"
#include "CompPlus_Settings.h"

#include "IZAPI.h"

#include <iostream>
#include <fstream>


namespace CompPlus_Core
{
	using namespace SonicMania;

    #pragma region Variables


    //Internal Paramater Variables
    bool StartupStageEnabled = false;

    //Status Variables
    bool HasStartupInit = false;
    bool StageRefresh = true;
    int LastSceneID = 0;
    int IZ_SceneChangeIdleTime = 0;
    HMODULE InfinityZoneDLL = nullptr;
    IZAPI::StageInfo CurrentStage = {};

    #pragma endregion

    #pragma region Init Calls

    extern void InitMod()
    {
        CompPlus_LevelSelectCore::Init();
        CompPlus_HubWorld::Init();
        CompPlus_ManiaMenu::Init();
        CompPlus_Credits::Init();
    }

    extern void InitAnnouncerFX()
    {
        CompPlus_Announcers::LoadAnnouncerFX();
    }

    extern void InitSettings(const char* path)
    {
        CompPlus_Settings::Settings_FilePath = path;
        CompPlus_Settings::LoadSettings();
    }

    #pragma endregion

    #pragma region Zone Loops

    void InfinityZoneLoop()
    {
        if (IZ_SceneChangeIdleTime == 0)
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
            else if (!strcmp(CurrentStage.StageKey, "CPLOGOS4")) CompPlus_GenericLogos::UpdateIZLogos();
            else if (!strcmp(CurrentStage.StageKey, "CPGPZ")) CompPlus_Scene_GustPlanet::OnFrame();
            else if (!strcmp(CurrentStage.StageKey, "CPGPZE")) CompPlus_Scene_GustPlanet::OnFrame();
            else if (!strcmp(CurrentStage.StageKey, "SMCP_LHPZ1")) CompPlus_Scene_LHPZ::OnFrame();
            else if (!strcmp(CurrentStage.StageKey, "SMCP_LHPZ1E")) CompPlus_Scene_LHPZ::OnFrame();
            CompPlus_Credits::OnFrame(!strcmp(CurrentStage.StageKey, "CPCREDITS"));
            CompPlus_SceneTweaks::UpdateScenes(CurrentStage.StageKey);
        }
        else
        {
            IZ_SceneChangeIdleTime = IZ_SceneChangeIdleTime - 1;
        }
    }

    void GenericZoneLoop()
    {
        if (CurrentSceneInt == 0) CompPlus_SceneTweaks::UpdateScenes("1");
        else if (CurrentSceneInt == 1) CompPlus_SceneTweaks::UpdateScenes("0");
        else if (CurrentSceneInt == 65) CompPlus_Common::LoadHUBWorld();
        else if (CurrentSceneInt == 66) CompPlus_Common::LoadLastLevelSelect();
        else if (CurrentSceneInt == 123) CompPlus_Common::LoadLevel_IZ("CPLOGOS2");
        else if (CurrentSceneInt == 2) CompPlus_ManiaMenu::UpdateManiaMenu();
        else if (CurrentSceneInt == SceneExt::Scene_PuyoPuyo) CompPlus_Scoring::ApplyPoyoPoyoRuleset();
    }

    #pragma endregion

    #pragma region General Methods

    void OnInit()
    {
        if (StartupStageEnabled) CompPlus_Common::LoadLevel_IZ("CPCREDITS");
        HasStartupInit = true;
    }

	void OnStageRefresh() 
	{
        CompPlus_Announcers::ReloadAnnouncerFX();
        CompPlus_ManiaLevelSelect::CheckForPointRefresh();
        CompPlus_EncoreLevelSelect::CheckForPointRefresh();
        CompPlus_CustomLevelSelect::CheckForPointRefresh();
        CompPlus_ChaotixLevelSelect::CheckForPointRefresh();
        CompPlus_Settings::RefreshSettings();
        CompPlus_Scoring::OnSceneReset();
        StageRefresh = false;
	}

    void OnLegacySceneChange()
    {
        LastSceneID = CurrentSceneInt;
        StageRefresh = true;
    }

    void OnSceneReset()
    {
        if (!(GameState & GameState_SoftPause)) CompPlus_HubWorld::isRestart = true;
        CompPlus_Credits::ResetScene();
        CompPlus_Settings::RefreshSettings();
        CompPlus_Scene_GustPlanet::OnReset();
    }

	void OnFrame()
	{
        if (!HasStartupInit) OnInit();
        if (StageRefresh) OnStageRefresh();
        if (LastSceneID != CurrentSceneInt) OnLegacySceneChange();
        CompPlus_Settings::OnFrame();
        CompPlus_Scoring::OnFrame();
        CompPlus_Controllers::OnFrame();
        CompPlus_Internal::OnFrame();
		if (CurrentStage.StageKey) InfinityZoneLoop();
		else GenericZoneLoop();
	}

	void OnDraw() 
	{
		CompPlus_Settings_Base::DoMenuOnScreenDraw();
	}

    void UpdateScreen() 
    {
        CompPlus_Settings::UpdateStrechScreen();
    }

    void OnActClear() 
    {

    }

    #pragma endregion

    #pragma region InfinityZone Calls

	void __cdecl OnStageLoad(IZAPI::StageInfo info, IZAPI::StageLoadPhase phase)
	{
		printf("StageLoad: %s\n", info.StageName);
		CurrentStage = info;
		StageRefresh = true;
		IZ_SceneChangeIdleTime = 10;
        OnSceneReset();
    }

	void __cdecl OnStageUnload(IZAPI::StageInfo info, IZAPI::StageLoadPhase phase)
	{		
		printf("StageUnload: %s\n", info.StageName);
		CurrentStage = { };
		StageRefresh = true;
		IZ_SceneChangeIdleTime = 10;
        if (!strcmp(info.StageKey, "CPLOGOS") && (CurrentSceneInt == 1 || CurrentSceneInt == 4)) CompPlus_Common::LoadLevel(123);
        OnSceneReset();
    }

    #pragma endregion

};

