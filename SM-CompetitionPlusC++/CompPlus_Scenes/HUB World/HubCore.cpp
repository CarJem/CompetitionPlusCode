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

    HubPlace ReturnDestination = HubPlace_StartPosition;
    using namespace SonicMania;

    bool isRestart = true;

    int HUDSpriteID = 0;
    bool HUDSpriteLoaded = false;

    Hitbox Player1Box;
    Hitbox Player2Box;
    Hitbox Player3Box;
    Hitbox Player4Box;

    void DrawCrownSprite(Vector2 LocationStart, bool ScreenRelative, int DrawOrder, int Rotation, int Angle)
    {
        if (!HUDSpriteLoaded)
        {
            HUDSpriteID = LoadAnimation(CompPlus_Common::Anim_HubCrown, Scope_Stage);
            HUDSpriteLoaded = true;
            return;
        }

        int SpriteFrame = 0;
        EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);;

        RingTemp->DrawOrder = DrawOrder;
        RingTemp->DrawFX = SonicMania::DrawingFX_Rotate;
        RingTemp->Rotation = Rotation;
        RingTemp->Angle = Angle;
        SetSpriteAnimation(HUDSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
        DrawSprite(&RingTemp->ActNumbersData, &LocationStart, true);
    }

    char* GetPlayerID(int PlayerID)
    {
        if (PlayerID == 1) return (char*)"1P";
        else if (PlayerID == 2) return (char*)"2P";
        else if (PlayerID == 3) return (char*)"3P";
        else if (PlayerID == 4) return (char*)"4P";
        else return (char*)"WORLD";
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

    void DrawPlayerHUD(Vector2 PlayerPosition, int offset, int LastPlacement, int PlayerID, int DrawOrder, Hitbox Hitbox)
    {
        Vector2 Position = Vector2((PlayerPosition.X - GetPointer(0xAA7628, 0x96000 + offset)), (PlayerPosition.Y - GetPointer(0xAA7628, 0x96004 + offset)));

        Vector2 TextPosition = Vector2(Position.X, Position.Y + Hitbox.Top + Hitbox.Bottom + 24);
        Vector2 CrownPosition = Vector2(Position.X, Position.Y - Hitbox.Top - Hitbox.Bottom - 45);
        Vector2 PlayerIDPosition = Vector2(Position.X, Position.Y - Hitbox.Top - Hitbox.Bottom - 24);
        Drawing::DrawDevTextSprite(GetPlayerID(PlayerID), PlayerIDPosition, true, DrawOrder, 0, 0, Alignment_Center, false);

        if (LastPlacement == 1)
        {
            Drawing::DrawDevTextSprite(GetPosition(PlayerID), TextPosition, true, DrawOrder, 0, 0, Alignment_Center, true);
            DrawCrownSprite(CrownPosition, false, DrawOrder, 0, 0);
        }
        else
        {
            Drawing::DrawDevTextSprite(GetPosition(PlayerID), TextPosition, true, DrawOrder, 0, 0, Alignment_Center, false);
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

        int offset = 0x96030 * screen;

        DrawWaitingForPlayers(offset);

        if (Player1.Camera != nullptr) DrawPlayerHUD(Player1.Position, offset, CompPlus_Scoring::P1_LastPlacement, 1, 14, Player1Box);
        if (Player2.Camera != nullptr) DrawPlayerHUD(Player2.Position, offset, CompPlus_Scoring::P2_LastPlacement, 2, 14, Player2Box);
        if (Player3.Camera != nullptr) DrawPlayerHUD(Player3.Position, offset, CompPlus_Scoring::P3_LastPlacement, 3, 14, Player3Box);
        if (Player4.Camera != nullptr) DrawPlayerHUD(Player4.Position, offset, CompPlus_Scoring::P4_LastPlacement, 4, 14, Player4Box);

        DrawKillScreens(screen, offset);
    }

    void SetHUBVisualSettings()
    {
        if (isRestart) 
        {
            if (Player1.Camera != nullptr) Hitbox Player1Box = *GetHitbox(&Player1.Animation, 1);
            if (Player2.Camera != nullptr) Hitbox Player2Box = *GetHitbox(&Player2.Animation, 1);
            if (Player3.Camera != nullptr) Hitbox Player3Box = *GetHitbox(&Player3.Animation, 1);
            if (Player4.Camera != nullptr) Hitbox Player4Box = *GetHitbox(&Player4.Animation, 1);
            HUDSpriteLoaded = false;
            isRestart = false;
        }

        //Stop Countdown
        SonicMania::Timer.Enabled = true;

        //Disable Timer
        SonicMania::Timer.ResetTimer();

        //Player Life Count Infinite
        SonicMania::Player1.LifeCount = 100;
        SonicMania::Player2.LifeCount = 100;
        SonicMania::Player3.LifeCount = 100;
        SonicMania::Player4.LifeCount = 100;
    }

    void UnloadDrawables() 
    {
        HUDSpriteLoaded = false;
    }
}