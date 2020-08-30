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


        bool operator < (const ScorableTime& time) const
        {
            int first = (Minutes * 6000) + (Seconds * 100) + Centiseconds;
            int second = (time.Minutes * 6000) + (time.Seconds * 100) + time.Centiseconds;
            return first < second;
        }
    };

    extern SonicMania::CompetitionSession LastSession;

    extern bool AllowUpdateVictory;

    extern int WinWait;
    extern int WinWaitMax;

    extern int CurrentRound_Plus;
    extern int LastRound_NoPlus;

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

    extern bool P1_HasWon;
    extern bool P2_HasWon;
    extern bool P3_HasWon;
    extern bool P4_HasWon;

    extern bool ThisMatchIsTied;
    extern bool CanGoToFinalResults;

    extern void SyncLastResults();

    extern void ClearMatchResults();

    extern void ClearInternalWins();

    extern void OnFrame();
}
