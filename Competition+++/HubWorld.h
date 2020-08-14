#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "SonicMania.h"
#include "CompetitionPlus.h"

namespace CompPlus_HubWorld
{
    extern void UpdateHUBWorld();
    extern void EnterLevelSelectLoop(bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed);
};

