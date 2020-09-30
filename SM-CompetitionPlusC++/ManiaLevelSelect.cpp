#include "stdafx.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "SonicMania.h"
#include "CompPlus_Core.h"
#include "CompPlus_Common.h"
#include "LevelSelectCore.h"


namespace CompPlus_ManiaLevelSelect
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

	int MLS_SelectorImage = 174;
	int MLS_UIControlSlot = 56;
	int MLS_MenuPointStartingSlot = 66;
	int MLS_MenuPointLeft = 200;
	int MLS_MenuPointRight = 199;
	int MLS_BG1Slot = 57;
	int MLS_BG2Slot = 58;
	int MLS_BG3Slot = 59;

	int MLS_MenuMax_X = 8;
	int MLS_MenuMax_Y = 4;

	MenuPoint **MLS_MenuPoints;

	void SetManiaLSelectBGColors()
	{
		SetUIBG_BGColor(56, 176, 200);
		SetUIBG_FGLowColor(240, 112, 40);
		SetUIBG_FGHighColor(80, 216, 160);
	}

	void SetupManiaLSelectMenuPoints()
	{
		MLS_MenuPoints = new MenuPoint*[MLS_MenuMax_Y];
		for (int i = 0; i < MLS_MenuMax_Y; i++) MLS_MenuPoints[i] = new MenuPoint[MLS_MenuMax_X];

		int startingSlot = MLS_MenuPointStartingSlot;

		MLS_MenuPoints[0][0] = MenuPoint(true, 0, 1);
		MLS_MenuPoints[0][1] = MenuPoint(startingSlot, (int)SceneExt::Scene_GHZ1, "GREEN HILL ZONE ACT 1", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[0][2] = MenuPoint(startingSlot + 1, (int)SceneExt::Scene_GHZ2, "GREEN HILL ZONE ACT 2", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[0][3] = MenuPoint(startingSlot + 2, (int)SceneExt::Scene_CPZ1, "CHEMICAL PLANT ZONE ACT 1", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[0][4] = MenuPoint(startingSlot + 3, (int)SceneExt::Scene_CPZ2, "CHEMICAL PLANT ZONE ACT 2", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[0][5] = MenuPoint(startingSlot + 4, (int)SceneExt::Scene_SPZ1, "STUDIOPOLIS ZONE ACT 1", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[0][6] = MenuPoint(startingSlot + 5, (int)SceneExt::Scene_SPZ2, "STUDIOPOLIS ZONE ACT 2", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[0][7] = MenuPoint(true, 7, 1);

		MLS_MenuPoints[1][0] = MenuPoint(MLS_MenuPointLeft, "CPCXLS", " ", " ", " ");
		MLS_MenuPoints[1][1] = MenuPoint(startingSlot + 6, (int)SceneExt::Scene_FBZ1, "FLYING BATTERY ZONE ACT 1", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[1][2] = MenuPoint(startingSlot + 7, "SMCP_FBZ2", "FLYING BATTERY ZONE ACT 2", "SEGA / MANIA TEAM (EDITS: CARJEM GENERATIONS)", " ");
		MLS_MenuPoints[1][3] = MenuPoint(startingSlot + 8, (int)SceneExt::Scene_PSZ1, "PRESS GARDEN ZONE ACT 1", "SEGA / MANIA TEAM (EDITS: CARJEM GENERATIONS)", " ");
		MLS_MenuPoints[1][4] = MenuPoint(startingSlot + 9, (int)SceneExt::Scene_PSZ2, "PRESS GARDEN ZONE ACT 2", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[1][5] = MenuPoint(startingSlot + 10, (int)SceneExt::Scene_SSZ1, "STARDUST SPEEDWAY ZONE ACT 1", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[1][6] = MenuPoint(startingSlot + 11, (int)SceneExt::Scene_SSZ2, "STARDUST SPEEDWAY ZONE ACT 2", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[1][7] = MenuPoint(MLS_MenuPointRight, "CPELS", " ", " ", " ");

		MLS_MenuPoints[2][0] = MenuPoint(true, 0, 1);
		MLS_MenuPoints[2][1] = MenuPoint(startingSlot + 12, (int)SceneExt::Scene_HCZ1, "HYRDOCITY ZONE ACT 1", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[2][2] = MenuPoint(startingSlot + 13, (int)SceneExt::Scene_HCZ2, "HYRDOCITY ZONE ACT 2", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[2][3] = MenuPoint(startingSlot + 14, (int)SceneExt::Scene_MSZ1, "MIRAGE SALOON ZONE ACT 1K", "SEGA / MANIA TEAM (EDITS: SONIKKO)", " ");
		MLS_MenuPoints[2][4] = MenuPoint(startingSlot + 15, (int)SceneExt::Scene_MSZ2, "MIRAGE SALOON ZONE ACT 2", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[2][5] = MenuPoint(startingSlot + 16, (int)SceneExt::Scene_OOZ1, "OIL OCEAN ZONE ACT 1", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[2][6] = MenuPoint(startingSlot + 17, (int)SceneExt::Scene_OOZ2, "OIL OCEAN ZONE ACT 2", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[2][7] = MenuPoint(true, 7, 1);

		MLS_MenuPoints[3][0] = MenuPoint(true, 0, 1);
		MLS_MenuPoints[3][1] = MenuPoint(startingSlot + 18, (int)SceneExt::Scene_LRZ1, "LAVA REEF ZONE ACT 1", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[3][2] = MenuPoint(startingSlot + 19, (int)SceneExt::Scene_LRZ2, "LAVA REEF ZONE ACT 2", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[3][3] = MenuPoint(startingSlot + 20, (int)SceneExt::Scene_MMZ1, "METALLIC MADNESS ZONE ACT 1", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[3][4] = MenuPoint(startingSlot + 21, (int)SceneExt::Scene_MMZ2, "METALLIC MADNESS ZONE ACT 2", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[3][5] = MenuPoint(startingSlot + 22, (int)SceneExt::Scene_TMZ1, "TITANIC MONARCH ZONE ACT 1", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[3][6] = MenuPoint(startingSlot + 23, (int)SceneExt::Scene_TMZ2, "TITANIC MONARCH ZONE ACT 2", "SEGA / MANIA TEAM", " ");
		MLS_MenuPoints[3][7] = MenuPoint(true, 7, 1);


		int reset_x = 1;
		int reset_y = 0;

		short start_x = MLS_MenuPoints[reset_y][reset_x].Position.X;
		short start_y = MLS_MenuPoints[reset_y][reset_x].Position.Y;



		ResetMenuPos(MenuPos_X, MenuPos_Y, reset_x, reset_y, LastMenuPos_X, LastMenuPos_Y, SwapLevelSelect);
		InitPosition(start_x, start_y);

		SetManiaLSelectBGColors();

		AreMenuPointsLoaded = true;

		ZoneInfoLoop(MLS_MenuPoints[MenuPos_Y][MenuPos_X], MLS_UIControlSlot, 205, 206, 207, 208, 209, true);
	}

	void SetupManiaSelector()
	{
		Entity& selector = *GetEntityFromSceneSlot<Entity>(MLS_SelectorImage);
		selector.Alpha = 60;


		Entity& bg1 = *GetEntityFromSceneSlot<Entity>(MLS_BG1Slot);
		Entity& bg2 = *GetEntityFromSceneSlot<Entity>(MLS_BG2Slot);
		Entity& bg3 = *GetEntityFromSceneSlot<Entity>(MLS_BG3Slot);

		bg1.InkEffect = Ink_Alpha;
		bg2.InkEffect = Ink_Alpha;
		bg3.InkEffect = Ink_Alpha;

		bg1.Alpha = 200;
		bg2.Alpha = 200;
		bg3.Alpha = 200;
	}

	void CheckForPointRefresh()
	{
		AreMenuPointsLoaded = false;
	}

	void UpdateManiaLSelect()
	{
        CompPlus_Common::SetLastLevelSelect(0);
		UniversalLSelectLoop();
		if (!AreMenuPointsLoaded) SetupManiaLSelectMenuPoints();
		SetupManiaSelector();



		if (!LevelSelected)
		{
			FixSummary();

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
				if (MenuPos_Y < MLS_MenuMax_Y - 1)
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
				if (MenuPos_X < MLS_MenuMax_X - 1)
				{
					LastMenuPos_Y = MenuPos_Y;
					LastMenuPos_X = MenuPos_X;
					MenuPos_X = MenuPos_X++;
					UpdateMenuScroll = true;
					PlayMenuMoveSoundFX(false);
				}
			}

			ZoneInfoLoop(MLS_MenuPoints[MenuPos_Y][MenuPos_X], MLS_UIControlSlot, 205, 206, 207, 208, 209, UpdateMenuScroll);
			UpdateLevelSelectSelection(MenuPos_X, MenuPos_Y, MLS_MenuMax_X, MLS_MenuMax_Y, MLS_MenuPoints);
			UpdateLevelSelectScroll(MenuPos_X, MenuPos_Y, LastMenuPos_X, LastMenuPos_Y, UpdateMenuScroll, MLS_UIControlSlot, MLS_SelectorImage, MLS_MenuPoints);
			ZoneInfoLoop(MLS_MenuPoints[MenuPos_Y][MenuPos_X], MLS_UIControlSlot, 205, 206, 207, 208, 209, UpdateMenuScroll);

			if ((PlayerControllers[0].A.Press || PlayerControllers[0].C.Press || PlayerControllers[0].Start.Press || PlayerControllers[0].Select.Press) && !PlayerControllers[0].B.Press)
			{
				if (MLS_MenuPoints[MenuPos_Y][MenuPos_X].OnInteract() == MenuPointState_LoadStage)
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
			if (!SwapLevelSelect) LevelSelectDelayLoop(MLS_SelectorImage, MLS_MenuPoints[MenuPos_Y][MenuPos_X], SwapLevelSelect, SceneLoadWaitTimer, SceneLoadWaitMax, LevelSelected, LevelSelectedWarpSoundPlayed);
			else LevelSelectDelayLoop(MLS_SelectorImage, "CPHW", SwapLevelSelect, SceneLoadWaitTimer, SwapLevelSelectMax, LevelSelected, LevelSelectedWarpSoundPlayed);
		}
	}

};