#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "SonicMania.h"
#include <string>






/*
dd is DWORD
dw is WORD
db is BYTE
*/
DataPointer(int, FrameMultiplier, 0x2680A4);

extern SonicMania::EntityPlayer GetPlayer(int RealID);
extern void DrawTextSprite(std::string Name, SonicMania::Vector2 LocationStart, bool ScreenRelative);
extern void SetUIPictureFrame(int slotID, int frameID);
extern SonicMania::EntityUIPicture* GetEntity(int slotID);
