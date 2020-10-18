#pragma once
#include <String>
namespace CompPlus_Common
{
    extern const char* SFX_MenuBleep;
    extern const char* SFX_MenuAccept;
    extern const char* SFX_SpecialWarp;

    extern const char* SFX_MenuBleepClassic;
    extern const char* SFX_MenuAcceptClassic;
    extern const char* SFX_LHPZSecret;
    extern const char* SFX_GPZButton;

    extern const char* Act_LSelect;

    extern const char* Anim_LSelectIcons_Mania;
    extern const char* Anim_LSelectIcons_Encore;
    extern const char* Anim_LSelectIcons_Custom;
    extern const char* Anim_LSelectIcons_Chaotix;
    extern const char* Anim_LSelectIcons_Exe;

    extern const char* Anim_HubCrown;

    extern const char* Anim_UISmallFont;
    extern const char* Anim_LSelectText;
    extern const char* Anim_LSelectText_Exe;

    extern const char* SMCP_Unused_SettingsWorld;
    extern const char* SMCP_Credits;


    extern const char* SceneID_MMZ;

    extern const char* SMCP_GHZ1;
    extern const char* SMCP_GHZ2;
    extern const char* SMCP_CPZ1;
    extern const char* SMCP_CPZ2;
    extern const char* SMCP_SPZ1;
    extern const char* SMCP_SPZ2;
    extern const char* SMCP_FBZ1;
    extern const char* SMCP_FBZ2;
    extern const char* SMCP_PGZ1;
    extern const char* SMCP_PGZ2;
    extern const char* SMCP_SSZ1;
    extern const char* SMCP_SSZ2;
    extern const char* SMCP_HCZ1;
    extern const char* SMCP_HCZ2;
    extern const char* SMCP_MSZ1K;
    extern const char* SMCP_MSZ2;
    extern const char* SMCP_OOZ1;
    extern const char* SMCP_OOZ2;
    extern const char* SMCP_LRZ1;
    extern const char* SMCP_LRZ2;
    extern const char* SMCP_MMZ1;
    extern const char* SMCP_MMZ2;
    extern const char* SMCP_TMZ1;
    extern const char* SMCP_TMZ2;

    extern const char* SMCP_GHZ1E;
    extern const char* SMCP_GHZ2E;
    extern const char* SMCP_CPZ1E;
    extern const char* SMCP_CPZ2E;
    extern const char* SMCP_SPZ1E;
    extern const char* SMCP_SPZ2E;
    extern const char* SMCP_FBZ1E;
    extern const char* SMCP_FBZ2E;
    extern const char* SMCP_PGZ1E;
    extern const char* SMCP_PGZ2E;
    extern const char* SMCP_SSZ1E;
    extern const char* SMCP_SSZ2E;
    extern const char* SMCP_HCZ1E;
    extern const char* SMCP_HCZ2E;
    extern const char* SMCP_MSZ1E;
    extern const char* SMCP_MSZ2E;
    extern const char* SMCP_OOZ1E;
    extern const char* SMCP_OOZ2E;
    extern const char* SMCP_LRZ1E;
    extern const char* SMCP_LRZ2E;
    extern const char* SMCP_MMZ1E;
    extern const char* SMCP_MMZ2E;
    extern const char* SMCP_TMZ1E;
    extern const char* SMCP_TMZ2E;

    extern const char* SMCP_AIZ_EXT;

    extern const char* SMCP_CXM_IIZ1;
    extern const char* SMCP_CXM_AAZ1;
    extern const char* SMCP_CXM_SSZ1;
    extern const char* SMCP_CXM_BBZ1;
    extern const char* SMCP_CXM_MMZ1;
    extern const char* SMCP_CXM_TTZ1;

    extern const char* SMCP_CXM_IIZ1E;
    extern const char* SMCP_CXM_AAZ1E;
    extern const char* SMCP_CXM_SSZ1E;
    extern const char* SMCP_CXM_BBZ1E;
    extern const char* SMCP_CXM_MMZ1E;
    extern const char* SMCP_CXM_TTZ1E;

    extern const char* SMCP_TSZ;

    extern const char* SMCP_DHZ;
    extern const char* SMCP_DHZE;

    extern const char* SMCP_SZ;
    extern const char* SMCP_SZE;

    extern const char* SMCP_GPZ1;
    extern const char* SMCP_GPZ1E;

    extern const char* SMCP_LHPZ1;
    extern const char* SMCP_LHPZ1E;

    extern const char* SMCP_Logos1;
    extern const char* SMCP_Logos2;
    extern const char* SMCP_Logos3;
    extern const char* SMCP_Logos4;

    extern const char* HUBWorld;
    extern const char* HUBWorld_EXE;
    extern const char* HUBSettings;
    extern const char* HUBRanking;

    extern const char* LSelect_Mania;
    extern const char* LSelect_Encore;
    extern const char* LSelect_Custom;
    extern const char* LSelect_Chaotix;
    extern const char* LSelect_Phantom;
    extern const char* LSelect_Exe;

	extern void LoadLevel_IZ(const char* key);
	extern void LoadLevel(int LevelID);
    extern void LoadHUBWorld(bool ForcedOverworld);
    extern void LoadHUBWorld();
	extern void PlayMenuMoveSoundFX(bool isClassic);
	extern void PlayMenuAcceptSoundFX(bool isClassic);
    extern void LoadLastLevelSelect();
    extern void SetLastLevelSelect(int Value);
};

