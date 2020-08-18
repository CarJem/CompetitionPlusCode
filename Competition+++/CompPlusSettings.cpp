#include "stdafx.h"
#include "CompPlusSettings.h"
#include "SonicMania.h"
#include "ManiaExt.h"

namespace CompPlusSettings 
{
	using namespace SonicMania;

	//Internal
	bool FixPlayers = false;


	//Developer Settings
	bool EnableDevMode = false;
	bool EnableDebugMode = false;


    //Gameplay Settings
    bool InfiniteLives = false;
    bool InfiniteTime = false;
    int InitalLives = 3; // Ignored when InfiniteLives = true;

    //Stock Competition Settings
    int NumberOfRounds = 2; // Ignored when EndlessRounds = true;
    ItemsConfig MonitorTypes = ItemsConfig_Default;

    //Competition Plus Settings
    bool EndlessRounds = false;
    VictoryMode VictoryStyle = VictoryMode_Default;
    AnnouncerType CurrentAnnouncer = Announcer_Default;
    SpeedShoesModification SpeedShoesMode = SpeedShoesModification_Default;

	bool DropdashAbility = true;
	bool InstaSheildAbility = false;

	bool Player1PeeloutAbility = false;
	bool Player2PeeloutAbility = false;
	bool Player3PeeloutAbility = false;
	bool Player4PeeloutAbility = false;

    ChosenPlayer Player1ChosenPlayer = ChosenPlayer_Sonic;
    ChosenPlayer Player2ChosenPlayer = ChosenPlayer_Tails;
    ChosenPlayer Player3ChosenPlayer = ChosenPlayer_Default;
    ChosenPlayer Player4ChosenPlayer = ChosenPlayer_Default;

    PlayerAbility Player1AbilitySet = AbilitySet_Default;
    PlayerAbility Player2AbilitySet = AbilitySet_Default;
    PlayerAbility Player3AbilitySet = AbilitySet_Default;
    PlayerAbility Player4AbilitySet = AbilitySet_Default;

	void SetAbility(int PlayerID, CompPlusSettings::PlayerAbility Ability)
	{
		if (PlayerID == 1)
		{
			CompPlusSettings::Player1AbilitySet = Ability;
			if (Ability == CompPlusSettings::AbilitySet_Sonic) Player1.Moveset = MOVESET_SONIC;
			else if (Ability == CompPlusSettings::AbilitySet_Tails) Player1.Moveset = MOVESET_TAILS;
			else if (Ability == CompPlusSettings::AbilitySet_Knuckles)Player1.Moveset = MOVESET_KNUX;
			else if (Ability == CompPlusSettings::AbilitySet_Mighty) Player1.Moveset = MOVESET_MIGHTY;
			else if (Ability == CompPlusSettings::AbilitySet_Ray) Player1.Moveset = MOVESET_RAY;
		}
		else if (PlayerID == 2)
		{
			CompPlusSettings::Player2AbilitySet = Ability;
			if (Ability == CompPlusSettings::AbilitySet_Sonic) Player2.Moveset = MOVESET_SONIC;
			else if (Ability == CompPlusSettings::AbilitySet_Tails) Player2.Moveset = MOVESET_TAILS;
			else if (Ability == CompPlusSettings::AbilitySet_Knuckles)Player2.Moveset = MOVESET_KNUX;
			else if (Ability == CompPlusSettings::AbilitySet_Mighty) Player2.Moveset = MOVESET_MIGHTY;
			else if (Ability == CompPlusSettings::AbilitySet_Ray) Player2.Moveset = MOVESET_RAY;
		}
		else if (PlayerID == 3)
		{
			CompPlusSettings::Player3AbilitySet = Ability;
			if (Ability == CompPlusSettings::AbilitySet_Sonic) Player3.Moveset = MOVESET_SONIC;
			else if (Ability == CompPlusSettings::AbilitySet_Tails) Player3.Moveset = MOVESET_TAILS;
			else if (Ability == CompPlusSettings::AbilitySet_Knuckles)Player3.Moveset = MOVESET_KNUX;
			else if (Ability == CompPlusSettings::AbilitySet_Mighty) Player3.Moveset = MOVESET_MIGHTY;
			else if (Ability == CompPlusSettings::AbilitySet_Ray) Player3.Moveset = MOVESET_RAY;
		}
		else if (PlayerID == 4)
		{
			CompPlusSettings::Player4AbilitySet = Ability;
			if (Ability == CompPlusSettings::AbilitySet_Sonic) Player4.Moveset = MOVESET_SONIC;
			else if (Ability == CompPlusSettings::AbilitySet_Tails) Player4.Moveset = MOVESET_TAILS;
			else if (Ability == CompPlusSettings::AbilitySet_Knuckles)Player4.Moveset = MOVESET_KNUX;
			else if (Ability == CompPlusSettings::AbilitySet_Mighty) Player4.Moveset = MOVESET_MIGHTY;
			else if (Ability == CompPlusSettings::AbilitySet_Ray) Player4.Moveset = MOVESET_RAY;
		}
	}
		
	void SetSonicAbilites()
	{
		//21 : No Dropdash or Instasheild     - (CD)
		//13 : Dropdash and Instasheild		  - (Max Control)
		//2  : Dropdash Only			      - (Mania)
		//8  : Instasheild Only		          - (S3&K)

		int MovesetID = 21;

		if (DropdashAbility && InstaSheildAbility) MovesetID = 13;			// Max Control Moveset
		else if (DropdashAbility && !InstaSheildAbility) MovesetID = 2;	// Mania Moveset
		else if (!DropdashAbility && InstaSheildAbility) MovesetID = 24;	// S3&K Moveset
		else if (!DropdashAbility && !InstaSheildAbility) MovesetID = 21;	// CD Moveset


		BYTE* Pointer = *(BYTE**)((baseAddress + 0xAA763C));
		WriteData((BYTE*)(Pointer + 0x410B4), (BYTE)MovesetID);
	}

	void SetDropdashAbility(bool State)
	{
		DropdashAbility = State;
		SetSonicAbilites();
	}

	void SetPeeloutAbility(int PlayerID, bool State)
	{
		SonicMania::Ability PeeloutState = MOVESET_NONE;
		if (State == true) PeeloutState = UpAbility_Peelout;

		if (PlayerID == 1)
		{
			Player1.UpAbility = PeeloutState;
			CompPlusSettings::Player1PeeloutAbility = State;
		}
		else if (PlayerID == 2)
		{
			Player2.UpAbility = PeeloutState;
			CompPlusSettings::Player2PeeloutAbility = State;
		}
		else if (PlayerID == 3)
		{
			Player3.UpAbility = PeeloutState;
			CompPlusSettings::Player3PeeloutAbility = State;
		}
		else if (PlayerID == 4)
		{
			Player4.UpAbility = PeeloutState;
			CompPlusSettings::Player4PeeloutAbility = State;
		}
		SetSonicAbilites();
	}

	void SetInstaSheildAbility(bool State)
	{
		InstaSheildAbility = State;
		SetSonicAbilites();
	}

	void SetPlayer(int PlayerID, SonicMania::Character Character, bool Force)
	{
		CompPlusSettings::ChosenPlayer Player = CompPlusSettings::ChosenPlayer_Default;

		if (Character == Characters_Sonic) Player = CompPlusSettings::ChosenPlayer_Sonic;
		else if (Character == Characters_Tails) Player = CompPlusSettings::ChosenPlayer_Tails;
		else if (Character == Characters_Knuckles) Player = CompPlusSettings::ChosenPlayer_Knuckles;
		else if (Character == Character_Mighty) Player = CompPlusSettings::ChosenPlayer_Mighty;
		else if (Character == Characters_Ray) Player = CompPlusSettings::ChosenPlayer_Ray;

		if (PlayerID == 1)
		{
			if (Force) SonicMania::FastChangeCharacter(&Player1, Character);
			CompPlusSettings::Player1ChosenPlayer = Player;
		}
		else if (PlayerID == 2)
		{
			if (Force) SonicMania::FastChangeCharacter(&Player2, Character);
			CompPlusSettings::Player2ChosenPlayer = Player;
		}
		else if (PlayerID == 3)
		{
			if (Force) SonicMania::FastChangeCharacter(&Player3, Character);
			CompPlusSettings::Player3ChosenPlayer = Player;
		}
		else if (PlayerID == 4)
		{
			if (Force) SonicMania::FastChangeCharacter(&Player4, Character);
			CompPlusSettings::Player4ChosenPlayer = Player;
		}
	}

	void SetPlayer(int PlayerID, CompPlusSettings::ChosenPlayer Character, bool Force)
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

		SetPlayer(PlayerID, Player, Force);
	}

	void FixAbilites(SonicMania::EntityPlayer* Player)
	{
		int RealID = 1;

		if (Player == &Player1) RealID = 1;
		else if (Player == &Player2) RealID = 2;
		else if (Player == &Player3) RealID = 3;
		else if (Player == &Player4) RealID = 4;

		if (Player->Character == Character_Sonic)
		{
			if (Player->Moveset == MOVESET_SONIC)
			{

			}
			else if (Player->Moveset == MOVESET_TAILS)
			{
				SetAbility(RealID, CompPlusSettings::AbilitySet_Mighty);
			}
			else if (Player->Moveset == MOVESET_KNUX)
			{
				SetAbility(RealID, CompPlusSettings::AbilitySet_Mighty);
			}
			else if (Player->Moveset == MOVESET_MIGHTY)
			{

			}
			else if (Player->Moveset == MOVESET_RAY)
			{
				SetAbility(RealID, CompPlusSettings::AbilitySet_Sonic);
			}
		}
		else if (Player->Character == Character_Tails)
		{
			if (Player->Moveset == MOVESET_SONIC)
			{

			}
			else if (Player->Moveset == MOVESET_TAILS)
			{

			}
			else if (Player->Moveset == MOVESET_KNUX)
			{
				SetAbility(RealID, CompPlusSettings::AbilitySet_Mighty);
			}
			else if (Player->Moveset == MOVESET_MIGHTY)
			{

			}
			else if (Player->Moveset == MOVESET_RAY)
			{
				SetAbility(RealID, CompPlusSettings::AbilitySet_Sonic);
			}
		}
		else if (Player->Character == Character_Knux)
		{
			if (Player->Moveset == MOVESET_SONIC)
			{

			}
			else if (Player->Moveset == MOVESET_TAILS)
			{
				SetAbility(RealID, CompPlusSettings::AbilitySet_Knuckles);
			}
			else if (Player->Moveset == MOVESET_KNUX)
			{

			}
			else if (Player->Moveset == MOVESET_MIGHTY)
			{

			}
			else if (Player->Moveset == MOVESET_RAY)
			{
				SetAbility(RealID, CompPlusSettings::AbilitySet_Sonic);
			}
		}
		else if (Player->Character == Character_Mighty)
		{
			if (Player->Moveset == MOVESET_SONIC)
			{

			}
			else if (Player->Moveset == MOVESET_TAILS)
			{
				SetAbility(RealID, CompPlusSettings::AbilitySet_Mighty);
			}
			else if (Player->Moveset == MOVESET_KNUX)
			{
				SetAbility(RealID, CompPlusSettings::AbilitySet_Mighty);
			}
			else if (Player->Moveset == MOVESET_MIGHTY)
			{

			}
			else if (Player->Moveset == MOVESET_RAY)
			{
				SetAbility(RealID, CompPlusSettings::AbilitySet_Sonic);
			}
		}
		else if (Player->Character == Character_Ray)
		{
			if (Player->Moveset == MOVESET_SONIC)
			{

			}
			else if (Player->Moveset == MOVESET_TAILS)
			{
				SetAbility(RealID, CompPlusSettings::AbilitySet_Mighty);
			}
			else if (Player->Moveset == MOVESET_KNUX)
			{
				SetAbility(RealID, CompPlusSettings::AbilitySet_Mighty);
			}
			else if (Player->Moveset == MOVESET_MIGHTY)
			{

			}
			else if (Player->Moveset == MOVESET_RAY)
			{

			}
		}
	}

	void StageLoadApplyConfig() 
	{
		SetAbility(1, Player1AbilitySet);
		SetAbility(2, Player2AbilitySet);
		SetAbility(3, Player3AbilitySet);
		SetAbility(4, Player4AbilitySet);

		FixAbilites(&Player1);
		FixAbilites(&Player2);
		FixAbilites(&Player3);
		FixAbilites(&Player4);

		SetPeeloutAbility(1, Player1PeeloutAbility);
		SetPeeloutAbility(2, Player2PeeloutAbility);
		SetPeeloutAbility(3, Player3PeeloutAbility);
		SetPeeloutAbility(4, Player4PeeloutAbility);

		SetSonicAbilites();

		FixPlayers = true;
	}

	void DevModeLoop() 
	{
		if (EnableDevMode) 
		{
			int x = Player1.Position.X;
			int y = Player1.Position.Y;

			Player2.Position.X = x;
			Player2.Position.Y = y;

			Player3.Position.X = x;
			Player3.Position.Y = y;

			Player4.Position.X = x;
			Player4.Position.Y = y;
		}
	}

	void DebugModeLoop() 
	{
		if (EnableDebugMode) 
		{
			DebugEnabled = 1;
		}
	}

	void UpdateSettingsLoop()
	{
		if (SonicMania::Timer.Enabled == true && FixPlayers)
		{
			//SetPlayer(1, Player1ChosenPlayer, true);
			//SetPlayer(2, Player2ChosenPlayer, true);
			//SetPlayer(3, Player3ChosenPlayer, true);
			//SetPlayer(4, Player4ChosenPlayer, true);
			FixPlayers = false;
		}

		DebugModeLoop();
		DevModeLoop();
	}
 
}