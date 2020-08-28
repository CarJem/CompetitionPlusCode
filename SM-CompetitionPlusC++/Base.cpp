// ManiaPlugin.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ManiaModLoader.h"
#include "SonicMania.h"
#include "CompetitionPlus.h"
#include "IZAPI.h"
#include "DevMenu.h"
#include <vector>
#include <ctime>
#include <algorithm>
#include <string>
#include "LevelSelectCore.h"

extern "C"
{
	using namespace SonicMania;

	extern wchar_t Strings[3];
 
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
			CompetitionPlus::InitAnnouncerFX();
			LoadedSounds = true;
		}
	}

	__declspec(dllexport) void OnScreenUpdate()
	{
		//Code Here Runs when the Game Updates the Screen Position.
	}

	__declspec(dllexport) void OnFrame()
	{
		if (GameState & GameState_Running)
		{
            LoadSounds();
			if (!(GameState & GameState_SoftPause)) CompetitionPlus::UpdateMenus();
			UpdateCompPlusDevMenu();
		}
        else if (GameState & GameState_NotRunning)
        {
            CompetitionPlus::OnSceneReset();
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
		CompetitionPlus::InitSettings((path_cpp + "\\Settings.xml").c_str());
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
        CompetitionPlus::InitMod();
	}
	__declspec(dllexport) ModInfo ManiaModInfo = { ModLoaderVer, GameVer };

}