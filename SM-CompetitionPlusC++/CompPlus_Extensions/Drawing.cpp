#include "Drawing.h"
#include "stdafx.h"
#include <string>
#include "CompPlus_Core/CompPlus_Common.h"

namespace Drawing
{
    using namespace SonicMania;

    int DevFontSpriteID = 0;
    bool DevFontLoaded = false;

    int ManiaFontSpriteID = 0;
    bool ManiaFontLoaded = false;

    int DevEXEFontSpriteID = 0;
    bool DevEXEFontLoaded = false;

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
            AdditionalY = Frame.PivotY;
        }
        else
        {
            AdditionalY = -Frame.PivotY;
        }
        return Vector2(Position.X + AdditionalX, Position.Y);
    }

    void ReloadDrawables()
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

    void DrawMenuTextSprite(std::string Name, Vector2 LocationStart, bool ScreenRelative, int DrawOrder = 0, int Rotation = 0, int Angle = 0, DevMenu_Alignment Alignment = Alignment_Right)
    {
        if (!ManiaFontLoaded)
        {
            ManiaFontSpriteID = LoadAnimation(CompPlus_Common::Anim_UISmallFont, Scope_Global);
            ManiaFontLoaded = true;
            return;
        }

        int SpriteFrame = 0;
        int RealSpriteFrame = 0;
        int BuildLength = 0;
        EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);;
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
        //Offset lenth to build to our point. 

        for (int i = 0; i < Name.length(); i++)
        {
            RealSpriteFrame = int(Name[i]);
            SpriteFrame = int(Name[i]) - 32;
            RingTemp->DrawOrder = DrawOrder;
            //RingTemp->DrawFX = SonicMania::DrawingFX_Rotate;
            RingTemp->Rotation = Rotation;
            RingTemp->Angle = Angle;
            SetSpriteAnimation(ManiaFontSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
            AnimationFrame Frame = *GetAnimationFrameFromFrameID(RingTemp->ActNumbersData, RealSpriteFrame);
            Vector2 FramePosition = GetFramePosition(LocationStart, Frame);
            DrawSprite(&RingTemp->ActNumbersData, &FramePosition, ScreenRelative);
            LocationStart.X = LocationStart.X + Frame.Width;
        }
    }

    void DrawDevTextSprite(std::string Name, Vector2 LocationStart, bool ScreenRelative, int DrawOrder = 0, int Rotation = 0, int Angle = 0, DevMenu_Alignment Alignment = Alignment_Right, bool Highlighed = false)
    {
        if (!DevFontLoaded)
        {
            DevFontSpriteID = LoadAnimation(CompPlus_Common::Anim_LSelectText, Scope_Global);
            DevFontLoaded = true;
            return;
        }


        int SpriteFrame = 0;
        int BuildLength = 0;
        EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);;
        for (int i = 0; i < Name.length(); i++)
        {
            SetSpriteAnimation(DevFontSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
            SpriteFrame = GetAnimationIndexFromFrameID(RingTemp->ActNumbersData, int(Name[i]));
            BuildLength = BuildLength + 8;
        }
        if (Alignment == DevMenu_Alignment::Alignment_Left) LocationStart.X = LocationStart.X - BuildLength;
        else if (Alignment == DevMenu_Alignment::Alignment_Center) LocationStart.X = LocationStart.X - (BuildLength != 0 ? (BuildLength / 2) : 0);
        //Offset lenth to build to our point. 

        for (int i = 0; i < Name.length(); i++)
        {
            SpriteFrame = GetAnimationIndexFromFrameID(RingTemp->ActNumbersData, int(Name[i]));
            RingTemp->DrawOrder = DrawOrder;
            RingTemp->DrawFX = SonicMania::DrawingFX_Rotate;
            RingTemp->Rotation = Rotation;
            RingTemp->Angle = Angle;
            AnimationFrame Frame = *GetAnimationFrameFromFrameID(RingTemp->ActNumbersData, SpriteFrame);
            Vector2 FramePosition = GetFramePosition(LocationStart, Frame);
            SetSpriteAnimation(DevFontSpriteID, (Highlighed ? 1 : 0), &RingTemp->ActNumbersData, true, SpriteFrame);
            DrawSprite(&RingTemp->ActNumbersData, &FramePosition, ScreenRelative);
            LocationStart.X = LocationStart.X + 8;

        }
    }

    void DrawDevEXETextSprite(std::string Name, Vector2 LocationStart, bool ScreenRelative, int DrawOrder = 0, int Rotation = 0, int Angle = 0, DevMenu_Alignment Alignment = Alignment_Right, bool Highlighed = false)
    {
        if (!DevEXEFontLoaded)
        {
            DevEXEFontSpriteID = LoadAnimation(CompPlus_Common::Anim_LSelectText_Exe, Scope_Global);
            DevEXEFontLoaded = true;
            return;
        }


        int SpriteFrame = 0;
        int BuildLength = 0;
        EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);;
        for (int i = 0; i < Name.length(); i++)
        {
            SetSpriteAnimation(DevEXEFontSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
            SpriteFrame = GetAnimationIndexFromFrameID(RingTemp->ActNumbersData, int(Name[i]));
            BuildLength = BuildLength + 8;
        }
        if (Alignment == DevMenu_Alignment::Alignment_Left) LocationStart.X = LocationStart.X - BuildLength;
        else if (Alignment == DevMenu_Alignment::Alignment_Center) LocationStart.X = LocationStart.X - (BuildLength != 0 ? (BuildLength / 2) : 0);
        //Offset lenth to build to our point. 

        for (int i = 0; i < Name.length(); i++)
        {
            SpriteFrame = GetAnimationIndexFromFrameID(RingTemp->ActNumbersData, int(Name[i]));
            RingTemp->DrawOrder = DrawOrder;
            RingTemp->DrawFX = SonicMania::DrawingFX_Rotate;
            RingTemp->Rotation = Rotation;
            RingTemp->Angle = Angle;
            AnimationFrame Frame = *GetAnimationFrameFromFrameID(RingTemp->ActNumbersData, SpriteFrame);
            Vector2 FramePosition = GetFramePosition(LocationStart, Frame);
            SetSpriteAnimation(DevEXEFontSpriteID, (Highlighed ? 1 : 0), &RingTemp->ActNumbersData, true, SpriteFrame);
            DrawSprite(&RingTemp->ActNumbersData, &FramePosition, ScreenRelative);
            LocationStart.X = LocationStart.X + 8;

        }
    }


}