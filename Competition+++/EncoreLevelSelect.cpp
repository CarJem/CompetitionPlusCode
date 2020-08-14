#include "stdafx.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "SonicMania.h"
#include "CompetitionPlus.h"
#include "Common.h"
#include "LevelSelectCore.h"

namespace CompPlus_EncoreLevelSelect
{
	using namespace SonicMania;
	using namespace CompetitionPlus;
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

	int ELS_SelectorImage = 174;
	int ELS_UIControlSlot = 56;
	int ELS_MenuPointStartingSlot = 66;
	int MLS_MenuPointLeft = 224;
	int MLS_MenuPointRight = 223;
	int ELS_BG1Slot = 57;
	int ELS_BG2Slot = 58;
	int ELS_BG3Slot = 59;

	int ELS_MenuMax_X = 8;
	int ELS_MenuMax_Y = 4;

	MenuPoint** ELS_MenuPoints;

	void SetEncoreLSelectBGColors()
	{
		SetUIBG_BGColor(168, 80, 240);
		SetUIBG_FGLowColor(136, 200, 1);
		SetUIBG_FGHighColor(1, 176, 240);
	}

	void SetupEncoreLSelectMenuPoints()
	{
		ELS_MenuPoints = new MenuPoint *[ELS_MenuMax_Y];
		for (int i = 0; i < ELS_MenuMax_Y; i++) ELS_MenuPoints[i] = new MenuPoint[ELS_MenuMax_X];

		int startingSlot = ELS_MenuPointStartingSlot;

		ELS_MenuPoints[0][0] = MenuPoint(true, 0, 1);
		ELS_MenuPoints[0][1] = MenuPoint(startingSlot, Scene::Scene_GHZ1_e);
		ELS_MenuPoints[0][2] = MenuPoint(startingSlot + 1, Scene::Scene_GHZ2_e);
		ELS_MenuPoints[0][3] = MenuPoint(startingSlot + 2, Scene::Scene_CPZ1_e);
		ELS_MenuPoints[0][4] = MenuPoint(startingSlot + 3, Scene::Scene_CPZ2_e);
		ELS_MenuPoints[0][5] = MenuPoint(startingSlot + 4, Scene::Scene_SPZ1_e);
		ELS_MenuPoints[0][6] = MenuPoint(startingSlot + 5, Scene::Scene_SPZ2_e);
		ELS_MenuPoints[0][7] = MenuPoint(true, 7, 1);

		ELS_MenuPoints[1][0] = MenuPoint(MLS_MenuPointLeft, "CPMLS");
		ELS_MenuPoints[1][1] = MenuPoint(startingSlot + 6, Scene::Scene_FBZ1_e);
		ELS_MenuPoints[1][2] = MenuPoint(startingSlot + 7, Scene::Scene_FBZ2_e);
		ELS_MenuPoints[1][3] = MenuPoint(startingSlot + 8, Scene::Scene_PSZ1_e);
		ELS_MenuPoints[1][4] = MenuPoint(startingSlot + 9, Scene::Scene_PSZ2_e);
		ELS_MenuPoints[1][5] = MenuPoint(startingSlot + 10, Scene::Scene_SSZ1_e);
		ELS_MenuPoints[1][6] = MenuPoint(startingSlot + 11, Scene::Scene_SSZ2_e);
		ELS_MenuPoints[1][7] = MenuPoint(MLS_MenuPointRight, "CPCLS");

		ELS_MenuPoints[2][0] = MenuPoint(true, 0, 1);
		ELS_MenuPoints[2][1] = MenuPoint(startingSlot + 12, Scene::Scene_HCZ1_e);
		ELS_MenuPoints[2][2] = MenuPoint(startingSlot + 13, Scene::Scene_HCZ2_e);
		ELS_MenuPoints[2][3] = MenuPoint(startingSlot + 14, Scene::Scene_MSZ1_e);
		ELS_MenuPoints[2][4] = MenuPoint(startingSlot + 15, Scene::Scene_MSZ2_e);
		ELS_MenuPoints[2][5] = MenuPoint(startingSlot + 16, Scene::Scene_OOZ1_e);
		ELS_MenuPoints[2][6] = MenuPoint(startingSlot + 17, Scene::Scene_OOZ2_e);
		ELS_MenuPoints[2][7] = MenuPoint(true, 7, 1);

		ELS_MenuPoints[3][0] = MenuPoint(true, 0, 1);
		ELS_MenuPoints[3][1] = MenuPoint(startingSlot + 18, Scene::Scene_LRZ1_e);
		ELS_MenuPoints[3][2] = MenuPoint(startingSlot + 19, Scene::Scene_LRZ2_e);
		ELS_MenuPoints[3][3] = MenuPoint(startingSlot + 20, Scene::Scene_MMZ1_e);
		ELS_MenuPoints[3][4] = MenuPoint(startingSlot + 21, Scene::Scene_MMZ2_e);
		ELS_MenuPoints[3][5] = MenuPoint(startingSlot + 22, Scene::Scene_TMZ1_e);
		ELS_MenuPoints[3][6] = MenuPoint(startingSlot + 23, Scene::Scene_TMZ2_e);
		ELS_MenuPoints[3][7] = MenuPoint(true, 7, 1);

		int reset_x = 1;
		int reset_y = 0;

		short start_x = ELS_MenuPoints[reset_y][reset_x].Position.X;
		short start_y = ELS_MenuPoints[reset_y][reset_x].Position.Y;

		ResetMenuPos(MenuPos_X, MenuPos_Y, reset_x, reset_y, LastMenuPos_X, LastMenuPos_Y, SwapLevelSelect);
		InitPosition(start_x, start_y);

		SetEncoreLSelectBGColors();

		AreMenuPointsLoaded = true;
	}

	void UpdateEncoreLSelectScroll()
	{
		if (ELS_MenuPoints[MenuPos_Y][MenuPos_X].isBlank)
		{
			MenuPos_X = ELS_MenuPoints[MenuPos_Y][MenuPos_X].RedirectX;
			MenuPos_Y = ELS_MenuPoints[MenuPos_Y][MenuPos_X].RedirectY;
		}

		short x1 = ELS_MenuPoints[MenuPos_Y][MenuPos_X].Position.X;
		short y1 = ELS_MenuPoints[MenuPos_Y][MenuPos_X].Position.Y;

		short x2 = ELS_MenuPoints[LastMenuPos_Y][LastMenuPos_X].Position.X;
		short y2 = ELS_MenuPoints[LastMenuPos_Y][LastMenuPos_X].Position.Y;

		ScrollToPosition(x1, y1, x2, y2, ELS_UIControlSlot, UpdateMenuScroll);
		ScrollToPosition(x1, y1, x2, y2, ELS_SelectorImage, UpdateMenuScroll);
		UpdateMenuScroll = false;
	}

	void SetupEncoreSelector()
	{
		Entity& selector = *GetEntityFromSceneSlot<Entity>(ELS_SelectorImage);
		selector.Alpha = 60;


		Entity& bg1 = *GetEntityFromSceneSlot<Entity>(ELS_BG1Slot);
		Entity& bg2 = *GetEntityFromSceneSlot<Entity>(ELS_BG2Slot);
		Entity& bg3 = *GetEntityFromSceneSlot<Entity>(ELS_BG3Slot);

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

	void UpdateEncoreLSelect()
	{
		if (!AreMenuPointsLoaded) SetupEncoreLSelectMenuPoints();
		SetupEncoreSelector();

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
				if (MenuPos_Y < ELS_MenuMax_Y - 1)
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
				if (MenuPos_X < ELS_MenuMax_X - 1)
				{
					LastMenuPos_Y = MenuPos_Y;
					LastMenuPos_X = MenuPos_X;
					MenuPos_X = MenuPos_X++;
					UpdateMenuScroll = true;
					PlayMenuMoveSoundFX(false);
				}
			}

			UpdateLevelSelectSelection(MenuPos_X, MenuPos_Y, ELS_MenuMax_X, ELS_MenuMax_Y, ELS_MenuPoints);
			UpdateLevelSelectScroll(MenuPos_X, MenuPos_Y, LastMenuPos_X, LastMenuPos_Y, UpdateMenuScroll, ELS_UIControlSlot, ELS_SelectorImage, ELS_MenuPoints);

			if ((PlayerControllers[0].A.Press || PlayerControllers[0].C.Press || PlayerControllers[0].Start.Press || PlayerControllers[0].Select.Press) && !PlayerControllers[0].B.Press)
			{
				if (!LevelSelected) LevelSelectDelay(false, LevelSelected);
			}
			else if (PlayerControllers[0].B.Press)
			{
				LevelSelected = true;
				SwapLevelSelect = true;
			}
		}


		if (LevelSelected)
		{
			if (!SwapLevelSelect) LevelSelectDelayLoop(ELS_SelectorImage, ELS_MenuPoints[MenuPos_Y][MenuPos_X], SwapLevelSelect, SceneLoadWaitTimer, SceneLoadWaitMax, LevelSelected, LevelSelectedWarpSoundPlayed);
			else LevelSelectDelayLoop(ELS_SelectorImage, "CPHW", SwapLevelSelect, SceneLoadWaitTimer, SwapLevelSelectMax, LevelSelected, LevelSelectedWarpSoundPlayed);
		}
	}

};