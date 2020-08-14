#include "stdafx.h"
#include "SettingsMenu.h"
#include "SonicMania.h"
#include "ManiaExt.h"
#include "CompetitionPlus.h"

namespace CompPlus_Settings_GeneralPage
{
	using namespace SonicMania;
	using namespace CompetitionPlus;
	using namespace CompPlus_Settings_Base;

	int ViewPortID = 44;
	int GeneralPageID = 107;
	int SelectorID = 105;

	int DisposalID = 102;

	Entity MainPagePoints[5][1] = { {},{},{},{},{} };

	bool AreMenuPointsLoaded = false;

#pragma region Main Page


	int MainMenuMax_X = 1;
	int MainMenuMax_Y = 5;

	int MainMenuPos_X = 0;
	int MainMenuPos_Y = 0;

	int MainLastMenuPos_X = 0;
	int MainLastMenuPos_Y = 0;



	void SetMainPageInteraction()
	{
		Entity& objectB = *GetEntityFromSceneSlot<Entity>(SelectorID);
		objectB.Position.X = MainPagePoints[MainMenuPos_Y][MainMenuPos_X].Position.X - 10;
		objectB.Position.Y = MainPagePoints[MainMenuPos_Y][MainMenuPos_X].Position.Y;

		/*
		for (int y = 0; y < MenuMax_Y; y++)
		{
			for (int x = 0; x < MenuMax_X; x++)
			{
				if (y != MenuPos_Y && x != MenuPos_X)
				{
					Entity& objectB = *MenuPoints[y][x];
					objectB.Visible = false;
				}
			}
		}

		Entity& objectA = *MenuPoints[MenuPos_Y][MenuPos_X];
		objectA.Visible = true;
		*/
	}

	void GetMainPageAcceptInputResult()
	{
		if (MainMenuPos_Y == 0)
		{
			SetCurrentPage(1);
		}
		else if (MainMenuPos_Y == 1)
		{
			SetCurrentPage(2);
		}
	}

	void GetMainPage()
	{
		if (PlayerControllers[0].Up.Press)
		{
			if (MainMenuPos_Y > 0)
			{
				MainLastMenuPos_Y = MainMenuPos_Y;
				MainLastMenuPos_X = MainMenuPos_X;
				MainMenuPos_Y = MainMenuPos_Y--;
				PlayMenuMoveSoundFX(false);
			}
		}
		if (PlayerControllers[0].Down.Press)
		{
			if (MainMenuPos_Y < MainMenuMax_Y - 1)
			{
				MainLastMenuPos_Y = MainMenuPos_Y;
				MainLastMenuPos_X = MainMenuPos_X;
				MainMenuPos_Y = MainMenuPos_Y++;
				PlayMenuMoveSoundFX(false);
			}
		}
		if (PlayerControllers[0].Left.Press)
		{
			if (MainMenuPos_X > 0)
			{
				MainLastMenuPos_Y = MainMenuPos_Y;
				MainLastMenuPos_X = MainMenuPos_X;
				MainMenuPos_X = MainMenuPos_X--;
				PlayMenuMoveSoundFX(false);
			}
		}
		if (PlayerControllers[0].Right.Press)
		{
			if (MainMenuPos_X < MainMenuMax_X - 1)
			{
				MainLastMenuPos_Y = MainMenuPos_Y;
				MainLastMenuPos_X = MainMenuPos_X;
				MainMenuPos_X = MainMenuPos_X++;
				PlayMenuMoveSoundFX(false);
			}
		}

		if (PlayerControllers[0].A.Press || PlayerControllers[0].C.Press || PlayerControllers[0].Start.Press || PlayerControllers[0].Select.Press)
		{
			GetMainPageAcceptInputResult();
		}

		SetMainPageInteraction();
	}

#pragma endregion


	void InitMenuPoints()
	{
		MainPagePoints[0][0] = *GetEntityFromSceneSlot<Entity>(72);
		MainPagePoints[1][0] = *GetEntityFromSceneSlot<Entity>(47);
		MainPagePoints[2][0] = *GetEntityFromSceneSlot<Entity>(70);
		MainPagePoints[3][0] = *GetEntityFromSceneSlot<Entity>(67);
		MainPagePoints[4][0] = *GetEntityFromSceneSlot<Entity>(69);

		AreMenuPointsLoaded = true;
	}

	void UpdateSettingsMenu()
	{
		FixSummary();
		Entity& viewPort = *GetEntityFromSceneSlot<Entity>(ViewPortID);
		if (!AreMenuPointsLoaded) InitMenuPoints();
		Entity& page = *GetEntityFromSceneSlot<Entity>(GeneralPageID);
		viewPort.Position = page.Position;
		GetMainPage();
	}

	void AllowPointRefresh()
	{
		AreMenuPointsLoaded = false;
	}
};