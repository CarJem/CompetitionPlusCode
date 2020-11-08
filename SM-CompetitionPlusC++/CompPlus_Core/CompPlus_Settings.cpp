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
#include "CompPlus_Announcers.h"
#include "CompPlus_Patches.h"

namespace CompPlus_Settings 
{
	using namespace SonicMania;

    #pragma region Internal Variables

    int NumberOfAnnouncers = 7;
    std::string Settings_FilePath;
    bool SettingsLoaded = false;

    #pragma endregion

    #pragma region Setting Variables

    //Developer Settings
    bool StartupStage_Enabled = false;
    bool StartupStage_UseIZ = true;
    int StartupStage_Normal = 0;
    std::string StartupStage_Infinity = "";
    bool EnableDevMode = false;
    bool EnableDebugMode = false;
    bool DarkDevMenu = true;
    bool LogAdvancedDebugOutput = false;

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
    bool TailsFlightCancel = false;
    VictoryMode VictoryStyle = VictoryMode_Default;
    AnnouncerType CurrentAnnouncer = Announcer_Default;
    SpeedShoesModification SpeedShoesMode = SpeedShoesModification_Default;
    int StrechEffectIntensity = 1;

    //Player Settings
    bool PlayerSettingsSaveMode = false;

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

    void SetPlayerSettingsSaveMode(bool Value) 
    {
        PlayerSettingsSaveMode = Value;
        SaveSettings();
    }

    void SetSpeedShoesMode(SpeedShoesModification Value) 
    {
        SpeedShoesMode = Value;
        SaveSettings();
    }

    void SetTailsFlightCancel(bool Value)
    {
        TailsFlightCancel = Value;
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

    #pragma region Update Methods

    void UpdateStockSettings() 
    {
        if (SonicMania::Options->CompetitionSession.MonitorMode != MonitorTypes) SonicMania::Options->CompetitionSession.MonitorMode = MonitorTypes;
        if (SonicMania::Options->ItemMode != MonitorTypes) SonicMania::Options->ItemMode = MonitorTypes;
    }

    void UpdateLives()
    {
        if (InfiniteLives)
        {
            SonicMania::Player1.LifeCount = 100;
            SonicMania::Player2.LifeCount = 100;
            SonicMania::Player3.LifeCount = 100;
            SonicMania::Player4.LifeCount = 100;

            SonicMania::Options->CompetitionSession.InitalLives_P1 = 100;
            SonicMania::Options->CompetitionSession.InitalLives_P2 = 100;
            SonicMania::Options->CompetitionSession.InitalLives_P3 = 100;
            SonicMania::Options->CompetitionSession.InitalLives_P4 = 100;
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

    void UpdateCharacter(SonicMania::EntityPlayer* Player, SonicMania::Character Character, int PlayerID, BYTE CharID, bool Force)
    {
        if (Force) FastChangeCharacter(Player, Character);

        if (PlayerID == 1)
        {
            *(BYTE*)GetAddress(baseAddress + 0xAA763C, 0x4) = CharID;
        }
        else if (PlayerID == 2)
        {
            *(BYTE*)GetAddress(baseAddress + 0xAA763C, 0x5) = CharID;
        }
        else if (PlayerID == 3 && SonicMania::Options->CompetitionSession.NumberOfPlayers == 3)
        {
            *(BYTE*)GetAddress(baseAddress + 0xAA763C, 0x6) = CharID;
        }
        else if (PlayerID == 4 && SonicMania::Options->CompetitionSession.NumberOfPlayers == 4)
        {
            *(BYTE*)GetAddress(baseAddress + 0xAA763C, 0x7) = CharID;
        }
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
            UpdateCharacter(&Player1, Character, PlayerID, CharID, Force);
            SonicMania::Options->CompetitionSession.CharacterFlags[0] = CharID;
            SonicMania::Options->CharacterFlags[0] = CharID;
            SonicMania::Player1.Character = Character;
            CompPlus_Settings::Player1ChosenPlayer = Player;
        }
        else if (PlayerID == 2)
        {
            UpdateCharacter(&Player2, Character, PlayerID, CharID, Force);
            SonicMania::Options->CompetitionSession.CharacterFlags[1] = CharID;
            SonicMania::Options->CharacterFlags[1] = CharID;
            SonicMania::Player2.Character = Character;
            CompPlus_Settings::Player2ChosenPlayer = Player;

        }
        else if (PlayerID == 3)
        {
            UpdateCharacter(&Player3, Character, PlayerID, CharID, Force);
            SonicMania::Options->CompetitionSession.CharacterFlags[2] = CharID;
            SonicMania::Options->CharacterFlags[2] = CharID;
            SonicMania::Player3.Character = Character;
            CompPlus_Settings::Player3ChosenPlayer = Player;
        }
        else if (PlayerID == 4)
        {
            UpdateCharacter(&Player4, Character, PlayerID, CharID, Force);
            SonicMania::Options->CompetitionSession.CharacterFlags[3] = CharID;
            SonicMania::Options->CharacterFlags[3] = CharID;
            SonicMania::Player4.Character = Character;
            CompPlus_Settings::Player4ChosenPlayer = Player;
        }

        CompPlus_Patches::PatchRayAndMightyVSFix();
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

    void LoadStringSetting(tinyxml2::XMLElement* xmlOption, const char* Setting, std::string &Resulter)
    {
        if (!strcmp(xmlOption->Name(), Setting))
        {
            const char* value = xmlOption->GetText();
            Resulter = value;

            if (LogAdvancedDebugOutput) LogLoadSetting(Setting, value);
        }
    }

    template <typename T>
    void LoadBoolSetting(tinyxml2::XMLElement* xmlOption, const char* Setting, T& Resulter)
    {
        if (!strcmp(xmlOption->Name(), Setting))
        {
            bool value = XMLGetBool(xmlOption);
            Resulter = (T)value;

            if (LogAdvancedDebugOutput) LogLoadSetting(Setting, std::to_string(value));
        }
    }

    template <typename T>
    void LoadIntSettingAlt(tinyxml2::XMLElement* xmlOption, const char* Setting, T& Resulter)
    {
        if (!strcmp(xmlOption->Name(), Setting))
        {
            int value = XMLGetInt(xmlOption);
            Resulter = (T)value;
            if (Resulter == 0) Resulter = (T)4;
            if (LogAdvancedDebugOutput) LogLoadSetting(Setting, std::to_string(value));
        }
    }

    template <typename T>
    void LoadIntSetting(tinyxml2::XMLElement *xmlOption, const char* Setting, T &Resulter)
    {
        if (!strcmp(xmlOption->Name(), Setting))
        {
            int value = XMLGetInt(xmlOption);
            Resulter = (T)value;

            if (LogAdvancedDebugOutput) LogLoadSetting(Setting, std::to_string(value));
        }
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
                    LoadIntSetting(xmlOption, "SelectedAnnouncer", CurrentAnnouncer);
                    LoadIntSetting(xmlOption, "InitalLives", InitalLives);
                    LoadBoolSetting(xmlOption, "TimeLimit", TimeLimit);
                    LoadBoolSetting(xmlOption, "NoHurryUpTimer", NoHurryUpTimer);
                    LoadBoolSetting(xmlOption, "UseDropdash", DropdashAbility);
                    LoadBoolSetting(xmlOption, "UseInstaSheild", InstaSheildAbility);
                    LoadIntSetting(xmlOption, "CurrentLSelect", CompPlus_Status::CurrentLevelSelect);
                    LoadIntSetting(xmlOption, "VictoryStyle", VictoryStyle);
                    LoadBoolSetting(xmlOption, "EndlessRounds", EndlessRounds);
                    LoadBoolSetting(xmlOption, "MonitorMode", MonitorTypes);
                    LoadIntSetting(xmlOption, "NumberOfRounds", NumberOfRounds);
                    LoadIntSettingAlt(xmlOption, "StrechEffectIntensity", StrechEffectIntensity);
                    LoadIntSetting(xmlOption, "CurrentSeason", CurrentSeason);
                    LoadBoolSetting(xmlOption, "TailsFlightCancel", TailsFlightCancel);
                    LoadIntSetting(xmlOption, "SpeedShoesMode", SpeedShoesMode);
                    LoadBoolSetting(xmlOption, "SpotLightChallenge", SpotLightChallenge);
                    LoadBoolSetting(xmlOption, "UseEncoreVapeMusic", UseEncoreVapeMusic);
                    LoadBoolSetting(xmlOption, "LHPZ_SecretUnlocked", LHPZ_SecretUnlocked);
                    LoadBoolSetting(xmlOption, "PlayerSettingsSaveMode", PlayerSettingsSaveMode);

                    if (PlayerSettingsSaveMode == true) 
                    {
                        LoadBoolSetting(xmlOption, "Player1DynCam", Player1DynCam);
                        LoadBoolSetting(xmlOption, "Player2DynCam", Player2DynCam);
                        LoadBoolSetting(xmlOption, "Player3DynCam", Player3DynCam);
                        LoadBoolSetting(xmlOption, "Player4DynCam", Player4DynCam);

                        LoadIntSetting(xmlOption, "Player1AbilitySet", Player1AbilitySet);
                        LoadIntSetting(xmlOption, "Player2AbilitySet", Player2AbilitySet);
                        LoadIntSetting(xmlOption, "Player3AbilitySet", Player3AbilitySet);
                        LoadIntSetting(xmlOption, "Player4AbilitySet", Player4AbilitySet);

                        LoadIntSetting(xmlOption, "Player1ChosenPlayer", Player1ChosenPlayer);
                        LoadIntSetting(xmlOption, "Player2ChosenPlayer", Player2ChosenPlayer);
                        LoadIntSetting(xmlOption, "Player3ChosenPlayer", Player3ChosenPlayer);
                        LoadIntSetting(xmlOption, "Player4ChosenPlayer", Player4ChosenPlayer);

                        LoadIntSetting(xmlOption, "Player1PeeloutAbility", Player1PeeloutAbility);
                        LoadIntSetting(xmlOption, "Player2PeeloutAbility", Player2PeeloutAbility);
                        LoadIntSetting(xmlOption, "Player3PeeloutAbility", Player3PeeloutAbility);
                        LoadIntSetting(xmlOption, "Player4PeeloutAbility", Player4PeeloutAbility);
                    }
                    
                    LoadBoolSetting(xmlOption, "EnableDevMode", EnableDevMode);
                    LoadBoolSetting(xmlOption, "EnableDebugMode", EnableDebugMode);
                    LoadBoolSetting(xmlOption, "DarkDevMenu", DarkDevMenu);

                    LoadBoolSetting(xmlOption, "StartupStage_Enabled", StartupStage_Enabled);
                    LoadBoolSetting(xmlOption, "StartupStage_UseIZ", StartupStage_UseIZ);
                    LoadIntSetting(xmlOption, "StartupStage_Normal", StartupStage_Normal);
                    LoadStringSetting(xmlOption, "StartupStage_Infinity", StartupStage_Infinity);
                }
                LogInfo("CompPlus_Settings::LoadSettings", "Settings Loaded!");
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

    void AddtoSaveSettingsIZString(std::string Name, std::string Value, std::string& text)
    {
        std::string realValue = (!Value.empty() ? Value : "IZ_NSZ");

        text += "<" + Name + ">" + realValue + "</" + Name + ">";
        if (LogAdvancedDebugOutput) LogSaveSetting(Name.c_str(), realValue);
    }

    void AddtoSaveSettings(std::string Name, std::string Value, std::string& text)
    {
        text += "<" + Name + ">" + Value + "</" + Name + ">";
        if (LogAdvancedDebugOutput) LogSaveSetting(Name.c_str(), Value);
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
            AddtoSaveSettings("PlayerSettingsSaveMode", BoolToString(PlayerSettingsSaveMode), text);

            if (PlayerSettingsSaveMode == true)
            {
                AddtoSaveSettings("Player1DynCam", BoolToString(Player1DynCam), text);
                AddtoSaveSettings("Player2DynCam", BoolToString(Player2DynCam), text);
                AddtoSaveSettings("Player3DynCam", BoolToString(Player3DynCam), text);
                AddtoSaveSettings("Player4DynCam", BoolToString(Player4DynCam), text);

                AddtoSaveSettings("Player1AbilitySet", IntToString(Player1AbilitySet), text);
                AddtoSaveSettings("Player2AbilitySet", IntToString(Player2AbilitySet), text);
                AddtoSaveSettings("Player3AbilitySet", IntToString(Player3AbilitySet), text);
                AddtoSaveSettings("Player4AbilitySet", IntToString(Player4AbilitySet), text);

                AddtoSaveSettings("Player1ChosenPlayer", IntToString(Player1ChosenPlayer), text);
                AddtoSaveSettings("Player2ChosenPlayer", IntToString(Player2ChosenPlayer), text);
                AddtoSaveSettings("Player3ChosenPlayer", IntToString(Player3ChosenPlayer), text);
                AddtoSaveSettings("Player4ChosenPlayer", IntToString(Player4ChosenPlayer), text);

                AddtoSaveSettings("Player1PeeloutAbility", IntToString(Player1PeeloutAbility), text);
                AddtoSaveSettings("Player2PeeloutAbility", IntToString(Player2PeeloutAbility), text);
                AddtoSaveSettings("Player3PeeloutAbility", IntToString(Player3PeeloutAbility), text);
                AddtoSaveSettings("Player4PeeloutAbility", IntToString(Player4PeeloutAbility), text);
            }

            AddtoSaveSettings("InitalLives", IntToString(InitalLives), text);
            AddtoSaveSettings("TimeLimit", BoolToString(TimeLimit), text);
            AddtoSaveSettings("NoHurryUpTimer", BoolToString(NoHurryUpTimer), text);
            AddtoSaveSettings("EndlessRounds", BoolToString(EndlessRounds), text);
            AddtoSaveSettings("NumberOfRounds", IntToString(NumberOfRounds), text); 
            AddtoSaveSettings("StrechEffectIntensity", IntToString(StrechEffectIntensity), text);
            AddtoSaveSettings("MonitorMode", IntToString(MonitorTypes), text);

            AddtoSaveSettings("CurrentSeason", IntToString(CurrentSeason), text);
            AddtoSaveSettings("UseEncoreVapeMusic", BoolToString(UseEncoreVapeMusic), text);
            AddtoSaveSettings("TailsFlightCancel", BoolToString(TailsFlightCancel), text);
            AddtoSaveSettings("SpotLightChallenge", BoolToString(SpotLightChallenge), text);
            AddtoSaveSettings("SpeedShoesMode", BoolToString(SpeedShoesMode), text);

            if (LHPZ_SecretUnlocked == true) AddtoSaveSettings("LHPZ_SecretUnlocked", BoolToString(LHPZ_SecretUnlocked), text);

            AddtoSaveSettings("StartupStage_Enabled", BoolToString(StartupStage_Enabled), text);
            AddtoSaveSettings("StartupStage_UseIZ", BoolToString(StartupStage_UseIZ), text);
            AddtoSaveSettings("StartupStage_Normal", IntToString(StartupStage_Normal), text);
            AddtoSaveSettingsIZString("StartupStage_Infinity", StartupStage_Infinity, text);
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
            UpdateLives();
            UpdateStockSettings();
        }
    }
}