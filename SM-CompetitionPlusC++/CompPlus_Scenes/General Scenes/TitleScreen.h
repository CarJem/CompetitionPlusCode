#pragma once
#include "include/ManiaAPI/SonicMania.h"
namespace CompPlus_TitleScreen
{
    extern bool StillDrawing;

    extern void OnFrame();

    extern int OnPlusLogoDraw(SonicMania::EntityAnimationData* AnimData, SonicMania::Vector2* Position, BOOL ScreenRelative);

    extern void OnDraw();

    extern void Reload();
}