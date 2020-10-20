#include "stdafx.h"
#include "CompPlus_Settings.h"
#include "CompPlus_Extensions/IZAPI.h"
#include "Base.h"
#include "SonicMania.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "depends/tinyxml2/tinyxml2.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "CompPlus_Status.h"
#include "CompPlus_Extensions/Helpers.h"
#include "CompPlus_Common.h"
#include "Base.h"
#include "CompPlus_Announcers.h"

namespace CompPlus_Settings 
{
	using namespace SonicMania;

    #pragma region Internal Variables

    int NumberOfAnnouncers = 5;
    std::string Settings_FilePath;
    bool SettingsLoaded = false;

    #pragma endregion

    #pragma region Setting Variables

    //Developer Settings
    bool EnableDevMode = false;
    bool EnableDebugMode = false;
    bool DarkDevMenu = true;

    //Stock Competition Settings
    int NumberOfRounds = 3; 
    ItemsConfig MonitorTypes = ItemsConfig_Default;

    //Competition Plus Settings
    int InitalLives = 3;
    bool InfiniteLives = false;
    bool TimeLimit = true;
    bool NoHurryUpTimer = false;
    bool EndlessRounds = false;
    bool DropdashAbility = true;
    bool InstaSheildAbility = false;
    bool TailsFlightDrop = false;
    VictoryMode VictoryStyle = VictoryMode_Default;
    AnnouncerType CurrentAnnouncer = Announcer_Default;
    SpeedShoesModification SpeedShoesMode = SpeedShoesModification_Default;

    //Peelout Ability Settings
    ThreeStateBool Player1PeeloutAbility = ThreeStateBool::Indeterminate;
    ThreeStateBool Player2PeeloutAbility = ThreeStateBool::Indeterminate;
    ThreeStateBool Player3PeeloutAbility = ThreeStateBool::Indeterminate;
    ThreeStateBool Player4PeeloutAbility = ThreeStateBool::Indeterminate;

    //DynCam Settings
    bool Player1DynCam = false;
    bool Player2DynCam = false;
    bool Player3DynCam = false;
    bool Player4DynCam = false;

    //Chosen Player Settings
    ChosenPlayer Player1ChosenPlayer = ChosenPlayer_Sonic;
    ChosenPlayer Player2ChosenPlayer = ChosenPlayer_Tails;
    ChosenPlayer Player3ChosenPlayer = ChosenPlayer_Knuckles;
    ChosenPlayer Player4ChosenPlayer = ChosenPlayer_Mighty;

    //Ability Set Settings
    PlayerAbility Player1AbilitySet = AbilitySet_Compatibility;
    PlayerAbility Player2AbilitySet = AbilitySet_Compatibility;
    PlayerAbility Player3AbilitySet = AbilitySet_Compatibility;
    PlayerAbility Player4AbilitySet = AbilitySet_Compatibility;

    //Game Mode Settings
    bool SpotLightChallenge = false;
    bool UseEncoreVapeMusic = true;
    SeasonType CurrentSeason = SeasonType::Season_EXE;

    //Secret Settings
    bool LHPZ_SecretUnlocked = false;
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

    #pragma region Change Settings Methods

    void UpdateSonicAbilities()
    {
        //17 : No Dropdash or Instasheild     - (None)
        //9  : Dropdash and Instasheild		  - (Max Control)
        //1  : Dropdash Only			      - (Mania)
        //24 : Instasheild Only		          - (S3&K)

        int MovesetID = 17;

        if (DropdashAbility && InstaSheildAbility) MovesetID = 9;	      // Max Control Moveset
        else if (DropdashAbility && !InstaSheildAbility) MovesetID = 1;	  // Mania Moveset
        else if (!DropdashAbility && InstaSheildAbility) MovesetID = 24;  // S3&K Moveset
        else if (!DropdashAbility && !InstaSheildAbility) MovesetID = 17; // None


        BYTE* Pointer = *(BYTE**)((baseAddress + 0xAA763C));
        WriteData((BYTE*)(Pointer + 0x410B4), (BYTE)MovesetID);
    }

    void SetTailsFlightDrop(bool Value)
    {
        TailsFlightDrop = Value;
        SaveSettings();
    }

    void SetSpotlightChallenge(bool Value)
    {
        SpotLightChallenge = Value;
        SaveSettings();
    }

    void SetEncoreVapeMusic(bool Value)
    {
        UseEncoreVapeMusic = Value;
        SaveSettings();
    }

    void SetSeason(CompPlus_Settings::SeasonType Season) 
    {
        CurrentSeason = Season;
        SaveSettings();
    }

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
            else if (Ability == CompPlus_Settings::AbilitySet_Compatibility) Player1.Moveset = SonicMania::GetMoveSetByCharacter(Player1.Character);
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
            else if (Ability == CompPlus_Settings::AbilitySet_Compatibility) Player2.Moveset = SonicMania::GetMoveSetByCharacter(Player2.Character);
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
            else if (Ability == CompPlus_Settings::AbilitySet_Compatibility) Player3.Moveset = SonicMania::GetMoveSetByCharacter(Player3.Character);
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
            else if (Ability == CompPlus_Settings::AbilitySet_Compatibility) Player4.Moveset = SonicMania::GetMoveSetByCharacter(Player4.Character);
		}      
	}

	void SetDropdashAbility(bool Value)
	{
		DropdashAbility = Value;
		UpdateSonicAbilities();       
        SaveSettings();
	}

    void SetDynCamMode(int PlayerID, bool State)
    {
        if (PlayerID == 1)
        {
            CompPlus_Settings::Player1DynCam = State;
        }
        else if (PlayerID == 2)
        {
            CompPlus_Settings::Player2DynCam = State;
        }
        else if (PlayerID == 3)
        {
            CompPlus_Settings::Player3DynCam = State;
        }
        else if (PlayerID == 4)
        {
            CompPlus_Settings::Player4DynCam = State;
        }
    }

	void SetPeeloutAbility(int PlayerID, ThreeStateBool State)
	{
		SonicMania::Ability PeeloutState = MOVESET_NONE;
		if (State == ThreeStateBool::True) PeeloutState = UpAbility_Peelout;

		if (PlayerID == 1)
		{
            if (CompPlus_Settings::Player1PeeloutAbility != ThreeStateBool::Indeterminate && State == ThreeStateBool::Indeterminate)
            {
                Player1.UpAbility = MOVESET_NONE;
            }
            CompPlus_Settings::Player1PeeloutAbility = State;
            if (CompPlus_Settings::Player1PeeloutAbility != ThreeStateBool::Indeterminate) Player1.UpAbility = PeeloutState;
		}
		else if (PlayerID == 2)
		{
            if (CompPlus_Settings::Player2PeeloutAbility != ThreeStateBool::Indeterminate && State == ThreeStateBool::Indeterminate)
            {
                Player2.UpAbility = MOVESET_NONE;
            }
            CompPlus_Settings::Player2PeeloutAbility = State;
            if (CompPlus_Settings::Player2PeeloutAbility != ThreeStateBool::Indeterminate) Player2.UpAbility = PeeloutState;
		}
		else if (PlayerID == 3)
		{
            if (CompPlus_Settings::Player3PeeloutAbility != ThreeStateBool::Indeterminate && State == ThreeStateBool::Indeterminate)
            {
                Player3.UpAbility = MOVESET_NONE;
            }
            CompPlus_Settings::Player3PeeloutAbility = State;
            if (CompPlus_Settings::Player3PeeloutAbility != ThreeStateBool::Indeterminate) Player3.UpAbility = PeeloutState;
		}
		else if (PlayerID == 4)
		{
            if (CompPlus_Settings::Player4PeeloutAbility != ThreeStateBool::Indeterminate && State == ThreeStateBool::Indeterminate)
            {
                Player4.UpAbility = MOVESET_NONE;
            }
            CompPlus_Settings::Player4PeeloutAbility = State;
            if (CompPlus_Settings::Player4PeeloutAbility != ThreeStateBool::Indeterminate) Player4.UpAbility = PeeloutState;
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
        CompPlus_Announcers::ReloadRequired = true;
        CompPlus_Announcers::PlayAnnouncerChangeFX(Value);
    }

    void SetTimeLimit(bool State) 
    {
        TimeLimit = State;       
        SaveSettings();
    }

    void SetHurryTimer(bool State) 
    {
        NoHurryUpTimer = State;
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
        CompPlus_Status::CurrentLevelSelect = value;      
        SaveSettings();
    }

    void SetStrechIntensity(int value)
    {
        StrechEffectIntensity = value;
        SaveSettings();
    }

    #pragma endregion

    #pragma region Screen Layout Methods

    //DataPointer(int, WindowSizeX, 0xA530E4);
    //DataPointer(int, WindowSizeY, 0xA530E8);
    DataPointer(int, WindowSizeX, 0x43C6F4);
    DataPointer(int, WindowSizeY, 0x43C6F8);
    DataPointer(int, ViewPortSizeX, 0x43C70C);
    DataPointer(int, ViewPortSizeY, 0x43C710);
    DataPointer(int, ImageXPosition, 0x43C704);
    DataPointer(int, ImageYPosition, 0x43C708);
    DataPointer(BYTE, ScreenCount, 0xA530FC);

    bool ScreenSizeSaved = false;

    int OriginalImageXPosition = 0;
    int OriginalImageYPosition = 0;

    int ModifiedViewPortX = 1200;
    int ModifiedViewPortY = 960;
    int ModifiedImageXPosition = 300;
    int ModifiedImageYPosition = 0;

    int StrechEffectIntensity = 1;

    void UpdateStrechScreen()
    {
        if (SonicMania::Options->CompetitionSession.inMatch == 1)
        {
            if (ScreenCount != 1 && SonicMania::Options->CompetitionSession.ReadOnlyDisplayMode == 0 && SonicMania::Options->CompetitionSession.NumberOfPlayers == 2 && StrechEffectIntensity > 1)
            {
                int Intensity = StrechEffectIntensity + 1;
                if (WindowSizeX != 0 && WindowSizeY != 0 && Intensity != 0)
                {
                    ViewPortSizeX = WindowSizeX / 2 + (WindowSizeX / Intensity);
                    ViewPortSizeY = WindowSizeY;
                    int CenterX = (WindowSizeX - ViewPortSizeX);
                    ImageXPosition = (CenterX == 0 ? 0 : CenterX / 2);
                    ImageYPosition = 0;
                }
            }
            else
            {
                ViewPortSizeX = WindowSizeX;
                ViewPortSizeY = WindowSizeY;
                ImageXPosition = OriginalImageXPosition;
                ImageYPosition = OriginalImageYPosition;
            }
        }

    }

    #pragma endregion

    #pragma region DynCam Methods

    static int Speed1 = 1;
    static int Speed2 = 3;

    void UpdateDynCam(SonicMania::EntityPlayer* Player) 
    {
        if (Player->Camera != nullptr)
        {
            if (Player->Speed >= 400000)
            {
                if (Player->Camera->OffsetX < 0)
                    Player->Camera->OffsetX += Speed2;
                else if (Player->Camera->OffsetX <= 128)
                    Player->Camera->OffsetX += Speed1;
            }
            else if (Player->Speed <= -400000)
            {
                if (Player->Camera->OffsetX > 0)
                    Player->Camera->OffsetX -= Speed2;
                else if (Player->Camera->OffsetX >= -128)
                    Player->Camera->OffsetX -= Speed1;
            }
            else if (Player->Camera->OffsetX < 0)
                Player->Camera->OffsetX += Speed1;
            else if (Player->Camera->OffsetX > 0)
                Player->Camera->OffsetX -= Speed1;
        }

    }

    void UpdateDynCams() 
    {
        if (!CompPlus_Status::DisableDynCam)
        {
            if (Player1DynCam) UpdateDynCam(&Player1);
            if (Player2DynCam) UpdateDynCam(&Player2);
            if (Player3DynCam) UpdateDynCam(&Player3);
            if (Player4DynCam) UpdateDynCam(&Player4);
        }
    }

    #pragma endregion

    #pragma region Update Methods

    void UpdateStockSettings() 
    {
        CompPlus_Internal::DisableVSPointAddingAddress();
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

    #pragma endregion

    #pragma region Update Player Methods

    void UpdateCharacter(SonicMania::EntityPlayer* Player, SonicMania::Character Character)
    {
        SonicMania::FastChangeCharacter(Player, Character);
    }

    void UpdatePlayer(int PlayerID, SonicMania::Character Character, bool Force)
    {
        CompPlus_Settings::ChosenPlayer Player = CompPlus_Settings::ChosenPlayer_Default;

        BYTE CharID = 1;
        if (Character == Character_Sonic) 
        { 
            Player = CompPlus_Settings::ChosenPlayer_Sonic;
            CharID = 1;
        }
        else if (Character == Character_Tails) 
        {
            Player = CompPlus_Settings::ChosenPlayer_Tails;
            CharID = 2;
        }
        else if (Character == Character_Knux) 
        {
            Player = CompPlus_Settings::ChosenPlayer_Knuckles;
            CharID = 4;
        }
        else if (Character == Character_Mighty) 
        {
            Player = CompPlus_Settings::ChosenPlayer_Mighty;
            CharID = 8;
        }
        else if (Character == Character_Ray) 
        {
            Player = CompPlus_Settings::ChosenPlayer_Ray;
            CharID = 16;
        }

        if (Force) 
        {
            std::string message = "Changing Player ";
            message += IntToString(PlayerID);
            message += " Forcefully";
            message += " to Character ";
            message += IntToString(Character);
            message += "!";
            LogInfo("CompPlus_Settings::UpdatePlayer", message.c_str());
        }

        if (PlayerID == 1)
        {
            if (Force) UpdateCharacter(&Player1, Character);
            SonicMania::Options->CompetitionSession.CharacterFlags[0] = CharID;
            SonicMania::Options->CharacterFlags[0] = CharID;
            SonicMania::Player1.Character = Character;
            CompPlus_Settings::Player1ChosenPlayer = Player;
        }
        else if (PlayerID == 2)
        {
            if (Force) UpdateCharacter(&Player2, Character);
            SonicMania::Options->CompetitionSession.CharacterFlags[1] = CharID;
            SonicMania::Options->CharacterFlags[1] = CharID;
            SonicMania::Player2.Character = Character;
            CompPlus_Settings::Player2ChosenPlayer = Player;
        }
        else if (PlayerID == 3)
        {
            if (Force) UpdateCharacter(&Player3, Character);
            SonicMania::Options->CompetitionSession.CharacterFlags[2] = CharID;
            SonicMania::Options->CharacterFlags[2] = CharID;
            SonicMania::Player3.Character = Character;
            CompPlus_Settings::Player3ChosenPlayer = Player;
        }
        else if (PlayerID == 4)
        {
            if (Force) UpdateCharacter(&Player4, Character);
            SonicMania::Options->CompetitionSession.CharacterFlags[3] = CharID;
            SonicMania::Options->CharacterFlags[3] = CharID;
            SonicMania::Player4.Character = Character;
            CompPlus_Settings::Player4ChosenPlayer = Player;
        }
        CompPlus_Internal::FixRayAndMighty2P();
    }

    void UpdatePlayer(int PlayerID, CompPlus_Settings::ChosenPlayer Character, bool Force)
    {
        SonicMania::Character Player = SonicMania::Character_None;

        if (Character == ChosenPlayer_Sonic) Player = SonicMania::Character_Sonic;
        else if (Character == ChosenPlayer_Tails) Player = SonicMania::Character_Tails;
        else if (Character == ChosenPlayer_Knuckles) Player = Character_Knux;
        else if (Character == ChosenPlayer_Mighty) Player = SonicMania::Character_Mighty;
        else if (Character == ChosenPlayer_Ray) Player = SonicMania::Character_Ray;

        UpdatePlayer(PlayerID, Player, Force);
    }

    void FixUnmatchingVSPlayers()
    {
        SonicMania::Character P1_Char = (SonicMania::Character)(SonicMania::Options->CompetitionSession.CharacterFlags[0]);
        SonicMania::Character P2_Char = (SonicMania::Character)(SonicMania::Options->CompetitionSession.CharacterFlags[1]);
        SonicMania::Character P3_Char = (SonicMania::Character)(SonicMania::Options->CompetitionSession.CharacterFlags[2]);
        SonicMania::Character P4_Char = (SonicMania::Character)(SonicMania::Options->CompetitionSession.CharacterFlags[3]);

        CompPlus_Settings::UpdatePlayer(1, P1_Char, false);
        CompPlus_Settings::UpdatePlayer(2, P2_Char, false);
        CompPlus_Settings::UpdatePlayer(3, P3_Char, false);
        CompPlus_Settings::UpdatePlayer(4, P4_Char, false);
    }

    #pragma endregion

    #pragma region Settings Methods

    void RefreshSettings()
    {
        UpdatePlayer(1, Player1ChosenPlayer, false);
        SetAbility(1, Player1AbilitySet, true);
        SetPeeloutAbility(1, Player1PeeloutAbility);

        UpdatePlayer(2, Player2ChosenPlayer, false);
        SetAbility(2, Player2AbilitySet, true);
        SetPeeloutAbility(2, Player2PeeloutAbility);

        UpdatePlayer(3, Player3ChosenPlayer, false);
        SetAbility(3, Player3AbilitySet, true);
        SetPeeloutAbility(3, Player3PeeloutAbility);

        UpdatePlayer(4, Player4ChosenPlayer, false);
        SetAbility(4, Player4AbilitySet, true);
        SetPeeloutAbility(4, Player4PeeloutAbility);

        UpdateSonicAbilities();
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
                    else if (!strcmp(xmlOption->Name(), "NoHurryUpTimer"))
                    {
                        bool value = XMLGetBool(xmlOption);
                        NoHurryUpTimer = value;

                        LogLoadSetting("NoHurryUpTimer", std::to_string(value));
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
                        CompPlus_Status::CurrentLevelSelect = value;

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
                    else if (!strcmp(xmlOption->Name(), "StrechEffectIntensity"))
                    {
                        bool value = XMLGetBool(xmlOption);
                       
                        StrechEffectIntensity = value;
                        if (StrechEffectIntensity == 0) StrechEffectIntensity = 4;
                        LogLoadSetting("StrechEffectIntensity", std::to_string(value));
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
                    else if (!strcmp(xmlOption->Name(), "CurrentSeason"))
                    {
                        int value = XMLGetInt(xmlOption);
                        CurrentSeason = (SeasonType)value;

                        LogLoadSetting("CurrentSeason", std::to_string(value));
                    }
                    else if (!strcmp(xmlOption->Name(), "TailsFlightDrop"))
                    {
                        bool value = XMLGetBool(xmlOption);
                        TailsFlightDrop = value;

                        LogLoadSetting("TailsFlightDrop", std::to_string(value));
                    }
                    else if (!strcmp(xmlOption->Name(), "SpotLightChallenge"))
                    {
                        bool value = XMLGetBool(xmlOption);
                        SpotLightChallenge = value;

                        LogLoadSetting("SpotLightChallenge", std::to_string(value));
                    }
                    else if (!strcmp(xmlOption->Name(), "UseEncoreVapeMusic"))
                    {
                        bool value = XMLGetBool(xmlOption);
                        UseEncoreVapeMusic = value;

                        LogLoadSetting("UseEncoreVapeMusic", std::to_string(value));
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
            AddtoSaveSettings("CurrentLSelect", IntToString(CompPlus_Status::CurrentLevelSelect), text);
            AddtoSaveSettings("VictoryStyle", IntToString(VictoryStyle), text);

            AddtoSaveSettings("UseDropdash", BoolToString(DropdashAbility), text);
            AddtoSaveSettings("UseInstaSheild", BoolToString(InstaSheildAbility), text);

            AddtoSaveSettings("InitalLives", IntToString(InitalLives), text);
            AddtoSaveSettings("TimeLimit", BoolToString(TimeLimit), text);
            AddtoSaveSettings("NoHurryUpTimer", BoolToString(NoHurryUpTimer), text);
            AddtoSaveSettings("EndlessRounds", BoolToString(EndlessRounds), text);
            AddtoSaveSettings("NumberOfRounds", IntToString(NumberOfRounds), text); 
            AddtoSaveSettings("StrechEffectIntensity", IntToString(StrechEffectIntensity), text);
            AddtoSaveSettings("MonitorMode", IntToString(MonitorTypes), text);

            AddtoSaveSettings("CurrentSeason", IntToString(CurrentSeason), text);
            AddtoSaveSettings("UseEncoreVapeMusic", BoolToString(UseEncoreVapeMusic), text);
            AddtoSaveSettings("TailsFlightDrop", BoolToString(TailsFlightDrop), text);
            AddtoSaveSettings("SpotLightChallenge", BoolToString(SpotLightChallenge), text);

            if (LHPZ_SecretUnlocked == true) AddtoSaveSettings("LHPZ_SecretUnlocked", BoolToString(LHPZ_SecretUnlocked), text);

            AddtoSaveSettings("EnableDebugMode", BoolToString(EnableDebugMode), text);
            AddtoSaveSettings("EnableDevMode", BoolToString(EnableDevMode), text);
            AddtoSaveSettings("DarkDevMenu", BoolToString(DarkDevMenu), text);




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

    void OnFrame()
    {
        if (SettingsLoaded) 
        {
            UpdateDynCams();
            UpdateLives();
            UpdateStockSettings();
        }
    }
}