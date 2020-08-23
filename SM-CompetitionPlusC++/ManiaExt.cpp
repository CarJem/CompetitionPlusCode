#include "stdafx.h"
#include "ManiaExt.h"
#include <string>

using namespace SonicMania;

void SetScreenCount(int count) 
{
	BYTE* Pointer = *(BYTE**)((baseAddress + 0xA530FC));
	WriteData((BYTE*)baseAddress + 0xA530FC, (BYTE)count);
}


void ConvertASCII2Unicode(wchar_t* dest, char* src, size_t size, int offset)
{
	memset(dest, 0, size * 2);
	for (int i = 0; i < size; ++i)
		dest[i] = src[i] + offset;
}

bool PlayerInRange(int player, int x1, int y1, int x2, int y2)
{
	bool inRange = false;
	switch (player) {
		case 1:
			inRange = (Player1.Position.X >= x1 && Player1.Position.X <= x2) && (Player1.Position.Y >= y1 && Player1.Position.Y <= y2);
			break;
		case 2:
			inRange = (Player2.Position.X >= x1 && Player2.Position.X <= x2) && (Player2.Position.Y >= y1 && Player2.Position.Y <= y2);
			break;
		case 3:
			inRange = (Player3.Position.X >= x1 && Player3.Position.X <= x2) && (Player3.Position.Y >= y1 && Player3.Position.Y <= y2);
			break;
		case 4:
			inRange = (Player4.Position.X >= x1 && Player4.Position.X <= x2) && (Player4.Position.Y >= y1 && Player4.Position.Y <= y2);
			break;
		default:
			break;
	}
	return inRange;
}

bool PlayerInRange(EntityPlayer* player, int x1, int y1, int x2, int y2)
{
	bool inRange = false;
	inRange = (player->Position.X >= x1 && player->Position.X <= x2) && (player->Position.Y >= y1 && player->Position.Y <= y2);
	return inRange;
}


BYTE* GetUIBGPointer()
{
	return *(BYTE**)(baseAddress + 0xAC68E4);
}

int DevFontSpriteID = 0;
bool DevFontLoaded = false;

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
		RingTemp->DrawFX = SonicMania::FX_Rotate;


		RingTemp->Rotation = Player1.Rotation;
		RingTemp->Angle = Player1.Angle;
		SetSpriteAnimation(DevFontSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
		DrawSprite(&RingTemp->ActNumbersData, &LocationStart, true);
		LocationStart.X = LocationStart.X + 8;

	}
}

void WriteColor(int offset, int r, int g, int b)
{
	unsigned int color = r << 16
		| g << 8 | b; // idk if this is reversed
	WriteData((unsigned int*)(GetUIBGPointer() + offset), color);
}

BYTE* GetUIButtonPointer(int slot)
{
	return *(BYTE**)((baseAddress + 0x0047B010) + (slot * 0x458));
}

void SetUIPictureFrame(int slotID, int frameID)
{
	WriteData(GetEntityFromSceneSlot<BYTE>(slotID) + 0x70, (BYTE)frameID);
}

void SetUIBG_BGColor(int r, int g, int b)
{
	WriteColor(4, r, g, b);
}
void SetUIBG_FGLowColor(int r, int g, int b)
{
	WriteColor(8, r, g, b);
}

void SetUIBG_FGHighColor(int r, int g, int b)
{
	WriteColor(12, r, g, b);
}

EntityUIPicture* GetEntity(int slotID)
{
	return GetEntityFromSceneSlot<EntityUIPicture>(slotID);
}