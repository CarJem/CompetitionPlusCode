// ManiaPlugin.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ManiaModLoader.h"
#include "SonicMania.h"
#include "CompetitionPlus.h"
#include "IZAPI.h"
#include <vector>
#include <ctime>
#include <algorithm>
#include <string>

extern "C"
{
	using namespace SonicMania;

	//SoundFX Defines from SonicMania/Data/Sounds/
	const char* SFX_CompPlus1 = "CompPlus/MenuBleepClassic.wav";
	const char* SFX_CompPlus2 = "CompPlus/MenuAcceptClassic.wav";

	const char* SFX_CompPlus_VO_ATG_1 = "Data/SoundFX/VO_ATG/Go.wav";
	const char* SFX_CompPlus_VO_ATG_2 = "Data/SoundFX/VO_ATG/Goal.wav";
	const char* SFX_CompPlus_VO_ATG_3 = "Data/SoundFX/VO_ATG/ItsADraw.wav";
	const char* SFX_CompPlus_VO_ATG_4 = "Data/SoundFX/VO_ATG/ItsADraw_Set.wav";
	const char* SFX_CompPlus_VO_ATG_5 = "Data/SoundFX/VO_ATG/Knuckles.wav";
	const char* SFX_CompPlus_VO_ATG_6 = "Data/SoundFX/VO_ATG/KnuxWins.wav";
	const char* SFX_CompPlus_VO_ATG_7 = "Data/SoundFX/VO_ATG/Mighty.wav";
	const char* SFX_CompPlus_VO_ATG_8 = "Data/SoundFX/VO_ATG/MightyWins.wav";
	const char* SFX_CompPlus_VO_ATG_9 = "Data/SoundFX/VO_ATG/NewRecordMid.wav";
	const char* SFX_CompPlus_VO_ATG_10 = "Data/SoundFX/VO_ATG/NewRecordTop.wav";
	const char* SFX_CompPlus_VO_ATG_11 = "Data/SoundFX/VO_ATG/One.wav";
	const char* SFX_CompPlus_VO_ATG_12 = "Data/SoundFX/VO_ATG/Player1.wav";
	const char* SFX_CompPlus_VO_ATG_13 = "Data/SoundFX/VO_ATG/Player2.wav";
	const char* SFX_CompPlus_VO_ATG_14 = "Data/SoundFX/VO_ATG/Player3.wav";
	const char* SFX_CompPlus_VO_ATG_15 = "Data/SoundFX/VO_ATG/Player4.wav";
	const char* SFX_CompPlus_VO_ATG_16 = "Data/SoundFX/VO_ATG/Ray.wav";
	const char* SFX_CompPlus_VO_ATG_17 = "Data/SoundFX/VO_ATG/RayWins.wav";
	const char* SFX_CompPlus_VO_ATG_18 = "Data/SoundFX/VO_ATG/Sonic.wav";
	const char* SFX_CompPlus_VO_ATG_19 = "Data/SoundFX/VO_ATG/SonicWins.wav";
	const char* SFX_CompPlus_VO_ATG_20 = "Data/SoundFX/VO_ATG/Tails.wav";
	const char* SFX_CompPlus_VO_ATG_21 = "Data/SoundFX/VO_ATG/TailsWins.wav";
	const char* SFX_CompPlus_VO_ATG_22 = "Data/SoundFX/VO_ATG/TheWinnerIs.wav";
	const char* SFX_CompPlus_VO_ATG_23 = "Data/SoundFX/VO_ATG/Three.wav";
	const char* SFX_CompPlus_VO_ATG_24 = "Data/SoundFX/VO_ATG/Two.wav";
	/*----------------------------------------------*/

	bool LoadedSounds = false;
	void LoadSounds()
	{
		if (!LoadedSounds)
		{
			//Load Sounds on First Run. //Global Scope fine for most things
			LoadSoundFX(SFX_CompPlus1, Scope_Global);
			LoadSoundFX(SFX_CompPlus2, Scope_Global);

			LoadSoundFX(SFX_CompPlus_VO_ATG_1, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_2, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_3, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_4, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_5, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_6, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_7, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_8, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_9, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_10, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_11, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_12, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_13, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_14, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_15, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_16, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_17, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_18, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_19, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_20, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_21, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_22, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_23, Scope_Global);
			LoadSoundFX(SFX_CompPlus_VO_ATG_24, Scope_Global);

			LoadedSounds = true;
		}

	}

	__declspec(dllexport) void OnScreenUpdate()
	{
		//Code Here Runs when the Game Updates the Screen Position.
	}

	__declspec(dllexport) void OnFrame()
	{
		if (GameState & GameState_Running && !(GameState & GameState_SoftPause))
		{
			LoadSounds();
			CompetitionPlus::UpdateMenus();
		}
	}

	void DoMenuOnScreenDraw()
	{
		CompetitionPlus::DrawHook();
	}

	static int OnScreenDrawReturn = baseAddress + 0x7FFE;
	static __declspec(naked) void OnScreenDrawHook()
	{
		__asm
		{
			pushad;
		}
		DoMenuOnScreenDraw();
		__asm
		{
			popad;
			mov edi, ecx
				mov[ebp - 0x10], eax
				jmp OnScreenDrawReturn
		}
	}
	void PatchOnScreenDrawHook()
	{
		WriteData<5>((void*)(baseAddress + 0x7FF9), 0x90);
		WriteJump((void*)(baseAddress + 0x7FF9), OnScreenDrawHook);
	}

	__declspec(dllexport) void PostInit(const char* path)
	{
		const std::string path_cpp = path;
		IZAPI::IZInit();
		IZAPI::LoadStagesFile((path_cpp + "\\Stages.xml").c_str());
		IZAPI::RegisterStageLoadEvent(CompetitionPlus::OnStageLoad);
		IZAPI::RegisterStageUnloadEvent(CompetitionPlus::OnStageUnload);
	}

	__declspec(dllexport) void Init(const char* path)
	{
		char buffer[MAX_PATH];
		GetCurrentDirectoryA(MAX_PATH, buffer);
		SetCurrentDirectoryA(path);
		// Load files here
		SetCurrentDirectoryA(buffer);
		//PatchOnScreenDrawHook();
	}
	__declspec(dllexport) ModInfo ManiaModInfo = { ModLoaderVer, GameVer };

}