#include "stdafx.h"
#include "CompPlusSettings.h"
namespace CompPlusSettings 
{
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

    // Basic Global Player Configuration : Ignored when AdvancedPlayerConfiguration = true;
    SonicAbility AbilitiesSonic = SonicAbility_Dropdash;
    bool AbilitiesTails = true;
    bool AbilitiesKnuckles = true;
    bool AbilitiesRay = true;
    bool AbilitiesMighty = true;

    ChosenPlayer Player1ChosenPlayer = ChosenPlayer_Default;
    ChosenPlayer Player2ChosenPlayer = ChosenPlayer_Default;
    ChosenPlayer Player3ChosenPlayer = ChosenPlayer_Default;
    ChosenPlayer Player4ChosenPlayer = ChosenPlayer_Default;

    // Advanced Player Configuration
    bool AdvancedPlayerConfiguration = false;

    // Advanced Player 1 Configuration
    ThreeStateBool Player1Peelout = Indeterminate;
    ThreeStateBool Player1Dropdash = Indeterminate;
    ThreeStateBool Player1Instasheild = Indeterminate;
    PlayerAbility Player1AbilitySet = AbilitySet_Default;

    // Advanced Player 2 Configuration
    ThreeStateBool Player2Peelout = Indeterminate;
    ThreeStateBool Player2Dropdash = Indeterminate;
    ThreeStateBool Player2Instasheild = Indeterminate;
    PlayerAbility Player2AbilitySet = AbilitySet_Default;

    // Advanced Player 3 Configuration
    ThreeStateBool Player3Peelout = Indeterminate;
    ThreeStateBool Player3Dropdash = Indeterminate;
    ThreeStateBool Player3Instasheild = Indeterminate;
    PlayerAbility Player3AbilitySet = AbilitySet_Default;

    // Advanced Player 4 Configuration
    ThreeStateBool Player4Peelout = Indeterminate;
    ThreeStateBool Player4Dropdash = Indeterminate;
    ThreeStateBool Player4Instasheild = Indeterminate;
    PlayerAbility Player4AbilitySet = AbilitySet_Default;


    void UpdateSettingsLoop() 
    {

    }
    
}