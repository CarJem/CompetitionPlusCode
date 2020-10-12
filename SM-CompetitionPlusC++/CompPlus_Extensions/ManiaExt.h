#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "SonicMania.h"
#include <string>



struct FBZStorm : SonicMania::Entity
{
    /* 0x00000058 */ BYTE State;
    /* 0x00000059 */ BYTE DrawState;
    /* 0x0000005A */ BYTE Something1;
    /* 0x0000005B */ BYTE Something2;
    /* 0x0000005C */ BYTE LightningTimer;

};

struct SpecialRing : SonicMania::Entity
{
    /* 0x00000058 */ BYTE Field_58;
    /* 0x00000059 */ BYTE Field_59;
    /* 0x0000005A */ BYTE Field_5A;
    /* 0x0000005B */ BYTE Field_5B;
    /* 0x0000005C */ BYTE ID;
    /* 0x0000005E */ BYTE Gap_5E[6];
    /* 0x00000064 */ DWORD PlaneFilter;
    /* 0x00000068 */ BYTE Gap_68[18];
    /* 0x0000007A */ BYTE TriggeredState;
    /* 0x0000007B */ BYTE Gap_7B[17];
    /* 0x0000008C */ bool Enabled;
};

/*
dd is DWORD
dw is WORD
db is BYTE
*/
DataPointer(int, FrameMultiplier, 0x2680A4);


extern bool DevFontLoaded;

extern void WarpWithCamera(SonicMania::EntityPlayer& Player, int x, int y);
extern bool IsPlayerActive(SonicMania::EntityPlayer Player);
extern SonicMania::EntityPlayer GetPlayer(int RealID);
extern void DrawTextSprite(SonicMania::EntityPlayer Player, std::string Name, SonicMania::Vector2 LocationStart, bool ScreenRelative);
extern void DrawTextSprite(std::string Name, SonicMania::Vector2 LocationStart, bool ScreenRelative);
extern void SetUIPictureFrame(int slotID, int frameID);
extern SonicMania::EntityUIPicture* GetEntity(int slotID);
