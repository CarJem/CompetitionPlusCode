#include "stdafx.h"
#include "HubWorld.h"
#include "ManiaExt.h"
#include "SonicMania.h"
#include "CompPlus_Settings.h"
#include "CompPlus_Common.h"
#include <string>
#include <sstream>
#include "CompPlus_Scoring.h"

namespace CompPlus_HubWorld
{
	using namespace SonicMania;
	using namespace CompPlus_Core;
	using namespace CompPlus_Common;

	#pragma region Reserved Slot IDs

	int EnterLSelectButton = 67;
    int AltSpawnSlotID = 439;
    int PlayerSpawnSlotID = 68;

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
    int HurryTimerToggleController = 475;
    int ItemBoxModeController = 180;
    int NumberOfRoundsController = 352;

	int AnnouncerTypeText = 132;
	int InfiniteRoundsToggleText = 136;
	int VictoryMethodSwapperText = 134;
	int LivesNUDText = 127;
	int RemoveTimeToggleText = 130;
    int HurryTimerToggleText = 478;
    int ItemBoxModeText = 206;
    int NumberOfRoundsText = 351;

    int VSModeTextSlot = 361;
    int WinsTallyTextSlot = 362;

	// Developer Settings
	int DevModeText = 138;
	int DebugModeText = 139;

	int DevModeController = 184;
	int DebugModeController = 185;
	// ---------------------------

    int SelectedLevelSelectText = 205;

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

    int RespawnObject_FirstPlace = 114;
    int RespawnObject_SecondPlace = 111;
    int RespawnObject_ThirdPlace = 105;
    int RespawnObject_FouthPlace = 112;

    int P1_HUD_1 = 311;
    int P1_HUD_2 = 313;
    int P1_HUD_3 = 314;
    int P1_HUD_4 = 364;

    int P2_HUD_1 = 315;
    int P2_HUD_2 = 316;
    int P2_HUD_3 = 317;
    int P2_HUD_4 = 365;

    int P3_HUD_1 = 318;
    int P3_HUD_2 = 319;
    int P3_HUD_3 = 320;
    int P3_HUD_4 = 366;

    int P4_HUD_1 = 321;
    int P4_HUD_2 = 322;
    int P4_HUD_3 = 323;
    int P4_HUD_4 = 367;

    int WarpSlotID_PlayerSettings = 80;
    int WarpSlotID_OtherSettings = 81;
    int WarpSlotID_Ranking = 79;
    int WarpSlotID_LevelSelect = 75;
    int WarpSlotID_ReturnToLast = 74;

    int WarpDestSlotID_PlayerSettings = 60;
    int WarpDestSlotID_OtherSettings = 61;
    int WarpDestSlotID_Ranking = 62;
    int WarpDestSlotID_LevelSelect = 72;
    int WarpDestSlotID_WarpHub = 73;

	#pragma endregion

    #pragma region Warp Room Variables

    bool P1_IsInWarpRoom = false;
    bool P2_IsInWarpRoom = false;
    bool P3_IsInWarpRoom = false;
    bool P4_IsInWarpRoom = false;

    int WarpTimerMax = 512;
    int WarpTimerCurrent_P1 = 0;
    int WarpTimerCurrent_P2 = 0;
    int WarpTimerCurrent_P3 = 0;
    int WarpTimerCurrent_P4 = 0;

    bool P1_IsInWarpLoop = false;
    bool P2_IsInWarpLoop = false;
    bool P3_IsInWarpLoop = false;
    bool P4_IsInWarpLoop = false;

    int P1_WarpAlpha = 255;
    int P2_WarpAlpha = 255;
    int P3_WarpAlpha = 255;
    int P4_WarpAlpha = 255;

    INT_Position WarpDest_PlayerSettings = INT_Position(0, 0);
    INT_Position WarpDest_OtherSettings = INT_Position(0, 0);
    INT_Position WarpDest_Ranking = INT_Position(0, 0);
    INT_Position WarpDest_LevelSelect = INT_Position(0, 0);
    INT_Position WarpDest_WarpHub = INT_Position(0, 0);

    INT_Position P1_LastWarpPosition = INT_Position(0, 0);
    INT_Position P2_LastWarpPosition = INT_Position(0, 0);
    INT_Position P3_LastWarpPosition = INT_Position(0, 0);
    INT_Position P4_LastWarpPosition = INT_Position(0, 0);

    INT_Position P1_WarpQueue = INT_Position(0, 0);
    INT_Position P2_WarpQueue = INT_Position(0, 0);
    INT_Position P3_WarpQueue = INT_Position(0, 0);
    INT_Position P4_WarpQueue = INT_Position(0, 0);

    #pragma endregion

	#pragma region Reserved Entity Positions

	INT_Position Pos_OutOfBounds = INT_Position(-10000, -10000);
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
    INT_Position Pos_ItemBoxModeText = INT_Position();
    INT_Position Pos_NumberOfRoundsText = INT_Position();
    INT_Position Pos_HurryTimerToggleText = INT_Position();

	#pragma endregion

	#pragma region Extra Region

	#pragma endregion

	#pragma region Other Variables

    static wchar_t* Strings[120];
	bool isSettingChanged = false;	//Controller Press Detection
	bool LevelSelected = false;
	bool LevelSelectedWarpSoundPlayed = false;
	int SceneLoadWaitTimer = 0;
	int SceneLoadWaitMax = 100;
	int SettingWaitTimer = 100;
    bool isRestart = true;
    bool CreditsSelected = false;

    int P1_HUDAlpha = 255;
    int P2_HUDAlpha = 255;
    int P3_HUDAlpha = 255;
    int P4_HUDAlpha = 255;

	#pragma endregion

	#pragma region Controller Trigger Methods


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

	bool ToggleController(int ControlSlotID, bool OldValue)
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

			if (Player->InRange(x1, y1, x2, y2) && Player->Up && !isSettingChanged)
			{
				if (OldValue == true) NewValue = false;
				else NewValue = true;
				CompPlus_Common::PlayMenuMoveSoundFX(false);
				isSettingChanged = true;
				SettingWaitTimerActivate();
			}
			else if (Player->InRange(x1, y1, x2, y2) && Player->Down && !isSettingChanged)
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
            
            if (isSettingChanged) return NewValue;
		}

		return NewValue;
	}

	int UpDownController(int ControlSlotID, int OldValue, int Min, int Max)
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

			if (Player->InRange(x1, y1, x2, y2) && Player->Up && !isSettingChanged)
			{
				if (OldValue + 1 > Max) NewValue = Min;
				else NewValue = OldValue + 1;
				CompPlus_Common::PlayMenuMoveSoundFX(false);
				isSettingChanged = true;
				SettingWaitTimerActivate();
			}
			else if (Player->InRange(x1, y1, x2, y2) && Player->Down && !isSettingChanged)
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
            
            if (isSettingChanged) return NewValue;
		}

		return NewValue;
	}

    bool ToggleController(int ControlSlotID, bool OldValue, int RealID)
    {
        Entity& Controller = *GetEntityFromSceneSlot<Entity>(ControlSlotID);

        int x1 = Controller.Position.X - GetControllerX1();
        int y1 = Controller.Position.Y - GetControllerY1();
        int x2 = Controller.Position.X + GetControllerX2();
        int y2 = Controller.Position.Y + GetControllerY2();
        bool NewValue = OldValue;

        SonicMania::EntityPlayer* Player;
        if (RealID == 1) Player = &Player1;
        else if (RealID == 2) Player = &Player2;
        else if (RealID == 3) Player = &Player3;
        else if (RealID == 4) Player = &Player4;
        else Player = &Player1;

        if (Player->InRange(x1, y1, x2, y2) && Player->Up && !isSettingChanged)
        {
            if (OldValue == true) NewValue = false;
            else NewValue = true;
            CompPlus_Common::PlayMenuMoveSoundFX(false);
            isSettingChanged = true;
            SettingWaitTimerActivate();
        }
        else if (Player->InRange(x1, y1, x2, y2) && Player->Down && !isSettingChanged)
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

        return NewValue;
    }

    int UpDownController(int ControlSlotID, int OldValue, int Min, int Max, int RealID, bool& isUp)
    {
        Entity& Controller = *GetEntityFromSceneSlot<Entity>(ControlSlotID);

        int x1 = Controller.Position.X - GetControllerX1();
        int y1 = Controller.Position.Y - GetControllerY1();
        int x2 = Controller.Position.X + GetControllerX2();
        int y2 = Controller.Position.Y + GetControllerY2();
        int NewValue = OldValue;

        SonicMania::EntityPlayer* Player;
        if (RealID == 1) Player = &Player1;
        else if (RealID == 2) Player = &Player2;
        else if (RealID == 3) Player = &Player3;
        else if (RealID == 4) Player = &Player4;
        else Player = &Player1;

        if (Player->InRange(x1, y1, x2, y2) && Player->Up && !isSettingChanged)
        {
            if (OldValue + 1 > Max) NewValue = Min;
            else NewValue = OldValue + 1;
            CompPlus_Common::PlayMenuMoveSoundFX(false);
            isSettingChanged = true;
            SettingWaitTimerActivate();
            isUp = true;
        }
        else if (Player->InRange(x1, y1, x2, y2) && Player->Down && !isSettingChanged)
        {
            if (OldValue - 1 < Min) NewValue = Max;
            else NewValue = OldValue - 1;
            CompPlus_Common::PlayMenuMoveSoundFX(false);
            isSettingChanged = true;
            SettingWaitTimerActivate();
            isUp = false;
        }
        else if (!Player->Up && !Player->Down && isSettingChanged)
        {
            if (SettingWaitTimer == 0) isSettingChanged = false;
        }

        return NewValue;
    }

	void ChangeCharacter(int PlayerID, int Value) 
	{
		CompPlus_Settings::UpdatePlayer(PlayerID, (CompPlus_Settings::ChosenPlayer)Value, true);
		CompPlus_Settings::SetAbility(PlayerID, (CompPlus_Settings::PlayerAbility)Value, true);
	}

	void ChangeAbility(int PlayerID, int Value, bool isUp)
	{
        bool CanForce = true;

        CompPlus_Settings::PlayerAbility Ability = (CompPlus_Settings::PlayerAbility)Value;
        CompPlus_Settings::ChosenPlayer ChosenPlayer;

        if (PlayerID == 4) ChosenPlayer = CompPlus_Settings::Player4ChosenPlayer;
        if (PlayerID == 3) ChosenPlayer = CompPlus_Settings::Player3ChosenPlayer;
        if (PlayerID == 2) ChosenPlayer = CompPlus_Settings::Player2ChosenPlayer;
        else ChosenPlayer = CompPlus_Settings::Player1ChosenPlayer;
        
        CompPlus_Settings::SetAbility(PlayerID, Ability, CanForce);

        if (ChosenPlayer == CompPlus_Settings::ChosenPlayer_Sonic)
        {
            if (isUp)
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Compatibility, CanForce);
            }
            else
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
            }
        }
        if (ChosenPlayer == CompPlus_Settings::ChosenPlayer_Tails)
        {
            if (isUp)
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Tails, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Compatibility, CanForce);
            }
            else
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Tails, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Tails, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
            }
        }
        if (ChosenPlayer == CompPlus_Settings::ChosenPlayer_Knuckles)
        {
            if (isUp)
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Knuckles, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Knuckles, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Compatibility, CanForce);
            }
            else
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Knuckles, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
            }

        }
        if (ChosenPlayer == CompPlus_Settings::ChosenPlayer_Mighty)
        {
            if (isUp)
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Compatibility, CanForce);
            }
            else
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
            }
        }
        if (ChosenPlayer == CompPlus_Settings::ChosenPlayer_Ray)
        {
            if (isUp)
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Ray, CanForce);
            }
            else
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Ray, CanForce);
            }
        }
	}

	void CheckSettings()
	{
		//Debug Mode Toggle
		bool DebugStatus = ToggleController(DebugModeController, CompPlus_Settings::EnableDebugMode);
		if (DebugStatus != CompPlus_Settings::EnableDebugMode) CompPlus_Settings::EnableDebugMode = DebugStatus;

		//Dev Mode Toggle
		bool DevStatus = ToggleController(DevModeController, CompPlus_Settings::EnableDevMode);
		if (DevStatus != CompPlus_Settings::EnableDevMode) CompPlus_Settings::EnableDevMode = DebugStatus;

		//Level Select NUD
		int LevelStatus = UpDownController(SwapLevelSelectController, CompPlus_Settings::CurrentLevelSelect, 0, 3);
		if (LevelStatus != CompPlus_Settings::CurrentLevelSelect) CompPlus_Settings::CurrentLevelSelect = LevelStatus;
		LevelStatus = UpDownController(SwapLevelSelectController2, CompPlus_Settings::CurrentLevelSelect, 0, 3);
		if (LevelStatus != CompPlus_Settings::CurrentLevelSelect) CompPlus_Settings::CurrentLevelSelect = LevelStatus;

        if (LevelStatus != CompPlus_Settings::CurrentLevelSelect) CompPlus_Settings::SaveSettings();

		//Insta-Sheild Toggle
		bool InstaSheildStatus = ToggleController(InstaSheildController, CompPlus_Settings::InstaSheildAbility);
		if (InstaSheildStatus != CompPlus_Settings::InstaSheildAbility) CompPlus_Settings::SetInstaSheildAbility(InstaSheildStatus);

		//Dropdash Toggle
		bool DropdashStatus = ToggleController(DropDashController, CompPlus_Settings::DropdashAbility);
		if (DropdashStatus != CompPlus_Settings::DropdashAbility) CompPlus_Settings::SetDropdashAbility(DropdashStatus);

		//Character NUD
        bool isUp = false;
		int CharacterP1Status = UpDownController(SwapPlayerController, (int)CompPlus_Settings::Player1ChosenPlayer, 1, 5, 1, isUp);
		if (CharacterP1Status != (int)CompPlus_Settings::Player1ChosenPlayer) ChangeCharacter(1, (CompPlus_Settings::ChosenPlayer)CharacterP1Status);
		int CharacterP2Status = UpDownController(SwapPlayerController, (int)CompPlus_Settings::Player2ChosenPlayer, 1, 5, 2, isUp);
		if (CharacterP2Status != (int)CompPlus_Settings::Player2ChosenPlayer) ChangeCharacter(2, (CompPlus_Settings::ChosenPlayer)CharacterP2Status);
		int CharacterP3Status = UpDownController(SwapPlayerController, (int)CompPlus_Settings::Player3ChosenPlayer, 1, 5, 3, isUp);
		if (CharacterP3Status != (int)CompPlus_Settings::Player3ChosenPlayer) ChangeCharacter(3, (CompPlus_Settings::ChosenPlayer)CharacterP3Status);
		int CharacterP4Status = UpDownController(SwapPlayerController, (int)CompPlus_Settings::Player4ChosenPlayer, 1, 5, 4, isUp);
		if (CharacterP4Status != (int)CompPlus_Settings::Player4ChosenPlayer) ChangeCharacter(4, (CompPlus_Settings::ChosenPlayer)CharacterP4Status);

		//Ability NUD
		int AbilityP1Status = UpDownController(SwapAbilityController, (int)CompPlus_Settings::Player1AbilitySet, 0, 5, 1, isUp);
		if (AbilityP1Status != (int)CompPlus_Settings::Player1AbilitySet) ChangeAbility(1, (CompPlus_Settings::PlayerAbility)AbilityP1Status, isUp);
		int AbilityP2Status = UpDownController(SwapAbilityController, (int)CompPlus_Settings::Player2AbilitySet, 0, 5, 2, isUp);
		if (AbilityP2Status != (int)CompPlus_Settings::Player2AbilitySet) ChangeAbility(2, (CompPlus_Settings::PlayerAbility)AbilityP2Status, isUp);
		int AbilityP3Status = UpDownController(SwapAbilityController, (int)CompPlus_Settings::Player3AbilitySet, 0, 5, 3, isUp);
		if (AbilityP3Status != (int)CompPlus_Settings::Player3AbilitySet) ChangeAbility(3, (CompPlus_Settings::PlayerAbility)AbilityP3Status, isUp);
		int AbilityP4Status = UpDownController(SwapAbilityController, (int)CompPlus_Settings::Player4AbilitySet, 0, 5, 4, isUp);
		if (AbilityP4Status != (int)CompPlus_Settings::Player4AbilitySet) ChangeAbility(4, (CompPlus_Settings::PlayerAbility)AbilityP4Status, isUp);

		//Peelout Toggle
        int PeeloutStateP1Status = UpDownController(PeeloutController, (int)CompPlus_Settings::Player1PeeloutAbility, 0, 2, 1, isUp);
		if (PeeloutStateP1Status != (int)CompPlus_Settings::Player1PeeloutAbility) CompPlus_Settings::SetPeeloutAbility(1, (CompPlus_Settings::ThreeStateBool)PeeloutStateP1Status);
        int PeeloutStateP2Status = UpDownController(PeeloutController, (int)CompPlus_Settings::Player2PeeloutAbility, 0, 2, 2, isUp);
		if (PeeloutStateP2Status != (int)CompPlus_Settings::Player2PeeloutAbility) CompPlus_Settings::SetPeeloutAbility(2, (CompPlus_Settings::ThreeStateBool)PeeloutStateP2Status);
        int PeeloutStateP3Status = UpDownController(PeeloutController, (int)CompPlus_Settings::Player3PeeloutAbility, 0, 2, 3, isUp);
		if (PeeloutStateP3Status != (int)CompPlus_Settings::Player3PeeloutAbility) CompPlus_Settings::SetPeeloutAbility(3, (CompPlus_Settings::ThreeStateBool)PeeloutStateP3Status);
		int PeeloutStateP4Status = UpDownController(PeeloutController, (int)CompPlus_Settings::Player4PeeloutAbility, 0, 2, 4, isUp);
		if (PeeloutStateP4Status != (int)CompPlus_Settings::Player4PeeloutAbility) CompPlus_Settings::SetPeeloutAbility(4, (CompPlus_Settings::ThreeStateBool)PeeloutStateP4Status);

		//Inital Lives NUD
		int LivesStatus = UpDownController(LivesNUDController, CompPlus_Settings::InitalLives, 1, 100);
		if (LivesStatus != CompPlus_Settings::InitalLives) CompPlus_Settings::SetInitalLives(LivesStatus);

		//Infinite Time Toggle
		bool InfiniteTimeStatus = ToggleController(RemoveTimeToggleController, CompPlus_Settings::TimeLimit);
		if (InfiniteTimeStatus != CompPlus_Settings::TimeLimit) CompPlus_Settings::SetTimeLimit(InfiniteTimeStatus);

        //Hurry Timer Toggle
        bool HurryTimerStatus = ToggleController(HurryTimerToggleController, CompPlus_Settings::NoHurryUpTimer);
        if (HurryTimerStatus != CompPlus_Settings::NoHurryUpTimer) CompPlus_Settings::SetHurryTimer(HurryTimerStatus);

		//Infinite Rounds Toggle
		bool InfiniteRoundsStatus = ToggleController(InfiniteRoundsToggleController, CompPlus_Settings::EndlessRounds);
		if (InfiniteRoundsStatus != CompPlus_Settings::EndlessRounds) CompPlus_Settings::SetEndlessRounds(InfiniteRoundsStatus);

		//Announcer Type NUD
		int AnnouncerTypeStatus = UpDownController(AnnouncerTypeController, (int)CompPlus_Settings::CurrentAnnouncer, 0, CompPlus_Settings::NumberOfAnnouncers - 1);
		if (AnnouncerTypeStatus != (int)CompPlus_Settings::CurrentAnnouncer) CompPlus_Settings::SetAnnouncer((CompPlus_Settings::AnnouncerType)AnnouncerTypeStatus);

		//Victory Type NUD
		int VictoryTypeStatus = UpDownController(VictoryMethodSwapperController, (int)CompPlus_Settings::VictoryStyle, 0, 5);
		if (VictoryTypeStatus != (int)CompPlus_Settings::VictoryStyle) CompPlus_Settings::SetVictoryMethod((CompPlus_Settings::VictoryMode)VictoryTypeStatus);

        //Item Box Config NUD
        int ItemBoxStatus = UpDownController(ItemBoxModeController, (int)CompPlus_Settings::MonitorTypes, 0, 2);
        if (ItemBoxStatus != (int)CompPlus_Settings::MonitorTypes) CompPlus_Settings::SetMonitorMode((CompPlus_Settings::ItemsConfig)ItemBoxStatus);

        //Number of Rounds NUD
        int NumberOfRoundsStatus = UpDownController(NumberOfRoundsController, (int)CompPlus_Settings::NumberOfRounds, 2, 99);
        if (NumberOfRoundsStatus != (int)CompPlus_Settings::NumberOfRounds) CompPlus_Settings::SetNumberOfRounds(NumberOfRoundsStatus);

		if (SettingWaitTimer != 0) SettingWaitTimer = SettingWaitTimer - 1;
	}

	#pragma endregion

	#pragma region Controller/Statistic Drawing Methods

    void UpdatePeeloutDisplay(int SlotID, int x, int y, CompPlus_Settings::ThreeStateBool State, int index) 
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

        Label3.Position.X = x;
        Label3.Position.Y = y;

        Label3.Text = (wchar_t*)Strings[index];

        if (State == CompPlus_Settings::ThreeStateBool::True)
        {
            char* on_text = (char*)"ON";
            ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
            Label3.TextLength = (WORD)2;
        }
        else if (State == CompPlus_Settings::ThreeStateBool::False)
        {
            char* on_text = (char*)"OFF";
            ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
            Label3.TextLength = (WORD)3;
        }
        else if (State == CompPlus_Settings::ThreeStateBool::Indeterminate)
        {
            char* on_text = (char*)"DEFAULT";
            ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
            Label3.TextLength = (WORD)7;
        }
    }

	void UpdateAbilitySwapperDisplay(int SlotID, int x, int y, CompPlus_Settings::PlayerAbility Ability, int index)
	{
		EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

		Label3.Position.X = x;
		Label3.Position.Y = y;

        Label3.Text = (wchar_t*)Strings[index];

		if (Ability == CompPlus_Settings::AbilitySet_Sonic)
		{
			char* on_text = (char*)"SONIC";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)5;
		}
		else if (Ability == CompPlus_Settings::AbilitySet_Tails)
		{
			char* on_text = (char*)"TAILS";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)5;
		}
		else if (Ability == CompPlus_Settings::AbilitySet_Knuckles)
		{
			char* on_text = (char*)"KNUCKLES";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)8;
		}
		else if (Ability == CompPlus_Settings::AbilitySet_Mighty)
		{
			char* on_text = (char*)"MIGHTY";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)6;
		}
		else if (Ability == CompPlus_Settings::AbilitySet_Ray)
		{
			char* on_text = (char*)"RAY";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)3;
		}
		else if (Ability == CompPlus_Settings::AbilitySet_Compatibility)
		{
			char* on_text = (char*)"DEFAULT";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)7;
		}
	}

	void UpdatePlayerSwapperDisplay(int SlotID, int x, int y, CompPlus_Settings::ChosenPlayer Player, int index)
	{
		EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

		Label3.Position.X = x;
		Label3.Position.Y = y;

        Label3.Text = (wchar_t*)Strings[index];
		if (Player == CompPlus_Settings::ChosenPlayer_Sonic)
		{
			char* on_text = (char*)"SONIC";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)5;
		}
		else if (Player == CompPlus_Settings::ChosenPlayer_Tails)
		{
			char* on_text = (char*)"TAILS";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)5;
		}
		else if (Player == CompPlus_Settings::ChosenPlayer_Knuckles)
		{
			char* on_text = (char*)"KNUCKLES";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)8;
		}
		else if (Player == CompPlus_Settings::ChosenPlayer_Mighty)
		{
			char* on_text = (char*)"MIGHTY";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)6;
		}
		else if (Player == CompPlus_Settings::ChosenPlayer_Ray)
		{
			char* on_text = (char*)"RAY";
			ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
			Label3.TextLength = (WORD)3;
		}
		else if (Player == CompPlus_Settings::ChosenPlayer_Default)
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
		switch (CompPlus_Settings::CurrentAnnouncer) 
		{
			case CompPlus_Settings::Announcer_Default:
				UpdateGeneralDisplay(SlotID, x, y, (char*)"SONIC MANIA", 11, index);
				break;
			case CompPlus_Settings::Announcer_Classic:
				UpdateGeneralDisplay(SlotID, x, y, (char*)"CLASSIC", 7, index);
				break;
			case CompPlus_Settings::Announcer_Garrulous64:
				UpdateGeneralDisplay(SlotID, x, y, (char*)"GARRULOUS64", 11, index);
				break;
			case CompPlus_Settings::Announcer_Angelthegamer:
				UpdateGeneralDisplay(SlotID, x, y, (char*)"ANGELTHEGAMER", 13, index);
				break;
			case CompPlus_Settings::Announcer_Memes:
				UpdateGeneralDisplay(SlotID, x, y, (char*)"MEMES", 5, index);
				break;
		}
	}

	void UpdateVictoryMethodDisplay(int SlotID, int x, int y, int index)
	{
		switch (CompPlus_Settings::VictoryStyle)
		{
			case CompPlus_Settings::VictoryMode_Default:
				UpdateGeneralDisplay(SlotID, x, y, (char*)"ORIGINAL", 8, index);
				break;
			case CompPlus_Settings::VictoryMode_Time:
				UpdateGeneralDisplay(SlotID, x, y, (char*)"TIME", 4, index);
				break;
            case CompPlus_Settings::VictoryMode_Rings:
                UpdateGeneralDisplay(SlotID, x, y, (char*)"RINGS", 5, index);
                break;
            case CompPlus_Settings::VictoryMode_TotalRings:
                UpdateGeneralDisplay(SlotID, x, y, (char*)"ALL RINGS", 9, index);
                break;
            case CompPlus_Settings::VictoryMode_Score:
                UpdateGeneralDisplay(SlotID, x, y, (char*)"SCORE", 5, index);
                break;
            case CompPlus_Settings::VictoryMode_Items:
                UpdateGeneralDisplay(SlotID, x, y, (char*)"ITEMS", 5, index);
                break;
		}
	}

	void UpdateLivesDisplay(int SlotID, int x, int y, int index)
	{
		if (CompPlus_Settings::InfiniteLives)
		{
			UpdateGeneralDisplay(SlotID, x, y, (char*)"INFINITE", 8, index);
		}
		else
		{
			std::string s = std::to_string(CompPlus_Settings::InitalLives);
			s.insert(0, "x");
			char* text = (char*)s.c_str();
			int size = (int)s.length();
			UpdateGeneralDisplay(SlotID, x, y, text, size, index);
		}
	}

    void UpdateNumberOfRoundsDisplay(int SlotID, int x, int y, int index)
    {
        if (CompPlus_Settings::EndlessRounds)
        {
            UpdateGeneralDisplay(SlotID, x, y, (char*)"INFINITE", 8, index);
        }
        else
        {
            std::string s = std::to_string(CompPlus_Settings::NumberOfRounds);
            s.insert(0, "x");
            char* text = (char*)s.c_str();
            int size = (int)s.length();
            UpdateGeneralDisplay(SlotID, x, y, text, size, index);
        }
    }

    void UpdateItemBoxModeDisplay(int SlotID, int x, int y, int index)
    {
        switch (CompPlus_Settings::MonitorTypes)
        {
            case CompPlus_Settings::ItemsConfig_Default:
                UpdateGeneralDisplay(SlotID, x, y, (char*)"FIXED", 5, index);
                break;
            case CompPlus_Settings::ItemsConfig_Random:
                UpdateGeneralDisplay(SlotID, x, y, (char*)"RANDOM", 6, index);
                break;
            case CompPlus_Settings::ItemsConfig_Teleporters:
                UpdateGeneralDisplay(SlotID, x, y, (char*)"TELEPORT", 8, index);
                break;
        }
    }

    void UpdateWinsTallyDisplay(int SlotID, int index) 
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);
        std::string __text = "";

        __text += std::to_string(CompPlus_Scoring::P1_WinsPlus);
        if (SonicMania::Options->CompetitionSession.NumberOfPlayers >= 2)
        {
            __text += " : ";
            __text += std::to_string(CompPlus_Scoring::P2_WinsPlus);
        }
        if (SonicMania::Options->CompetitionSession.NumberOfPlayers >= 3)
        {
            __text += " : ";
            __text += std::to_string(CompPlus_Scoring::P3_WinsPlus);
        }
        if (SonicMania::Options->CompetitionSession.NumberOfPlayers >= 4)
        {
            __text += " : ";
            __text += std::to_string(CompPlus_Scoring::P4_WinsPlus);
        }

        Label3.DrawOrder = 12;

        char* _text = (char*)__text.c_str();
        Label3.Text = (wchar_t*)Strings[index];
        ConvertASCII2Unicode(Label3.Text, _text, strlen(_text), -32);
        Label3.TextLength = __text.length();
    }

    void UpdateVSModeDisplay(int SlotID, int index)
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);
        int x = Label3.Position.X;
        int y = Label3.Position.Y;

        switch (CompPlus_Settings::VictoryStyle)
        {
        case CompPlus_Settings::VictoryMode_Default:
            UpdateGeneralDisplay(SlotID, x, y, (char*)"VS MODE - ORIGINAL", 18, index);
            break;
        case CompPlus_Settings::VictoryMode_Time:
            UpdateGeneralDisplay(SlotID, x, y, (char*)"VS MODE - TIME", 14, index);
            break;
        case CompPlus_Settings::VictoryMode_Rings:
            UpdateGeneralDisplay(SlotID, x, y, (char*)"VS MODE - RINGS", 15, index);
            break;
        case CompPlus_Settings::VictoryMode_TotalRings:
            UpdateGeneralDisplay(SlotID, x, y, (char*)"VS MODE - ALL RINGS", 19, index);
            break;
        case CompPlus_Settings::VictoryMode_Score:
            UpdateGeneralDisplay(SlotID, x, y, (char*)"VS MODE - SCORE", 15, index);
            break;
        case CompPlus_Settings::VictoryMode_Items:
            UpdateGeneralDisplay(SlotID, x, y, (char*)"VS MODE - ITEMS", 15, index);
            break;
        }
    }

    std::string GetPlayerPositionString(int PlayerID) 
    {
        int Position = 0;
        if (PlayerID == 1) Position = CompPlus_Scoring::P1_LastPlacement;
        else if (PlayerID == 2) Position = CompPlus_Scoring::P2_LastPlacement;
        else if (PlayerID == 3) Position = CompPlus_Scoring::P3_LastPlacement;
        else if (PlayerID == 4) Position = CompPlus_Scoring::P4_LastPlacement;

        if (Position == 1) return "1st";
        else if (Position == 2) return "2nd";
        else if (Position == 3) return "3rd";
        else if (Position == 4) return "4th";
        else return "";
    }

    bool GetIsPlayerAWinner(int PlayerID)
    {
        int Position = 0;
        if (PlayerID == 1) Position = CompPlus_Scoring::P1_LastPlacement;
        else if (PlayerID == 2) Position = CompPlus_Scoring::P2_LastPlacement;
        else if (PlayerID == 3) Position = CompPlus_Scoring::P3_LastPlacement;
        else if (PlayerID == 4) Position = CompPlus_Scoring::P4_LastPlacement;

        return Position == 1;
    }

    void UpdateHUBPrivateHUDAlpha(SonicMania::EntityPlayer& Player, Entity& Entity, int& HUDAlpha, bool& isInWarpLoop, bool& isInQuickWarp)
    {
        Entity.InkEffect = Ink_Alpha;
        if ((Player.XVelocity == 0 && Player.YVelocity == 0) && !isInWarpLoop && !isInQuickWarp)
        {
            Entity.Alpha = (HUDAlpha < 256 ? HUDAlpha : 256);
            if (HUDAlpha < 256) HUDAlpha = HUDAlpha + 20;
        }
        else
        {
            Entity.Alpha = (HUDAlpha > 0 ? HUDAlpha : 0);
            if (HUDAlpha > 0) HUDAlpha = HUDAlpha - 20;
            else HUDAlpha = 0;
        }
    }

    int UpdateHUBPrivateHUD(SonicMania::EntityPlayer& Player, int& HUDAlpha, bool& isInQuickWarp, bool& isInWarpLoop, int PlayerSlot, int StatSlot, int ExtraSlot, int CrownSlot, int lastIndex)
    {
        int upper_offset = 30;
        int lower_offset = 20;

        Entity& HUD_PlayerID = *GetEntityFromSceneSlot<Entity>(PlayerSlot);
        Entity& HUD_Statistics = *GetEntityFromSceneSlot<Entity>(StatSlot);
        Entity& HUD_Extra = *GetEntityFromSceneSlot<Entity>(ExtraSlot);
        Entity& HUD_Winner = *GetEntityFromSceneSlot<Entity>(CrownSlot);

        HUD_PlayerID.DrawOrder = Player.DrawOrder;
        HUD_Statistics.DrawOrder = (Player.DrawOrder + 1 <= 14 ? Player.DrawOrder + 1 : Player.DrawOrder);
        HUD_Extra.DrawOrder = Player.DrawOrder;
        HUD_Winner.DrawOrder = Player.DrawOrder;

        int PlayerID = 1;


        if (Player.Active)
        {
            UpdateHUBPrivateHUDAlpha(Player, HUD_PlayerID, HUDAlpha, isInWarpLoop, isInQuickWarp);
            UpdateHUBPrivateHUDAlpha(Player, HUD_Statistics, HUDAlpha, isInWarpLoop, isInQuickWarp);
            //UpdateHUBPrivateHUDAlpha(Player, HUD_Extra, HUDAlpha, isInWarpLoop, isInQuickWarp);
            UpdateHUBPrivateHUDAlpha(Player, HUD_Winner, HUDAlpha, isInWarpLoop, isInQuickWarp);


            int x = Player.Position.X;
            int y = Player.Position.Y;


            HUD_PlayerID.Position.X = x;
            HUD_PlayerID.Position.Y = y - upper_offset;

            HUD_Statistics.Position.X = x;
            HUD_Statistics.Position.Y = y + lower_offset;

            HUD_Extra.Position.X = Pos_OutOfBounds.X;
            HUD_Extra.Position.Y = Pos_OutOfBounds.Y;


            if (Player.PlayerID == Player1.PlayerID)
            {
                PlayerID = 1;
                UpdateGeneralDisplay(PlayerSlot, (char*)"P1", 2, lastIndex);
                lastIndex++;

                std::string pos = GetPlayerPositionString(1);
                UpdateGeneralDisplay(StatSlot, (char*)pos.c_str(), pos.length(), lastIndex);
                lastIndex++;
                //UpdateGeneralDisplay(ExtraSlot, (char*)"", 0, lastIndex);
                //lastIndex++;
            }
            else if (Player.PlayerID == Player2.PlayerID)
            {
                PlayerID = 2;
                UpdateGeneralDisplay(PlayerSlot, (char*)"P2", 2, lastIndex);
                lastIndex++;
                std::string pos = GetPlayerPositionString(2);
                UpdateGeneralDisplay(StatSlot, (char*)pos.c_str(), pos.length(), lastIndex);
                lastIndex++;
                //UpdateGeneralDisplay(ExtraSlot, (char*)"", 0, lastIndex);
                //lastIndex++;
            }
            else if (Player.PlayerID == Player3.PlayerID)
            {
                PlayerID = 3;
                UpdateGeneralDisplay(PlayerSlot, (char*)"P3", 2, lastIndex);
                lastIndex++;
                std::string pos = GetPlayerPositionString(3);
                UpdateGeneralDisplay(StatSlot, (char*)pos.c_str(), pos.length(), lastIndex);
                lastIndex++;
                //UpdateGeneralDisplay(ExtraSlot, (char*)"", 0, lastIndex);
                //lastIndex++;
            }
            else if (Player.PlayerID == Player4.PlayerID)
            {
                PlayerID = 4;
                UpdateGeneralDisplay(PlayerSlot, (char*)"P4", 2, lastIndex);
                lastIndex++;
                std::string pos = GetPlayerPositionString(4);
                UpdateGeneralDisplay(StatSlot, (char*)pos.c_str(), pos.length(), lastIndex);
                lastIndex++;
                //UpdateGeneralDisplay(ExtraSlot, (char*)"", 0, lastIndex);
                //lastIndex++;
            }

            if (HUDAlpha != 0) 
            {
                if (GetIsPlayerAWinner(PlayerID))
                {
                    HUD_Winner.Position.X = x;
                    HUD_Winner.Position.Y = y - upper_offset + 10;
                }
                else
                {
                    HUD_Winner.Position.X = Pos_OutOfBounds.X;
                    HUD_Winner.Position.Y = Pos_OutOfBounds.Y;
                }
            }
        }
        else
        {
            int x = Pos_OutOfBounds.X;
            int y = Pos_OutOfBounds.Y;

            HUD_PlayerID.Position.X = x;
            HUD_PlayerID.Position.Y = y;

            HUD_Statistics.Position.X = x;
            HUD_Statistics.Position.Y = y;

            HUD_Extra.Position.X = x;
            HUD_Extra.Position.Y = y;

            //HUD_Winner.Position.X = x;
            //HUD_Winner.Position.Y = y;
        }

        return lastIndex;
    }

    int UpdateHUBPrivateHUDs(int lastIndex)
    {
        lastIndex = UpdateHUBPrivateHUD(Player1, P1_HUDAlpha, P1_IsInWarpRoom, P1_IsInWarpLoop, P1_HUD_1, P1_HUD_2, P1_HUD_3, P1_HUD_4, lastIndex);
        lastIndex = UpdateHUBPrivateHUD(Player2, P2_HUDAlpha, P2_IsInWarpRoom, P2_IsInWarpLoop, P2_HUD_1, P2_HUD_2, P2_HUD_3, P2_HUD_4, lastIndex);
        lastIndex = UpdateHUBPrivateHUD(Player3, P3_HUDAlpha, P3_IsInWarpRoom, P3_IsInWarpLoop, P3_HUD_1, P3_HUD_2, P3_HUD_3, P3_HUD_4, lastIndex);
        lastIndex = UpdateHUBPrivateHUD(Player4, P4_HUDAlpha, P4_IsInWarpRoom, P4_IsInWarpLoop, P4_HUD_1, P4_HUD_2, P4_HUD_3, P4_HUD_4, lastIndex);
        return lastIndex;
    }

    int UpdateScoreboardDisplays(int lastIndex) 
    {
        if (CompPlus_Settings::EndlessRounds) 
        {
            std::string roundNumber = "INFINITE";
            UpdateGeneralDisplay(RoundsCounterText, (char*)roundNumber.c_str(), roundNumber.length(), lastIndex);
            lastIndex++;
        }
        else 
        {       
            std::string roundNumber = std::to_string(CompPlus_Scoring::GetPlusCurrentRound() + 1) + "\\" + std::to_string(CompPlus_Settings::NumberOfRounds);
            UpdateGeneralDisplay(RoundsCounterText, (char*)roundNumber.c_str(), roundNumber.length(), lastIndex);
            lastIndex++;
        }
        

        std::string winsP1 = std::to_string(CompPlus_Scoring::P1_WinsPlus);
        UpdateGeneralDisplay(P1_WinsCounterText, (char*)winsP1.c_str(), winsP1.length(), lastIndex);
        lastIndex++;
        std::string winsP2 = std::to_string(CompPlus_Scoring::P2_WinsPlus);
        UpdateGeneralDisplay(P2_WinsCounterText, (char*)winsP2.c_str(), winsP2.length(), lastIndex);
        lastIndex++;
        std::string winsP3 = std::to_string(CompPlus_Scoring::P3_WinsPlus);
        UpdateGeneralDisplay(P3_WinsCounterText, (char*)winsP3.c_str(), winsP3.length(), lastIndex);
        lastIndex++;
        std::string winsP4 = std::to_string(CompPlus_Scoring::P4_WinsPlus);
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


        UpdateWinsTallyDisplay(WinsTallyTextSlot, lastIndex);
        lastIndex++;

        UpdateVSModeDisplay(VSModeTextSlot, lastIndex);
        lastIndex++;

        std::string timeP1 = std::to_string(CompPlus_Scoring::LastSession.TimeMinutes_P1) + "\'" + (CompPlus_Scoring::LastSession.TimeSeconds_P1 < 10 ? "0" : "") + std::to_string(CompPlus_Scoring::LastSession.TimeSeconds_P1) + "\"" + (CompPlus_Scoring::LastSession.TimeCentiseconds_P1 < 10 ? "0" : "") + std::to_string(CompPlus_Scoring::LastSession.TimeCentiseconds_P1);
        UpdateGeneralDisplay(P1_TimeCounterText_Board, (char*)timeP1.c_str(), timeP1.length(), lastIndex);
        lastIndex++;
        std::string timeP2 = std::to_string(CompPlus_Scoring::LastSession.TimeMinutes_P2) + "\'" + (CompPlus_Scoring::LastSession.TimeSeconds_P2 < 10 ? "0" : "") + std::to_string(CompPlus_Scoring::LastSession.TimeSeconds_P2) + "\"" + (CompPlus_Scoring::LastSession.TimeCentiseconds_P2 < 10 ? "0" : "") + std::to_string(CompPlus_Scoring::LastSession.TimeCentiseconds_P2);
        UpdateGeneralDisplay(P2_TimeCounterText_Board, (char*)timeP2.c_str(), timeP2.length(), lastIndex);
        lastIndex++;
        std::string timeP3 = std::to_string(CompPlus_Scoring::LastSession.TimeMinutes_P3) + "\'" + (CompPlus_Scoring::LastSession.TimeSeconds_P3 < 10 ? "0" : "") + std::to_string(CompPlus_Scoring::LastSession.TimeSeconds_P3) + "\"" + (CompPlus_Scoring::LastSession.TimeCentiseconds_P3 < 10 ? "0" : "") + std::to_string(CompPlus_Scoring::LastSession.TimeCentiseconds_P3);
        UpdateGeneralDisplay(P3_TimeCounterText_Board, (char*)timeP3.c_str(), timeP3.length(), lastIndex);
        lastIndex++;
        std::string timeP4 = std::to_string(CompPlus_Scoring::LastSession.TimeMinutes_P4) + "\'" + (CompPlus_Scoring::LastSession.TimeSeconds_P4 < 10 ? "0" : "") + std::to_string(CompPlus_Scoring::LastSession.TimeSeconds_P4) + "\"" + (CompPlus_Scoring::LastSession.TimeCentiseconds_P4 < 10 ? "0" : "") + std::to_string(CompPlus_Scoring::LastSession.TimeCentiseconds_P4);
        UpdateGeneralDisplay(P4_TimeCounterText_Board, (char*)timeP4.c_str(), timeP4.length(), lastIndex);
        lastIndex++;

        std::string scoreP1 = std::to_string(CompPlus_Scoring::LastSession.Score_P1);
        UpdateGeneralDisplay(P1_ScoreCounterText_Board, (char*)scoreP1.c_str(), scoreP1.length(), lastIndex);
        lastIndex++;
        std::string scoreP2 = std::to_string(CompPlus_Scoring::LastSession.Score_P2);
        UpdateGeneralDisplay(P2_ScoreCounterText_Board, (char*)scoreP2.c_str(), scoreP2.length(), lastIndex);
        lastIndex++;
        std::string scoreP3 = std::to_string(CompPlus_Scoring::LastSession.Score_P3);
        UpdateGeneralDisplay(P3_ScoreCounterText_Board, (char*)scoreP3.c_str(), scoreP3.length(), lastIndex);
        lastIndex++;
        std::string scoreP4 = std::to_string(CompPlus_Scoring::LastSession.Score_P4);
        UpdateGeneralDisplay(P4_ScoreCounterText_Board, (char*)scoreP4.c_str(), scoreP4.length(), lastIndex);
        lastIndex++;

        std::string ringsP1 = std::to_string(CompPlus_Scoring::LastSession.Rings_P1);
        UpdateGeneralDisplay(P1_RingsCounterText_Board, (char*)ringsP1.c_str(), ringsP1.length(), lastIndex);
        lastIndex++;
        std::string ringsP2 = std::to_string(CompPlus_Scoring::LastSession.Rings_P2);
        UpdateGeneralDisplay(P2_RingsCounterText_Board, (char*)ringsP2.c_str(), ringsP2.length(), lastIndex);
        lastIndex++;
        std::string ringsP3 = std::to_string(CompPlus_Scoring::LastSession.Rings_P3);
        UpdateGeneralDisplay(P3_RingsCounterText_Board, (char*)ringsP3.c_str(), ringsP3.length(), lastIndex);
        lastIndex++;
        std::string ringsP4 = std::to_string(CompPlus_Scoring::LastSession.Rings_P4);
        UpdateGeneralDisplay(P4_RingsCounterText_Board, (char*)ringsP4.c_str(), ringsP4.length(), lastIndex);
        lastIndex++;

        std::string itemsP1 = std::to_string(CompPlus_Scoring::LastSession.Items_P1);
        UpdateGeneralDisplay(P1_ItemsCounterText_Board, (char*)itemsP1.c_str(), itemsP1.length(), lastIndex);
        lastIndex++;
        std::string itemsP2 = std::to_string(CompPlus_Scoring::LastSession.Items_P2);
        UpdateGeneralDisplay(P2_ItemsCounterText_Board, (char*)itemsP2.c_str(), itemsP2.length(), lastIndex);
        lastIndex++;
        std::string itemsP3 = std::to_string(CompPlus_Scoring::LastSession.Items_P3);
        UpdateGeneralDisplay(P3_ItemsCounterText_Board, (char*)itemsP3.c_str(), itemsP3.length(), lastIndex);
        lastIndex++;
        std::string itemsP4 = std::to_string(CompPlus_Scoring::LastSession.Items_P4);
        UpdateGeneralDisplay(P4_ItemsCounterText_Board, (char*)itemsP4.c_str(), itemsP4.length(), lastIndex);
        lastIndex++;


        std::string totalringsP1 = std::to_string(CompPlus_Scoring::LastSession.TotalRings_P1);
        UpdateGeneralDisplay(P1_TotalRingsCounterText_Board, (char*)totalringsP1.c_str(), totalringsP1.length(), lastIndex);
        lastIndex++;
        std::string totalringsP2 = std::to_string(CompPlus_Scoring::LastSession.TotalRings_P2);
        UpdateGeneralDisplay(P2_TotalRingsCounterText_Board, (char*)totalringsP2.c_str(), totalringsP2.length(), lastIndex);
        lastIndex++;
        std::string totalringsP3 = std::to_string(CompPlus_Scoring::LastSession.TotalRings_P3);
        UpdateGeneralDisplay(P3_TotalRingsCounterText_Board, (char*)totalringsP3.c_str(), totalringsP3.length(), lastIndex);
        lastIndex++;
        std::string totalringsP4 = std::to_string(CompPlus_Scoring::LastSession.TotalRings_P4);
        UpdateGeneralDisplay(P4_TotalRingsCounterText_Board, (char*)totalringsP4.c_str(), totalringsP4.length(), lastIndex);
        lastIndex++;

        return lastIndex;
    }

	void UpdateHUBDisplays()
	{
		//Character Select Display
		UpdatePlayerSwapperDisplay(SwapPlayerText_P1, Pos_SwapPlayerText.X, Pos_SwapPlayerText.Y - 48, CompPlus_Settings::Player1ChosenPlayer, 0);
		UpdatePlayerSwapperDisplay(SwapPlayerText_P2, Pos_SwapPlayerText.X, Pos_SwapPlayerText.Y - 32, CompPlus_Settings::Player2ChosenPlayer, 1);
		UpdatePlayerSwapperDisplay(SwapPlayerText_P3, Pos_SwapPlayerText.X, Pos_SwapPlayerText.Y - 16, CompPlus_Settings::Player3ChosenPlayer, 2);
		UpdatePlayerSwapperDisplay(SwapPlayerText_P4, Pos_SwapPlayerText.X, Pos_SwapPlayerText.Y - 0, CompPlus_Settings::Player4ChosenPlayer, 3);
		//Player Ability Display
		UpdateAbilitySwapperDisplay(SwapAbilityText_P1, Pos_SwapAbilityText.X, Pos_SwapAbilityText.Y - 48, CompPlus_Settings::Player1AbilitySet, 4);
		UpdateAbilitySwapperDisplay(SwapAbilityText_P2, Pos_SwapAbilityText.X, Pos_SwapAbilityText.Y - 32, CompPlus_Settings::Player2AbilitySet, 5);
		UpdateAbilitySwapperDisplay(SwapAbilityText_P3, Pos_SwapAbilityText.X, Pos_SwapAbilityText.Y - 16, CompPlus_Settings::Player3AbilitySet, 6);
		UpdateAbilitySwapperDisplay(SwapAbilityText_P4, Pos_SwapAbilityText.X, Pos_SwapAbilityText.Y - 0, CompPlus_Settings::Player4AbilitySet, 7);
		//Peelout Ability Display
		UpdatePeeloutDisplay(PeeloutToggleText_P1, Pos_PeeloutText.X, Pos_PeeloutText.Y - 48, CompPlus_Settings::Player1PeeloutAbility, 8);
		UpdatePeeloutDisplay(PeeloutToggleText_P2, Pos_PeeloutText.X, Pos_PeeloutText.Y - 32, CompPlus_Settings::Player2PeeloutAbility, 9);
        UpdatePeeloutDisplay(PeeloutToggleText_P3, Pos_PeeloutText.X, Pos_PeeloutText.Y - 16, CompPlus_Settings::Player3PeeloutAbility, 10);
        UpdatePeeloutDisplay(PeeloutToggleText_P4, Pos_PeeloutText.X, Pos_PeeloutText.Y - 0, CompPlus_Settings::Player4PeeloutAbility, 11);
		//Dropdash Display
		UpdateToggleDisplay(DropDashToggleText, Pos_DropDashText.X, Pos_DropDashText.Y, CompPlus_Settings::DropdashAbility, 12);
		//Insta-Sheild Display
		UpdateToggleDisplay(InstaSheildToggleText, Pos_InstaSheildText.X, Pos_InstaSheildText.Y, CompPlus_Settings::InstaSheildAbility, 13);
		//Debug Mode Display
		UpdateToggleDisplay(DebugModeText, Pos_DebugModeText.X, Pos_DebugModeText.Y, CompPlus_Settings::EnableDebugMode, 14);
		//Dev Mode Display
		UpdateToggleDisplay(DevModeText, Pos_DevModeText.X, Pos_DevModeText.Y, CompPlus_Settings::EnableDevMode, 15);
		//Level Select Display
		UpdateLevelSelectStatusDisplay(CompPlus_Settings::CurrentLevelSelect, 16);
		//Lives Display
		UpdateLivesDisplay(LivesNUDText, Pos_LivesNUDText.X, Pos_LivesNUDText.Y, 17);
		//Remove Time Display
        UpdateToggleDisplay(RemoveTimeToggleText, Pos_RemoveTimeText.X, Pos_RemoveTimeText.Y, CompPlus_Settings::TimeLimit, 18);
        //Hurry Timer Display
        UpdateToggleDisplayInverted(HurryTimerToggleText, Pos_HurryTimerToggleText.X, Pos_HurryTimerToggleText.Y, CompPlus_Settings::NoHurryUpTimer, 19);
		//Infinite Rounds Display
		UpdateToggleDisplay(InfiniteRoundsToggleText, Pos_InfiniteRoundsText.X, Pos_InfiniteRoundsText.Y, CompPlus_Settings::EndlessRounds, 20);
		//Announcer Type Display
		UpdateAnnouncerDisplay(AnnouncerTypeText, Pos_AnnouncerTypeText.X, Pos_AnnouncerTypeText.Y, 21);
		//Victory Method Display
		UpdateVictoryMethodDisplay(VictoryMethodSwapperText, Pos_VictoryMethodText.X, Pos_VictoryMethodText.Y, 22);
        //Item Box Mode Type Display
        UpdateItemBoxModeDisplay(ItemBoxModeText, Pos_ItemBoxModeText.X, Pos_ItemBoxModeText.Y, 23);
        //Number Of Rounds Display
        UpdateNumberOfRoundsDisplay(NumberOfRoundsText, Pos_NumberOfRoundsText.X, Pos_NumberOfRoundsText.Y, 24);
        //Scoreboard Displays
        int lastIndex = UpdateScoreboardDisplays(25);
        lastIndex = UpdateHUBPrivateHUDs(lastIndex);
	}

	void UpdateHUBPositions()
	{
		//X: 11264 Y: 11123

		int OffsetX = 0;
		int OffsetY = 88;

		int OffsetY_2 = 48;

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
        Entity& E13 = *GetEntityFromSceneSlot<Entity>(ItemBoxModeController);
        Entity& E14 = *GetEntityFromSceneSlot<Entity>(NumberOfRoundsController);
        Entity& E15 = *GetEntityFromSceneSlot<Entity>(HurryTimerToggleController);

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

        Pos_ItemBoxModeText.X = E13.Position.X + OffsetX;
        Pos_ItemBoxModeText.Y = E13.Position.Y + OffsetY_2;

        Pos_NumberOfRoundsText.X = E14.Position.X + OffsetX;
        Pos_NumberOfRoundsText.Y = E14.Position.Y + OffsetY_2;

        Pos_HurryTimerToggleText.X = E15.Position.X + OffsetX;
        Pos_HurryTimerToggleText.Y = E15.Position.Y + OffsetY_2;
       
        Entity& QuickWarpSpawn = *GetEntityFromSceneSlot<Entity>(WarpDestSlotID_WarpHub);
        Entity& RankingWarpSpawn = *GetEntityFromSceneSlot<Entity>(WarpDestSlotID_Ranking);
        Entity& OtherOptionsSpawn = *GetEntityFromSceneSlot<Entity>(WarpDestSlotID_OtherSettings);
        Entity& PlayerOptionsSpawn = *GetEntityFromSceneSlot<Entity>(WarpDestSlotID_PlayerSettings);
        Entity& LevelSelectSpawn = *GetEntityFromSceneSlot<Entity>(WarpDestSlotID_LevelSelect);

        WarpDest_PlayerSettings = INT_Position(PlayerOptionsSpawn.Position.X, PlayerOptionsSpawn.Position.Y);
        WarpDest_OtherSettings = INT_Position(OtherOptionsSpawn.Position.X, OtherOptionsSpawn.Position.Y);
        WarpDest_Ranking = INT_Position(RankingWarpSpawn.Position.X, RankingWarpSpawn.Position.Y);
        WarpDest_LevelSelect = INT_Position(LevelSelectSpawn.Position.X, LevelSelectSpawn.Position.Y);
        WarpDest_WarpHub = INT_Position(QuickWarpSpawn.Position.X, QuickWarpSpawn.Position.Y);
	}

	#pragma endregion

    #pragma region HUB Startup Methods

    void SetSpawnPosition(SonicMania::EntityPlayer& Player, int Placement)
    {
        Entity& FirstPlacePodieumSpawn = *GetEntityFromSceneSlot<Entity>(RespawnObject_FirstPlace);
        Entity& SecondPlacePodieumSpawn = *GetEntityFromSceneSlot<Entity>(RespawnObject_SecondPlace);
        Entity& ThirdPlacePodieumSpawn = *GetEntityFromSceneSlot<Entity>(RespawnObject_ThirdPlace);
        Entity& ForthPlacePodieumSpawn = *GetEntityFromSceneSlot<Entity>(RespawnObject_FouthPlace);

        Entity& InitalSpawn = *GetEntityFromSceneSlot<Entity>(PlayerSpawnSlotID);
        Entity& AltSpawn = *GetEntityFromSceneSlot<Entity>(AltSpawnSlotID);

        if (Placement == 1)
        {
            Player.Position.X = FirstPlacePodieumSpawn.Position.X;
            Player.Position.Y = FirstPlacePodieumSpawn.Position.Y;
        }
        else if (Placement == 2)
        {
            Player.Position.X = SecondPlacePodieumSpawn.Position.X;
            Player.Position.Y = SecondPlacePodieumSpawn.Position.Y;
        }
        else if (Placement == 3)
        {
            Player.Position.X = ThirdPlacePodieumSpawn.Position.X;
            Player.Position.Y = ThirdPlacePodieumSpawn.Position.Y;
        }
        else if (Placement == 4)
        {
            Player.Position.X = ForthPlacePodieumSpawn.Position.X;
            Player.Position.Y = ForthPlacePodieumSpawn.Position.Y;
        }
        else if (CompPlus_Scoring::PodeiumSpawnActive)
        {
            Player.Position.X = InitalSpawn.Position.X;
            Player.Position.Y = InitalSpawn.Position.Y;
        }
        else 
        {
            Player.Position.X = AltSpawn.Position.X;
            Player.Position.Y = AltSpawn.Position.Y;
        }

        if (Player.Camera != nullptr)
        {
            Player.Camera->Position.X = Player.Position.X;
            Player.Camera->Position.Y = Player.Position.Y;
        }
    }

    void SetSpawnPositions()
    {
        SetSpawnPosition(Player1, CompPlus_Scoring::P1_LastPlacement);
        SetSpawnPosition(Player2, CompPlus_Scoring::P2_LastPlacement);
        SetSpawnPosition(Player3, CompPlus_Scoring::P3_LastPlacement);
        SetSpawnPosition(Player4, CompPlus_Scoring::P4_LastPlacement);
    }

    void SetHUBVisualSettings()
    {
        //Disable Timer
        SonicMania::Timer.ResetTimer();

        //Disable HUD
        WriteData((BYTE*)(baseAddress + 0x47B065), (BYTE)0);

        //Player Life Count Infinite
        Player1.LifeCount = 99;
        Player2.LifeCount = 99;
        Player3.LifeCount = 99;
        Player4.LifeCount = 99;
    }

    #pragma endregion

    #pragma region  HUB Quick Warp Room

    void SetIsInWarpRoomState(int PlayerID, bool value)
    {
        if (PlayerID == 1) P1_IsInWarpRoom = value;
        else if (PlayerID == 2) P2_IsInWarpRoom = value;
        else if (PlayerID == 3) P3_IsInWarpRoom = value;
        else if (PlayerID == 4) P4_IsInWarpRoom = value;
    }

    INT_Position GetLastWarpPosition(int PlayerID)
    {
        if (PlayerID == 1) return P1_LastWarpPosition;
        else if (PlayerID == 2) return P2_LastWarpPosition;
        else if (PlayerID == 3) return P3_LastWarpPosition;
        else if (PlayerID == 4) return P4_LastWarpPosition;
        else return INT_Position(0, 0);
    }

    void QueueWarp(SonicMania::EntityPlayer& Player, int x, int y, bool isEnter, int PlayerID)
    {
        if (PlayerID == 1) 
        { 
            P1_WarpQueue = INT_Position(x,y);
            P1_IsInWarpLoop = true;
            if (!isEnter) P1_WarpAlpha = 0;
        }
        else if (PlayerID == 2) 
        {
            P2_WarpQueue = INT_Position(x, y);
            P2_IsInWarpLoop = true;
            if (!isEnter) P2_WarpAlpha = 0;
        }
        else if (PlayerID == 3) 
        {
            P3_WarpQueue = INT_Position(x, y);
            P3_IsInWarpLoop = true;
            if (!isEnter) P3_WarpAlpha = 0;
        }
        else if (PlayerID == 4) 
        {
            P4_WarpQueue = INT_Position(x, y);
            P4_IsInWarpLoop = true;
            if (!isEnter) P4_WarpAlpha = 0;
        }
        SetIsInWarpRoomState(PlayerID, isEnter);
    }

    void TeleWarp(SonicMania::EntityPlayer& Player, int x, int y, int PlayerID)
    {
        int checkpoint_Offset = *(int*)(baseAddress + 0x00AC672C);

        switch (PlayerID) 
        {
            case 1:
                WriteData((int*)(checkpoint_Offset + 0x12), x);
                WriteData((int*)(checkpoint_Offset + 0x16), y);
                WriteData((int*)(checkpoint_Offset + 0x34), 1);
                break;                                   
            case 2:                                      
                WriteData((int*)(checkpoint_Offset + 0x1A), x);
                WriteData((int*)(checkpoint_Offset + 0x1E), y);
                WriteData((int*)(checkpoint_Offset + 0x35), 1);
                break;                                   
            case 3:                                     
                WriteData((int*)(checkpoint_Offset + 0x22), x);
                WriteData((int*)(checkpoint_Offset + 0x26), y);
                WriteData((int*)(checkpoint_Offset + 0x36), 1);
                break;                                  
            case 4:                                    
                WriteData((int*)(checkpoint_Offset + 0x2A), x);
                WriteData((int*)(checkpoint_Offset + 0x2E), y);
                WriteData((int*)(checkpoint_Offset + 0x37), 1);
                break;
        }

        Player.Kill();
        Player.Position.X = x;
        Player.Position.Y = y;
    }

    DataPointer(int, IsPlayerInDebugMode, 0x31F9AC);
    DataPointer(int, IsPlayerInDebugMode_Alt, 0x30D130);

    bool isPlayerInDebug() 
    {
        if (IsPlayerInDebugMode == 1 || IsPlayerInDebugMode_Alt == 1) 
        {
            return true;
        }
        else return false;
    }

    void CheckQuickWarp()
    {
        if (P1_IsInWarpRoom == false && Player1.Active)
        {
            P1_LastWarpPosition.X = (int)Player1.Position.X;
            P1_LastWarpPosition.Y = (int)Player1.Position.Y;
        }
        if (P2_IsInWarpRoom == false && Player2.Active)
        {
            P2_LastWarpPosition.X = (int)Player2.Position.X;
            P2_LastWarpPosition.Y = (int)Player2.Position.Y;
        }
        if (P3_IsInWarpRoom == false && Player3.Active)
        {
            P3_LastWarpPosition.X = (int)Player3.Position.X;
            P3_LastWarpPosition.Y = (int)Player3.Position.Y;
        }
        if (P4_IsInWarpRoom == false && Player4.Active)
        {
            P4_LastWarpPosition.X = (int)Player4.Position.X;
            P4_LastWarpPosition.Y = (int)Player4.Position.Y;
        }

        if (PlayerControllers[1].Y.Press && !P1_IsInWarpRoom && Player1.Grounded && Player1.XVelocity == 0 && Player1.YVelocity == 0) 
        {
            if (!isPlayerInDebug()) QueueWarp(Player1, WarpDest_WarpHub.X, WarpDest_WarpHub.Y, true, 1);
        }
        if (PlayerControllers[2].Y.Press && !P2_IsInWarpRoom && Player2.Grounded && Player2.XVelocity == 0 && Player2.YVelocity == 0) QueueWarp(Player2, WarpDest_WarpHub.X, WarpDest_WarpHub.Y, true, 2);
        if (PlayerControllers[3].Y.Press && !P3_IsInWarpRoom && Player3.Grounded && Player3.XVelocity == 0 && Player3.YVelocity == 0) QueueWarp(Player3, WarpDest_WarpHub.X, WarpDest_WarpHub.Y, true, 3);
        if (PlayerControllers[4].Y.Press && !P4_IsInWarpRoom && Player4.Grounded && Player4.XVelocity == 0 && Player4.YVelocity == 0) QueueWarp(Player4, WarpDest_WarpHub.X, WarpDest_WarpHub.Y, true, 4);
    }

    void CheckPlayerReturnWarp(SonicMania::EntityPlayer& Player, int SlotID, int X1, int Y1, int X2, int Y2, int PlayerID)
    {
        Entity& WarpDetector = *GetEntityFromSceneSlot<Entity>(SlotID);
        int _X1 = WarpDetector.Position.X + X1;
        int _Y1 = WarpDetector.Position.Y + Y1;
        int _X2 = WarpDetector.Position.X + X2;
        int _Y2 = WarpDetector.Position.Y + Y2;

        if (Player.InRange(_X1, _Y1, _X2, _Y2))
        {
            INT_Position Warp = GetLastWarpPosition(PlayerID);
            QueueWarp(Player, Warp.X, Warp.Y, false, PlayerID);
        }
    }

    void CheckPlayerQuickWarp(SonicMania::EntityPlayer &Player, int SlotID, int X1, int Y1, int X2, int Y2, int WarpX, int WarpY, int PlayerID)
    {
        Entity& WarpDetector = *GetEntityFromSceneSlot<Entity>(SlotID);
        int _X1 = WarpDetector.Position.X + X1;
        int _Y1 = WarpDetector.Position.Y + Y1;
        int _X2 = WarpDetector.Position.X + X2;
        int _Y2 = WarpDetector.Position.Y + Y2;

        if (Player.InRange(_X1, _Y1, _X2, _Y2))
        {
            QueueWarp(Player, WarpX, WarpY, false, PlayerID);
        }
    }

    void CheckPlayersReturnWarp(int SlotID, int X1, int Y1, int X2, int Y2)
    {
        CheckPlayerReturnWarp(SonicMania::Player1, SlotID, X1, Y1, X2, Y2, 1);
        CheckPlayerReturnWarp(SonicMania::Player2, SlotID, X1, Y1, X2, Y2, 2);
        CheckPlayerReturnWarp(SonicMania::Player3, SlotID, X1, Y1, X2, Y2, 3);
        CheckPlayerReturnWarp(SonicMania::Player4, SlotID, X1, Y1, X2, Y2, 4);
    }

    void CheckPlayersQuickWarp(int SlotID, int X1, int Y1, int X2, int Y2, int WarpX, int WarpY)
    {
        CheckPlayerQuickWarp(SonicMania::Player1, SlotID, X1, Y1, X2, Y2, WarpX, WarpY, 1);
        CheckPlayerQuickWarp(SonicMania::Player2, SlotID, X1, Y1, X2, Y2, WarpX, WarpY, 2);
        CheckPlayerQuickWarp(SonicMania::Player3, SlotID, X1, Y1, X2, Y2, WarpX, WarpY, 3);
        CheckPlayerQuickWarp(SonicMania::Player4, SlotID, X1, Y1, X2, Y2, WarpX, WarpY, 4);
    }

    void WarpLoop(SonicMania::EntityPlayer& Player, int PlayerID, int& WarpAlpha, bool& IsInWarpLoop, INT_Position& WarpQueue)
    {
        if (Player.Active) 
        {
            Player.InkEffect = Ink_Alpha;
            if (IsInWarpLoop)
            {
                Player.Alpha = (WarpAlpha > 0 ? WarpAlpha : 0);
                if (WarpAlpha > 0) WarpAlpha = WarpAlpha - 10;
                else 
                {
                    WarpAlpha = 0;
                    TeleWarp(Player, WarpQueue.X, WarpQueue.Y, PlayerID);
                    IsInWarpLoop = false;
                }
            }
            else
            {
                Player.Alpha = (WarpAlpha < 256 ? WarpAlpha : 256);
                if (WarpAlpha < 256) WarpAlpha = WarpAlpha + 10;
            }
        }
    }

    void UpdateWarpEffects()
    {
        WarpLoop(Player1, 1, P1_WarpAlpha, P1_IsInWarpLoop, P1_WarpQueue);
        WarpLoop(Player2, 2, P2_WarpAlpha, P2_IsInWarpLoop, P2_WarpQueue);
        WarpLoop(Player3, 3, P3_WarpAlpha, P3_IsInWarpLoop, P3_WarpQueue);
        WarpLoop(Player4, 4, P4_WarpAlpha, P4_IsInWarpLoop, P4_WarpQueue);
    }

    void UpdateQuickWarpRoom() 
    {
        UpdateWarpEffects();
        CheckQuickWarp();
        CheckPlayersQuickWarp(WarpSlotID_PlayerSettings, -50, -50, 50, 50, WarpDest_PlayerSettings.X, WarpDest_PlayerSettings.Y);
        CheckPlayersQuickWarp(WarpSlotID_OtherSettings, -50, -50, 50, 50, WarpDest_OtherSettings.X, WarpDest_OtherSettings.Y);
        CheckPlayersQuickWarp(WarpSlotID_Ranking, -50, -50, 50, 50, WarpDest_Ranking.X, WarpDest_Ranking.Y);
        CheckPlayersQuickWarp(WarpSlotID_LevelSelect, -50, -50, 50, 50, WarpDest_LevelSelect.X, WarpDest_LevelSelect.Y);
        CheckPlayersReturnWarp(WarpSlotID_ReturnToLast, -50, -55, 50, 50);
    }

    void ResetWarps() 
    {
        P1_IsInWarpRoom = false;
        P2_IsInWarpRoom = false;
        P3_IsInWarpRoom = false;
        P4_IsInWarpRoom = false;
        P1_LastWarpPosition = INT_Position(0, 0);
        P2_LastWarpPosition = INT_Position(0, 0);
        P3_LastWarpPosition = INT_Position(0, 0);
        P4_LastWarpPosition = INT_Position(0, 0);
    }

    #pragma endregion

    #pragma region HUB General Methods

    void CreditsWarp() 
    {
        for (int RealID = 1; RealID <= 4; RealID++)
        {
            SonicMania::EntityPlayer* Player;
            if (RealID == 1) Player = &Player1;
            else if (RealID == 2) Player = &Player2;
            else if (RealID == 3) Player = &Player3;
            else if (RealID == 4) Player = &Player4;
            else Player = &Player1;
            bool isPlayerInRange = Player->InRange(12512, 10704, 12592, 10752);
            if (isPlayerInRange && !CreditsSelected)
            {
                CreditsSelected = true;
                P1_IsInWarpRoom = true;
                P2_IsInWarpRoom = true;
                P3_IsInWarpRoom = true;
                P4_IsInWarpRoom = true;
            }
        }
    }

    void CreditsWarpLoop(bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
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
            P1_IsInWarpRoom = false;
            P2_IsInWarpRoom = false;
            P3_IsInWarpRoom = false;
            P4_IsInWarpRoom = false;
            CompPlus_Common::LoadLevel_IZ("CPCREDITS");
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

	void OnFrame() 
	{	
        
        CreditsWarp();
		SetHUBVisualSettings();
        UpdateQuickWarpRoom();

        if (SonicMania::Timer.Enabled == false && SonicMania::Options->CompetitionSession.NumberOfPlayers >= 2) isRestart = true;

        if (isRestart) 
        {
            SetSpawnPositions();
            ResetWarps();
            isRestart = false;
        }

		SonicMania::EntityButton& ConfirmButton = *GetEntityFromSceneSlot<SonicMania::EntityButton>(EnterLSelectButton);

		UpdateHUBPositions();
		CheckSettings();
		UpdateHUBDisplays();

		if (ConfirmButton.Pressed) LevelSelected = true;
		

        if (CreditsSelected) CreditsWarpLoop(true, SceneLoadWaitTimer, SceneLoadWaitMax, CreditsSelected, LevelSelectedWarpSoundPlayed);

		if (LevelSelected) WarpLoop(true, SceneLoadWaitTimer, SceneLoadWaitMax, LevelSelected, LevelSelectedWarpSoundPlayed);
        
	}

	void WarpLoop(bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
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
			CompPlus_Common::LoadLevel(66);
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
        for (int i = 0; i < 120; ++i)
            Strings[i] = (wchar_t*)malloc(128);
    }

    #pragma endregion


}