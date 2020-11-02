#include "stdafx.h"
#include "CompPlus_Common.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/PointScrolling.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "SonicMania.h"
#include "Base.h"
#include "CompPlus_Settings.h"
#include "CompPlus_Status.h"
#include "CompPlus_Scoring.h"
#include "CompPlus_Scenes/HUB World/HubCore.h"

namespace CompPlus_Common
{

    #pragma region Internal Strings

     const char* Internal_VersionNumber = "5.0";
     const char* Internal_VersionNumberAlt = "5.0.EXE";
     const char* Internal_VersionName = "HALLOWEEN DEMO";
     const char* Internal_VersionNameShort = "DEMO";

    #pragma endregion

    #pragma region SFX Paths

     const char* SFX_MenuBleep = "Global/MenuBleep.wav";
     const char* SFX_MenuAccept = "Global/MenuAccept.wav";
     const char* SFX_SpecialWarp = "Global/SpecialWarp.wav";

     const char* SFX_MenuBleepClassic = "CompPlus/MenuBleepClassic.wav";
     const char* SFX_MenuAcceptClassic = "CompPlus/MenuAcceptClassic.wav";
     const char* SFX_LHPZSecret = "CompPlus/LHPZSecret.wav";
     const char* SFX_GPZButton = "CompPlus/GPZ_Button.wav";

     const char* SFX_EXE_KYS = "SMCP_Executor/KYS.wav";
     const char* SFX_EXE_Laugh = "SMCP_Executor/Laugh.wav";

    #pragma endregion

    #pragma region Animation Paths

     const char* Anim_LSelectIcons_Mania = "SMCP_LSelect/Icons.bin";
     const char* Anim_LSelectIcons_Encore = "SMCP_LSelect/Icons_Encore.bin";
     const char* Anim_LSelectIcons_Custom = "SMCP_LSelect/Icons_Custom.bin";
     const char* Anim_LSelectIcons_Chaotix = "SMCP_LSelect/Icons_Chaotix.bin";
     const char* Anim_LSelectIcons_Exe = "SMCP_LSelect/Icons_Exe.bin";

     const char* Anim_HubCrown = "HUB/Crown.bin";

     const char* Anim_EXE_Sprites = "SMCP_Executor/Explosions.bin";

     const char* Anim_UISmallFont = "UI/SmallFont.bin";
     const char* Anim_LSelectText = "LSelect/Text.bin";
     const char* Anim_LSelectText_Exe = "SMCP_LSelect/Text_EXE.bin";
     const char* Anim_Cred_UISmallFont = "SMCP_Cred/SmallFont.bin";

     const char* Anim_Ring_Normal = "Global/Ring.bin";

     const char* Anim_ItemBox_Original = "Data/Sprites/Global/ItemBox.bin";
     const char* Anim_ItemBox_Stock = "Data/Sprites/SMCP_ItemMods/ItemBox_Normal.bin";
     const char* Anim_ItemBox_JumpUp = "Data/Sprites/SMCP_ItemMods/ItemBox_JumpBoost.bin";
     const char* Anim_ItemBox_Freeze = "Data/Sprites/SMCP_ItemMods/ItemBox_Freeze.bin";
     const char* Anim_ItemBox_Slowdown = "Data/Sprites/SMCP_ItemMods/ItemBox_SpeedDown.bin";

     const char* Anim_DAGarden_Chaotix = "SMCP_DAGarden/Objects_Chaotix.bin";

     const char* Anim_Title_CompPlusLogo = "Title/PlusLogoSMCP.bin";

    #pragma endregion

    #pragma region Palette Paths

     const char* Act_LSelect = "/Data/Palettes/SMCP_LSelect/LSelect.act";
     const char* Act_HUB_Objects = "/Data/Palettes/SMCP_Custom/HUB_Objects.act";
     const char* Act_MBZ_Day = "/Data/Palettes/SMCP_MBZ/MBZ_Day.act";
     const char* Act_MBZ_Sunset = "/Data/Palettes/SMCP_MBZ/MBZ_Sunset2.act";
     const char* Act_MBZ_Night = "/Data/Palettes/SMCP_MBZ/MBZ_Night.act";

    #pragma endregion

    #pragma region Scene IDs

     const char* SMCP_Unused_SettingsWorld = "SMCP_SW";
     const char* SMCP_Credits = "SMCP_CREDITS";

     const char* SMCP_DAGarden = "SMCP_DAGARDEN_1";
     const char* SMCP_DAGarden_Mania = "SMCP_DAGARDEN_2";
     const char* SMCP_DAGarden_Encore = "SMCP_DAGARDEN_3";
     const char* SMCP_DAGarden_Custom = "SMCP_DAGARDEN_4";
     const char* SMCP_DAGarden_Chaotix = "SMCP_DAGARDEN_5";

     const char* SMCP_GHZ1 = "SMCP_GHZ1";
     const char* SMCP_GHZ2 = "SMCP_GHZ2";
     const char* SMCP_CPZ1 = "SMCP_CPZ1";
     const char* SMCP_CPZ2 = "SMCP_CPZ2";
     const char* SMCP_SPZ1 = "SMCP_SPZ1";
     const char* SMCP_SPZ2 = "SMCP_SPZ2";
     const char* SMCP_FBZ1 = "SMCP_FBZ1";
     const char* SMCP_FBZ2 = "SMCP_FBZ2";
     const char* SMCP_PGZ1 = "SMCP_PGZ1";
     const char* SMCP_PGZ2 = "SMCP_PGZ2";
     const char* SMCP_SSZ1 = "SMCP_SSZ1";
     const char* SMCP_SSZ2 = "SMCP_SSZ2";
     const char* SMCP_HCZ1 = "SMCP_HCZ1";
     const char* SMCP_HCZ2 = "SMCP_HCZ2";
     const char* SMCP_MSZ1K = "SMCP_MSZ1K";
     const char* SMCP_MSZ2 = "SMCP_MSZ2";
     const char* SMCP_OOZ1 = "SMCP_OOZ1";
     const char* SMCP_OOZ2 = "SMCP_OOZ2";
     const char* SMCP_LRZ1 = "SMCP_LRZ1";
     const char* SMCP_LRZ2 = "SMCP_LRZ2";
     const char* SMCP_MMZ1 = "SMCP_MMZ1";
     const char* SMCP_MMZ2 = "SMCP_MMZ2";
     const char* SMCP_TMZ1 = "SMCP_TMZ1";
     const char* SMCP_TMZ2 = "SMCP_TMZ2";

     const char* SMCP_GHZ1E = "SMCP_GHZ1E";
     const char* SMCP_GHZ2E = "SMCP_GHZ2E";
     const char* SMCP_CPZ1E = "SMCP_CPZ1E";
     const char* SMCP_CPZ2E = "SMCP_CPZ2E";
     const char* SMCP_SPZ1E = "SMCP_SPZ1E";
     const char* SMCP_SPZ2E = "SMCP_SPZ2E";
     const char* SMCP_FBZ1E = "SMCP_FBZ1E";
     const char* SMCP_FBZ2E = "SMCP_FBZ2E";
     const char* SMCP_PGZ1E = "SMCP_PGZ1E";
     const char* SMCP_PGZ2E = "SMCP_PGZ2E";
     const char* SMCP_SSZ1E = "SMCP_SSZ1E";
     const char* SMCP_SSZ2E = "SMCP_SSZ2E";
     const char* SMCP_HCZ1E = "SMCP_HCZ1E";
     const char* SMCP_HCZ2E = "SMCP_HCZ2E";
     const char* SMCP_MSZ1E = "SMCP_MSZ1E";
     const char* SMCP_MSZ2E = "SMCP_MSZ2E";
     const char* SMCP_OOZ1E = "SMCP_OOZ1E";
     const char* SMCP_OOZ2E = "SMCP_OOZ2E";
     const char* SMCP_LRZ1E = "SMCP_LRZ1E";
     const char* SMCP_LRZ2E = "SMCP_LRZ2E";
     const char* SMCP_MMZ1E = "SMCP_MMZ1E";
     const char* SMCP_MMZ2E = "SMCP_MMZ2E";
     const char* SMCP_TMZ1E = "SMCP_TMZ1E";
     const char* SMCP_TMZ2E = "SMCP_TMZ2E";

     const char* SMCP_GHZ1_EXE = "SMCP_GHZ1_EXE";
     const char* SMCP_GHZ2_EXE = "SMCP_GHZ2_EXE";

     const char* SMCP_AIZ_EXT = "SMCP_AIZ_EX";

     const char* SMCP_CXM_IIZ1 = "SMCP_CXM_IIZ1";
     const char* SMCP_CXM_AAZ1 = "SMCP_CXM_AAZ";
     const char* SMCP_CXM_SSZ1 = "SMCP_CXM_SSZ1";
     const char* SMCP_CXM_BBZ1 = "SMCP_CXM_BBZ";
     const char* SMCP_CXM_MMZ1 = "SMCP_CXM_MMZ1";
     const char* SMCP_CXM_TTZ1 = "SMCP_CXM_TTZ1";

     const char* SMCP_CXM_IIZ1E = "SMCP_CXM_IIZ1E";
     const char* SMCP_CXM_AAZ1E = "SMCP_CXM_AAZE";
     const char* SMCP_CXM_SSZ1E = "SMCP_CXM_SSZ1E";
     const char* SMCP_CXM_BBZ1E = "SMCP_CXM_BBZE";
     const char* SMCP_CXM_MMZ1E = "SMCP_CXM_MMZ1E";
     const char* SMCP_CXM_TTZ1E = "SMCP_CXM_TTZ1E";

     const char* SMCP_TSZ = "SMCP_TSZ";

     const char* SMCP_DHZ = "SMCP_DHZ";
     const char* SMCP_DHZE = "SMCP_DHZE";

     const char* SMCP_SZ = "SMCP_SZ";
     const char* SMCP_SZE = "SMCP_SZE";

     const char* SMCP_GPZ1 = "SMCP_GPZ";
     const char* SMCP_GPZ1E = "SMCP_GPZE";

     const char* SMCP_LHPZ1 = "SMCP_LHPZ1";
     const char* SMCP_LHPZ1E = "SMCP_LHPZ1E";

     const char* SMCP_STHZ1 = "SMCP_STHZ1";
     const char* SMCP_STHZ2 = "SMCP_STHZ2";

     const char* SMCP_MBZ1 = "SMCP_MBZ1";
     const char* SMCP_MBZ2 = "SMCP_MBZ2";

     const char* SMCP_GGZ1 = "SMCP_GGZ1";
     const char* SMCP_GGZ2 = "SMCP_GGZ2";

     const char* SMCP_SPZ1_DX = "SMCP_SPZ1_DX";
     const char* SMCP_SPZ2_DX = "SMCP_SPZ2_DX";
     const char* SMCP_SPZ1_DXE = "SMCP_SPZ1_DXE";
     const char* SMCP_SPZ2_DXE = "SMCP_SPZ2_DXE";

     const char* SMCP_Logos1 = "SMCP_LOGOS";
     const char* SMCP_Logos2 = "SMCP_LOGOS2";
     const char* SMCP_Logos3 = "SMCP_LOGOS3";
     const char* SMCP_Logos4 = "SMCP_LOGOS4";

     const char* HUBWorld = "SMCP_HUB1";
     const char* HUBWorld_EXE = "SMCP_HUB1HWN";
     const char* HUBSettings = "SMCP_HUB3";
     const char* HUBRanking = "SMCP_HUB2";

     const char* LSelect_Mania = "SMCP_M_LS";
     const char* LSelect_Encore = "SMCP_E_LS";
     const char* LSelect_Custom = "SMCP_C_LS";
     const char* LSelect_Chaotix = "SMCP_CX_LS";
     const char* LSelect_Phantom = "SMCP_P_LS";
     const char* LSelect_Exe = "SMCP_EXE_LS";

    #pragma endregion

    #pragma region Music Definitions

    // UNUSED:
    // AIZ - "EAngelIsland2.ogg"
    // SSZ2 METAL - "EMetalSonic.ogg"
    // MSZ1 (ST) - "EMirageSaloon1.ogg"

     const char* Music_GHZ1E = "SMCP_Vape/EGreenHill1.ogg";
     const char* Music_GHZ2E = "SMCP_Vape/EGreenHill2.ogg";
     const char* Music_CPZ1E = "SMCP_Vape/EChemicalPlant1.ogg";
     const char* Music_CPZ2E = "SMCP_Vape/EChemicalPlant2.ogg";
     const char* Music_SPZ1E = "SMCP_Vape/EStudiopolis1.ogg";
     const char* Music_SPZ2E = "SMCP_Vape/EStudiopolis2.ogg";
     const char* Music_FBZ1E = "SMCP_Vape/EFlyingBattery1.ogg";
     const char* Music_FBZ2E = "SMCP_Vape/EFlyingBattery2.ogg";
     const char* Music_PGZ1E = "SMCP_Vape/EPulpSolstice1.ogg";
     const char* Music_PGZ2E = "SMCP_Vape/EPulpSolstice2.ogg";
     const char* Music_SSZ1E = "SMCP_Vape/EStardustSpeedway1.ogg";
     const char* Music_SSZ2E = "SMCP_Vape/EStardustSpeedway2.ogg";
     const char* Music_HCZ1E = "SMCP_Vape/EHydrocity1.ogg";
     const char* Music_HCZ2E = "SMCP_Vape/EHydrocity2.ogg";
     const char* Music_MSZ1E = "SMCP_Vape/EMirageSaloon1K.ogg";
     const char* Music_MSZ2E = "SMCP_Vape/EMirageSaloon2.ogg";
     const char* Music_OOZ1E = "SMCP_Vape/EOilOcean1.ogg";
     const char* Music_OOZ2E = "SMCP_Vape/EOilOcean2.ogg";
     const char* Music_LRZ1E = "SMCP_Vape/ELavaReef1.ogg";
     const char* Music_LRZ2E = "SMCP_Vape/ELavaReef2.ogg";
     const char* Music_MMZ1E = "SMCP_Vape/EMetallicMadness1.ogg";
     const char* Music_MMZ2E = "SMCP_Vape/EMetallicMadness2.ogg";
     const char* Music_TMZ1E = "SMCP_Vape/ETitanicMonarch1.ogg";
     const char* Music_TMZ2E = "SMCP_Vape/ETitanicMonarch2.ogg";

     const char* Music_GHZ1 = "GreenHill1.ogg";
     const char* Music_GHZ2 = "GreenHill2.ogg";
     const char* Music_CPZ1 = "ChemicalPlant1.ogg";
     const char* Music_CPZ2 = "ChemicalPlant2.ogg";
     const char* Music_SPZ1 = "Studiopolis1.ogg";
     const char* Music_SPZ2 = "Studiopolis2.ogg";
     const char* Music_FBZ1 = "FlyingBattery1.ogg";
     const char* Music_FBZ2 = "FlyingBattery2.ogg";
     const char* Music_PGZ1 = "PulpSolstice1.ogg";
     const char* Music_PGZ2 = "PulpSolstice2.ogg";
     const char* Music_SSZ1 = "StardustSpeedway1.ogg";
     const char* Music_SSZ2 = "StardustSpeedway2.ogg";
     const char* Music_HCZ1 = "Hydrocity1.ogg";
     const char* Music_HCZ2 = "Hydrocity2.ogg";
     const char* Music_MSZ1 = "MirageSaloon1K.ogg";
     const char* Music_MSZ2 = "MirageSaloon2.ogg";
     const char* Music_OOZ1 = "OilOcean1.ogg";
     const char* Music_OOZ2 = "OilOcean2.ogg";
     const char* Music_LRZ1 = "LavaReef1.ogg";
     const char* Music_LRZ2 = "LavaReef2.ogg";
     const char* Music_MMZ1 = "MetallicMadness1.ogg";
     const char* Music_MMZ2 = "MetallicMadness2.ogg";
     const char* Music_TMZ1 = "TitanicMonarch1.ogg";
     const char* Music_TMZ2 = "TitanicMonarch2.ogg";

     int GHZ1_TrackLoop = 776160;
     int GHZ2_TrackLoop = 775552;
     int CPZ1_TrackLoop = 680400;
     int CPZ2_TrackLoop = 680400;
     int SPZ1_TrackLoop = 1146600;
     int SPZ2_TrackLoop = 311142;
     int FBZ1_TrackLoop = 158760;
     int FBZ2_TrackLoop = 70560;
     int PGZ1_TrackLoop = 318316;
     int PGZ2_TrackLoop = 226625;
     int SSZ1_TrackLoop = 432894;
     int SSZ2_TrackLoop = 1;
     int HCZ1_TrackLoop = 1;
     int HCZ2_TrackLoop = 329797;
     int MSZ1_TrackLoop = 1007820;
     int MSZ2_TrackLoop = 179390;
     int OOZ1_TrackLoop = 358389;
     int OOZ2_TrackLoop = 176400;
     int LRZ1_TrackLoop = 497329;
     int LRZ2_TrackLoop = 769745;
     int MMZ1_TrackLoop = 470400;
     int MMZ2_TrackLoop = 296056;
     int TMZ1_TrackLoop = 184069;
     int TMZ2_TrackLoop = 384873;

     int GHZ1_TrackLoop_E = 1034880;
     int GHZ2_TrackLoop_E = 1034069;
     int CPZ1_TrackLoop_E = 907200;
     int CPZ2_TrackLoop_E = 907200;
     int SPZ1_TrackLoop_E = 1528800;
     int SPZ2_TrackLoop_E = 414856;
     int FBZ1_TrackLoop_E = 211680;
     int FBZ2_TrackLoop_E = 94080;
     int PGZ1_TrackLoop_E = 424421;
     int PGZ2_TrackLoop_E = 302167;
     int SSZ1_TrackLoop_E = 577192;
     int SSZ2_TrackLoop_E = 1;
     int HCZ1_TrackLoop_E = 1;
     int HCZ2_TrackLoop_E = 439729;
     int MSZ1_TrackLoop_E = 1343760;
     int MSZ2_TrackLoop_E = 239187;
     int OOZ1_TrackLoop_E = 477852;
     int OOZ2_TrackLoop_E = 235200;
     int LRZ1_TrackLoop_E = 663105;
     int LRZ2_TrackLoop_E = 1026327;
     int MMZ1_TrackLoop_E = 627200;
     int MMZ2_TrackLoop_E = 394741;
     int TMZ1_TrackLoop_E = 245425;
     int TMZ2_TrackLoop_E = 513164;

    #pragma endregion

    #pragma region Static Object Paths

     const char* Obj_SpeedShoes_Original = "Data/Objects/Static/36D61A3DE508B500AE0ECF8D33F32943.bin";
     const char* Obj_SpeedShoes_JumpUp = "Data/Objects/CompPlus_SpeedShoesAbility/JumpBoost.bin";
     const char* Obj_SpeedShoes_Freeze = "Data/Objects/CompPlus_SpeedShoesAbility/Freeze.bin";
     const char* Obj_SpeedShoes_Slowdown = "Data/Objects/CompPlus_SpeedShoesAbility/SpeedDown.bin";

    #pragma endregion

    void SpawnFadeOut(int Time, int SpeedIn, int Wait, int SpeedOut, int Color, bool OneWay, bool EventOnly, bool OverHud, bool FadeOutBlack, int DrawOrder) 
    {
        SonicMania::Entity* FXFade = SpawnObject(SonicMania::GetObjectIDFromType(SonicMania::ObjectType_FXFade), 0, SonicMania::Vector2(SonicMania::Player1.Position.X, SonicMania::Player1.Position.Y - 30));
        SonicMania::EntityFXFade* FxFadeR = (SonicMania::EntityFXFade*)FXFade;

        FxFadeR->Time = Time;
        FxFadeR->SpeedIn = SpeedIn;
        FxFadeR->Wait = Wait;
        FxFadeR->SpeedOut = SpeedOut;
        FxFadeR->Color = Color;
        FxFadeR->OneWay = OneWay;
        FxFadeR->EventOnly = EventOnly;
        FxFadeR->Overhud = OverHud;
        FxFadeR->FadeOutBlack = FadeOutBlack;
        FxFadeR->DrawOrder = DrawOrder;
    }

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

    void LoadHUBWorld(bool ForcedOverworld = false)
    {
        if (CompPlus_Scoring::PodeiumSpawnActive && !ForcedOverworld)
        {
            CompPlus_HubCore::ReturnDestination = 2;
            LoadLevel_IZ(HUBRanking);
        }
        else 
        {
            CompPlus_HubCore::ReturnDestination = 0;
            if (CompPlus_Settings::CurrentSeason == CompPlus_Settings::Season_EXE) LoadLevel_IZ(HUBWorld_EXE);
            else LoadLevel_IZ(HUBWorld);
        }

    }

    void LoadHUBWorld()
    {
        LoadHUBWorld(false);
    }

	void PlayMenuMoveSoundFX(bool isClassic)
	{
		if (isClassic) PlaySoundFXS(SFX_MenuBleepClassic);
		else PlaySoundFXS(SFX_MenuBleep);
	}

	void PlayMenuAcceptSoundFX(bool isClassic)
	{
		if (isClassic) PlaySoundFXS(SFX_MenuAcceptClassic);
        else PlaySoundFXS(SFX_MenuAccept);
	}

    void LoadLastLevelSelect() 
    {
        if (CompPlus_Status::CurrentLevelSelect == 1) LoadLevel_IZ(LSelect_Encore);
        else if (CompPlus_Status::CurrentLevelSelect == 2) LoadLevel_IZ(LSelect_Custom);
        else if (CompPlus_Status::CurrentLevelSelect == 3) LoadLevel_IZ(LSelect_Chaotix);
        else LoadLevel_IZ(LSelect_Mania);
    }

    void SetLastLevelSelect(int Value) 
    {
        if (CompPlus_Status::CurrentLevelSelect != Value) CompPlus_Settings::SetCurrentLSelect(Value);
    }
};
