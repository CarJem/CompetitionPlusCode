#pragma once
#include "CompPlus_Extensions/IZAPI.h"
extern "C"
{
    namespace CompPlus_Core 
    {
        extern bool StageRefresh;
        extern int IZ_SceneChangeIdleTime;
        extern IZAPI::StageInfo CurrentStage;

        extern void OnDraw();
        extern void OnSceneReset();

        extern void OnStageLoad(IZAPI::StageInfo info, IZAPI::StageLoadPhase phase);
        extern void OnStageUnload(IZAPI::StageInfo info, IZAPI::StageLoadPhase phase);
    }
}