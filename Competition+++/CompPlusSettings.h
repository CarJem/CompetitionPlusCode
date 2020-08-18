#include "SonicMania.h"
#pragma once
namespace CompPlusSettings
{
    enum ThreeStateBool : int {
        Indeterminate = 0,
        True = 1,
        False = 2
    };

    enum SpeedShoesModification : int {
        SpeedShoesModification_Default = 0,
        SpeedShoesModification_SpeedDown = 1,
        SpeedShoesModification_Freeze = 2,
        SpeedShoesModification_HighJump = 3
    };

    enum SonicAbility : int {
        SonicAbility_Dropdash = 0,
        SonicAbility_Peelout = 1,
        SonicAbility_InstaSheild = 2,
        SonicAbility_MaxControl = 3,
        SonicAbility_None = 4
    };

    enum ItemsConfig : int {
        ItemsConfig_Default = 0,
        ItemsConfig_Random = 1,
        ItemsConfig_Teleporters = 2
    };

    enum VictoryMode : int {
        VictoryMode_Default = 0,
        VictoryMode_Winner = 1
    };

    enum PlayerAbility : int {
        AbilitySet_Default = 0,
        AbilitySet_Sonic = 1,
        AbilitySet_Tails = 2,
        AbilitySet_Knuckles = 3,
        AbilitySet_Mighty = 4,
        AbilitySet_Ray = 5
    };

    enum ChosenPlayer : int {
        ChosenPlayer_Default = 0,
        ChosenPlayer_Sonic = 1,
        ChosenPlayer_Tails = 2,
        ChosenPlayer_Knuckles = 3,
        ChosenPlayer_Mighty = 4,
        ChosenPlayer_Ray = 5
    };

    enum AnnouncerType : int {
        Announcer_Default = 0,
        Announcer_Sonic2 = 1
    };

#define UpAbility_Peelout    (SonicMania::Ability)(baseAddress + 0x000C8FF0)

    //Gameplay Settings
    extern bool InfiniteLives;
    extern bool InfiniteTime;
    extern int InitalLives; // Ignored when InfiniteLives = true;

    //Developer Settings
    extern bool EnableDevMode;
    extern bool EnableDebugMode;

    //Stock Competition Settings
    extern int NumberOfRounds; // Ignored when EndlessRounds = true;
    extern ItemsConfig MonitorTypes;

    //Competition Plus Settings
    extern bool EndlessRounds;
    extern VictoryMode VictoryStyle;
    extern AnnouncerType CurrentAnnouncer;
    extern SpeedShoesModification SpeedShoesMode;

    extern bool DropdashAbility;
    extern bool InstaSheildAbility;

    extern bool Player1PeeloutAbility;
    extern bool Player2PeeloutAbility;
    extern bool Player3PeeloutAbility;
    extern bool Player4PeeloutAbility;

    extern ChosenPlayer Player1ChosenPlayer;
    extern ChosenPlayer Player2ChosenPlayer;
    extern ChosenPlayer Player3ChosenPlayer;
    extern ChosenPlayer Player4ChosenPlayer;

    extern PlayerAbility Player1AbilitySet;
    extern PlayerAbility Player2AbilitySet;
    extern PlayerAbility Player3AbilitySet;
    extern PlayerAbility Player4AbilitySet;



    extern void SetDropdashAbility(bool State);

    extern void SetPeeloutAbility(int PlayerID, bool State);

    extern void SetInstaSheildAbility(bool State);

    extern void SetAbility(int PlayerID, CompPlusSettings::PlayerAbility Ability);

    extern void SetPlayer(int PlayerID, SonicMania::Character Character, bool Force = true);

    extern void SetPlayer(int PlayerID, CompPlusSettings::ChosenPlayer Character, bool Force = true);

    extern void FixAbilites(SonicMania::EntityPlayer* Player);

    extern void StageLoadApplyConfig();

    extern void UpdateSettingsLoop();
}


