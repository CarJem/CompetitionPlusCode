#pragma once
namespace CompPlus_Common
{
	extern void LoadLevel_IZ(const char* key);
	extern void LoadLevel(int LevelID);
	extern void PlayMenuMoveSoundFX(bool isClassic);
	extern void PlayMenuAcceptSoundFX(bool isClassic);
	extern void FixSummary();
    extern void LoadLastLevelSelect();
};

