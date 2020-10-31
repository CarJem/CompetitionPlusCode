#include "stdafx.h"
#include "ManiaExt.h"
#include <string>
#include <vector>

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
        Player.CameraOffset = 0;
        //Player.Camera->PanType = 1;
        Player.Camera->Position.X = x;
        Player.Camera->Position.Y = y;
        //Player.Camera->BoundPanningSpeedX = INT_MAX;
        //Player.Camera->BoundPanningSpeedY = INT_MAX;
        //Player.Camera->PanSpeed = INT_MAX;
        //Player.Camera->PanProgress = INT_MAX;
        //Player.Camera->MinX = INT_MIN;
        //Player.Camera->MinY = INT_MIN;
        //Player.Camera->MaxX = INT_MAX;
        //Player.Camera->MaxY = INT_MAX;
        //Player.Camera->AdjustY = 0;
        //Player.Camera->DestinationOffsetX = 0;
        //Player.Camera->DestinationOffsetY = 0;
        Player.Camera->LastXPos = x;
        Player.Camera->LastYPos = y;
        //Player.Camera->XVelocity = INT_MAX;
       // Player.Camera->YVelocity = INT_MAX;
        Player.Camera->PanToPositionSTart.X = x;
        Player.Camera->PanToPositionSTart.Y = y;
        Player.Camera->PanToPositionEnd.X = x;
        Player.Camera->PanToPositionEnd.Y = y;
    }
}

void StorePalette(std::string filepath, SHORT(&PaletteStorage)[256], int& PaletteStorage_Length)
{
    unsigned int size = 0;
    FILE* file;
    fopen_s(&file, filepath.c_str(), "rb");
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    char* act = (char*)malloc(size);
    fseek(file, 0, SEEK_SET);
    fread(act, 1, size, file);

    int actCount = size / 3;
    memset(PaletteStorage, 0, sizeof(PaletteStorage));

    for (int i = 0; i < actCount; ++i)
    {
        int red = (BYTE)act[i * 3 + 0];
        int green = (BYTE)act[i * 3 + 1];
        int blue = (BYTE)act[i * 3 + 2];
        PaletteStorage[i] = SonicMania::ToRGB565(red, green, blue);
    }
    PaletteStorage_Length = actCount;
    delete act;
}


bool IsPlayerActive(SonicMania::EntityPlayer Player) 
{
    return (Player.Camera != nullptr && Player.Grounded && Player.XVelocity == 0 && Player.YVelocity == 0);
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