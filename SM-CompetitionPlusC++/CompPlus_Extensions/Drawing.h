#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "include/ManiaAPI/SonicMania.h"
#include <string>
namespace Drawing 
{
    extern void LoadDrawables();

    struct AnimationFrame //82 Bytes Total
    {
        /* 00000000 */ short X;
        /* 00000002 */ short Y;
        /* 00000004 */ short Width;
        /* 00000006 */ short Height;
        /* 00000008 */ short PivotX;
        /* 0000000A */ short PivotY;
        /* 0000000C */ short Delay;
        /* 0000000E */ short FrameID;
        /* 00000010 */ byte Gap_10[65];

        AnimationFrame()
        {
            X = 0;
            Y = 0;
            Width = 0;
            Height = 0;
            PivotX = 0;
            PivotY = 0;
            Delay = 0;
            FrameID = 0;
        }
    };

    extern SonicMania::Color InterpolateColors(SonicMania::Color a, SonicMania::Color b, float t);
    extern SonicMania::Vector2 GetFramePosition(SonicMania::Vector2 Position, AnimationFrame Frame);
    extern AnimationFrame* GetAnimationFrameFromFrameID(SonicMania::EntityAnimationData Animation, int FrameID);
    extern int GetAnimationIndexFromFrameID(SonicMania::EntityAnimationData Animation, int FrameID);
    extern void DrawTitleCardRect(int x, int y, int width, int height, int color, int alpha, SonicMania::InkEffect effect);
    extern void DrawDevTextSprite(std::string Name, SonicMania::Vector2 LocationStart, bool ScreenRelative, int DrawOrder, int Rotation, int Angle, SonicMania::DevMenu_Alignment Alignment, bool Highlighed);
    extern void DrawDevEXETextSprite(std::string Name, SonicMania::Vector2 LocationStart, bool ScreenRelative, int DrawOrder, int Rotation, int Angle, SonicMania::DevMenu_Alignment Alignment, bool Highlighed);
    extern void DrawMenuTextSprite(std::wstring Name, SonicMania::Vector2 LocationStart, bool ScreenRelative, int DrawOrder, int Rotation, int Angle, SonicMania::DevMenu_Alignment Alignment);
    extern void DrawMenuTextSprite(std::string Name, SonicMania::Vector2 LocationStart, bool ScreenRelative, int DrawOrder, int Rotation, int Angle, SonicMania::DevMenu_Alignment Alignment);

}