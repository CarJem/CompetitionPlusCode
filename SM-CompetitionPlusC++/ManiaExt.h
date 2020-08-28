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

struct EntityUIButton : SonicMania::Entity {
	/* 00000058 */ DWORD field_58;
	/* 0000005C */ DWORD dword5C;
	/* 00000060 */ DWORD dword60;
	/* 00000064 */ DWORD field_64;
	/* 00000068 */ DWORD dword68;
	/* 0000006C */ DWORD dword6C;
	/* 00000070 */ DWORD dword70;
	/* 00000074 */ DWORD dword74;
	/* 00000078 */ DWORD dword78;
	/* 0000007C */ DWORD dword7C;
	/* 00000080 */ BYTE gap80[128];
	/* 00000100 */ DWORD Disabled;
	/* 00000104 */ SonicMania::Vector2 Size;
	/* 0000010C */ DWORD ListID;
	/* 00000110 */ DWORD FrameID;
	/* 00000114 */ DWORD Align;
	/* 00000118 */ DWORD ChoiceCount;
	/* 0000011C */ DWORD ChoiceDir;
	/* 0000011D */ DWORD Unused1;
	/* 0000011E */ DWORD Unused2;
	/* 0000011F */ DWORD Unused3;
	/* 00000120 */ DWORD Invisible;
	/* 00000124 */ DWORD AlignsP1;
	/* 00000128 */ DWORD FreeBindP2;
	/* 0000012C */ DWORD Transition;
	/* 00000130 */ DWORD StopMusic;
	/* 00000134 */ DWORD field_134;
	/* 00000138 */ DWORD dword138;
	/* 0000013C */ BYTE gap13C[16];
	/* 0000014C */ DWORD dword14C;
	/* 00000150 */ BYTE gap150[20];
	/* 00000164 */ SonicMania::EntityAnimationData entityanimationdata164l;
	/* 0000017C */ WORD word17C;
	/* 0000017E */ BYTE field_17E;
	/* 0000017F */ BYTE field_17F;
	/* 00000180 */ DWORD dword180;
	/* 00000184 */ DWORD dword184;
};

struct EntityUIVsRoundPicker : SonicMania::Entity
{
	/* 00000058 */ DWORD gap58;
	/* 0000005C */ DWORD dword5C;
	/* 00000060 */ DWORD dword60;
	/* 00000064 */ BYTE Unknown1[156];
	/* 00000100 */ DWORD Disabled;    
	/* 00000104 */ SonicMania::Vector2 Size;
	/* 0000010C */ DWORD Align;
	/* 00000110 */ DWORD ArrowWidth;
	/* 00000114 */ DWORD Val;
	/* 00000118 */ DWORD MaxVal;
	/* 0000011C */ BYTE gap11C[4];     
	/* 00000120 */ DWORD dword120;
	/* 00000124 */ BYTE gap124[16];         
	/* 00000134 */ DWORD dword134;
	/* 00000138 */ BYTE gap138[12];         
	/* 00000144 */ SonicMania::EntityAnimationData AnimData1;
	/* 0000015C */ SonicMania::EntityAnimationData AnimData2;
	/* 00000174 */ SonicMania::EntityAnimationData AnimData3;
	/* 0000018C */ SonicMania::EntityAnimationData AnimData4;
	/* 000001A4 */ WORD word1A4;
	/* 000001A6 */ BYTE field_1A6;
	/* 000001A7 */ BYTE field_1A7;
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
	/* 0x00000084 */ int TextLength;
	/* 0x00000086 */ BYTE field_86;
	/* 0x00000087 */ BYTE field_87;
	/* 0x00000088 */ DWORD field_88;
	/* 0x0000008C */ SonicMania::EntityAnimationData AnimData2;
};

struct EntityUITextPrivate : SonicMania::Entity
{
	/* 0x00000058 */ void* State;
	/* 0x0000005C */ void* StateDraw;
	/* 0x00000060 */ wchar_t* Text;
	/* 0x00000064 */ WORD TextLength;
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

/*
dd is DWORD
dw is WORD
db is BYTE
*/

struct EntityUIControl : SonicMania::Entity
{
    /* 0x00000058 */ DWORD field_58;
    /* 0x0000005C */ DWORD field_5C;
    /* 0x00000060 */ DWORD SelectedElement;
    /* 0x00000064 */ DWORD Tag;
    /* 0x00000068 */ DWORD field_68;
    /* 0x0000006C */ DWORD parentTag;
    /* 0x00000070 */ DWORD field_70;
    /* 0x00000074 */ DWORD ActiveOnLoad;
    /* 0x00000078 */ DWORD NoWidgets;
    /* 0x0000007C */ DWORD ResetSelection;
    /* 0x00000080 */ BYTE field_80;
    /* 0x00000081 */ BYTE byte81;
    /* 0x00000082 */ BYTE RowCount;
    /* 0x00000083 */ BYTE ColumnCount;
    /* 0x00000084 */ BYTE StartingID;
    /* 0x00000085 */ DWORD field_85;
    /* 0x00000086 */ DWORD field_86;
    /* 0x00000087 */ DWORD field_87;
    /* 0x00000088 */ SonicMania::Vector2 Size;
    /* 0x00000090 */ SonicMania::Vector2 CameraOffset;
    /* 0x00000098 */ SonicMania::Vector2 ScrollSpeed;
    /* 0x000000A0 */ DWORD NoClamp;
    /* 0x000000A4 */ DWORD NoWrap;
    /* 0x000000A8 */ DWORD dwordA;
    /* 0x000000AC */ DWORD dwordAC;
    /* 0x000000B0 */ DWORD gapB0[20];
    /* 0x000000C4 */ DWORD dwordC4;
    /* 0x000000C8 */ DWORD gapC8[4];
    /* 0x000000CC */ DWORD dwordCC;
    /* 0x000000D0 */ DWORD gapD0[4];
    /* 0x000000D4 */ DWORD dwordD4;
    /* 0x000000D8 */ DWORD field_D8[336];
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
