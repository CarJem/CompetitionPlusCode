#include "stdafx.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "SonicMania.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include"CompPlus_Core/CompPlus_Status.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include <string>
#include <sstream>
#include "CompPlus_Core/CompPlus_Scoring.h"
#include "HubCore.h"
#include "HubText.h"
#include "HubControllers.h"
#include "HubWorld.h"

namespace CompPlus_HubWorld
{
    #pragma region Variables

    int SwapLevelSelectController = 88;
    int SwapLevelSelectController2 = 87;
    int VSModeTextSlot = 361;
    int WinsTallyTextSlot = 362;
    int EnterLSelectButton = 67;
    int SelectedLevelSelectText = 205;
    int RoundsCounterText = 69;

    int P1_WinsCounterText = 267;
    int P2_WinsCounterText = 268;
    int P3_WinsCounterText = 269;
    int P4_WinsCounterText = 270;

    int UIVersionTitleSlotID = 363;

    int WarpSlotID_PlayerSettings = 80;
    int WarpSlotID_OtherSettings = 81;
    int WarpSlotID_Ranking = 79;
    int WarpSlotID_LevelSelect = 75;

    int Spawnpoint_OtherSettings_ID = 68;
    int Spawnpoint_Ranking_ID = 62;
    int Spawnpoint_LevelSelect_ID = 72;
    int Spawnpoint_WarpHub_ID = 73;
    int Spawnpoint_None_ID = 439;

    int SceneWarpBounds_Settings_ID = 612;
    int SceneWarpBounds_Ranking_ID = 611;
    int SceneWarpBounds_LevelSelect_ID = 613;

    bool P1_IsInWarpRoom = false;
    bool P2_IsInWarpRoom = false;
    bool P3_IsInWarpRoom = false;
    bool P4_IsInWarpRoom = false;

    bool P1_IsInWarpLoop = false;
    bool P2_IsInWarpLoop = false;
    bool P3_IsInWarpLoop = false;
    bool P4_IsInWarpLoop = false;

    int WarpTimerMax = 512;

    int WarpTimerCurrent_P1 = 0;
    int WarpTimerCurrent_P2 = 0;
    int WarpTimerCurrent_P3 = 0;
    int WarpTimerCurrent_P4 = 0;

    int P1_WarpAlpha = 255;
    int P2_WarpAlpha = 255;
    int P3_WarpAlpha = 255;
    int P4_WarpAlpha = 255;

    CompPlus_HubCore::INT_Position Spawnpoint_StartingLine = CompPlus_HubCore::INT_Position(0, 0);
    CompPlus_HubCore::INT_Position Spawnpoint_OtherSettings = CompPlus_HubCore::INT_Position(0, 0);
    CompPlus_HubCore::INT_Position Spawnpoint_Ranking = CompPlus_HubCore::INT_Position(0, 0);
    CompPlus_HubCore::INT_Position Spawnpoint_LevelSelect = CompPlus_HubCore::INT_Position(0, 0);
    CompPlus_HubCore::INT_Position Spawnpoint_WarpHub = CompPlus_HubCore::INT_Position(0, 0);

    CompPlus_HubCore::INT_Position P1_WarpQueue = CompPlus_HubCore::INT_Position(0, 0);
    CompPlus_HubCore::INT_Position P2_WarpQueue = CompPlus_HubCore::INT_Position(0, 0);
    CompPlus_HubCore::INT_Position P3_WarpQueue = CompPlus_HubCore::INT_Position(0, 0);
    CompPlus_HubCore::INT_Position P4_WarpQueue = CompPlus_HubCore::INT_Position(0, 0);

    CompPlus_HubCore::INT_Position Pos_OutOfBounds = CompPlus_HubCore::INT_Position(-10000, -10000);

    bool isRestart = true;
    bool LevelSelected = false;
    bool SettingsSelected = false;
    bool RankingSelected = false;

    int RankingsRingSlot = 615;
    int SettingsRingSlot = 616;

    bool LevelSelectedWarpSoundPlayed = false;
    int SceneLoadWaitTimer = 0;
    int SceneLoadWaitMax = 100;

    struct CollapsingPlatform : SonicMania::Entity
    {
        /* 0x00000058 */ BYTE Field_58;
        /* 0x00000059 */ BYTE Field_59;
        /* 0x0000005A */ BYTE Field_5A;
        /* 0x0000005B */ BYTE Field_5B;
        /* 0x0000005C */ BYTE Field_5C;
        /* 0x0000005D */ BYTE Field_5D;
        /* 0x0000005E */ BYTE SizeX;
        /* 0x0000005F */ BYTE Field_5F;
        /* 0x00000060 */ BYTE Field_60;
        /* 0x00000061 */ BYTE Field_61;
        /* 0x00000062 */ BYTE SizeY;
        /* 0x00000063 */ BYTE Field_63;
        /* 0x00000064 */ BYTE Field_64;
        /* 0x00000065 */ BYTE Field_65;
        /* 0x00000066 */ BYTE Field_66;
        /* 0x00000067 */ BYTE Field_67;
    };

    #pragma endregion

    #pragma region Billboard Palette Systems

    bool PaletteLoaded = false;
    std::vector<SHORT> PaletteMemory = std::vector<SHORT>(256);
    std::vector<SHORT> PaletteStorage;

    void LoadPalette() 
    {
        if (PaletteLoaded) return;

        int i = 0;
        PaletteStorage = std::vector<SHORT>(256);

        PaletteStorage[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000080); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x0038C0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x0068F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x1888F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x30A0F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x68D0F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x185868); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x60A0B0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x98C8C8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xA0E0E0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xC06830); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE09060); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0B090); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0D0C0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x400000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x900000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE00000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x800000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xB03000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE07000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE0A000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE0C000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x200008); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x700010); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE00020); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE84848); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE87878); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE89898); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x700000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xC00010); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x282028); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x383040); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x484868); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x587090); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x80A0B0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x98C0C8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xB0D0D0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xC0E0E0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE0E0E0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0F0F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x401000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x883800); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xB86800); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0B000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0D800); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0F000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x200000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x480008); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x900010); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE00000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF08C18); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x604080); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xA0A0C0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x283898); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x3050A8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x881020); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xC04000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x505878); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE07000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0B000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0D800); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0F0F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000080); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x0038C0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x0068F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x1888F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x30A0F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x68D0F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x7F0300); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xAC1A00); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xCD4F00); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xDC7800); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE48E00); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xECA600); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x005800); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x00A000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x00C800); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xD8D020); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x580018); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x980030); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xD00040); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE82858); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF06080); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF08088); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x400068); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x900088); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF00098); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0A0C8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0F0F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x501010); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x882020); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xA83030); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xC84040); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE06868); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF09098); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xA86020); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xD08840); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE8A860); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0D090); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x780000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xA80000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x087858); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x08C890); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x883000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xA06800); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xB88810); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xD0A810); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE0C020); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE8D038); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0E078); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xB05000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xC87048); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE8A078); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x5801B8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xA001F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xC818F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE828F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x203830); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x205038); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x306850); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x38A078); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x50B898); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x58C8B8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x88D8D8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xC8E8E8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x482010); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x602010); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x883810); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xC85010); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE87820); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0A020); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0C860); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0E0B8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x280120); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x400130); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x580150); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x680148); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x880150); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xA80158); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xC00148); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF00148); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x100150); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x011078); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x083098); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x1058B0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x1078C0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x3090D0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x88C8E0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xA0D8E8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xB8E0E8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xC8E8F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xD0F0F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE8F0F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x6878C8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x6880D0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x6890D0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x68A0D8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x60B0E0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x60C0E8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x68D0E0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x50E0E0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x60E8C8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x80F0C0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xA8F0C8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0E8D0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0F0E0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0F0F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xC8F0E0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xC8C0B8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE0D0C0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE8D8C8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xC08868); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xD08860); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xD89050); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE89858); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0A048); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0B070); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0C880); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0E0A8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0A848); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xD86848); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF07848); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF09858); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x9868C8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xB068D0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xC868D0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xD868D8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE868D8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE878D0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xB860B0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xC860A0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xD06098); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xD86890); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE86880); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xE87888); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x000000); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x209048); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x30A058); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x40B068); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x50C078); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x60D088); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x70D898); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x78E0A0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF00101); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x48D8F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x98E0F0); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF0F0D8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xF098A8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0x01F080); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xD89058); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xB850B8); i++;
        PaletteStorage[i] = SonicMania::ToRGB565(0xFFFFFF); i++;

        PaletteLoaded = true;
    }

    void SetObjectPalette()
    {
        LoadPalette();

        for (int i = 0; i < 256; i++)
        {
            PaletteMemory[i] = SonicMania::Palette0[i];
        }

        for (int i = 0; i < 256; i++)
        {
            SonicMania::Palette0[i] = PaletteStorage[i];
        }
    }

    void UnsetObjectPalette()
    {
        for (int i = 0; i < 256; i++)
        {
            SonicMania::Palette0[i] = PaletteMemory[i];
        }

        PaletteMemory.clear();
    }

    #pragma endregion

    #pragma region Controller/Drawing Methods

    int UpdateHUBDisplays() 
    {
        int StringIndex = 0;
        //Level Select Display
        CompPlus_HubText::UpdateLevelSelectStatusDisplay(CompPlus_Status::CurrentLevelSelect, 0, StringIndex, SelectedLevelSelectText);
        StringIndex++;

        if (CompPlus_Settings::EndlessRounds)
        {
            std::string roundNumber = "INFINITE";
            CompPlus_HubText::UpdateGeneralDisplay(RoundsCounterText, (char*)roundNumber.c_str(), roundNumber.length(), 0, StringIndex);
            StringIndex++;
        }
        else
        {
            std::string roundNumber = std::to_string(CompPlus_Scoring::GetPlusCurrentRound() + 1) + "\\" + std::to_string(CompPlus_Settings::NumberOfRounds);
            CompPlus_HubText::UpdateGeneralDisplay(RoundsCounterText, (char*)roundNumber.c_str(), roundNumber.length(), 0, StringIndex);
            StringIndex++;
        }

        std::string winsP1 = std::to_string(CompPlus_Scoring::P1_WinsPlus);
        CompPlus_HubText::UpdateGeneralDisplay(P1_WinsCounterText, (char*)winsP1.c_str(), winsP1.length(), 0, StringIndex);
        StringIndex++;
        std::string winsP2 = std::to_string(CompPlus_Scoring::P2_WinsPlus);
        CompPlus_HubText::UpdateGeneralDisplay(P2_WinsCounterText, (char*)winsP2.c_str(), winsP2.length(), 0, StringIndex);
        StringIndex++;
        std::string winsP3 = std::to_string(CompPlus_Scoring::P3_WinsPlus);
        CompPlus_HubText::UpdateGeneralDisplay(P3_WinsCounterText, (char*)winsP3.c_str(), winsP3.length(), 0, StringIndex);
        StringIndex++;
        std::string winsP4 = std::to_string(CompPlus_Scoring::P4_WinsPlus);
        CompPlus_HubText::UpdateGeneralDisplay(P4_WinsCounterText, (char*)winsP4.c_str(), winsP4.length(), 0, StringIndex);
        StringIndex++;

        CompPlus_HubText::UpdateWinsTallyDisplay(WinsTallyTextSlot, 0, StringIndex);
        StringIndex++;

        CompPlus_HubText::UpdateVSModeDisplay(VSModeTextSlot, 0, StringIndex);
        StringIndex++;

        std::string VersionNumber = CompPlus_Common::Internal_VersionNumberAlt;
        std::string VersionName = CompPlus_Common::Internal_VersionNameShort;

        std::string VersionDescriptor = ("COMPETITION+ " + VersionNumber + " (" + VersionName + ")");

        CompPlus_HubText::UpdateGeneralDisplay(UIVersionTitleSlotID, (char*)VersionDescriptor.c_str(), VersionDescriptor.length(), 0, StringIndex);
        StringIndex++;

        return StringIndex;
    }

    void CheckHUBSettings() 
    {
        //Level Select NUD
        int LevelStatus = CompPlus_HubControllers::SingleUpDownController(SwapLevelSelectController, CompPlus_Status::CurrentLevelSelect, 0, 4);
        if (LevelStatus != CompPlus_Status::CurrentLevelSelect) CompPlus_Status::CurrentLevelSelect = LevelStatus;
        LevelStatus = CompPlus_HubControllers::SingleUpDownController(SwapLevelSelectController2, LevelStatus, 0, 4);
        if (LevelStatus != CompPlus_Status::CurrentLevelSelect) CompPlus_Status::CurrentLevelSelect = LevelStatus;

        if (LevelStatus != CompPlus_Status::CurrentLevelSelect) CompPlus_Settings::SaveSettings();

        if (CompPlus_HubControllers::SettingWaitTimer != 0) CompPlus_HubControllers::SettingWaitTimer = CompPlus_HubControllers::SettingWaitTimer - 1;
    }

	#pragma endregion

    #pragma region HUB Travel Methods

    void UpdateQuickWarpPositions()
    {
        SonicMania::Entity& QuickWarpSpawn = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(Spawnpoint_WarpHub_ID);
        SonicMania::Entity& RankingWarpSpawn = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(Spawnpoint_Ranking_ID);
        SonicMania::Entity& OtherOptionsSpawn = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(Spawnpoint_OtherSettings_ID);
        SonicMania::Entity& StartingLineSpawn = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(Spawnpoint_None_ID);
        SonicMania::Entity& LevelSelectSpawn = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(Spawnpoint_LevelSelect_ID);

        Spawnpoint_StartingLine = CompPlus_HubCore::INT_Position(StartingLineSpawn.Position.X, StartingLineSpawn.Position.Y);
        Spawnpoint_OtherSettings = CompPlus_HubCore::INT_Position(OtherOptionsSpawn.Position.X, OtherOptionsSpawn.Position.Y);
        Spawnpoint_Ranking = CompPlus_HubCore::INT_Position(RankingWarpSpawn.Position.X, RankingWarpSpawn.Position.Y);
        Spawnpoint_LevelSelect = CompPlus_HubCore::INT_Position(LevelSelectSpawn.Position.X, LevelSelectSpawn.Position.Y);
        Spawnpoint_WarpHub = CompPlus_HubCore::INT_Position(QuickWarpSpawn.Position.X, QuickWarpSpawn.Position.Y);
    }

    void SetIsInWarpRoomState(int PlayerID, bool value)
    {
        if (PlayerID == 1) P1_IsInWarpRoom = value;
        else if (PlayerID == 2) P2_IsInWarpRoom = value;
        else if (PlayerID == 3) P3_IsInWarpRoom = value;
        else if (PlayerID == 4) P4_IsInWarpRoom = value;
    }

    void QueueQuickWarp(SonicMania::EntityPlayer& Player, int x, int y, bool isEnter, int PlayerID)
    {
        if (PlayerID == 1) 
        { 
            P1_WarpQueue = CompPlus_HubCore::INT_Position(x,y);
            P1_IsInWarpLoop = true;
        }
        else if (PlayerID == 2) 
        {
            P2_WarpQueue = CompPlus_HubCore::INT_Position(x, y);
            P2_IsInWarpLoop = true;
        }
        else if (PlayerID == 3) 
        {
            P3_WarpQueue = CompPlus_HubCore::INT_Position(x, y);
            P3_IsInWarpLoop = true;
        }
        else if (PlayerID == 4) 
        {
            P4_WarpQueue = CompPlus_HubCore::INT_Position(x, y);
            P4_IsInWarpLoop = true;
        }

        SetIsInWarpRoomState(PlayerID, isEnter);
    }

    void TeleQuickWarp(SonicMania::EntityPlayer& Player, int x, int y, int PlayerID)
    {
        int checkpoint_Offset = *(int*)(baseAddress + 0x00AC672C);

        Player.Position.X = x;
        Player.Position.Y = y;

        if (SonicMania::Options->CompetitionSession.NumberOfPlayers >= 2) 
        {
            Player.KillFlag = 1;
        }

        if (Player.Camera != nullptr)
        {
            WarpWithCamera(Player, x, y);
        }

        switch (PlayerID) 
        {
            case 1:
                WriteData((int*)(checkpoint_Offset + 0x12), x);
                WriteData((int*)(checkpoint_Offset + 0x16), y);
                WriteData((int*)(checkpoint_Offset + 0x34), 1);
                break;                                   
            case 2:                                      
                WriteData((int*)(checkpoint_Offset + 0x1A), x);
                WriteData((int*)(checkpoint_Offset + 0x1E), y);
                WriteData((int*)(checkpoint_Offset + 0x35), 1);
                break;                                   
            case 3:                                     
                WriteData((int*)(checkpoint_Offset + 0x22), x);
                WriteData((int*)(checkpoint_Offset + 0x26), y);
                WriteData((int*)(checkpoint_Offset + 0x36), 1);
                break;                                  
            case 4:                                    
                WriteData((int*)(checkpoint_Offset + 0x2A), x);
                WriteData((int*)(checkpoint_Offset + 0x2E), y);
                WriteData((int*)(checkpoint_Offset + 0x37), 1);
                break;
        }
    }



    bool isPlayerInDebug() 
    {       
        if (IsPlayerInDebugMode == 1) //|| IsPlayerInDebugMode_Alt == 1) 
        {
            return true;
        }
        else return false;
    }

    void CheckQuickWarp()
    {
        if (SonicMania::PlayerControllers[1].Y.Press && !P1_IsInWarpRoom && SonicMania::Player1.Grounded && SonicMania::Player1.XVelocity == 0 && SonicMania::Player1.YVelocity == 0)
        {
            if (!isPlayerInDebug()) QueueQuickWarp(SonicMania::Player1, Spawnpoint_WarpHub.X, Spawnpoint_WarpHub.Y, true, 1);
        }
        if (SonicMania::PlayerControllers[2].Y.Press && !P2_IsInWarpRoom && SonicMania::Player2.Grounded && SonicMania::Player2.XVelocity == 0 && SonicMania::Player2.YVelocity == 0) QueueQuickWarp(SonicMania::Player2, Spawnpoint_WarpHub.X, Spawnpoint_WarpHub.Y, true, 2);
        if (SonicMania::PlayerControllers[3].Y.Press && !P3_IsInWarpRoom && SonicMania::Player3.Grounded && SonicMania::Player3.XVelocity == 0 && SonicMania::Player3.YVelocity == 0) QueueQuickWarp(SonicMania::Player3, Spawnpoint_WarpHub.X, Spawnpoint_WarpHub.Y, true, 3);
        if (SonicMania::PlayerControllers[4].Y.Press && !P4_IsInWarpRoom && SonicMania::Player4.Grounded && SonicMania::Player4.XVelocity == 0 && SonicMania::Player4.YVelocity == 0) QueueQuickWarp(SonicMania::Player4, Spawnpoint_WarpHub.X, Spawnpoint_WarpHub.Y, true, 4);
    }

    void CheckPlayerQuickWarp(SonicMania::EntityPlayer &Player, int SlotID, int X1, int Y1, int X2, int Y2, int WarpX, int WarpY, int PlayerID)
    {
        SonicMania::Entity& WarpDetector = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(SlotID);
        int _X1 = WarpDetector.Position.X + X1;
        int _Y1 = WarpDetector.Position.Y + Y1;
        int _X2 = WarpDetector.Position.X + X2;
        int _Y2 = WarpDetector.Position.Y + Y2;

        if (Player.InRange(_X1, _Y1, _X2, _Y2))
        {
            QueueQuickWarp(Player, WarpX, WarpY, false, PlayerID);
        }
    }

    void CheckPlayersQuickWarp(int SlotID, int X1, int Y1, int X2, int Y2, int WarpX, int WarpY)
    {
        CheckPlayerQuickWarp(SonicMania::Player1, SlotID, X1, Y1, X2, Y2, WarpX, WarpY, 1);
        CheckPlayerQuickWarp(SonicMania::Player2, SlotID, X1, Y1, X2, Y2, WarpX, WarpY, 2);
        CheckPlayerQuickWarp(SonicMania::Player3, SlotID, X1, Y1, X2, Y2, WarpX, WarpY, 3);
        CheckPlayerQuickWarp(SonicMania::Player4, SlotID, X1, Y1, X2, Y2, WarpX, WarpY, 4);
    }

    int SavedPanningSpeedX = 0;
    int SavedPanningSpeedY = 0;
    int SavedPanSpeed = 0;

    void QuickWarpLoop(SonicMania::EntityPlayer& Player, int PlayerID, int& WarpAlpha, bool& IsInWarpLoop, CompPlus_HubCore::INT_Position& WarpQueue)
    {
        bool isActive = Player.Camera != nullptr;
        if (isActive && IsInWarpLoop)
        {
            Player.InkEffect = SonicMania::Ink_Alpha;
            if (IsInWarpLoop)
            {
                Player.Alpha = (WarpAlpha > 0 ? WarpAlpha : 0);
                if (WarpAlpha > 0)
                {
                    WarpAlpha = WarpAlpha - 10;
                }
                else
                {
                    WarpAlpha = 0;
                    TeleQuickWarp(Player, WarpQueue.X, WarpQueue.Y, PlayerID);
                    IsInWarpLoop = false;
                }
            }
        }
        else if (Player.State == PLAYERSTATE_DIE) WarpAlpha = 0;
        else if (!IsInWarpLoop)
        {
            Player.Alpha = (WarpAlpha < 256 ? WarpAlpha : 256);
            if (WarpAlpha < 256) WarpAlpha = WarpAlpha + 10;
        }
    }

    void QuickWarpLoops()
    {
        QuickWarpLoop(SonicMania::Player1, 1, P1_WarpAlpha, P1_IsInWarpLoop, P1_WarpQueue);
        QuickWarpLoop(SonicMania::Player2, 2, P2_WarpAlpha, P2_IsInWarpLoop, P2_WarpQueue);
        QuickWarpLoop(SonicMania::Player3, 3, P3_WarpAlpha, P3_IsInWarpLoop, P3_WarpQueue);
        QuickWarpLoop(SonicMania::Player4, 4, P4_WarpAlpha, P4_IsInWarpLoop, P4_WarpQueue);
    }

    void UpdateQuickWarpRoom() 
    {
        UpdateQuickWarpPositions();
        QuickWarpLoops();
        CheckQuickWarp();
        CheckPlayersQuickWarp(WarpSlotID_PlayerSettings, -16, -16, 16, 16, Spawnpoint_StartingLine.X, Spawnpoint_StartingLine.Y);
        CheckPlayersQuickWarp(WarpSlotID_OtherSettings, -16, -16, 16, 16, Spawnpoint_OtherSettings.X, Spawnpoint_OtherSettings.Y);
        CheckPlayersQuickWarp(WarpSlotID_Ranking, -16, -16, 16, 16, Spawnpoint_Ranking.X, Spawnpoint_Ranking.Y);
        CheckPlayersQuickWarp(WarpSlotID_LevelSelect, -16, -16, 16, 16, Spawnpoint_LevelSelect.X, Spawnpoint_LevelSelect.Y);
    }

    void ResetQuickWarps() 
    {
        P1_IsInWarpRoom = false;
        P2_IsInWarpRoom = false;
        P3_IsInWarpRoom = false;
        P4_IsInWarpRoom = false;
    }

    #pragma endregion

    #pragma region Spawn Position Methods


    void SetSpawnPosition(SonicMania::EntityPlayer& Player, int Placement)
    {
        SonicMania::Entity& SettingsSpawn = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(Spawnpoint_OtherSettings_ID);
        SonicMania::Entity& RankingSpawn = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(Spawnpoint_Ranking_ID);
        SonicMania::Entity& LevelSelectSpawn = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(Spawnpoint_LevelSelect_ID);
        SonicMania::Entity& NormalSpawn = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(Spawnpoint_None_ID);

        int x = 0;
        int y = 0;

        if (Placement == 0)
        {
            x = NormalSpawn.Position.X;
            y = NormalSpawn.Position.Y;
        }
        else if (Placement == 1)
        {
            x = SettingsSpawn.Position.X;
            y = SettingsSpawn.Position.Y;
        }
        else if (Placement == 2)
        {
            x = RankingSpawn.Position.X;
            y = RankingSpawn.Position.Y;
        }
        else if (Placement == 3)
        {
            x = LevelSelectSpawn.Position.X;
            y = LevelSelectSpawn.Position.Y;
        }
        else 
        {
            x = NormalSpawn.Position.X;
            y = NormalSpawn.Position.Y;
        }

        Player.Position.X = x;
        Player.Position.Y = y;

        if (Player.Camera != nullptr)
        {
            WarpWithCamera(Player, x, y);
        }
    }

    void SetSpawnPositions()
    {
        SetSpawnPosition(SonicMania::Player1, CompPlus_HubCore::ReturnDestination);
        SetSpawnPosition(SonicMania::Player2, CompPlus_HubCore::ReturnDestination);
        SetSpawnPosition(SonicMania::Player3, CompPlus_HubCore::ReturnDestination);
        SetSpawnPosition(SonicMania::Player4, CompPlus_HubCore::ReturnDestination);

        CompPlus_HubCore::ReturnDestination = 0;
    }

    #pragma endregion

    #pragma region Warp Methods Methods

    void SceneWarp()
    {
        CollapsingPlatform RankingBounds = *SonicMania::GetEntityFromSceneSlot<CollapsingPlatform>(SceneWarpBounds_Ranking_ID);
        CollapsingPlatform SettingsBounds = *SonicMania::GetEntityFromSceneSlot<CollapsingPlatform>(SceneWarpBounds_Settings_ID);
        CollapsingPlatform LevelSelectBounds = *SonicMania::GetEntityFromSceneSlot<CollapsingPlatform>(SceneWarpBounds_LevelSelect_ID);


        int x1_ranking = RankingBounds.Position.X - (RankingBounds.SizeX == 0 ? 1 : RankingBounds.SizeX / 2);
        int y1_ranking = RankingBounds.Position.Y - (RankingBounds.SizeY == 0 ? 1 : RankingBounds.SizeY / 2);
        int x2_ranking = RankingBounds.Position.X + (RankingBounds.SizeX == 0 ? 1 : RankingBounds.SizeX / 2);
        int y2_ranking = RankingBounds.Position.Y + (RankingBounds.SizeY == 0 ? 1 : RankingBounds.SizeY / 2);

        int x1_settings = SettingsBounds.Position.X - (SettingsBounds.SizeX == 0 ? 1 : SettingsBounds.SizeX / 2);
        int y1_settings = SettingsBounds.Position.Y - (SettingsBounds.SizeY == 0 ? 1 : SettingsBounds.SizeY / 2);
        int x2_settings = SettingsBounds.Position.X + (SettingsBounds.SizeX == 0 ? 1 : SettingsBounds.SizeX / 2);
        int y2_settings = SettingsBounds.Position.Y + (SettingsBounds.SizeY == 0 ? 1 : SettingsBounds.SizeY / 2);

        int x1_levelSelect = LevelSelectBounds.Position.X - (LevelSelectBounds.SizeX == 0 ? 1 : LevelSelectBounds.SizeX / 2);
        int y1_levelSelect = LevelSelectBounds.Position.Y - (LevelSelectBounds.SizeY == 0 ? 1 : LevelSelectBounds.SizeY / 2);
        int x2_levelSelect = LevelSelectBounds.Position.X + (LevelSelectBounds.SizeX == 0 ? 1 : LevelSelectBounds.SizeX / 2);
        int y2_levelSelect = LevelSelectBounds.Position.Y + (LevelSelectBounds.SizeY == 0 ? 1 : LevelSelectBounds.SizeY / 2);

        int SettingsCount = 0;
        int RankingCount = 0;
        int ButtonCount = 0;

        int NumberOfPlayers = (SonicMania::Options->CompetitionSession.inMatch == 1 ? SonicMania::Options->CompetitionSession.NumberOfPlayers : 1);

        if (SonicMania::Player1.Camera != nullptr) 
        {
            bool isPlayerInRangeOfRanking = SonicMania::Player1.InRange(x1_ranking, y1_ranking, x2_ranking, y2_ranking);
            bool isPlayerInRangeOfSettings = SonicMania::Player1.InRange(x1_settings, y1_settings, x2_settings, y2_settings);
            bool isPlayerInRangeOfButton = SonicMania::Player1.InRange(x1_levelSelect, y1_levelSelect, x2_levelSelect, y2_levelSelect);

            if (isPlayerInRangeOfRanking) RankingCount += 1;
            if (isPlayerInRangeOfSettings) SettingsCount += 1;
            if (isPlayerInRangeOfButton) ButtonCount += 1;
        }
        if (SonicMania::Player2.Camera != nullptr)
        {
            bool isPlayerInRangeOfRanking = SonicMania::Player2.InRange(x1_ranking, y1_ranking, x2_ranking, y2_ranking);
            bool isPlayerInRangeOfSettings = SonicMania::Player2.InRange(x1_settings, y1_settings, x2_settings, y2_settings);
            bool isPlayerInRangeOfButton = SonicMania::Player2.InRange(x1_levelSelect, y1_levelSelect, x2_levelSelect, y2_levelSelect);

            if (isPlayerInRangeOfRanking) RankingCount += 1;
            if (isPlayerInRangeOfSettings) SettingsCount += 1;
            if (isPlayerInRangeOfButton) ButtonCount += 1;
        }
        if (SonicMania::Player3.Camera != nullptr)
        {
            bool isPlayerInRangeOfRanking = SonicMania::Player3.InRange(x1_ranking, y1_ranking, x2_ranking, y2_ranking);
            bool isPlayerInRangeOfSettings = SonicMania::Player3.InRange(x1_settings, y1_settings, x2_settings, y2_settings);
            bool isPlayerInRangeOfButton = SonicMania::Player3.InRange(x1_levelSelect, y1_levelSelect, x2_levelSelect, y2_levelSelect);

            if (isPlayerInRangeOfRanking) RankingCount += 1;
            if (isPlayerInRangeOfSettings) SettingsCount += 1;
            if (isPlayerInRangeOfButton) ButtonCount += 1;
        }
        if (SonicMania::Player4.Camera != nullptr)
        {
            bool isPlayerInRangeOfRanking = SonicMania::Player4.InRange(x1_ranking, y1_ranking, x2_ranking, y2_ranking);
            bool isPlayerInRangeOfSettings = SonicMania::Player4.InRange(x1_settings, y1_settings, x2_settings, y2_settings);
            bool isPlayerInRangeOfButton = SonicMania::Player4.InRange(x1_levelSelect, y1_levelSelect, x2_levelSelect, y2_levelSelect);

            if (isPlayerInRangeOfRanking) RankingCount += 1;
            if (isPlayerInRangeOfSettings) SettingsCount += 1;
            if (isPlayerInRangeOfButton) ButtonCount += 1;
        }


        SpecialRing& SettingsRing = *SonicMania::GetEntityFromSceneSlot<SpecialRing>(SettingsRingSlot);


        if (SettingsCount >= NumberOfPlayers)
        {
            SettingsRing.Enabled = true;
        }
        else
        {
            SettingsRing.Enabled = false;
        }

        if (SettingsRing.TriggeredState == 2 && !SettingsSelected)
        {
            SettingsSelected = true;
        }

        SpecialRing& RankingRing = *SonicMania::GetEntityFromSceneSlot<SpecialRing>(RankingsRingSlot);


        if (RankingCount >= NumberOfPlayers)
        {
            RankingRing.Enabled = true;
        }
        else
        {
            RankingRing.Enabled = false;
        }

        if (RankingRing.TriggeredState == 2 && !RankingSelected)
        {
            RankingSelected = true;
        }

        SonicMania::EntityButton& ConfirmButton = *SonicMania::GetEntityFromSceneSlot<SonicMania::EntityButton>(EnterLSelectButton);
        if (ButtonCount >= NumberOfPlayers && ConfirmButton.Pressed && !LevelSelected)
        {
            LevelSelected = true;
        }
        else if (ConfirmButton.Pressed)
        {
            ConfirmButton.Pressed = false;
        }
    }

    void RankingWarpLoop(bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
    {
        if (FastWarp && SceneLoadWaitTimer < 50)
        {
            SceneLoadWaitTimer = 50;
        }

        if (SceneLoadWaitTimer >= SceneLoadWaitMax)
        {
            SceneLoadWaitTimer = 0;
            LevelSelected = false;
            LevelSelectedWarpSoundPlayed = false;
            CompPlus_Common::LoadLevel_IZ(CompPlus_Common::HUBRanking);
        }
        else
        {
            if (SceneLoadWaitTimer >= 50 && !LevelSelectedWarpSoundPlayed)
            {
                SonicMania::PlaySoundFXS(CompPlus_Common::SFX_SpecialWarp);
                LevelSelectedWarpSoundPlayed = true;

                SonicMania::Entity* FXFade = SonicMania::SpawnObject(SonicMania::GetObjectIDFromType(SonicMania::ObjectType_FXFade), 0, SonicMania::Vector2(SonicMania::Player1.Position.X, SonicMania::Player1.Position.Y - 30));
                SonicMania::EntityFXFade* FxFadeR = (SonicMania::EntityFXFade*)FXFade;

                FxFadeR->Time = 0;
                FxFadeR->SpeedIn = 10;
                FxFadeR->Wait = 3;
                FxFadeR->SpeedOut = 0;
                FxFadeR->Color = 0x000000;
                FxFadeR->OneWay = true;
                FxFadeR->EventOnly = false;
                FxFadeR->Overhud = false;
                FxFadeR->FadeOutBlack = true;

            }
            SceneLoadWaitTimer++;
        }

        SonicMania::stru_26B818[0].playStatus = 0;

    }

    void SettingsWarpLoop(bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
    {
        if (FastWarp && SceneLoadWaitTimer < 50)
        {
            SceneLoadWaitTimer = 50;
        }

        if (SceneLoadWaitTimer >= SceneLoadWaitMax)
        {
            SceneLoadWaitTimer = 0;
            LevelSelected = false;
            LevelSelectedWarpSoundPlayed = false;
            CompPlus_Common::LoadLevel_IZ(CompPlus_Common::HUBSettings);
        }
        else
        {
            if (SceneLoadWaitTimer >= 50 && !LevelSelectedWarpSoundPlayed)
            {
                SonicMania::PlaySoundFXS(CompPlus_Common::SFX_SpecialWarp);
                LevelSelectedWarpSoundPlayed = true;

                SonicMania::Entity* FXFade = SonicMania::SpawnObject(SonicMania::GetObjectIDFromType(SonicMania::ObjectType_FXFade), 0, SonicMania::Vector2(SonicMania::Player1.Position.X, SonicMania::Player1.Position.Y - 30));
                SonicMania::EntityFXFade* FxFadeR = (SonicMania::EntityFXFade*)FXFade;

                FxFadeR->Time = 0;
                FxFadeR->SpeedIn = 10;
                FxFadeR->Wait = 3;
                FxFadeR->SpeedOut = 0;
                FxFadeR->Color = 0x000000;
                FxFadeR->OneWay = true;
                FxFadeR->EventOnly = false;
                FxFadeR->Overhud = false;
                FxFadeR->FadeOutBlack = true;

            }
            SceneLoadWaitTimer++;
        }

        SonicMania::stru_26B818[0].playStatus = 0;

    }

    void WarpLoop(bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
    {
        if (FastWarp && SceneLoadWaitTimer < 50)
        {
            SceneLoadWaitTimer = 50;
        }


        if (SceneLoadWaitTimer >= SceneLoadWaitMax)
        {
            SceneLoadWaitTimer = 0;
            LevelSelected = false;
            LevelSelectedWarpSoundPlayed = false;
            CompPlus_Common::LoadLastLevelSelect();
        }
        else
        {
            if (SceneLoadWaitTimer >= 50 && !LevelSelectedWarpSoundPlayed)
            {
                SonicMania::PlaySoundFXS(CompPlus_Common::SFX_SpecialWarp);
                LevelSelectedWarpSoundPlayed = true;

                SonicMania::Entity* FXFade = SpawnObject(SonicMania::GetObjectIDFromType(SonicMania::ObjectType_FXFade), 0, SonicMania::Vector2(SonicMania::Player1.Position.X, SonicMania::Player1.Position.Y - 30));
                SonicMania::EntityFXFade* FxFadeR = (SonicMania::EntityFXFade*)FXFade;

                FxFadeR->Time = 0;
                FxFadeR->SpeedIn = 10;
                FxFadeR->Wait = 3;
                FxFadeR->SpeedOut = 0;
                FxFadeR->Color = 0x000000;
                FxFadeR->OneWay = true;
                FxFadeR->EventOnly = false;
                FxFadeR->Overhud = false;
                FxFadeR->FadeOutBlack = true;

            }
            SceneLoadWaitTimer++;
        }

        SonicMania::stru_26B818[0].playStatus = 0;

    }

    #pragma endregion

    void OnFrame()
    {
        CompPlus_HubCore::SetHUBVisualSettings();
        UpdateQuickWarpRoom();
        UpdateHUBDisplays();
        CheckHUBSettings();
        SceneWarp();

        if (SonicMania::Timer.Enabled == false && SonicMania::Options->CompetitionSession.NumberOfPlayers >= 2) isRestart = true;

        if (isRestart && SonicMania::Timer.Enabled)
        {
            SetSpawnPositions();
            ResetQuickWarps();
            isRestart = false;
        }

        if (RankingSelected) RankingWarpLoop(true, SceneLoadWaitTimer, SceneLoadWaitMax, RankingSelected, LevelSelectedWarpSoundPlayed);
        if (SettingsSelected) SettingsWarpLoop(true, SceneLoadWaitTimer, SceneLoadWaitMax, SettingsSelected, LevelSelectedWarpSoundPlayed);
        if (LevelSelected) WarpLoop(true, SceneLoadWaitTimer, SceneLoadWaitMax, LevelSelected, LevelSelectedWarpSoundPlayed);

    }




}