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


    //Gameplay Settings
    extern bool InfiniteLives;
    extern bool InfiniteTime;
    extern int InitalLives; // Ignored when InfiniteLives = true;

    //Stock Competition Settings
    extern int NumberOfRounds; // Ignored when EndlessRounds = true;
    extern ItemsConfig MonitorTypes;

    //Competition Plus Settings
    extern bool EndlessRounds;
    extern VictoryMode VictoryStyle;
    extern AnnouncerType CurrentAnnouncer;
    extern SpeedShoesModification SpeedShoesMode;

    // Basic Global Player Configuration : Ignored when AdvancedPlayerConfiguration = true;
    extern SonicAbility AbilitiesSonic;
    extern bool AbilitiesTails;
    extern bool AbilitiesKnuckles;
    extern bool AbilitiesRay;
    extern bool AbilitiesMighty;

    extern ChosenPlayer Player1ChosenPlayer;
    extern ChosenPlayer Player2ChosenPlayer;
    extern ChosenPlayer Player3ChosenPlayer;
    extern ChosenPlayer Player4ChosenPlayer;

    // Advanced Player Configuration
    extern bool AdvancedPlayerConfiguration;

    // Advanced Player 1 Configuration
    extern ThreeStateBool Player1Peelout;
    extern ThreeStateBool Player1Dropdash;
    extern ThreeStateBool Player1Instasheild;
    extern PlayerAbility Player1AbilitySet;

    // Advanced Player 2 Configuration
    extern ThreeStateBool Player2Peelout;
    extern ThreeStateBool Player2Dropdash;
    extern ThreeStateBool Player2Instasheild;
    extern PlayerAbility Player2AbilitySet;

    // Advanced Player 3 Configuration
    extern ThreeStateBool Player3Peelout;
    extern ThreeStateBool Player3Dropdash;
    extern ThreeStateBool Player3Instasheild;
    extern PlayerAbility Player3AbilitySet;

    // Advanced Player 4 Configuration
    extern ThreeStateBool Player4Peelout;
    extern ThreeStateBool Player4Dropdash;
    extern ThreeStateBool Player4Instasheild;
    extern PlayerAbility Player4AbilitySet;


    extern void UpdateSettingsLoop();
}

