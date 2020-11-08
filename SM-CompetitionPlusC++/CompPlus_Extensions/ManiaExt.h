#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "include/ManiaAPI/SonicMania.h"
#include <string>
#include <vector>


struct FBZStorm : SonicMania::Entity
{
    /* 0x00000058 */ void* State;
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


extern void StorePalette(std::string filepath, SHORT(&PaletteStorage)[256], int& PaletteStorage_Length);
extern void WarpWithCamera(SonicMania::EntityPlayer& Player, int x, int y);
extern bool IsPlayerActive(SonicMania::EntityPlayer Player);
extern SonicMania::EntityPlayer GetPlayer(int RealID);
extern void SetUIPictureFrame(int slotID, int frameID);
extern SonicMania::EntityUIPicture* GetEntity(int slotID);
