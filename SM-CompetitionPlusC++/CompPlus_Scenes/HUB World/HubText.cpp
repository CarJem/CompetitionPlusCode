#include "stdafx.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "SonicMania.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "Base.h"
#include "CompPlus_Core/CompPlus_Scoring.h"
#include <string>
#include <sstream>
#include "HubText.h"

namespace CompPlus_HubText
{
    using namespace SonicMania;
    using namespace CompPlus_Core;
    using namespace CompPlus_Common;
    using namespace CompPlus_HubCore;

    static wchar_t*** Strings;

    void UpdatePeeloutDisplay(int SlotID, CompPlus_Settings::ThreeStateBool State, int StageIndex, int Index)
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

        Label3.Text = (wchar_t*)Strings[StageIndex][Index];

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

    void UpdateAbilitySwapperDisplay(int SlotID, CompPlus_Settings::PlayerAbility Ability, int StageIndex, int Index)
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);


        Label3.Text = (wchar_t*)Strings[StageIndex][Index];

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

    void UpdatePlayerSwapperDisplay(int SlotID, CompPlus_Settings::ChosenPlayer Player, int StageIndex, int Index)
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

        Label3.Text = (wchar_t*)Strings[StageIndex][Index];
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

    void UpdateSeasonDisplay(int SlotID, CompPlus_Settings::SeasonType Season, int StageIndex, int Index)
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

        Label3.Text = (wchar_t*)Strings[StageIndex][Index];

        if (Season == CompPlus_Settings::Season_EXE)
        {
            char* on_text = (char*)"HALLOWEEN";
            ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
            Label3.TextLength = (WORD)9;
        }
        else 
        {
            char* on_text = (char*)"NORMAL";
            ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
            Label3.TextLength = (WORD)6;
        }
    }

    void UpdateLevelSelectStatusDisplay(int State, int StageIndex, int Index, int SlotID)
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

        Label3.Text= (wchar_t*)Strings[StageIndex][Index];

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
        else if (State == 4)
        {
            char* on_text = (char*)"LSELECT: EXECUTOR";
            ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
            Label3.TextLength = (WORD)17;
        }
    }

    void UpdateToggleDisplay(int SlotID, bool State, int StageIndex, int Index)
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

        Label3.Text= (wchar_t*)Strings[StageIndex][Index];

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

    void UpdateSaveToggle(int SlotID, bool State, int StageIndex, int Index)
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

        Label3.Text = (wchar_t*)Strings[StageIndex][Index];

        if (State)
        {
            char* on_text = (char*)"SAVE";
            ConvertASCII2Unicode(Label3.Text, on_text, strlen(on_text), -32);
            Label3.TextLength = (WORD)4;
        }
        else
        {
            char* off_text = (char*)"NO SAVE";
            ConvertASCII2Unicode(Label3.Text, off_text, strlen(off_text), -32);
            Label3.TextLength = (WORD)7;
        }
    }

    void UpdateToggleDisplayInverted(int SlotID, bool State, int StageIndex, int Index)
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

        Label3.Text= (wchar_t*)Strings[StageIndex][Index];

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

    void UpdateGeneralDisplay(int SlotID, char* _text, int size, int StageIndex, int Index)
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

        Label3.Text= (wchar_t*)Strings[StageIndex][Index];
        ConvertASCII2Unicode(Label3.Text, _text, strlen(_text), -32);
        Label3.TextLength = (WORD)size;
    }

    void UpdateGeneralDisplay(SonicMania::EntityUIInfoLabel& Label3, char* _text, int size, int StageIndex, int Index)
    {
        Label3.Text = (wchar_t*)Strings[StageIndex][Index];
        ConvertASCII2Unicode(Label3.Text, _text, strlen(_text), -32);
        Label3.TextLength = (WORD)size;
    }

    void UpdateAnnouncerDisplay(int SlotID, int StageIndex, int Index)
    {
        switch (CompPlus_Settings::CurrentAnnouncer)
        {
        case CompPlus_Settings::Announcer_Default:
            UpdateGeneralDisplay(SlotID, (char*)"SONIC MANIA", 11, StageIndex, Index);
            break;
        case CompPlus_Settings::Announcer_Classic:
            UpdateGeneralDisplay(SlotID, (char*)"CLASSIC", 7, StageIndex, Index);
            break;
        case CompPlus_Settings::Announcer_Garrulous64:
            UpdateGeneralDisplay(SlotID, (char*)"GARRULOUS64", 11, StageIndex, Index);
            break;
        case CompPlus_Settings::Announcer_Angelthegamer:
            UpdateGeneralDisplay(SlotID, (char*)"ANGELTHEGAMER", 13, StageIndex, Index);
            break;
        case CompPlus_Settings::Announcer_Memes:
            UpdateGeneralDisplay(SlotID, (char*)"MEMES", 5, StageIndex, Index);
            break;
        case CompPlus_Settings::Announcer_KC3K:
            UpdateGeneralDisplay(SlotID, (char*)"KNUX3&KC", 8, StageIndex, Index);
            break;
        case CompPlus_Settings::Announcer_DanielUK:
            UpdateGeneralDisplay(SlotID, (char*)"DANIEL-UK", 9, StageIndex, Index);
            break;
        }
    }

    void UpdateVictoryMethodDisplay(int SlotID, int StageIndex, int Index)
    {
        switch (CompPlus_Settings::VictoryStyle)
        {
        case CompPlus_Settings::VictoryMode_Default:
            UpdateGeneralDisplay(SlotID, (char*)"ORIGINAL", 8, StageIndex, Index);
            break;
        case CompPlus_Settings::VictoryMode_Time:
            UpdateGeneralDisplay(SlotID, (char*)"TIME", 4, StageIndex, Index);
            break;
        case CompPlus_Settings::VictoryMode_Rings:
            UpdateGeneralDisplay(SlotID, (char*)"RINGS", 5, StageIndex, Index);
            break;
        case CompPlus_Settings::VictoryMode_AntiRings:
            UpdateGeneralDisplay(SlotID, (char*)"ANTI-RINGS", 10, StageIndex, Index);
            break;
        case CompPlus_Settings::VictoryMode_TotalRings:
            UpdateGeneralDisplay(SlotID, (char*)"ALL RINGS", 9, StageIndex, Index);
            break;
        case CompPlus_Settings::VictoryMode_Score:
            UpdateGeneralDisplay(SlotID, (char*)"SCORE", 5, StageIndex, Index);
            break;
        case CompPlus_Settings::VictoryMode_Items:
            UpdateGeneralDisplay(SlotID, (char*)"ITEMS", 5, StageIndex, Index);
            break;
        }
    }

    void UpdateIntDisplay(int SlotID, int value, int StageIndex, int Index)
    {
        std::string s = std::to_string(value);
        s.insert(0, "x");
        char* text = (char*)s.c_str();
        int size = (int)s.length();
        UpdateGeneralDisplay(SlotID, text, size, StageIndex, Index);
    }

    void UpdateLivesDisplay(int SlotID, int StageIndex, int Index)
    {
        if (CompPlus_Settings::InfiniteLives)
        {
            UpdateGeneralDisplay(SlotID, (char*)"INFINITE", 8, StageIndex, Index);
        }
        else
        {
            std::string s = std::to_string(CompPlus_Settings::InitalLives);
            s.insert(0, "x");
            char* text = (char*)s.c_str();
            int size = (int)s.length();
            UpdateGeneralDisplay(SlotID, text, size, StageIndex, Index);
        }
    }

    void UpdateNumberOfRoundsDisplay(int SlotID, int StageIndex, int Index)
    {
        if (CompPlus_Settings::EndlessRounds)
        {
            UpdateGeneralDisplay(SlotID, (char*)"INFINITE", 8, StageIndex, Index);
        }
        else
        {
            std::string s = std::to_string(CompPlus_Settings::NumberOfRounds);
            s.insert(0, "x");
            char* text = (char*)s.c_str();
            int size = (int)s.length();
            UpdateGeneralDisplay(SlotID, text, size, StageIndex, Index);
        }
    }

    void UpdateShoesDisplay(int SlotID, int StageIndex, int Index)
    {
        switch (CompPlus_Settings::SpeedShoesMode)
        {
            case CompPlus_Settings::SpeedShoesModification_Default:
                UpdateGeneralDisplay(SlotID, (char*)"DEFAULT", 7, StageIndex, Index);
                break;
            case CompPlus_Settings::SpeedShoesModification_HighJump:
                UpdateGeneralDisplay(SlotID, (char*)"JUMP UP", 7, StageIndex, Index);
                break;
            case CompPlus_Settings::SpeedShoesModification_Freeze:
                UpdateGeneralDisplay(SlotID, (char*)"FREEZE", 6, StageIndex, Index);
                break;
            case CompPlus_Settings::SpeedShoesModification_SpeedDown:
                UpdateGeneralDisplay(SlotID, (char*)"SLOWDOWN", 8, StageIndex, Index);
                break;
            case CompPlus_Settings::SpeedShoesModification_Random:
                UpdateGeneralDisplay(SlotID, (char*)"RANDOM", 6, StageIndex, Index);
                break;
        }
    }

    void UpdateItemBoxModeDisplay(int SlotID, int StageIndex, int Index)
    {
        switch (CompPlus_Settings::MonitorTypes)
        {
        case CompPlus_Settings::ItemsConfig_Default:
            UpdateGeneralDisplay(SlotID, (char*)"FIXED", 5, StageIndex, Index);
            break;
        case CompPlus_Settings::ItemsConfig_Random:
            UpdateGeneralDisplay(SlotID, (char*)"RANDOM", 6, StageIndex, Index);
            break;
        case CompPlus_Settings::ItemsConfig_Teleporters:
            UpdateGeneralDisplay(SlotID, (char*)"TELEPORT", 8, StageIndex, Index);
            break;
        }
    }

    void UpdateWinsTallyDisplay(int SlotID, int StageIndex, int Index)
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
        Label3.Text= (wchar_t*)Strings[StageIndex][Index];
        ConvertASCII2Unicode(Label3.Text, _text, strlen(_text), -32);
        Label3.TextLength = __text.length();
    }

    void UpdateVSModeDisplay(int SlotID, int StageIndex, int Index)
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

        switch (CompPlus_Settings::VictoryStyle)
        {
            case CompPlus_Settings::VictoryMode_Default:
                UpdateGeneralDisplay(SlotID, (char*)"VS MODE - ORIGINAL", 18, StageIndex, Index);
                break;
            case CompPlus_Settings::VictoryMode_Time:
                UpdateGeneralDisplay(SlotID, (char*)"VS MODE - TIME", 14, StageIndex, Index);
                break;
            case CompPlus_Settings::VictoryMode_Rings:
                UpdateGeneralDisplay(SlotID, (char*)"VS MODE - RINGS", 15, StageIndex, Index);
                break;
            case CompPlus_Settings::VictoryMode_TotalRings:
                UpdateGeneralDisplay(SlotID, (char*)"VS MODE - ALL RINGS", 19, StageIndex, Index);
                break;
            case CompPlus_Settings::VictoryMode_AntiRings:
                UpdateGeneralDisplay(SlotID, (char*)"VS MODE - ANTI-RINGS", 20, StageIndex, Index);
                break;
            case CompPlus_Settings::VictoryMode_Score:
                UpdateGeneralDisplay(SlotID, (char*)"VS MODE - SCORE", 15, StageIndex, Index);
                break;
            case CompPlus_Settings::VictoryMode_Items:
                UpdateGeneralDisplay(SlotID, (char*)"VS MODE - ITEMS", 15, StageIndex, Index);
                break;
        }
    }

    void Init()
    {
        int Length_Y = 4;
        int Length_X = 50;

        Strings = new wchar_t* * [Length_Y];
        for (int y = 0; y < Length_Y; y++) 
        {
            Strings[y] = new wchar_t* [Length_X];
            for (int x = 0; x < Length_X; ++x) 
            {
                Strings[y][x] = (wchar_t*)malloc(128);
            }
        }
    }
}