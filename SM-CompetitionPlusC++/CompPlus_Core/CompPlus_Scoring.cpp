#include "stdafx.h"
#include "CompPlus_Extensions/IZAPI.h"
#include "SonicMania.h"
#include "CompPlus_Extensions/ManiaExt.h"
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

     std::string LastZone = "???";

     int WinWait = 0;
     int WinWaitMax = 100;

     bool RoundStatsSaved = false;

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

     bool P1_HasWon_Round = false;
     bool P2_HasWon_Round = false;
     bool P3_HasWon_Round = false;
     bool P4_HasWon_Round = false;

     bool P1_HasWon_Match = false;
     bool P2_HasWon_Match = false;
     bool P3_HasWon_Match = false;
     bool P4_HasWon_Match = false;

     int LastCurrentRound = 0;
     int PlusCurrentRound = 0;

     bool PodeiumSpawnActive = false;
     bool ThisMatchIsTied = false;
     bool CanGoToFinalResults = false;

     DataPointer(int, InitalCountdown, 0x6A7074);

     DataPointer(int, HaveAllCrossedTheFinishLine, 0x46C160);
     DataPointer(int, HasSomeoneCrossed, 0x33C890);

     std::vector<ScorableTime> TimeRanking;
     std::vector<ScorableInt> TotalRingRanking;
     std::vector<ScorableInt> ScoreRanking;
     std::vector<ScorableInt> RingRanking;
     std::vector<ScorableInt> ItemRanking;
     std::vector<ScorableInt> AverageRanking;
     std::vector<ScorableInt> AntiRingRanking;

    #pragma region Check/Get/Set Methods

    void SetCurrentRound(int value) 
    {
        SonicMania::Options->CompetitionSession.CurrentRound = value;
    }

    int GetCurrentRound() 
    {
        return SonicMania::Options->CompetitionSession.CurrentRound;
    }

    int GetPlusCurrentRound() 
    {
        return PlusCurrentRound;
    }

    void SetPlusCurrentRound(int value)
    {
        PlusCurrentRound = value;
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

    bool HasTimePeaked(int PlayerID)
    {
        if (PlayerID == 1)
        {
            return (SonicMania::Options->CompetitionSession.TimeMinutes_P1 == 9 && SonicMania::Options->CompetitionSession.TimeSeconds_P1 == 59 && SonicMania::Options->CompetitionSession.TimeCentiseconds_P1 == 99);
        }
        else if (PlayerID == 2)
        {
            return (SonicMania::Options->CompetitionSession.TimeMinutes_P2 == 9 && SonicMania::Options->CompetitionSession.TimeSeconds_P2 == 59 && SonicMania::Options->CompetitionSession.TimeCentiseconds_P2 == 99);
        }
        else if (PlayerID == 3)
        {
            return (SonicMania::Options->CompetitionSession.TimeMinutes_P3 == 9 && SonicMania::Options->CompetitionSession.TimeSeconds_P3 == 59 && SonicMania::Options->CompetitionSession.TimeCentiseconds_P3 == 99);
        }
        else if (PlayerID == 4)
        {
            return (SonicMania::Options->CompetitionSession.TimeMinutes_P4 == 9 && SonicMania::Options->CompetitionSession.TimeSeconds_P4 == 59 && SonicMania::Options->CompetitionSession.TimeCentiseconds_P4 == 99);
        }
        else
        {
            return (SonicMania::Options->CompetitionSession.TimeMinutes_P1 == 9 && SonicMania::Options->CompetitionSession.TimeSeconds_P1 == 59 && SonicMania::Options->CompetitionSession.TimeCentiseconds_P1 == 99);
        }
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
            PlayerScore.Value = INT_MAX;
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
        std::sort(PlayerScores.begin(), PlayerScores.end(), AntiScoreSorter);

        int Position = GetNumberOfPlayers();
        int MinValue = 0;

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            PlayerScores[i].Position = Position;
            if (PlayerScores[i].Value < MinValue) MinValue = PlayerScores[i].Value;
            Position--;
        }

        for (int i = 0; i < GetNumberOfPlayers(); i++)
        {
            if (PlayerScores[i].Value == MinValue) PlayerScores[i].HasWon = true;
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

    int ConvertPositionToAverage(int Position)
    {
        if (Position == 1) return 4;
        else if (Position == 2) return 3;
        else if (Position == 3) return 2;
        else if (Position == 4) return 1;
        else return 0;
    }

    int ConvertWinToAverage(bool hasWon)
    {
        if (hasWon) return 1;
        else return 0;
    }

    int GetPlayerAverage(int PlayerID)
    {
        int CurrentScore = 0;

        for (int j = 0; j < GetNumberOfPlayers(); j++)
        {
            if (TimeRanking[j].PlayerID == PlayerID)
            {
                CurrentScore += ConvertWinToAverage(TimeRanking[j].HasWon);
            }
            if (ScoreRanking[j].PlayerID == PlayerID)
            {
                CurrentScore += ConvertWinToAverage(ScoreRanking[j].HasWon);
            }
            if (RingRanking[j].PlayerID == PlayerID)
            {
                CurrentScore += ConvertWinToAverage(RingRanking[j].HasWon);
            }
            if (ItemRanking[j].PlayerID == PlayerID)
            {
                CurrentScore += ConvertWinToAverage(ItemRanking[j].HasWon);
            }
            if (TotalRingRanking[j].PlayerID == PlayerID)
            {
                CurrentScore += ConvertWinToAverage(TotalRingRanking[j].HasWon);
            }
        }
        return CurrentScore;
    }

    std::vector<ScorableInt> GetAverageRanking()
    {
        int NumberOfPlayers = GetNumberOfPlayers();

        int P1_TotalScore = 0;
        int P2_TotalScore = 0;
        int P3_TotalScore = 0;
        int P4_TotalScore = 0;

        if (NumberOfPlayers >= 1) P1_TotalScore = GetPlayerAverage(1);
        if (NumberOfPlayers >= 2) P2_TotalScore = GetPlayerAverage(2);
        if (NumberOfPlayers >= 3) P3_TotalScore = GetPlayerAverage(3);
        if (NumberOfPlayers >= 4) P4_TotalScore = GetPlayerAverage(4);

        ScorableInt Player1Score = ScorableInt(P1_TotalScore, 1);
        ScorableInt Player2Score = ScorableInt(P2_TotalScore, 2);
        ScorableInt Player3Score = ScorableInt(P3_TotalScore, 3);
        ScorableInt Player4Score = ScorableInt(P4_TotalScore, 4);


        std::vector<ScorableInt> PlayerScores;

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
        //Flags
        //00 - No Winner
        //01 - P1 Wins
        //02 - P2 Wins
        //03 - P1/P2 Tie
        //04 - P3 Wins
        //05 - P1/P3 Tie
        //06 - P2/P3 Tie
        //07 - P1-P3 Tie
        //08 - P4 Wins
        //09 - P1/P4 Tie
        //10 - P2/P4 Tie
        //11 - P3/P4 Tie
        //12 - P1/P2/P4 Tie
        //13 - P1/P3/P4 Tie
        //14 - P1-P4 Tie (All Tie)

        BYTE P1_Char = SonicMania::Options->CompetitionSession.CharacterFlags[0];
        BYTE P2_Char = SonicMania::Options->CompetitionSession.CharacterFlags[1];
        BYTE P3_Char = SonicMania::Options->CompetitionSession.CharacterFlags[2];
        BYTE P4_Char = SonicMania::Options->CompetitionSession.CharacterFlags[3];

        if (CurrentPlayer == 1)
        {
            P1_HasWon_Round = HasWon;
            if (HasWon)
            {
                WinnerPlayerID = 1;
                WinnerID = 1;
                if (HasWinner) isTied = true;
                else HasWinner = true;
            }
            P1_Placement = Position;
        }
        else if (CurrentPlayer == 2)
        {
            P2_HasWon_Round = HasWon;
            if (HasWon)
            {
                WinnerPlayerID = 2;
                WinnerID = 2;
                if (HasWinner) isTied = true;
                else HasWinner = true;
            }
            P2_Placement = Position;
        }
        else if (CurrentPlayer == 3)
        {
            P3_HasWon_Round = HasWon;
            if (HasWon)
            {
                WinnerPlayerID = 3;
                WinnerID = 4;
                if (HasWinner) isTied = true;
                else HasWinner = true;
            }
            P3_Placement = Position;
        }
        else if (CurrentPlayer == 4)
        {
            P4_HasWon_Round = HasWon;
            if (HasWon)
            {
                WinnerPlayerID = 4;
                WinnerID = 8;
                if (HasWinner) isTied = true;
                else HasWinner = true;
            }
            P4_Placement = Position;
        }
        
    }

    void SetFinalRanking(std::vector<ScorableInt> PlayerRanks)
    {
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

        SetFinalRanking_Final(isTied, HasWinner, 0, WinnerID, WinnerPlayerID);
    }

    void SetFinalRanking(std::vector<ScorableTime> PlayerRanks)
    {
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

        SetFinalRanking_Final(isTied, HasWinner, 0, WinnerID, WinnerPlayerID);
    }

    void SetRoundEndWinner()
    {
        if (SonicMania::Options->CompetitionSession.inMatch == 1)
        {
            TimeRanking = GetTimeRanking();
            RingRanking = GetRingsRanking();
            TotalRingRanking = GetTotalRingsRanking();
            ScoreRanking = GetScoreRanking();
            ItemRanking = GetItemRanking();
            AverageRanking = GetAverageRanking();
            AntiRingRanking = GetAntiRingsRanking();

            switch (CompPlus_Settings::VictoryStyle)
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
    }

    #pragma endregion

    #pragma region Match/Round Reset Methods

    void ApplyPoyoPoyoRuleset()
    {
        if (SonicMania::Options->CompetitionSession.inMatch)
        {
            if (SonicMania::Options->CompetitionSession.CurrentRound == SonicMania::Options->CompetitionSession.TotalRounds)
            {
                CanGoToFinalResults = false;
            }
        }
    }

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
        PodeiumSpawnActive = true;
    }

    void ClearMatchResults()
    {
        LastSession = SonicMania::CompetitionSession();
        PlusCurrentRound = 0;
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
        P1_HasWon_Match = false;
        P2_HasWon_Match = false;
        P3_HasWon_Match = false;
        P4_HasWon_Match = false;
        P1_HasWon_Round = false;
        P2_HasWon_Round = false;
        P3_HasWon_Round = false;
        P4_HasWon_Round = false;
        CanGoToFinalResults = false;
        SonicMania::Options->CompetitionSession.Wins_P1 = 0;
        SonicMania::Options->CompetitionSession.Wins_P2 = 0;
        SonicMania::Options->CompetitionSession.Wins_P3 = 0;
        SonicMania::Options->CompetitionSession.Wins_P4 = 0;
        LastZone = "???";
        PodeiumSpawnActive = false;
        AllowUpdateVictory = true;
    }

    void ClearTemporaryResults()
    {
        if (!CanGoToFinalResults)
        {
            SonicMania::Options->CompetitionSession.Wins_P1 = 0;
            SonicMania::Options->CompetitionSession.Wins_P2 = 0;
            SonicMania::Options->CompetitionSession.Wins_P3 = 0;
            SonicMania::Options->CompetitionSession.Wins_P4 = 0;
            P1_HasWon_Round = false;
            P2_HasWon_Round = false;
            P3_HasWon_Round = false;
            P4_HasWon_Round = false;
            LastZone = "???";
        }
    }

    #pragma endregion

    #pragma region Update Match/Round Methods

    void UpdateMatchLength()
    {
        if (!CompPlus_Settings::EndlessRounds) 
        {
            if (SonicMania::CurrentScene == 2)
            {
                int MaxRounds = CompPlus_Settings::NumberOfRounds;

                // At beginning of match
                int WinThreshold = (MaxRounds / 2) + 1;

                if (GetPlusCurrentRound() == MaxRounds)
                {
                    // Player with most wins is overall winner (could be a tie)
                    int MaxWins = 0;

                    if (P1_WinsPlus > MaxWins) MaxWins = P1_WinsPlus;
                    if (P2_WinsPlus > MaxWins) MaxWins = P2_WinsPlus;
                    if (P3_WinsPlus > MaxWins) MaxWins = P3_WinsPlus;
                    if (P4_WinsPlus > MaxWins) MaxWins = P4_WinsPlus;

                    if (MaxWins == P1_WinsPlus) P1_HasWon_Match = true;
                    if (MaxWins == P2_WinsPlus) P2_HasWon_Match = true;
                    if (MaxWins == P3_WinsPlus) P3_HasWon_Match = true;
                    if (MaxWins == P4_WinsPlus) P4_HasWon_Match = true;
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
                        if (MaxWins == P1_WinsPlus) P1_HasWon_Match = true;
                        if (MaxWins == P2_WinsPlus) P2_HasWon_Match = true;
                        if (MaxWins == P3_WinsPlus) P3_HasWon_Match = true;
                        if (MaxWins == P4_WinsPlus) P4_HasWon_Match = true;
                        CanGoToFinalResults = true;
                    }
                    else
                    {
                        //No Clear Winner Yet
                    }
                }
            }
        }
    }

    void SaveRoundsStats() 
    {
        if (!RoundStatsSaved) 
        {
            LastCurrentRound = GetPlusCurrentRound();
            RoundStatsSaved = true;
        }
    }

    void UpdateRounds()
    {
        if (SonicMania::Options->CompetitionSession.UIVsSelectedZoneID != 0 || SonicMania::Options->CompetitionSession.UIVsSelectedZoneID != 0 || SonicMania::Options->CompetitionSession.UIVsLevelSelectIndex != 0)
        {
            SonicMania::Options->CompetitionSession.UIVsLevelSelectIndex = 0;
            SonicMania::Options->CompetitionSession.UIVsSelectedZoneID = 0;
            SonicMania::Options->CompetitionSession.UIVsSelectedActID = 0;
        }


        if (!CompPlus_Scoring::CanGoToFinalResults)
        {
            SaveRoundsStats();
            if (SonicMania::Options->CompetitionSession.TotalRounds != 14) SonicMania::Options->CompetitionSession.TotalRounds = 14;
            if (GetCurrentRound() >= 1)
            {
                SetPlusCurrentRound(PlusCurrentRound + 1);
                SetCurrentRound(0);
            }
            RoundStatsSaved = false;
        }
        else
        {
            SaveRoundsStats();
            SetCurrentRound(2);
            SonicMania::Options->CompetitionSession.TotalRounds = 2;
            SonicMania::Options->CompetitionSession.Wins_P1 = (CompPlus_Scoring::P1_HasWon_Match ? 2 : 0);
            SonicMania::Options->CompetitionSession.Wins_P2 = (CompPlus_Scoring::P2_HasWon_Match ? 2 : 0);
            SonicMania::Options->CompetitionSession.Wins_P3 = (CompPlus_Scoring::P3_HasWon_Match ? 2 : 0);
            SonicMania::Options->CompetitionSession.Wins_P4 = (CompPlus_Scoring::P4_HasWon_Match ? 2 : 0);
        }



        if (SonicMania::Options->CompetitionSession.inMatch == false)
        {
            ClearMatchResults();
        }
    }

    #pragma endregion

    void OnSceneReset()
    {

    }

    void OnFrame()
    {
        UpdateRounds();
        UpdateMatchLength();
    }
}
