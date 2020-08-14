#include "stdafx.h"
#include "ManiaExt.h"

using namespace SonicMania;

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