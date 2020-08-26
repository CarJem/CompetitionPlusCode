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

	int AnnouncerTypeController = 183;
	int InfiniteRoundsToggleController = 181;
	int VictoryMethodSwapperController = 182;
	int LivesNUDController = 178;
	int RemoveTimeToggleController = 179;

	int AnnouncerTypeText = 132;
	int InfiniteRoundsToggleText = 136;
	int VictoryMethodSwapperText = 134;
	int LivesNUDText = 127;
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

	INT_Position Pos_OutOfBounds = INT_Position(-100, -100);
	INT_Position Pos_SwapPlayerText = INT_Position();
	INT_Position Pos_SwapAbilityText = INT_Position();
	INT_Position Pos_PeeloutText = INT_Position();
	INT_Position Pos_InstaSheildText = INT_Position();
	INT_Position Pos_DropDashText = INT_Position();
	INT_Position Pos_DevModeText = INT_Position();
	INT_Position Pos_DebugModeText = INT_Position();
	INT_Position Pos_LivesNUDText = INT_Position();
	INT_Position Pos_RemoveTimeText = INT_Position();
	INT_Position Pos_InfiniteRoundsText = INT_Position();
	INT_Position Pos_AnnouncerTypeText = INT_Position();
	INT_Position Pos_VictoryMethodText = INT_Position();

	#pragma endregion

	#pragma region Extra Region

	#pragma endregion

	#pragma region Other Variables

    static wchar_t* Strings[100];
	bool isSettingChanged = false;	//Controller Press Detection
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

	bool ToggleController(int ControlSlotID, bool OldValue, int PlayerID)
	{
		Entity& Controller = *GetEntityFromSceneSlot<Entity>(ControlSlotID);

		int x1 = Controller.Position.X - GetControllerX1();
		int y1 = Controller.Position.Y - GetControllerY1();
		int x2 = Controller.Position.X + GetControllerX2();
		int y2 = Controller.Position.Y + GetControllerY2();
		bool NewValue = OldValue;

		for (int RealID = 1; RealID <= 4; RealID++)
		{
			SonicMania::EntityPlayer* Player;
			if (RealID == 1) Player = &Player1;
			else if (RealID == 2) Player = &Player2;
			else if (RealID == 3) Player = &Player3;
			else if (RealID == 4) Player = &Player4;
			else Player = &Player1;

			if (PlayerInRange(Player, x1, y1, x2, y2) && Player->Up && !isSettingChanged)
			{
				if (OldValue == true) NewValue = false;
				else NewValue = true;
				CompPlus_Common::PlayMenuMoveSoundFX(false);
				isSettingChanged = true;
				SettingWaitTimerActivate();
			}
			else if (PlayerInRange(Player, x1, y1, x2, y2) && Player->Down && !isSettingChanged)
			{
				if (OldValue == true) NewValue = false;
				else NewValue = true;
				CompPlus_Common::PlayMenuMoveSoundFX(false);
				isSettingChanged = true;
				SettingWaitTimerActivate();
			}
			else if (!Player->Up && !Player->Down && isSettingChanged)
			{
				if (SettingWaitTimer == 0) isSettingChanged = false;
			}

			if (PlayerID == RealID) return NewValue;
			else if (PlayerID == -1 && isSettingChanged) return NewValue;
		}

		return NewValue;
	}

	int UpDownController(int ControlSlotID, int OldValue, int Min, int Max, int PlayerID)
	{
		Entity& Controller = *GetEntityFromSceneSlot<Entity>(ControlSlotID);

		int x1 = Controller.Position.X - GetControllerX1();
		int y1 = Controller.Position.Y - GetControllerY1();
		int x2 = Controller.Position.X + GetControllerX2();
		int y2 = Controller.Position.Y + GetControllerY2();
		int NewValue = OldValue;

		for (int RealID = 1; RealID <= 4; RealID++)
		{
			SonicMania::EntityPlayer* Player;
			if (RealID == 1) Player = &Player1;
			else if (RealID == 2) Player = &Player2;
			else if (RealID == 3) Player = &Player3;
			else if (RealID == 4) Player = &Player4;
			else Player = &Player1;

			if (PlayerInRange(Player, x1, y1, x2, y2) && Player->Up && !isSettingChanged)
			{
				if (OldValue + 1 > Max) NewValue = Min;
				else NewValue = OldValue + 1;
				CompPlus_Common::PlayMenuMoveSoundFX(false);
				isSettingChanged = true;
				SettingWaitTimerActivate();
			}
			else if (PlayerInRange(Player, x1, y1, x2, y2) && Player->Down && !isSettingChanged)
			{
				if (OldValue - 1 < Min) NewValue = Max;
				else NewValue = OldValue - 1;
				CompPlus_Common::PlayMenuMoveSoundFX(false);
				isSettingChanged = true;
				SettingWaitTimerActivate();
			}
			else if (!Player->Up && !Player->Down && isSettingChanged)
			{
				if (SettingWaitTimer == 0) isSettingChanged = false;
			}

			if (PlayerID == RealID) return NewValue;
			else if (PlayerID == -1 && isSettingChanged) return NewValue;
		}

		return NewValue;
	}

	void ChangeCharacter(int PlayerID, int Value) 
	{
		CompPlusSettings::SetPlayer(PlayerID, (CompPlusSettings::ChosenPlayer)Value);
		CompPlusSettings::SetAbility(PlayerID, (CompPlusSettings::PlayerAbility)Value);
	}

	void ChangeAbility(int PlayerID, int Value)
	{
		CompPlusSettings::SetAbility(PlayerID, (CompPlusSettings::PlayerAbility)Value);
	}

	void SetInitalLives(int Value) 
	{
		if (Value == 0 || Value == 100) CompPlusSettings::InfiniteLives = true;
		else CompPlusSettings::InfiniteLives = false;
		CompPlusSettings::InitalLives = Value;
	}

	void CheckSettings()
	{
		//Debug Mode Toggle
		bool DebugStatus = ToggleController(DebugModeController, CompPlusSettings::EnableDebugMode, -1);
		if (DebugStatus != CompPlusSettings::EnableDebugMode) CompPlusSettings::EnableDebugMode = DebugStatus;

		//Dev Mode Toggle
		bool DevStatus = ToggleController(DevModeController, CompPlusSettings::EnableDevMode, -1);
		if (DevStatus != CompPlusSettings::EnableDevMode) CompPlusSettings::EnableDevMode = DebugStatus;

		//Level Select NUD
		int LevelStatus = UpDownController(SwapLevelSelectController, CurrentLevelSelect, 0, 3, -1);
		if (LevelStatus != CurrentLevelSelect) CurrentLevelSelect = LevelStatus;
		LevelStatus = UpDownController(SwapLevelSelectController2, CurrentLevelSelect, 0, 3, -1);
		if (LevelStatus != CurrentLevelSelect) CurrentLevelSelect = LevelStatus;

		//Insta-Sheild Toggle
		bool InstaSheildStatus = ToggleController(InstaSheildController, CompPlusSettings::InstaSheildAbility, -1);
		if (InstaSheildStatus != CompPlusSettings::InstaSheildAbility) CompPlusSettings::SetInstaSheildAbility(InstaSheildStatus);

		//Dropdash Toggle
		bool DropdashStatus = ToggleController(DropDashController, CompPlusSettings::DropdashAbility, -1);
		if (DropdashStatus != CompPlusSettings::DropdashAbility) CompPlusSettings::SetDropdashAbility(DropdashStatus);

		//Character NUD
		int CharacterP1Status = UpDownController(SwapPlayerController, (int)CompPlusSettings::Player1ChosenPlayer, 1, 5, 1);
		if (CharacterP1Status != (int)CompPlusSettings::Player1ChosenPlayer) ChangeCharacter(1, (CompPlusSettings::ChosenPlayer)CharacterP1Status);
		int CharacterP2Status = UpDownController(SwapPlayerController, (int)CompPlusSettings::Player2ChosenPlayer, 1, 5, 2);
		if (CharacterP2Status != (int)CompPlusSettings::Player2ChosenPlayer) ChangeCharacter(2, (CompPlusSettings::ChosenPlayer)CharacterP2Status);
		int CharacterP3Status = UpDownController(SwapPlayerController, (int)CompPlusSettings::Player3ChosenPlayer, 1, 5, 3);
		if (CharacterP3Status != (int)CompPlusSettings::Player3ChosenPlayer) ChangeCharacter(3, (CompPlusSettings::ChosenPlayer)CharacterP3Status);
		int CharacterP4Status = UpDownController(SwapPlayerController, (int)CompPlusSettings::Player4ChosenPlayer, 1, 5, 4);
		if (CharacterP4Status != (int)CompPlusSettings::Player4ChosenPlayer) ChangeCharacter(4, (CompPlusSettings::ChosenPlayer)CharacterP4Status);

		//Ability NUD
		int AbilityP1Status = UpDownController(SwapAbilityController, (int)CompPlusSettings::Player1AbilitySet, 1, 5, 1);
		if (AbilityP1Status != (int)CompPlusSettings::Player1AbilitySet) ChangeAbility(1, (CompPlusSettings::ChosenPlayer)AbilityP1Status);
		int AbilityP2Status = UpDownController(SwapAbilityController, (int)CompPlusSettings::Player2AbilitySet, 1, 5, 2);
		if (AbilityP2Status != (int)CompPlusSettings::Player2AbilitySet) ChangeAbility(2, (CompPlusSettings::ChosenPlayer)AbilityP2Status);
		int AbilityP3Status = UpDownController(SwapAbilityController, (int)CompPlusSettings::Player3AbilitySet, 1, 5, 3);
		if (AbilityP3Status != (int)CompPlusSettings::Player3AbilitySet) ChangeAbility(3, (CompPlusSettings::ChosenPlayer)AbilityP3Status);
		int AbilityP4Status = UpDownController(SwapAbilityController, (int)CompPlusSettings::Player4AbilitySet, 1, 5, 4);
		if (AbilityP4Status != (int)CompPlusSettings::Player4AbilitySet) ChangeAbility(4, (CompPlusSettings::ChosenPlayer)AbilityP4Status);

		//Peelout Toggle
		bool PeeloutStateP1Status = ToggleController(PeeloutController, (bool)CompPlusSettings::Player1PeeloutAbility, 1);
		if (PeeloutStateP1Status != (bool)CompPlusSettings::Player1PeeloutAbility) CompPlusSettings::SetPeeloutAbility(1, PeeloutStateP1Status);
		bool PeeloutStateP2Status = ToggleController(PeeloutController, (bool)CompPlusSettings::Player2PeeloutAbility, 2);
		if (PeeloutStateP2Status != (bool)CompPlusSettings::Player2PeeloutAbility) CompPlusSettings::SetPeeloutAbility(2, PeeloutStateP2Status);
		bool PeeloutStateP3Status = ToggleController(PeeloutController, (bool)CompPlusSettings::Player3PeeloutAbility, 3);
		if (PeeloutStateP3Status != (bool)CompPlusSettings::Player3PeeloutAbility) CompPlusSettings::SetPeeloutAbility(3, PeeloutStateP3Status);
		bool PeeloutStateP4Status = ToggleController(PeeloutController, (bool)CompPlusSettings::Player4PeeloutAbility, 4);
		if (PeeloutStateP4Status != (bool)CompPlusSettings::Player4PeeloutAbility) CompPlusSettings::SetPeeloutAbility(4, PeeloutStateP4Status);

		//Inital Lives NUD
		int LivesStatus = UpDownController(LivesNUDController, CompPlusSettings::InitalLives, 0, 99, -1);
		if (LivesStatus != CompPlusSettings::InitalLives) SetInitalLives(LivesStatus);

		//Infinite Time Toggle
		bool InfiniteTimeStatus = ToggleController(RemoveTimeToggleController, CompPlusSettings::InfiniteTime, -1);
		if (InfiniteTimeStatus != CompPlusSettings::InfiniteTime) CompPlusSettings::InfiniteTime = InfiniteTimeStatus;

		//Infinite Rounds Toggle
		bool InfiniteRoundsStatus = ToggleController(InfiniteRoundsToggleController, CompPlusSettings::EndlessRounds, -1);
		if (InfiniteRoundsStatus != CompPlusSettings::EndlessRounds) CompPlusSettings::EndlessRounds = InfiniteRoundsStatus;

		//Announcer Type NUD
		int AnnouncerTypeStatus = UpDownController(AnnouncerTypeController, (int)CompPlusSettings::CurrentAnnouncer, 0, CompPlusSettings::NumberOfAnnouncers - 1, -1);
		if (AnnouncerTypeStatus != (int)CompPlusSettings::CurrentAnnouncer) CompPlusSettings::SetAnnouncer((CompPlusSettings::AnnouncerType)AnnouncerTypeStatus);

		//Victory Type NUD
		int VictoryTypeStatus = UpDownController(VictoryMethodSwapperController, (int)CompPlusSettings::VictoryStyle, 0, 1, -1);
		if (VictoryTypeStatus != (int)CompPlusSettings::VictoryStyle) CompPlusSettings::VictoryStyle = (CompPlusSettings::VictoryMode)VictoryTypeStatus;

		CompPlusSettings::FixAbilites(&Player1);
		CompPlusSettings::FixAbilites(&Player2);
		CompPlusSettings::FixAbilites(&Player3);
		CompPlusSettings::FixAbilites(&Player4);

		if (SettingWaitTimer != 0) SettingWaitTimer = SettingWaitTimer - 1;
	}

	#pragma endregion

	#pragma region Drawing

	void UpdateAbilitySwapperDisplay(int SlotID, int x, int y, CompPlusSettings::PlayerAbility Ability, int index)
	{
		EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

		Label3.Position.X = x;
		Label3.Position.Y = y;

        Label3.Text = (wchar_t*)Strings[index];

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

	void UpdatePlayerSwapperDisplay(int SlotID, int x, int y, CompPlusSettings::ChosenPlayer Player, int index)
	{
		EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

		Label3.Position.X = x;
		Label3.Position.Y = y;

        Label3.Text = (wchar_t*)Strings[index];
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

	void UpdateLevelSelectStatusDisplay(int State, int index)
	{
		EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SelectedLevelSelectText);

        Label3.Text = (wchar_t*)Strings[index];

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
		else if (State == 3)
		{
			char* on_text = (char*)"LSELECT: CHAOTIX";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)16;
		}
	}

	void UpdateToggleDisplay(int SlotID, int x, int y, bool State, int index)
	{
		EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

		Label3.Position.X = x;
		Label3.Position.Y = y;

        Label3.Text = (wchar_t*)Strings[index];

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

	void UpdateToggleDisplayInverted(int SlotID, int x, int y, bool State, int index)
	{
		EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

		Label3.Position.X = x;
		Label3.Position.Y = y;

        Label3.Text = (wchar_t*)Strings[index];

		if (!State)
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

    void UpdateGeneralDisplay(int SlotID, char* _text, int size, int index)
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

        Label3.Text = (wchar_t*)Strings[index];
        ConvertASCII2Unicode(Label3.Text, _text, strlen(_text), -32);
        Label3.TextLength = (WORD)size;
    }

	void UpdateGeneralDisplay(int SlotID, int x, int y, char* _text, int size, int index)
	{
		EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

		Label3.Position.X = x;
		Label3.Position.Y = y;

        Label3.Text = (wchar_t*)Strings[index];
		ConvertASCII2Unicode(Label3.Text, _text, strlen(_text), -32);
		Label3.TextLength = (WORD)size;
	}

	void UpdateAnnouncerDisplay(int SlotID, int x, int y, int index)
	{
		switch (CompPlusSettings::CurrentAnnouncer) 
		{
			case CompPlusSettings::Announcer_Default:
				UpdateGeneralDisplay(SlotID, x, y, (char*)"SONIC MANIA", 11, index);
				break;
			case CompPlusSettings::Announcer_Sonic2:
				UpdateGeneralDisplay(SlotID, x, y, (char*)"SONIC 2", 7, index);
				break;
			case CompPlusSettings::Announcer_Garrulous64:
				UpdateGeneralDisplay(SlotID, x, y, (char*)"GARRULOUS64", 11, index);
				break;
			case CompPlusSettings::Announcer_Angelthegamer:
				UpdateGeneralDisplay(SlotID, x, y, (char*)"ANGELTHEGAMER", 13, index);
				break;
			case CompPlusSettings::Announcer_Daniel:
				UpdateGeneralDisplay(SlotID, x, y, (char*)"DANIEL", 6, index);
				break;
			case CompPlusSettings::Announcer_Memes:
				UpdateGeneralDisplay(SlotID, x, y, (char*)"MEMES", 5, index);
				break;
		}
	}

	void UpdateVictoryMethodDisplay(int SlotID, int x, int y, int index)
	{
		switch (CompPlusSettings::VictoryStyle)
		{
			case CompPlusSettings::VictoryMode_Default:
				UpdateGeneralDisplay(SlotID, x, y, (char*)"ORIGINAL", 8, index);
				break;
			case CompPlusSettings::VictoryMode_Winner:
				UpdateGeneralDisplay(SlotID, x, y, (char*)"WINNER", 6, index);
				break;
		}
	}

	void UpdateLivesDisplay(int SlotID, int x, int y, int index)
	{
		if (CompPlusSettings::InfiniteLives)
		{
			UpdateGeneralDisplay(SlotID, x, y, (char*)"INFINITE", 8, index);
		}
		else
		{
			std::string s = std::to_string(CompPlusSettings::InitalLives);
			s.insert(0, "x");
			char* text = (char*)s.c_str();
			int size = (int)s.length();
			UpdateGeneralDisplay(SlotID, x, y, text, size, index);
		}
	}

    int RoundsCounterText = 69;
    int P1_WinsCounterText = 267;
    int P2_WinsCounterText = 268;
    int P3_WinsCounterText = 269;
    int P4_WinsCounterText = 270;

    int P1_WinsCounterText_Board = 280;
    int P2_WinsCounterText_Board = 281;
    int P3_WinsCounterText_Board = 282;
    int P4_WinsCounterText_Board = 283;

    int P1_TimeCounterText_Board = 284;
    int P2_TimeCounterText_Board = 285;
    int P3_TimeCounterText_Board = 286;
    int P4_TimeCounterText_Board = 287;

    int P1_ScoreCounterText_Board = 288;
    int P2_ScoreCounterText_Board = 289;
    int P3_ScoreCounterText_Board = 290;
    int P4_ScoreCounterText_Board = 291;

    int P1_RingsCounterText_Board = 292;
    int P2_RingsCounterText_Board = 293;
    int P3_RingsCounterText_Board = 294;
    int P4_RingsCounterText_Board = 295;

    int P1_ItemsCounterText_Board = 296;
    int P2_ItemsCounterText_Board = 297;
    int P3_ItemsCounterText_Board = 298;
    int P4_ItemsCounterText_Board = 299;

    int P1_TotalRingsCounterText_Board = 301;
    int P2_TotalRingsCounterText_Board = 302;
    int P3_TotalRingsCounterText_Board = 303;
    int P4_TotalRingsCounterText_Board = 304;

    void UpdateScoreboardDisplays(int lastIndex) 
    {
        std::string roundNumber = std::to_string(SonicMania::Options->CompetitionSession.CurrentRound) + "\\" + std::to_string(SonicMania::Options->CompetitionSession.TotalRounds);
        UpdateGeneralDisplay(RoundsCounterText, (char*)roundNumber.c_str(), roundNumber.length(), lastIndex);
        lastIndex++;

        std::string winsP1 = std::to_string(SonicMania::Options->CompetitionSession.Wins_P1);
        UpdateGeneralDisplay(P1_WinsCounterText, (char*)winsP1.c_str(), winsP1.length(), lastIndex);
        lastIndex++;
        std::string winsP2 = std::to_string(SonicMania::Options->CompetitionSession.Wins_P2);
        UpdateGeneralDisplay(P2_WinsCounterText, (char*)winsP2.c_str(), winsP2.length(), lastIndex);
        lastIndex++;
        std::string winsP3 = std::to_string(SonicMania::Options->CompetitionSession.Wins_P3);
        UpdateGeneralDisplay(P3_WinsCounterText, (char*)winsP3.c_str(), winsP3.length(), lastIndex);
        lastIndex++;
        std::string winsP4 = std::to_string(SonicMania::Options->CompetitionSession.Wins_P4);
        UpdateGeneralDisplay(P4_WinsCounterText, (char*)winsP4.c_str(), winsP4.length(), lastIndex);
        lastIndex++;

        UpdateGeneralDisplay(P1_WinsCounterText_Board, (char*)winsP1.c_str(), winsP1.length(), lastIndex);
        lastIndex++;
        UpdateGeneralDisplay(P2_WinsCounterText_Board, (char*)winsP2.c_str(), winsP2.length(), lastIndex);
        lastIndex++;
        UpdateGeneralDisplay(P3_WinsCounterText_Board, (char*)winsP3.c_str(), winsP3.length(), lastIndex);
        lastIndex++;
        UpdateGeneralDisplay(P4_WinsCounterText_Board, (char*)winsP4.c_str(), winsP4.length(), lastIndex);
        lastIndex++;

        std::string timeP1 = std::to_string(SonicMania::Options->CompetitionSession.TimeMinutes_P1) + "\'" + std::to_string(SonicMania::Options->CompetitionSession.TimeSeconds_P1) + "\"" + std::to_string(SonicMania::Options->CompetitionSession.TimeMilliseconds_P1);
        UpdateGeneralDisplay(P1_TimeCounterText_Board, (char*)timeP1.c_str(), timeP1.length(), lastIndex);
        lastIndex++;
        std::string timeP2 = std::to_string(SonicMania::Options->CompetitionSession.TimeMinutes_P2) + "\'" + std::to_string(SonicMania::Options->CompetitionSession.TimeSeconds_P2) + "\"" + std::to_string(SonicMania::Options->CompetitionSession.TimeMilliseconds_P2);
        UpdateGeneralDisplay(P2_TimeCounterText_Board, (char*)timeP2.c_str(), timeP2.length(), lastIndex);
        lastIndex++;
        std::string timeP3 = std::to_string(SonicMania::Options->CompetitionSession.TimeMinutes_P3) + "\'" + std::to_string(SonicMania::Options->CompetitionSession.TimeSeconds_P3) + "\"" + std::to_string(SonicMania::Options->CompetitionSession.TimeMilliseconds_P3);
        UpdateGeneralDisplay(P3_TimeCounterText_Board, (char*)timeP3.c_str(), timeP3.length(), lastIndex);
        lastIndex++;
        std::string timeP4 = std::to_string(SonicMania::Options->CompetitionSession.TimeMinutes_P4) + "\'" + std::to_string(SonicMania::Options->CompetitionSession.TimeSeconds_P4) + "\"" + std::to_string(SonicMania::Options->CompetitionSession.TimeMilliseconds_P4);
        UpdateGeneralDisplay(P4_TimeCounterText_Board, (char*)timeP4.c_str(), timeP4.length(), lastIndex);
        lastIndex++;

        std::string scoreP1 = std::to_string(SonicMania::Options->CompetitionSession.Score_P1);
        UpdateGeneralDisplay(P1_ScoreCounterText_Board, (char*)scoreP1.c_str(), scoreP1.length(), lastIndex);
        lastIndex++;
        std::string scoreP2 = std::to_string(SonicMania::Options->CompetitionSession.Score_P2);
        UpdateGeneralDisplay(P2_ScoreCounterText_Board, (char*)scoreP2.c_str(), scoreP2.length(), lastIndex);
        lastIndex++;
        std::string scoreP3 = std::to_string(SonicMania::Options->CompetitionSession.Score_P3);
        UpdateGeneralDisplay(P3_ScoreCounterText_Board, (char*)scoreP3.c_str(), scoreP3.length(), lastIndex);
        lastIndex++;
        std::string scoreP4 = std::to_string(SonicMania::Options->CompetitionSession.Score_P4);
        UpdateGeneralDisplay(P4_ScoreCounterText_Board, (char*)scoreP4.c_str(), scoreP4.length(), lastIndex);
        lastIndex++;

        std::string ringsP1 = std::to_string(SonicMania::Options->CompetitionSession.Rings_P1);
        UpdateGeneralDisplay(P1_RingsCounterText_Board, (char*)ringsP1.c_str(), ringsP1.length(), lastIndex);
        lastIndex++;
        std::string ringsP2 = std::to_string(SonicMania::Options->CompetitionSession.Rings_P2);
        UpdateGeneralDisplay(P2_RingsCounterText_Board, (char*)ringsP2.c_str(), ringsP2.length(), lastIndex);
        lastIndex++;
        std::string ringsP3 = std::to_string(SonicMania::Options->CompetitionSession.Rings_P3);
        UpdateGeneralDisplay(P3_RingsCounterText_Board, (char*)ringsP3.c_str(), ringsP3.length(), lastIndex);
        lastIndex++;
        std::string ringsP4 = std::to_string(SonicMania::Options->CompetitionSession.Rings_P4);
        UpdateGeneralDisplay(P4_RingsCounterText_Board, (char*)ringsP4.c_str(), ringsP4.length(), lastIndex);
        lastIndex++;

        std::string itemsP1 = std::to_string(SonicMania::Options->CompetitionSession.Items_P1);
        UpdateGeneralDisplay(P1_ItemsCounterText_Board, (char*)itemsP1.c_str(), itemsP1.length(), lastIndex);
        lastIndex++;
        std::string itemsP2 = std::to_string(SonicMania::Options->CompetitionSession.Items_P2);
        UpdateGeneralDisplay(P2_ItemsCounterText_Board, (char*)itemsP2.c_str(), itemsP2.length(), lastIndex);
        lastIndex++;
        std::string itemsP3 = std::to_string(SonicMania::Options->CompetitionSession.Items_P3);
        UpdateGeneralDisplay(P3_ItemsCounterText_Board, (char*)itemsP3.c_str(), itemsP3.length(), lastIndex);
        lastIndex++;
        std::string itemsP4 = std::to_string(SonicMania::Options->CompetitionSession.Items_P4);
        UpdateGeneralDisplay(P4_ItemsCounterText_Board, (char*)itemsP4.c_str(), itemsP4.length(), lastIndex);
        lastIndex++;


        std::string totalringsP1 = std::to_string(SonicMania::Options->CompetitionSession.TotalRings_P1);
        UpdateGeneralDisplay(P1_TotalRingsCounterText_Board, (char*)totalringsP1.c_str(), totalringsP1.length(), lastIndex);
        lastIndex++;
        std::string totalringsP2 = std::to_string(SonicMania::Options->CompetitionSession.TotalRings_P2);
        UpdateGeneralDisplay(P2_TotalRingsCounterText_Board, (char*)totalringsP2.c_str(), totalringsP2.length(), lastIndex);
        lastIndex++;
        std::string totalringsP3 = std::to_string(SonicMania::Options->CompetitionSession.TotalRings_P3);
        UpdateGeneralDisplay(P3_TotalRingsCounterText_Board, (char*)totalringsP3.c_str(), totalringsP3.length(), lastIndex);
        lastIndex++;
        std::string totalringsP4 = std::to_string(SonicMania::Options->CompetitionSession.TotalRings_P4);
        UpdateGeneralDisplay(P4_TotalRingsCounterText_Board, (char*)totalringsP4.c_str(), totalringsP4.length(), lastIndex);
        lastIndex++;
    }

	void UpdateHUBDisplays()
	{
		//Character Select Display
		UpdatePlayerSwapperDisplay(SwapPlayerText_P1, Pos_SwapPlayerText.X, Pos_SwapPlayerText.Y - 48, CompPlusSettings::Player1ChosenPlayer, 0);
		UpdatePlayerSwapperDisplay(SwapPlayerText_P2, Pos_SwapPlayerText.X, Pos_SwapPlayerText.Y - 32, CompPlusSettings::Player2ChosenPlayer, 1);
		UpdatePlayerSwapperDisplay(SwapPlayerText_P3, Pos_SwapPlayerText.X, Pos_SwapPlayerText.Y - 16, CompPlusSettings::Player3ChosenPlayer, 2);
		UpdatePlayerSwapperDisplay(SwapPlayerText_P4, Pos_SwapPlayerText.X, Pos_SwapPlayerText.Y - 0, CompPlusSettings::Player4ChosenPlayer, 3);
		//Player Ability Display
		UpdateAbilitySwapperDisplay(SwapAbilityText_P1, Pos_SwapAbilityText.X, Pos_SwapAbilityText.Y - 48, CompPlusSettings::Player1AbilitySet, 4);
		UpdateAbilitySwapperDisplay(SwapAbilityText_P2, Pos_SwapAbilityText.X, Pos_SwapAbilityText.Y - 32, CompPlusSettings::Player2AbilitySet, 5);
		UpdateAbilitySwapperDisplay(SwapAbilityText_P3, Pos_SwapAbilityText.X, Pos_SwapAbilityText.Y - 16, CompPlusSettings::Player3AbilitySet, 6);
		UpdateAbilitySwapperDisplay(SwapAbilityText_P4, Pos_SwapAbilityText.X, Pos_SwapAbilityText.Y - 0, CompPlusSettings::Player4AbilitySet, 7);
		//Peelout Ability Display
		UpdateToggleDisplay(PeeloutToggleText_P1, Pos_PeeloutText.X, Pos_PeeloutText.Y - 48, CompPlusSettings::Player1PeeloutAbility, 8);
		UpdateToggleDisplay(PeeloutToggleText_P2, Pos_PeeloutText.X, Pos_PeeloutText.Y - 32, CompPlusSettings::Player2PeeloutAbility, 9);
		UpdateToggleDisplay(PeeloutToggleText_P3, Pos_PeeloutText.X, Pos_PeeloutText.Y - 16, CompPlusSettings::Player3PeeloutAbility, 10);
		UpdateToggleDisplay(PeeloutToggleText_P4, Pos_PeeloutText.X, Pos_PeeloutText.Y - 0, CompPlusSettings::Player4PeeloutAbility, 11);
		//Dropdash Display
		UpdateToggleDisplay(DropDashToggleText, Pos_DropDashText.X, Pos_DropDashText.Y, CompPlusSettings::DropdashAbility, 12);
		//Insta-Sheild Display
		UpdateToggleDisplay(InstaSheildToggleText, Pos_InstaSheildText.X, Pos_InstaSheildText.Y, CompPlusSettings::InstaSheildAbility, 13);
		//Debug Mode Display
		UpdateToggleDisplay(DebugModeText, Pos_DebugModeText.X, Pos_DebugModeText.Y, CompPlusSettings::EnableDebugMode, 14);
		//Dev Mode Display
		UpdateToggleDisplay(DevModeText, Pos_DevModeText.X, Pos_DevModeText.Y, CompPlusSettings::EnableDevMode, 15);
		//Level Select Display
		UpdateLevelSelectStatusDisplay(CurrentLevelSelect, 16);
		//Lives Display
		UpdateLivesDisplay(LivesNUDText, Pos_LivesNUDText.X, Pos_LivesNUDText.Y, 17);
		//Remove Time Display
		UpdateToggleDisplayInverted(RemoveTimeToggleText, Pos_RemoveTimeText.X, Pos_RemoveTimeText.Y, CompPlusSettings::InfiniteTime, 18);
		//Infinite Rounds Display
		UpdateToggleDisplay(InfiniteRoundsToggleText, Pos_InfiniteRoundsText.X, Pos_InfiniteRoundsText.Y, CompPlusSettings::EndlessRounds, 19);
		//Announcer Type Display
		UpdateAnnouncerDisplay(AnnouncerTypeText, Pos_AnnouncerTypeText.X, Pos_AnnouncerTypeText.Y, 20);
		//Victory Method Display
		UpdateVictoryMethodDisplay(VictoryMethodSwapperText, Pos_VictoryMethodText.X, Pos_VictoryMethodText.Y, 21);
        //Scoreboard Displays
        UpdateScoreboardDisplays(22);
	}

	void UpdateHUBPositions()
	{
		//X: 11264 Y: 11123

		int OffsetX = 0;
		int OffsetY = 85;

		int OffsetY_2 = 45;

		Entity& E1 = *GetEntityFromSceneSlot<Entity>(SwapPlayerController);
		Entity& E2 = *GetEntityFromSceneSlot<Entity>(SwapAbilityController);
		Entity& E3 = *GetEntityFromSceneSlot<Entity>(DropDashController);
		Entity& E4 = *GetEntityFromSceneSlot<Entity>(PeeloutController);
		Entity& E5 = *GetEntityFromSceneSlot<Entity>(InstaSheildController);
		Entity& E6 = *GetEntityFromSceneSlot<Entity>(DebugModeController);
		Entity& E7 = *GetEntityFromSceneSlot<Entity>(DevModeController);
		Entity& E8 = *GetEntityFromSceneSlot<Entity>(LivesNUDController);
		Entity& E9 = *GetEntityFromSceneSlot<Entity>(InfiniteRoundsToggleController);
		Entity& E10 = *GetEntityFromSceneSlot<Entity>(AnnouncerTypeController);
		Entity& E11 = *GetEntityFromSceneSlot<Entity>(VictoryMethodSwapperController);
		Entity& E12 = *GetEntityFromSceneSlot<Entity>(RemoveTimeToggleController);

		Pos_SwapPlayerText.X = E1.Position.X + OffsetX;
		Pos_SwapPlayerText.Y = E1.Position.Y + OffsetY;

		Pos_SwapAbilityText.X = E2.Position.X + OffsetX;
		Pos_SwapAbilityText.Y = E2.Position.Y + OffsetY;

		Pos_PeeloutText.X = E4.Position.X + OffsetX;
		Pos_PeeloutText.Y = E4.Position.Y + OffsetY;

		Pos_InstaSheildText.X = E5.Position.X + OffsetX;
		Pos_InstaSheildText.Y = E5.Position.Y + OffsetY_2;

		Pos_DropDashText.X = E3.Position.X + OffsetX;
		Pos_DropDashText.Y = E3.Position.Y + OffsetY_2;

		Pos_DebugModeText.X = E6.Position.X + OffsetX;
		Pos_DebugModeText.Y = E6.Position.Y + OffsetY_2;

		Pos_DevModeText.X = E7.Position.X + OffsetX;
		Pos_DevModeText.Y = E7.Position.Y + OffsetY_2;

		Pos_LivesNUDText.X = E8.Position.X + OffsetX;
		Pos_LivesNUDText.Y = E8.Position.Y + OffsetY_2;

		Pos_InfiniteRoundsText.X = E9.Position.X + OffsetX;
		Pos_InfiniteRoundsText.Y = E9.Position.Y + OffsetY_2;

		Pos_AnnouncerTypeText.X = E10.Position.X + OffsetX;
		Pos_AnnouncerTypeText.Y = E10.Position.Y + OffsetY_2;

		Pos_VictoryMethodText.X = E11.Position.X + OffsetX;
		Pos_VictoryMethodText.Y = E11.Position.Y + OffsetY_2;

		Pos_RemoveTimeText.X = E12.Position.X + OffsetX;
		Pos_RemoveTimeText.Y = E12.Position.Y + OffsetY_2;
	}

	#pragma endregion

	void SetHUBVisualSettings() 
	{
		//Disable Timer
		SonicMania::Timer.ResetTimer();
		if (SonicMania::Timer.Enabled)
		{
			SonicMania::Timer.Enabled = false;
		}

		//Disable HUD
		WriteData((BYTE*)(baseAddress + 0x47B065), (BYTE)0);
	}



	void UpdateHUBWorld() 
	{	
		SetHUBVisualSettings();


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
		else if (CurrentLevelSelect == 3) LoadLevel_IZ("CPCXLS");
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

    void Init()
    {
        for (int i = 0; i < 100; ++i)
            Strings[i] = (wchar_t*)malloc(128);
    }


}