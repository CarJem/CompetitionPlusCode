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
	/*----------------------------------------------*/

	bool LoadedSounds = false;
	void LoadSounds()
	{
		if (!LoadedSounds)
		{
			//Load Sounds on First Run. //Global Scope fine for most things
			LoadSoundFX(SFX_CompPlus1, Scope_Global);
			LoadSoundFX(SFX_CompPlus2, Scope_Global);
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
			DrawRect(0, 0, 16, 16, 0x00000000, 255, SonicMania::Ink_None, true);
			//Your Code runs here - Only running when game is running and not paused.
		}
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
	}
	__declspec(dllexport) ModInfo ManiaModInfo = { ModLoaderVer, GameVer };

}