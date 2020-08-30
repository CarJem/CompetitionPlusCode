#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "ManiaExt.h"
#include "SonicMania.h"
#include "IZAPI.h"

namespace CompPlus_Core
{
    enum SceneExt : short
    {
        Scene_NONE = -1,
        // Presentation 
        Scene_Logo,
        Scene_Title,
        Scene_MainMenu,
        Scene_ThanksForPlaying,
        Scene_LevelSelect,
        Scene_Credits,
        Scene_Continue,
        Scene_Summary,
        Scene_Summary_e,
        // Mania Mode
        Scene_GHZ1,
        Scene_GHZ2,
        Scene_CPZ1,
        Scene_CPZ2,
        Scene_SPZ1,
        Scene_SPZ2,
        Scene_FBZ1,
        Scene_FBZ2,
        Scene_PSZ1,
        Scene_PSZ2,
        Scene_SSZ1,
        Scene_SSZ2,
        Scene_SSZ2M,
        Scene_HCZ1,
        Scene_HCZ2,
        Scene_MSZ1,
        Scene_MSZ2,
        Scene_OOZ1,
        Scene_OOZ2,
        Scene_LRZ1,
        Scene_LRZ2,
        Scene_LRZ3,
        Scene_MMZ1,
        Scene_MMZ2,
        Scene_TMZ1,
        Scene_TMZ2,
        Scene_TMZ3,
        Scene_ERZ,
        // Encore Mode
        Scene_GHZ1_e,
        Scene_GHZ2_e,
        Scene_CPZ1_e,
        Scene_CPZ2_e,
        Scene_SPZ1_e,
        Scene_SPZ2_e,
        Scene_FBZ1_e,
        Scene_FBZ2_e,
        Scene_PSZ1_e,
        Scene_PSZ2_e,
        Scene_SSZ1_e,
        Scene_SSZ2_e,
        Scene_SSZ2M_e,
        Scene_HCZ1_e,
        Scene_HCZ2_e,
        Scene_MSZ1_e,
        Scene_MSZ2_e,
        Scene_OOZ1_e,
        Scene_OOZ2_e,
        Scene_LRZ1_e,
        Scene_LRZ2_e,
        Scene_LRZ3_e,
        Scene_MMZ1_e,
        Scene_MMZ2_e,
        Scene_TMZ1_e,
        Scene_TMZ2_e,
        Scene_TMZ3_e,
        // Special Stage
        Scene_SpecialStage1,
        Scene_SpecialStage2,
        Scene_SpecialStage3,
        Scene_SpecialStage4,
        Scene_SpecialStage5,
        Scene_SpecialStage6,
        Scene_SpecialStage7,
        Scene_SpecialStage1_e,
        Scene_SpecialStage2_e,
        Scene_SpecialStage3_e,
        Scene_SpecialStage4_e,
        Scene_SpecialStage5_e,
        Scene_SpecialStage6_e,
        Scene_SpecialStage7_e,
        // Blue Sphere (+0 - +31)
        Scene_BlueSphere,
        Scene_BlueSphere_Random = Scene_BlueSphere + 32,
        Scene_BlueSphere_Random2,
        // Pinball
        Scene_Pinball,
        // Extras
        Scene_PuyoPuyo,
        Scene_DAGarden,
        Scene_DAGarden_e,
        // Cutscene
        Scene_Cutscene_AngelIsland,
        Scene_Cutscene_AngelIsland_e,
        Scene_Cutscene_GreenHillZone,
        Scene_Cutscene_GreenHillZone2,
        Scene_Cutscene_MirageSaloonKnucklesIntro,
        Scene_Cutscene_StardustSpeedwayTimeTravel,
        Scene_TryAgain,
        Scene_Cutscene_MirageSaloonEnd_e,
        Scene_TryAgain_e,
        // Video
        Scene_BadEnd_Sonic,
        Scene_BadEnd_Sonic2,
        Scene_BadEnd_Tails,
        Scene_BadEnd_Knux,
        Scene_BadEnd_Mighty,
        Scene_BadEnd_Ray,
        Scene_GoodEnd,
        Scene_TrueEnd,

        Scene_CompPlus_ManiaLSelect = 133,
        Scene_CompPlus_EncoreLSelect = 134,
        Scene_CompPlus_CustomLSelect = 135,
        Scene_CompPlus_PhantomLSelect = 136,
        Scene_CompPlus_SettingsMenu = 137,
        Scene_CompPlus_HubWorld = 138
    };

	extern bool StageRefresh;
	extern int IdleTime;

	//extern IZAPI::StageInfo GetCurrentStage();
	//typedef void(__cdecl* IZChangeStage_Type)(const char*);
	//
	extern void IZChangeStage(const char* key);

	extern void UpdateMenus();
	extern void DrawHook();

    extern void OnSceneReset();

	extern void OnStageLoad(IZAPI::StageInfo info, IZAPI::StageLoadPhase phase);
	extern void OnStageUnload(IZAPI::StageInfo info, IZAPI::StageLoadPhase phase);

    extern void InitMod();
    extern void InitAnnouncerFX();
    extern void InitSettings(const char* path);
};

