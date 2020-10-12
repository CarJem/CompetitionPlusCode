#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "SonicMania.h"
#include "HubCore.h"

namespace CompPlus_HubWorld
{
    DataPointer(int, IsPlayerInDebugMode, 0x31F9AC);
    DataPointer(int, IsPlayerInDebugMode_Alt, 0x30D130);

    extern bool isRestart;
    extern int UpdateHUBDisplays();
    extern void OnFrame();
    extern void WarpLoop(bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed);
};

