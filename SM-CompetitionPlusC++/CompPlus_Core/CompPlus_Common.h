#pragma once
namespace CompPlus_Common
{

	extern void LoadLevel_IZ(const char* key);
	extern void LoadLevel(int LevelID);
    extern void LoadHUBWorld(bool ForcedOverworld);
    extern void LoadHUBWorld();
	extern void PlayMenuMoveSoundFX(bool isClassic);
	extern void PlayMenuAcceptSoundFX(bool isClassic);
    extern void LoadLastLevelSelect();
    extern void SetLastLevelSelect(int Value);
};

