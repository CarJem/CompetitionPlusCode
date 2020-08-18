#include "stdafx.h"
#include "HubWorld.h"
#include "ManiaExt.h"
#include "SonicMania.h"
#include "CompetitionPlus.h"
#include "CompPlusSettings.h"
#include "Common.h"
#include <string>
#include <sstream>

namespace CompPlus_HubWorld
{
	using namespace SonicMania;
	using namespace CompetitionPlus;
	using namespace CompPlus_Common;

	#pragma region Reserved Slot IDs

	int EnterLSelectButton = 67;

	//Player Setting Controllers
	int SwapPlayerController = 110;
	int SwapAbilityController = 115;
	int PeeloutController = 121;

	//Global Settings Controllers
	int DropDashController = 117;
	int InstaSheildController = 119;

	int SwapLevelSelectController = 88;
	int SwapLevelSelectController2 = 87;

	int PeeloutToggleText_P1 = 143;
	int PeeloutToggleText_P2 = 135;
	int PeeloutToggleText_P3 = 129;
	int PeeloutToggleText_P4 = 128;

	int SwapPlayerText_P1 = 203;
	int SwapPlayerText_P2 = 125;
	int SwapPlayerText_P3 = 133;
	int SwapPlayerText_P4 = 126;

	int SwapAbilityText_P1 = 141;
	int SwapAbilityText_P2 = 131;
	int SwapAbilityText_P3 = 140;
	int SwapAbilityText_P4 = 137;

	int DropDashToggleText = 144;
	int InstaSheildToggleText = 142;

	int AnnouncerTypeText = 132;
	int InfiniteRoundsToggleText = 136;
	int VictoryMethodSwapperText = 134;
	int LiveNUDText = 127;
	int RemoveTimeToggleText = 130;

	// Developer Settings
	int DevModeText = 138;
	int DebugModeText = 139;

	int DevModeController = 184;
	int DebugModeController = 185;
	// ---------------------------

	int SelectedLevelSelectText = 205;

	#pragma endregion

	#pragma region Reserved Entity Positions

	int OutOfBoundsX = -100;
	int OutOfBoundsY = -100;

	int SwapPlayerTextLocationX = 11264;
	int SwapPlayerTextLocationY = 11208;

	int SwapAbilityTextLocationX = 11344;
	int SwapAbilityTextLocationY = 11208;

	int PeeloutTextLocationX = 11617;
	int PeeloutTextLocationY = 11208;

	int InstaSheildTextLocationX = 11537;
	int InstaSheildTextLocationY = 11208;

	int DropDashTextLocationX = 11456;
	int DropDashTextLocationY = 11208;

	int DevModeTextLocationX = 0;
	int DevModeTextLocationY = 0;

	int DebugModeTextLocationX = 0;
	int DebugModeTextLocationY = 0;

	#pragma endregion

	#pragma region Extra Region

	#pragma endregion

	#pragma region Other Variables

	//Button Press Detection
	bool isSwapCharacterPressed = false;
	bool isSwapAbilityPressed = false;
	bool isInstaSheildPressed = false;
	bool isDropdashPressed = false;
	bool isPeeloutPressed = false;
	bool isLevelSelectSwapPressed = false; 
	bool isDevModePressed = false;
	bool isDebugModePressed = false;

	int CurrentLevelSelect = 0;

	bool LevelSelected = false;
	bool LevelSelectedWarpSoundPlayed = false;
	int SceneLoadWaitTimer = 0;
	int SceneLoadWaitMax = 100;
	int SettingWaitTimer = 100;

	#pragma endregion





	#pragma region Controller Triggers


	int GetControllerX1() 
	{
		return 3;
	}
	int GetControllerX2()
	{
		return 3;
	}
	int GetControllerY1()
	{
		return 10;
	}
	int GetControllerY2()
	{
		return 16;
	}

	void SettingWaitTimerActivate()
	{
		SettingWaitTimer = 10;
	}
	bool ToggleDebugMode(int ControlSlotID, int PlayerID, SonicMania::EntityPlayer* Player, bool isPressed)
	{
		int RealID = 1;
		bool LastState = CompPlusSettings::EnableDebugMode;

		if (Player == &Player1) RealID = 1;
		else if (Player == &Player2) RealID = 2;
		else if (Player == &Player3) RealID = 3;
		else if (Player == &Player4) RealID = 4;

		Entity& Controller = *GetEntityFromSceneSlot<Entity>(ControlSlotID);

		int x1 = Controller.Position.X - GetControllerX1();
		int y1 = Controller.Position.Y - GetControllerY1();
		int x2 = Controller.Position.X + GetControllerX2();
		int y2 = Controller.Position.Y + GetControllerY2();
		if (PlayerInRange(Player, x1, y1, x2, y2) && Player->Up && !isPressed)
		{
			if (LastState == true && !isPressed)
			{
				CompPlusSettings::EnableDebugMode = false;
				isPressed = true;
				SettingWaitTimerActivate();
			}
			else if (!isPressed)
			{
				CompPlusSettings::EnableDebugMode = true;
				isPressed = true;
				SettingWaitTimerActivate();
			}
		}
		else if (!Player->Up && isPressed)
		{
			if (SettingWaitTimer == 0) isPressed = false;
		}

		return isPressed;
	}

	bool ToggleDevMode(int ControlSlotID, int PlayerID, SonicMania::EntityPlayer* Player, bool isPressed)
	{
		int RealID = 1;
		bool LastState = CompPlusSettings::EnableDevMode;

		if (Player == &Player1) RealID = 1;
		else if (Player == &Player2) RealID = 2;
		else if (Player == &Player3) RealID = 3;
		else if (Player == &Player4) RealID = 4;

		Entity& Controller = *GetEntityFromSceneSlot<Entity>(ControlSlotID);

		int x1 = Controller.Position.X - GetControllerX1();
		int y1 = Controller.Position.Y - GetControllerY1();
		int x2 = Controller.Position.X + GetControllerX2();
		int y2 = Controller.Position.Y + GetControllerY2();
		if (PlayerInRange(Player, x1, y1, x2, y2) && Player->Up && !isPressed)
		{
			if (LastState == true && !isPressed)
			{
				CompPlusSettings::EnableDevMode = false;
				isPressed = true;
				SettingWaitTimerActivate();
			}
			else if (!isPressed)
			{
				CompPlusSettings::EnableDevMode = true;
				isPressed = true;
				SettingWaitTimerActivate();
			}
		}
		else if (!Player->Up && isPressed)
		{
			if (SettingWaitTimer == 0) isPressed = false;
		}

		return isPressed;
	}

	bool ChangeLevelSelect(int ControlSlotID, int PlayerID, SonicMania::EntityPlayer* Player, bool isPressed)
	{
		int RealID = 1;

		if (Player == &Player1) RealID = 1;
		else if (Player == &Player2) RealID = 2;
		else if (Player == &Player3) RealID = 3;
		else if (Player == &Player4) RealID = 4;

		Entity& Controller = *GetEntityFromSceneSlot<Entity>(ControlSlotID);

		int x1 = Controller.Position.X - GetControllerX1();
		int y1 = Controller.Position.Y - GetControllerY1();
		int x2 = Controller.Position.X + GetControllerX2();
		int y2 = Controller.Position.Y + GetControllerY2();
		if (PlayerInRange(Player, x1, y1, x2, y2) && Player->Up && !isPressed)
		{
			if (CurrentLevelSelect == 0)
			{
				CurrentLevelSelect = 1;
				isPressed = true;
				SettingWaitTimerActivate();
			}
			else if (CurrentLevelSelect == 1)
			{
				CurrentLevelSelect = 2;
				isPressed = true;
				SettingWaitTimerActivate();
			}
			else if (CurrentLevelSelect == 2)
			{
				CurrentLevelSelect = 0;
				isPressed = true;
				SettingWaitTimerActivate();
			}
		}
		else if (!Player->Up && isPressed)
		{
			if (SettingWaitTimer == 0) isPressed = false;
		}

		return isPressed;
	}

	bool ChangeCharacter(int ControlSlotID, int PlayerID, SonicMania::EntityPlayer* Player, bool isPressed)
	{
		int RealID = 1;

		if (Player == &Player1) RealID = 1;
		else if (Player == &Player2) RealID = 2;
		else if (Player == &Player3) RealID = 3;
		else if (Player == &Player4) RealID = 4;

		Entity& Controller = *GetEntityFromSceneSlot<Entity>(ControlSlotID);

		int x1 = Controller.Position.X - GetControllerX1();
		int y1 = Controller.Position.Y - GetControllerY1();
		int x2 = Controller.Position.X + GetControllerX2();
		int y2 = Controller.Position.Y + GetControllerY2();
		if (PlayerInRange(Player, x1, y1, x2, y2) && Player->Up && !isPressed)
		{
			if (Player->Character == Character_Sonic && !isPressed)
			{
				CompPlusSettings::SetPlayer(RealID, SonicMania::Character_Tails);
				CompPlusSettings::SetAbility(RealID, CompPlusSettings::AbilitySet_Tails);
				isPressed = true;
				SettingWaitTimerActivate();
			}
			else if (Player->Character == Character_Tails && !isPressed)
			{
				CompPlusSettings::SetPlayer(RealID, SonicMania::Character_Knux);
				CompPlusSettings::SetAbility(RealID, CompPlusSettings::AbilitySet_Knuckles);
				isPressed = true;
				SettingWaitTimerActivate();
			}
			else if (Player->Character == Character_Knux && !isPressed)
			{
				CompPlusSettings::SetPlayer(RealID, SonicMania::Character_Mighty);
				CompPlusSettings::SetAbility(RealID, CompPlusSettings::AbilitySet_Mighty);
				isPressed = true;
				SettingWaitTimerActivate();
			}
			else if (Player->Character == Character_Mighty && !isPressed)
			{
				CompPlusSettings::SetPlayer(RealID, SonicMania::Character_Ray);
				CompPlusSettings::SetAbility(RealID, CompPlusSettings::AbilitySet_Ray);
				isPressed = true;
				SettingWaitTimerActivate();
			}
			else if (Player->Character == Character_Ray && !isPressed)
			{
				CompPlusSettings::SetPlayer(RealID, SonicMania::Character_Sonic);
				CompPlusSettings::SetAbility(RealID, CompPlusSettings::AbilitySet_Sonic);
				isPressed = true;
				SettingWaitTimerActivate();
			}
		}
		else if (!Player->Up && isPressed)
		{
			if (SettingWaitTimer == 0) isPressed = false;
		}

		return isPressed;
	}

	bool ChangePlayerAbility(int ControlSlotID, int PlayerID, SonicMania::EntityPlayer* Player, bool isPressed)
	{
		int RealID = 1;

		if (Player == &Player1) RealID = 1;
		else if (Player == &Player2) RealID = 2;
		else if (Player == &Player3) RealID = 3;
		else if (Player == &Player4) RealID = 4;

		Entity& Controller = *GetEntityFromSceneSlot<Entity>(ControlSlotID);

		int x1 = Controller.Position.X - GetControllerX1();
		int y1 = Controller.Position.Y - GetControllerY1();
		int x2 = Controller.Position.X + GetControllerX2();
		int y2 = Controller.Position.Y + GetControllerY2();
		if (PlayerInRange(Player, x1, y1, x2, y2) && Player->Up && !isPressed)
		{
			if (Player->Moveset == MOVESET_SONIC && !isPressed)
			{
				SetAbility(RealID, CompPlusSettings::AbilitySet_Tails);
				isPressed = true;
				SettingWaitTimerActivate();
			}
			else if (Player->Moveset == MOVESET_TAILS && !isPressed)
			{
				SetAbility(RealID, CompPlusSettings::AbilitySet_Knuckles);
				isPressed = true;
				SettingWaitTimerActivate();
			}
			else if (Player->Moveset == MOVESET_KNUX && !isPressed)
			{
				SetAbility(RealID, CompPlusSettings::AbilitySet_Mighty);
				isPressed = true;
				SettingWaitTimerActivate();
			}
			else if (Player->Moveset == MOVESET_MIGHTY && !isPressed)
			{
				SetAbility(RealID, CompPlusSettings::AbilitySet_Ray);
				isPressed = true;
				SettingWaitTimerActivate();
			}
			else if (Player->Moveset == MOVESET_RAY && !isPressed)
			{
				SetAbility(RealID, CompPlusSettings::AbilitySet_Sonic);
				isPressed = true;
				SettingWaitTimerActivate();
			}
		}
		else if (!Player->Up && isPressed)
		{
			if (SettingWaitTimer == 0) isPressed = false;
		}

		return isPressed;
	}

	bool ToggleInstaSheild(int ControlSlotID, int PlayerID, SonicMania::EntityPlayer* Player, bool isPressed)
	{
		int RealID = 1;
		bool LastState = CompPlusSettings::InstaSheildAbility;

		if (Player == &Player1) RealID = 1;
		else if (Player == &Player2) RealID = 2;
		else if (Player == &Player3) RealID = 3;
		else if (Player == &Player4) RealID = 4;

		Entity& Controller = *GetEntityFromSceneSlot<Entity>(ControlSlotID);

		int x1 = Controller.Position.X - GetControllerX1();
		int y1 = Controller.Position.Y - GetControllerY1();
		int x2 = Controller.Position.X + GetControllerX2();
		int y2 = Controller.Position.Y + GetControllerY2();
		if (PlayerInRange(Player, x1, y1, x2, y2) && Player->Up && !isPressed)
		{
			if (LastState == true && !isPressed)
			{
				CompPlusSettings::SetInstaSheildAbility(false);
				isPressed = true;
				SettingWaitTimerActivate();
			}
			else if (!isPressed)
			{
				CompPlusSettings::SetInstaSheildAbility(true);
				isPressed = true;
				SettingWaitTimerActivate();
			}
		}
		else if (!Player->Up && isPressed)
		{
			if (SettingWaitTimer == 0) isPressed = false;
		}

		return isPressed;
	}

	bool ToggleDropDash(int ControlSlotID, int PlayerID, SonicMania::EntityPlayer* Player, bool isPressed)
	{
		int RealID = 1;
		bool LastState = CompPlusSettings::DropdashAbility;

		if (Player == &Player1) RealID = 1;
		else if (Player == &Player2) RealID = 2;
		else if (Player == &Player3) RealID = 3;
		else if (Player == &Player4) RealID = 4;

		Entity& Controller = *GetEntityFromSceneSlot<Entity>(ControlSlotID);

		int x1 = Controller.Position.X - GetControllerX1();
		int y1 = Controller.Position.Y - GetControllerY1();
		int x2 = Controller.Position.X + GetControllerX2();
		int y2 = Controller.Position.Y + GetControllerY2();
		if (PlayerInRange(Player, x1, y1, x2, y2) && Player->Up && !isPressed)
		{
			if (LastState == true && !isPressed)
			{
				CompPlusSettings::SetDropdashAbility(false);
				isPressed = true;
				SettingWaitTimerActivate();
			}
			else if (!isPressed)
			{
				CompPlusSettings::SetDropdashAbility(true);
				isPressed = true;
				SettingWaitTimerActivate();
			}
		}
		else if (!Player->Up && isPressed)
		{
			if (SettingWaitTimer == 0) isPressed = false;
		}

		return isPressed;
	}

	bool TogglePeelout(int ControlSlotID, int PlayerID, SonicMania::EntityPlayer* Player, bool isPressed)
	{
		int RealID = 1;
		bool LastState = false;

		if (Player == &Player1)
		{
			RealID = 1;
			LastState = CompPlusSettings::Player1PeeloutAbility;
		}
		else if (Player == &Player2)
		{
			RealID = 2;
			LastState = CompPlusSettings::Player2PeeloutAbility;
		}
		else if (Player == &Player3)
		{
			RealID = 3;
			LastState = CompPlusSettings::Player3PeeloutAbility;
		}
		else if (Player == &Player4)
		{
			RealID = 4;
			LastState = CompPlusSettings::Player4PeeloutAbility;
		}

		Entity& Controller = *GetEntityFromSceneSlot<Entity>(ControlSlotID);

		int x1 = Controller.Position.X - GetControllerX1();
		int y1 = Controller.Position.Y - GetControllerY1();
		int x2 = Controller.Position.X + GetControllerX2();
		int y2 = Controller.Position.Y + GetControllerY2();
		if (PlayerInRange(Player, x1, y1, x2, y2) && Player->Up && !isPressed)
		{
			if (LastState == true && !isPressed)
			{
				CompPlusSettings::SetPeeloutAbility(RealID, false);
				isPressed = true;
				SettingWaitTimerActivate();
			}
			else if (!isPressed)
			{
				CompPlusSettings::SetPeeloutAbility(RealID, true);
				isPressed = true;
				SettingWaitTimerActivate();
			}
		}
		else if (!Player->Up && isPressed)
		{
			if (SettingWaitTimer == 0) isPressed = false;
		}

		return isPressed;
	}

	void CheckSettings()
	{
		isLevelSelectSwapPressed = ChangeLevelSelect(SwapLevelSelectController, 1, &Player1, isLevelSelectSwapPressed);
		isLevelSelectSwapPressed = ChangeLevelSelect(SwapLevelSelectController, 2, &Player2, isLevelSelectSwapPressed);
		isLevelSelectSwapPressed = ChangeLevelSelect(SwapLevelSelectController, 3, &Player3, isLevelSelectSwapPressed);
		isLevelSelectSwapPressed = ChangeLevelSelect(SwapLevelSelectController, 4, &Player4, isLevelSelectSwapPressed);

		isLevelSelectSwapPressed = ChangeLevelSelect(SwapLevelSelectController2, 1, &Player1, isLevelSelectSwapPressed);
		isLevelSelectSwapPressed = ChangeLevelSelect(SwapLevelSelectController2, 2, &Player2, isLevelSelectSwapPressed);
		isLevelSelectSwapPressed = ChangeLevelSelect(SwapLevelSelectController2, 3, &Player3, isLevelSelectSwapPressed);
		isLevelSelectSwapPressed = ChangeLevelSelect(SwapLevelSelectController2, 4, &Player4, isLevelSelectSwapPressed);

		isSwapCharacterPressed = ChangeCharacter(SwapPlayerController, 1, &Player1, isSwapCharacterPressed);
		isSwapCharacterPressed = ChangeCharacter(SwapPlayerController, 2, &Player2, isSwapCharacterPressed);
		isSwapCharacterPressed = ChangeCharacter(SwapPlayerController, 3, &Player3, isSwapCharacterPressed);
		isSwapCharacterPressed = ChangeCharacter(SwapPlayerController, 4, &Player4, isSwapCharacterPressed);

		isSwapAbilityPressed = ChangePlayerAbility(SwapAbilityController, 1, &Player1, isSwapAbilityPressed);
		isSwapAbilityPressed = ChangePlayerAbility(SwapAbilityController, 2, &Player2, isSwapAbilityPressed);
		isSwapAbilityPressed = ChangePlayerAbility(SwapAbilityController, 3, &Player3, isSwapAbilityPressed);
		isSwapAbilityPressed = ChangePlayerAbility(SwapAbilityController, 4, &Player4, isSwapAbilityPressed);

		isPeeloutPressed = TogglePeelout(PeeloutController, 1, &Player1, isPeeloutPressed);
		isPeeloutPressed = TogglePeelout(PeeloutController, 2, &Player2, isPeeloutPressed);
		isPeeloutPressed = TogglePeelout(PeeloutController, 3, &Player3, isPeeloutPressed);
		isPeeloutPressed = TogglePeelout(PeeloutController, 4, &Player4, isPeeloutPressed);

		isInstaSheildPressed = ToggleInstaSheild(InstaSheildController, 1, &Player1, isInstaSheildPressed);
		isInstaSheildPressed = ToggleInstaSheild(InstaSheildController, 2, &Player2, isInstaSheildPressed);
		isInstaSheildPressed = ToggleInstaSheild(InstaSheildController, 3, &Player3, isInstaSheildPressed);
		isInstaSheildPressed = ToggleInstaSheild(InstaSheildController, 4, &Player4, isInstaSheildPressed);

		isDropdashPressed = ToggleDropDash(DropDashController, 1, &Player1, isDropdashPressed);
		isDropdashPressed = ToggleDropDash(DropDashController, 2, &Player2, isDropdashPressed);
		isDropdashPressed = ToggleDropDash(DropDashController, 3, &Player3, isDropdashPressed);
		isDropdashPressed = ToggleDropDash(DropDashController, 4, &Player4, isDropdashPressed);

		isDevModePressed = ToggleDevMode(DevModeController, 1, &Player1, isDevModePressed);
		isDevModePressed = ToggleDevMode(DevModeController, 2, &Player2, isDevModePressed);
		isDevModePressed = ToggleDevMode(DevModeController, 3, &Player3, isDevModePressed);
		isDevModePressed = ToggleDevMode(DevModeController, 4, &Player4, isDevModePressed);

		isDebugModePressed = ToggleDebugMode(DebugModeController, 1, &Player1, isDebugModePressed);
		isDebugModePressed = ToggleDebugMode(DebugModeController, 2, &Player2, isDebugModePressed);
		isDebugModePressed = ToggleDebugMode(DebugModeController, 3, &Player3, isDebugModePressed);
		isDebugModePressed = ToggleDebugMode(DebugModeController, 4, &Player4, isDebugModePressed);

		CompPlusSettings::FixAbilites(&Player1);
		CompPlusSettings::FixAbilites(&Player2);
		CompPlusSettings::FixAbilites(&Player3);
		CompPlusSettings::FixAbilites(&Player4);

		if (SettingWaitTimer != 0) SettingWaitTimer = SettingWaitTimer - 1;
	}

	#pragma endregion

	#pragma region Drawing

	void UpdateAbilitySwapperDisplay(int SlotID, int x, int y, CompPlusSettings::PlayerAbility Ability)
	{
		EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

		Label3.Position.X = x;
		Label3.Position.Y = y;

		if (Ability == CompPlusSettings::AbilitySet_Sonic)
		{
			char* on_text = (char*)"SONIC";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)5;
		}
		else if (Ability == CompPlusSettings::AbilitySet_Tails)
		{
			char* on_text = (char*)"TAILS";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)5;
		}
		else if (Ability == CompPlusSettings::AbilitySet_Knuckles)
		{
			char* on_text = (char*)"KNUCKLES";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)8;
		}
		else if (Ability == CompPlusSettings::AbilitySet_Mighty)
		{
			char* on_text = (char*)"MIGHTY";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)6;
		}
		else if (Ability == CompPlusSettings::AbilitySet_Ray)
		{
			char* on_text = (char*)"RAY";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)3;
		}
		else if (Ability == CompPlusSettings::AbilitySet_Default)
		{
			char* on_text = (char*)"DEFAULT";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)7;
		}
	}

	void UpdatePlayerSwapperDisplay(int SlotID, int x, int y, CompPlusSettings::ChosenPlayer Player)
	{
		EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

		Label3.Position.X = x;
		Label3.Position.Y = y;

		if (Player == CompPlusSettings::ChosenPlayer_Sonic)
		{
			char* on_text = (char*)"SONIC";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)5;
		}
		else if (Player == CompPlusSettings::ChosenPlayer_Tails)
		{
			char* on_text = (char*)"TAILS";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)5;
		}
		else if (Player == CompPlusSettings::ChosenPlayer_Knuckles)
		{
			char* on_text = (char*)"KNUCKLES";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)8;
		}
		else if (Player == CompPlusSettings::ChosenPlayer_Mighty)
		{
			char* on_text = (char*)"MIGHTY";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)6;
		}
		else if (Player == CompPlusSettings::ChosenPlayer_Ray)
		{
			char* on_text = (char*)"RAY";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)3;
		}
		else if (Player == CompPlusSettings::ChosenPlayer_Default)
		{
			char* on_text = (char*)"DEFAULT";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)7;
		}
	}

	void UpdatePlayerPeeloutDisplay(int SlotID, int x, int y, bool State)
	{
		EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

		Label3.Position.X = x;
		Label3.Position.Y = y;

		if (State)
		{
			char* on_text = (char*)"ON";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)2;
		}
		else
		{
			char* off_text = (char*)"OFF";
			ConvertASCII2Unicode(Label3.Text, off_text, strlen(off_text), -32);
			Label3.TextLength = (WORD)3;
		}
	}

	void UpdateDevModeToggleDisplay(bool State)
	{
		EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(DevModeText);
		Label3.Position.X = DevModeTextLocationX;
		Label3.Position.Y = DevModeTextLocationY;

		if (State)
		{
			char* on_text = (char*)"ON";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)2;
		}
		else
		{
			char* off_text = (char*)"OFF";
			ConvertASCII2Unicode(Label3.Text, off_text, strlen(off_text), -32);
			Label3.TextLength = (WORD)3;
		}
	}

	void UpdateDebugModeToggleDisplay(bool State)
	{
		EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(DebugModeText);

		Label3.Position.X = DebugModeTextLocationX;
		Label3.Position.Y = DebugModeTextLocationY;

		if (State)
		{
			char* on_text = (char*)"ON";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)2;
		}
		else
		{
			char* off_text = (char*)"OFF";
			ConvertASCII2Unicode(Label3.Text, off_text, strlen(off_text), -32);
			Label3.TextLength = (WORD)3;
		}
	}

	void UpdateDropDashToggleDisplay(bool State)
	{
		EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(DropDashToggleText);
		Label3.Position.X = DropDashTextLocationX;
		Label3.Position.Y = DropDashTextLocationY;

		if (State)
		{
			char* on_text = (char*)"ON";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)2;
		}
		else
		{
			char* off_text = (char*)"OFF";
			ConvertASCII2Unicode(Label3.Text, off_text, strlen(off_text), -32);
			Label3.TextLength = (WORD)3;
		}
	}

	void UpdateInstaSheildToggleDisplay(bool State)
	{
		EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(InstaSheildToggleText);

		Label3.Position.X = InstaSheildTextLocationX;
		Label3.Position.Y = InstaSheildTextLocationY;

		if (State)
		{
			char* on_text = (char*)"ON";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)2;
		}
		else
		{
			char* off_text = (char*)"OFF";
			ConvertASCII2Unicode(Label3.Text, off_text, strlen(off_text), -32);
			Label3.TextLength = (WORD)3;
		}
	}

	void UpdateLevelSelectStatusDisplay(int State) 
	{
		EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SelectedLevelSelectText);

		if (State == 0)
		{
			char* on_text = (char*)"LSELECT: MANIA";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)14;
		}
		else if (State == 1)
		{
			char* on_text = (char*)"LSELECT: ENCORE";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)15;
		}
		else if (State == 2)
		{
			char* on_text = (char*)"LSELECT: CUSTOM";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)15;
		}
	}

	void UpdateHUBDisplays()
	{
		UpdatePlayerSwapperDisplay(SwapPlayerText_P1, SwapPlayerTextLocationX, SwapPlayerTextLocationY - 48, CompPlusSettings::Player1ChosenPlayer);
		UpdatePlayerSwapperDisplay(SwapPlayerText_P2, SwapPlayerTextLocationX, SwapPlayerTextLocationY - 32, CompPlusSettings::Player2ChosenPlayer);
		UpdatePlayerSwapperDisplay(SwapPlayerText_P3, SwapPlayerTextLocationX, SwapPlayerTextLocationY - 16, CompPlusSettings::Player3ChosenPlayer);
		UpdatePlayerSwapperDisplay(SwapPlayerText_P4, SwapPlayerTextLocationX, SwapPlayerTextLocationY - 0, CompPlusSettings::Player4ChosenPlayer);

		UpdateAbilitySwapperDisplay(SwapAbilityText_P1, SwapAbilityTextLocationX, SwapAbilityTextLocationY - 48, CompPlusSettings::Player1AbilitySet);
		UpdateAbilitySwapperDisplay(SwapAbilityText_P2, SwapAbilityTextLocationX, SwapAbilityTextLocationY - 32, CompPlusSettings::Player2AbilitySet);
		UpdateAbilitySwapperDisplay(SwapAbilityText_P3, SwapAbilityTextLocationX, SwapAbilityTextLocationY - 16, CompPlusSettings::Player3AbilitySet);
		UpdateAbilitySwapperDisplay(SwapAbilityText_P4, SwapAbilityTextLocationX, SwapAbilityTextLocationY - 0, CompPlusSettings::Player4AbilitySet);

		UpdatePlayerPeeloutDisplay(PeeloutToggleText_P1, PeeloutTextLocationX, PeeloutTextLocationY - 48, CompPlusSettings::Player1PeeloutAbility);
		UpdatePlayerPeeloutDisplay(PeeloutToggleText_P2, PeeloutTextLocationX, PeeloutTextLocationY - 32, CompPlusSettings::Player2PeeloutAbility);
		UpdatePlayerPeeloutDisplay(PeeloutToggleText_P3, PeeloutTextLocationX, PeeloutTextLocationY - 16, CompPlusSettings::Player3PeeloutAbility);
		UpdatePlayerPeeloutDisplay(PeeloutToggleText_P4, PeeloutTextLocationX, PeeloutTextLocationY - 0, CompPlusSettings::Player4PeeloutAbility);

		UpdateDropDashToggleDisplay(CompPlusSettings::DropdashAbility);
		UpdateInstaSheildToggleDisplay(CompPlusSettings::InstaSheildAbility);

		UpdateDebugModeToggleDisplay(CompPlusSettings::EnableDebugMode);
		UpdateDevModeToggleDisplay(CompPlusSettings::EnableDevMode);


		UpdateLevelSelectStatusDisplay(CurrentLevelSelect);
	}

	void UpdateHUBPositions()
	{
		//X: 11264 Y: 11123

		int OffsetX = 0;
		int OffsetY = 85;

		Entity& E1 = *GetEntityFromSceneSlot<Entity>(SwapPlayerController);
		Entity& E2 = *GetEntityFromSceneSlot<Entity>(SwapAbilityController);
		Entity& E3 = *GetEntityFromSceneSlot<Entity>(DropDashController);
		Entity& E4 = *GetEntityFromSceneSlot<Entity>(PeeloutController);
		Entity& E5 = *GetEntityFromSceneSlot<Entity>(InstaSheildController);
		Entity& E6 = *GetEntityFromSceneSlot<Entity>(DebugModeController);
		Entity& E7 = *GetEntityFromSceneSlot<Entity>(DevModeController);

		SwapPlayerTextLocationX = E1.Position.X + OffsetX;
		SwapPlayerTextLocationY = E1.Position.Y + OffsetY;

		SwapAbilityTextLocationX = E2.Position.X + OffsetX;
		SwapAbilityTextLocationY = E2.Position.Y + OffsetY;

		PeeloutTextLocationX = E4.Position.X + OffsetX;
		PeeloutTextLocationY = E4.Position.Y + OffsetY;

		InstaSheildTextLocationX = E5.Position.X + OffsetX;
		InstaSheildTextLocationY = E5.Position.Y + OffsetY;

		DropDashTextLocationX = E3.Position.X + OffsetX;
		DropDashTextLocationY = E3.Position.Y + OffsetY;

		DebugModeTextLocationX = E6.Position.X + OffsetX;
		DebugModeTextLocationY = E6.Position.Y + OffsetY;

		DevModeTextLocationX = E7.Position.X + OffsetX;
		DevModeTextLocationY = E7.Position.Y + OffsetY;
	}

	#pragma endregion





	void UpdateHUBWorld() 
	{	
		SonicMania::Timer.ResetTimer();
		if (SonicMania::Timer.Enabled) 
		{
			SonicMania::Timer.Enabled = false;
		}

		Button& ConfirmButton = *GetEntityFromSceneSlot<Button>(EnterLSelectButton);

		UpdateHUBPositions();
		CheckSettings();
		UpdateHUBDisplays();

		if (ConfirmButton.Pressed) LevelSelected = true;
		
		if (LevelSelected) EnterLevelSelectLoop(true, SceneLoadWaitTimer, SceneLoadWaitMax, LevelSelected, LevelSelectedWarpSoundPlayed);
	}

	void LoadLevelSelect() 
	{
		if (CurrentLevelSelect == 0) LoadLevel_IZ("CPMLS");
		else if (CurrentLevelSelect == 1) LoadLevel_IZ("CPELS");
		else if (CurrentLevelSelect == 2) LoadLevel_IZ("CPCLS");
	}

	void EnterLevelSelectLoop(bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
	{
		if (FastWarp && SceneLoadWaitTimer < 50)
		{
			SceneLoadWaitTimer = 50;
		}


		if (SceneLoadWaitTimer >= SceneLoadWaitMax)
		{
			SceneLoadWaitTimer = 0;
			LevelSelected = false;
			LevelSelectedWarpSoundPlayed = false;
			CompPlus_Common::LoadLevel(141);
		}
		else
		{
			if (SceneLoadWaitTimer >= 50 && !LevelSelectedWarpSoundPlayed)
			{
				PlaySoundFXS("Global/SpecialWarp.wav");
				LevelSelectedWarpSoundPlayed = true;

				Entity* FXFade = SpawnObject(GetObjectIDFromType(ObjectType_FXFade), 0, Vector2(Player1.Position.X, Player1.Position.Y - 30));
				EntityFXFade* FxFadeR = (EntityFXFade*)FXFade;

				FxFadeR->Time = 0;
				FxFadeR->SpeedIn = 10;
				FxFadeR->Wait = 3;
				FxFadeR->SpeedOut = 0;
				FxFadeR->Color = 0x000000;
				FxFadeR->OneWay = true;
				FxFadeR->EventOnly = false;
				FxFadeR->Overhud = false;
				FxFadeR->FadeOutBlack = true;

			}
			SceneLoadWaitTimer++;
		}

		stru_26B818[0].playStatus = 0;

	}


}