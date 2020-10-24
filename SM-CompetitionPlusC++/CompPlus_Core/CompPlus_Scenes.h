#pragma once

namespace CompPlus_Scenes
{
    extern void OnObjectPreDraw(const char* object);
    extern void OnObjectPostDraw(const char* object);
    extern void OnSceneDraw();
    extern void OnScenePreload();
    extern void SetSceneSpecifics();
    extern void UpdateScenes();
}

