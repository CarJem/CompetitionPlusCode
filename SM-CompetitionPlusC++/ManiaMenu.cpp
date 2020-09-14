#include "stdafx.h"
#include "ManiaMenu.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "CompPlus_Settings.h"
#include "SonicMania.h"
#include "CompPlus_Scoring.h"
#include "CompPlus_Core.h"
#include "CompPlus_Common.h"

namespace CompPlus_ManiaMenu
{
    using namespace SonicMania;


    int LastMenuModWriteState = 0;
    int UIVsRoundPickerSlotID = 228;
    bool inMatch = false;
    bool StoredResults = false;
    int UIControlSlotID = 354;
    int UIButtonASlotID = 231;
    int UIButtonBSlotID = 232;
    int UIButtonScreenLayoutSlotID = 239;
    int UIVsResultsScreenUIControl = 357;
    int UIVsLevelSelectUIControl = 586;
    int UIVsPlayerSelectUIControl = 352;
    int UIVsFinalResultsScreenUIControl = 356;

    int EntityUIVsResultsP1_SlotID = 241;
    int EntityUIVsResultsP2_SlotID = 242;
    int EntityUIVsResultsP3_SlotID = 243;
    int EntityUIVsResultsP4_SlotID = 244;

    int UIHeadingResultsSlotID = 63;

    int EntityUIVsFinalResultsP1_SlotID = 245;
    int EntityUIVsFinalResultsP2_SlotID = 246;
    int EntityUIVsFinalResultsP3_SlotID = 247;
    int EntityUIVsFinalResultsP4_SlotID = 248;

    int UIInfoWinCounterLabel_SlotID = 687;
    int UIInfoWinCounterLabel2_SlotID = 707;
    int UIInfoZoneLabel_SlotID = 690;
    int UIInfoRoundLabel1_SlotID = 700;
    int UIInfoRoundLabel2_SlotID = 705;
    int UIInfoRoundLabel3_SlotID = 68;

    int UIInfoModeLabel = 749;


    static wchar_t* Strings[10];

    bool isPatched = false;

    void PatchCompetitionString()
    {
        if (!isPatched)
        {
            isPatched = true;
        }

    }

    void SetPosition(SonicMania::Entity& object, int x, int y)
    {
        object.Position.X = x;
        object.Position.Y = y;
    }

    void UpdateModeLabel()
    {
        EntityUIInfoLabel& ModeLabel = *GetEntityFromSceneSlot<EntityUIInfoLabel>(UIInfoModeLabel);
        std::string __text;
        switch (CompPlus_Settings::VictoryStyle)
        {
        case CompPlus_Settings::VictoryMode_Default:
            __text = (char*)"VS MODE - ORIGINAL";
            break;
        case CompPlus_Settings::VictoryMode_Time:
            __text = (char*)"VS MODE - TIME";
            break;
        case CompPlus_Settings::VictoryMode_Rings:
            __text = (char*)"VS MODE - RINGS";
            break;
        case CompPlus_Settings::VictoryMode_TotalRings:
            __text = (char*)"VS MODE - ALL RINGS";
            break;
        case CompPlus_Settings::VictoryMode_Score:
            __text = (char*)"VS MODE - SCORE";
            break;
        case CompPlus_Settings::VictoryMode_Items:
            __text = (char*)"VS MODE - ITEMS";
            break;
        }

        char* _text = (char*)__text.c_str();
        ModeLabel.Text = (wchar_t*)Strings[4];
        ConvertASCII2Unicode(ModeLabel.Text, _text, strlen(_text), -32);
        ModeLabel.TextLength = __text.length();
    }

    std::string GetPlayerPositionString(int PlayerID)
    {
        int Position = 0;
        if (PlayerID == 1) Position = CompPlus_Scoring::P1_LastPlacement;
        else if (PlayerID == 2) Position = CompPlus_Scoring::P2_LastPlacement;
        else if (PlayerID == 3) Position = CompPlus_Scoring::P3_LastPlacement;
        else if (PlayerID == 4) Position = CompPlus_Scoring::P4_LastPlacement;

        if (Position == 1) return "1st";
        else if (Position == 2) return "2nd";
        else if (Position == 3) return "3rd";
        else if (Position == 4) return "4th";
        else return "";
    }

    void UpdateLastRoundLabel()
    {
        EntityUIInfoLabel& LastRound = *GetEntityFromSceneSlot<EntityUIInfoLabel>(UIInfoRoundLabel1_SlotID);
        std::string __text = "";
        if (CompPlus_Settings::EndlessRounds)
        {
            __text += "Endless Rounds";
        }
        else
        {
            __text += "Round ";
            __text += std::to_string(CompPlus_Scoring::LastCurrentRound);
            __text += "/";
            __text += std::to_string(CompPlus_Settings::NumberOfRounds);
        }


        char* _text = (char*)__text.c_str();
        LastRound.Text = (wchar_t*)Strings[2];
        ConvertASCII2Unicode(LastRound.Text, _text, strlen(_text), -32);
        LastRound.TextLength = __text.length();
    }

    void UpdateCurrentRoundLabels()
    {
        EntityUIInfoLabel& LastRound = *GetEntityFromSceneSlot<EntityUIInfoLabel>(UIInfoRoundLabel2_SlotID);
        std::string __text = "";
        if (CompPlus_Settings::EndlessRounds)
        {
            __text += "Endless Rounds";
        }
        else
        {
            __text += "Round ";
            __text += std::to_string(CompPlus_Scoring::LastCurrentRound + 1);
            __text += "/";
            __text += std::to_string(CompPlus_Settings::NumberOfRounds);
        }

        char* _text = (char*)__text.c_str();
        LastRound.Text = (wchar_t*)Strings[3];
        ConvertASCII2Unicode(LastRound.Text, _text, strlen(_text), -32);
        LastRound.TextLength = __text.length();
    }

    void UpdateFinalResultsRoundLabel()
    {
        EntityUIInfoLabel& LastRound = *GetEntityFromSceneSlot<EntityUIInfoLabel>(UIInfoRoundLabel3_SlotID);
        std::string __text = std::to_string(CompPlus_Settings::NumberOfRounds);
        __text += " Rounds";

        char* _text = (char*)__text.c_str();
        LastRound.Text = (wchar_t*)Strings[5];
        ConvertASCII2Unicode(LastRound.Text, _text, strlen(_text), -32);
        LastRound.TextLength = __text.length();
    }

    void UpdatePositionLabel(int PlayerID, int index, int SlotID)
    {
        EntityUIInfoLabel& PositionLabel = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);
        std::string __text = GetPlayerPositionString(PlayerID);

        char* _text = (char*)__text.c_str();
        PositionLabel.Text = (wchar_t*)Strings[index];
        ConvertASCII2Unicode(PositionLabel.Text, _text, strlen(_text), -32);
        PositionLabel.TextLength = __text.length();
    }

    void UpdateFinalUIVsResults()
    {
        EntityUIVsResults& P1_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(EntityUIVsFinalResultsP1_SlotID);
        EntityUIVsResults& P2_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(EntityUIVsFinalResultsP2_SlotID);
        EntityUIVsResults& P3_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(EntityUIVsFinalResultsP3_SlotID);
        EntityUIVsResults& P4_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(EntityUIVsFinalResultsP4_SlotID);
    }

    void UpdateWinsDisplay(int PlayerID, int Wins, int x, int y, int SlotIDs[14])
    {
        SonicMania::Entity& UIInfoLabelTop = *GetEntityFromSceneSlot<SonicMania::Entity>(SlotIDs[0]);
        SonicMania::Entity& UIInfoLabelMiddle = *GetEntityFromSceneSlot<SonicMania::Entity>(SlotIDs[1]);
        SonicMania::Entity& UIInfoLabelBottom = *GetEntityFromSceneSlot<SonicMania::Entity>(SlotIDs[2]);

        EntityUIPicture& SingleTrophy1 = *GetEntityFromSceneSlot<EntityUIPicture>(SlotIDs[3]);
        EntityUIPicture& SingleTrophy2 = *GetEntityFromSceneSlot<EntityUIPicture>(SlotIDs[4]);
        EntityUIPicture& SingleTrophy3 = *GetEntityFromSceneSlot<EntityUIPicture>(SlotIDs[5]);
        EntityUIPicture& SingleTrophy4 = *GetEntityFromSceneSlot<EntityUIPicture>(SlotIDs[6]);

        EntityUIPicture& FivesTrophy = *GetEntityFromSceneSlot<EntityUIPicture>(SlotIDs[7]);
        EntityUIPicture& TensTrophy = *GetEntityFromSceneSlot<EntityUIPicture>(SlotIDs[9]);
        EntityUIPicture& FiftiesTrophy = *GetEntityFromSceneSlot<EntityUIPicture>(SlotIDs[8]);
        EntityUIPicture& HundredsTrophy = *GetEntityFromSceneSlot<EntityUIPicture>(SlotIDs[10]);

        EntityUIPicture& TensTrophyMultiplier = *GetEntityFromSceneSlot<EntityUIPicture>(SlotIDs[12]);
        EntityUIPicture& FiftiesTrophyMultiplier = *GetEntityFromSceneSlot<EntityUIPicture>(SlotIDs[11]);
        EntityUIPicture& HundredsTrophyMultiplier = *GetEntityFromSceneSlot<EntityUIPicture>(SlotIDs[13]);

        int Hundreds = Wins / 100;
        int Fifties = (Wins - 100 * Hundreds) / 50;
        int Tens = ((Wins - 100 * Hundreds) - 50 * Fifties) / 10;
        int Fives = (((Wins - 100 * Hundreds) - 50 * Fifties) - 10 * Tens) / 5;
        int Ones = ((((Wins - 100 * Hundreds) - 50 * Fifties) - 10 * Tens) - 5 * Fives) / 1;

        UpdatePositionLabel(PlayerID, 5 + PlayerID, SlotIDs[2]);

        SetPosition(UIInfoLabelTop, x, y - 12);
        SetPosition(UIInfoLabelMiddle, x, y - 6);
        SetPosition(UIInfoLabelBottom, x, y + 6);

        SetPosition(SingleTrophy1, x + 44, y - 6);
        SetPosition(SingleTrophy2, x + 44, y - 19);
        SetPosition(SingleTrophy3, x + 44 - 13, y - 6);
        SetPosition(SingleTrophy4, x + 44 - 13, y - 19);

        SetPosition(FivesTrophy, x + 17, y - 17);
        SetPosition(TensTrophy, x - 1, y - 15);
        SetPosition(FiftiesTrophy, x - 21, y - 15);
        SetPosition(HundredsTrophy, x - 42, y - 15);

        SetPosition(TensTrophyMultiplier, x - 1, y - 2);
        SetPosition(FiftiesTrophyMultiplier, x - 21, y - 2);
        SetPosition(HundredsTrophyMultiplier, x - 42, y - 2);

        if (Hundreds >= 1) HundredsTrophy.AnimData.CurrentFrame = 9;
        else HundredsTrophy.AnimData.CurrentFrame = 8;

        if (Fifties >= 1) FiftiesTrophy.AnimData.CurrentFrame = 7;
        else FiftiesTrophy.AnimData.CurrentFrame = 6;

        if (Tens >= 1) TensTrophy.AnimData.CurrentFrame = 5;
        else TensTrophy.AnimData.CurrentFrame = 4;

        if (Fives >= 1) FivesTrophy.AnimData.CurrentFrame = 3;



        else FivesTrophy.AnimData.CurrentFrame = 2;

        if (Ones >= 1) SingleTrophy1.AnimData.CurrentFrame = 1;
        else SingleTrophy1.AnimData.CurrentFrame = 0;

        if (Ones >= 2) SingleTrophy2.AnimData.CurrentFrame = 1;
        else SingleTrophy2.AnimData.CurrentFrame = 0;

        if (Ones >= 3) SingleTrophy3.AnimData.CurrentFrame = 1;
        else SingleTrophy3.AnimData.CurrentFrame = 0;

        if (Ones >= 4) SingleTrophy4.AnimData.CurrentFrame = 1;
        else SingleTrophy4.AnimData.CurrentFrame = 0;


        switch (Tens)
        {
        case 0:
            TensTrophyMultiplier.AnimData.CurrentFrame = 0;
            break;
        case 1:
            TensTrophyMultiplier.AnimData.CurrentFrame = 1 - 1;
            break;
        case 2:
            TensTrophyMultiplier.AnimData.CurrentFrame = 2 - 1;
            break;
        case 3:
            TensTrophyMultiplier.AnimData.CurrentFrame = 3 - 1;
            break;
        case 4:
            TensTrophyMultiplier.AnimData.CurrentFrame = 4 - 1;
            break;
        default:
            TensTrophyMultiplier.AnimData.CurrentFrame = 0;
            break;
        }

        FiftiesTrophyMultiplier.AnimData.CurrentFrame = 0;

        switch (Hundreds)
        {
        case 0:
            HundredsTrophyMultiplier.AnimData.CurrentFrame = 0;
            break;
        case 1:
            HundredsTrophyMultiplier.AnimData.CurrentFrame = 1 - 1;
            break;
        case 2:
            HundredsTrophyMultiplier.AnimData.CurrentFrame = 2 - 1;
            break;
        case 3:
            HundredsTrophyMultiplier.AnimData.CurrentFrame = 3 - 1;
            break;
        case 4:
            HundredsTrophyMultiplier.AnimData.CurrentFrame = 4 - 1;
            break;
        case 5:
            HundredsTrophyMultiplier.AnimData.CurrentFrame = 5 - 1;
            break;
        case 6:
            HundredsTrophyMultiplier.AnimData.CurrentFrame = 6 - 1;
            break;
        case 7:
            HundredsTrophyMultiplier.AnimData.CurrentFrame = 7 - 1;
            break;
        case 8:
            HundredsTrophyMultiplier.AnimData.CurrentFrame = 8 - 1;
            break;
        case 9:
            HundredsTrophyMultiplier.AnimData.CurrentFrame = 9 - 1;
            break;
        default:
            HundredsTrophyMultiplier.AnimData.CurrentFrame = 0;
            break;
        }
    }

    void UpdateRetroWinsDisplay(int SlotID)
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
        Label3.Text = (wchar_t*)Strings[0];
        ConvertASCII2Unicode(Label3.Text, _text, strlen(_text), -32);
        Label3.TextLength = __text.length();
    }

    void UpdateZoneDisplay()
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(UIInfoZoneLabel_SlotID);
        std::string __text = CompPlus_Scoring::LastZone;

        char* _text = (char*)__text.c_str();
        Label3.Text = (wchar_t*)Strings[1];
        ConvertASCII2Unicode(Label3.Text, _text, strlen(_text), -32);
        Label3.TextLength = __text.length();
    }

    void UpdateResultHighlights(EntityUIVsResults& Results, bool HasWon)
    {
        for (int i = 0; i < SonicMania::Options->CompetitionSession.NumberOfPlayers; i++) 
        {
            switch (CompPlus_Settings::VictoryStyle)
            {
                case CompPlus_Settings::VictoryMode_Time:
                    Results.Row0Highlight = false;
                    Results.Row1Highlight = false;
                    Results.Row2Highlight = false;
                    Results.Row3Highlight = false;
                    Results.Row4Highlight = HasWon;
                    break;
                case CompPlus_Settings::VictoryMode_Score:
                    Results.Row0Highlight = false;
                    Results.Row1Highlight = false;
                    Results.Row3Highlight = false;
                    Results.Row4Highlight = false;
                    Results.Row2Highlight = HasWon;
                    break;
                case CompPlus_Settings::VictoryMode_Rings:
                    Results.Row1Highlight = false;
                    Results.Row2Highlight = false;
                    Results.Row3Highlight = false;
                    Results.Row4Highlight = false;
                    Results.Row0Highlight = HasWon;
                    break;
                case CompPlus_Settings::VictoryMode_TotalRings:
                    Results.Row0Highlight = false;
                    Results.Row2Highlight = false;
                    Results.Row3Highlight = false;
                    Results.Row4Highlight = false;
                    Results.Row1Highlight = HasWon;
                    break;
                case CompPlus_Settings::VictoryMode_Items:
                    Results.Row0Highlight = false;
                    Results.Row1Highlight = false;
                    Results.Row2Highlight = false;
                    Results.Row4Highlight = false;
                    Results.Row3Highlight = HasWon;
                    break;
                case CompPlus_Settings::VictoryMode_AntiRings:
                    Results.Row0Highlight = false;
                    Results.Row2Highlight = false;
                    Results.Row3Highlight = false;
                    Results.Row4Highlight = false;
                    Results.Row1Highlight = HasWon;
                    break;
            }
        }
       
    }

    void UpdateResultsScoreboard(bool isFinalResults)
    {
        EntityUIVsResults& P1_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(isFinalResults ? EntityUIVsFinalResultsP1_SlotID : EntityUIVsResultsP1_SlotID);
        EntityUIVsResults& P2_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(isFinalResults ? EntityUIVsFinalResultsP2_SlotID : EntityUIVsResultsP2_SlotID);
        EntityUIVsResults& P3_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(isFinalResults ? EntityUIVsFinalResultsP3_SlotID : EntityUIVsResultsP3_SlotID);
        EntityUIVsResults& P4_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(isFinalResults ? EntityUIVsFinalResultsP4_SlotID : EntityUIVsResultsP4_SlotID);

        int OffsetY = isFinalResults ? 39 : 39;

        int P1_SlotIDs[14] = { 61, 67, 387, 428, 429, 430, 418, 433, 431, 434, 432, 438, 416, 417 };
        int P2_SlotIDs[14] = { 386, 408, 409, 435, 469, 450, 451, 473, 471, 470, 467, 475, 476, 472 };
        int P3_SlotIDs[14] = { 410, 411, 412, 485, 488, 489, 477, 492, 490, 493, 491, 497, 494, 495 };
        int P4_SlotIDs[14] = { 413, 414, 415, 496, 509, 498, 499, 513, 511, 512, 510, 515, 516, 514 };


        
        
        if (SonicMania::Options->CompetitionSession.NumberOfPlayers >= 1)
        {
            UpdateWinsDisplay(1, CompPlus_Scoring::P1_WinsPlus, P1_Results.Position.X, P1_Results.Position.Y - OffsetY, P1_SlotIDs);
            if (!isFinalResults) UpdateResultHighlights(P1_Results, CompPlus_Scoring::P1_HasWon_Round);
        }
        else 
        {
            UpdateWinsDisplay(1, CompPlus_Scoring::P1_WinsPlus, -100, -100, P1_SlotIDs);
        }
        if (SonicMania::Options->CompetitionSession.NumberOfPlayers >= 2)
        {
            UpdateWinsDisplay(2, CompPlus_Scoring::P2_WinsPlus, P2_Results.Position.X, P2_Results.Position.Y - OffsetY, P2_SlotIDs);
            if (!isFinalResults) UpdateResultHighlights(P2_Results, CompPlus_Scoring::P2_HasWon_Round);
        }
        else
        {
            UpdateWinsDisplay(2, CompPlus_Scoring::P2_WinsPlus, -100, -100, P2_SlotIDs);
        }
        if (SonicMania::Options->CompetitionSession.NumberOfPlayers >= 3)
        {
            UpdateWinsDisplay(3, CompPlus_Scoring::P3_WinsPlus, P3_Results.Position.X, P3_Results.Position.Y - OffsetY, P3_SlotIDs);
            if (!isFinalResults) UpdateResultHighlights(P3_Results, CompPlus_Scoring::P3_HasWon_Round);
        }
        else
        {
            UpdateWinsDisplay(3, CompPlus_Scoring::P3_WinsPlus, -100, -100, P3_SlotIDs);
        }
        if (SonicMania::Options->CompetitionSession.NumberOfPlayers >= 4)
        {
            UpdateWinsDisplay(4, CompPlus_Scoring::P4_WinsPlus, P4_Results.Position.X, P4_Results.Position.Y - OffsetY, P4_SlotIDs);
            if (!isFinalResults) UpdateResultHighlights(P4_Results, CompPlus_Scoring::P4_HasWon_Round);
        }
        else
        {
            UpdateWinsDisplay(4, CompPlus_Scoring::P4_WinsPlus, -100, -100, P4_SlotIDs);
        }
    }

    void UpdateGlobalBGColors() 
    {
        SetUIBG_BGColor(74, 211, 156);
        SetUIBG_FGLowColor(247, 146, 24);
        SetUIBG_FGHighColor(57, 178, 206);
    }

    void UpdatePreMatchStuff()
    {
        CompPlus_Common::FixUnmatchingVSPlayers();
    }

    void UpdateOptionsPage() 
    {
        EntityUIVsRoundPicker& roundPicker = *GetEntityFromSceneSlot<EntityUIVsRoundPicker>(232);
        roundPicker.MaxVal = 999;

        EntityUIControl& CompetitionSettingsPage = *GetEntityFromSceneSlot<EntityUIControl>(UIControlSlotID);
        EntityUIControl& CompetitionLevelSelectPage = *GetEntityFromSceneSlot<EntityUIControl>(UIVsLevelSelectUIControl);

        if (CompetitionSettingsPage.SelectedElement == 0) CompetitionSettingsPage.SelectedElement = 2;
        else if (CompetitionSettingsPage.SelectedElement == 1) CompetitionSettingsPage.SelectedElement = 3;

        if (CompetitionSettingsPage.InBounds)
        {
            UpdatePreMatchStuff();
        }
    }

    void UpdateMiscStuff() 
    {
        Entity& diaorma = *GetEntityFromSceneSlot<Entity>(285);
        diaorma.Visible = false;
    }

    void UpdateFinalResultsPage() 
    {
        EntityUIControl& CompetitionFinalResultsPage = *GetEntityFromSceneSlot<EntityUIControl>(UIVsFinalResultsScreenUIControl);

        if (CompetitionFinalResultsPage.InBounds)
        {
            UpdateResultsScoreboard(true);
        }
        UpdateFinalUIVsResults();
        UpdateFinalResultsRoundLabel();
        UpdateRetroWinsDisplay(UIInfoWinCounterLabel2_SlotID);
    }

    void UpdateResultsPage() 
    {
        EntityUIVsResults& P1_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(EntityUIVsResultsP1_SlotID);
        EntityUIVsResults& P2_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(EntityUIVsResultsP2_SlotID);
        EntityUIVsResults& P3_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(EntityUIVsResultsP3_SlotID);
        EntityUIVsResults& P4_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(EntityUIVsResultsP4_SlotID);

        SonicMania::Entity& object = *GetEntityFromSceneSlot<SonicMania::Entity>(UIHeadingResultsSlotID);
        object.Visible = false;
        

        EntityUIControl& CompetitionResultsPage = *GetEntityFromSceneSlot<EntityUIControl>(UIVsResultsScreenUIControl);

        if (CompetitionResultsPage.InBounds && StoredResults == false)
        {
            CompPlus_Scoring::SyncLastResults();
            SonicMania::Options->CompetitionSession.FinishFlags = 0;
            StoredResults = true;
        }

        if (CompetitionResultsPage.InBounds)
        {
            UpdateResultsScoreboard(false);
        }

        UpdateRetroWinsDisplay(UIInfoWinCounterLabel_SlotID);
        UpdateZoneDisplay();
    }

    void UpdatePlayerSelectPage() 
    {
        EntityUIControl& CompetitionPlayerSelect = *GetEntityFromSceneSlot<EntityUIControl>(UIVsPlayerSelectUIControl);
        if (CompetitionPlayerSelect.InBounds)
        {
            CompPlus_Scoring::ClearMatchResults();
        }
    }

    void UpdateLevelSelect() 
    {
        SonicMania::EntityUIVsZoneButton& object = *GetEntityFromSceneSlot<SonicMania::EntityUIVsZoneButton>(590);
        object.Disabled = false;
        //object.Obfuscate = true;
        object.XOut = false;
        object.ZoneID = 11;
        object.Act = 31;

        SonicMania::EntityUIVsZoneButton& object2 = *GetEntityFromSceneSlot<SonicMania::EntityUIVsZoneButton>(591);
        object2.Disabled = false;
        //object2.Obfuscate = true;
        object2.XOut = false;
        object2.ZoneID = 11;
        object2.Act = 32;

        EntityUIControl& CompetitionLevelSelect = *GetEntityFromSceneSlot<EntityUIControl>(UIVsLevelSelectUIControl);

        if (CompetitionLevelSelect.InBounds)
        {
            CompPlus_Scoring::ClearTemporaryResults();
            StoredResults = false;
        }
    }

	void UpdateManiaMenu()
	{
        PatchCompetitionString();
        UpdateLevelSelect();
        UpdateGlobalBGColors();
        UpdateOptionsPage();
        UpdateMiscStuff();
        UpdateResultsPage();

        UpdateModeLabel();
        UpdateLastRoundLabel();
        UpdateCurrentRoundLabels();
        UpdateFinalResultsPage();
	}

    void Init() 
    {
        for (int i = 0; i < 10; ++i)
            Strings[i] = (wchar_t*)malloc(128);
    }
};