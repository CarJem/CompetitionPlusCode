#include "stdafx.h"
#include "CompetitionManiaMenu.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "CompPlus_Settings.h"
#include "SonicMania.h"
#include "CompPlus_Scoring.h"

namespace CompPlus_CompetitionMenu
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

    int EntityUIVsResultsP1_SlotID = 241;
    int EntityUIVsResultsP2_SlotID = 242;
    int EntityUIVsResultsP3_SlotID = 243;
    int EntityUIVsResultsP4_SlotID = 244;

    int UIInfoWinCounterLabel_SlotID_Position = 687;
    int UIInfoZoneLabel_SlotID_Position = 690;

    int UIInfoWinCounterLabel_SlotID = 687;
    int UIInfoZoneLabel_SlotID = 690;

    static wchar_t* Strings[10];

    bool isPatched = false;

    void PatchCompetitionString() 
    {
        if (!isPatched) 
        {
            /*
            void* dest1 = (void*)(baseAddress + 0x1F21C0);
            void* dest2 = (void*)(baseAddress + 0x1CE8D4);
            void* dest3 = (void*)(baseAddress + 0x1CE820);
            // NOP bytes
            char nops1[4];
            char nops2[4];
            char nops3[8];
            memset(nops1, 0x90, sizeof nops1);
            memset(nops2, 0x90, sizeof nops2);
            memset(nops3, 0x90, sizeof nops3);

            WriteData(dest1, nops1, 0x02);
            //WriteData(dest2, nops2, 0x02);
            //WriteData(dest3, nops2, 0x06);
            */
            isPatched = true;
        }

    }

    void UpdatePreMatchStuff() 
    {
        if (!inMatch)
        {
            CompPlus_Settings::FixUnmatchingVSPlayers();
            inMatch = true;
        }
    }

    void SetPosition(SonicMania::Entity& object, int x, int y)
    {
        object.Position.X = x;
        object.Position.Y = y;
    }

    void UpdateWinsDisplay(int Wins, int x, int y, int SlotIDs[14])
    {
        SonicMania::Entity& UIInfoLabelTop = *GetEntityFromSceneSlot<SonicMania::Entity>(SlotIDs[0]);
        SonicMania::Entity& UIInfoLabelMiddle = *GetEntityFromSceneSlot<SonicMania::Entity>(SlotIDs[1]);
        SonicMania::Entity& UIInfoLabelBottom = *GetEntityFromSceneSlot<SonicMania::Entity>(SlotIDs[2]);

        EntityUIPicture& SingleTrophy1 = *GetEntityFromSceneSlot<EntityUIPicture>(SlotIDs[3]);
        EntityUIPicture& SingleTrophy2 = *GetEntityFromSceneSlot<EntityUIPicture>(SlotIDs[5]);
        EntityUIPicture& SingleTrophy3 = *GetEntityFromSceneSlot<EntityUIPicture>(SlotIDs[4]);
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


        SetPosition(UIInfoLabelTop, x, y - 12);
        SetPosition(UIInfoLabelMiddle, x, y - 6);
        SetPosition(UIInfoLabelBottom, x, y);

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

    void UpdateRetroWinsDisplay() 
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(UIInfoWinCounterLabel_SlotID);
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

    void UpdateResultsScoreboard()
    {
        SonicMania::Entity& P1_Results = *GetEntityFromSceneSlot<SonicMania::Entity>(EntityUIVsResultsP1_SlotID);
        SonicMania::Entity& P2_Results = *GetEntityFromSceneSlot<SonicMania::Entity>(EntityUIVsResultsP2_SlotID);
        SonicMania::Entity& P3_Results = *GetEntityFromSceneSlot<SonicMania::Entity>(EntityUIVsResultsP3_SlotID);
        SonicMania::Entity& P4_Results = *GetEntityFromSceneSlot<SonicMania::Entity>(EntityUIVsResultsP4_SlotID);

        int P1_SlotIDs[14] = { 61, 67, 387, 428, 429, 430, 418, 433, 431, 434, 432, 438, 416, 417 };
        int P2_SlotIDs[14] = { 386, 408, 409, 435, 469, 450, 451, 473, 471, 470, 467, 475, 476, 472 };
        int P3_SlotIDs[14] = { 410, 411, 412, 485, 488, 489, 477, 492, 490, 493, 491, 497, 494, 495 };
        int P4_SlotIDs[14] = { 413, 414, 415, 496, 509, 498, 499, 513, 511, 512, 510, 515, 516, 514 };
        
        
        if (SonicMania::Options->CompetitionSession.NumberOfPlayers >= 1)
        {
            UpdateWinsDisplay(CompPlus_Scoring::P1_WinsPlus, P1_Results.Position.X, P1_Results.Position.Y - 39, P1_SlotIDs);
        }
        else 
        {
            UpdateWinsDisplay(CompPlus_Scoring::P1_WinsPlus, -100, -100, P1_SlotIDs);
        }
        if (SonicMania::Options->CompetitionSession.NumberOfPlayers >= 2)
        {
            UpdateWinsDisplay(CompPlus_Scoring::P2_WinsPlus, P2_Results.Position.X, P2_Results.Position.Y - 39, P2_SlotIDs);
        }
        else
        {
            UpdateWinsDisplay(CompPlus_Scoring::P2_WinsPlus, -100, -100, P2_SlotIDs);
        }
        if (SonicMania::Options->CompetitionSession.NumberOfPlayers >= 3)
        {
            UpdateWinsDisplay(CompPlus_Scoring::P3_WinsPlus, P3_Results.Position.X, P3_Results.Position.Y - 39, P3_SlotIDs);
        }
        else
        {
            UpdateWinsDisplay(CompPlus_Scoring::P3_WinsPlus, -100, -100, P3_SlotIDs);
        }
        if (SonicMania::Options->CompetitionSession.NumberOfPlayers >= 4)
        {
            UpdateWinsDisplay(CompPlus_Scoring::P4_WinsPlus, P4_Results.Position.X, P4_Results.Position.Y - 39, P4_SlotIDs);
        }
        else
        {
            UpdateWinsDisplay(CompPlus_Scoring::P4_WinsPlus, -100, -100, P4_SlotIDs);
        }
    }

    void UpdateGlobalBGColors() 
    {
        SetUIBG_BGColor(74, 211, 156);
        SetUIBG_FGLowColor(247, 146, 24);
        SetUIBG_FGHighColor(57, 178, 206);
    }

    void UpdateOptionsPage() 
    {
        EntityUIVsRoundPicker& roundPicker = *GetEntityFromSceneSlot<EntityUIVsRoundPicker>(232);
        roundPicker.MaxVal = 999;

        EntityUIControl& CompetitionSettingsPage = *GetEntityFromSceneSlot<EntityUIControl>(UIControlSlotID);
        EntityUIControl& CompetitionLevelSelectPage = *GetEntityFromSceneSlot<EntityUIControl>(UIVsLevelSelectUIControl);

        if (CompetitionSettingsPage.SelectedElement == 0) CompetitionSettingsPage.SelectedElement = 2;
        else if (CompetitionSettingsPage.SelectedElement == 1) CompetitionSettingsPage.SelectedElement = 3;
    }

    void UpdateMiscStuff() 
    {
        if (SonicMania::Options->CompetitionSession.inMatch == 1) UpdatePreMatchStuff();
        else inMatch = false;
    }

    void UpdateResultsPage() 
    {
        EntityUIVsResults& P1_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(EntityUIVsResultsP1_SlotID);
        EntityUIVsResults& P2_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(EntityUIVsResultsP2_SlotID);
        EntityUIVsResults& P3_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(EntityUIVsResultsP3_SlotID);
        EntityUIVsResults& P4_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(EntityUIVsResultsP4_SlotID);

        EntityUIControl& CompetitionResultsPage = *GetEntityFromSceneSlot<EntityUIControl>(UIVsResultsScreenUIControl);

        if (CompetitionResultsPage.Visible && StoredResults == false)
        {
            CompPlus_Scoring::SyncLastResults();
            SonicMania::Options->CompetitionSession.FinishFlags = 0;
            StoredResults = true;
        }

        UpdateResultsScoreboard();
        UpdateRetroWinsDisplay();
        UpdateZoneDisplay();
    }

    void UpdatePlayerSelectPage() 
    {
        EntityUIControl& CompetitionPlayerSelect = *GetEntityFromSceneSlot<EntityUIControl>(UIVsPlayerSelectUIControl);
        if (CompetitionPlayerSelect.Visible)
        {
            CompPlus_Scoring::ClearMatchResults();
        }
    }

    void UpdateLevelSelect() 
    {
        SonicMania::UIVsZoneButton& object = *GetEntityFromSceneSlot<SonicMania::UIVsZoneButton>(590);
        object.Disabled = false;
        //object.Obfuscate = true;
        object.XOut = false;
        object.ZoneID = 11;
        object.Act = 106;

        SonicMania::UIVsZoneButton& object2 = *GetEntityFromSceneSlot<SonicMania::UIVsZoneButton>(591);
        object2.Disabled = false;
        //object2.Obfuscate = true;
        object2.XOut = false;
        object2.ZoneID = 11;
        object2.Act = 107;

        EntityUIControl& CompetitionLevelSelect = *GetEntityFromSceneSlot<EntityUIControl>(UIVsLevelSelectUIControl);

        if (CompetitionLevelSelect.Visible) 
        {
            CompPlus_Scoring::ClearInternalWins();
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
	}

    void Init() 
    {
        for (int i = 0; i < 2; ++i)
            Strings[i] = (wchar_t*)malloc(128);
    }
};