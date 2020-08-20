#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "SonicMania.h"
#include "CompetitionPlus.h"

namespace CompPlus_HubWorld
{
    struct INT_Position {

        int X;
        int Y;

        INT_Position(int _x, int _y)
        {
            X = _x;
            Y = _y;
        }

        INT_Position() 
        {
            X = 0;
            Y = 0;
        }
    };
    extern void LoadLevelSelect();
    extern void UpdateHUBWorld();
    extern void EnterLevelSelectLoop(bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed);
};

