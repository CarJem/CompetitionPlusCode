#include "SonicMania.h"
#include <string>
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
        VictoryMode_Time = 1,
        VictoryMode_Score = 2,
        VictoryMode_Rings = 3,
        VictoryMode_TotalRings = 4,
        VictoryMode_Items = 5
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
        Announcer_Classic = 1,
        Announcer_Garrulous64 = 2,
        Announcer_Angelthegamer = 3,
        Announcer_Daniel = 4,
        Announcer_Memes = 5
    };

    struct ScorableInt 
    {
        int Value;
        int PlayerID = 0;

        ScorableInt() 
        {

        }

        ScorableInt(int _value, int _playerID) : ScorableInt()
        {
            Value = _value;
            PlayerID = _playerID;
        }
    };

    struct Time 
    {
        int Minutes;
        int Seconds;
        int Centiseconds;
        int PlayerID;

        Time()
        {

        }

        Time(int m, int s, int c) : Time()
        {
            Minutes = m;
            Seconds = s;
            Centiseconds = s;
        }
    };

#define UpAbility_Peelout    (SonicMania::Ability)(baseAddress + 0x000C8FF0)

    #pragma region Internal Variables

    extern int NumberOfAnnouncers;
    extern std::string Settings_FilePath;
    extern SonicMania::CompetitionSession LastSession;
    extern int CurrentRound_Plus;
    extern bool AllowUpdateVictory;

    #pragma endregion

    #pragma region Setting Variables

    //Developer Settings
    extern bool EnableDevMode;
    extern bool EnableDebugMode;
    extern bool DarkDevMenu;

    extern bool DevMode_ControlPlayer1;
    extern bool DevMode_ControlPlayer2;
    extern bool DevMode_ControlPlayer3;
    extern bool DevMode_ControlPlayer4;

    extern bool DevMode_ControllerSwap;
    extern int DevMode_ControllerSwapPosition;

    //Stock Competition Settings
    extern int NumberOfRounds; // Ignored when EndlessRounds = true;
    extern ItemsConfig MonitorTypes;

    //Competition Plus Settings
    extern int InitalLives; // Ignored when InfiniteLives = true;
    extern bool InfiniteLives;
    extern bool TimeLimit;
    extern bool EndlessRounds;
    extern bool DropdashAbility;
    extern bool InstaSheildAbility;
    extern VictoryMode VictoryStyle;
    extern AnnouncerType CurrentAnnouncer;
    extern SpeedShoesModification SpeedShoesMode;

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

    //Status States
    extern int CurrentLevelSelect;
    extern int P1_LastPlacement;
    extern int P2_LastPlacement;
    extern int P3_LastPlacement;
    extern int P4_LastPlacement;

    #pragma endregion

    extern void SetLastMatchResults();

    extern void DevMode_WarpAllPlayersTo(int PlayerID);

    extern void SetTimeLimit(bool Value);

    extern void SetCurrentLSelect(int Value);

    extern void SetVictoryMethod(CompPlusSettings::VictoryMode Value);

    extern void SetMonitorMode(CompPlusSettings::ItemsConfig Value);

    extern void SetNumberOfRounds(int Value);

    extern void SetEndlessRounds(bool Value);

    extern void SetDropdashAbility(bool Value);

    extern void SetPeeloutAbility(int PlayerID, bool Value);

    extern void SetInstaSheildAbility(bool Value);

    extern void SetAnnouncer(AnnouncerType Value);

    extern void SetInitalLives(int value);

    extern void SetAbility(int PlayerID, CompPlusSettings::PlayerAbility Ability);

    extern void SetPlayer(int PlayerID, SonicMania::Character Character, bool Force = true);

    extern void SetPlayer(int PlayerID, CompPlusSettings::ChosenPlayer Character, bool Force = true);

    extern void FixAbilites(SonicMania::EntityPlayer* Player);

    extern void RefreshSettings();

    extern void OnStageChange();

    extern void OnFrame();

    extern void LoadSettings();

    extern void SaveSettings();

    extern void FixUnmatchingVSPlayers();
}


