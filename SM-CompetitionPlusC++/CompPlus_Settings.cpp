#include "stdafx.h"
#include "CompPlus_Settings.h"
#include "IZAPI.h"
#include "CompPlus_Core.h"
#include "SonicMania.h"
#include "ManiaExt.h"
#include "depends/tinyxml2/tinyxml2.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "Helpers.h"

namespace CompPlus_Settings 
{
	using namespace SonicMania;

    #pragma region Internal Variables

    int NumberOfAnnouncers = 6;
    bool FixPlayers = false;
    std::string Settings_FilePath;
    bool SettingsLoaded = false;
    int DevMode_ControllerSwapPosition = 0;

    bool HasCopiedOriginalTimeCode = false;
    bool IsLimitedWriten = false;
    bool IsUnlimitedWriten = false;
    char ETA_OriginalCode[0x02];
    char TLK_OriginalCode[0x06];

    bool isUnlockWriten = false;
    bool isLockWriten = false;
    bool isVSControllerInputUnlocked = false;
    bool HasCopiedOriginalControlUnlockCode = false;
    char ControlLock_OriginalCode[0x06];


    bool DevMenuEnabledMemory;

    Controller InitalInputP1;
    Controller InitalInputP2;
    Controller InitalInputP3;
    Controller InitalInputP4;

    bool P1_InputSaved = false;
    bool P2_InputSaved = false;
    bool P3_InputSaved = false;
    bool P4_InputSaved = false;

    bool InitalInputCollected = false;


    #pragma endregion


    #pragma region Setting Variables

    //Developer Settings
    bool EnableDevMode = true;
    bool EnableDebugMode = true;
    bool DevMode_ControllerSwap = false;
    bool DarkDevMenu = true;

    bool DevMode_ControlPlayer1 = true;
    bool DevMode_ControlPlayer2 = false;
    bool DevMode_ControlPlayer3 = false;
    bool DevMode_ControlPlayer4 = false;

    bool LHPZ_SecretUnlocked = false;

    //Stock Competition Settings
    int NumberOfRounds = 3; // Ignored when EndlessRounds = true;
    ItemsConfig MonitorTypes = ItemsConfig_Default;

    //Competition Plus Settings
    int InitalLives = 3;
    bool InfiniteLives = false;
    bool TimeLimit = false;
    bool EndlessRounds = false;
    bool DropdashAbility = true;
    bool InstaSheildAbility = false;
    VictoryMode VictoryStyle = VictoryMode_Time;
    AnnouncerType CurrentAnnouncer = Announcer_Default;
    SpeedShoesModification SpeedShoesMode = SpeedShoesModification_Default;

    ThreeStateBool Player1PeeloutAbility = ThreeStateBool::Indeterminate;
    ThreeStateBool Player2PeeloutAbility = ThreeStateBool::Indeterminate;
    ThreeStateBool Player3PeeloutAbility = ThreeStateBool::Indeterminate;
    ThreeStateBool Player4PeeloutAbility = ThreeStateBool::Indeterminate;

    ChosenPlayer Player1ChosenPlayer = ChosenPlayer_Sonic;
    ChosenPlayer Player2ChosenPlayer = ChosenPlayer_Tails;
    ChosenPlayer Player3ChosenPlayer = ChosenPlayer_Knuckles;
    ChosenPlayer Player4ChosenPlayer = ChosenPlayer_Mighty;

    PlayerAbility Player1AbilitySet = AbilitySet_Compatibility;
    PlayerAbility Player2AbilitySet = AbilitySet_Compatibility;
    PlayerAbility Player3AbilitySet = AbilitySet_Compatibility;
    PlayerAbility Player4AbilitySet = AbilitySet_Compatibility;

    //Status States
    int CurrentLevelSelect = 0;

    #pragma endregion

    #pragma region Get Methods

    SonicMania::Character GetCharacter(CompPlus_Settings::ChosenPlayer Character)
    {
        if (Character == ChosenPlayer_Sonic) return SonicMania::Character_Sonic;
        else if (Character == ChosenPlayer_Tails) return SonicMania::Character_Tails;
        else if (Character == ChosenPlayer_Knuckles) return SonicMania::Character_Knux;
        else if (Character == ChosenPlayer_Mighty) return SonicMania::Character_Mighty;
        else if (Character == ChosenPlayer_Ray) return SonicMania::Character_Ray;
        else return SonicMania::Character_None;
    }

    #pragma endregion

    #pragma region Fix Methods

    void DisableVSPointAddingAddress() 
    {
        void* vs_incrementing_address = (void*)(baseAddress + 0xE35C);
        char nops[2];
        memset(nops, 0x90, sizeof nops);
        WriteData(vs_incrementing_address, nops, 0x02);
    }

    void FixUnmatchingVSPlayers()
    {
        SonicMania::Character P1_Char = (SonicMania::Character)(SonicMania::Options->CompetitionSession.CharacterFlags >> 0x00 & 0xFF >> 1);
        SonicMania::Character P2_Char = (SonicMania::Character)(SonicMania::Options->CompetitionSession.CharacterFlags >> 0x08 & 0xFF >> 1);
        SonicMania::Character P3_Char = (SonicMania::Character)(SonicMania::Options->CompetitionSession.CharacterFlags >> 0x10 & 0xFF >> 1);
        SonicMania::Character P4_Char = (SonicMania::Character)(SonicMania::Options->CompetitionSession.CharacterFlags >> 0x18 & 0xFF >> 1);

        CompPlus_Settings::UpdatePlayer(1, P1_Char, true);
        CompPlus_Settings::UpdatePlayer(2, P2_Char, true);
        CompPlus_Settings::UpdatePlayer(3, P3_Char, true);
        CompPlus_Settings::UpdatePlayer(4, P4_Char, true);
    }

    void FixRayAndMighty2P()
    {
        int PatchP2Ray[] = { 0xE9, 0xC4, 0x01, 0x00, 0x00, 0x90 };
        int i;
        int OffsetNormal = 0xC31E5;
        for (i = 0; i < 6; i++)
        {
            WriteData<1>((void*)(baseAddress + OffsetNormal), PatchP2Ray[i]);//put data back.
            OffsetNormal++;

        }
    }

    #pragma endregion

    #pragma region Update Player Methods

    void UpdatePlayerSprites(SonicMania::EntityPlayer& Player)
    {
        if (Player.Character == Characters_Sonic)
        {
            if (Player.State == PLAYERSTATE_HAMMERDROP)
            {
                //Player.Animation.CurrentAnimation = 54; //551
                //SetSpriteAnimation(0, 54, &Player.Animation, true, 6);
            }
        }
    }

    void UpdateMultiPlayerSprites()
    {
        UpdatePlayerSprites(Player1);
        UpdatePlayerSprites(Player2);
        UpdatePlayerSprites(Player3);
        UpdatePlayerSprites(Player4);
    }

    void UpdateSonicAbilities()
    {
        //21 : No Dropdash or Instasheild     - (CD)
        //13 : Dropdash and Instasheild		  - (Max Control)
        //2  : Dropdash Only			      - (Mania)
        //8  : Instasheild Only		          - (S3&K)

        int MovesetID = 22;

        if (DropdashAbility && InstaSheildAbility) MovesetID = 13;	      // Max Control Moveset
        else if (DropdashAbility && !InstaSheildAbility) MovesetID = 0;	  // Mania Moveset
        else if (!DropdashAbility && InstaSheildAbility) MovesetID = 8;	  // S3&K Moveset
        else if (!DropdashAbility && !InstaSheildAbility) MovesetID = 21; // CD Moveset


        BYTE* Pointer = *(BYTE**)((baseAddress + 0xAA763C));
        WriteData((BYTE*)(Pointer + 0x410B4), (BYTE)MovesetID);
    }

    void UpdatePlayer(int PlayerID, SonicMania::Character Character, bool Force)
    {
        CompPlus_Settings::ChosenPlayer Player = CompPlus_Settings::ChosenPlayer_Default;

        if (Character == Characters_Sonic) Player = CompPlus_Settings::ChosenPlayer_Sonic;
        else if (Character == Characters_Tails) Player = CompPlus_Settings::ChosenPlayer_Tails;
        else if (Character == Characters_Knuckles) Player = CompPlus_Settings::ChosenPlayer_Knuckles;
        else if (Character == Character_Mighty) Player = CompPlus_Settings::ChosenPlayer_Mighty;
        else if (Character == Characters_Ray) Player = CompPlus_Settings::ChosenPlayer_Ray;

        int CharacterID = (int)Character;
        //SonicMania::Options->CompetitionSession.CharacterFlags &= 0xFFFFFFFF ^ (0xFF << (PlayerID - 1));

        if (PlayerID == 1)
        {
            if (Force) SonicMania::Player1.Character = Character;
            Player1.Character = Character;
            SonicMania::Options->CompetitionSession.CharacterFlags |= Character << (0 * 8);
            CompPlus_Settings::Player1ChosenPlayer = Player;
        }
        else if (PlayerID == 2)
        {
            if (Force) SonicMania::Player2.Character = Character;
            Player2.Character = Character;
            SonicMania::Options->CompetitionSession.CharacterFlags |= Character << (1 * 8);
            CompPlus_Settings::Player2ChosenPlayer = Player;
        }
        else if (PlayerID == 3)
        {
            if (Force) SonicMania::Player3.Character = Character;
            Player3.Character = Character;
            SonicMania::Options->CompetitionSession.CharacterFlags |= Character << (2 * 8);
            CompPlus_Settings::Player3ChosenPlayer = Player;
        }
        else if (PlayerID == 4)
        {
            if (Force) SonicMania::Player4.Character = Character;
            Player4.Character = Character;
            SonicMania::Options->CompetitionSession.CharacterFlags |= Character << (3 * 8);
            CompPlus_Settings::Player4ChosenPlayer = Player;
        }
        FixRayAndMighty2P();
    }

    void UpdatePlayer(int PlayerID, CompPlus_Settings::ChosenPlayer Character, bool Force)
    {
        SonicMania::Character Player = SonicMania::Character_None;

        if (Character == ChosenPlayer_Sonic) Player = SonicMania::Character_Sonic;
        else if (Character == ChosenPlayer_Tails) Player = SonicMania::Character_Tails;
        else if (Character == ChosenPlayer_Knuckles) Player = SonicMania::Character_Knux;
        else if (Character == ChosenPlayer_Mighty) Player = SonicMania::Character_Mighty;
        else if (Character == ChosenPlayer_Ray) Player = SonicMania::Character_Ray;
        else if (Character == ChosenPlayer_Default)
        {
            if (PlayerID == 1) Player = Player1.Character;
            if (PlayerID == 2) Player = Player2.Character;
            if (PlayerID == 3) Player = Player3.Character;
            if (PlayerID == 4) Player = Player4.Character;
        }

        UpdatePlayer(PlayerID, Player, Force);
    }

    #pragma endregion

    #pragma region Change Settings Methods

    void SetMonitorMode(CompPlus_Settings::ItemsConfig Value) 
    {
        MonitorTypes = Value;      
        SaveSettings();
    }

    void SetNumberOfRounds(int Value) 
    {
        NumberOfRounds = Value;     
        SaveSettings();
    }

    void SetAbility(int PlayerID, CompPlus_Settings::PlayerAbility Ability, bool Force)
	{
		if (PlayerID == 1)
		{
			CompPlus_Settings::Player1AbilitySet = Ability;
            if (!Force) return;
			if (Ability == CompPlus_Settings::AbilitySet_Sonic) Player1.Moveset = MOVESET_SONIC;
			else if (Ability == CompPlus_Settings::AbilitySet_Tails) Player1.Moveset = MOVESET_TAILS;
			else if (Ability == CompPlus_Settings::AbilitySet_Knuckles)Player1.Moveset = MOVESET_KNUX;
			else if (Ability == CompPlus_Settings::AbilitySet_Mighty) Player1.Moveset = MOVESET_MIGHTY;
			else if (Ability == CompPlus_Settings::AbilitySet_Ray) Player1.Moveset = MOVESET_RAY;
		}
		else if (PlayerID == 2)
		{
			CompPlus_Settings::Player2AbilitySet = Ability;
            if (!Force) return;
			if (Ability == CompPlus_Settings::AbilitySet_Sonic) Player2.Moveset = MOVESET_SONIC;
			else if (Ability == CompPlus_Settings::AbilitySet_Tails) Player2.Moveset = MOVESET_TAILS;
			else if (Ability == CompPlus_Settings::AbilitySet_Knuckles)Player2.Moveset = MOVESET_KNUX;
			else if (Ability == CompPlus_Settings::AbilitySet_Mighty) Player2.Moveset = MOVESET_MIGHTY;
			else if (Ability == CompPlus_Settings::AbilitySet_Ray) Player2.Moveset = MOVESET_RAY;
		}
		else if (PlayerID == 3)
		{
			CompPlus_Settings::Player3AbilitySet = Ability;
            if (!Force) return;
			if (Ability == CompPlus_Settings::AbilitySet_Sonic) Player3.Moveset = MOVESET_SONIC;
			else if (Ability == CompPlus_Settings::AbilitySet_Tails) Player3.Moveset = MOVESET_TAILS;
			else if (Ability == CompPlus_Settings::AbilitySet_Knuckles)Player3.Moveset = MOVESET_KNUX;
			else if (Ability == CompPlus_Settings::AbilitySet_Mighty) Player3.Moveset = MOVESET_MIGHTY;
			else if (Ability == CompPlus_Settings::AbilitySet_Ray) Player3.Moveset = MOVESET_RAY;
		}
		else if (PlayerID == 4)
		{
			CompPlus_Settings::Player4AbilitySet = Ability;
            if (!Force) return;
			if (Ability == CompPlus_Settings::AbilitySet_Sonic) Player4.Moveset = MOVESET_SONIC;
			else if (Ability == CompPlus_Settings::AbilitySet_Tails) Player4.Moveset = MOVESET_TAILS;
			else if (Ability == CompPlus_Settings::AbilitySet_Knuckles)Player4.Moveset = MOVESET_KNUX;
			else if (Ability == CompPlus_Settings::AbilitySet_Mighty) Player4.Moveset = MOVESET_MIGHTY;
			else if (Ability == CompPlus_Settings::AbilitySet_Ray) Player4.Moveset = MOVESET_RAY;
		}      
	}

	void SetDropdashAbility(bool Value)
	{
		DropdashAbility = Value;
		UpdateSonicAbilities();       
        SaveSettings();
	}

	void SetPeeloutAbility(int PlayerID, ThreeStateBool State)
	{
		SonicMania::Ability PeeloutState = MOVESET_NONE;
		if (State == ThreeStateBool::True) PeeloutState = UpAbility_Peelout;

		if (PlayerID == 1 && State != ThreeStateBool::Indeterminate)
		{
			Player1.UpAbility = PeeloutState;
			CompPlus_Settings::Player1PeeloutAbility = State;
		}
		else if (PlayerID == 2 && State != ThreeStateBool::Indeterminate)
		{
			Player2.UpAbility = PeeloutState;
			CompPlus_Settings::Player2PeeloutAbility = State;
		}
		else if (PlayerID == 3 && State != ThreeStateBool::Indeterminate)
		{
			Player3.UpAbility = PeeloutState;
			CompPlus_Settings::Player3PeeloutAbility = State;
		}
		else if (PlayerID == 4 && State != ThreeStateBool::Indeterminate)
		{
			Player4.UpAbility = PeeloutState;
			CompPlus_Settings::Player4PeeloutAbility = State;
		}
		UpdateSonicAbilities();  
	}

	void SetInstaSheildAbility(bool State)
	{
		InstaSheildAbility = State;
		UpdateSonicAbilities();   
        SaveSettings();
	}
    
    void SetInitalLives(int value)
    {
        InitalLives = value;

        if (InitalLives == 100) InfiniteLives = true;
        else InfiniteLives = false; 

        SaveSettings();
    }

    void SetAnnouncer(AnnouncerType Value)
    {
        CurrentAnnouncer = Value;    
        SaveSettings();
    }

    void SetTimeLimit(bool State) 
    {
        TimeLimit = State;       
        SaveSettings();
    }

    void SetVictoryMethod(CompPlus_Settings::VictoryMode State) 
    {
        VictoryStyle = State;
        SaveSettings();
    }

    void SetEndlessRounds(bool State)
    {
        EndlessRounds = State;       
        SaveSettings();
    }

    void SetCurrentLSelect(int value)
    {
        CurrentLevelSelect = value;      
        SaveSettings();
    }

    #pragma endregion



    #pragma region Update Methods

    void UpdateVSControlLockState()
    {
        void* vs_player_freeze_address = (void*)(baseAddress + 0xC3E2B);
        // NOP bytes
        char nops[6];
        memset(nops, 0x90, sizeof nops);


        if (!HasCopiedOriginalControlUnlockCode)
        {
            memcpy(ControlLock_OriginalCode, vs_player_freeze_address, 0x06);
            HasCopiedOriginalControlUnlockCode = true;
        }

        if (!isVSControllerInputUnlocked)
        {
            if (!isLockWriten)
            {
                WriteData(vs_player_freeze_address, ControlLock_OriginalCode, 0x06);
                isUnlockWriten = false;
                isLockWriten = true;
            }
        }
        else
        {
            if (!isUnlockWriten)
            {
                WriteData(vs_player_freeze_address, nops, 0x06);
                isLockWriten = false;
                isUnlockWriten = true;
            }
        }
    }

    void UpdateStockSettings() 
    {
        DisableVSPointAddingAddress();
        if (SonicMania::Options->CompetitionSession.MonitorMode != MonitorTypes) SonicMania::Options->CompetitionSession.MonitorMode = MonitorTypes;
        if (SonicMania::Options->ItemMode != MonitorTypes) SonicMania::Options->ItemMode = MonitorTypes;
    }

    void UpdateLives()
    {
        if (InfiniteLives)
        {
            SonicMania::Player1.LifeCount = 99;
            SonicMania::Player2.LifeCount = 99;
            SonicMania::Player3.LifeCount = 99;
            SonicMania::Player4.LifeCount = 99;

            SonicMania::Options->CompetitionSession.InitalLives_P1 = 99;
            SonicMania::Options->CompetitionSession.InitalLives_P2 = 99;
            SonicMania::Options->CompetitionSession.InitalLives_P3 = 99;
            SonicMania::Options->CompetitionSession.InitalLives_P4 = 99;
        }
        else 
        {
            SonicMania::Options->CompetitionSession.InitalLives_P1 = InitalLives;
            SonicMania::Options->CompetitionSession.InitalLives_P2 = InitalLives;
            SonicMania::Options->CompetitionSession.InitalLives_P3 = InitalLives;
            SonicMania::Options->CompetitionSession.InitalLives_P4 = InitalLives;
        }
    }

    void UpdateTimer()
    {
        void* extended_time_address = (void*)(baseAddress + 0x535BD);
        void* time_limit_kill_jne_address = (void*)(baseAddress + 0xADD03);
        void* time_limit_skip_jne_adderss = (void*)(baseAddress + 0x00ADDE7);
        void* time_limit_kill_jmp_nop_address = (void*)(baseAddress + 0xADD03 + 0x5);
        // NOP bytes
        char nops1[4];
        char nops2[8];
        memset(nops1, 0x90, sizeof nops1);
        memset(nops2, 0x90, sizeof nops2);

        if (!HasCopiedOriginalTimeCode)
        {
            memcpy(ETA_OriginalCode, extended_time_address, 0x02);
            memcpy(TLK_OriginalCode, time_limit_kill_jne_address, 0x06);
            HasCopiedOriginalTimeCode = true;
        }

        if (!TimeLimit)
        {
            if (!IsUnlimitedWriten)
            {
                WriteData(extended_time_address, nops2, 0x02);
                ReplaceJNEwithJump(time_limit_kill_jne_address, time_limit_skip_jne_adderss);
                WriteData(time_limit_kill_jmp_nop_address, nops1, 0x06);
                IsUnlimitedWriten = true;
                IsLimitedWriten = false;
            }
        }
        else
        {
            if (!IsLimitedWriten)
            {
                WriteData(extended_time_address, ETA_OriginalCode, 0x02);
                WriteData(time_limit_kill_jne_address, TLK_OriginalCode, 0x06);
                IsLimitedWriten = true;
                IsUnlimitedWriten = false;
            }
        }
    }

    #pragma endregion

    #pragma region DevMode Methods

    void DevMode_WarpAllPlayersTo(int PlayerID)
    {
        int x, y;
        if (PlayerID == 4)
        {
            x = Player4.Position.X;
            y = Player4.Position.Y;
        }
        else if (PlayerID == 3)
        {
            x = Player3.Position.X;
            y = Player3.Position.Y;
        }
        else if (PlayerID == 2)
        {
            x = Player2.Position.X;
            y = Player2.Position.Y;
        }
        else
        {
            x = Player1.Position.X;
            y = Player1.Position.Y;
        }

        Player1.Position.X = x;
        Player1.Position.Y = y;

        Player2.Position.X = x;
        Player2.Position.Y = y;

        Player3.Position.X = x;
        Player3.Position.Y = y;

        Player4.Position.X = x;
        Player4.Position.Y = y;
    }

    void DevMode_BindPlayer1()
    {
        if (DevMode_ControlPlayer1 || !EnableDevMode)
        {
            if (P1_InputSaved)
            {
                SonicMania::PlayerControllers[1] = InitalInputP1;
                P1_InputSaved = false;
            }
            InitalInputP1 = SonicMania::PlayerControllers[1];
        }

        if (!DevMode_ControlPlayer1)
        {
            if (!P1_InputSaved)
            {
                InitalInputP1 = SonicMania::PlayerControllers[1];
                P1_InputSaved = true;

                SonicMania::PlayerControllers[1].A.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].B.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].C.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].X.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Y.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Z.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Up.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Down.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Left.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Right.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Start.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Select.Key = (DWORD)0x0;
            }

        }
    }

    void DevMode_BindController(int TargetPlayerID)
    {
        switch (TargetPlayerID)
        {
        case 2:
            if (!P2_InputSaved)
            {
                InitalInputP2 = SonicMania::PlayerControllers[TargetPlayerID];
                P2_InputSaved = true;
            }
            break;
        case 3:
            if (!P3_InputSaved)
            {
                InitalInputP3 = SonicMania::PlayerControllers[TargetPlayerID];
                P3_InputSaved = true;
            }
            break;
        case 4:
            if (!P4_InputSaved)
            {
                InitalInputP4 = SonicMania::PlayerControllers[TargetPlayerID];
                P4_InputSaved = true;
            }
            break;
        }

        SonicMania::PlayerControllers[TargetPlayerID].A.Key = InitalInputP1.A.Key;
        SonicMania::PlayerControllers[TargetPlayerID].B.Key = InitalInputP1.B.Key;
        SonicMania::PlayerControllers[TargetPlayerID].C.Key = InitalInputP1.C.Key;
        SonicMania::PlayerControllers[TargetPlayerID].X.Key = InitalInputP1.X.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Y.Key = InitalInputP1.Y.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Z.Key = InitalInputP1.Z.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Up.Key = InitalInputP1.Up.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Down.Key = InitalInputP1.Down.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Left.Key = InitalInputP1.Left.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Right.Key = InitalInputP1.Right.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Start.Key = InitalInputP1.Start.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Select.Key = InitalInputP1.Select.Key;

    }

    void DevMode_RestoreController(int TargetPlayerID)
    {
        switch (TargetPlayerID)
        {
        case 2:
            if (P2_InputSaved)
            {
                SonicMania::PlayerControllers[TargetPlayerID] = InitalInputP2;
                P2_InputSaved = false;
            }
            break;
        case 3:
            if (P3_InputSaved)
            {
                SonicMania::PlayerControllers[TargetPlayerID] = InitalInputP3;
                P3_InputSaved = false;
            }
            break;
        case 4:
            if (P4_InputSaved)
            {
                SonicMania::PlayerControllers[TargetPlayerID] = InitalInputP4;
                P4_InputSaved = false;
            }
            break;
        }
    }

    void DevModeLoop()
    {
        if (EnableDebugMode)
        {
            DebugEnabled = 1;
        }

        DevMode_BindPlayer1();

        if (EnableDevMode)
        {
            if (DevMode_ControlPlayer2) DevMode_BindController(2);
            else DevMode_RestoreController(2);

            if (DevMode_ControlPlayer3) DevMode_BindController(3);
            else DevMode_RestoreController(3);

            if (DevMode_ControlPlayer4) DevMode_BindController(4);
            else DevMode_RestoreController(4);
        }
        else
        {
            DevMode_RestoreController(2);
            DevMode_RestoreController(3);
            DevMode_RestoreController(4);
        }
    }

    #pragma endregion

    #pragma region Settings Methods

    void RefreshSettings()
    {
        SetAbility(1, Player1AbilitySet, true);
        SetPeeloutAbility(1, Player1PeeloutAbility);

        SetAbility(2, Player2AbilitySet, true);
        SetPeeloutAbility(2, Player2PeeloutAbility);

        SetAbility(3, Player3AbilitySet, true);
        SetPeeloutAbility(3, Player3PeeloutAbility);

        SetAbility(4, Player4AbilitySet, true);
        SetPeeloutAbility(4, Player4PeeloutAbility);

        UpdateSonicAbilities();

        FixPlayers = true;
    }

    void LogLoadSetting(const char* Name, std::string Value)
    {
        std::string output = Name;
        output += " = " + Value;
        LogInfo("LoadXML", output.c_str());
    }

    void LogSaveSetting(const char* Name, std::string Value)
    {
        std::string output = Name;
        output += " = " + Value;
        LogInfo("SaveXML", output.c_str());
    }

    int XMLGetInt(tinyxml2::XMLElement* xmlOption)
    {
        const char* str_value = xmlOption->GetText();
        int value = atoi(str_value);
        return value;
    }

    bool XMLGetBool(tinyxml2::XMLElement* xmlOption)
    {
        const char* str_value = xmlOption->GetText();
        bool value;
        if ((!strcmp(str_value, "1"))) value = true;
        else value = false;

        return value;
    }

    void LoadSettings()
    {
        std::string message = "Loading \"";
        message += Settings_FilePath;
        message += "\"...";
        LogInfo("CompPlus_Settings::LoadSettings", message.c_str());
        unsigned int size = 0;

        // Open file
        std::ifstream file(Settings_FilePath);

        // Get size and allocate memory
        file.seekg(0, std::ios::end);
        size = static_cast<unsigned int>(file.tellg());
        char* xml = (char*)malloc(size);
        file.seekg(0, std::ios::beg);

        // Read file
        file.read(xml, size);

        if (xml && size)
        {
            LogInfo("CompPlus_Settings::LoadSettings", "Prasing File....");
            tinyxml2::XMLDocument document;
            document.Parse(static_cast<const char*>(xml), size);

            auto xmlSettings = document.FirstChildElement("Settings");
            if (xmlSettings)
            {
                for (auto xmlOption = xmlSettings->FirstChildElement(); xmlOption != nullptr; xmlOption = xmlOption->NextSiblingElement())
                {
                    if (!strcmp(xmlOption->Name(), "SelectedAnnouncer"))
                    {
                        int value = XMLGetInt(xmlOption);
                        CurrentAnnouncer = (AnnouncerType)value;

                        LogLoadSetting("SelectedAnnouncer", std::to_string(value));
                    }
                    else if (!strcmp(xmlOption->Name(), "InitalLives"))
                    {
                        int value = XMLGetInt(xmlOption);
                        InitalLives = value;

                        LogLoadSetting("InitalLives", std::to_string(value));
                    }
                    else if (!strcmp(xmlOption->Name(), "TimeLimit"))
                    {
                        bool value = XMLGetBool(xmlOption);
                        TimeLimit = value;

                        LogLoadSetting("TimeLimit", std::to_string(value));
                    }
                    else if (!strcmp(xmlOption->Name(), "UseDropdash"))
                    {
                        bool value = XMLGetBool(xmlOption);
                        DropdashAbility = value;

                        LogLoadSetting("UseDropdash", std::to_string(value));
                    }
                    else if (!strcmp(xmlOption->Name(), "UseInstaSheild"))
                    {
                        bool value = XMLGetBool(xmlOption);
                        InstaSheildAbility = value;

                        LogLoadSetting("UseInstaSheild", std::to_string(value));
                    }
                    else if (!strcmp(xmlOption->Name(), "CurrentLSelect"))
                    {
                        int value = XMLGetInt(xmlOption);
                        CurrentLevelSelect = value;

                        LogLoadSetting("CurrentLSelect", std::to_string(value));
                    }
                    else if (!strcmp(xmlOption->Name(), "VictoryStyle"))
                    {
                        int value = XMLGetInt(xmlOption);
                        VictoryStyle = (VictoryMode)value;

                        LogLoadSetting("VictoryStyle", std::to_string(value));
                    }
                    else if (!strcmp(xmlOption->Name(), "EndlessRounds"))
                    {
                        bool value = XMLGetBool(xmlOption);
                        EndlessRounds = value;

                        LogLoadSetting("EndlessRounds", std::to_string(value));
                    }
                    else if (!strcmp(xmlOption->Name(), "MonitorMode"))
                    {
                        int value = XMLGetInt(xmlOption);
                        MonitorTypes = (ItemsConfig)value;

                        LogLoadSetting("MonitorMode", std::to_string(value));
                    }
                    else if (!strcmp(xmlOption->Name(), "NumberOfRounds"))
                    {
                        int value = XMLGetInt(xmlOption);
                        NumberOfRounds = value;

                        LogLoadSetting("NumberOfRounds", std::to_string(value));
                    }
                    else if (!strcmp(xmlOption->Name(), "EnableDebugMode"))
                    {
                        bool value = XMLGetBool(xmlOption);
                        EnableDebugMode = value;

                        LogLoadSetting("EnableDebugMode", std::to_string(value));
                    }
                    else if (!strcmp(xmlOption->Name(), "EnableDevMode"))
                    {
                        bool value = XMLGetBool(xmlOption);
                        EnableDevMode = value;

                        LogLoadSetting("EnableDevMode", std::to_string(value));
                    }
                    else if (!strcmp(xmlOption->Name(), "DarkDevMenu"))
                    {
                        bool value = XMLGetBool(xmlOption);
                        DarkDevMenu = value;

                        LogLoadSetting("DarkDevMenu", std::to_string(value));
                    }
                    else if (!strcmp(xmlOption->Name(), "LHPZ_SecretUnlocked"))
                    {
                    bool value = XMLGetBool(xmlOption);
                    LHPZ_SecretUnlocked = value;

                    LogLoadSetting("LHPZ_SecretUnlocked", std::to_string(value));
                    }
                }
            }
            else
            {
                LogError("CompPlus_Settings::LoadSettings", "Unable to Read File....");
            }
        }
        // Clean up
        free(xml);

        file.close();
        SettingsLoaded = true;
    }

    void AddtoSaveSettings(std::string Name, std::string Value, std::string& text)
    {
        text += "<" + Name + ">" + Value + "</" + Name + ">";
        LogSaveSetting(Name.c_str(), Value);
    }

    void SaveSettings()
    {
        if (SettingsLoaded) 
        {
            LogInfo("CompPlus_Settings::SaveSettings", "Saving XML File....");
            tinyxml2::XMLDocument document;

            std::string text = "<Settings>";
            AddtoSaveSettings("SelectedAnnouncer", IntToString(CurrentAnnouncer), text);
            AddtoSaveSettings("CurrentLSelect", IntToString(CurrentLevelSelect), text);
            AddtoSaveSettings("VictoryStyle", IntToString(VictoryStyle), text);

            AddtoSaveSettings("UseDropdash", BoolToString(DropdashAbility), text);
            AddtoSaveSettings("UseInstaSheild", BoolToString(InstaSheildAbility), text);

            AddtoSaveSettings("InitalLives", IntToString(InitalLives), text);
            AddtoSaveSettings("TimeLimit", IntToString(TimeLimit), text);
            AddtoSaveSettings("EndlessRounds", BoolToString(EndlessRounds), text);
            AddtoSaveSettings("NumberOfRounds", IntToString(NumberOfRounds), text);
            AddtoSaveSettings("MonitorMode", IntToString(MonitorTypes), text);

            AddtoSaveSettings("EnableDebugMode", BoolToString(EnableDebugMode), text);
            AddtoSaveSettings("EnableDevMode", BoolToString(EnableDevMode), text);
            AddtoSaveSettings("DarkDevMenu", BoolToString(DarkDevMenu), text);
            if (LHPZ_SecretUnlocked == true) AddtoSaveSettings("LHPZ_SecretUnlocked", BoolToString(LHPZ_SecretUnlocked), text);

            text += "</Settings>";
            document.Parse((const char*)text.c_str());
            tinyxml2::XMLError error = document.SaveFile(Settings_FilePath.c_str(), true);
            if (error != 0) 
            {
                LogError("CompPlus_Settings::SaveSettings", "Error Saving File!");
            }
            else 
            {
                LogInfo("CompPlus_Settings::SaveSettings", "Saved Successfully!");
            }
        }
    }

    #pragma endregion

    void OnFixPlayers() 
    {

        if (FixPlayers)
        {
            UpdatePlayer(1, Player1ChosenPlayer, true);
            UpdatePlayer(2, Player2ChosenPlayer, true);
            UpdatePlayer(3, Player3ChosenPlayer, true);
            UpdatePlayer(4, Player4ChosenPlayer, true);
            FixPlayers = false;
        }
    }

    void OnFrame()
    {
        if (SettingsLoaded) 
        {
            OnFixPlayers();
            UpdateVSControlLockState();
            UpdateLives();
            UpdateStockSettings();
            UpdateMultiPlayerSprites();
            UpdateTimer();
            DevModeLoop();
        }
    }


 
}