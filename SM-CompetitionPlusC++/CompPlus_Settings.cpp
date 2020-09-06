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
#include "CompPlus_Common.h"
#include "CompPlus_Announcers.h"

namespace CompPlus_Settings 
{
	using namespace SonicMania;

    #pragma region Internal Variables

    int NumberOfAnnouncers = 6;
    std::string Settings_FilePath;
    bool SettingsLoaded = false;

    #pragma endregion

    #pragma region Status Variables

    bool isVSControllerInputUnlocked = false;
    int CurrentLevelSelect = 0;

    #pragma endregion

    #pragma region Setting Variables

    //Developer Settings
    bool EnableDevMode = true;
    bool EnableDebugMode = true;
    bool DarkDevMenu = true;

    //Stock Competition Settings
    int NumberOfRounds = 3; 
    ItemsConfig MonitorTypes = ItemsConfig_Default;

    //Competition Plus Settings
    int InitalLives = 3;
    bool InfiniteLives = false;
    bool TimeLimit = false;
    bool EndlessRounds = false;
    bool DropdashAbility = true;
    bool InstaSheildAbility = false;
    VictoryMode VictoryStyle = VictoryMode_Default;
    AnnouncerType CurrentAnnouncer = Announcer_Default;
    SpeedShoesModification SpeedShoesMode = SpeedShoesModification_Default;

    //Peelout Ability Settings
    ThreeStateBool Player1PeeloutAbility = ThreeStateBool::Indeterminate;
    ThreeStateBool Player2PeeloutAbility = ThreeStateBool::Indeterminate;
    ThreeStateBool Player3PeeloutAbility = ThreeStateBool::Indeterminate;
    ThreeStateBool Player4PeeloutAbility = ThreeStateBool::Indeterminate;

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

	void SetPeeloutAbility(int PlayerID, ThreeStateBool State)
	{
		SonicMania::Ability PeeloutState = MOVESET_NONE;
		if (State == ThreeStateBool::True) PeeloutState = UpAbility_Peelout;

		if (PlayerID == 1)
		{
            if (State != ThreeStateBool::Indeterminate) Player1.UpAbility = PeeloutState;
			CompPlus_Settings::Player1PeeloutAbility = State;
		}
		else if (PlayerID == 2)
		{
            if (State != ThreeStateBool::Indeterminate) Player2.UpAbility = PeeloutState;
			CompPlus_Settings::Player2PeeloutAbility = State;
		}
		else if (PlayerID == 3)
		{
            if (State != ThreeStateBool::Indeterminate) Player3.UpAbility = PeeloutState;
			CompPlus_Settings::Player3PeeloutAbility = State;
		}
		else if (PlayerID == 4)
		{
            if (State != ThreeStateBool::Indeterminate) Player4.UpAbility = PeeloutState;
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

    void UpdateStockSettings() 
    {
        CompPlus_Common::DisableVSPointAddingAddress();
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



    void UpdatePlayer(int PlayerID, SonicMania::Character Character, bool Force)
    {
        CompPlus_Settings::ChosenPlayer Player = CompPlus_Settings::ChosenPlayer_Default;

        if (Character == Characters_Sonic) Player = CompPlus_Settings::ChosenPlayer_Sonic;
        else if (Character == Characters_Tails) Player = CompPlus_Settings::ChosenPlayer_Tails;
        else if (Character == Characters_Knuckles) Player = CompPlus_Settings::ChosenPlayer_Knuckles;
        else if (Character == Character_Mighty) Player = CompPlus_Settings::ChosenPlayer_Mighty;
        else if (Character == Characters_Ray) Player = CompPlus_Settings::ChosenPlayer_Ray;

        int CharacterID = (int)Character;

        if (PlayerID == 1)
        {
            if (Force) SonicMania::FastChangeCharacter(&Player1, Character);
            SonicMania::Options->CompetitionSession.CharacterFlags[PlayerID - 1] = Character;
            CompPlus_Settings::Player1ChosenPlayer = Player;
        }
        else if (PlayerID == 2)
        {
            if (Force) SonicMania::FastChangeCharacter(&Player2, Character);
            SonicMania::Options->CompetitionSession.CharacterFlags[PlayerID - 1] = Character;
            CompPlus_Settings::Player2ChosenPlayer = Player;
        }
        else if (PlayerID == 3)
        {
            if (Force) SonicMania::FastChangeCharacter(&Player3, Character);
            SonicMania::Options->CompetitionSession.CharacterFlags[PlayerID - 1] = Character;
            CompPlus_Settings::Player3ChosenPlayer = Player;
        }
        else if (PlayerID == 4)
        {
            if (Force) SonicMania::FastChangeCharacter(&Player4, Character);
            SonicMania::Options->CompetitionSession.CharacterFlags[PlayerID - 1] = Character;
            CompPlus_Settings::Player4ChosenPlayer = Player;
        }
        CompPlus_Common::FixRayAndMighty2P();
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
                    else if (!strcmp(xmlOption->Name(), "EnableDebugMode") && !CompPlus_Core::NonDeveloperBuild)
                    {
                        bool value = XMLGetBool(xmlOption);
                        EnableDebugMode = value;

                        LogLoadSetting("EnableDebugMode", std::to_string(value));
                    }
                    else if (!strcmp(xmlOption->Name(), "EnableDevMode") && !CompPlus_Core::NonDeveloperBuild)
                    {
                        bool value = XMLGetBool(xmlOption);
                        EnableDevMode = value;

                        LogLoadSetting("EnableDevMode", std::to_string(value));
                    }
                    else if (!strcmp(xmlOption->Name(), "DarkDevMenu") && !CompPlus_Core::NonDeveloperBuild)
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

            if (LHPZ_SecretUnlocked == true) AddtoSaveSettings("LHPZ_SecretUnlocked", BoolToString(LHPZ_SecretUnlocked), text);

            if (!CompPlus_Core::NonDeveloperBuild) 
            {
                AddtoSaveSettings("EnableDebugMode", BoolToString(EnableDebugMode), text);
                AddtoSaveSettings("EnableDevMode", BoolToString(EnableDevMode), text);
                AddtoSaveSettings("DarkDevMenu", BoolToString(DarkDevMenu), text);
            }




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