#include "CompPlus_Scenes.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "include/ManiaAPI/SonicMania.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "CompPlus_Extensions/IZAPI.h"
#include "CompPlus_Extensions/Helpers.h"

#include "CompPlus_Scenes/Custom Scenes/GustPlanet.h"
#include "CompPlus_Scenes/Custom Scenes/LHPZ.h"
#include "CompPlus_Scenes/Custom Scenes/MetrotropicBeach.h"

#include "CompPlus_Core/CompPlus_Scenes.h"
#include "CompPlus_Scenes/General Scenes/ManiaMenu.h"
#include "CompPlus_Scenes/General Scenes/CreditsScene.h"
#include "CompPlus_Scenes/General Scenes/PlayerSettings.h"
#include "CompPlus_Scenes/General Scenes/GenericLogos.h"
#include "CompPlus_Scenes/General Scenes/DAGarden.h"
#include "CompPlus_Scenes/General Scenes/TitleScreen.h"

#include "CompPlus_Functionality/ZoneSpecifics.h"
#include "CompPlus_Functionality/SpecialRings.h"
#include "CompPlus_Functionality/EntityLoop.h"
#include "CompPlus_Functionality/SizeLazer.h"
#include "CompPlus_Functionality/Halloween2018.h"
#include "CompPlus_Functionality/VapeMusic.h"
#include "CompPlus_Functionality/FBZStorm.h"

#include "CompPlus_Scenes/Level Select/ManiaLevelSelect.h"
#include "CompPlus_Scenes/Level Select/EncoreLevelSelect.h"
#include "CompPlus_Scenes/Level Select/CustomLevelSelect.h"
#include "CompPlus_Scenes/Level Select/ChaotixLevelSelect.h"
#include "CompPlus_Scenes/Level Select/ExeLevelSelect.h"
#include "CompPlus_Scenes/Level Select/PhantomLevelSelect.h"
#include "CompPlus_Scenes/Level Select/CoreLevelSelect.h"

#include "Base.h"
#include "CompPlus_Core/CompPlus_Scoring.h"
#include "CompPlus_Core/CompPlus_Announcers.h"
#include "CompPlus_Core/CompPlus_Controllers.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_DevMenu.h"
#include "CompPlus_Core/CompPlus_Status.h"

#include "CompPlus_Scenes/HUB World/HubWorld.h"
#include "CompPlus_Scenes/HUB World/HubRanking.h"
#include "CompPlus_Scenes/HUB World/HubSettings.h"
#include "CompPlus_Scenes/HUB World/HubText.h"

#include <iostream>
#include <fstream>

namespace CompPlus_Scenes
{
    using namespace CompPlus_Core;

    void UpdateSZ() 
    {
        if (!SonicMania::Timer.Enabled) 
        {
            SonicMania::Player1.Right = true;
            SonicMania::Player2.Right = true;
            SonicMania::Player3.Right = true;
            SonicMania::Player4.Right = true;
        }
    }

    CompPlus_Patches::WaterColorDefintion OnWaterColorDraw() 
    {
        if (CurrentStage.SceneKey)
        {
            if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_MBZ1)) return CompPlus_Patches::WaterColorDefintion(SonicMania::Color(0, 0, 255), 15, InkEffect::Ink_Alpha);
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_MBZ2)) return CompPlus_Patches::WaterColorDefintion(SonicMania::Color(0, 0, 255), 15, InkEffect::Ink_Alpha);
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_STHZ2)) return CompPlus_Patches::WaterColorDefintion(SonicMania::Color(97, 213, 255), 10, InkEffect::Ink_Alpha);
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_DHZ)) return CompPlus_Patches::WaterColorDefintion(SonicMania::Color(50, 0, 255), 15, InkEffect::Ink_Alpha);
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_DHZE)) return CompPlus_Patches::WaterColorDefintion(SonicMania::Color(50, 0, 255), 15, InkEffect::Ink_Alpha);
        }

        return CompPlus_Patches::WaterColorDefintion(SonicMania::Color(0, 0, 0), 0, InkEffect::Ink_Alpha);
    }

    void UpdateTitleCard()
    {
        if (CompPlus_Status::IsExecutorStage)
        {
            IZAPI::SetGlobalAsset("Data/Sprites/Global/TitleCard.bin", "Data/Sprites/SMCP_Executor/TitleCard.bin");
        }
        else
        {
            IZAPI::SetGlobalAsset("Data/Sprites/Global/TitleCard.bin", nullptr);
        }
    }

    void SetSceneSpecifics() 
    {
        if (CurrentStage.SceneKey) CompPlus_ZoneSpecifics::UpdateSpecifics(CurrentStage.SceneKey, -1);
        else CompPlus_ZoneSpecifics::UpdateSpecifics("", CurrentSceneInt);
    }

    void OnObjectPreDraw(const char* object) 
    {
        if (object) 
        {
            if (!strcmp(object, "HUBWorld"))
            {
                if (CurrentStage.SceneKey)
                {
                    if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBWorld)) CompPlus_HubWorld::SetObjectPalette();
                    else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBWorld_EXE)) CompPlus_HubWorld::SetObjectPalette();
                }
            }
        }
    }
    void OnObjectPostDraw(const char* object)
    {
        if (object)
        {
            if (!strcmp(object, "HUBWorld"))
            {
                if (CurrentStage.SceneKey) 
                {
                    if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBWorld)) CompPlus_HubWorld::UnsetObjectPalette();
                    else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBWorld_EXE)) CompPlus_HubWorld::UnsetObjectPalette();
                }
            }
        }
    }

    void OnSceneDraw() 
    {

        if (CompPlus_Status::IsExecutorStage) CompPlus_Halloween2018::OnDraw();

        if (CurrentStage.SceneKey)
        {
            if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Mania)) CompPlus_ManiaLevelSelect::OnDraw();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Encore)) CompPlus_EncoreLevelSelect::OnDraw();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Custom)) CompPlus_CustomLevelSelect::OnDraw();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Chaotix)) CompPlus_ChaotixLevelSelect::OnDraw();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Exe)) CompPlus_ExeLevelSelect::OnDraw();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBWorld)) CompPlus_HubCore::OnDraw();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBWorld_EXE)) CompPlus_HubCore::OnDraw();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBRanking)) CompPlus_HubCore::OnDraw();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBSettings)) CompPlus_HubCore::OnDraw();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_Credits)) CompPlus_Credits::OnDraw();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_DAGarden_Chaotix)) CompPlus_DAGarden_Chaotix::OnDraw();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_PlayerSettings)) CompPlus_PlayerSettings::DoMenuOnScreenDraw();
        }
        else if (CurrentSceneInt == 1) CompPlus_TitleScreen::OnDraw();

        CompPlus_FBZStorm::OnDraw();
    }

    void OnScenePreload()
    {
        if (CurrentStage.SceneKey)
        {
            if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Mania)) CompPlus_ManiaLevelSelect::OnPreload();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Encore)) CompPlus_EncoreLevelSelect::OnPreload();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Custom)) CompPlus_CustomLevelSelect::OnPreload();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Chaotix)) CompPlus_ChaotixLevelSelect::OnPreload();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Exe)) CompPlus_ExeLevelSelect::OnPreload();
        }
    }

    void IZRunningLoop()
    {
        if (IZ_SceneChangeIdleTime == 0)
        {
            // D.A. Gardens
            if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_DAGarden)) CompPlus_DAGarden::OnFrame();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_DAGarden_Mania)) CompPlus_DAGarden_Mania::OnFrame();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_DAGarden_Encore)) CompPlus_DAGarden_Encore::OnFrame();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_DAGarden_Custom)) CompPlus_DAGarden_Custom::OnFrame();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_DAGarden_Chaotix)) CompPlus_DAGarden_Chaotix::OnFrame();
            // Level Selects
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Mania)) CompPlus_ManiaLevelSelect::OnFrame();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Encore)) CompPlus_EncoreLevelSelect::OnFrame();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Custom)) CompPlus_CustomLevelSelect::OnFrame();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Chaotix)) CompPlus_ChaotixLevelSelect::OnFrame();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Phantom)) CompPlus_PhantomLevelSelect::OnFrame();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::LSelect_Exe)) CompPlus_ExeLevelSelect::OnFrame();
            // Logos
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_Logos2)) CompPlus_GenericLogos::UpdateATGLogos();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_Logos3)) CompPlus_GenericLogos::UpdateCJLogos();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_Logos4)) CompPlus_GenericLogos::UpdateIZLogos();
            // HUB Levels
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBWorld)) CompPlus_HubWorld::OnFrame();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBWorld_EXE)) CompPlus_HubWorld::OnFrame();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBRanking)) CompPlus_HubRanking::OnFrame();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::HUBSettings)) CompPlus_HubSettings::OnFrame();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_PlayerSettings)) CompPlus_PlayerSettings::OnFrame();
            // Custom Levels
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_FBZ2)) CompPlus_FBZStorm::OnFrame();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_FBZ2E)) CompPlus_FBZStorm::OnFrame();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_SZ)) UpdateSZ();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_SZE)) UpdateSZ();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_GPZ1)) CompPlus_Scene_GustPlanet::OnFrame();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_GPZ1E)) CompPlus_Scene_GustPlanet::OnFrame();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_LHPZ1)) CompPlus_Scene_LHPZ::OnFrame();
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_LHPZ1E)) CompPlus_Scene_LHPZ::OnFrame();

            //Unique Coded Levels
            CompPlus_Credits::OnFrame(!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_Credits));
        }
        else IZ_SceneChangeIdleTime = IZ_SceneChangeIdleTime - 1;
    }

    void AlwaysRunningLoop() 
    {
        if (CurrentStage.SceneKey)
        {
            if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_MBZ1)) CompPlus_MetrotropicBeach::OnFrame(1);
            else if (!strcmp(CurrentStage.SceneKey, CompPlus_Common::SMCP_MBZ2)) CompPlus_MetrotropicBeach::OnFrame(2);
        }
    }

    void NormalRunningLoop()
    {

        if (CurrentSceneInt == 0) CompPlus_Common::LoadLevel_IZ(CompPlus_Common::SMCP_Logos1);
        else if (CurrentSceneInt == 65) CompPlus_Common::LoadHUBWorld();
        else if (CurrentSceneInt == 66) CompPlus_Common::LoadLastLevelSelect();
        else if (CurrentSceneInt == 67) CompPlus_Common::LoadLevel_IZ(CompPlus_Common::HUBRanking);
        else if (CurrentSceneInt == 123) CompPlus_Common::LoadLevel_IZ(CompPlus_Common::SMCP_Logos2);
        else if (CurrentSceneInt == 2) CompPlus_ManiaMenu::UpdateManiaMenu();
        else if (CurrentSceneInt == Scene::Scene_DAGarden) CompPlus_Common::LoadLevel_IZ(CompPlus_Common::SMCP_DAGarden);
        else if (CurrentSceneInt == Scene::Scene_DAGarden_e) CompPlus_Common::LoadLevel_IZ(CompPlus_Common::SMCP_DAGarden);
        else if (CurrentSceneInt == Scene::Scene_Credits) CompPlus_Common::LoadLevel_IZ(CompPlus_Common::HUBSettings);
        else if (CurrentSceneInt == Scene::Scene_PuyoPuyo) CompPlus_Scoring::ApplyPoyoPoyoRuleset();
    }

    void UpdateScenes() 
    {
        if (CurrentStage.StageKey) IZRunningLoop();
        else NormalRunningLoop();

        CompPlus_DAGarden_Core::OnFrame();
        CompPlus_TitleScreen::OnFrame();
        UpdateTitleCard();
    }
}