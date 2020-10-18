#include "stdafx.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "SonicMania.h"
#include <string>
#include <sstream>
#include "HubCore.h"
#include "HubText.h"
#include "CompPlus_Core/CompPlus_Announcers.h"
#include "CompPlus_Core/CompPlus_Scoring.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "Base.h"

namespace CompPlus_HubCore
{
    int ReturnDestination = 0;
    using namespace SonicMania;

    bool CanDrawP1 = false;
    bool CanDrawP2 = false;
    bool CanDrawP3 = false;
    bool CanDrawP4 = false;

    bool isRestart = true;

    bool HUDDrawOrderSet = false;
    int HUDDrawOrder = 0;
    int HUDSpriteID = 0;
    bool HUDSpriteLoaded = false;

    void DrawCrownSprite(SonicMania::EntityPlayer Player, Vector2 LocationStart, bool ScreenRelative)
    {
        if (!HUDSpriteLoaded)
        {
            HUDSpriteID = LoadAnimation(CompPlus_Common::Anim_HubCrown, Scope_Global);
            HUDSpriteLoaded = true;
            return;
        }


        if (ScreenRelative)
        {
            int x = SonicMania::OBJ_Camera->XPos;
            int y = SonicMania::OBJ_Camera->YPos;

            LocationStart = Vector2(x + LocationStart.GetFullX(), y + LocationStart.GetFullY());
        }


        int SpriteFrame = 0;
        EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);;

        RingTemp->DrawOrder = Player.DrawOrder;
        RingTemp->DrawFX = SonicMania::DrawingFX_Rotate;
        RingTemp->ActiveScreens = Player.ActiveScreens;
        RingTemp->Rotation = Player.Rotation;
        RingTemp->Angle = Player.Angle;
        SetSpriteAnimation(HUDSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
        DrawSprite(&RingTemp->ActNumbersData, &LocationStart, true);
        LocationStart.X = LocationStart.X + 8;
    }

    char* GetPosition(int PlayerID)
    {
        int Position = 0;
        if (PlayerID == 1) Position = CompPlus_Scoring::P1_LastPlacement;
        else if (PlayerID == 2) Position = CompPlus_Scoring::P2_LastPlacement;
        else if (PlayerID == 3) Position = CompPlus_Scoring::P3_LastPlacement;
        else if (PlayerID == 4) Position = CompPlus_Scoring::P4_LastPlacement;

        if (Position == 1) return (char*)"1st";
        else if (Position == 2) return (char*)"2nd";
        else if (Position == 3) return (char*)"3rd";
        else if (Position == 4) return (char*)"4th";
        else return (char*)"   ";
    }

    void EndDraw(int pointer)
    {
        if (pointer == 0) CanDrawP1 = false;
        else if (pointer == 1) CanDrawP2 = false;
        else if (pointer == 2) CanDrawP3 = false;
        else if (pointer == 3) CanDrawP4 = false;
    }

    bool CanDraw(int pointer)
    {
        if (pointer == 0) return CanDrawP1;
        else if (pointer == 1) return CanDrawP2;
        else if (pointer == 2) return CanDrawP3;
        else if (pointer == 3) return CanDrawP4;
    }

    Hitbox Player1Box;
    Hitbox Player2Box;
    Hitbox Player3Box;
    Hitbox Player4Box;

    void OnUnusedDraw(EntityPlayer* ThisObject, int offset) 
    {
        DrawCircleOutline((ThisObject->Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (ThisObject->Position.Y - GetPointer(0xAA7628, 0x96004 + offset)), 50 + 75, 1000, ToRGB888(GetPaletteEntry(0, 1)), 140, Ink_Alpha, true);
        DrawCircleOutline((ThisObject->Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (ThisObject->Position.Y - GetPointer(0xAA7628, 0x96004 + offset)), 50 + ThisObject->RingCount, 1000, ToRGB888(GetPaletteEntry(0, 1)), 160, Ink_Alpha, true);
        DrawCircleOutline((ThisObject->Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (ThisObject->Position.Y - GetPointer(0xAA7628, 0x96004 + offset)), 60 + ThisObject->RingCount, 1000, ToRGB888(GetPaletteEntry(0, 1)), 250, Ink_Alpha, true);
    }

    void DrawWaitingForPlayers(int offset) 
    {
        for (int i = 0; i < 2301; ++i)
        {
            SonicMania::Entity& entity = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(i);
            if (entity.ObjectID == SonicMania::GetObjectIDFromType(SonicMania::ObjectType_SSRing))
            {
                SpecialRing& specialRing = *SonicMania::GetEntityFromSceneSlot<SpecialRing>(i);
                if (!specialRing.Enabled)
                {

                    int X1 = specialRing.Position.X - GetPointer(0xAA7628, 0x96000 + offset) - 30;
                    int X2 = specialRing.Position.X - GetPointer(0xAA7628, 0x96000 + offset) - 15;
                    int Y1 = specialRing.Position.Y - GetPointer(0xAA7628, 0x96004 + offset) + 45;
                    int Y2 = specialRing.Position.Y - GetPointer(0xAA7628, 0x96004 + offset) + 8 + 45;
                    int Y3 = specialRing.Position.Y - GetPointer(0xAA7628, 0x96004 + offset) + 16 + 45;

                    Vector2 Position1 = Vector2(X1, Y1);
                    Vector2 Position2 = Vector2(X2, Y2);
                    Vector2 Position3 = Vector2(X1, Y3);

                    DrawTextSprite(Player1, "Waiting", Position1, 0);
                    DrawTextSprite(Player1, "For", Position2, 0);
                    DrawTextSprite(Player1, "Players", Position3, 0);
                }
            }
        }


    }

    void OnDraw()
    {
        ushort pointer = GetSpritePointer(0xAA7634, 0x14);
        int screen = 0;

        if (pointer == 0) screen = 0;
        else if (pointer == 1) screen = 1;
        else if (pointer == 2) screen = 2;
        else if (pointer == 3) screen = 3;

        if (CanDraw(screen))
        {
            int offset = 0x96030 * screen;

            DrawWaitingForPlayers(offset);


            if (Player1.Camera != nullptr)
            {
                Vector2 position_p1 = Vector2((SonicMania::Player1.Position.X - GetPointer(0xAA7628, 0x96000 + offset)) - 11, (Player1.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) + Player1Box.Top + Player1Box.Bottom + 24);
                Vector2 position_p1_top = Vector2((SonicMania::Player1.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player1.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) - Player1Box.Top - Player1Box.Bottom - 45);
                Vector2 position_p1_top2 = Vector2((SonicMania::Player1.Position.X - GetPointer(0xAA7628, 0x96000 + offset)) - 8, (Player1.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) - Player1Box.Top - Player1Box.Bottom - 24);
                DrawTextSprite(Player1, "1P", position_p1_top2, 0);
                DrawTextSprite(Player1, GetPosition(1), position_p1, 0);
                if (CompPlus_Scoring::P1_LastPlacement == 1) DrawCrownSprite(Player1, position_p1_top, false);
                //if (screen == 0) OnUnusedDraw(&Player1, offset);
            }
            if (Player2.Camera != nullptr)
            {

                Vector2 position_p2 = Vector2((SonicMania::Player2.Position.X - GetPointer(0xAA7628, 0x96000 + offset)) - 11, (Player2.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) + Player2Box.Top + Player2Box.Bottom + 24);
                Vector2 position_p2_top = Vector2((SonicMania::Player2.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player2.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) - Player2Box.Top - Player2Box.Bottom - 45);
                Vector2 position_p2_top2 = Vector2((SonicMania::Player2.Position.X - GetPointer(0xAA7628, 0x96000 + offset)) - 8, (Player2.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) - Player2Box.Top - Player2Box.Bottom - 24);
                DrawTextSprite(Player2, "2P", position_p2_top2, 0);
                DrawTextSprite(Player2, GetPosition(2), position_p2, 0);
                if (CompPlus_Scoring::P2_LastPlacement == 1) DrawCrownSprite(Player2, position_p2_top, false);
                //if (screen == 1) OnUnusedDraw(&Player2, offset);
            }
            if (Player3.Camera != nullptr)
            {

                Vector2 position_p3 = Vector2((SonicMania::Player3.Position.X - GetPointer(0xAA7628, 0x96000 + offset)) - 11, (Player3.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) + Player3Box.Top + Player3Box.Bottom + 24);
                Vector2 position_p3_top = Vector2((SonicMania::Player3.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player3.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) - Player3Box.Top - Player3Box.Bottom - 45);
                Vector2 position_p3_top2 = Vector2((SonicMania::Player3.Position.X - GetPointer(0xAA7628, 0x96000 + offset)) - 8, (Player3.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) - Player3Box.Top - Player3Box.Bottom - 24);
                DrawTextSprite(Player3, "3P", position_p3_top2, 0);
                DrawTextSprite(Player3, GetPosition(3), position_p3, 0);
                if (CompPlus_Scoring::P3_LastPlacement == 1) DrawCrownSprite(Player3, position_p3_top, false);
                //if (screen == 2) OnUnusedDraw(&Player3, offset);
            }
            if (Player4.Camera != nullptr)
            {
                Vector2 position_p4 = Vector2((SonicMania::Player4.Position.X - GetPointer(0xAA7628, 0x96000 + offset)) - 11, (Player4.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) + Player4Box.Top + Player4Box.Bottom + 24);
                Vector2 position_p4_top = Vector2((SonicMania::Player4.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player4.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) - Player4Box.Top - Player4Box.Bottom - 45);
                Vector2 position_p4_top2 = Vector2((SonicMania::Player4.Position.X - GetPointer(0xAA7628, 0x96000 + offset)) - 8, (Player4.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) - Player4Box.Top - Player4Box.Bottom - 24);
                DrawTextSprite(Player4, "4P", position_p4_top2, 0);
                DrawTextSprite(Player4, GetPosition(4), position_p4, 0);
                if (CompPlus_Scoring::P4_LastPlacement == 1) DrawCrownSprite(Player4, position_p4_top, false);
                //if (screen == 3) OnUnusedDraw(&Player4, offset);
            }

            EndDraw(screen);
        }
    }

    void DisableCountdown() 
    {
        SonicMania::Timer.Enabled = true;
    }

    void SetHUBVisualSettings()
    {
        if (isRestart) 
        {
            if (Player1.Camera != nullptr) Hitbox Player1Box = *GetHitbox(&Player1.Animation, 1);
            if (Player2.Camera != nullptr) Hitbox Player2Box = *GetHitbox(&Player2.Animation, 1);
            if (Player3.Camera != nullptr) Hitbox Player3Box = *GetHitbox(&Player3.Animation, 1);
            if (Player4.Camera != nullptr) Hitbox Player4Box = *GetHitbox(&Player4.Animation, 1);
            //DevFontLoaded = false;
            //HUDSpriteLoaded = false;
            isRestart = false;
        }

        //Stop Countdown
        DisableCountdown();

        //Disable Timer
        SonicMania::Timer.ResetTimer();

        //Disable HUD
        //WriteData((BYTE*)(baseAddress + 0x47B065), (BYTE)0);

        //Player Life Count Infinite
        SonicMania::Player1.LifeCount = 99;
        SonicMania::Player2.LifeCount = 99;
        SonicMania::Player3.LifeCount = 99;
        SonicMania::Player4.LifeCount = 99;

        //Allow Draw
        CanDrawP1 = true;
        CanDrawP2 = true;
        CanDrawP3 = true;
        CanDrawP4 = true;
    }
}