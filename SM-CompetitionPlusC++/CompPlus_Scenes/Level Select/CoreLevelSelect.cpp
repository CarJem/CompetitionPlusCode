#include "stdafx.h"
#include "CoreLevelSelect.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/PointScrolling.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "SonicMania.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include <vector>
#include "CompPlus_Core/CompPlus_Scoring.h"
#include "CompPlus_Scenes/HUB World/HubCore.h"
#include "CompPlus_Extensions/Drawing.h"

namespace CompPlus_CoreLevelSelect
{
    using namespace CompPlus_Common;

    std::string PaletteACT_FilePath;
    bool PaletteSaved = false;
    SHORT PaletteStorage[256];
    int PaletteStorage_Length;

    int CurrentDraw_StartX = 0;
    int CurrentDraw_StartY = 0;
    int CurrentDraw_SpacingX = 0;
    int CurrentDraw_SpacingY = 0;

    bool isSelectorVisible = false;

    int GeneralDrawOrder = 8;

    void LevelSelectDelayLoop(int selectorID, MenuPoint level, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
    {
        if (FastWarp && SceneLoadWaitTimer < 30)
        {
            SceneLoadWaitTimer = 30;
        }


        if (SceneLoadWaitTimer >= SceneLoadWaitMax)
        {
            if (level.isIZ)
            {
                CompPlus_Scoring::LastZone = level.CP_Name.c_str();
                CompPlus_Common::LoadLevel_IZ(level.LevelID_IZ.c_str());
            }
            else
            {
                CompPlus_Scoring::LastZone = level.CP_Name.c_str();
                CompPlus_Common::LoadLevel(level.LevelID);
            }

            SceneLoadWaitTimer = 0;
            LevelSelected = false;
            LevelSelectedWarpSoundPlayed = false;
        }
        else
        {
            if (SceneLoadWaitTimer >= 30 && !LevelSelectedWarpSoundPlayed)
            {
                PlaySoundFXS(CompPlus_Common::SFX_SpecialWarp);
                LevelSelectedWarpSoundPlayed = true;

                if (FastWarp)
                {
                    CompPlus_Common::SpawnFadeOut(0, 20, 0, 0, 0x000000, true, false, false, true, 14);
                }
                else
                {
                    CompPlus_Common::SpawnFadeOut(0, 10, 3, 0, 0x000000, true, false, false, true, 14);
                }


            }
            SceneLoadWaitTimer++;
        }

        stru_26B818[0].playStatus = 0;
    }

    void UniversalLSelectLoop()
    {
        SonicMania::SetVSScreenCount(1);
    }

    void LevelSelectDelayLoop(int selectorID, int levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
    {
        if (FastWarp && SceneLoadWaitTimer < 50)
        {
            SceneLoadWaitTimer = 50;
        }


        if (SceneLoadWaitTimer >= SceneLoadWaitMax)
        {
            LoadLevel(levelID);
            SceneLoadWaitTimer = 0;
            LevelSelected = false;
            LevelSelectedWarpSoundPlayed = false;
        }
        else
        {
            if (SceneLoadWaitTimer >= 50 && !LevelSelectedWarpSoundPlayed)
            {
                PlaySoundFXS(CompPlus_Common::SFX_SpecialWarp);
                LevelSelectedWarpSoundPlayed = true;

                CompPlus_Common::SpawnFadeOut(0, 10, 3, 0, 0x000000, true, false, false, true, 14);
            }
            SceneLoadWaitTimer++;
        }

        stru_26B818[0].playStatus = 0;
    }

    void LevelSelectExitDelayLoop(int selectorID, const char* levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
    {
        if (FastWarp && SceneLoadWaitTimer < 50)
        {
            SceneLoadWaitTimer = 50;
        }


        if (SceneLoadWaitTimer >= SceneLoadWaitMax)
        {
            CompPlus_HubCore::ReturnDestination = 3;
            CompPlus_Common::LoadHUBWorld();
            SceneLoadWaitTimer = 0;
            LevelSelected = false;
            LevelSelectedWarpSoundPlayed = false;
        }
        else
        {
            if (SceneLoadWaitTimer >= 50 && !LevelSelectedWarpSoundPlayed)
            {
                PlaySoundFXS(CompPlus_Common::SFX_SpecialWarp);
                LevelSelectedWarpSoundPlayed = true;

                CompPlus_Common::SpawnFadeOut(0, 10, 3, 0, 0x000000, true, false, false, true, 14);
            }
            SceneLoadWaitTimer++;
        }

        stru_26B818[0].playStatus = 0;
    }

    void LevelSelectDelayLoop(int selectorID, const char* levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
    {
        if (FastWarp && SceneLoadWaitTimer < 30)
        {
            SceneLoadWaitTimer = 30;
        }


        if (SceneLoadWaitTimer >= SceneLoadWaitMax)
        {
            CompPlus_Common::LoadLevel_IZ(levelID);
            SceneLoadWaitTimer = 0;
            LevelSelected = false;
            LevelSelectedWarpSoundPlayed = false;
        }
        else
        {
            if (SceneLoadWaitTimer >= 30 && !LevelSelectedWarpSoundPlayed)
            {
                PlaySoundFXS(CompPlus_Common::SFX_SpecialWarp);
                LevelSelectedWarpSoundPlayed = true;

                if (FastWarp)
                {
                    CompPlus_Common::SpawnFadeOut(0, 20, 0, 0, 0x000000, true, false, false, true, 14);
                }
                else
                {
                    CompPlus_Common::SpawnFadeOut(0, 10, 3, 0, 0x000000, true, false, false, true, 14);
                }


            }
            SceneLoadWaitTimer++;
        }

        stru_26B818[0].playStatus = 0;
    }

    void LevelSelectDelay(bool isClassic, bool& LevelSelected)
    {
        PlayMenuAcceptSoundFX(isClassic);
        LevelSelected = true;
    }

    void ApplyPalette() 
    {
        memcpy(SonicMania::Palette0, PaletteStorage, PaletteStorage_Length * sizeof(SHORT));
        memcpy(SonicMania::Palette1, PaletteStorage, PaletteStorage_Length * sizeof(SHORT));
        memcpy(SonicMania::Palette2, PaletteStorage, PaletteStorage_Length * sizeof(SHORT));
        memcpy(SonicMania::Palette3, PaletteStorage, PaletteStorage_Length * sizeof(SHORT));
    }  

    void EnforcePalette()
    {
        if (!PaletteSaved)
        {
            StorePalette(PaletteACT_FilePath, PaletteStorage, PaletteStorage_Length);
            PaletteSaved = true;
        }
        else
        {
            ApplyPalette();
        }
    }

    int GetPositionOffsetX()
    {
        return (ScreenOffsetX != 0 ? ScreenOffsetX : 0);
    }

    int GetPositionOffsetY()
    {
        return (ScreenOffsetY != 0 ? ScreenOffsetY / 2 : 0);
    }

    void SetUIBackgroundObject(UIBackgroundDefinition Definition) 
    {
        SetUIBG_BGColor(Definition.BG.Red, Definition.BG.Green, Definition.BG.Blue);
        SetUIBG_FGLowColor(Definition.FG1.Red, Definition.FG1.Green, Definition.FG1.Blue);
        SetUIBG_FGHighColor(Definition.FG2.Red, Definition.FG2.Green, Definition.FG2.Blue);
    }

    void InitDrawVariables(int StartX, int StartY, int SpacingX, int SpacingY)
    {
        CurrentDraw_StartX = StartX;
        CurrentDraw_StartY = StartY;
        CurrentDraw_SpacingX = SpacingX;
        CurrentDraw_SpacingY = SpacingY;

        for (int i = 0; i < 2301; ++i)
        {
            Entity& entity = *GetEntityFromSceneSlot<Entity>(i);

            if (entity.ObjectID == GetObjectIDFromType(ObjectType_FXFade))
            {
                entity.DrawOrder = 14;
            }
        }

    }

    void DrawZoneInfo(MenuPoint Point, EntityTitleCard* Canvas) 
    {
        int InitalOrder = Canvas->DrawOrder;
        Canvas->DrawOrder = GeneralDrawOrder;
        if (!Point.isBlank)
        {
            SonicMania::Vector2 CurrentPosition = SonicMania::Vector2(PosXCurrent + GetPositionOffsetX(), PosYCurrent + GetPositionOffsetY());
            int StartY = CurrentPosition.Y + 86;

            int HalfSize = (WindowSizeX != 0 ? WindowSizeX / 2 : 0);
            int TopSize = (WindowSizeY != 0 ? WindowSizeY / 2 : 0);

            int NameY = StartY + 16 - 4;
            int AuthorY = StartY + 30 - 4;
            int ExtrasY = StartY + 46 - 4;


            Canvas->DrawOrder = 12;
            Drawing::DrawTitleCardRect(CurrentPosition.X - HalfSize, StartY + 4, WindowSizeX, 60, 0x000000, 150, InkEffect::Ink_Alpha);

            Drawing::DrawMenuTextSprite(Point.CP_Name, SonicMania::Vector2(CurrentPosition.X, NameY), false, 10, 0, 0, DevMenu_Alignment::Alignment_Center);
            Drawing::DrawMenuTextSprite(Point.CP_Author, SonicMania::Vector2(CurrentPosition.X, AuthorY), false, 10, 0, 0, DevMenu_Alignment::Alignment_Center);
            Drawing::DrawMenuTextSprite(Point.CP_Extra, SonicMania::Vector2(CurrentPosition.X, ExtrasY), false, 10, 0, 0, DevMenu_Alignment::Alignment_Center);
        }
        Canvas->DrawOrder = InitalOrder;
    }

    void DrawEntryChaotix(MenuPoint Point, int x, int y, int IconsSpriteID, int MenuPos_X, int MenuPos_Y, EntityTitleCard* Canvas)
    {
        int InitalOrder = Canvas->DrawOrder;
        Canvas->DrawOrder = GeneralDrawOrder;
        if (!Point.isBlank)
        {
            if (MenuPos_Y == y && MenuPos_X == x) SonicMania::SetSpriteAnimation(IconsSpriteID, 0, &Canvas->ActNumbersData, true, 1);
            else SonicMania::SetSpriteAnimation(IconsSpriteID, 0, &Canvas->ActNumbersData, true, 0);
            DrawSprite(&Canvas->ActNumbersData, &SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY), false);
            SonicMania::SetSpriteAnimation(IconsSpriteID, Point.ImageAnimID, &Canvas->ActNumbersData, true, Point.ImageFrameID);
            DrawSprite(&Canvas->ActNumbersData, &SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY), false);
            if (Point.isLocked) 
            {
                SonicMania::SetSpriteAnimation(IconsSpriteID, 2, &Canvas->ActNumbersData, true, 3);
                DrawSprite(&Canvas->ActNumbersData, &SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY), false);
            }
        }
    }

    void DrawEntry(MenuPoint Point, int x, int y, int IconsSpriteID, int MenuPos_X, int MenuPos_Y, EntityTitleCard* Canvas)
    {
        int InitalOrder = Canvas->DrawOrder;
        Canvas->DrawOrder = GeneralDrawOrder;
        if (!Point.isBlank)
        {
            if (MenuPos_Y == y && MenuPos_X == x) SonicMania::SetSpriteAnimation(IconsSpriteID, 0, &Canvas->ActNumbersData, true, 1);
            else SonicMania::SetSpriteAnimation(IconsSpriteID, 0, &Canvas->ActNumbersData, true, 0);
            DrawSprite(&Canvas->ActNumbersData, &SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY), false);
            SonicMania::SetSpriteAnimation(IconsSpriteID, Point.ImageAnimID, &Canvas->ActNumbersData, true, Point.ImageFrameID);
            DrawSprite(&Canvas->ActNumbersData, &SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY), false);
        }
        Canvas->DrawOrder = InitalOrder;
    }

    void DrawEntryText(MenuPoint Point, int x, int y) 
    {
        EntityTitleCard* Canvas = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);
        int InitalOrder = Canvas->DrawOrder;
        Canvas->DrawOrder = GeneralDrawOrder;
        int TextOffsetY = 40;
        if (!Point.isBlank)
        {
            if (Point.YellowText)  Drawing::DrawDevTextSprite(Point.CP_Title, SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY + TextOffsetY), false, 10, 0, 0, DevMenu_Alignment::Alignment_Center, true);
            else Drawing::DrawDevTextSprite(Point.CP_Title, SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY + TextOffsetY), false, 10, 0, 0, DevMenu_Alignment::Alignment_Center, false);
        }
        Canvas->DrawOrder = InitalOrder;
    }

    void DrawEntryTextEXE(MenuPoint Point, int x, int y)
    {
        EntityTitleCard* Canvas = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);
        int InitalOrder = Canvas->DrawOrder;
        Canvas->DrawOrder = GeneralDrawOrder;
        int TextOffsetY = 40;
        if (!Point.isBlank)
        {
            if (Point.YellowText)  Drawing::DrawDevEXETextSprite(Point.CP_Title, SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY + TextOffsetY), false, 10, 0, 0, DevMenu_Alignment::Alignment_Center, true);
            else Drawing::DrawDevEXETextSprite(Point.CP_Title, SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY + TextOffsetY), false, 10, 0, 0, DevMenu_Alignment::Alignment_Center, false);

        }
        Canvas->DrawOrder = InitalOrder;
    }

    void DrawSelector(int x, int y, int IconsSpriteID, EntityTitleCard* Canvas, bool IsSelected)
    {
        int InitalOrder = Canvas->DrawOrder;
        Canvas->DrawOrder = GeneralDrawOrder;
        if (IsSelected)
        {
            if (isSelectorVisible) isSelectorVisible = false;
            else isSelectorVisible = true;
        }
        else isSelectorVisible = true;

        if (isSelectorVisible) 
        {
            SonicMania::SetSpriteAnimation(IconsSpriteID, 0, &Canvas->ActNumbersData, true, 3);
            DrawSprite(&Canvas->ActNumbersData, &SonicMania::Vector2(PosXCurrent + GetPositionOffsetX(), PosYCurrent + GetPositionOffsetY()), false);
        }
        Canvas->DrawOrder = InitalOrder;
    }

    MenuPoint CreateBlankMenuPoint(int x, int y)
    {
        MenuPoint Point = MenuPoint(true, x, y);
        Point.Position = Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY);
        return Point;
    }

    MenuPoint CreateMenuPoint(int y, int x, std::string SceneID, std::string Title, std::string Name, std::string Author, int AnimID, int FrameID, bool isLocked)
    {
        MenuPoint Point = MenuPoint();
        Point.Position = Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY);
        Point.CP_Title = Title.c_str();
        Point.CP_Name = Name.c_str();
        Point.CP_Author = Author.c_str();
        Point.isIZ = true;
        Point.LevelID_IZ = SceneID;
        Point.ImageAnimID = AnimID;
        Point.ImageFrameID = FrameID;
        Point.isLocked = isLocked;
        return Point;
    }

    MenuPoint CreateMenuPoint(int y, int x, int LevelID, std::string Title, std::string Name, std::string Author, int AnimID, int FrameID, bool isLocked)
    {
        MenuPoint Point = MenuPoint();
        Point.Position = Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY);
        Point.CP_Title = Title.c_str();
        Point.CP_Name = Name.c_str();
        Point.CP_Author = Author.c_str();
        Point.isIZ = false;
        Point.LevelID = LevelID;
        Point.ImageAnimID = AnimID;
        Point.ImageFrameID = FrameID;
        Point.isLocked = isLocked;
        return Point;
    }

    void SetupPosition(short MenuPos_X, short MenuPos_Y)
    {
        MenuPos_X -= GetPositionOffsetX();
        MenuPos_Y -= GetPositionOffsetY();
        InitPosition(MenuPos_X, MenuPos_Y);
    }

    void ResetMenuPos(int& MenuPos_X, int& MenuPos_Y, int SMenuPos_X, int SMenuPos_Y, int& LastMenuPos_X, int& LastMenuPos_Y, bool& SwapLevelSelect)
    {
        MenuPos_X = SMenuPos_X;
        MenuPos_Y = SMenuPos_Y;

        LastMenuPos_X = SMenuPos_X;
        LastMenuPos_Y = SMenuPos_Y;

        SwapLevelSelect = false;
    }

    void ResetMenuPos(int& MenuPos_X, int& MenuPos_Y, int& LastMenuPos_X, int& LastMenuPos_Y, bool& SwapLevelSelect)
    {
        MenuPos_X = 0;
        MenuPos_Y = 0;

        LastMenuPos_X = 0;
        LastMenuPos_Y = 0;

        SwapLevelSelect = false;
    }

    void UpdateLevelSelectScroll(int& MenuPos_X, int& MenuPos_Y, int& LastMenuPos_X, int& LastMenuPos_Y, bool& UpdateMenuScroll, MenuPoint** MenuPoints)
    {
        if (MenuPoints[MenuPos_Y][MenuPos_X].isBlank)
        {
            MenuPos_X = MenuPoints[MenuPos_Y][MenuPos_X].RedirectX;
            MenuPos_Y = MenuPoints[MenuPos_Y][MenuPos_X].RedirectY;
        }

        short x1 = MenuPoints[MenuPos_Y][MenuPos_X].Position.X - GetPositionOffsetX();
        short y1 = MenuPoints[MenuPos_Y][MenuPos_X].Position.Y - GetPositionOffsetY();

        short x2 = MenuPoints[LastMenuPos_Y][LastMenuPos_X].Position.X - GetPositionOffsetX();
        short y2 = MenuPoints[LastMenuPos_Y][LastMenuPos_X].Position.Y - GetPositionOffsetY();

        ScrollToPosition(x1, y1, x2, y2, WorldViewX, WorldViewY, UpdateMenuScroll);
        UpdateMenuScroll = false;
    }

    void UpdateLastPos(int& LastMenuPos_X, int& LastMenuPos_Y, int& MenuPos_X, int& MenuPos_Y)
    {
        LastMenuPos_Y = MenuPos_Y;
        LastMenuPos_X = MenuPos_X;
    }

    void Init(std::string modPath) 
    {
        PaletteACT_FilePath = modPath + CompPlus_Common::Act_LSelect;
    }
};