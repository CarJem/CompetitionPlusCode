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

void DrawTextSprite(std::string Name, Vector2 LocationStart, bool ScreenRelative)
{
	if (!DevFontLoaded) 
	{
		DevFontSpriteID = LoadAnimation("Dev/Font.bin", Scope_Global);
		DevFontLoaded = true;
		return;
	}

	/*
	if (ScreenRelative) 
	{
		int x = SonicMania::OBJ_Camera->XPos;
		int y = SonicMania::OBJ_Camera->YPos;

		LocationStart = Vector2(x + LocationStart.GetFullX(), y + LocationStart.GetFullY());
	}
	*/

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