#include "stdafx.h"
#include "SettingsMenu.h"
#include "SonicMania.h"
#include "ManiaExt.h"
#include "CompetitionPlus.h"

namespace CompPlus_Settings_CompetitionPage
{
	using namespace SonicMania;
	using namespace CompetitionPlus;
	using namespace CompPlus_Settings_Base;

	bool InfiniteRounds = false;
	bool InfiniteLives = false;
	bool TimeLimit = true;

	int ViewPortID = 44;
	int CompetitionPageID = 68;
	int SelectorID = 105;

	int DisposalID = 102;

	Entity CompetitionPagePoints[4][1] = { {},{},{},{} };

	bool AreMenuPointsLoaded = false;

	int InfiniteRoundsSpawnID = 103;
	int InfiniteRoundsNoID = 109;
	int InfiniteRoundsYesID = 110;

	int TimeLimitSpawnID = 106;
	int TimeLimitNoID = 111;
	int TimeLimitYesID = 112;

	int InfiniteLiveSpawnID = 108;
	int InfiniteLiveNoID = 113;
	int InfiniteLiveYesID = 114;

	int CompetitionMenuMax_X = 1;
	int CompetitionMenuMax_Y = 4;

	int CompetitionMenuPos_X = 0;
	int CompetitionMenuPos_Y = 0;

	int CompetitionLastMenuPos_X = 0;
	int CompetitionLastMenuPos_Y = 0;


	// Gameplay Settings

	void SetCompetitionPageInfiniteRoundsSetting(bool state) 
	{
		InfiniteRounds = state;
		if (!InfiniteRounds)
		{
			Entity& unselectedItem = *GetEntityFromSceneSlot<Entity>(InfiniteRoundsNoID);
			Entity& selectedItem = *GetEntityFromSceneSlot<Entity>(InfiniteRoundsYesID);
			Entity& spawnItem = *GetEntityFromSceneSlot<Entity>(InfiniteRoundsSpawnID);
			Entity& disposalItem = *GetEntityFromSceneSlot<Entity>(DisposalID);
			selectedItem.Position = spawnItem.Position;
			unselectedItem.Position = disposalItem.Position;
		}
		else 
		{
			Entity& unselectedItem = *GetEntityFromSceneSlot<Entity>(InfiniteRoundsYesID);
			Entity& selectedItem = *GetEntityFromSceneSlot<Entity>(InfiniteRoundsNoID);
			Entity& spawnItem = *GetEntityFromSceneSlot<Entity>(InfiniteRoundsSpawnID);
			Entity& disposalItem = *GetEntityFromSceneSlot<Entity>(DisposalID);
			selectedItem.Position = spawnItem.Position;
			unselectedItem.Position = disposalItem.Position;
		}
	}

	void SetCompetitionPageInfiniteLivesSetting(bool state)
	{
		InfiniteLives = state;
		if (!InfiniteLives)
		{
			Entity& unselectedItem = *GetEntityFromSceneSlot<Entity>(InfiniteLiveNoID);
			Entity& selectedItem = *GetEntityFromSceneSlot<Entity>(InfiniteLiveYesID);
			Entity& spawnItem = *GetEntityFromSceneSlot<Entity>(InfiniteLiveSpawnID);
			Entity& disposalItem = *GetEntityFromSceneSlot<Entity>(DisposalID);
			selectedItem.Position = spawnItem.Position;
			unselectedItem.Position = disposalItem.Position;
		}
		else
		{
			Entity& unselectedItem = *GetEntityFromSceneSlot<Entity>(InfiniteLiveYesID);
			Entity& selectedItem = *GetEntityFromSceneSlot<Entity>(InfiniteLiveNoID);
			Entity& spawnItem = *GetEntityFromSceneSlot<Entity>(InfiniteLiveSpawnID);
			Entity& disposalItem = *GetEntityFromSceneSlot<Entity>(DisposalID);
			selectedItem.Position = spawnItem.Position;
			unselectedItem.Position = disposalItem.Position;
		}
	}

	void SetCompetitionPageTimeLimitSetting(bool state)
	{
		TimeLimit = state;
		if (!TimeLimit)
		{
			Entity& unselectedItem = *GetEntityFromSceneSlot<Entity>(TimeLimitNoID);
			Entity& selectedItem = *GetEntityFromSceneSlot<Entity>(TimeLimitYesID);
			Entity& spawnItem = *GetEntityFromSceneSlot<Entity>(TimeLimitSpawnID);
			Entity& disposalItem = *GetEntityFromSceneSlot<Entity>(DisposalID);
			selectedItem.Position = spawnItem.Position;
			unselectedItem.Position = disposalItem.Position;
		}
		else
		{
			Entity& unselectedItem = *GetEntityFromSceneSlot<Entity>(TimeLimitYesID);
			Entity& selectedItem = *GetEntityFromSceneSlot<Entity>(TimeLimitNoID);
			Entity& spawnItem = *GetEntityFromSceneSlot<Entity>(TimeLimitSpawnID);
			Entity& disposalItem = *GetEntityFromSceneSlot<Entity>(DisposalID);
			selectedItem.Position = spawnItem.Position;
			unselectedItem.Position = disposalItem.Position;
		}
	}

	void UpdateCompetitionPageEntries()
	{
		SetCompetitionPageInfiniteRoundsSetting(InfiniteRounds);
		SetCompetitionPageInfiniteLivesSetting(InfiniteLives);
		SetCompetitionPageTimeLimitSetting(TimeLimit);
	}





	void SetCompetitionPageInteraction()
	{
		Entity& objectB = *GetEntityFromSceneSlot<Entity>(SelectorID);
		objectB.Position.X = CompetitionPagePoints[CompetitionMenuPos_Y][CompetitionMenuPos_X].Position.X - 10;
		objectB.Position.Y = CompetitionPagePoints[CompetitionMenuPos_Y][CompetitionMenuPos_X].Position.Y;

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

	void GetCompetitionPageAcceptInputResult() 
	{
		if (CompetitionMenuPos_Y == 3)
		{
			SetCurrentPage(0);
		}
	}

	void GetCompetitionPageCancelInputResult()
	{
		SetCurrentPage(0);
	}

	void GetCompetitionPageLeftInputResult()
	{
		if (CompetitionMenuPos_Y == 0)
		{
			SetCompetitionPageInfiniteRoundsSetting(!InfiniteRounds);
		}
		else if (CompetitionMenuPos_Y == 1)
		{
			SetCompetitionPageTimeLimitSetting(!TimeLimit);
		}
		else if (CompetitionMenuPos_Y == 2)
		{
			SetCompetitionPageInfiniteLivesSetting(!InfiniteLives);
		}
		else 
		{
			if (CompetitionMenuPos_X > 0)
			{
				CompetitionLastMenuPos_Y = CompetitionMenuPos_Y;
				CompetitionLastMenuPos_X = CompetitionMenuPos_X;
				CompetitionMenuPos_X = CompetitionMenuPos_X--;
				PlayMenuMoveSoundFX(false);
			}
		}

	}

	void GetCompetitionPageRightInputResult()
	{
		if (CompetitionMenuPos_Y == 0)
		{
			SetCompetitionPageInfiniteRoundsSetting(!InfiniteRounds);
		}
		else if (CompetitionMenuPos_Y == 1)
		{
			SetCompetitionPageTimeLimitSetting(!TimeLimit);
		}
		else if (CompetitionMenuPos_Y == 2)
		{
			SetCompetitionPageInfiniteLivesSetting(!InfiniteLives);
		}
		else 
		{
			if (CompetitionMenuPos_X < CompetitionMenuMax_X - 1)
			{
				CompetitionLastMenuPos_Y = CompetitionMenuPos_Y;
				CompetitionLastMenuPos_X = CompetitionMenuPos_X;
				CompetitionMenuPos_X = CompetitionMenuPos_X++;
				PlayMenuMoveSoundFX(false);
			}
		}

	}

	void GetCompetitionPageUpInputResult()
	{
		if (CompetitionMenuPos_Y > 0)
		{
			CompetitionLastMenuPos_Y = CompetitionMenuPos_Y;
			CompetitionLastMenuPos_X = CompetitionMenuPos_X;
			CompetitionMenuPos_Y = CompetitionMenuPos_Y--;
			PlayMenuMoveSoundFX(false);
		}
	}

	void GetCompetitionPageDownInputResult()
	{
		if (CompetitionMenuPos_Y < CompetitionMenuMax_Y - 1)
		{
			CompetitionLastMenuPos_Y = CompetitionMenuPos_Y;
			CompetitionLastMenuPos_X = CompetitionMenuPos_X;
			CompetitionMenuPos_Y = CompetitionMenuPos_Y++;
			PlayMenuMoveSoundFX(false);
		}
	}

	void GetCompetitionPage()
	{
		UpdateCompetitionPageEntries();

		if (PlayerControllers[0].Up.Press)
		{
			GetCompetitionPageUpInputResult();
		}
		if (PlayerControllers[0].Down.Press)
		{
			GetCompetitionPageDownInputResult();
		}
		if (PlayerControllers[0].Left.Press)
		{
			GetCompetitionPageLeftInputResult();
		}
		if (PlayerControllers[0].Right.Press)
		{
			GetCompetitionPageRightInputResult();
		}

		if (PlayerControllers[0].B.Press)
		{
			GetCompetitionPageCancelInputResult();
		}

		if (PlayerControllers[0].A.Press || PlayerControllers[0].C.Press || PlayerControllers[0].Start.Press || PlayerControllers[0].Select.Press)
		{
			GetCompetitionPageAcceptInputResult();
		}

		SetCompetitionPageInteraction();
	}

	void InitMenuPoints()
	{
		CompetitionPagePoints[0][0] = *GetEntityFromSceneSlot<Entity>(75);
		CompetitionPagePoints[1][0] = *GetEntityFromSceneSlot<Entity>(78);
		CompetitionPagePoints[2][0] = *GetEntityFromSceneSlot<Entity>(77);
		CompetitionPagePoints[3][0] = *GetEntityFromSceneSlot<Entity>(80);

		SetCompetitionPageInfiniteRoundsSetting(InfiniteRounds);

		AreMenuPointsLoaded = true;
	}

	void UpdateSettingsMenu()
	{
		FixSummary();
		Entity& viewPort = *GetEntityFromSceneSlot<Entity>(ViewPortID);
		if (!AreMenuPointsLoaded) InitMenuPoints();
		Entity& page2 = *GetEntityFromSceneSlot<Entity>(CompetitionPageID);
		viewPort.Position = page2.Position;
		GetCompetitionPage();
	}

	void AllowPointRefresh()
	{
		AreMenuPointsLoaded = false;
	}
};