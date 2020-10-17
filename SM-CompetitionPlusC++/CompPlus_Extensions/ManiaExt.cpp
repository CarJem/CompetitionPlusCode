#include "stdafx.h"
#include "ManiaExt.h"
#include <string>

using namespace SonicMania;



int DevFontSpriteID = 0;
bool DevFontLoaded = false;


SonicMania::EntityPlayer GetPlayer(int RealID) 
{
    switch (RealID) 
    {
        case 1:
            return SonicMania::Player1;
        case 2:
            return SonicMania::Player2;
        case 3:
            return SonicMania::Player3;
        case 4:
            return SonicMania::Player4;
        default:
            return SonicMania::Player1;
    }
}


void WarpWithCamera(SonicMania::EntityPlayer& Player, int x, int y)
{
    Player.Position.X = x;
    Player.Position.Y = y;

    if (Player.Camera != nullptr) 
    {
        Player.Camera->Position.X = x;
        Player.Camera->Position.Y = y;
        Player.Camera->LastXPos = x;
        Player.Camera->LastYPos = y;
        Player.Camera->PanToPositionSTart.X = x;
        Player.Camera->PanToPositionSTart.Y = y;
        Player.Camera->PanToPositionEnd.X = x;
        Player.Camera->PanToPositionEnd.Y = y;
    }
}


bool IsPlayerActive(SonicMania::EntityPlayer Player) 
{
    return (Player.Camera != nullptr && Player.Grounded && Player.XVelocity == 0 && Player.YVelocity == 0);
}

void DrawTextSprite(SonicMania::EntityPlayer Player, std::string Name, Vector2 LocationStart, bool ScreenRelative)
{
    if (!DevFontLoaded)
    {
        DevFontSpriteID = LoadAnimation("Dev/Font.bin", Scope_Global);
        DevFontLoaded = true;
        return;
    }


    if (ScreenRelative)
    {
        int x = SonicMania::OBJ_Camera->XPos;
        int y = SonicMania::OBJ_Camera->YPos;

        LocationStart = Vector2(x + LocationStart.GetFullX(), y + LocationStart.GetFullY());
    }


    int SpriteFrame = 0;
    int BuildLength = 0;
    EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);;
    for (int i = 0; i < Name.length(); i++)
    {
        SpriteFrame = int(Name[i]);

        BuildLength = BuildLength + 8;


    }
    //LocationStart.X = LocationStart.X - BuildLength;
    //Offset lenth to build to our point. 

    for (int i = 0; i < Name.length(); i++)
    {
        SpriteFrame = int(Name[i]);
        RingTemp->DrawOrder = Player.DrawOrder;
        RingTemp->DrawFX = SonicMania::DrawingFX_Rotate;
        RingTemp->Rotation = Player.Rotation;
        RingTemp->Angle = Player.Angle;
        EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);;
        SetSpriteAnimation(DevFontSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
        DrawSprite(&RingTemp->ActNumbersData, &LocationStart, true);
        LocationStart.X = LocationStart.X + 8;

    }
}

void DrawTextSprite(std::string Name, Vector2 LocationStart, bool ScreenRelative)
{
	if (!DevFontLoaded) 
	{
		DevFontSpriteID = LoadAnimation("Dev/Font.bin", Scope_Global);
		DevFontLoaded = true;
		return;
	}

	
	if (ScreenRelative) 
	{
		int x = SonicMania::OBJ_Camera->XPos;
		int y = SonicMania::OBJ_Camera->YPos;

		LocationStart = Vector2(x, y);
	}
	

	int SpriteFrame = 0;
	int BuildLength = 0;
	EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);;
	for (int i = 0; i < Name.length(); i++)
	{
		SpriteFrame = int(Name[i]);

		BuildLength = BuildLength + 8;


	}
	//LocationStart.X = LocationStart.X - BuildLength;
	//Offset lenth to build to our point. 

	for (int i = 0; i < Name.length(); i++)
	{
		SpriteFrame = int(Name[i]);
		RingTemp->DrawOrder = Player1.DrawOrder;
		RingTemp->DrawFX = SonicMania::DrawingFX_Rotate;
		RingTemp->Rotation = Player1.Rotation;
		RingTemp->Angle = Player1.Angle;
		SetSpriteAnimation(DevFontSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
		DrawSprite(&RingTemp->ActNumbersData, &LocationStart, true);
		LocationStart.X = LocationStart.X + 8;

	}
}

void DrawTextSprite(std::string Name, Vector2 LocationStart, bool ScreenRelative, int DrawOrder = 0, int Rotation = 0, int Angle = 0, DevMenu_Alignment Alignment = Alignment_Right)
{
    if (!DevFontLoaded)
    {
        DevFontSpriteID = LoadAnimation("Dev/Font.bin", Scope_Global);
        DevFontLoaded = true;
        return;
    }


    int SpriteFrame = 0;
    int BuildLength = 0;
    EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);;
    for (int i = 0; i < Name.length(); i++)
    {
        SpriteFrame = int(Name[i]);

        BuildLength = BuildLength + 8;
    }
    if (Alignment == DevMenu_Alignment::Alignment_Left) LocationStart.X = LocationStart.X - BuildLength;
    else if (Alignment == DevMenu_Alignment::Alignment_Center) LocationStart.X = LocationStart.X - (BuildLength != 0 ? (BuildLength / 2) : 0);
    //Offset lenth to build to our point. 

    for (int i = 0; i < Name.length(); i++)
    {
        SpriteFrame = int(Name[i]);
        RingTemp->DrawOrder = DrawOrder;
        RingTemp->DrawFX = SonicMania::DrawingFX_Rotate;
        RingTemp->Rotation = Rotation;
        RingTemp->Angle = Angle;
        SetSpriteAnimation(DevFontSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
        DrawSprite(&RingTemp->ActNumbersData, &LocationStart, ScreenRelative);
        LocationStart.X = LocationStart.X + 8;

    }
}


BYTE* GetUIButtonPointer(int slot)
{
	return *(BYTE**)((baseAddress + 0x0047B010) + (slot * 0x458));
}

void SetUIPictureFrame(int slotID, int frameID)
{
	WriteData(GetEntityFromSceneSlot<BYTE>(slotID) + 0x70, (BYTE)frameID);
}


EntityUIPicture* GetEntity(int slotID)
{
	return GetEntityFromSceneSlot<EntityUIPicture>(slotID);
}