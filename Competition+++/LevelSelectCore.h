#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "SonicMania.h"
#include "ManiaLevelSelect.h"

namespace CompPlus_LevelSelectCore
{

	struct MenuPoint {

		Vector2 Position;

		EntityUIPicture* Object;

		int LevelID;

		const char* LevelID_IZ;

		bool isIZ = false;

		bool isBlank = false;

		int RedirectX = 0;

		int RedirectY = 0;

		MenuPoint()
		{

		}

		MenuPoint(bool _isBlank, int x, int y) : MenuPoint() 
		{
			isBlank = _isBlank;
			Position.X = 0;
			Position.Y = 0;
			RedirectX = x;
			RedirectY = y;
		}

		MenuPoint(int slotID, const char* levelID_IZ) : MenuPoint()
		{
			LevelID_IZ = levelID_IZ;
			Object = GetEntity(slotID);
			Position.X = Object->Position.X;
			Position.Y = Object->Position.Y;
			isIZ = true;
		}

		MenuPoint(int slotID, short levelID) : MenuPoint()
		{
			LevelID = levelID;
			Object = GetEntity(slotID);
			Position.X = Object->Position.X;
			Position.Y = Object->Position.Y;
		}

		MenuPoint(int slotID, int levelID) : MenuPoint()
		{
			LevelID = levelID;
			Object = GetEntity(slotID);
			Position.X = Object->Position.X;
			Position.Y = Object->Position.Y;
		}

		void OnInteract()
		{

		}
	};

	extern void LevelSelectDelayLoop(int selectorID, MenuPoint levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed);
	extern void LevelSelectDelayLoop(int selectorID, int levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed);
	extern void LevelSelectDelayLoop(int selectorID, const char* levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed);
	extern void LevelSelectDelay(bool isClassic, bool& LevelSelected);
	extern void UpdateLevelSelectSelection(int& MenuPos_X, int& MenuPos_Y, int& MenuMax_X, int& MenuMax_Y, MenuPoint **MenuPoints);
	extern void UpdateLevelSelectScroll(int& MenuPos_X, int& MenuPos_Y, int& LastMenuPos_X, int& LastMenuPos_Y, bool& UpdateMenuScroll, int& UIControlSlot, int& SelectorImage, MenuPoint** MenuPoints);
	extern void ResetMenuPos(int& MenuPos_X, int& MenuPos_Y, int& LastMenuPos_X, int& LastMenuPos_Y, bool& SwapLevelSelect);
	extern void ResetMenuPos(int& MenuPos_X, int& MenuPos_Y, int SMenuPos_X, int SMenuPos_Y, int& LastMenuPos_X, int& LastMenuPos_Y, bool& SwapLevelSelect);
	extern void UpdateLastPos(int& LastMenuPos_X, int& LastMenuPos_Y, int& MenuPos_X, int& MenuPos_Y);
};

