#pragma once
#include "stdafx.h"
#include "IZAPI.h"
#include "SonicMania.h"
#include "ManiaExt.h"
#include "depends/tinyxml2/tinyxml2.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>

namespace CompPlus_Scoring
{
    struct ScorableInt
    {
        int Position = 0;
        int Value;
        int PlayerID = 0;
        bool HasWon = false;
        int RealPosition = 0;

        ScorableInt()
        {

        }

        ScorableInt(int _value, int _playerID) : ScorableInt()
        {
            Value = _value;
            PlayerID = _playerID;
        }
    };

    struct ScorableTime
    {
        int RealPosition = 0;
        int Position = 0;
        int Minutes;
        int Seconds;
        int Centiseconds;
        int PlayerID;
        bool HasWon = false;

        ScorableTime()
        {

        }

        ScorableTime(int m, int s, int c) : ScorableTime()
        {
            Minutes = m;
            Seconds = s;
            Centiseconds = s;
        }

        bool operator != (const ScorableTime& time) const
        {
            int first = (Minutes * 6000) + (Seconds * 100) + Centiseconds;
            int second = (time.Minutes * 6000) + (time.Seconds * 100) + time.Centiseconds;
            return first != second;
        }

        bool operator < (const ScorableTime& time) const
        {
            int first = (Minutes * 6000) + (Seconds * 100) + Centiseconds;
            int second = (time.Minutes * 6000) + (time.Seconds * 100) + time.Centiseconds;
            return first < second;
        }
    };

    extern std::vector<ScorableTime> TimeRanking;
    extern std::vector<ScorableInt> TotalRingRanking;
    extern std::vector<ScorableInt> ScoreRanking;
    extern std::vector<ScorableInt> RingRanking;
    extern std::vector<ScorableInt> ItemRanking;
    extern std::vector<ScorableInt> AverageRanking;
    extern std::vector<ScorableInt> AntiRingRanking;

    extern SonicMania::CompetitionSession LastSession;

    extern bool AllowUpdateVictory;

    extern bool PodeiumSpawnActive;

    extern const char* LastZone;

    extern int WinWait;
    extern int WinWaitMax;

    extern int P1_Placement;
    extern int P2_Placement;
    extern int P3_Placement;
    extern int P4_Placement;

    extern int P1_LastPlacement;
    extern int P2_LastPlacement;
    extern int P3_LastPlacement;
    extern int P4_LastPlacement;

    extern int P1_WinsPlus;
    extern int P2_WinsPlus;
    extern int P3_WinsPlus;
    extern int P4_WinsPlus;

    extern bool P1_HasWon_Round;
    extern bool P2_HasWon_Round;
    extern bool P3_HasWon_Round;
    extern bool P4_HasWon_Round;

    extern bool P1_HasWon_Match;
    extern bool P2_HasWon_Match;
    extern bool P3_HasWon_Match;
    extern bool P4_HasWon_Match;

    extern int LastCurrentRound;

    extern bool ThisMatchIsTied;
    extern bool CanGoToFinalResults;

    extern void SetPlusCurrentRound(int value);
    extern int GetPlusCurrentRound();

    extern void SyncLastResults();

    extern void ApplyPoyoPoyoRuleset();

    extern void SetRoundEndWinner();

    extern void ClearMatchResults();

    extern void ClearTemporaryResults();

    extern void OnSceneReset();

    extern void OnFrame();
}
