#include "stdafx.h"
#include "SettingsMenu.h"
#include "SonicMania.h"
#include "ManiaExt.h"
#include "CompetitionPlus.h"

namespace CompPlus_Settings_PlayerConfig
{
	using namespace SonicMania;
	using namespace CompetitionPlus;
	using namespace CompPlus_Settings_Base;

	#pragma region Definitions

	int CharChoice[5] = { 0,0,0,0,0 };
	int AbilityChoice[5] = { 0,0,0,0,0 };
	bool DropdashChoice[5] = { 0,0,0,0,0 };
	bool PeelOutChoice[5] = { 0,0,0,0,0 };
	bool InstaSheildChoice[5] = { 0,0,0,0,0 };

	int PlayerPosY[5] = { 0,0,0,0,0 };

	int PlayerPosYMax[5] = { 5,5,5,5,5 };

	bool AreMenuPointsLoaded = false;

	#pragma region Object IDs

	int ViewPortID = 44;
	int PlayerCFGPageID = 115;
	int SelectorID = 105;

	int PlayerSelectorP1_ID = 129;
	int PlayerSelectorP2_ID = 120;
	int PlayerSelectorP3_ID = 126;
	int PlayerSelectorP4_ID = 128;

	int AbilitySelectorP1_ID = 134;
	int AbilitySelectorP2_ID = 138;
	int AbilitySelectorP3_ID = 142;
	int AbilitySelectorP4_ID = 146;

	int DropDashSelectorP1_ID = 144;
	int DropDashSelectorP2_ID = 140;
	int DropDashSelectorP3_ID = 136;
	int DropDashSelectorP4_ID = 148;

	int PeelOutSelectorP1_ID = 141;
	int PeelOutSelectorP2_ID = 137;
	int PeelOutSelectorP3_ID = 133;
	int PeelOutSelectorP4_ID = 145;

	int InstaSheildSelectorP1_ID = 143;
	int InstaSheildSelectorP2_ID = 139;
	int InstaSheildSelectorP3_ID = 135;
	int InstaSheildSelectorP4_ID = 147;

	int DisposalID = 102;

	#pragma endregion

	#pragma endregion

	#pragma region Update UI

	void UpdatePlayerDropDashChoice() 
	{

		SonicMania::EntityUIText& objectP1 = *GetEntityFromSceneSlot<SonicMania::EntityUIText>(DropDashSelectorP1_ID);
		SonicMania::EntityUIText& objectP2 = *GetEntityFromSceneSlot<SonicMania::EntityUIText>(DropDashSelectorP2_ID);
		SonicMania::EntityUIText& objectP3 = *GetEntityFromSceneSlot<SonicMania::EntityUIText>(DropDashSelectorP3_ID);
		SonicMania::EntityUIText& objectP4 = *GetEntityFromSceneSlot<SonicMania::EntityUIText>(DropDashSelectorP4_ID);
		switch (DropdashChoice[1])
		{
		case true:
			objectP1.Text = (char*)"ON";
			break;
		case false:
			objectP1.Text = (char*)"OFF";
			break;
		default:
			objectP1.Text = (char*)"OFF";
			break;
		}
		switch (DropdashChoice[2])
		{
		case true:
			objectP1.Text = (char*)"ON";
			break;
		case false:
			objectP1.Text = (char*)"OFF";
			break;
		default:
			objectP1.Text = (char*)"OFF";
			break;
		}
		switch (DropdashChoice[3])
		{
		case true:
			objectP1.Text = (char*)"ON";
			break;
		case false:
			objectP1.Text = (char*)"OFF";
			break;
		default:
			objectP1.Text = (char*)"OFF";
			break;
		}
		switch (DropdashChoice[4])
		{
		case true:
			objectP1.Text = (char*)"ON";
			break;
		case false:
			objectP1.Text = (char*)"OFF";
			break;
		default:
			objectP1.Text = (char*)"OFF";
			break;
		}
	}

	void UpdatePlayerAbilitySelectors()
	{
		EntityUIPicture& objectP1 = *GetEntity(AbilitySelectorP1_ID);
		EntityUIPicture& objectP2 = *GetEntity(AbilitySelectorP2_ID);
		EntityUIPicture& objectP3 = *GetEntity(AbilitySelectorP3_ID);
		EntityUIPicture& objectP4 = *GetEntity(AbilitySelectorP4_ID);
		switch (AbilityChoice[1])
		{
		case 0:
			objectP1.AnimData.CurrentFrame = 1;
			break;
		case 1:
			objectP1.AnimData.CurrentFrame = 2;
			break;
		case 2:
			objectP1.AnimData.CurrentFrame = 3;
			break;
		case 3:
			objectP1.AnimData.CurrentFrame = 4;
			break;
		case 4:
			objectP1.AnimData.CurrentFrame = 5;
			break;
		default:
			objectP1.AnimData.CurrentFrame = 1;
			break;
		}
		switch (AbilityChoice[2])
		{
		case 0:
			objectP2.AnimData.CurrentFrame = 1;
			break;
		case 1:
			objectP2.AnimData.CurrentFrame = 2;
			break;
		case 2:
			objectP2.AnimData.CurrentFrame = 3;
			break;
		case 3:
			objectP2.AnimData.CurrentFrame = 4;
			break;
		case 4:
			objectP2.AnimData.CurrentFrame = 5;
			break;
		default:
			objectP2.AnimData.CurrentFrame = 1;
			break;
		}
		switch (AbilityChoice[3])
		{
		case 0:
			objectP3.AnimData.CurrentFrame = 1;
			break;
		case 1:
			objectP3.AnimData.CurrentFrame = 2;
			break;
		case 2:
			objectP3.AnimData.CurrentFrame = 3;
			break;
		case 3:
			objectP3.AnimData.CurrentFrame = 4;
			break;
		case 4:
			objectP3.AnimData.CurrentFrame = 5;
			break;
		default:
			objectP3.AnimData.CurrentFrame = 1;
			break;
		}
		switch (AbilityChoice[4])
		{
		case 0:
			objectP4.AnimData.CurrentFrame = 1;
			break;
		case 1:
			objectP4.AnimData.CurrentFrame = 2;
			break;
		case 2:
			objectP4.AnimData.CurrentFrame = 3;
			break;
		case 3:
			objectP4.AnimData.CurrentFrame = 4;
			break;
		case 4:
			objectP4.AnimData.CurrentFrame = 5;
			break;
		default:
			objectP4.AnimData.CurrentFrame = 1;
			break;
		}
	}

	void UpdatePlayerCharSelectors() 
	{
		EntityUIPicture &objectP1 = *GetEntity(PlayerSelectorP1_ID);
		EntityUIPicture &objectP2 = *GetEntity(PlayerSelectorP2_ID);
		EntityUIPicture &objectP3 = *GetEntity(PlayerSelectorP3_ID);
		EntityUIPicture &objectP4 = *GetEntity(PlayerSelectorP4_ID);
		switch (CharChoice[1])
		{
		case 0:
			objectP1.AnimData.CurrentFrame = 1;
			break;
		case 1:
			objectP1.AnimData.CurrentFrame = 2;
			break;
		case 2:
			objectP1.AnimData.CurrentFrame = 3;
			break;
		case 3:
			objectP1.AnimData.CurrentFrame = 4;
			break;
		case 4:
			objectP1.AnimData.CurrentFrame = 5;
			break;
		default:
			objectP1.AnimData.CurrentFrame = 1;
			break;
		}
		switch (CharChoice[2])
		{
		case 0:
			objectP2.AnimData.CurrentFrame = 1;
			break;
		case 1:
			objectP2.AnimData.CurrentFrame = 2;
			break;
		case 2:
			objectP2.AnimData.CurrentFrame = 3;
			break;
		case 3:
			objectP2.AnimData.CurrentFrame = 4;
			break;
		case 4:
			objectP2.AnimData.CurrentFrame = 5;
			break;
		default:
			objectP2.AnimData.CurrentFrame = 1;
			break;
		}
		switch (CharChoice[3])
		{
		case 0:
			objectP3.AnimData.CurrentFrame = 1;
			break;
		case 1:
			objectP3.AnimData.CurrentFrame = 2;
			break;
		case 2:
			objectP3.AnimData.CurrentFrame = 3;
			break;
		case 3:
			objectP3.AnimData.CurrentFrame = 4;
			break;
		case 4:
			objectP3.AnimData.CurrentFrame = 5;
			break;
		default:
			objectP3.AnimData.CurrentFrame = 1;
			break;
		}
		switch (CharChoice[4])
		{
		case 0:
			objectP4.AnimData.CurrentFrame = 1;
			break;
		case 1:
			objectP4.AnimData.CurrentFrame = 2;
			break;
		case 2:
			objectP4.AnimData.CurrentFrame = 3;
			break;
		case 3:
			objectP4.AnimData.CurrentFrame = 4;
			break;
		case 4:
			objectP4.AnimData.CurrentFrame = 5;
			break;
		default:
			objectP4.AnimData.CurrentFrame = 1;
			break;
		}
	}

	void UpdateUI()
	{
		UpdatePlayerCharSelectors();
		UpdatePlayerAbilitySelectors();
	}

	#pragma endregion

	#pragma region Nudge Settings

	void NudgeTemplateChoice(int player)
	{

	}

	void NudgePlayerInstaSheildChoice(int player)
	{
		if (InstaSheildChoice[player] == false)
		{
			InstaSheildChoice[player] = true;
		}
		else
		{
			InstaSheildChoice[player] = false;
		}
	}

	void NudgePlayerPeelOutChoice(int player)
	{
		if (PeelOutChoice[player] == false) 
		{
			PeelOutChoice[player] = true;
		}
		else 
		{
			PeelOutChoice[player] = false;
		}
	}

	void NudgePlayerDropdashChoice(int player)
	{
		if (DropdashChoice[player] == false)
		{
			DropdashChoice[player] = true;
		}
		else
		{
			DropdashChoice[player] = false;
		}
	}

	void NudgePlayerAbilityChoice(int player, bool subtract = false)
	{
		if (subtract)
		{
			if (AbilityChoice[player] == 0)
			{
				AbilityChoice[player] = 4;
			}
			else
			{
				AbilityChoice[player] = AbilityChoice[player] - 1;
			}
		}
		else
		{
			if (AbilityChoice[player] == 4)
			{
				AbilityChoice[player] = 0;
			}
			else
			{
				AbilityChoice[player] = AbilityChoice[player] + 1;
			}
		}
	}

	void NudgePlayerCharChoice(int player, bool subtract = false) 
	{
		if (subtract) 
		{
			if (CharChoice[player] == 0)
			{
				CharChoice[player] = 4;
			}
			else
			{
				CharChoice[player] = CharChoice[player] - 1;
			}
		}
		else 
		{
			if (CharChoice[player] == 4)
			{
				CharChoice[player] = 0;
			}
			else
			{
				CharChoice[player] = CharChoice[player] + 1;
			}
		}
	}

	#pragma endregion

	#pragma region Get Input

	void GetPlayerNavigationInput(int player) 
	{
		if (PlayerControllers[player].Up.Press)
		{
			if (PlayerPosY[player] > 0)
			{
				PlayerPosY[player] = PlayerPosY[player] - 1;
			}
		}
		else if (PlayerControllers[player].Down.Press)
		{
			if (PlayerPosY[player] < PlayerPosYMax[player] - 1)
			{
				PlayerPosY[player] = PlayerPosY[player] + 1;
			}
		}
	}

	void GetPlayerConfigurationInput(int player)
	{
		if (PlayerControllers[player].Left.Press)
		{
			if (PlayerPosY[player] == 0) NudgePlayerCharChoice(player, true);
			else if (PlayerPosY[player] == 1) NudgePlayerAbilityChoice(player, true);
			else if (PlayerPosY[player] == 2) NudgePlayerDropdashChoice(player);
			else if (PlayerPosY[player] == 3) NudgePlayerPeelOutChoice(player);
			else if (PlayerPosY[player] == 4) NudgePlayerInstaSheildChoice(player);
		}
		else if (PlayerControllers[player].Right.Press)
		{
			if (PlayerPosY[player] == 0) NudgePlayerCharChoice(player, false);
			else if (PlayerPosY[player] == 1) NudgePlayerAbilityChoice(player, false);
			else if (PlayerPosY[player] == 2) NudgePlayerDropdashChoice(player);
			else if (PlayerPosY[player] == 3) NudgePlayerPeelOutChoice(player);
			else if (PlayerPosY[player] == 4) NudgePlayerInstaSheildChoice(player);
		}
	}

	void GetPlayerInput(int player) 
	{
		GetPlayerNavigationInput(player);
		GetPlayerConfigurationInput(player);
	}

	#pragma endregion

	#pragma region General

	void GetCompetitionPage()
	{
		GetPlayerInput(1);
		GetPlayerInput(2);
		GetPlayerInput(3);
		GetPlayerInput(4);
		UpdateUI();

		if (PlayerControllers[0].A.Press || PlayerControllers[0].C.Press || PlayerControllers[0].Start.Press || PlayerControllers[0].Select.Press)
		{
			SetCurrentPage(0);
		}
	}

	void InitMenuPoints()
	{
		AreMenuPointsLoaded = true;
	}

	void UpdateSettingsMenu()
	{
		FixSummary();
		Entity& viewPort = *GetEntityFromSceneSlot<Entity>(ViewPortID);
		if (!AreMenuPointsLoaded) InitMenuPoints();
		Entity& page2 = *GetEntityFromSceneSlot<Entity>(PlayerCFGPageID);
		viewPort.Position = page2.Position;
		GetCompetitionPage();
	}

	void AllowPointRefresh()
	{
		AreMenuPointsLoaded = false;
	}

	#pragma endregion
};