#include "stdafx.h"
#include "PlayerSettings.h"
#include "include/ManiaAPI/SonicMania.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "Base.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include <string>
#include "CompPlus_Core/CompPlus_Patches.h"
#include "CompPlus_Extensions/Drawing.h"

namespace CompPlus_PlayerSettings
{
	using namespace SonicMania;
	using namespace CompPlus_Core;
	using namespace CompPlus_Common;

	bool IsInit = false;
	bool CanDraw = false;
    bool SpritesLoaded = false;

    int HUDSpriteID = 0;

    int Player1_X = 0;
    int Player1_Y = 0;

    int Player2_X = 0;
    int Player2_Y = 0;

    int Player3_X = 0;
    int Player3_Y = 0;

    int Player4_X = 0;
    int Player4_Y = 0;

    void DrawCommonSprite(int SpriteID, int AnimID, int FrameID, Vector2 LocationStart, bool ScreenRelative, int DrawOrder, int Rotation, int Angle)
    {
        EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);;

        RingTemp->DrawOrder = DrawOrder;
        RingTemp->DrawFX = SonicMania::DrawingFX_Rotate;
        RingTemp->Rotation = Rotation;
        RingTemp->Angle = Angle;
        SetSpriteAnimation(SpriteID, AnimID, &RingTemp->ActNumbersData, true, FrameID);
        DrawSprite(&RingTemp->ActNumbersData, &LocationStart, ScreenRelative);
    }


    void DrawPlayer1Values(int x, int y)
    {
        int CurrentY = y + 72;

        int IconOffsetY = 8;

        int RectWidths = 200;
        int RectHeights = 14;
        int TextShiftX = RectWidths - 5;

        DrawCommonSprite(HUDSpriteID, 2, 0, Vector2(x + TextShiftX - 18, CurrentY + 7 + IconOffsetY), true, 14, 0, 0);
        CurrentY += 28;
        DrawCommonSprite(HUDSpriteID, 2, 0, Vector2(x + TextShiftX - 18, CurrentY + 7 + IconOffsetY), true, 14, 0, 0);
        CurrentY += 28;
        Drawing::DrawMenuTextSprite("ON", Vector2(x + TextShiftX, CurrentY), true, 14, 0, 0, Alignment_Left);
        CurrentY += 16;
        Drawing::DrawMenuTextSprite("ON", Vector2(x + TextShiftX, CurrentY + 7), true, 14, 0, 0, Alignment_Left);
        CurrentY += 28;
        CurrentY += 32;
        CurrentY += RectHeights;
    }

    void DrawSet(int x, int y, int PlayerID) 
    {
        int CurrentY = y;

        int RectWidths = 200;
        int RectHeights = 14;
        int TextShiftX = 5;


        std::string Title = "PLAYER WLRD";
        if (PlayerID == 1) Title = "PLAYER 1";
        else if (PlayerID == 2) Title = "PLAYER 2";
        else if (PlayerID == 3) Title = "PLAYER 3";
        else if (PlayerID == 4) Title = "PLAYER 4";

        DrawRect(x, CurrentY - (RectHeights / 2), RectWidths, RectHeights, 0x000000, 255, Ink_Alpha, true);
        Drawing::DrawMenuTextSprite(Title, Vector2(x + (RectWidths / 2), CurrentY), true, 14, 0, 0, Alignment_Center);
        CurrentY += 72;
        DrawRect(x, CurrentY - (RectHeights / 2), RectWidths, RectHeights, 0x000000, 255, Ink_Alpha, true);
        Drawing::DrawMenuTextSprite("CURRENT", Vector2(x + TextShiftX, CurrentY), true, 14, 0, 0, Alignment_Right);
        CurrentY += 12;
        DrawRect(x, CurrentY - (RectHeights / 2), RectWidths, RectHeights, 0x000000, 255, Ink_Alpha, true);
        Drawing::DrawMenuTextSprite("CHARACTER", Vector2(x + TextShiftX, CurrentY), true, 14, 0, 0, Alignment_Right);
        CurrentY += 16;
        DrawRect(x, CurrentY - (RectHeights / 2), RectWidths, RectHeights, 0x000000, 255, Ink_Alpha, true);
        Drawing::DrawMenuTextSprite("CURRENT", Vector2(x + TextShiftX, CurrentY), true, 14, 0, 0, Alignment_Right);
        CurrentY += 12;
        DrawRect(x, CurrentY - (RectHeights / 2), RectWidths, RectHeights, 0x000000, 255, Ink_Alpha, true);
        Drawing::DrawMenuTextSprite("ABILITY", Vector2(x + TextShiftX, CurrentY), true, 14, 0, 0, Alignment_Right);
        CurrentY += 16;
        DrawRect(x, CurrentY - (RectHeights / 2), RectWidths, RectHeights, 0x000000, 255, Ink_Alpha, true);
        Drawing::DrawMenuTextSprite("PEELOUT", Vector2(x + TextShiftX, CurrentY), true, 14, 0, 0, Alignment_Right);
        CurrentY += 16;
        DrawRect(x, CurrentY - (RectHeights / 2), RectWidths, RectHeights, 0x000000, 255, Ink_Alpha, true);
        Drawing::DrawMenuTextSprite("DYNAMIC", Vector2(x + TextShiftX, CurrentY), true, 14, 0, 0, Alignment_Right);
        CurrentY += 12;
        DrawRect(x, CurrentY - (RectHeights / 2), RectWidths, RectHeights, 0x000000, 255, Ink_Alpha, true);
        Drawing::DrawMenuTextSprite("CAMERA", Vector2(x + TextShiftX, CurrentY), true, 14, 0, 0, Alignment_Right);
        CurrentY += 16;
        CurrentY += 32;
        DrawRect(x, CurrentY - (RectHeights / 2), RectWidths, RectHeights, 0x000000, 255, Ink_Alpha, true);
        Drawing::DrawMenuTextSprite("OK", Vector2(x + (RectWidths / 2), CurrentY), true, 14, 0, 0, Alignment_Center);
        CurrentY += RectHeights;

        int BoxHeight = CurrentY - y;
        int BorderThickness = 2;

        DrawRect(x - BorderThickness, y - (RectHeights / 2) - BorderThickness, RectWidths + BorderThickness, BorderThickness, 0x000000, 255, Ink_Alpha, true);
        DrawRect(x - BorderThickness, y - (RectHeights / 2) - BorderThickness, BorderThickness, BorderThickness + BoxHeight + BorderThickness, 0x000000, 255, Ink_Alpha, true);
        DrawRect(x + RectWidths, y - (RectHeights / 2) - BorderThickness, BorderThickness, BorderThickness + BoxHeight, 0x000000, 255, Ink_Alpha, true);
        DrawRect(x, CurrentY - (RectHeights / 2), RectWidths + BorderThickness, BorderThickness, 0x000000, 255, Ink_Alpha, true);

        if (PlayerID == 1) DrawPlayer1Values(x, y);
        //else if (PlayerID == 2) DrawPlayer2Values(x, y);
        //else if (PlayerID == 3) DrawPlayer3Values(x, y);
        //else if (PlayerID == 4) DrawPlayer4Values(x, y);
    }

    void LoadSprites() 
    {
        if (!SpritesLoaded) 
        {
            HUDSpriteID = LoadAnimation("Global/HUD.bin", Scope_Stage);
            SpritesLoaded = true;
        }
    }

	void DoMenuOnScreenDraw()
	{
		if (CanDraw) 
		{
            LoadSprites();
            DrawSet(5, 10, 1);
            //DrawSet(5 + 105, 10, 2);
            //DrawSet(5 + 105 * 2, 10, 3);
            //DrawSet(5 + 105 * 3, 10, 4);
		}
	}

	void OnFrame()
	{
        CanDraw = true;
	}

    void Reload() 
    {
        SpritesLoaded = false;
    }
};