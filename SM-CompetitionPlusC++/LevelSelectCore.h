#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "SonicMania.h"
#include "ManiaLevelSelect.h"

namespace CompPlus_LevelSelectCore
{

	enum MenuPointState : int
	{
		MenuPointState_Locked = 0,
		MenuPointState_LoadStage = 1,
	};

	struct MenuPoint {

		Vector2 Position;

		EntityUIPicture* Object;

		int LevelID;

		const char* LevelID_IZ;

		bool isIZ = false;

		bool isLocked = false;

		bool isBlank = false;

		int RedirectX = 0;

		int RedirectY = 0;

		const char* CP_Name = " ";

		const char* CP_Author = " ";

		const char* CP_Extra = " ";

		MenuPoint()
		{

		}

		MenuPoint(int slotID, bool _isLocked) : MenuPoint()
		{
			isLocked = _isLocked;
			Object = GetEntity(slotID);
			Position.X = Object->Position.X;
			Position.Y = Object->Position.Y;
		}

		MenuPoint(bool _isBlank, int x, int y) : MenuPoint() 
		{
			isBlank = _isBlank;
			Position.X = 0;
			Position.Y = 0;
			RedirectX = x;
			RedirectY = y;
		}

		MenuPoint(int slotID, const char* levelID_IZ, const char* _CP_Name, const char* _CP_Author, const char* _CP_Extra) : MenuPoint()
		{
			LevelID_IZ = levelID_IZ;
			Object = GetEntity(slotID);
			Position.X = Object->Position.X;
			Position.Y = Object->Position.Y;
			isIZ = true;

			CP_Name = _CP_Name;
			CP_Author = _CP_Author;
			CP_Extra = _CP_Extra;
		}

		MenuPoint(int slotID, const char* levelID_IZ, const char* _CP_Name, const char* _CP_Author, const char* _CP_Extra, bool _isLocked) : MenuPoint()
		{
			LevelID_IZ = levelID_IZ;
			Object = GetEntity(slotID);
			Position.X = Object->Position.X;
			Position.Y = Object->Position.Y;
			isIZ = true;

			CP_Name = _CP_Name;
			CP_Author = _CP_Author;
			CP_Extra = _CP_Extra;

			isLocked = _isLocked;
		}

		MenuPoint(int slotID, short levelID, const char* _CP_Name, const char* _CP_Author, const char* _CP_Extra) : MenuPoint()
		{
			LevelID = levelID;
			Object = GetEntity(slotID);
			Position.X = Object->Position.X;
			Position.Y = Object->Position.Y;

			CP_Name = _CP_Name;
			CP_Author = _CP_Author;
			CP_Extra = _CP_Extra;
		}

		MenuPoint(int slotID, int levelID, const char* _CP_Name, const char* _CP_Author, const char* _CP_Extra) : MenuPoint()
		{
			LevelID = levelID;
			Object = GetEntity(slotID);
			Position.X = Object->Position.X;
			Position.Y = Object->Position.Y;

			CP_Name = _CP_Name;
			CP_Author = _CP_Author;
			CP_Extra = _CP_Extra;
		}

		MenuPointState OnInteract()
		{
			if (isLocked) 
			{
				SonicMania::PlaySoundFXS("Stage/Fail.wav");
				return  MenuPointState_Locked;
			}
			else return MenuPointState_LoadStage;
		}
	};

	extern void UniversalLSelectLoop();
	extern void LevelSelectDelayLoop(int selectorID, MenuPoint levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed);
	extern void LevelSelectDelayLoop(int selectorID, int levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed);
	extern void LevelSelectDelayLoop(int selectorID, const char* levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed);
	extern void LevelSelectDelay(bool isClassic, bool& LevelSelected);
	extern void UpdateLevelSelectSelection(int& MenuPos_X, int& MenuPos_Y, int& MenuMax_X, int& MenuMax_Y, MenuPoint **MenuPoints);
	extern void UpdateLevelSelectScroll(int& MenuPos_X, int& MenuPos_Y, int& LastMenuPos_X, int& LastMenuPos_Y, bool& UpdateMenuScroll, int& UIControlSlot, int& SelectorImage, MenuPoint** MenuPoints);
	extern void ZoneInfoLoop(MenuPoint SelectedZone, int& UIControlSlot, int DescriptionTextASlot, int DescriptionTextBSlot, int DescriptionTextCSlot, int DescriptionTextDSlot, int DescriptionTextESlot, bool UpdateMenuScroll);
	extern void ResetMenuPos(int& MenuPos_X, int& MenuPos_Y, int& LastMenuPos_X, int& LastMenuPos_Y, bool& SwapLevelSelect);
	extern void ResetMenuPos(int& MenuPos_X, int& MenuPos_Y, int SMenuPos_X, int SMenuPos_Y, int& LastMenuPos_X, int& LastMenuPos_Y, bool& SwapLevelSelect);
	extern void UpdateLastPos(int& LastMenuPos_X, int& LastMenuPos_Y, int& MenuPos_X, int& MenuPos_Y);
};

