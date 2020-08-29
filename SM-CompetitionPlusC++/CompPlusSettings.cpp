#include "stdafx.h"
#include "CompPlusSettings.h"
#include "IZAPI.h"
#include "CompetitionPlus.h"
#include "SonicMania.h"
#include "ManiaExt.h"
#include "depends/tinyxml2/tinyxml2.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "Helpers.h"

namespace CompPlusSettings 
{
	using namespace SonicMania;

    #pragma region Internal Variables

    int NumberOfAnnouncers = 6;
    bool FixPlayers = false;
    bool AllowUpdateVictory = false;
    std::string Settings_FilePath;
    int DevMode_ControllerSwapPosition = 0;

    int CurrentRound_Plus = 0;
    int LastRound_NoPlus = 0;

    char ETA_OriginalCode[0x02];
    char TLK_OriginalCode[0x06];

    bool HasCopiedOriginalTimeCode = false;
    bool IsLimitedWriten = false;
    bool IsUnlimitedWriten = false;
    bool DevMenuEnabledMemory;

    Controller InitalInputP1;
    Controller InitalInputP2;
    Controller InitalInputP3;
    Controller InitalInputP4;

    bool InitalInputCollected = false;

    bool P1_InputSaved = false;
    bool P2_InputSaved = false;
    bool P3_InputSaved = false;
    bool P4_InputSaved = false;

    #pragma endregion

    #pragma region Status Variables

    SonicMania::CompetitionSession LastSession;

    int P1_Placement = 0;
    int P2_Placement = 0;
    int P3_Placement = 0;
    int P4_Placement = 0;

    int P1_LastPlacement = 0;
    int P2_LastPlacement = 0;
    int P3_LastPlacement = 0;
    int P4_LastPlacement = 0;

    int P1_TimeRanking = 0;
    int P2_TimeRanking = 0;
    int P3_TimeRanking = 0;
    int P4_TimeRanking = 0;

    int P1_TotalRingRanking = 0;
    int P2_TotalRingRanking = 0;
    int P3_TotalRingRanking = 0;
    int P4_TotalRingRanking = 0;

    int P1_ScoreRanking = 0;
    int P2_ScoreRanking = 0;
    int P3_ScoreRanking = 0;
    int P4_ScoreRanking = 0;

    int P1_RingRanking = 0;
    int P2_RingRanking = 0;
    int P3_RingRanking = 0;
    int P4_RingRanking = 0;

    int P1_ItemRanking = 0;
    int P2_ItemRanking = 0;
    int P3_ItemRanking = 0;
    int P4_ItemRanking = 0;

    int P1_AverageRanking = 0;
    int P2_AverageRanking = 0;
    int P3_AverageRanking = 0;
    int P4_AverageRanking = 0;

    #pragma endregion


    #pragma region Setting Variables

    //Developer Settings
    bool EnableDevMode = true;
    bool EnableDebugMode = true;
    bool DevMode_ControllerSwap = false;
    bool DarkDevMenu = true;

    bool DevMode_ControlPlayer1 = true;
    bool DevMode_ControlPlayer2 = false;
    bool DevMode_ControlPlayer3 = false;
    bool DevMode_ControlPlayer4 = false;

    //Stock Competition Settings
    int NumberOfRounds = 3; // Ignored when EndlessRounds = true;
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

    bool Player1PeeloutAbility = false;
    bool Player2PeeloutAbility = false;
    bool Player3PeeloutAbility = false;
    bool Player4PeeloutAbility = false;

    ChosenPlayer Player1ChosenPlayer = ChosenPlayer_Default;
    ChosenPlayer Player2ChosenPlayer = ChosenPlayer_Default;
    ChosenPlayer Player3ChosenPlayer = ChosenPlayer_Default;
    ChosenPlayer Player4ChosenPlayer = ChosenPlayer_Default;

    PlayerAbility Player1AbilitySet = AbilitySet_Default;
    PlayerAbility Player2AbilitySet = AbilitySet_Default;
    PlayerAbility Player3AbilitySet = AbilitySet_Default;
    PlayerAbility Player4AbilitySet = AbilitySet_Default;

    //Status States
    extern int CurrentLevelSelect = 0;

    #pragma endregion

    #pragma region Extension Methods

    bool TimeLessThan(Time& me, Time& t)
    {
        if (me.Minutes < t.Minutes) return true;
        else
        {
            if (me.Seconds < t.Seconds) return true;
            else
            {
                if (me.Centiseconds < t.Centiseconds) return true;
                else return false;
            }

        }
    }

    void ScorableIntStructSort(ScorableInt a[], int n) {
        int i, j, max;
        ScorableInt temp;
        for (i = 0; i < n - 1; i++)
        {
            max = i;
            for (j = i + 1; j < n; j++)
            {
                if (a[j].Value < a[max].Value) max = j;
                temp = a[i];
                a[i] = a[max];
                a[max] = temp;
            }
        }
    }

    void ScorableIntStructSortReverse(ScorableInt a[], int n) {
        int i, j, max;
        ScorableInt temp;
        for (i = 0; i < n - 1; i++) 
        {
            max = i;
            for (j = i + 1; j < n; j++) 
            {
                if (a[j].Value > a[max].Value) max = j;
                temp = a[i];
                a[i] = a[max];
                a[max] = temp;
            }
        }
    }

    void TimeStructSort(Time a[], int n) {
        int i, j, min;
        Time temp;
        for (i = 0; i < n - 1; i++)
        {
            min = i;
            for (j = i + 1; j < n; j++)
            {
                if (TimeLessThan(a[j], a[min])) min = j;
                temp = a[i];
                a[i] = a[min];
                a[min] = temp;
            }
        }
    }

    #pragma endregion


    #pragma region Fix Methods

    void DisableVSPointAddingAddress() 
    {
        void* vs_incrementing_address = (void*)(baseAddress + 0xE35C);
        char nops[2];
        memset(nops, 0x90, sizeof nops);
        WriteData(vs_incrementing_address, nops, 0x02);
    }

    void FixUnmatchingVSPlayers()
    {
        SonicMania::Character P1_Char = (SonicMania::Character)(SonicMania::Options->CompetitionSession.CharacterFlags >> 0x00 & 0xFF >> 1);
        SonicMania::Character P2_Char = (SonicMania::Character)(SonicMania::Options->CompetitionSession.CharacterFlags >> 0x08 & 0xFF >> 1);
        SonicMania::Character P3_Char = (SonicMania::Character)(SonicMania::Options->CompetitionSession.CharacterFlags >> 0x10 & 0xFF >> 1);
        SonicMania::Character P4_Char = (SonicMania::Character)(SonicMania::Options->CompetitionSession.CharacterFlags >> 0x18 & 0xFF >> 1);

        CompPlusSettings::SetPlayer(1, P1_Char, false);
        CompPlusSettings::SetPlayer(2, P2_Char, false);
        CompPlusSettings::SetPlayer(3, P3_Char, false);
        CompPlusSettings::SetPlayer(4, P4_Char, false);
    }

    void FixAbilites(SonicMania::EntityPlayer* Player)
    {
        int RealID = 1;

        if (Player == &Player1) RealID = 1;
        else if (Player == &Player2) RealID = 2;
        else if (Player == &Player3) RealID = 3;
        else if (Player == &Player4) RealID = 4;

        if (Player->Character == Character_Sonic)
        {
            if (Player->Moveset == MOVESET_SONIC)
            {

            }
            else if (Player->Moveset == MOVESET_TAILS)
            {
                SetAbility(RealID, CompPlusSettings::AbilitySet_Mighty);
            }
            else if (Player->Moveset == MOVESET_KNUX)
            {
                SetAbility(RealID, CompPlusSettings::AbilitySet_Mighty);
            }
            else if (Player->Moveset == MOVESET_MIGHTY)
            {

            }
            else if (Player->Moveset == MOVESET_RAY)
            {
                SetAbility(RealID, CompPlusSettings::AbilitySet_Sonic);
            }
        }
        else if (Player->Character == Character_Tails)
        {
            if (Player->Moveset == MOVESET_SONIC)
            {

            }
            else if (Player->Moveset == MOVESET_TAILS)
            {

            }
            else if (Player->Moveset == MOVESET_KNUX)
            {
                SetAbility(RealID, CompPlusSettings::AbilitySet_Mighty);
            }
            else if (Player->Moveset == MOVESET_MIGHTY)
            {

            }
            else if (Player->Moveset == MOVESET_RAY)
            {
                SetAbility(RealID, CompPlusSettings::AbilitySet_Sonic);
            }
        }
        else if (Player->Character == Character_Knux)
        {
            if (Player->Moveset == MOVESET_SONIC)
            {

            }
            else if (Player->Moveset == MOVESET_TAILS)
            {
                SetAbility(RealID, CompPlusSettings::AbilitySet_Knuckles);
            }
            else if (Player->Moveset == MOVESET_KNUX)
            {

            }
            else if (Player->Moveset == MOVESET_MIGHTY)
            {

            }
            else if (Player->Moveset == MOVESET_RAY)
            {
                SetAbility(RealID, CompPlusSettings::AbilitySet_Sonic);
            }
        }
        else if (Player->Character == Character_Mighty)
        {
            if (Player->Moveset == MOVESET_SONIC)
            {

            }
            else if (Player->Moveset == MOVESET_TAILS)
            {
                SetAbility(RealID, CompPlusSettings::AbilitySet_Mighty);
            }
            else if (Player->Moveset == MOVESET_KNUX)
            {
                SetAbility(RealID, CompPlusSettings::AbilitySet_Mighty);
            }
            else if (Player->Moveset == MOVESET_MIGHTY)
            {

            }
            else if (Player->Moveset == MOVESET_RAY)
            {
                SetAbility(RealID, CompPlusSettings::AbilitySet_Sonic);
            }
        }
        else if (Player->Character == Character_Ray)
        {
            if (Player->Moveset == MOVESET_SONIC)
            {

            }
            else if (Player->Moveset == MOVESET_TAILS)
            {
                SetAbility(RealID, CompPlusSettings::AbilitySet_Mighty);
            }
            else if (Player->Moveset == MOVESET_KNUX)
            {
                SetAbility(RealID, CompPlusSettings::AbilitySet_Mighty);
            }
            else if (Player->Moveset == MOVESET_MIGHTY)
            {

            }
            else if (Player->Moveset == MOVESET_RAY)
            {

            }
        }
    }

    void FixRayAndMighty2P()
    {
        int PatchP2Ray[] = { 0xE9, 0xC4, 0x01, 0x00, 0x00, 0x90 };
        int i;
        int OffsetNormal = 0xC31E5;
        for (i = 0; i < 6; i++)
        {
            WriteData<1>((void*)(baseAddress + OffsetNormal), PatchP2Ray[i]);//put data back.
            OffsetNormal++;

        }
    }

    #pragma endregion

    #pragma region Get Methods

    SonicMania::Character GetCharacter(CompPlusSettings::ChosenPlayer Character)
    {
        if (Character == ChosenPlayer_Sonic) return SonicMania::Character_Sonic;
        else if (Character == ChosenPlayer_Tails) return SonicMania::Character_Tails;
        else if (Character == ChosenPlayer_Knuckles) return SonicMania::Character_Knux;
        else if (Character == ChosenPlayer_Mighty) return SonicMania::Character_Mighty;
        else if (Character == ChosenPlayer_Ray) return SonicMania::Character_Ray;
        else return SonicMania::Character_None;
    }

    Time GetPlayerTime(int PlayerID)
    {
        Time PlayerTime;
        PlayerTime.PlayerID = PlayerID;
        int NumberOfPlayers = SonicMania::Options->CompetitionSession.NumberOfPlayers;
        if (PlayerID == 1 && NumberOfPlayers >= 1)
        {
            PlayerTime.Minutes = SonicMania::Options->CompetitionSession.TimeMinutes_P1;
            PlayerTime.Seconds = SonicMania::Options->CompetitionSession.TimeSeconds_P1;
            PlayerTime.Centiseconds = SonicMania::Options->CompetitionSession.TimeCentiseconds_P1;
        }
        else if (PlayerID == 2 && NumberOfPlayers >= 2)
        {
            PlayerTime.Minutes = SonicMania::Options->CompetitionSession.TimeMinutes_P2;
            PlayerTime.Seconds = SonicMania::Options->CompetitionSession.TimeSeconds_P2;
            PlayerTime.Centiseconds = SonicMania::Options->CompetitionSession.TimeCentiseconds_P2;
        }
        else if (PlayerID == 3 && NumberOfPlayers >= 3)
        {
            PlayerTime.Minutes = SonicMania::Options->CompetitionSession.TimeMinutes_P3;
            PlayerTime.Seconds = SonicMania::Options->CompetitionSession.TimeSeconds_P3;
            PlayerTime.Centiseconds = SonicMania::Options->CompetitionSession.TimeCentiseconds_P3;
        }
        else if (PlayerID == 4 && NumberOfPlayers >= 4)
        {
            PlayerTime.Minutes = SonicMania::Options->CompetitionSession.TimeMinutes_P4;
            PlayerTime.Seconds = SonicMania::Options->CompetitionSession.TimeSeconds_P4;
            PlayerTime.Centiseconds = SonicMania::Options->CompetitionSession.TimeCentiseconds_P4;
        }
        else 
        {
            PlayerTime.Minutes = 99;
            PlayerTime.Seconds = 99;
            PlayerTime.Centiseconds = 99;
        }
        return PlayerTime;
    }

    void GetTimeRanking(int& P1_Placement, int& P2_Placement, int& P3_Placement, int& P4_Placement)
    {
        Time Player1Time = GetPlayerTime(1);
        Time Player2Time = GetPlayerTime(2);
        Time Player3Time = GetPlayerTime(3);
        Time Player4Time = GetPlayerTime(4);

        Time PlayerTimes[4] = { Player1Time, Player2Time, Player3Time, Player4Time };
        TimeStructSort(PlayerTimes, 4);

        int Position = 1;

        int CurrentRound = SonicMania::Options->CompetitionSession.CurrentRound;

        for (int i = 0; i < 4; i++) 
        {
            if (PlayerTimes[i].PlayerID == 1)
            {
                if (Position == 1)
                {
                    SonicMania::Options->CompetitionSession.WinnerFlag[CurrentRound] = 1;
                }
                P1_Placement = Position;
                Position++;
            }
            else if (PlayerTimes[i].PlayerID == 2)
            {
                if (Position == 1)
                {
                    SonicMania::Options->CompetitionSession.WinnerFlag[CurrentRound] = 2;
                }
                P2_Placement = Position;
                Position++;
            }
            else if (PlayerTimes[i].PlayerID == 3)
            {
                if (Position == 1)
                {
                    SonicMania::Options->CompetitionSession.WinnerFlag[CurrentRound] = 3;
                }
                P3_Placement = Position;
                Position++;
            }
            else if (PlayerTimes[i].PlayerID == 4)
            {
                if (Position == 1)
                {
                    SonicMania::Options->CompetitionSession.WinnerFlag[CurrentRound] = 4;
                }
                P4_Placement = Position;
                Position++;
            }
        }
    }

    void GetTotalRingsRanking(int& P1_Placement, int& P2_Placement, int& P3_Placement, int& P4_Placement)
    {
        ScorableInt Player1Score = ScorableInt(SonicMania::Options->CompetitionSession.TotalRings_P1, 1);
        ScorableInt Player2Score = ScorableInt(SonicMania::Options->CompetitionSession.TotalRings_P2, 2);
        ScorableInt Player3Score = ScorableInt(SonicMania::Options->CompetitionSession.TotalRings_P3, 3);
        ScorableInt Player4Score = ScorableInt(SonicMania::Options->CompetitionSession.TotalRings_P4, 4);

        ScorableInt PlayerScores[4] = { Player1Score, Player2Score, Player3Score, Player4Score };
        ScorableIntStructSortReverse(PlayerScores, 4);

        int Position = 1;

        for (int i = 0; i < 4; i++)
        {
            if ((int)PlayerScores[i].PlayerID == 1)
            {
                P1_Placement = Position;
                Position++;
            }
            else if ((int)PlayerScores[i].PlayerID == 2)
            {
                P2_Placement = Position;
                Position++;
            }
            else if ((int)PlayerScores[i].PlayerID == 3)
            {
                P3_Placement = Position;
                Position++;
            }
            else if ((int)PlayerScores[i].PlayerID == 4)
            {
                P4_Placement = Position;
                Position++;
            }
        }
    }

    void GetRingsRanking(int& P1_Placement, int& P2_Placement, int& P3_Placement, int& P4_Placement)
    {
        ScorableInt Player1Score = ScorableInt(SonicMania::Options->CompetitionSession.Rings_P1, 1);
        ScorableInt Player2Score = ScorableInt(SonicMania::Options->CompetitionSession.Rings_P2, 2);
        ScorableInt Player3Score = ScorableInt(SonicMania::Options->CompetitionSession.Rings_P3, 3);
        ScorableInt Player4Score = ScorableInt(SonicMania::Options->CompetitionSession.Rings_P4, 4);

        ScorableInt PlayerScores[4] = { Player1Score, Player2Score, Player3Score, Player4Score };
        ScorableIntStructSortReverse(PlayerScores, 4);

        int Position = 1;

        for (int i = 0; i < 4; i++)
        {
            if ((int)PlayerScores[i].PlayerID == 1)
            {
                P1_Placement = Position;
                Position++;
            }
            else if ((int)PlayerScores[i].PlayerID == 2)
            {
                P2_Placement = Position;
                Position++;
            }
            else if ((int)PlayerScores[i].PlayerID == 3)
            {
                P3_Placement = Position;
                Position++;
            }
            else if ((int)PlayerScores[i].PlayerID == 4)
            {
                P4_Placement = Position;
                Position++;
            }
        }
    }

    void GetScoreRanking(int& P1_Placement, int& P2_Placement, int& P3_Placement, int& P4_Placement)
    {
        ScorableInt Player1Score = ScorableInt(SonicMania::Options->CompetitionSession.Score_P1, 1);
        ScorableInt Player2Score = ScorableInt(SonicMania::Options->CompetitionSession.Score_P2, 2);
        ScorableInt Player3Score = ScorableInt(SonicMania::Options->CompetitionSession.Score_P3, 3);
        ScorableInt Player4Score = ScorableInt(SonicMania::Options->CompetitionSession.Score_P4, 4);

        ScorableInt PlayerScores[4] = { Player1Score, Player2Score, Player3Score, Player4Score };
        ScorableIntStructSortReverse(PlayerScores, 4);

        int Position = 1;

        for (int i = 0; i < 4; i++)
        {
            if ((int)PlayerScores[i].PlayerID == 1)
            {
                P1_Placement = Position;
                Position++;
            }
            else if ((int)PlayerScores[i].PlayerID == 2)
            {
                P2_Placement = Position;
                Position++;
            }
            else if ((int)PlayerScores[i].PlayerID == 3)
            {
                P3_Placement = Position;
                Position++;
            }
            else if ((int)PlayerScores[i].PlayerID == 4)
            {
                P4_Placement = Position;
                Position++;
            }
        }
    }

    void GetItemRanking(int& P1_Placement, int& P2_Placement, int& P3_Placement, int& P4_Placement)
    {
        ScorableInt Player1Score = ScorableInt(SonicMania::Options->CompetitionSession.Items_P1, 1);
        ScorableInt Player2Score = ScorableInt(SonicMania::Options->CompetitionSession.Items_P2, 2);
        ScorableInt Player3Score = ScorableInt(SonicMania::Options->CompetitionSession.Items_P3, 3);
        ScorableInt Player4Score = ScorableInt(SonicMania::Options->CompetitionSession.Items_P4, 4);

        ScorableInt PlayerScores[4] = { Player1Score, Player2Score, Player3Score, Player4Score };
        ScorableIntStructSortReverse(PlayerScores, 4);

        int Position = 1;

        for (int i = 0; i < 4; i++)
        {
            if ((int)PlayerScores[i].PlayerID == 1)
            {
                P1_Placement = Position;
                Position++;
            }
            else if ((int)PlayerScores[i].PlayerID == 2)
            {
                P2_Placement = Position;
                Position++;
            }
            else if ((int)PlayerScores[i].PlayerID == 3)
            {
                P3_Placement = Position;
                Position++;
            }
            else if ((int)PlayerScores[i].PlayerID == 4)
            {
                P4_Placement = Position;
                Position++;
            }
        }
    }

    void GetAverageRanking(int& P1_Placement, int& P2_Placement, int& P3_Placement, int& P4_Placement) 
    {
        ScorableInt Player1Score = ScorableInt(P1_TimeRanking + P1_ScoreRanking + P1_RingRanking + P1_ItemRanking + P1_TotalRingRanking, 1);
        ScorableInt Player2Score = ScorableInt(P2_TimeRanking + P2_ScoreRanking + P2_RingRanking + P2_ItemRanking + P2_TotalRingRanking, 2);
        ScorableInt Player3Score = ScorableInt(P3_TimeRanking + P3_ScoreRanking + P3_RingRanking + P3_ItemRanking + P3_TotalRingRanking, 3);
        ScorableInt Player4Score = ScorableInt(P4_TimeRanking + P4_ScoreRanking + P4_RingRanking + P4_ItemRanking + P4_TotalRingRanking, 4);

        ScorableInt PlayerScores[4] = { Player1Score, Player2Score, Player3Score, Player4Score };
        ScorableIntStructSortReverse(PlayerScores, 4);

        int Position = 1;

        for (int i = 0; i < 4; i++)
        {
            if ((int)PlayerScores[i].PlayerID == 1)
            {
                P1_Placement = Position;
                Position++;
            }
            else if ((int)PlayerScores[i].PlayerID == 2)
            {
                P2_Placement = Position;
                Position++;
            }
            else if ((int)PlayerScores[i].PlayerID == 3)
            {
                P3_Placement = Position;
                Position++;
            }
            else if ((int)PlayerScores[i].PlayerID == 4)
            {
                P4_Placement = Position;
                Position++;
            }
        }
    }

    #pragma endregion

    #pragma region Set Methods

    void SetFinalRanking(int PlayerRanks[4], int& P1_Placement, int& P2_Placement, int& P3_Placement, int& P4_Placement)
    {
        int CurrentRound = SonicMania::Options->CompetitionSession.CurrentRound;

        for (int i = 0; i < 4; i++)
        {
            int Position = PlayerRanks[i];
            int CurrentPlayer = i + 1;

            if (CurrentPlayer == 1)
            {
                if (Position == 1)
                {
                    SonicMania::Options->CompetitionSession.WinnerFlag[CurrentRound] = 1;
                    SonicMania::Options->CompetitionSession.Wins_P1 += 1;
                }
                P1_Placement = Position;
                Position++;
            }
            else if (CurrentPlayer == 2)
            {
                if (Position == 1)
                {
                    SonicMania::Options->CompetitionSession.WinnerFlag[CurrentRound] = 2;
                    SonicMania::Options->CompetitionSession.Wins_P2 += 1;
                }
                P2_Placement = Position;
                Position++;
            }
            else if (CurrentPlayer == 3)
            {
                if (Position == 1)
                {
                    SonicMania::Options->CompetitionSession.WinnerFlag[CurrentRound] = 3;
                    SonicMania::Options->CompetitionSession.Wins_P3 += 1;
                }
                P3_Placement = Position;
                Position++;
            }
            else if (CurrentPlayer == 4)
            {
                if (Position == 1)
                {
                    SonicMania::Options->CompetitionSession.WinnerFlag[CurrentRound] = 4;
                    SonicMania::Options->CompetitionSession.Wins_P4 += 1;
                }
                P4_Placement = Position;
                Position++;
            }
        }
    }

    void SetWinnerBasedOnSpecific(CompPlusSettings::VictoryMode Setting) 
    {
        int PlayerTimes[4] = { P1_TimeRanking, P2_TimeRanking, P3_TimeRanking, P4_TimeRanking };
        int PlayerScores[4] = { P1_ScoreRanking, P2_ScoreRanking, P3_ScoreRanking, P4_ScoreRanking };
        int PlayerRings[4] = { P1_RingRanking, P2_RingRanking, P3_RingRanking, P4_RingRanking };
        int PlayerItems[4] = { P1_ItemRanking, P2_ItemRanking, P3_ItemRanking, P4_ItemRanking };
        int PlayerTotalRings[4] = { P1_TotalRingRanking, P2_TotalRingRanking, P3_TotalRingRanking, P4_TotalRingRanking };
        int PlayerAverage[4] = { P1_AverageRanking, P2_AverageRanking, P3_AverageRanking, P4_AverageRanking };

        switch (Setting)
        {
            case VictoryMode_Time:
                SetFinalRanking(PlayerTimes, P1_Placement, P2_Placement, P3_Placement, P4_Placement);
                break;
            case VictoryMode_Score:
                SetFinalRanking(PlayerScores, P1_Placement, P2_Placement, P3_Placement, P4_Placement);
                break;
            case VictoryMode_Rings:
                SetFinalRanking(PlayerRings, P1_Placement, P2_Placement, P3_Placement, P4_Placement);
                break;
            case VictoryMode_TotalRings:
                SetFinalRanking(PlayerTotalRings, P1_Placement, P2_Placement, P3_Placement, P4_Placement);
                break;
            case VictoryMode_Items:
                SetFinalRanking(PlayerItems, P1_Placement, P2_Placement, P3_Placement, P4_Placement);
                break;
            case VictoryMode_Default:
                SetFinalRanking(PlayerAverage, P1_Placement, P2_Placement, P3_Placement, P4_Placement);
                break;
        }
    }

    void SetMonitorMode(CompPlusSettings::ItemsConfig Value) 
    {
        MonitorTypes = Value;       
    }

    void SetNumberOfRounds(int Value) 
    {
        NumberOfRounds = Value;     
    }

    void SetLastMatchResults() 
    {
        P1_LastPlacement = P1_Placement;
        P2_LastPlacement = P2_Placement;
        P3_LastPlacement = P3_Placement;
        P4_LastPlacement = P4_Placement;
        P1_Placement = 0;
        P2_Placement = 0;
        P3_Placement = 0;
        P4_Placement = 0;
    }

    void SetSonicAbilities()
    {
        //21 : No Dropdash or Instasheild     - (CD)
        //13 : Dropdash and Instasheild		  - (Max Control)
        //2  : Dropdash Only			      - (Mania)
        //8  : Instasheild Only		          - (S3&K)

        int MovesetID = 21;

        if (DropdashAbility && InstaSheildAbility) MovesetID = 13;	      // Max Control Moveset
        else if (DropdashAbility && !InstaSheildAbility) MovesetID = 0;	  // Mania Moveset
        else if (!DropdashAbility && InstaSheildAbility) MovesetID = 8;	  // S3&K Moveset
        else if (!DropdashAbility && !InstaSheildAbility) MovesetID = 21; // CD Moveset


        BYTE* Pointer = *(BYTE**)((baseAddress + 0xAA763C));
        WriteData((BYTE*)(Pointer + 0x410B4), (BYTE)MovesetID);
    }

    void SetAbility(int PlayerID, CompPlusSettings::PlayerAbility Ability)
	{
		if (PlayerID == 1)
		{
			CompPlusSettings::Player1AbilitySet = Ability;
			if (Ability == CompPlusSettings::AbilitySet_Sonic) Player1.Moveset = MOVESET_SONIC;
			else if (Ability == CompPlusSettings::AbilitySet_Tails) Player1.Moveset = MOVESET_TAILS;
			else if (Ability == CompPlusSettings::AbilitySet_Knuckles)Player1.Moveset = MOVESET_KNUX;
			else if (Ability == CompPlusSettings::AbilitySet_Mighty) Player1.Moveset = MOVESET_MIGHTY;
			else if (Ability == CompPlusSettings::AbilitySet_Ray) Player1.Moveset = MOVESET_RAY;
		}
		else if (PlayerID == 2)
		{
			CompPlusSettings::Player2AbilitySet = Ability;
			if (Ability == CompPlusSettings::AbilitySet_Sonic) Player2.Moveset = MOVESET_SONIC;
			else if (Ability == CompPlusSettings::AbilitySet_Tails) Player2.Moveset = MOVESET_TAILS;
			else if (Ability == CompPlusSettings::AbilitySet_Knuckles)Player2.Moveset = MOVESET_KNUX;
			else if (Ability == CompPlusSettings::AbilitySet_Mighty) Player2.Moveset = MOVESET_MIGHTY;
			else if (Ability == CompPlusSettings::AbilitySet_Ray) Player2.Moveset = MOVESET_RAY;
		}
		else if (PlayerID == 3)
		{
			CompPlusSettings::Player3AbilitySet = Ability;
			if (Ability == CompPlusSettings::AbilitySet_Sonic) Player3.Moveset = MOVESET_SONIC;
			else if (Ability == CompPlusSettings::AbilitySet_Tails) Player3.Moveset = MOVESET_TAILS;
			else if (Ability == CompPlusSettings::AbilitySet_Knuckles)Player3.Moveset = MOVESET_KNUX;
			else if (Ability == CompPlusSettings::AbilitySet_Mighty) Player3.Moveset = MOVESET_MIGHTY;
			else if (Ability == CompPlusSettings::AbilitySet_Ray) Player3.Moveset = MOVESET_RAY;
		}
		else if (PlayerID == 4)
		{
			CompPlusSettings::Player4AbilitySet = Ability;
			if (Ability == CompPlusSettings::AbilitySet_Sonic) Player4.Moveset = MOVESET_SONIC;
			else if (Ability == CompPlusSettings::AbilitySet_Tails) Player4.Moveset = MOVESET_TAILS;
			else if (Ability == CompPlusSettings::AbilitySet_Knuckles)Player4.Moveset = MOVESET_KNUX;
			else if (Ability == CompPlusSettings::AbilitySet_Mighty) Player4.Moveset = MOVESET_MIGHTY;
			else if (Ability == CompPlusSettings::AbilitySet_Ray) Player4.Moveset = MOVESET_RAY;
		}
        
	}

	void SetDropdashAbility(bool Value)
	{
		DropdashAbility = Value;
		SetSonicAbilities();       
	}

	void SetPeeloutAbility(int PlayerID, bool State)
	{
		SonicMania::Ability PeeloutState = MOVESET_NONE;
		if (State == true) PeeloutState = UpAbility_Peelout;

		if (PlayerID == 1)
		{
			Player1.UpAbility = PeeloutState;
			CompPlusSettings::Player1PeeloutAbility = State;
		}
		else if (PlayerID == 2)
		{
			Player2.UpAbility = PeeloutState;
			CompPlusSettings::Player2PeeloutAbility = State;
		}
		else if (PlayerID == 3)
		{
			Player3.UpAbility = PeeloutState;
			CompPlusSettings::Player3PeeloutAbility = State;
		}
		else if (PlayerID == 4)
		{
			Player4.UpAbility = PeeloutState;
			CompPlusSettings::Player4PeeloutAbility = State;
		}
		SetSonicAbilities();  
	}

	void SetInstaSheildAbility(bool State)
	{
		InstaSheildAbility = State;
		SetSonicAbilities();    
	}
    
    void SetInitalLives(int value)
    {
        InitalLives = value;

        if (InitalLives == 100) InfiniteLives = true;
        else InfiniteLives = false;     
    }

    void SetAnnouncer(AnnouncerType Value)
    {
        CurrentAnnouncer = Value;    
    }

	void SetPlayer(int PlayerID, SonicMania::Character Character, bool Force)
	{
		CompPlusSettings::ChosenPlayer Player = CompPlusSettings::ChosenPlayer_Default;

		if (Character == Characters_Sonic) Player = CompPlusSettings::ChosenPlayer_Sonic;
		else if (Character == Characters_Tails) Player = CompPlusSettings::ChosenPlayer_Tails;
		else if (Character == Characters_Knuckles) Player = CompPlusSettings::ChosenPlayer_Knuckles;
		else if (Character == Character_Mighty) Player = CompPlusSettings::ChosenPlayer_Mighty;
		else if (Character == Characters_Ray) Player = CompPlusSettings::ChosenPlayer_Ray;


        int CharacterID = (int)Character;
        //SonicMania::Options->CompetitionSession.CharacterFlags &= 0xFFFFFFFF ^ (0xFF << (PlayerID - 1));

		if (PlayerID == 1)
		{
			if (Force) SonicMania::FastChangeCharacter(&Player1, Character);
            SonicMania::Options->CompetitionSession.CharacterFlags |= Character << (0 * 8);
            CompPlusSettings::Player1ChosenPlayer = Player;
		}
		else if (PlayerID == 2)
		{
			if (Force) SonicMania::FastChangeCharacter(&Player2, Character);
            SonicMania::Options->CompetitionSession.CharacterFlags |= Character << (1 * 8);
            CompPlusSettings::Player2ChosenPlayer = Player;
		}
		else if (PlayerID == 3)
		{
			if (Force) SonicMania::FastChangeCharacter(&Player3, Character);
            SonicMania::Options->CompetitionSession.CharacterFlags |= Character << (2 * 8);
            CompPlusSettings::Player3ChosenPlayer = Player;
		}
		else if (PlayerID == 4)
		{
			if (Force) SonicMania::FastChangeCharacter(&Player4, Character);
            SonicMania::Options->CompetitionSession.CharacterFlags |= Character << (3 * 8);
            CompPlusSettings::Player4ChosenPlayer = Player;
		}
        FixRayAndMighty2P();
	}

	void SetPlayer(int PlayerID, CompPlusSettings::ChosenPlayer Character, bool Force)
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

		SetPlayer(PlayerID, Player, Force);
	}

    void SetTimeLimit(bool State) 
    {
        TimeLimit = State;       
    }

    void SetVictoryMethod(CompPlusSettings::VictoryMode State) 
    {
        VictoryStyle = State;       
    }

    void SetEndlessRounds(bool State)
    {
        EndlessRounds = State;        
    }

    void SetCurrentLSelect(int value)
    {
        CurrentLevelSelect = value;      
    }

    #pragma endregion

    #pragma region Update Methods

    void UpdateStockSettings() 
    {
        DisableVSPointAddingAddress();
        if (SonicMania::Options->CompetitionSession.MonitorMode != MonitorTypes) SonicMania::Options->CompetitionSession.MonitorMode = MonitorTypes;
        if (SonicMania::Options->ItemMode != MonitorTypes) SonicMania::Options->ItemMode = MonitorTypes;
    }

    void UpdatePlayerSprites(SonicMania::EntityPlayer &Player)
    {
        if (Player.Character == Characters_Sonic) 
        {
            if (Player.State == PLAYERSTATE_HAMMERDROP) 
            {
                //Player.Animation.CurrentAnimation = 54; //551
                //SetSpriteAnimation(0, 54, &Player.Animation, true, 6);
            }
        }
    }

    void UpdateMultiPlayerSprites() 
    {
        UpdatePlayerSprites(Player1);
        UpdatePlayerSprites(Player2);
        UpdatePlayerSprites(Player3);
        UpdatePlayerSprites(Player4);
    }

    void UpdateRounds() 
    {
        if (SonicMania::Options->CompetitionSession.TotalRounds != NumberOfRounds) SonicMania::Options->CompetitionSession.TotalRounds = NumberOfRounds;
        if (EndlessRounds) 
        {
            if (SonicMania::Options->CompetitionSession.CurrentRound != 0) SonicMania::Options->CompetitionSession.CurrentRound = 0;
        }
        else 
        {
            if (SonicMania::Options->CompetitionSession.CurrentRound == 0) 
            {
                //Reset Personalized Round Counter
                CurrentRound_Plus = 0;
                LastRound_NoPlus = 0;
            }
            else 
            {
                if (SonicMania::Options->CompetitionSession.CurrentRound != LastRound_NoPlus) 
                {
                    if (SonicMania::Options->CompetitionSession.CurrentRound == 5 && CurrentRound_Plus != (NumberOfRounds - 1))
                    {
                        int Diff = SonicMania::Options->CompetitionSession.CurrentRound - LastRound_NoPlus;
                        LastRound_NoPlus = 0;
                        SonicMania::Options->CompetitionSession.CurrentRound = 0;
                        CurrentRound_Plus += Diff;
                    }
                    else 
                    {
                        int Diff = SonicMania::Options->CompetitionSession.CurrentRound - LastRound_NoPlus;
                        LastRound_NoPlus = SonicMania::Options->CompetitionSession.CurrentRound;
                        CurrentRound_Plus += Diff;
                    }
                }
            }
        }
    }

    void UpdateWinnerForVictory() 
    {
        if (AllowUpdateVictory) 
        {
            GetTimeRanking(P1_TimeRanking, P2_TimeRanking, P3_TimeRanking, P4_TimeRanking);
            GetRingsRanking(P1_RingRanking, P2_RingRanking, P3_RingRanking, P4_RingRanking);
            GetTotalRingsRanking(P1_TotalRingRanking, P2_TotalRingRanking, P3_TotalRingRanking, P4_TotalRingRanking);
            GetScoreRanking(P1_ScoreRanking, P2_ScoreRanking, P3_ScoreRanking, P4_ScoreRanking);
            GetItemRanking(P1_ItemRanking, P2_ItemRanking, P3_ItemRanking, P4_ItemRanking);
            GetAverageRanking(P1_AverageRanking, P2_AverageRanking, P3_AverageRanking, P4_AverageRanking);

            SetWinnerBasedOnSpecific(VictoryStyle);


            CompPlusSettings::LastSession = SonicMania::Options->CompetitionSession;
            CompPlusSettings::SetLastMatchResults();

            AllowUpdateVictory = false;
        }

    }

    void UpdatePlayerResults() 
    {
        int FinishFlags = SonicMania::Options->CompetitionSession.FinishFlags;
        int P1_FinishFlag = Player1.Active ? (FinishFlags >> 0x00 & 0xFF) : 0;
        int P2_FinishFlag = Player2.Active ? (FinishFlags >> 0x08 & 0xFF) : 0;
        int P3_FinishFlag = Player3.Active ? (FinishFlags >> 0x10 & 0xFF) : 0;
        int P4_FinishFlag = Player4.Active ? (FinishFlags >> 0x18 & 0xFF) : 0;

        bool P1_Finished = Player1.Active ? P1_FinishFlag != 0 : true;
        bool P2_Finished = Player2.Active ? P2_FinishFlag != 0 : true;
        bool P3_Finished = Player3.Active ? P3_FinishFlag != 0 : true;
        bool P4_Finished = Player4.Active ? P4_FinishFlag != 0 : true;

        if (P1_Finished && P2_Finished && P3_Finished && P4_Finished && Timer.Enabled) UpdateWinnerForVictory();
        else AllowUpdateVictory = true;
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

    void UpdateTimer(bool isLimited)
    {
        void* extended_time_address = (void*)(baseAddress + 0x535BD);
        void* time_limit_kill_jne_address = (void*)(baseAddress + 0xADD03);
        void* time_limit_skip_jne_adderss = (void*)(baseAddress + 0x00ADDE7);
        void* time_limit_kill_jmp_nop_address = (void*)(baseAddress + 0xADD03 + 0x5);
        // NOP bytes
        char nops1[4];
        char nops2[8];
        memset(nops1, 0x90, sizeof nops1);
        memset(nops2, 0x90, sizeof nops2);

        if (!HasCopiedOriginalTimeCode)
        {
            memcpy(ETA_OriginalCode, extended_time_address, 0x02);
            memcpy(TLK_OriginalCode, time_limit_kill_jne_address, 0x06);
            HasCopiedOriginalTimeCode = true;
        }

        if (!isLimited)
        {
            if (!IsUnlimitedWriten)
            {
                WriteData(extended_time_address, nops2, 0x02);
                ReplaceJNEwithJump(time_limit_kill_jne_address, time_limit_skip_jne_adderss);
                WriteData(time_limit_kill_jmp_nop_address, nops1, 0x06);
                IsUnlimitedWriten = true;
                IsLimitedWriten = false;
            }
        }
        else
        {
            if (!IsLimitedWriten)
            {
                WriteData(extended_time_address, ETA_OriginalCode, 0x02);
                WriteData(time_limit_kill_jne_address, TLK_OriginalCode, 0x06);
                IsLimitedWriten = true;
                IsUnlimitedWriten = false;
            }
        }
    }

    #pragma endregion

    #pragma region DevMode Methods

    void DevMode_WarpAllPlayersTo(int PlayerID)
    {
        int x, y;
        if (PlayerID == 4)
        {
            x = Player4.Position.X;
            y = Player4.Position.Y;
        }
        else if (PlayerID == 3)
        {
            x = Player3.Position.X;
            y = Player3.Position.Y;
        }
        else if (PlayerID == 2)
        {
            x = Player2.Position.X;
            y = Player2.Position.Y;
        }
        else
        {
            x = Player1.Position.X;
            y = Player1.Position.Y;
        }

        Player1.Position.X = x;
        Player1.Position.Y = y;

        Player2.Position.X = x;
        Player2.Position.Y = y;

        Player3.Position.X = x;
        Player3.Position.Y = y;

        Player4.Position.X = x;
        Player4.Position.Y = y;
    }

    void DevMode_BindPlayer1()
    {
        if (DevMode_ControlPlayer1 || !EnableDevMode)
        {
            if (P1_InputSaved)
            {
                SonicMania::PlayerControllers[1] = InitalInputP1;
                P1_InputSaved = false;
            }
            InitalInputP1 = SonicMania::PlayerControllers[1];
        }

        if (!DevMode_ControlPlayer1)
        {
            if (!P1_InputSaved)
            {
                InitalInputP1 = SonicMania::PlayerControllers[1];
                P1_InputSaved = true;

                SonicMania::PlayerControllers[1].A.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].B.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].C.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].X.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Y.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Z.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Up.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Down.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Left.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Right.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Start.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Select.Key = (DWORD)0x0;
            }

        }
    }

    void DevMode_BindController(int TargetPlayerID)
    {
        switch (TargetPlayerID)
        {
        case 2:
            if (!P2_InputSaved)
            {
                InitalInputP2 = SonicMania::PlayerControllers[TargetPlayerID];
                P2_InputSaved = true;
            }
            break;
        case 3:
            if (!P3_InputSaved)
            {
                InitalInputP3 = SonicMania::PlayerControllers[TargetPlayerID];
                P3_InputSaved = true;
            }
            break;
        case 4:
            if (!P4_InputSaved)
            {
                InitalInputP4 = SonicMania::PlayerControllers[TargetPlayerID];
                P4_InputSaved = true;
            }
            break;
        }

        SonicMania::PlayerControllers[TargetPlayerID].A.Key = InitalInputP1.A.Key;
        SonicMania::PlayerControllers[TargetPlayerID].B.Key = InitalInputP1.B.Key;
        SonicMania::PlayerControllers[TargetPlayerID].C.Key = InitalInputP1.C.Key;
        SonicMania::PlayerControllers[TargetPlayerID].X.Key = InitalInputP1.X.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Y.Key = InitalInputP1.Y.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Z.Key = InitalInputP1.Z.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Up.Key = InitalInputP1.Up.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Down.Key = InitalInputP1.Down.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Left.Key = InitalInputP1.Left.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Right.Key = InitalInputP1.Right.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Start.Key = InitalInputP1.Start.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Select.Key = InitalInputP1.Select.Key;

    }

    void DevMode_RestoreController(int TargetPlayerID)
    {
        switch (TargetPlayerID)
        {
        case 2:
            if (P2_InputSaved)
            {
                SonicMania::PlayerControllers[TargetPlayerID] = InitalInputP2;
                P2_InputSaved = false;
            }
            break;
        case 3:
            if (P3_InputSaved)
            {
                SonicMania::PlayerControllers[TargetPlayerID] = InitalInputP3;
                P3_InputSaved = false;
            }
            break;
        case 4:
            if (P4_InputSaved)
            {
                SonicMania::PlayerControllers[TargetPlayerID] = InitalInputP4;
                P4_InputSaved = false;
            }
            break;
        }
    }

    void DevModeLoop()
    {
        if (EnableDebugMode)
        {
            DebugEnabled = 1;
        }

        DevMode_BindPlayer1();

        if (EnableDevMode)
        {
            if (DevMode_ControlPlayer2) DevMode_BindController(2);
            else DevMode_RestoreController(2);

            if (DevMode_ControlPlayer3) DevMode_BindController(3);
            else DevMode_RestoreController(3);

            if (DevMode_ControlPlayer4) DevMode_BindController(4);
            else DevMode_RestoreController(4);
        }
        else
        {
            DevMode_RestoreController(2);
            DevMode_RestoreController(3);
            DevMode_RestoreController(4);
        }
    }

    #pragma endregion

    #pragma region Settings Methods

    void RefreshSettings()
    {
        SetAbility(1, Player1AbilitySet);
        SetAbility(2, Player2AbilitySet);
        SetAbility(3, Player3AbilitySet);
        SetAbility(4, Player4AbilitySet);

        FixAbilites(&Player1);
        FixAbilites(&Player2);
        FixAbilites(&Player3);
        FixAbilites(&Player4);

        SetPeeloutAbility(1, Player1PeeloutAbility);
        SetPeeloutAbility(2, Player2PeeloutAbility);
        SetPeeloutAbility(3, Player3PeeloutAbility);
        SetPeeloutAbility(4, Player4PeeloutAbility);

        SetSonicAbilities();

        FixPlayers = true;
    }

    void LoadSettings()
    {
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
            tinyxml2::XMLDocument document;
            document.Parse(static_cast<const char*>(xml), size);

            tinyxml2::XMLElement* xmlSettings = document.FirstChildElement("Settings");
            if (xmlSettings)
            {
                for (auto xmlOption = xmlSettings->FirstChildElement(); xmlOption != nullptr; xmlOption = xmlOption->NextSiblingElement())
                {
                    LogInfo("XML", xmlOption->Name());
                    if (!strcmp(xmlOption->Name(), "SelectedAnnouncer"))
                    {
                        const char* str_value = xmlOption->GetText();
                        int value = atoi(str_value);
                        CurrentAnnouncer = (AnnouncerType)value;
                    }
                    else if (!strcmp(xmlOption->Name(), "InitalLives"))
                    {
                        const char* str_value = xmlOption->GetText();
                        int value = atoi(str_value);
                        InitalLives = value;
                    }
                    else if (!strcmp(xmlOption->Name(), "TimeLimit"))
                    {
                        const char* str_value = xmlOption->GetText();
                        if (str_value == "1") TimeLimit = true;
                        else TimeLimit = false;
                    }
                    else if (!strcmp(xmlOption->Name(), "UseDropdash"))
                    {
                        const char* str_value = xmlOption->GetText();
                        if (str_value == "1") DropdashAbility = true;
                        else DropdashAbility = false;
                    }
                    else if (!strcmp(xmlOption->Name(), "UseInstaSheild"))
                    {
                        const char* str_value = xmlOption->GetText();
                        if (str_value == "1") InstaSheildAbility = true;
                        else InstaSheildAbility = false;
                    }
                    else if (!strcmp(xmlOption->Name(), "PeeloutP1"))
                    {
                        const char* str_value = xmlOption->GetText();
                        if (str_value == "1") Player1PeeloutAbility = true;
                        else Player1PeeloutAbility = false;
                    }
                    else if (!strcmp(xmlOption->Name(), "PeeloutP2"))
                    {
                        const char* str_value = xmlOption->GetText();
                        if (str_value == "1") Player2PeeloutAbility = true;
                        else Player2PeeloutAbility = false;
                    }
                    else if (!strcmp(xmlOption->Name(), "PeeloutP3"))
                    {
                        const char* str_value = xmlOption->GetText();
                        if (str_value == "1") Player3PeeloutAbility = true;
                        else Player3PeeloutAbility = false;
                    }
                    else if (!strcmp(xmlOption->Name(), "PeeloutP4"))
                    {
                        const char* str_value = xmlOption->GetText();
                        if (str_value == "1") Player4PeeloutAbility = true;
                        else Player4PeeloutAbility = false;
                    }
                    else if (!strcmp(xmlOption->Name(), "CurrentLSelect"))
                    {
                        const char* str_value = xmlOption->GetText();
                        int value = atoi(str_value);
                        CurrentLevelSelect = value;
                    }
                    else if (!strcmp(xmlOption->Name(), "VictoryStyle"))
                    {
                        const char* str_value = xmlOption->GetText();
                        int value = atoi(str_value);
                        VictoryStyle = (VictoryMode)value;
                    }
                    else if (!strcmp(xmlOption->Name(), "EndlessRounds"))
                    {
                        const char* str_value = xmlOption->GetText();
                        if (str_value == "1") EndlessRounds = true;
                        else EndlessRounds = false;
                    }
                    else if (!strcmp(xmlOption->Name(), "MonitorMode"))
                    {
                        const char* str_value = xmlOption->GetText();
                        int value = atoi(str_value);
                        MonitorTypes = (ItemsConfig)value;
                    }
                    else if (!strcmp(xmlOption->Name(), "NumberOfRounds"))
                    {
                        const char* str_value = xmlOption->GetText();
                        int value = atoi(str_value);
                        NumberOfRounds = value;
                    }
                    else if (!strcmp(xmlOption->Name(), "EnableDebugMode"))
                    {
                        const char* str_value = xmlOption->GetText();
                        if (str_value == "1") EnableDebugMode = true;
                        else EnableDebugMode = false;
                    }
                    else if (!strcmp(xmlOption->Name(), "EnableDevMode"))
                    {
                        const char* str_value = xmlOption->GetText();
                        if (str_value == "1") EnableDevMode = true;
                        else EnableDevMode = false;
                    }
                    else if (!strcmp(xmlOption->Name(), "DarkDevMenu"))
                    {
                        const char* str_value = xmlOption->GetText();
                        if (str_value == "1") DarkDevMenu = true;
                        else DarkDevMenu = false;
                    }
                }
            }
            else
            {

            }
        }
        // Clean up
        free(xml);
    }

    void SaveSettings()
    {
        tinyxml2::XMLDocument document;

        std::string text = "<Settings>";
        text += "<SelectedAnnouncer>" + IntToString(CurrentAnnouncer) + "</SelectedAnnouncer>";
        text += "<InitalLives>" + IntToString(InitalLives) + "</InitalLives>";
        text += "<TimeLimit>" + std::to_string(TimeLimit) + "</TimeLimit>";
        text += "<UseDropdash>" + std::to_string(DropdashAbility) + "</UseDropdash>";
        text += "<UseInstaSheild>" + std::to_string(InstaSheildAbility) + "</UseInstaSheild>";
        text += "<PeeloutP1>" + std::to_string(Player1PeeloutAbility) + "</PeeloutP1>";
        text += "<PeeloutP2>" + std::to_string(Player2PeeloutAbility) + "</PeeloutP2>";
        text += "<PeeloutP3>" + std::to_string(Player3PeeloutAbility) + "</PeeloutP3>";
        text += "<PeeloutP4>" + std::to_string(Player4PeeloutAbility) + "</PeeloutP4>";
        text += "<CurrentLSelect>" + std::to_string(CurrentLevelSelect) + "</CurrentLSelect>";
        text += "<VictoryStyle>" + std::to_string(VictoryStyle) + "</VictoryStyle>";
        text += "<EndlessRounds>" + std::to_string(EndlessRounds) + "</EndlessRounds>";
        text += "<NumberOfRounds>" + std::to_string(NumberOfRounds) + "</NumberOfRounds>";
        text += "<MonitorMode>" + std::to_string(MonitorTypes) + "</MonitorMode>";
        text += "<EnableDebugMode>" + std::to_string(EnableDebugMode) + "</EnableDebugMode>";
        text += "<EnableDevMode>" + std::to_string(EnableDevMode) + "</EnableDevMode>";
        text += "<DarkDevMenu>" + std::to_string(DarkDevMenu) + "</DarkDevMenu>";
        text += "</Settings>";
        document.Parse((const char*)text.c_str());
        document.SaveFile(Settings_FilePath.c_str());
    }

    #pragma endregion

    void OnStageChange() 
    {
        SaveSettings();
    }

    void OnFrame()
    {
        if (FixPlayers) FixPlayers = false;
        UpdateLives();
        UpdateRounds();
        UpdatePlayerResults();
        UpdateStockSettings();
        UpdateMultiPlayerSprites();
        UpdateTimer(!TimeLimit);
        DevModeLoop();
    }


 
}