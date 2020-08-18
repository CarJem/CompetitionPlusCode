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

	//const char* TestString = "NULL";
	//const char* SonicInvin = "NULL";
	/*----------------------------------------------*/

	bool LoadedSounds = false;
	void LoadSounds()
	{
		if (!LoadedSounds)
		{
			//int* InvincibleOgg = (int*)(baseAddress + 0x2966);
			//*InvincibleOgg = (int)(&SonicInvin[0]);

			//Load Sounds on First Run. //Global Scope fine for most things
			LoadSoundFX(SFX_CompPlus1, Scope_Global);
			LoadSoundFX(SFX_CompPlus2, Scope_Global);
			LoadedSounds = true;
		}

	}

	__declspec(dllexport) void Testing()
	{
		for (int i = 0; i < 2301; ++i)
		{
			auto entity = GetEntityFromSceneSlot<Entity>(i);

			//TODO : Figure out how to change Pointer Strings
			/*if (entity->ObjectID == 6)
			{
				EntityUIText* ThisObject = (SonicMania::EntityUIText*)entity;
				ThisObject->Text = (char*)SonicInvin;
			}*/

			/*
			if (entity->ObjectID == GetObjectIDFromType(ObjectType_Ring))
			{
				EntityRing* ThisObject = (EntityRing*)entity;
				ThisObject->StateDraw = DrawTest;
			}
			*/

			/*
			if (entity->ObjectID == 6)
			{
				EntityUITextPrivate* ThisObject = (EntityUITextPrivate*)entity;
				ThisObject->StateDraw = DrawTest;
			}
			*/
		}
		//Your Code runs here - Only running when game is running and not paused.
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