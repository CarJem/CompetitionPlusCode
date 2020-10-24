#include "stdafx.h"
#include "ManiaModLoader.h"
#include "SonicMania.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "CompPlus_Extensions/IZAPI.h"
#include "CompPlus_Extensions/Helpers.h"
#include "CompPlus_Extensions/TitleCardColors.h"

#include "CompPlus_Scenes/Custom Scenes/GustPlanet.h"
#include "CompPlus_Scenes/Custom Scenes/LHPZ.h"

#include "CompPlus_Scenes/General Scenes/ManiaMenu.h"
#include "CompPlus_Scenes/General Scenes/CreditsScene.h"
#include "CompPlus_Scenes/General Scenes/SettingsMenu.h"
#include "CompPlus_Scenes/General Scenes/GenericLogos.h"
#include "CompPlus_Scenes/General Scenes/DAGarden.h"
#include "CompPlus_Scenes/General Scenes/TitleScreen.h"

#include "CompPlus_Scenes/Functionality/ZoneSpecifics.h"
#include "CompPlus_Scenes/Functionality/SpecialRings.h"
#include "CompPlus_Scenes/Functionality/EntityLoop.h"
#include "CompPlus_Scenes/Functionality/SizeLazer.h"
#include "CompPlus_Scenes/Functionality/Halloween2018.h"
#include "CompPlus_Scenes/Functionality/VapeMusic.h"
#include "CompPlus_Scenes/Functionality/CustomScreenStretch.h"
#include "CompPlus_Scenes/Functionality/DynCam.h"
#include "CompPlus_Scenes/Functionality/TailsFlightCancel.h"
#include "CompPlus_Scenes/Functionality/SpotlightC.h"
#include "CompPlus_Scenes/Functionality/PlayerSkins.h"

#include "CompPlus_Scenes/Level Select/ManiaLevelSelect.h"
#include "CompPlus_Scenes/Level Select/EncoreLevelSelect.h"
#include "CompPlus_Scenes/Level Select/CustomLevelSelect.h"
#include "CompPlus_Scenes/Level Select/ChaotixLevelSelect.h"
#include "CompPlus_Scenes/Level Select/ExeLevelSelect.h"
#include "CompPlus_Scenes/Level Select/PhantomLevelSelect.h"
#include "CompPlus_Scenes/Level Select/CoreLevelSelect.h"

#include "Base.h"
#include "CompPlus_Core/CompPlus_Scenes.h"
#include "CompPlus_Core/CompPlus_Scoring.h"
#include "CompPlus_Core/CompPlus_Announcers.h"
#include "CompPlus_Core/CompPlus_Controllers.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_DevMenu.h"
#include "CompPlus_Core/CompPlus_Status.h"
#include "CompPlus_Core/CompPlus_Patches.h"

#include "CompPlus_Scenes/HUB World/HubWorld.h"
#include "CompPlus_Scenes/HUB World/HubRanking.h"
#include "CompPlus_Scenes/HUB World/HubSettings.h"
#include "CompPlus_Scenes/HUB World/HubText.h"

#include <iostream>
#include <fstream>

extern "C"
{
    using namespace SonicMania;

    namespace CompPlus_Core
    {
        #pragma region Variables

        HMODULE InfinityZoneDLL = nullptr;
        IZAPI::StageInfo CurrentStage = {};

        const char* FullPath;
        char* SceneDirectory = (char*)(baseAddress + 0xA5359C);

        //Internal Paramater Variables
        bool StartupStage_Enabled = false;
        bool StartupStage_UseIZ = true;
        Scene StartupStage_Normal = Scene_Title;
        const char* StartupStage_Infinity = CompPlus_Common::SMCP_Credits;


        //Status Variables
        bool HasStartupInit = false;
        bool StageRefresh = true;
        int LastSceneID = 0;
        int IZ_SceneChangeIdleTime = 0;

        #pragma endregion

        #pragma region Initilization

        void InitDirectory(const char* path) 
        {
            char buffer[MAX_PATH];
            GetCurrentDirectoryA(MAX_PATH, buffer);
            FullPath = buffer;
            SetCurrentDirectoryA(path);
            // Load files here
            SetCurrentDirectoryA(buffer);
        }

        void InitMod(const char* path)
        {
            CompPlus_Patches::InitPatches();
            CompPlus_HubText::Init();
            CompPlus_ManiaMenu::Init();
            CompPlus_Credits::Init();
            TileCardColors::Init();
            CompPlus_CoreLevelSelect::Init(path);
            CompPlus_Halloween2018::Init();
            CompPlus_Announcers::LoadAnnouncerFX();
            CompPlus_DAGarden::Init();
            CompPlus_DAGarden_Mania::Init();
            CompPlus_DAGarden_Encore::Init();
            CompPlus_DAGarden_Custom::Init();
            CompPlus_DAGarden_Chaotix::Init();
        }

        void InitSettings(const char* path)
        {
            const std::string path_string = path;
            CompPlus_Settings::Settings_FilePath = (path_string + "\\Settings.xml");
            CompPlus_Settings::LoadSettings();
        }

        void InitIZ(const char* path)
        {
            const std::string path_string = path;
            IZAPI::IZInit();
            IZAPI::LoadStagesFile((path_string + "\\Stages.xml").c_str());
            IZAPI::RegisterStageLoadEvent(CompPlus_Core::OnStageLoad);
            IZAPI::RegisterStageUnloadEvent(CompPlus_Core::OnStageUnload);
        }

        #pragma endregion

        #pragma region General Methods

        void OnDraw() 
        {
            CompPlus_Scenes::OnSceneDraw();
            CompPlus_SpotlightC::OnDraw();

            EntityTitleCard* Canvas = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);
            Canvas->DrawOrder = 12;
        }

        void OnStartupInit()
        {
            if (HasStartupInit) return;
            if (StartupStage_Enabled)
            {
                if (StartupStage_UseIZ) CompPlus_Common::LoadLevel_IZ(StartupStage_Infinity);
                else CompPlus_Common::LoadLevel(StartupStage_Normal);
            }
            HasStartupInit = true;
        }

        void OnSceneReset()
        {
            CompPlus_Announcers::ReloadAnnouncerFX();
            CompPlus_CustomScreenStretch::OnFrame();

            if (!(GameState & GameState_NotRunning)) CompPlus_HubWorld::isRestart = true;
            if (!(GameState & GameState_NotRunning)) CompPlus_HubCore::isRestart = true;

            CompPlus_Settings::RefreshSettings();
            CompPlus_ManiaLevelSelect::Reload();
            CompPlus_EncoreLevelSelect::Reload();
            CompPlus_CustomLevelSelect::Reload();
            CompPlus_ChaotixLevelSelect::Reload();
            CompPlus_ExeLevelSelect::Reload();
            CompPlus_Credits::ResetScene();
            CompPlus_Scene_GustPlanet::OnReset();
            CompPlus_Scoring::OnSceneReset();
            CompPlus_TitleScreen::Reload();
            CompPlus_PlayerSkins::Reload();

            CompPlus_Status::SpecialRingsNeedRefresh = true;
            CompPlus_SizeLazer::RefreshChibiSprites = true;
        }

        void OnRunning()
        {
            if ((SonicMania::GameState & SonicMania::GameState_SoftPause)) return;
            CompPlus_Core::OnStartupInit();
            CompPlus_SpotlightC::OnFrame();
            CompPlus_Halloween2018::OnFrame();
            CompPlus_DynCam::OnFrame();
            CompPlus_TailsFlightCancel::OnFrame();
            CompPlus_Settings::OnFrame();
            CompPlus_Scoring::OnFrame();
            CompPlus_Controllers::OnFrame();
            CompPlus_Patches::DynamicPatchesOnFrame();
            CompPlus_SpecialRings::UpdateSpecialRings();
            CompPlus_EntityLoop::OnFrame();
            CompPlus_PlayerSkins::OnFrame();
            CompPlus_Scenes::UpdateScenes();
        }

        void OnFrame_Running()
        {
            CompPlus_Patches::LoadSounds();
            CompPlus_Core::OnRunning();
            CompPlus_CustomScreenStretch::OnFrame();
            CompPlus_DevMenu::UpdateCompPlusDevMenu();
        }

        void OnFrame_NotRunning()
        {
            OnSceneReset();
        }

        void OnFrame_SoftPause()
        {
            OnSceneReset();
        }

        void OnFrame_Always()
        {
            bool isActive = !(SonicMania::GameState & SonicMania::GameState & SonicMania::GameState_NotRunning);
            if (!isActive) return;
            CompPlus_Scenes::OnScenePreload();
            CompPlus_Scenes::SetSceneSpecifics();
        }

        #pragma endregion

        #pragma region Declspec(DllExport) Calls

        __declspec(dllexport) void Init(const char* path)
        {
            InitDirectory(path);
            InitMod(path);
        }

        __declspec(dllexport) void PostInit(const char* path)
        {
            InitIZ(path);
            InitSettings(path);
        }

        void __cdecl OnStageLoad(IZAPI::StageInfo info, IZAPI::StageLoadPhase phase)
        {
            printf("StageLoad: %s\n", info.StageName);
            CurrentStage = info;
            StageRefresh = true;
            IZ_SceneChangeIdleTime = 10;
            CompPlus_ZoneSpecifics::UpdateSpecifics(CurrentStage.SceneKey, CurrentSceneInt);
            OnSceneReset();
        }

        void __cdecl OnStageUnload(IZAPI::StageInfo info, IZAPI::StageLoadPhase phase)
        {
            printf("StageUnload: %s\n", info.StageName);
            CurrentStage = { };
            StageRefresh = true;
            IZ_SceneChangeIdleTime = 10;
            if (!strcmp(info.StageKey, CompPlus_Common::SMCP_Logos1) && (CurrentSceneInt == 1 || CurrentSceneInt == 4)) CompPlus_Common::LoadLevel(123);
            CompPlus_ZoneSpecifics::UpdateSpecifics("", CurrentSceneInt);
            OnSceneReset();
        }

        __declspec(dllexport) void OnScreenUpdate()
        {
            //Code Here Runs when the Game Updates the Screen Position.
        }

        __declspec(dllexport) void OnScreenDrawUpdate()
        {
            OnDraw();
        }

        __declspec(dllexport) void OnFrame()
        {
            bool NotRunning = SonicMania::GameState & SonicMania::GameState_NotRunning;
            bool SoftPaused = SonicMania::GameState & SonicMania::GameState_SoftPause;
            bool GameActive = SonicMania::GameState & SonicMania::GameState_Running;

            int Multiplier = FrameMultiplier;
            for (int i = 0; i < Multiplier; i++)
            {
                OnFrame_Always();
                if (GameActive) OnFrame_Running();
                else if (NotRunning) OnFrame_NotRunning();
                else if (SoftPaused) OnFrame_SoftPause();
            }
        }

        __declspec(dllexport) ModInfo ManiaModInfo = { ModLoaderVer, GameVer };

        #pragma endregion
    }
}

