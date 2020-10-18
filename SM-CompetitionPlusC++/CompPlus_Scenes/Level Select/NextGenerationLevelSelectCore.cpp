#include "stdafx.h"
#include "NextGenerationLevelSelectCore.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/PointScrolling.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "SonicMania.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include <vector>
#include "CompPlus_Core/CompPlus_Scoring.h"
#include "CompPlus_Scenes/HUB World/HubCore.h"
#include "CompPlus_Extensions/Drawing.h"


namespace CompPlus_NextGenerationLevelSelectCore
{
    using namespace CompPlus_Common;

    DataPointer(int, WorldViewX, 0x782A88);
    DataPointer(int, WorldViewY, 0x782A8C);

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

                Entity* FXFade = SpawnObject(GetObjectIDFromType(ObjectType_FXFade), 0, Vector2(Player1.Position.X, Player1.Position.Y - 30));
                EntityFXFade* FxFadeR = (EntityFXFade*)FXFade;

                if (FastWarp)
                {
                    PlaySoundFXS(CompPlus_Common::SFX_SpecialWarp);
                    LevelSelectedWarpSoundPlayed = true;

                    FxFadeR->Time = 0;
                    FxFadeR->SpeedIn = 20;
                    FxFadeR->Wait = 0;
                    FxFadeR->SpeedOut = 0;
                    FxFadeR->Color = 0x000000;
                    FxFadeR->OneWay = true;
                    FxFadeR->EventOnly = false;
                    FxFadeR->Overhud = false;
                    FxFadeR->FadeOutBlack = true;
                }
                else
                {
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

                Entity* FXFade = SpawnObject(GetObjectIDFromType(ObjectType_FXFade), 0, Vector2(Player1.Position.X, Player1.Position.Y - 30));
                EntityFXFade* FxFadeR = (EntityFXFade*)FXFade;

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

                Entity* FXFade = SpawnObject(GetObjectIDFromType(ObjectType_FXFade), 0, Vector2(Player1.Position.X, Player1.Position.Y - 30));
                EntityFXFade* FxFadeR = (EntityFXFade*)FXFade;

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

        stru_26B818[0].playStatus = 0;
    }

    void LevelSelectDelayLoop(int selectorID, const char* levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
    {
        if (FastWarp && SceneLoadWaitTimer < 50)
        {
            SceneLoadWaitTimer = 50;
        }


        if (SceneLoadWaitTimer >= SceneLoadWaitMax)
        {
            LoadLevel_IZ(levelID);
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

                Entity* FXFade = SpawnObject(GetObjectIDFromType(ObjectType_FXFade), 0, Vector2(Player1.Position.X, Player1.Position.Y - 30));
                EntityFXFade* FxFadeR = (EntityFXFade*)FXFade;

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

        stru_26B818[0].playStatus = 0;
    }

    void LevelSelectDelay(bool isClassic, bool& LevelSelected)
    {
        PlayMenuAcceptSoundFX(isClassic);
        LevelSelected = true;
    }

    std::string PaletteACT_FilePath;

    bool PaletteSaved = false;

    SHORT* PaletteStorage3;
    int* PaletteStorage3_Old;
    int PaletteStorage3_Length;

    SHORT* PaletteStorage2;
    int* PaletteStorage2_Old;
    int PaletteStorage2_Length;

    SHORT* PaletteStorage1;
    int* PaletteStorage1_Old;
    int PaletteStorage1_Length;

    SHORT* PaletteStorage0;
    int* PaletteStorage0_Old;
    int PaletteStorage0_Length;

    void OldStorePaletteLoop(int*& PaletteStorage, int& Length, int Source, int SourceLength)
    {
        Length = SourceLength;
        PaletteStorage = new int[Length];
        for (int i = 0; i < Length; i++)
        {
            PaletteStorage[i] = GetPaletteEntry(Source, i);
        }
    }

    void ApplyPaletteOldLoop(int*& PaletteStorage, int& Length, int Source)
    {
        for (int i = 0; i < Length; i++)
        {
            SetPaletteEntry(Source, i, PaletteStorage[i]);
        }
    }

    void ApplyPalette_Old()
    {
        GameStates OldState = GameState;
        GameState = GameState_DevMenu;
        ApplyPaletteOldLoop(PaletteStorage0_Old, PaletteStorage0_Length, 0);
        ApplyPaletteOldLoop(PaletteStorage1_Old, PaletteStorage1_Length, 1);
        ApplyPaletteOldLoop(PaletteStorage2_Old, PaletteStorage2_Length, 2);
        ApplyPaletteOldLoop(PaletteStorage3_Old, PaletteStorage3_Length, 3);
        GameState = OldState;
    }

    void ApplyPalette() 
    {
        for (int i = 0; i < PaletteStorage0_Length; i++) SonicMania::Palette0[i] = PaletteStorage0[i];
        for (int i = 0; i < PaletteStorage1_Length; i++) SonicMania::Palette1[i] = PaletteStorage1[i];
        for (int i = 0; i < PaletteStorage2_Length; i++) SonicMania::Palette2[i] = PaletteStorage2[i];
        for (int i = 0; i < PaletteStorage3_Length; i++) SonicMania::Palette3[i] = PaletteStorage3[i];
    }
        
    void StorePalette_Old() 
    {
        OldStorePaletteLoop(PaletteStorage0_Old, PaletteStorage0_Length, 0, Palette0_Length);
        OldStorePaletteLoop(PaletteStorage1_Old, PaletteStorage1_Length, 1, Palette1_Length);
        OldStorePaletteLoop(PaletteStorage2_Old, PaletteStorage2_Length, 2, Palette2_Length);
        OldStorePaletteLoop(PaletteStorage3_Old, PaletteStorage3_Length, 3, Palette3_Length);
    }

    void StorePalette(std::string filepath)
    {
        unsigned int size = 0;

        // Open file
        std::ifstream file(filepath);

        // Get size and allocate memory
        file.seekg(0, std::ios::end);
        size = static_cast<unsigned int>(file.tellg());
        char* act = (char*)malloc(size);
        file.seekg(0, std::ios::beg);

        // Read file
        file.read(act, size);

        int actCount = size / 3;
        SHORT palette[256];
        BOOL paletteMask[256];
        memset(paletteMask, 0, sizeof(paletteMask));
        for (int i = 0; i < actCount; ++i)
        {
            int color = *(int*)(act + (i * 3)) & 0xFFFFFF;
            paletteMask[i] = !(color == 0xFF00FF);
            palette[i] = SonicMania::ToRGB565(color);
        }

        PaletteStorage0 = palette;
        PaletteStorage0_Length = actCount;
        PaletteStorage1 = palette;
        PaletteStorage1_Length = actCount;
        PaletteStorage2 = palette;
        PaletteStorage2_Length = actCount;
        PaletteStorage3 = palette;
        PaletteStorage3_Length = actCount;
    }

    void EnforcePalette()
    {
        if (!PaletteSaved)
        {
            StorePalette_Old();
            //StorePalette(PaletteACT_FilePath);
            PaletteSaved = true;
        }
        else
        {
            ApplyPalette_Old();
            //ApplyPalette();
        }
    }

    int CurrentDraw_StartX = 0;
    int CurrentDraw_StartY = 0;
    int CurrentDraw_SpacingX = 0;
    int CurrentDraw_SpacingY = 0;

    int GetPositionOffsetX()
    {
        return (WindowSizeX != 0 ? WindowSizeX / 8 : 0);
    }

    int GetPositionOffsetY()
    {
        return (WindowSizeY != 0 ? WindowSizeY / 8 : 0);
    }

    int GetPositionCenterX()
    {
        return (WindowSizeX != 0 ? WindowSizeX / 2 : 0);
    }

    int GetPositionCenterY()
    {
        return (WindowSizeY != 0 ? WindowSizeY / 2 : 0);
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
    }

    void DrawZoneInfo(MenuPoint Point, EntityTitleCard* Canvas) 
    {
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

    }

    void DrawEntryChaotix(MenuPoint Point, int x, int y, int IconsSpriteID, int MenuPos_X, int MenuPos_Y, EntityTitleCard* Canvas)
    {
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
        if (!Point.isBlank)
        {
            if (MenuPos_Y == y && MenuPos_X == x) SonicMania::SetSpriteAnimation(IconsSpriteID, 0, &Canvas->ActNumbersData, true, 1);
            else SonicMania::SetSpriteAnimation(IconsSpriteID, 0, &Canvas->ActNumbersData, true, 0);
            DrawSprite(&Canvas->ActNumbersData, &SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY), false);
            SonicMania::SetSpriteAnimation(IconsSpriteID, Point.ImageAnimID, &Canvas->ActNumbersData, true, Point.ImageFrameID);
            DrawSprite(&Canvas->ActNumbersData, &SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY), false);
        }
    }

    void DrawEntryText(MenuPoint Point, int x, int y) 
    {
        int TextOffsetY = 40;
        if (!Point.isBlank)
        {
            if (Point.YellowText)  Drawing::DrawDevTextSprite(Point.CP_Title, SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY + TextOffsetY), false, 10, 0, 0, DevMenu_Alignment::Alignment_Center, true);
            else Drawing::DrawDevTextSprite(Point.CP_Title, SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY + TextOffsetY), false, 10, 0, 0, DevMenu_Alignment::Alignment_Center, false);

        }
    }

    void DrawEntryTextEXE(MenuPoint Point, int x, int y)
    {
        int TextOffsetY = 40;
        if (!Point.isBlank)
        {
            if (Point.YellowText)  Drawing::DrawDevEXETextSprite(Point.CP_Title, SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY + TextOffsetY), false, 10, 0, 0, DevMenu_Alignment::Alignment_Center, true);
            else Drawing::DrawDevEXETextSprite(Point.CP_Title, SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY + TextOffsetY), false, 10, 0, 0, DevMenu_Alignment::Alignment_Center, false);

        }
    }

    bool isSelectorVisible = false;

    void DrawSelector(int x, int y, int IconsSpriteID, EntityTitleCard* Canvas, bool IsSelected)
    {
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