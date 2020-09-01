#include "stdafx.h"
#include "IZAPI.h"
#include "SonicMania.h"
#include "ManiaExt.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "CompPlus_Scoring.h"
#include "CompPlus_Settings.h"


namespace CompPlus_Scoring
{
     SonicMania::CompetitionSession LastSession;

     bool AllowUpdateVictory = false;

     const char* LastZone = "???";

     int WinWait = 0;
     int WinWaitMax = 100;

     int P1_Placement = 0;
     int P2_Placement = 0;
     int P3_Placement = 0;
     int P4_Placement = 0;

     int P1_LastPlacement = 0;
     int P2_LastPlacement = 0;
     int P3_LastPlacement = 0;
     int P4_LastPlacement = 0;

     int P1_WinsPlus = 0;
     int P2_WinsPlus = 0;
     int P3_WinsPlus = 0;
     int P4_WinsPlus = 0;

     bool P1_HasWon = false;
     bool P2_HasWon = false;
     bool P3_HasWon = false;
     bool P4_HasWon = false;

     int LastCurrentRound = 0;

     bool ThisMatchIsTied = false;
     bool CanGoToFinalResults = false;

    std::vector<ScorableTime> TimeRanking;
    std::vector<ScorableInt> TotalRingRanking;
    std::vector<ScorableInt> ScoreRanking;
    std::vector<ScorableInt> RingRanking;
    std::vector<ScorableInt> ItemRanking;
    std::vector<ScorableInt> AverageRanking;
    std::vector<ScorableInt> AntiRingRanking;

    #pragma region SonicMania Header Get/Set Methods

    void SetCurrentRound(int value) 
    {
        SonicMania::Options->CompetitionSession.CurrentRound = value;
    }

    int GetCurrentRound() 
    {
        return SonicMania::Options->CompetitionSession.CurrentRound;
    }

    int GetPlayerTime(int PlayerID, int Mode) 
    {
        if (PlayerID == 1) 
        {
            if (Mode == 0) return SonicMania::Options->CompetitionSession.TimeMinutes_P1;
            else if (Mode == 1) return SonicMania::Options->CompetitionSession.TimeSeconds_P1;
            else if (Mode == 2) return SonicMania::Options->CompetitionSession.TimeCentiseconds_P1;
        }
        else if (PlayerID == 2)
        {
            if (Mode == 0) return SonicMania::Options->CompetitionSession.TimeMinutes_P2;
            else if (Mode == 1) return SonicMania::Options->CompetitionSession.TimeSeconds_P2;
            else if (Mode == 2) return SonicMania::Options->CompetitionSession.TimeCentiseconds_P2;
        }
        else if (PlayerID == 3)
        {
            if (Mode == 0) return SonicMania::Options->CompetitionSession.TimeMinutes_P3;
            else if (Mode == 1) return SonicMania::Options->CompetitionSession.TimeSeconds_P3;
            else if (Mode == 2) return SonicMania::Options->CompetitionSession.TimeCentiseconds_P3;
        }
        else if (PlayerID == 4)
        {
            if (Mode == 0) return SonicMania::Options->CompetitionSession.TimeMinutes_P4;
            else if (Mode == 1) return SonicMania::Options->CompetitionSession.TimeSeconds_P4;
            else if (Mode == 2) return SonicMania::Options->CompetitionSession.TimeCentiseconds_P4;
        }
        
        return 0;
    }

    int GetPlayerRings(int PlayerID)
    {
        if (PlayerID == 1)
        {
            return SonicMania::Options->CompetitionSession.Rings_P1;
        }
        else if (PlayerID == 2)
        {
            return SonicMania::Options->CompetitionSession.Rings_P2;
        }
        else if (PlayerID == 3)
        {
            return SonicMania::Options->CompetitionSession.Rings_P3;
        }
        else if (PlayerID == 4)
        {
            return SonicMania::Options->CompetitionSession.Rings_P4;
        }
        else return 0;
    }

    int GetPlayerTotalRings(int PlayerID)
    {
        if (PlayerID == 1)
        {
            return SonicMania::Options->CompetitionSession.TotalRings_P1;
        }
        else if (PlayerID == 2)
        {
            return SonicMania::Options->CompetitionSession.TotalRings_P2;
        }
        else if (PlayerID == 3)
        {
            return SonicMania::Options->CompetitionSession.TotalRings_P3;
        }
        else if (PlayerID == 4)
        {
            return SonicMania::Options->CompetitionSession.TotalRings_P4;
        }
        else return 0;
    }

    int GetPlayerScore(int PlayerID)
    {
        if (PlayerID == 1)
        {
            return SonicMania::Options->CompetitionSession.Score_P1;
        }
        else if (PlayerID == 2)
        {
            return SonicMania::Options->CompetitionSession.Score_P2;
        }
        else if (PlayerID == 3)
        {
            return SonicMania::Options->CompetitionSession.Score_P3;
        }
        else if (PlayerID == 4)
        {
            return SonicMania::Options->CompetitionSession.Score_P4;
        }
        else return 0;
    }

    int GetPlayerItems(int PlayerID)
    {
        if (PlayerID == 1)
        {
            return SonicMania::Options->CompetitionSession.Items_P1;
        }
        else if (PlayerID == 2)
        {
            return SonicMania::Options->CompetitionSession.Items_P2;
        }
        else if (PlayerID == 3)
        {
            return SonicMania::Options->CompetitionSession.Items_P3;
        }
        else if (PlayerID == 4)
        {
            return SonicMania::Options->CompetitionSession.Items_P4;
        }
        else return 0;
    }

    int GetNumberOfPlayers()
    {
        return SonicMania::Options->CompetitionSession.NumberOfPlayers;
    }

    #pragma endregion


    #pragma region Comparors/Helpers

    bool ScoreSorter(const ScorableInt& me, const ScorableInt& t)
    {
        return me.Value < t.Value;
    }

    bool AntiScoreSorter(const ScorableInt& me, const ScorableInt& t)
    {
        return me.Value > t.Value;
    }

    bool TimeSorter(const ScorableTime& A, const ScorableTime& B)
    {
        return A < B;
    }

    #pragma endregion

    #pragma region Get Methods

    ScorableTime GetPlayerTime(int PlayerID)
    {
        ScorableTime PlayerTime;
        PlayerTime.PlayerID = PlayerID;
        int NumberOfPlayers = GetNumberOfPlayers();
        if (PlayerID == 1 && NumberOfPlayers >= 1)
        {
            PlayerTime.Minutes = GetPlayerTime(PlayerID, 0);
            PlayerTime.Seconds = GetPlayerTime(PlayerID, 1);
            PlayerTime.Centiseconds = GetPlayerTime(PlayerID, 2);
            PlayerTime.PlayerID = PlayerID;
        }
        else if (PlayerID == 2 && NumberOfPlayers >= 2)
        {
            PlayerTime.Minutes = GetPlayerTime(PlayerID, 0);
            PlayerTime.Seconds = GetPlayerTime(PlayerID, 1);
            PlayerTime.Centiseconds = GetPlayerTime(PlayerID, 2);
            PlayerTime.PlayerID = PlayerID;
        }
        else if (PlayerID == 3 && NumberOfPlayers >= 3)
        {
            PlayerTime.Minutes = GetPlayerTime(PlayerID, 0);
            PlayerTime.Seconds = GetPlayerTime(PlayerID, 1);
            PlayerTime.Centiseconds = GetPlayerTime(PlayerID, 2);
            PlayerTime.PlayerID = PlayerID;
        }
        else if (PlayerID == 4 && NumberOfPlayers >= 4)
        {
            PlayerTime.Minutes = GetPlayerTime(PlayerID, 0);
            PlayerTime.Seconds = GetPlayerTime(PlayerID, 1);
            PlayerTime.Centiseconds = GetPlayerTime(PlayerID, 2);
            PlayerTime.PlayerID = PlayerID;
        }
        else
        {
            PlayerTime.Minutes = 99;
            PlayerTime.Seconds = 99;
            PlayerTime.Centiseconds = 99;
            PlayerTime.PlayerID = PlayerID;
        }
        return PlayerTime;
    }

     ScorableInt GetAntiRings(int PlayerID)
    {
        ScorableInt PlayerScore;
        PlayerScore.PlayerID = PlayerID;
        int NumberOfPlayers = SonicMania::Options->CompetitionSession.NumberOfPlayers;
        if (PlayerID == 1 && NumberOfPlayers >= 1)
        {
            PlayerScore.Value = GetPlayerTotalRings(PlayerID);
            PlayerScore.PlayerID = PlayerID;
        }
        else if (PlayerID == 2 && NumberOfPlayers >= 2)
        {
            PlayerScore.Value = GetPlayerTotalRings(PlayerID);
            PlayerScore.PlayerID = PlayerID;
        }
        else if (PlayerID == 3 && NumberOfPlayers >= 3)
        {
            PlayerScore.Value = GetPlayerTotalRings(PlayerID);
            PlayerScore.PlayerID = PlayerID;
        }
        else if (PlayerID == 4 && NumberOfPlayers >= 4)
        {
            PlayerScore.Value = GetPlayerTotalRings(PlayerID);
            PlayerScore.PlayerID = PlayerID;
        }
        else
        {
            PlayerScore.Value = 999;
            PlayerScore.PlayerID = PlayerID;
        }
        return PlayerScore;
    }

     std::vector<ScorableTime> GetTimeRanking()
    {
        ScorableTime Player1Time = GetPlayerTime(1);
        ScorableTime Player2Time = GetPlayerTime(2);
        ScorableTime Player3Time = GetPlayerTime(3);
        ScorableTime Player4Time = GetPlayerTime(4);

        std::vector<ScorableTime> PlayerTimes;
        int NumberOfPlayers = GetNumberOfPlayers();
        if (NumberOfPlayers == 1) PlayerTimes = { Player1Time };
        if (NumberOfPlayers == 2) PlayerTimes = { Player1Time, Player2Time };
        if (NumberOfPlayers == 3) PlayerTimes = { Player1Time, Player2Time, Player3Time };
        if (NumberOfPlayers == 4) PlayerTimes = { Player1Time, Player2Time, Player3Time, Player4Time };
        std::sort(PlayerTimes.begin(), PlayerTimes.end(), TimeSorter);

        int Position = 1;
        ScorableTime MinValue = ScorableTime(99, 99, 99);

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            PlayerTimes[i].Position = Position;
            if (PlayerTimes[i] < MinValue) MinValue = PlayerTimes[i];
            Position++;
        }

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            bool SameMin = PlayerTimes[i].Minutes == MinValue.Minutes;
            bool SameSec = PlayerTimes[i].Seconds == MinValue.Seconds;
            bool SameCenti = PlayerTimes[i].Centiseconds == MinValue.Centiseconds;
            if (SameMin && SameSec && SameCenti) PlayerTimes[i].HasWon = true;
        }

        return PlayerTimes;
    }

     std::vector<ScorableInt> GetTotalRingsRanking()
    {
         ScorableInt Player1Score = ScorableInt(GetPlayerTotalRings(1), 1);
         ScorableInt Player2Score = ScorableInt(GetPlayerTotalRings(2), 2);
         ScorableInt Player3Score = ScorableInt(GetPlayerTotalRings(3), 3);
         ScorableInt Player4Score = ScorableInt(GetPlayerTotalRings(4), 4);

        std::vector<ScorableInt> PlayerScores;
        int NumberOfPlayers = GetNumberOfPlayers();
        if (NumberOfPlayers == 1) PlayerScores = { Player1Score };
        if (NumberOfPlayers == 2) PlayerScores = { Player1Score, Player2Score };
        if (NumberOfPlayers == 3) PlayerScores = { Player1Score, Player2Score, Player3Score };
        if (NumberOfPlayers == 4) PlayerScores = { Player1Score, Player2Score, Player3Score, Player4Score };
        std::sort(PlayerScores.begin(), PlayerScores.end(), ScoreSorter);

        int Position = GetNumberOfPlayers();
        int MaxValue = 0;

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            PlayerScores[i].Position = Position;
            if (PlayerScores[i].Value > MaxValue) MaxValue = PlayerScores[i].Value;
            Position--;
        }

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            if (PlayerScores[i].Value == MaxValue) PlayerScores[i].HasWon = true;
        }

        return PlayerScores;
    }

     std::vector<ScorableInt> GetRingsRanking()
    {
        ScorableInt Player1Score = ScorableInt(GetPlayerRings(1), 1);
        ScorableInt Player2Score = ScorableInt(GetPlayerRings(2), 2);
        ScorableInt Player3Score = ScorableInt(GetPlayerRings(3), 3);
        ScorableInt Player4Score = ScorableInt(GetPlayerRings(4), 4);

        std::vector<ScorableInt> PlayerScores;
        int NumberOfPlayers = GetNumberOfPlayers();
        if (NumberOfPlayers == 1) PlayerScores = { Player1Score };
        if (NumberOfPlayers == 2) PlayerScores = { Player1Score, Player2Score };
        if (NumberOfPlayers == 3) PlayerScores = { Player1Score, Player2Score, Player3Score };
        if (NumberOfPlayers == 4) PlayerScores = { Player1Score, Player2Score, Player3Score, Player4Score };
        std::sort(PlayerScores.begin(), PlayerScores.end(), ScoreSorter);

        int Position = GetNumberOfPlayers();
        int MaxValue = 0;

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            PlayerScores[i].Position = Position;
            if (PlayerScores[i].Value > MaxValue) MaxValue = PlayerScores[i].Value;
            Position--;
        }

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            if (PlayerScores[i].Value == MaxValue) PlayerScores[i].HasWon = true;
        }

        return PlayerScores;
    }

     std::vector<ScorableInt> GetAntiRingsRanking()
    {
        ScorableInt Player1Score = GetAntiRings(1);
        ScorableInt Player2Score = GetAntiRings(2);
        ScorableInt Player3Score = GetAntiRings(3);
        ScorableInt Player4Score = GetAntiRings(4);

        std::vector<ScorableInt> PlayerScores;
        int NumberOfPlayers = GetNumberOfPlayers();
        if (NumberOfPlayers == 1) PlayerScores = { Player1Score };
        if (NumberOfPlayers == 2) PlayerScores = { Player1Score, Player2Score };
        if (NumberOfPlayers == 3) PlayerScores = { Player1Score, Player2Score, Player3Score };
        if (NumberOfPlayers == 4) PlayerScores = { Player1Score, Player2Score, Player3Score, Player4Score };
        std::sort(PlayerScores.begin(), PlayerScores.end(), AntiScoreSorter);

        int Position = GetNumberOfPlayers();
        int MaxValue = 0;

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            PlayerScores[i].Position = Position;
            if (PlayerScores[i].Value > MaxValue) MaxValue = PlayerScores[i].Value;
            Position--;
        }

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            if (PlayerScores[i].Value == MaxValue) PlayerScores[i].HasWon = true;
        }

        return PlayerScores;
    }

     std::vector<ScorableInt> GetScoreRanking()
    {
         ScorableInt Player1Score = ScorableInt(GetPlayerScore(1), 1);
         ScorableInt Player2Score = ScorableInt(GetPlayerScore(2), 2);
         ScorableInt Player3Score = ScorableInt(GetPlayerScore(3), 3);
         ScorableInt Player4Score = ScorableInt(GetPlayerScore(4), 4);

        std::vector<ScorableInt> PlayerScores;
        int NumberOfPlayers = GetNumberOfPlayers();
        if (NumberOfPlayers == 1) PlayerScores = { Player1Score };
        if (NumberOfPlayers == 2) PlayerScores = { Player1Score, Player2Score };
        if (NumberOfPlayers == 3) PlayerScores = { Player1Score, Player2Score, Player3Score };
        if (NumberOfPlayers == 4) PlayerScores = { Player1Score, Player2Score, Player3Score, Player4Score };
        std::sort(PlayerScores.begin(), PlayerScores.end(), ScoreSorter);

        int Position = GetNumberOfPlayers();
        int MaxValue = 0;

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            PlayerScores[i].Position = Position;
            if (PlayerScores[i].Value > MaxValue) MaxValue = PlayerScores[i].Value;
            Position--;
        }

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            if (PlayerScores[i].Value == MaxValue) PlayerScores[i].HasWon = true;
        }

        return PlayerScores;
    }

     std::vector<ScorableInt> GetItemRanking()
    {
         ScorableInt Player1Score = ScorableInt(GetPlayerItems(1), 1);
         ScorableInt Player2Score = ScorableInt(GetPlayerItems(2), 2);
         ScorableInt Player3Score = ScorableInt(GetPlayerItems(3), 3);
         ScorableInt Player4Score = ScorableInt(GetPlayerItems(4), 4);

        std::vector<ScorableInt> PlayerScores;
        int NumberOfPlayers = GetNumberOfPlayers();
        if (NumberOfPlayers == 1) PlayerScores = { Player1Score };
        if (NumberOfPlayers == 2) PlayerScores = { Player1Score, Player2Score };
        if (NumberOfPlayers == 3) PlayerScores = { Player1Score, Player2Score, Player3Score };
        if (NumberOfPlayers == 4) PlayerScores = { Player1Score, Player2Score, Player3Score, Player4Score };
        std::sort(PlayerScores.begin(), PlayerScores.end(), ScoreSorter);

        int Position = GetNumberOfPlayers();
        int MaxValue = 0;

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            PlayerScores[i].Position = Position;
            if (PlayerScores[i].Value > MaxValue) MaxValue = PlayerScores[i].Value;
            Position--;
        }

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            if (PlayerScores[i].Value == MaxValue) PlayerScores[i].HasWon = true;
        }

        return PlayerScores;
    }

     std::vector<ScorableInt> GetAverageRanking()
    {
        int P1_TotalScore = 0;
        int P2_TotalScore = 0;
        int P3_TotalScore = 0;
        int P4_TotalScore = 0;

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            int CurrentScore = 0;
            int PlayerID = i + 1;
            if (TimeRanking[i].PlayerID == PlayerID)
            {
                CurrentScore += TimeRanking[i].Position;
            }
            if (ScoreRanking[i].PlayerID == PlayerID)
            {
                CurrentScore += ScoreRanking[i].Position;
            }
            if (RingRanking[i].PlayerID == PlayerID)
            {
                CurrentScore += RingRanking[i].Position;
            }
            if (ItemRanking[i].PlayerID == PlayerID)
            {
                CurrentScore += ItemRanking[i].Position;
            }
            if (TotalRingRanking[i].PlayerID == PlayerID)
            {
                CurrentScore += TotalRingRanking[i].Position;
            }

            if (PlayerID == 1) P1_TotalScore = CurrentScore;
            else if (PlayerID == 2) P2_TotalScore = CurrentScore;
            else if (PlayerID == 3) P3_TotalScore = CurrentScore;
            else if (PlayerID == 4) P4_TotalScore = CurrentScore;
        }

        ScorableInt Player1Score = ScorableInt(P1_TotalScore, 1);
        ScorableInt Player2Score = ScorableInt(P2_TotalScore, 2);
        ScorableInt Player3Score = ScorableInt(P3_TotalScore, 3);
        ScorableInt Player4Score = ScorableInt(P4_TotalScore, 4);


        std::vector<ScorableInt> PlayerScores;
        int NumberOfPlayers = GetNumberOfPlayers();
        if (NumberOfPlayers == 1) PlayerScores = { Player1Score };
        if (NumberOfPlayers == 2) PlayerScores = { Player1Score, Player2Score };
        if (NumberOfPlayers == 3) PlayerScores = { Player1Score, Player2Score, Player3Score };
        if (NumberOfPlayers == 4) PlayerScores = { Player1Score, Player2Score, Player3Score, Player4Score };
        std::sort(PlayerScores.begin(), PlayerScores.end(), ScoreSorter);
        std::reverse(PlayerScores.begin(), PlayerScores.end());

        int Position = GetNumberOfPlayers();
        int MaxValue = 0;

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            PlayerScores[i].Position = Position;
            if (PlayerScores[i].Value > MaxValue) MaxValue = PlayerScores[i].Value;
            Position--;
        }

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            if (PlayerScores[i].Value == MaxValue) PlayerScores[i].HasWon = true;
        }

        return PlayerScores;
    }

    #pragma endregion

    #pragma region Set Methods

    void SetFinalRanking_Final(bool isTied, bool HasWinner, int CurrentRound, int WinnerID, int WinnerPlayerID)
    {


        if (isTied || !HasWinner) SonicMania::Options->CompetitionSession.WinnerFlag[CurrentRound] = 0;
        else 
        {
            if (WinnerPlayerID == 1) 
            {
                SonicMania::Options->CompetitionSession.Wins_P1 += 1;
                P1_WinsPlus += 1;
            }
            else if (WinnerPlayerID == 2)
            {
                SonicMania::Options->CompetitionSession.Wins_P2 += 1;
                P2_WinsPlus += 1;
            }
            else if (WinnerPlayerID == 3)
            {
                SonicMania::Options->CompetitionSession.Wins_P3 += 1;
                P3_WinsPlus += 1;
            }
            else if (WinnerPlayerID == 4)
            {
                SonicMania::Options->CompetitionSession.Wins_P4 += 1;
                P4_WinsPlus += 1;
            }
            SonicMania::Options->CompetitionSession.WinnerFlag[CurrentRound] = WinnerID;
        }

    }

    void SetFinalRanking_ForLoop(int CurrentPlayer, bool& HasWon, bool& isTied, int& WinnerID, int Position, bool& HasWinner, int& WinnerPlayerID)
    {
        int P1_Char = (SonicMania::Options->CompetitionSession.CharacterFlags >> 0x00 & 0xFF >> 1);
        int P2_Char = (SonicMania::Options->CompetitionSession.CharacterFlags >> 0x08 & 0xFF >> 1);
        int P3_Char = (SonicMania::Options->CompetitionSession.CharacterFlags >> 0x10 & 0xFF >> 1);
        int P4_Char = (SonicMania::Options->CompetitionSession.CharacterFlags >> 0x18 & 0xFF >> 1);

        if (CurrentPlayer == 1)
        {
            if (HasWon)
            {
                WinnerPlayerID = 1;
                WinnerID = P1_Char;
                if (HasWinner) isTied = true;
                else HasWinner = true;
            }
            P1_Placement = Position;
        }
        else if (CurrentPlayer == 2)
        {
            if (HasWon)
            {
                WinnerPlayerID = 2;
                WinnerID = P2_Char;
                if (HasWinner) isTied = true;
                else HasWinner = true;
            }
            P2_Placement = Position;
        }
        else if (CurrentPlayer == 3)
        {
            if (HasWon)
            {
                WinnerPlayerID = 3;
                WinnerID = P3_Char;
                if (HasWinner) isTied = true;
                else HasWinner = true;
            }
            P3_Placement = Position;
        }
        else if (CurrentPlayer == 4)
        {
            if (HasWon)
            {
                WinnerPlayerID = 4;
                WinnerID = P4_Char;
                if (HasWinner) isTied = true;
                else HasWinner = true;
            }
            P4_Placement = Position;
        }
    }

    void SetFinalRanking(std::vector<ScorableInt> PlayerRanks)
    {
        int CurrentRound = GetCurrentRound();
        bool isTied = false;
        bool HasWinner = false;
        int WinnerID = 0;
        int WinnerPlayerID = 0;

        for (int i = 0; i < PlayerRanks.size(); i++)
        {
            bool HasWon = PlayerRanks[i].HasWon;
            int CurrentPlayer = PlayerRanks[i].PlayerID;
            int Position = PlayerRanks[i].Position;

            SetFinalRanking_ForLoop(CurrentPlayer, HasWon, isTied, WinnerID, Position, HasWinner, WinnerPlayerID);
        }

        SetFinalRanking_Final(isTied, HasWinner, CurrentRound, WinnerID, WinnerPlayerID);
    }

    void SetFinalRanking(std::vector<ScorableTime> PlayerRanks)
    {
        int CurrentRound = GetCurrentRound();
        bool isTied = false;
        bool HasWinner = false;
        int WinnerID = 0;
        int WinnerPlayerID = 0;

        for (int i = 0; i < PlayerRanks.size(); i++)
        {
            bool HasWon = PlayerRanks[i].HasWon;
            int CurrentPlayer = PlayerRanks[i].PlayerID;
            int Position = PlayerRanks[i].Position;

            SetFinalRanking_ForLoop(CurrentPlayer, HasWon, isTied, WinnerID, Position, HasWinner, WinnerPlayerID);
        }

        SetFinalRanking_Final(isTied, HasWinner, CurrentRound, WinnerID, WinnerPlayerID);
    }

    void SetWinnerBasedOnSpecific(CompPlus_Settings::VictoryMode Setting)
    {
        switch (Setting)
        {
        case CompPlus_Settings::VictoryMode_Time:
            SetFinalRanking(TimeRanking);
            break;
        case CompPlus_Settings::VictoryMode_Score:
            SetFinalRanking(ScoreRanking);
            break;
        case CompPlus_Settings::VictoryMode_Rings:
            SetFinalRanking(RingRanking);
            break;
        case CompPlus_Settings::VictoryMode_TotalRings:
            SetFinalRanking(TotalRingRanking);
            break;
        case CompPlus_Settings::VictoryMode_Items:
            SetFinalRanking(ItemRanking);
            break;
        case CompPlus_Settings::VictoryMode_Default:
            SetFinalRanking(AverageRanking);
            break;
        case CompPlus_Settings::VictoryMode_AntiRings:
            SetFinalRanking(AntiRingRanking);
            break;
        }
    }

    void SetRoundEndWinner()
    {
        if (AllowUpdateVictory)
        {
            if (WinWait <= WinWaitMax)
            {
                TimeRanking = GetTimeRanking();
                RingRanking = GetRingsRanking();
                TotalRingRanking = GetTotalRingsRanking();
                ScoreRanking = GetScoreRanking();
                ItemRanking = GetItemRanking();
                AverageRanking = GetAverageRanking();
                AntiRingRanking = GetAntiRingsRanking();

                SetWinnerBasedOnSpecific(CompPlus_Settings::VictoryStyle);

                WinWait = 0;
                AllowUpdateVictory = false;
            }
            else
            {
                WinWait += 1;
            }

        }

    }

    #pragma endregion

    #pragma region Match/Round Reset Methods

    void SyncLastResults()
    {
        LastSession = SonicMania::Options->CompetitionSession;
        P1_LastPlacement = 0;
        P2_LastPlacement = 0;
        P3_LastPlacement = 0;
        P4_LastPlacement = 0;
        P1_LastPlacement = P1_Placement;
        P2_LastPlacement = P2_Placement;
        P3_LastPlacement = P3_Placement;
        P4_LastPlacement = P4_Placement;
        P1_Placement = 0;
        P2_Placement = 0;
        P3_Placement = 0;
        P4_Placement = 0;
    }

    void ClearMatchResults()
    {
        LastSession = SonicMania::CompetitionSession();
        P1_LastPlacement = 0;
        P2_LastPlacement = 0;
        P3_LastPlacement = 0;
        P4_LastPlacement = 0;
        P1_Placement = 0;
        P2_Placement = 0;
        P3_Placement = 0;
        P4_Placement = 0;
        P1_WinsPlus = 0;
        P2_WinsPlus = 0;
        P3_WinsPlus = 0;
        P4_WinsPlus = 0;
        P1_HasWon = false;
        P2_HasWon = false;
        P3_HasWon = false;
        P4_HasWon = false;
        CanGoToFinalResults = false;
        SonicMania::Options->CompetitionSession.Wins_P1 = 0;
        SonicMania::Options->CompetitionSession.Wins_P2 = 0;
        SonicMania::Options->CompetitionSession.Wins_P3 = 0;
        SonicMania::Options->CompetitionSession.Wins_P4 = 0;
        LastZone = "???";
    }

    void ClearInternalWins()
    {
        if (!CanGoToFinalResults)
        {
            SonicMania::Options->CompetitionSession.Wins_P1 = 0;
            SonicMania::Options->CompetitionSession.Wins_P2 = 0;
            SonicMania::Options->CompetitionSession.Wins_P3 = 0;
            SonicMania::Options->CompetitionSession.Wins_P4 = 0;
            LastZone = "???";
        }
    }

    #pragma endregion

    #pragma region Update Match/Round Methods

    void UpdateMatchLength()
    {
        if (SonicMania::CurrentScene == 2) 
        {
            int MaxRounds = CompPlus_Settings::NumberOfRounds;

            // At beginning of match
            int WinThreshold = (MaxRounds / 2) + 1;

            if (GetCurrentRound() == MaxRounds)
            {
                // Player with most wins is overall winner (could be a tie)
                int MaxWins = 0;

                if (P1_WinsPlus > MaxWins) MaxWins = P1_WinsPlus;
                if (P2_WinsPlus > MaxWins) MaxWins = P2_WinsPlus;
                if (P3_WinsPlus > MaxWins) MaxWins = P3_WinsPlus;
                if (P4_WinsPlus > MaxWins) MaxWins = P4_WinsPlus;

                if (MaxWins == P1_WinsPlus) P1_HasWon = true;
                if (MaxWins == P2_WinsPlus) P2_HasWon = true;
                if (MaxWins == P3_WinsPlus) P3_HasWon = true;
                if (MaxWins == P4_WinsPlus) P4_HasWon = true;
                CanGoToFinalResults = true;
            }
            else
            {
                int MaxWins = 0;

                if (P1_WinsPlus > MaxWins) MaxWins = P1_WinsPlus;
                if (P2_WinsPlus > MaxWins) MaxWins = P2_WinsPlus;
                if (P3_WinsPlus > MaxWins) MaxWins = P3_WinsPlus;
                if (P4_WinsPlus > MaxWins) MaxWins = P4_WinsPlus;

                // Player at or over WinThreshold is overall winner (could be a tie)
                if (MaxWins >= WinThreshold)
                {
                    if (MaxWins == P1_WinsPlus) P1_HasWon = true;
                    if (MaxWins == P2_WinsPlus) P2_HasWon = true;
                    if (MaxWins == P3_WinsPlus) P3_HasWon = true;
                    if (MaxWins == P4_WinsPlus) P4_HasWon = true;
                    CanGoToFinalResults = true;
                }
                else
                {
                    //No Clear Winner Yet
                }
            }
        }
    }

    bool RoundStatsSaved = false;

    void SaveRoundsStats() 
    {
        if (!RoundStatsSaved) 
        {
            LastCurrentRound = GetCurrentRound();
            RoundStatsSaved = true;
        }
    }

    void UpdateRounds()
    {
        if (!CompPlus_Scoring::CanGoToFinalResults)
        {
            SaveRoundsStats();
            if (SonicMania::Options->CompetitionSession.TotalRounds != CompPlus_Settings::NumberOfRounds) SonicMania::Options->CompetitionSession.TotalRounds = CompPlus_Settings::NumberOfRounds;
            if (CompPlus_Settings::EndlessRounds && GetCurrentRound() != 0) SetCurrentRound(0);
            RoundStatsSaved = false;
        }
        else
        {
            SaveRoundsStats();
            SetCurrentRound(2);
            SonicMania::Options->CompetitionSession.TotalRounds = 2;
            SonicMania::Options->CompetitionSession.Wins_P1 = (CompPlus_Scoring::P1_HasWon ? 2 : 0);
            SonicMania::Options->CompetitionSession.Wins_P2 = (CompPlus_Scoring::P2_HasWon ? 2 : 0);
            SonicMania::Options->CompetitionSession.Wins_P3 = (CompPlus_Scoring::P3_HasWon ? 2 : 0);
            SonicMania::Options->CompetitionSession.Wins_P4 = (CompPlus_Scoring::P4_HasWon ? 2 : 0);
        }



        if (SonicMania::Options->CompetitionSession.inMatch == false)
        {
            ClearMatchResults();
        }
    }

    void UpdatePlayerResults()
    {
        int TotalPlayers = SonicMania::Options->CompetitionSession.NumberOfPlayers;
        int FinishFlags = SonicMania::Options->CompetitionSession.FinishFlags;
        int P1_FinishFlag = TotalPlayers >= 1 ? (FinishFlags >> 0x00 & 0xFF) : 0;
        int P2_FinishFlag = TotalPlayers >= 2 ? (FinishFlags >> 0x08 & 0xFF) : 0;
        int P3_FinishFlag = TotalPlayers >= 3 ? (FinishFlags >> 0x10 & 0xFF) : 0;
        int P4_FinishFlag = TotalPlayers >= 4 ? (FinishFlags >> 0x18 & 0xFF) : 0;

        bool P1_Finished = TotalPlayers >= 1 ? P1_FinishFlag != 0 : true;
        bool P2_Finished = TotalPlayers >= 2 ? P2_FinishFlag != 0 : true;
        bool P3_Finished = TotalPlayers >= 3 ? P3_FinishFlag != 0 : true;
        bool P4_Finished = TotalPlayers >= 4 ? P4_FinishFlag != 0 : true;

        if (P1_Finished && P2_Finished && P3_Finished && P4_Finished && SonicMania::Timer.Enabled) SetRoundEndWinner();
        else AllowUpdateVictory = true;
    }

    #pragma endregion

    void OnFrame()
    {
        UpdatePlayerResults();
        UpdateRounds();
        UpdateMatchLength();
    }
}
