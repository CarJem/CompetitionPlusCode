#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "SonicMania.h"
#include <string>


namespace SonicMania
{
	FunctionPointer(__int16, CreateObject, (SonicMania::Object* ObjectStruct, const char* ObjectName, unsigned int EntitySize, int ObjSize,
		void (*Update)(), void (*LateUpdate)(), void* EarlyUpdate, void* Draw, void* Startup, void* StageLoad, int a11, int a12,
		void* GetAttributes), 0x1D3090);

	// ADDITIONS
	DataArray(unsigned short, Framebuffer, 0x6ECA88, 432 * 240);		// 424x240 display

	DataPointer(float, StreamVolume, 0xA53078);
	DataPointer(float, SFXVolume, 0xA5307C);

	DataPointer(DWORD*, ScreenInfo, 0xAA7628);
}

// Music struct
struct struct_0
{
	int anonymous_0;
	int anonymous_1;
	float volume;
	int anonymous_3;
	int anonymous_4;
	int anonymous_5;
	int anonymous_6;
	int hasLoop;
	__int16 anonymous_8;
	_BYTE gap22[1];
	char playStatus;
};
DataArray(struct_0, stru_26B818, 0x0026B818, 16);


/*
dd is DWORD
dw is WORD
db is BYTE
*/

struct ObjectUIPicture : SonicMania::Object
{
	/* 0x00000004 */ WORD SpriteIndex;
};

struct ObjectUIText : SonicMania::Object
{
	/* 0x00000004 */ WORD SpriteIndex;
};

struct EntityUIPicture : SonicMania::Entity
{
	/* 0x00000058 */ DWORD ListID;
	/* 0x0000005C */ DWORD FrameID;
	/* 0x00000060 */ DWORD Tag;
	/* 0x00000064 */ BYTE ZonePalette;
	/* 0x00000065 */ BYTE field_65;
	/* 0x00000066 */ BYTE field_66;
	/* 0x00000067 */ BYTE field_67;
	/* 0x00000068 */ DWORD ZoneID;
	/* 0x0000006C */ SonicMania::EntityAnimationData AnimData;
};

struct EntityUIInfoLabel : SonicMania::Entity
{
	/* 0x00000058 */ SonicMania::EntityAnimationData AnimData;
	/* 0x00000070 */ BYTE field_70;
	/* 0x00000071 */ BYTE field_71;
	/* 0x00000072 */ BYTE field_72;
	/* 0x00000073 */ BYTE field_73;
	/* 0x00000074 */ BYTE field_74;
	/* 0x00000075 */ BYTE field_75;
	/* 0x00000076 */ BYTE field_76;
	/* 0x00000077 */ BYTE field_77;
	/* 0x00000078 */ SonicMania::Vector2 Size;
	/* 0x00000080 */ wchar_t* Text;
	/* 0x00000084 */ WORD TextLength;
	/* 0x00000086 */ BYTE field_86;
	/* 0x00000087 */ BYTE field_87;
	/* 0x00000088 */ DWORD field_88;
	/* 0x0000008C */ SonicMania::EntityAnimationData AnimData2;
};

struct EntityUITextPrivate : SonicMania::Entity
{
	/* 0x00000058 */ void* State;
	/* 0x0000005C */ void* StateDraw;
	/* 0x00000060 */ DWORD Text;
	/* 0x00000064 */ WORD field_64;
	/* 0x00000066 */ WORD field_66;
	/* 0x00000068 */ DWORD Tag;
	/* 0x0000006C */ DWORD field_6C;
	/* 0x00000070 */ DWORD Selectable;
	/* 0x00000074 */ WORD AnimListID;
	/* 0x00000076 */ WORD gap76;
	/* 0x00000078 */ DWORD Align;
	/* 0x0000007C */ DWORD Data0;
	/* 0x00000080 */ DWORD Data1;
	/* 0x00000084 */ DWORD Data2;
	/* 0x00000088 */ DWORD  Data3;
	/* 0x0000008C */ DWORD Highlighted;
	/* 0x00000090 */ SonicMania::EntityAnimationData  AnimData;
};

struct Button : SonicMania::Entity
{
	/* 0x00000058 */ DWORD field_58;
	/* 0x0000005C */ DWORD field_5C;
	/* 0x00000060 */ DWORD field_60;
	/* 0x00000064 */ WORD field_64;
	/* 0x00000066 */ WORD field_66;
	/* 0x00000068 */ bool Pressed;
};

//int UIBackgroundMainOffset = 0xAC68E4;



extern void SetScreenCount(int count);
extern void ConvertASCII2Unicode(wchar_t* dest, char* src, size_t size, int offset);
extern void DrawTextSprite(std::string Name, SonicMania::Vector2 LocationStart, bool ScreenRelative);
extern bool PlayerInRange(int player, int x1, int y1, int x2, int y2);
extern bool PlayerInRange(SonicMania::EntityPlayer* player, int x1, int y1, int x2, int y2);
extern BYTE* GetUIButtonPointer(int slotID);
extern BYTE* GetUIBGPointer();
extern void SetUIPictureFrame(int slotID, int frameID);
extern void SetUIBG_BGColor(int r, int g, int b);
extern void SetUIBG_FGLowColor(int r, int g, int b);
extern void SetUIBG_FGHighColor(int r, int g, int b);
extern EntityUIPicture* GetEntity(int slotID);
