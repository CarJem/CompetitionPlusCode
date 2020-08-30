#include "stdafx.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "SonicMania.h"
#include "CompPlus_Core.h"
#include "CompPlus_Common.h"
#include "LevelSelectCore.h"

namespace CompPlus_ChaotixLevelSelect
{
	using namespace SonicMania;
	using namespace CompPlus_Core;
	using namespace CompPlus_Common;
	using namespace CompPlus_LevelSelectCore;

	bool SwapLevelSelect = false;
	bool LevelSelected = false;
	bool LevelSelectedWarpSoundPlayed = false;

	bool AreMenuPointsLoaded = false;

	int SceneLoadWaitTimer = 0;
	int SceneLoadWaitMax = 100;
	int SwapLevelSelectMax = 100;

	int MenuPos_X = 0;
	int MenuPos_Y = 0;

	int LastMenuPos_X = 0;
	int LastMenuPos_Y = 0;

	bool UpdateMenuScroll = false;

	int CLS_SelectorImage = 174;
	int CLS_UIControlSlot = 56;
	int CLS_MenuPointStartingSlot = 66;
	int CLS_MenuPointLeft = 200;
	int CLS_MenuPointRight = 199;
	int CLS_BG1Slot = 57;
	int CLS_BG2Slot = 58;
	int CLS_BG3Slot = 59;

	int CLS_MenuMax_X = 8;
	int CLS_MenuMax_Y = 4;

	MenuPoint** CLS_MenuPoints;

	void SetChaotixLSelectBGColors()
	{
		SetUIBG_BGColor(102, 71, 95);
		SetUIBG_FGLowColor(95, 38, 47);
		SetUIBG_FGHighColor(24, 151, 31);
	}

	void SetupChaotixLSelectMenuPoints()
	{
		CLS_MenuPoints = new MenuPoint * [CLS_MenuMax_Y];
		for (int i = 0; i < CLS_MenuMax_Y; i++) CLS_MenuPoints[i] = new MenuPoint[CLS_MenuMax_X];

		int startingSlot = CLS_MenuPointStartingSlot;


		CLS_MenuPoints[0][0] = MenuPoint(true, 0, 1);
		CLS_MenuPoints[0][1] = MenuPoint(startingSlot + 0, "CPCXMIIZ1", "ISOLATED ISLAND ZONE ACT 1", "STAR WARRIOR / MCNUGGIE", " ");
		CLS_MenuPoints[0][2] = MenuPoint(startingSlot + 1, "CPCXMAAZ", "AMAZING ARENA ZONE ACT 1", "THE VAGABOND", " ");
		CLS_MenuPoints[0][3] = MenuPoint(startingSlot + 2, "CPCXMSSZ1", "SPEED SLIDER ZONE ACT 1", "THE VAGABOND", " ");
		CLS_MenuPoints[0][4] = MenuPoint(startingSlot + 3, "CPCXMBBZ", "BOTANIC BASE ZONE ACT 1", "THE VAGABOND", " ");
		CLS_MenuPoints[0][5] = MenuPoint(startingSlot + 4, "CPCXMMMZ1", "MARINA MADNESS ZONE ACT 1", "THE VAGABOND", " ");
		CLS_MenuPoints[0][6] = MenuPoint(startingSlot + 5, "CPCXMTTZ1", "TECHNO TOWER ZONE ACT 1", "NEOEXPERIENCES / MUSIC: COBALTBW", " ");
		CLS_MenuPoints[0][7] = MenuPoint(true, 7, 1);

		CLS_MenuPoints[1][0] = MenuPoint(CLS_MenuPointLeft, "CPCLS", " ", " ", " ");
		CLS_MenuPoints[1][1] = MenuPoint(startingSlot + 6, "CPCXMIIZ1E", "ISOLATED ISLAND ZONE ACT 1 (ENCORE)", "STAR WARRIOR / MCNUGGIE", " ", true);
		CLS_MenuPoints[1][2] = MenuPoint(startingSlot + 7, "CPCXMAAZE", "AMAZING ARENA ZONE ACT 1 (ENCORE)", "THE VAGABOND", " ");
		CLS_MenuPoints[1][3] = MenuPoint(startingSlot + 8, "CPCXMSSZ1E", "SPEED SLIDER ZONE ACT 1 (ENCORE)", "THE VAGABOND", " ");
		CLS_MenuPoints[1][4] = MenuPoint(startingSlot + 9, "CPCXMBBZE", "BOTANIC BASE ZONE ACT 1 (ENCORE)", "THE VAGABOND", " ");
		CLS_MenuPoints[1][5] = MenuPoint(startingSlot + 10, "CPCXMMMZ1E", "MARINA MADNESS ZONE ACT 1 (ENCORE)", "THE VAGABOND", " ");
		CLS_MenuPoints[1][6] = MenuPoint(startingSlot + 11, "CPCXMTTZ1E", "TECHNO TOWER ZONE ACT 1 (ENCORE)", "NEOEXPERIENCES / MUSIC: COBALTBW", " ");
		CLS_MenuPoints[1][7] = MenuPoint(CLS_MenuPointRight, "CPMLS", " ", " ", " ");

		CLS_MenuPoints[2][0] = MenuPoint(true, 0, 1);
		CLS_MenuPoints[2][1] = MenuPoint(startingSlot + 12, true);
		CLS_MenuPoints[2][2] = MenuPoint(startingSlot + 13, true);
		CLS_MenuPoints[2][3] = MenuPoint(startingSlot + 14, true);
		CLS_MenuPoints[2][4] = MenuPoint(startingSlot + 15, true);
		CLS_MenuPoints[2][5] = MenuPoint(startingSlot + 16, true);
		CLS_MenuPoints[2][6] = MenuPoint(startingSlot + 17, true);
		CLS_MenuPoints[2][7] = MenuPoint(true, 7, 1);

		CLS_MenuPoints[3][0] = MenuPoint(true, 0, 1);
		CLS_MenuPoints[3][1] = MenuPoint(startingSlot + 18, true);
		CLS_MenuPoints[3][2] = MenuPoint(startingSlot + 19, true);
		CLS_MenuPoints[3][3] = MenuPoint(startingSlot + 20, true);
		CLS_MenuPoints[3][4] = MenuPoint(startingSlot + 21, true);
		CLS_MenuPoints[3][5] = MenuPoint(startingSlot + 22, true);
		CLS_MenuPoints[3][6] = MenuPoint(startingSlot + 23, true);
		CLS_MenuPoints[3][7] = MenuPoint(true, 7, 1);

		int reset_x = 1;
		int reset_y = 0;

		short start_x = CLS_MenuPoints[reset_y][reset_x].Position.X;
		short start_y = CLS_MenuPoints[reset_y][reset_x].Position.Y;

		ResetMenuPos(MenuPos_X, MenuPos_Y, reset_x, reset_y, LastMenuPos_X, LastMenuPos_Y, SwapLevelSelect);
		InitPosition(start_x, start_y);

		SetChaotixLSelectBGColors();

		AreMenuPointsLoaded = true;

		ZoneInfoLoop(CLS_MenuPoints[MenuPos_Y][MenuPos_X], CLS_UIControlSlot, 231, 232, 233, 234, 235, true);
	}

	void SetupChaotixSelector()
	{
		Entity& selector = *GetEntityFromSceneSlot<Entity>(CLS_SelectorImage);
		selector.Alpha = 60;


		Entity& bg1 = *GetEntityFromSceneSlot<Entity>(CLS_BG1Slot);
		Entity& bg2 = *GetEntityFromSceneSlot<Entity>(CLS_BG2Slot);
		Entity& bg3 = *GetEntityFromSceneSlot<Entity>(CLS_BG3Slot);

		bg1.InkEffect = Ink_Alpha;
		bg2.InkEffect = Ink_Alpha;
		bg3.InkEffect = Ink_Alpha;

		bg1.Alpha = 120;
		bg2.Alpha = 120;
		bg3.Alpha = 120;
	}

	void CheckForPointRefresh() 
	{
		AreMenuPointsLoaded = false;
	}

	void UpdateChaotixLSelect()
	{
        CompPlus_Common::SetLastLevelSelect(3);
		UniversalLSelectLoop();
		if (!AreMenuPointsLoaded) SetupChaotixLSelectMenuPoints();
		SetupChaotixSelector();

		FixSummary();

		if (!LevelSelected)
		{

			if (PlayerControllers[0].Up.Press)
			{
				if (MenuPos_Y > 0)
				{
					LastMenuPos_Y = MenuPos_Y;
					LastMenuPos_X = MenuPos_X;
					MenuPos_Y = MenuPos_Y--;
					UpdateMenuScroll = true;
					PlayMenuMoveSoundFX(false);
				}
			}
			if (PlayerControllers[0].Down.Press)
			{
				if (MenuPos_Y < CLS_MenuMax_Y - 1)
				{
					LastMenuPos_Y = MenuPos_Y;
					LastMenuPos_X = MenuPos_X;
					MenuPos_Y = MenuPos_Y++;
					UpdateMenuScroll = true;
					PlayMenuMoveSoundFX(false);
				}
			}
			if (PlayerControllers[0].Left.Press)
			{
				if (MenuPos_X > 0)
				{
					LastMenuPos_Y = MenuPos_Y;
					LastMenuPos_X = MenuPos_X;
					MenuPos_X = MenuPos_X--;
					UpdateMenuScroll = true;
					PlayMenuMoveSoundFX(false);
				}
			}
			if (PlayerControllers[0].Right.Press)
			{
				if (MenuPos_X < CLS_MenuMax_X - 1)
				{
					LastMenuPos_Y = MenuPos_Y;
					LastMenuPos_X = MenuPos_X;
					MenuPos_X = MenuPos_X++;
					UpdateMenuScroll = true;
					PlayMenuMoveSoundFX(false);
				}
			}

			ZoneInfoLoop(CLS_MenuPoints[MenuPos_Y][MenuPos_X], CLS_UIControlSlot, 231, 232, 233, 234, 235, UpdateMenuScroll);
			UpdateLevelSelectSelection(MenuPos_X, MenuPos_Y, CLS_MenuMax_X, CLS_MenuMax_Y, CLS_MenuPoints);
			UpdateLevelSelectScroll(MenuPos_X, MenuPos_Y, LastMenuPos_X, LastMenuPos_Y, UpdateMenuScroll, CLS_UIControlSlot, CLS_SelectorImage, CLS_MenuPoints);
			ZoneInfoLoop(CLS_MenuPoints[MenuPos_Y][MenuPos_X], CLS_UIControlSlot, 231, 232, 233, 234, 235, UpdateMenuScroll);

			if ((PlayerControllers[0].A.Press || PlayerControllers[0].C.Press || PlayerControllers[0].Start.Press || PlayerControllers[0].Select.Press) && !PlayerControllers[0].B.Press)
			{
				if (CLS_MenuPoints[MenuPos_Y][MenuPos_X].OnInteract() == MenuPointState_LoadStage)
				{
					if (!LevelSelected) LevelSelectDelay(true, LevelSelected);
				}
			}
			else if (PlayerControllers[0].B.Press)
			{
				LevelSelected = true;
				SwapLevelSelect = true;
			}
		}


		if (LevelSelected)
		{
			if (!SwapLevelSelect) LevelSelectDelayLoop(CLS_SelectorImage, CLS_MenuPoints[MenuPos_Y][MenuPos_X], SwapLevelSelect, SceneLoadWaitTimer, SceneLoadWaitMax, LevelSelected, LevelSelectedWarpSoundPlayed);
			else LevelSelectDelayLoop(CLS_SelectorImage, "CPHW", SwapLevelSelect, SceneLoadWaitTimer, SwapLevelSelectMax, LevelSelected, LevelSelectedWarpSoundPlayed);
		}
	}

};