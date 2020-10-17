#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "SonicMania.h"
#include <string>
namespace Drawing 
{
    extern void ReloadDrawables();
    extern void DrawTitleCardRect(int x, int y, int width, int height, int color, int alpha, SonicMania::InkEffect effect);
    extern void DrawDevTextSprite(std::string Name, SonicMania::Vector2 LocationStart, bool ScreenRelative, int DrawOrder, int Rotation, int Angle, SonicMania::DevMenu_Alignment Alignment, bool Highlighed);
    extern void DrawDevEXETextSprite(std::string Name, SonicMania::Vector2 LocationStart, bool ScreenRelative, int DrawOrder, int Rotation, int Angle, SonicMania::DevMenu_Alignment Alignment, bool Highlighed);
    extern void DrawMenuTextSprite(std::string Name, SonicMania::Vector2 LocationStart, bool ScreenRelative, int DrawOrder, int Rotation, int Angle, SonicMania::DevMenu_Alignment Alignment);

}