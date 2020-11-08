#pragma once
#include "CompPlus_Patches.h"
namespace CompPlus_Scenes
{
    extern CompPlus_Patches::WaterColorDefintion OnWaterColorDraw();
    extern void AlwaysRunningLoop();
    extern void UpdateTitleCard();
    extern void OnObjectPreDraw(const char* object);
    extern void OnObjectPostDraw(const char* object);
    extern void OnSceneDraw(bool HUDDraw);
    extern void OnScenePreload();
    extern void SetSceneSpecifics();
    extern void UpdateScenes();
}

