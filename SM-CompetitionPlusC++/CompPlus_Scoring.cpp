#include "stdafx.h"
#include "IZAPI.h"
#include "SonicMania.h"
#include "ManiaExt.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "CompPlus_Scoring.h"
#include "CompPlusSettings.h"


namespace CompPlus_Scoring
{
     SonicMania::CompetitionSession LastSession;

     bool AllowUpdateVictory = false;

     int WinWait = 0;
     int WinWaitMax = 100;

     int CurrentRound_Plus = 0;
     int LastRound_NoPlus = 0;

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

     bool ThisMatchIsTied = false;
     bool CanGoToFinalResults = false;

    std::vector<ScorableTime> TimeRanking;
    std::vector<ScorableInt> TotalRingRanking;
    std::vector<ScorableInt> ScoreRanking;
    std::vector<ScorableInt> RingRanking;
    std::vector<ScorableInt> ItemRanking;
    std::vector<ScorableInt> AverageRanking;

    #pragma region Comparors/Helpers

        int GetNumberOfPlayers() 
        {
            return SonicMania::Options->CompetitionSession.NumberOfPlayers;
        }

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
        int NumberOfPlayers = SonicMania::Options->CompetitionSession.NumberOfPlayers;
        if (PlayerID == 1 && NumberOfPlayers >= 1)
        {
            PlayerTime.Minutes = SonicMania::Options->CompetitionSession.TimeMinutes_P1;
            PlayerTime.Seconds = SonicMania::Options->CompetitionSession.TimeSeconds_P1;
            PlayerTime.Centiseconds = SonicMania::Options->CompetitionSession.TimeCentiseconds_P1;
            PlayerTime.PlayerID = PlayerID;
        }
        else if (PlayerID == 2 && NumberOfPlayers >= 2)
        {
            PlayerTime.Minutes = SonicMania::Options->CompetitionSession.TimeMinutes_P2;
            PlayerTime.Seconds = SonicMania::Options->CompetitionSession.TimeSeconds_P2;
            PlayerTime.Centiseconds = SonicMania::Options->CompetitionSession.TimeCentiseconds_P2;
            PlayerTime.PlayerID = PlayerID;
        }
        else if (PlayerID == 3 && NumberOfPlayers >= 3)
        {
            PlayerTime.Minutes = SonicMania::Options->CompetitionSession.TimeMinutes_P3;
            PlayerTime.Seconds = SonicMania::Options->CompetitionSession.TimeSeconds_P3;
            PlayerTime.Centiseconds = SonicMania::Options->CompetitionSession.TimeCentiseconds_P3;
            PlayerTime.PlayerID = PlayerID;
        }
        else if (PlayerID == 4 && NumberOfPlayers >= 4)
        {
            PlayerTime.Minutes = SonicMania::Options->CompetitionSession.TimeMinutes_P4;
            PlayerTime.Seconds = SonicMania::Options->CompetitionSession.TimeSeconds_P4;
            PlayerTime.Centiseconds = SonicMania::Options->CompetitionSession.TimeCentiseconds_P4;
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
            PlayerScore.Value = SonicMania::Options->CompetitionSession.TotalRings_P1;
            PlayerScore.PlayerID = PlayerID;
        }
        else if (PlayerID == 2 && NumberOfPlayers >= 2)
        {
            PlayerScore.Value = SonicMania::Options->CompetitionSession.TotalRings_P2;
            PlayerScore.PlayerID = PlayerID;
        }
        else if (PlayerID == 3 && NumberOfPlayers >= 3)
        {
            PlayerScore.Value = SonicMania::Options->CompetitionSession.TotalRings_P3;
            PlayerScore.PlayerID = PlayerID;
        }
        else if (PlayerID == 4 && NumberOfPlayers >= 4)
        {
            PlayerScore.Value = SonicMania::Options->CompetitionSession.TotalRings_P4;
            PlayerScore.PlayerID = PlayerID;
        }
        else
        {
            PlayerScore.Value = 999;
            PlayerScore.PlayerID = PlayerID;
        }
        return PlayerScore;
    }

     std::vector<ScorableTime> GetPositionData(std::vector<ScorableTime> PlayerTimes)
    {
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

     std::vector<ScorableInt> GetPositionData(std::vector<ScorableInt>  PlayerScores)
    {
        int Position = 1;
        int MaxValue = 0;

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            PlayerScores[i].Position = Position;
            if (PlayerScores[i].Value > MaxValue) MaxValue = PlayerScores[i].Value;
            Position++;
        }

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            if (PlayerScores[i].Value == MaxValue) PlayerScores[i].HasWon = true;
        }
        return PlayerScores;
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
        std::sort(PlayerTimes.begin(), PlayerTimes.end());

        PlayerTimes = GetPositionData(PlayerTimes);
        return PlayerTimes;
    }

     std::vector<ScorableInt> GetTotalRingsRanking()
    {
        ScorableInt Player1Score = ScorableInt(SonicMania::Options->CompetitionSession.TotalRings_P1, 1);
        ScorableInt Player2Score = ScorableInt(SonicMania::Options->CompetitionSession.TotalRings_P2, 2);
        ScorableInt Player3Score = ScorableInt(SonicMania::Options->CompetitionSession.TotalRings_P3, 3);
        ScorableInt Player4Score = ScorableInt(SonicMania::Options->CompetitionSession.TotalRings_P4, 4);

        std::vector<ScorableInt> PlayerScores;
        int NumberOfPlayers = GetNumberOfPlayers();
        if (NumberOfPlayers == 1) PlayerScores = { Player1Score };
        if (NumberOfPlayers == 2) PlayerScores = { Player1Score, Player2Score };
        if (NumberOfPlayers == 3) PlayerScores = { Player1Score, Player2Score, Player3Score };
        if (NumberOfPlayers == 4) PlayerScores = { Player1Score, Player2Score, Player3Score, Player4Score };
        std::sort(PlayerScores.begin(), PlayerScores.end(), ScoreSorter);

        PlayerScores = GetPositionData(PlayerScores);
        return PlayerScores;
    }

     std::vector<ScorableInt> GetRingsRanking()
    {
        ScorableInt Player1Score = ScorableInt(SonicMania::Options->CompetitionSession.Rings_P1, 1);
        ScorableInt Player2Score = ScorableInt(SonicMania::Options->CompetitionSession.Rings_P2, 2);
        ScorableInt Player3Score = ScorableInt(SonicMania::Options->CompetitionSession.Rings_P3, 3);
        ScorableInt Player4Score = ScorableInt(SonicMania::Options->CompetitionSession.Rings_P4, 4);

        std::vector<ScorableInt> PlayerScores;
        int NumberOfPlayers = GetNumberOfPlayers();
        if (NumberOfPlayers == 1) PlayerScores = { Player1Score };
        if (NumberOfPlayers == 2) PlayerScores = { Player1Score, Player2Score };
        if (NumberOfPlayers == 3) PlayerScores = { Player1Score, Player2Score, Player3Score };
        if (NumberOfPlayers == 4) PlayerScores = { Player1Score, Player2Score, Player3Score, Player4Score };
        std::sort(PlayerScores.begin(), PlayerScores.end(), ScoreSorter);

        PlayerScores = GetPositionData(PlayerScores);
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

        PlayerScores = GetPositionData(PlayerScores);
        return PlayerScores;
    }

     std::vector<ScorableInt> GetScoreRanking()
    {
        ScorableInt Player1Score = ScorableInt(SonicMania::Options->CompetitionSession.Score_P1, 1);
        ScorableInt Player2Score = ScorableInt(SonicMania::Options->CompetitionSession.Score_P2, 2);
        ScorableInt Player3Score = ScorableInt(SonicMania::Options->CompetitionSession.Score_P3, 3);
        ScorableInt Player4Score = ScorableInt(SonicMania::Options->CompetitionSession.Score_P4, 4);

        std::vector<ScorableInt> PlayerScores;
        int NumberOfPlayers = GetNumberOfPlayers();
        if (NumberOfPlayers == 1) PlayerScores = { Player1Score };
        if (NumberOfPlayers == 2) PlayerScores = { Player1Score, Player2Score };
        if (NumberOfPlayers == 3) PlayerScores = { Player1Score, Player2Score, Player3Score };
        if (NumberOfPlayers == 4) PlayerScores = { Player1Score, Player2Score, Player3Score, Player4Score };
        std::sort(PlayerScores.begin(), PlayerScores.end(), ScoreSorter);

        PlayerScores = GetPositionData(PlayerScores);
        return PlayerScores;
    }

     std::vector<ScorableInt> GetItemRanking()
    {
        ScorableInt Player1Score = ScorableInt(SonicMania::Options->CompetitionSession.Items_P1, 1);
        ScorableInt Player2Score = ScorableInt(SonicMania::Options->CompetitionSession.Items_P2, 2);
        ScorableInt Player3Score = ScorableInt(SonicMania::Options->CompetitionSession.Items_P3, 3);
        ScorableInt Player4Score = ScorableInt(SonicMania::Options->CompetitionSession.Items_P4, 4);

        std::vector<ScorableInt> PlayerScores;
        int NumberOfPlayers = GetNumberOfPlayers();
        if (NumberOfPlayers == 1) PlayerScores = { Player1Score };
        if (NumberOfPlayers == 2) PlayerScores = { Player1Score, Player2Score };
        if (NumberOfPlayers == 3) PlayerScores = { Player1Score, Player2Score, Player3Score };
        if (NumberOfPlayers == 4) PlayerScores = { Player1Score, Player2Score, Player3Score, Player4Score };
        std::sort(PlayerScores.begin(), PlayerScores.end(), ScoreSorter);

        PlayerScores = GetPositionData(PlayerScores);
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

        PlayerScores = GetPositionData(PlayerScores);
        return PlayerScores;
    }

    #pragma endregion

    #pragma region Set Methods

    void SetFinalRanking_Final(bool isTied, bool HasWinner, int CurrentRound, int WinnerID)
    {
        if (isTied || !HasWinner) SonicMania::Options->CompetitionSession.WinnerFlag[CurrentRound] = 0;
        else SonicMania::Options->CompetitionSession.WinnerFlag[CurrentRound] = WinnerID;

        if (isTied && HasWinner) ThisMatchIsTied = true;
    }

    void SetFinalRanking_ForLoop(int CurrentPlayer, bool& HasWon, bool& isTied, int& WinnerID, int Position, bool& HasWinner)
    {
        if (CurrentPlayer == 1)
        {
            if (HasWon)
            {
                WinnerID = 1;
                SonicMania::Options->CompetitionSession.Wins_P1 += 1;
                P1_WinsPlus += 1;

                if (HasWinner) isTied = true;
                else HasWinner = true;
            }
            P1_Placement = Position;
        }
        else if (CurrentPlayer == 2)
        {
            if (HasWon)
            {
                WinnerID = 2;
                SonicMania::Options->CompetitionSession.Wins_P2 += 1;
                P2_WinsPlus += 1;

                if (HasWinner) isTied = true;
                else HasWinner = true;
            }
            P2_Placement = Position;
        }
        else if (CurrentPlayer == 3)
        {
            if (HasWon)
            {
                WinnerID = 3;
                SonicMania::Options->CompetitionSession.Wins_P3 += 1;
                P3_WinsPlus += 1;

                if (HasWinner) isTied = true;
                else HasWinner = true;
            }
            P3_Placement = Position;
        }
        else if (CurrentPlayer == 4)
        {
            if (HasWon)
            {
                WinnerID = 4;
                SonicMania::Options->CompetitionSession.Wins_P4 += 1;
                P4_WinsPlus += 1;

                if (HasWinner) isTied = true;
                else HasWinner = true;
            }
            P4_Placement = Position;
        }
    }

    void SetFinalRanking(std::vector<ScorableInt> PlayerRanks)
    {
        int CurrentRound = SonicMania::Options->CompetitionSession.CurrentRound;
        bool isTied = false;
        bool HasWinner = false;
        int WinnerID = 0;

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            bool HasWon = PlayerRanks[i].HasWon;
            int CurrentPlayer = PlayerRanks[i].PlayerID;
            int Position = PlayerRanks[i].Position;

            SetFinalRanking_ForLoop(CurrentPlayer, HasWon, isTied, WinnerID, Position, HasWinner);
        }

        SetFinalRanking_Final(isTied, HasWinner, CurrentRound, WinnerID);
    }

    void SetFinalRanking(std::vector<ScorableTime> PlayerRanks)
    {
        int CurrentRound = SonicMania::Options->CompetitionSession.CurrentRound;
        bool isTied = false;
        bool HasWinner = false;
        int WinnerID = 0;

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            bool HasWon = PlayerRanks[i].HasWon;
            int CurrentPlayer = PlayerRanks[i].PlayerID;
            int Position = PlayerRanks[i].Position;

            SetFinalRanking_ForLoop(CurrentPlayer, HasWon, isTied, WinnerID, Position, HasWinner);
        }

        SetFinalRanking_Final(isTied, HasWinner, CurrentRound, WinnerID);
    }

    void SetWinnerBasedOnSpecific(CompPlusSettings::VictoryMode Setting)
    {
        switch (Setting)
        {
        case CompPlusSettings::VictoryMode_Time:
            SetFinalRanking(TimeRanking);
            break;
        case CompPlusSettings::VictoryMode_Score:
            SetFinalRanking(ScoreRanking);
            break;
        case CompPlusSettings::VictoryMode_Rings:
            SetFinalRanking(RingRanking);
            break;
        case CompPlusSettings::VictoryMode_TotalRings:
            SetFinalRanking(TotalRingRanking);
            break;
        case CompPlusSettings::VictoryMode_Items:
            SetFinalRanking(ItemRanking);
            break;
        case CompPlusSettings::VictoryMode_Default:
            SetFinalRanking(AverageRanking);
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

                SetWinnerBasedOnSpecific(CompPlusSettings::VictoryStyle);

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
    }

    void ClearInternalWins()
    {
        if (!CanGoToFinalResults)
        {
            SonicMania::Options->CompetitionSession.Wins_P1 = 0;
            SonicMania::Options->CompetitionSession.Wins_P2 = 0;
            SonicMania::Options->CompetitionSession.Wins_P3 = 0;
            SonicMania::Options->CompetitionSession.Wins_P4 = 0;
        }
    }

    #pragma endregion

    #pragma region Update Match/Round Methods

    void UpdateMatchLength()
    {
        int MaxRounds = CompPlusSettings::NumberOfRounds;

        // At beginning of match
        int WinThreshold = (MaxRounds / 2) + 1;

        if (CurrentRound_Plus == MaxRounds)
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

    void UpdateRounds()
    {
        if (!CompPlus_Scoring::CanGoToFinalResults)
        {
            if (SonicMania::Options->CompetitionSession.TotalRounds != CompPlusSettings::NumberOfRounds) SonicMania::Options->CompetitionSession.TotalRounds = CompPlusSettings::NumberOfRounds;
            if (CompPlusSettings::EndlessRounds && SonicMania::Options->CompetitionSession.CurrentRound != 0) SonicMania::Options->CompetitionSession.CurrentRound = 0;
        }
        else
        {
            SonicMania::Options->CompetitionSession.CurrentRound = 2;
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
        int P1_FinishFlag = SonicMania::Player1.Active && TotalPlayers >= 1 ? (FinishFlags >> 0x00 & 0xFF) : 0;
        int P2_FinishFlag = SonicMania::Player2.Active && TotalPlayers >= 2 ? (FinishFlags >> 0x08 & 0xFF) : 0;
        int P3_FinishFlag = SonicMania::Player3.Active && TotalPlayers >= 3 ? (FinishFlags >> 0x10 & 0xFF) : 0;
        int P4_FinishFlag = SonicMania::Player4.Active && TotalPlayers >= 4 ? (FinishFlags >> 0x18 & 0xFF) : 0;

        bool P1_Finished = SonicMania::Player1.Active && TotalPlayers >= 1 ? P1_FinishFlag != 0 : true;
        bool P2_Finished = SonicMania::Player2.Active && TotalPlayers >= 2 ? P2_FinishFlag != 0 : true;
        bool P3_Finished = SonicMania::Player3.Active && TotalPlayers >= 3 ? P3_FinishFlag != 0 : true;
        bool P4_Finished = SonicMania::Player4.Active && TotalPlayers >= 4 ? P4_FinishFlag != 0 : true;

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
