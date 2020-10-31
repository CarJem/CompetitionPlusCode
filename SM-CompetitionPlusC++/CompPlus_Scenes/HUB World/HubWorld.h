#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "SonicMania.h"
#include "HubCore.h"
#include <string>

namespace CompPlus_HubWorld
{
    //0x486A548
    //0x486A54C
    DataPointer(int, IsPlayerInDebugMode, 0x31F9AC);
    DataPointer(int, IsPlayerInDebugMode_Alt, 0x30D130);

    extern int P1_WarpAlpha;
    extern int P2_WarpAlpha;
    extern int P3_WarpAlpha;
    extern int P4_WarpAlpha;


    extern void SetObjectPalette();
    extern void UnsetObjectPalette();

    extern bool isRestart;
    extern int UpdateHUBDisplays();
    extern void OnFrame();
    extern void WarpLoop(bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed);
    extern void Init(std::string modPath);
};

