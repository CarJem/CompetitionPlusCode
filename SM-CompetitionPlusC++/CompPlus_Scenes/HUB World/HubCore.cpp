#include "stdafx.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "SonicMania.h"
#include <string>
#include <sstream>
#include "HubCore.h"
#include "HubText.h"
#include "HubWorld.h"
#include "CompPlus_Core/CompPlus_Announcers.h"
#include "CompPlus_Core/CompPlus_Scoring.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "Base.h"
#include "CompPlus_Extensions/Drawing.h"

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

        //CompPlus_HubWorld::SetObjectPalette();


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

        //CompPlus_HubWorld::UnsetObjectPalette();
    }

    char* GetPosition(int PlayerID)
    {
        int Position = 0;
        if (PlayerID == 1) Position = CompPlus_Scoring::P1_LastPlacement;
        else if (PlayerID == 2) Position = CompPlus_Scoring::P2_LastPlacement;
        else if (PlayerID == 3) Position = CompPlus_Scoring::P3_LastPlacement;
        else if (PlayerID == 4) Position = CompPlus_Scoring::P4_LastPlacement;

        if (Position == 1) return (char*)"1ST";
        else if (Position == 2) return (char*)"2ND";
        else if (Position == 3) return (char*)"3RD";
        else if (Position == 4) return (char*)"4TH";
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
        else return false;
    }

    Hitbox Player1Box;
    Hitbox Player2Box;
    Hitbox Player3Box;
    Hitbox Player4Box;

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

                    int X1 = specialRing.Position.X - GetPointer(0xAA7628, 0x96000 + offset);
                    int X2 = specialRing.Position.X - GetPointer(0xAA7628, 0x96000 + offset);
                    int Y1 = specialRing.Position.Y - GetPointer(0xAA7628, 0x96004 + offset) + 45;
                    int Y2 = specialRing.Position.Y - GetPointer(0xAA7628, 0x96004 + offset) + 8 + 45;
                    int Y3 = specialRing.Position.Y - GetPointer(0xAA7628, 0x96004 + offset) + 16 + 45;

                    Vector2 Position1 = Vector2(X1, Y1);
                    Vector2 Position2 = Vector2(X2, Y2);
                    Vector2 Position3 = Vector2(X1, Y3);

                    Drawing::DrawDevTextSprite("WAITING", Position1, true, 14, 0, 0, DevMenu_Alignment::Alignment_Center, false);
                    Drawing::DrawDevTextSprite("FOR", Position2, true, 14, 0, 0, DevMenu_Alignment::Alignment_Center, false);
                    Drawing::DrawDevTextSprite("PLAYERS", Position3, true, 14, 0, 0, DevMenu_Alignment::Alignment_Center, false);
                }
            }
        }


    }

    void DrawKillScreens(int screen, int offset)
    {
        EntityTitleCard* Canvas = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);
        int OldDrawOrder = Canvas->DrawOrder;
        Canvas->DrawOrder = 14;


        int P1_Alpha = 255 - CompPlus_HubWorld::P1_WarpAlpha;
        int P2_Alpha = 255 - CompPlus_HubWorld::P2_WarpAlpha;
        int P3_Alpha = 255 - CompPlus_HubWorld::P3_WarpAlpha;
        int P4_Alpha = 255 - CompPlus_HubWorld::P4_WarpAlpha;

        Vector2 position_p1 = Vector2(SonicMania::Player1.Position.X, SonicMania::Player1.Position.Y);
        Vector2 position_p2 = Vector2(SonicMania::Player2.Position.X, SonicMania::Player2.Position.Y);
        Vector2 position_p3 = Vector2(SonicMania::Player3.Position.X, SonicMania::Player3.Position.Y);
        Vector2 position_p4 = Vector2(SonicMania::Player4.Position.X, SonicMania::Player4.Position.Y);


        if (screen == 0) DrawRect(0, 0, 500, 500, 0xFFFFFF, P1_Alpha, Ink_Alpha, true);
        if (screen == 1) DrawRect(0, 0, 500, 500, 0xFFFFFF, P2_Alpha, Ink_Alpha, true);
        if (screen == 2) DrawRect(0, 0, 500, 500, 0xFFFFFF, P3_Alpha, Ink_Alpha, true);
        if (screen == 3) DrawRect(0, 0, 500, 500, 0xFFFFFF, P4_Alpha, Ink_Alpha, true);
        Canvas->DrawOrder = OldDrawOrder;
    }

    void OnDraw()
    {
        EntityTitleCard* Canvas = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);
        int OldDrawOrder = Canvas->DrawOrder;

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
                Vector2 position_p1_top2 = Vector2((SonicMania::Player1.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player1.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) - Player1Box.Top - Player1Box.Bottom - 24);
                Drawing::DrawDevTextSprite("1P", position_p1_top2, true, Player1.DrawOrder, 0, 0, Alignment_Center, false);

                if (CompPlus_Scoring::P1_LastPlacement == 1) 
                {
                    Drawing::DrawDevTextSprite(GetPosition(1), position_p1, true, 12, 0, 0, Alignment_Center, true);
                    DrawCrownSprite(Player1, position_p1_top, false);
                }
                else 
                {
                    Drawing::DrawDevTextSprite(GetPosition(1), position_p1, true, 12, 0, 0, Alignment_Center, false);
                }
            }
            if (Player2.Camera != nullptr)
            {

                Vector2 position_p2 = Vector2((SonicMania::Player2.Position.X - GetPointer(0xAA7628, 0x96000 + offset)) - 11, (Player2.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) + Player2Box.Top + Player2Box.Bottom + 24);
                Vector2 position_p2_top = Vector2((SonicMania::Player2.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player2.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) - Player2Box.Top - Player2Box.Bottom - 45);
                Vector2 position_p2_top2 = Vector2((SonicMania::Player2.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player2.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) - Player2Box.Top - Player2Box.Bottom - 24);
                Drawing::DrawDevTextSprite("2P", position_p2_top2, true, 12, 0, 0, Alignment_Center, false);

                if (CompPlus_Scoring::P2_LastPlacement == 1) 
                {
                    Drawing::DrawDevTextSprite(GetPosition(2), position_p2, true, 12, 0, 0, Alignment_Center, true);
                    DrawCrownSprite(Player2, position_p2_top, false);
                }
                else 
                {
                    Drawing::DrawDevTextSprite(GetPosition(2), position_p2, true, 12, 0, 0, Alignment_Center, false);
                }
            }
            if (Player3.Camera != nullptr)
            {

                Vector2 position_p3 = Vector2((SonicMania::Player3.Position.X - GetPointer(0xAA7628, 0x96000 + offset)) - 11, (Player3.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) + Player3Box.Top + Player3Box.Bottom + 24);
                Vector2 position_p3_top = Vector2((SonicMania::Player3.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player3.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) - Player3Box.Top - Player3Box.Bottom - 45);
                Vector2 position_p3_top2 = Vector2((SonicMania::Player3.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player3.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) - Player3Box.Top - Player3Box.Bottom - 24);
                Drawing::DrawDevTextSprite("3P", position_p3_top2, true, 12, 0, 0, Alignment_Center, false);
                
                if (CompPlus_Scoring::P3_LastPlacement == 1)
                {
                    Drawing::DrawDevTextSprite(GetPosition(3), position_p3, true, 12, 0, 0, Alignment_Center, true);
                    DrawCrownSprite(Player3, position_p3_top, false);
                }
                else 
                {
                    Drawing::DrawDevTextSprite(GetPosition(3), position_p3, true, 12, 0, 0, Alignment_Center, false);
                }
            }
            if (Player4.Camera != nullptr)
            {
                Vector2 position_p4 = Vector2((SonicMania::Player4.Position.X - GetPointer(0xAA7628, 0x96000 + offset)) - 11, (Player4.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) + Player4Box.Top + Player4Box.Bottom + 24);
                Vector2 position_p4_top = Vector2((SonicMania::Player4.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player4.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) - Player4Box.Top - Player4Box.Bottom - 45);
                Vector2 position_p4_top2 = Vector2((SonicMania::Player4.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player4.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)) - Player4Box.Top - Player4Box.Bottom - 24);
                Drawing::DrawDevTextSprite("4P", position_p4_top2, true, 12, 0, 0, Alignment_Center, false);
                
                if (CompPlus_Scoring::P4_LastPlacement == 1)
                {
                    Drawing::DrawDevTextSprite(GetPosition(4), position_p4, true, 12, 0, 0, Alignment_Center, true);
                    DrawCrownSprite(Player4, position_p4_top, false);
                }
                else 
                {
                    Drawing::DrawDevTextSprite(GetPosition(4), position_p4, true, 12, 0, 0, Alignment_Center, false);
                }
            }

            DrawKillScreens(screen, offset);

            EndDraw(screen);
        }
        Canvas->DrawOrder = OldDrawOrder;
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