#include "Drawing.h"
#include "stdafx.h"
#include <string>
#include <vector>
#include "CompPlus_Core/CompPlus_Common.h"
#include "depends/colorspace/ColorSpace.h"
#include "depends/colorspace/Comparison.h"
#include "depends/colorspace/Conversion.h"

namespace Drawing
{
    using namespace SonicMania;

    int DevFontSpriteID = 0;
    bool DevFontLoaded = false;

    int ManiaFontSpriteID = 0;
    bool ManiaFontLoaded = false;

    int DevEXEFontSpriteID = 0;
    bool DevEXEFontLoaded = false;

    double Interpolate(double a, double b, float t)
    {
        return (1.0 - t) * a + t * b;
    }

    SonicMania::Color InterpolateColors(SonicMania::Color a, SonicMania::Color b, float t)
    {
        ColorSpace::Rgb _a(a.Red, a.Green, a.Blue);
        ColorSpace::Rgb _b(b.Red, b.Green, b.Blue);
        ColorSpace::Rgb final;

        final.r = Interpolate(_a.r, _b.r, t);
        final.g = Interpolate(_a.g, _b.g, t);
        final.b = Interpolate(_a.b, _b.b, t);

        return SonicMania::Color(final.r, final.g, final.b);
    }

    Vector2 GetFramePosition(Vector2 Position, AnimationFrame Frame)
    {
        int AdditionalX = 0;
        int AdditionalY = 0;
        if (Frame.PivotX > 0)
        {
            AdditionalX = Frame.PivotX;
        }
        else
        {
            AdditionalX = -Frame.PivotX;
        }
        if (Frame.PivotY > 0)
        {
            AdditionalY = -Frame.PivotY;
        }
        else
        {
            AdditionalY = Frame.PivotY;
        }
        return Vector2(Position.X + AdditionalX, Position.Y - 1);
    }

    void UnloadDrawables()
    {
        DevFontSpriteID = 0;
        DevFontLoaded = false;
        ManiaFontSpriteID = 0;
        ManiaFontLoaded = false;
        DevEXEFontSpriteID = 0;
        DevEXEFontLoaded = false;
    }

    AnimationFrame* GetAnimationFrameFromFrameID(SonicMania::EntityAnimationData Animation, int FrameID)
    {      
        AnimationFrame* Frame = &AnimationFrame();
        for (int i = 0; i < Animation.FrameCount - 1; i++) 
        {
            Frame = (AnimationFrame*)GetAddress((int)&Animation.Animationptr, sizeof(AnimationFrame) * i);
            if (Frame == nullptr) continue;
            else if (Frame->FrameID == FrameID) return Frame;
        }
        if (Frame == nullptr) Frame = &AnimationFrame();
        return Frame;
    }

    int GetAnimationIndexFromFrameID(SonicMania::EntityAnimationData Animation, int FrameID)
    {
        AnimationFrame* Frame = &AnimationFrame();
        int currentIndex = 0;
        for (int i = 0; i < Animation.FrameCount - 1; i++)
        {
            Frame = (AnimationFrame*)GetAddress((int)&Animation.Animationptr, sizeof(AnimationFrame) * i);
            if (Frame == nullptr) continue;
            else if (Frame->FrameID == FrameID) return i;
            currentIndex = i;
        }
        return currentIndex;
    }

    void DrawTitleCardRect(int x, int y, int width, int height, int color, int alpha, InkEffect effect) 
    {
        Vector2 RectPosition = Vector2(x - GetPointer(0xAA7628, 0x96000), y - GetPointer(0xAA7628, 0x96004));
        DrawRect(RectPosition.X, RectPosition.Y, width, height, color, alpha, effect, true);
    }


    void DrawMenuTextSprite(std::wstring Name, Vector2 LocationStart, bool ScreenRelative, int DrawOrder = 0, int Rotation = 0, int Angle = 0, DevMenu_Alignment Alignment = Alignment_Right)
    {
        if (!ManiaFontLoaded)
        {
            ManiaFontSpriteID = LoadAnimation(CompPlus_Common::Anim_UISmallFont, Scope_None);
            ManiaFontLoaded = true;
            return;
        }

        int SpriteFrame = 0;
        int RealSpriteFrame = 0;
        int BuildLength = 0;
        EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);
        if (!&RingTemp->ActNumbersData) return;
        int OldDrawOrder = RingTemp->DrawOrder;
        for (int i = 0; i < Name.length(); i++)
        {
            RealSpriteFrame = int(Name[i]);
            SpriteFrame = int(Name[i]) - 32;
            SetSpriteAnimation(ManiaFontSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
            AnimationFrame Frame = *GetAnimationFrameFromFrameID(RingTemp->ActNumbersData, RealSpriteFrame);
            BuildLength = BuildLength + Frame.Width;
        }
        if (Alignment == DevMenu_Alignment::Alignment_Left) LocationStart.X = LocationStart.X - BuildLength;
        else if (Alignment == DevMenu_Alignment::Alignment_Center) LocationStart.X = LocationStart.X - (BuildLength != 0 ? (BuildLength / 2) + BuildLength % 2 : 0);
        //Offset length to build to our point. 

        for (int i = 0; i < Name.length(); i++)
        {
            RealSpriteFrame = int(Name[i]);
            SpriteFrame = int(Name[i]) - 32;
            RingTemp->DrawFX = SonicMania::DrawingFX_Rotate;
            RingTemp->Rotation = Rotation;
            RingTemp->Angle = Angle;
            RingTemp->DrawOrder = DrawOrder;
            SetSpriteAnimation(ManiaFontSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
            AnimationFrame Frame = *GetAnimationFrameFromFrameID(RingTemp->ActNumbersData, RealSpriteFrame);
            Vector2 FramePosition = GetFramePosition(LocationStart, Frame);
            DrawSprite(&RingTemp->ActNumbersData, &FramePosition, ScreenRelative);
            LocationStart.X = LocationStart.X + Frame.Width;
        }
        RingTemp->DrawOrder = OldDrawOrder;
    }

    void DrawMenuTextSprite(std::string Name, Vector2 LocationStart, bool ScreenRelative, int DrawOrder = 0, int Rotation = 0, int Angle = 0, DevMenu_Alignment Alignment = Alignment_Right)
    {
        if (!ManiaFontLoaded)
        {
            ManiaFontSpriteID = LoadAnimation(CompPlus_Common::Anim_UISmallFont, Scope_Stage);
            ManiaFontLoaded = true;
            return;
        }

        int SpriteFrame = 0;
        int RealSpriteFrame = 0;
        int BuildLength = 0;
        EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);
        if (!&RingTemp->ActNumbersData) return;
        int OldDrawOrder = RingTemp->DrawOrder;
        for (int i = 0; i < Name.length(); i++)
        {
            RealSpriteFrame = int(Name[i]);
            SpriteFrame = int(Name[i]) - 32;
            SetSpriteAnimation(ManiaFontSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
            AnimationFrame Frame = *GetAnimationFrameFromFrameID(RingTemp->ActNumbersData, RealSpriteFrame);
            BuildLength = BuildLength + Frame.Width;
        }
        if (Alignment == DevMenu_Alignment::Alignment_Left) LocationStart.X = LocationStart.X - BuildLength;
        else if (Alignment == DevMenu_Alignment::Alignment_Center) LocationStart.X = LocationStart.X - (BuildLength != 0 ? (BuildLength / 2) : 0);
        //Offset length to build to our point. 

        for (int i = 0; i < Name.length(); i++)
        {
            RealSpriteFrame = int(Name[i]);
            SpriteFrame = int(Name[i]) - 32;
            RingTemp->DrawFX = SonicMania::DrawingFX_Rotate;
            RingTemp->Rotation = Rotation;
            RingTemp->Angle = Angle;
            RingTemp->DrawOrder = DrawOrder;
            SetSpriteAnimation(ManiaFontSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
            AnimationFrame Frame = *GetAnimationFrameFromFrameID(RingTemp->ActNumbersData, RealSpriteFrame);
            Vector2 FramePosition = GetFramePosition(LocationStart, Frame);
            DrawSprite(&RingTemp->ActNumbersData, &FramePosition, ScreenRelative);
            LocationStart.X = LocationStart.X + Frame.Width;
        }
        RingTemp->DrawOrder = OldDrawOrder;
    }

    void DrawDevTextSprite(std::string Name, Vector2 LocationStart, bool ScreenRelative, int DrawOrder = 0, int Rotation = 0, int Angle = 0, DevMenu_Alignment Alignment = Alignment_Right, bool Highlighed = false)
    {
        if (!DevFontLoaded)
        {
            DevFontSpriteID = LoadAnimation(CompPlus_Common::Anim_LSelectText, Scope_Stage);
            DevFontLoaded = true;
            return;
        }


        int SpriteFrame = 0;
        int BuildLength = 0;
        EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);
        if (!&RingTemp->ActNumbersData) return;
        int OldDrawOrder = RingTemp->DrawOrder;
        for (int i = 0; i < Name.length(); i++)
        {
            SetSpriteAnimation(DevFontSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
            SpriteFrame = GetAnimationIndexFromFrameID(RingTemp->ActNumbersData, int(Name[i]));
            BuildLength = BuildLength + 8;
        }
        if (Alignment == DevMenu_Alignment::Alignment_Left) LocationStart.X = LocationStart.X - BuildLength;
        else if (Alignment == DevMenu_Alignment::Alignment_Center) LocationStart.X = LocationStart.X - (BuildLength != 0 ? (BuildLength / 2) : 0);
        //Offset length to build to our point. 

        for (int i = 0; i < Name.length(); i++)
        {
            SpriteFrame = GetAnimationIndexFromFrameID(RingTemp->ActNumbersData, int(Name[i]));
            RingTemp->DrawFX = SonicMania::DrawingFX_Rotate;
            RingTemp->Rotation = Rotation;
            RingTemp->Angle = Angle;
            RingTemp->DrawOrder = DrawOrder;
            AnimationFrame Frame = *GetAnimationFrameFromFrameID(RingTemp->ActNumbersData, SpriteFrame);
            Vector2 FramePosition = GetFramePosition(LocationStart, Frame);
            SetSpriteAnimation(DevFontSpriteID, (Highlighed ? 1 : 0), &RingTemp->ActNumbersData, true, SpriteFrame);
            DrawSprite(&RingTemp->ActNumbersData, &FramePosition, ScreenRelative);
            LocationStart.X = LocationStart.X + 8;

        }
        RingTemp->DrawOrder = OldDrawOrder;
    }

    void DrawDevEXETextSprite(std::string Name, Vector2 LocationStart, bool ScreenRelative, int DrawOrder = 0, int Rotation = 0, int Angle = 0, DevMenu_Alignment Alignment = Alignment_Right, bool Highlighed = false)
    {
        if (!DevEXEFontLoaded)
        {
            DevEXEFontSpriteID = LoadAnimation(CompPlus_Common::Anim_LSelectText_Exe, Scope_Stage);
            DevEXEFontLoaded = true;
            return;
        }


        int SpriteFrame = 0;
        int BuildLength = 0;
        EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);
        int OldDrawOrder = RingTemp->DrawOrder;
        for (int i = 0; i < Name.length(); i++)
        {
            SetSpriteAnimation(DevEXEFontSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
            SpriteFrame = GetAnimationIndexFromFrameID(RingTemp->ActNumbersData, int(Name[i]));
            BuildLength = BuildLength + 8;
        }
        if (Alignment == DevMenu_Alignment::Alignment_Left) LocationStart.X = LocationStart.X - BuildLength;
        else if (Alignment == DevMenu_Alignment::Alignment_Center) LocationStart.X = LocationStart.X - (BuildLength != 0 ? (BuildLength / 2) : 0);
        //Offset length to build to our point. 

        for (int i = 0; i < Name.length(); i++)
        {
            SpriteFrame = GetAnimationIndexFromFrameID(RingTemp->ActNumbersData, int(Name[i]));
            RingTemp->DrawFX = SonicMania::DrawingFX_Rotate;
            RingTemp->Rotation = Rotation;
            RingTemp->Angle = Angle;
            RingTemp->DrawOrder = DrawOrder;
            AnimationFrame Frame = *GetAnimationFrameFromFrameID(RingTemp->ActNumbersData, SpriteFrame);
            Vector2 FramePosition = GetFramePosition(LocationStart, Frame);
            SetSpriteAnimation(DevEXEFontSpriteID, (Highlighed ? 1 : 0), &RingTemp->ActNumbersData, true, SpriteFrame);
            DrawSprite(&RingTemp->ActNumbersData, &FramePosition, ScreenRelative);
            LocationStart.X = LocationStart.X + 8;

        }
        RingTemp->DrawOrder = OldDrawOrder;
    }


}