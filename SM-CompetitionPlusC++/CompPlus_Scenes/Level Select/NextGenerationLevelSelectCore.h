#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/PointScrolling.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "SonicMania.h"
#include "ManiaLevelSelect.h"

namespace CompPlus_NextGenerationLevelSelectCore
{

    enum MenuPointState : int
    {
        MenuPointState_Locked = 0,
        MenuPointState_LoadStage = 1,
    };

    struct MenuPoint {

        Vector2 Position;

        EntityUIPicture* Object;

        int LevelID;

        std::string LevelID_IZ;

        bool isIZ = false;

        bool isLocked = false;

        bool isBlank = false;

        int RedirectX = 0;

        int RedirectY = 0;

        int ImageAnimID = 0;

        int ImageFrameID = 0;

        bool YellowText = false;

        std::string CP_Title = " ";

        std::string CP_Name = " ";

        std::string CP_Author = " ";

        std::string CP_Extra = " ";

        MenuPoint()
        {

        }

        MenuPoint(int slotID, bool _isLocked) : MenuPoint()
        {
            isLocked = _isLocked;
            Object = GetEntity(slotID);
            Position.X = Object->Position.X;
            Position.Y = Object->Position.Y;
        }

        MenuPoint(bool _isBlank, int x, int y) : MenuPoint()
        {
            isBlank = _isBlank;
            Position.X = 0;
            Position.Y = 0;
            RedirectX = x;
            RedirectY = y;
        }

        MenuPoint(int slotID, const char* levelID_IZ, const char* _CP_Name, const char* _CP_Author, const char* _CP_Extra) : MenuPoint()
        {
            LevelID_IZ = levelID_IZ;
            Object = GetEntity(slotID);
            Position.X = Object->Position.X;
            Position.Y = Object->Position.Y;
            isIZ = true;

            CP_Name = _CP_Name;
            CP_Author = _CP_Author;
            CP_Extra = _CP_Extra;
        }

        MenuPoint(int slotID, const char* levelID_IZ, const char* _CP_Name, const char* _CP_Author, const char* _CP_Extra, bool _isLocked) : MenuPoint()
        {
            LevelID_IZ = levelID_IZ;
            Object = GetEntity(slotID);
            Position.X = Object->Position.X;
            Position.Y = Object->Position.Y;
            isIZ = true;

            CP_Name = _CP_Name;
            CP_Author = _CP_Author;
            CP_Extra = _CP_Extra;

            isLocked = _isLocked;
        }

        MenuPoint(int slotID, short levelID, const char* _CP_Name, const char* _CP_Author, const char* _CP_Extra) : MenuPoint()
        {
            LevelID = levelID;
            Object = GetEntity(slotID);
            Position.X = Object->Position.X;
            Position.Y = Object->Position.Y;

            CP_Name = _CP_Name;
            CP_Author = _CP_Author;
            CP_Extra = _CP_Extra;
        }

        MenuPoint(int slotID, int levelID, const char* _CP_Name, const char* _CP_Author, const char* _CP_Extra) : MenuPoint()
        {
            LevelID = levelID;
            Object = GetEntity(slotID);
            Position.X = Object->Position.X;
            Position.Y = Object->Position.Y;

            CP_Name = _CP_Name;
            CP_Author = _CP_Author;
            CP_Extra = _CP_Extra;
        }

        MenuPointState OnInteract()
        {
            if (isLocked)
            {
                SonicMania::PlaySoundFXS("Stage/Fail.wav");
                return  MenuPointState_Locked;
            }
            else return MenuPointState_LoadStage;
        }
    };

    struct UIBackgroundDefinition
    {
        SonicMania::Color BG;
        SonicMania::Color FG1;
        SonicMania::Color FG2;

        UIBackgroundDefinition()
        {

        }

        UIBackgroundDefinition(SonicMania::Color _BG, SonicMania::Color _FG1, SonicMania::Color _FG2)
        {
            BG = _BG;
            FG1 = _FG1;
            FG2 = _FG2;
        }
    };

    DataPointer(int, WindowSizeX, 0x43C6F4);
    DataPointer(int, WindowSizeY, 0x43C6F8);

    extern bool PaletteSaved;

    extern void UniversalLSelectLoop();
    extern void LevelSelectDelayLoop(int selectorID, MenuPoint levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed);
    extern void LevelSelectDelayLoop(int selectorID, int levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed);
    extern void LevelSelectDelayLoop(int selectorID, const char* levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed);
    extern void LevelSelectExitDelayLoop(int selectorID, const char* levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed);
    extern void LevelSelectDelay(bool isClassic, bool& LevelSelected);
    extern void EnforcePalette();
    extern int GetPositionOffsetX();
    extern int GetPositionOffsetY();
    extern void SetUIBackgroundObject(UIBackgroundDefinition Definition);
    extern void InitDrawVariables(int StartX, int StartY, int SpacingX, int SpacingY);
    extern MenuPoint CreateBlankMenuPoint(int x, int y);
    extern MenuPoint CreateMenuPoint(int y, int x, std::string SceneID, std::string Title, std::string Name, std::string Author, int AnimID, int FrameID, bool isLocked);
    extern MenuPoint CreateMenuPoint(int y, int x, int LevelID, std::string Title, std::string Name, std::string Author, int AnimID, int FrameID, bool isLocked);
    extern void DrawZoneInfo(MenuPoint Point, EntityTitleCard* Canvas);
    extern void DrawEntryChaotix(MenuPoint Point, int x, int y, int IconsSpriteID, int MenuPos_X, int MenuPos_Y, EntityTitleCard* Canvas);
    extern void DrawEntry(MenuPoint Point, int x, int y, int IconsSpriteID, int MenuPos_X, int MenuPos_Y, EntityTitleCard* Canvas);
    extern void DrawEntryTextEXE(MenuPoint Point, int x, int y);
    extern void DrawEntryText(MenuPoint Point, int x, int y);
    extern void DrawSelector(int x, int y, int IconsSpriteID, SonicMania::EntityTitleCard* Canvas, bool IsSelected);
    extern void SetupPosition(short MenuPos_X, short MenuPos_Y);
    extern void UpdateLevelSelectScroll(int& MenuPos_X, int& MenuPos_Y, int& LastMenuPos_X, int& LastMenuPos_Y, bool& UpdateMenuScroll, MenuPoint** MenuPoints);
    extern void ResetMenuPos(int& MenuPos_X, int& MenuPos_Y, int& LastMenuPos_X, int& LastMenuPos_Y, bool& SwapLevelSelect);
    extern void ResetMenuPos(int& MenuPos_X, int& MenuPos_Y, int SMenuPos_X, int SMenuPos_Y, int& LastMenuPos_X, int& LastMenuPos_Y, bool& SwapLevelSelect);
    extern void UpdateLastPos(int& LastMenuPos_X, int& LastMenuPos_Y, int& MenuPos_X, int& MenuPos_Y);

    extern void Init(std::string modPath);
};

