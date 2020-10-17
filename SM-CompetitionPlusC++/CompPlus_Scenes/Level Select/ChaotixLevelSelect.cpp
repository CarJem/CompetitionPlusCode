#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/PointScrolling.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "SonicMania.h"
#include "Base.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "NextGenerationLevelSelectCore.h"
#include "Base.h"
#include "CompPlus_Extensions/Drawing.h"
#include <vector>
#include <String>


namespace CompPlus_ChaotixLevelSelect
{
    using namespace SonicMania;
    using namespace CompPlus_Core;
    using namespace CompPlus_Common;
    using namespace CompPlus_NextGenerationLevelSelectCore;


    std::vector<std::string> LevelTitles =
    {
        "IIZ 1",
        "AAZ 1",
        "SSZ 1",
        "BBZ 1",
        "MMZ 1",
        "TTZ 1",
        "IIZ 1+",
        "AAZ 1+",
        "SSZ 1+",
        "BBZ 1+",
        "MMZ 1+",
        "TTZ 1+",
        "IIZ 2",
        "AAZ 2",
        "SSZ 2",
        "BBZ 2",
        "MMZ 2",
        "TTZ 2",
        "IIZ 2+",
        "AAZ 2+",
        "SSZ 2+",
        "BBZ 2+",
        "MMZ 2+",
        "TTZ 2+"
    };

    std::vector<std::string> LevelNames =
    {
        "ISOLATED ISLAND ZONE ACT 1",
        "AMAZING ARENA ZONE ACT 1",
        "SPEED SLIDER ZONE ACT 1",
        "BOTANIC BASE ZONE ACT 1",
        "MARINA MADNESS ZONE ACT 1",
        "TECHNO TOWER ZONE ACT 1",

        "ISOLATED ISLAND ZONE ACT 1 (ENCORE)",
        "AMAZING ARENA ZONE ACT 1 (ENCORE)",
        "SPEED SLIDER ZONE ACT 1 (ENCORE)",
        "BOTANIC BASE ZONE ACT 1 (ENCORE)",
        "MARINA MADNESS ZONE ACT 1 (ENCORE)",
        "TECHNO TOWER ZONE ACT 1 (ENCORE)",
        
        "ISOLATED ISLAND ZONE ACT 2",
        "AMAZING ARENA ZONE ACT 2",
        "SPEED SLIDER ZONE ACT 2",
        "BOTANIC BASE ZONE ACT 2",
        "MARINA MADNESS ZONE ACT 2",
        "TECHNO TOWER ZONE ACT 2",

        "ISOLATED ISLAND ZONE ACT 2 (ENCORE)",
        "AMAZING ARENA ZONE ACT 2 (ENCORE)",
        "SPEED SLIDER ZONE ACT 2 (ENCORE)",
        "BOTANIC BASE ZONE ACT 2 (ENCORE)",
        "MARINA MADNESS ZONE ACT 2 (ENCORE)",
        "TECHNO TOWER ZONE ACT 2 (ENCORE)",
    };

    std::vector<std::string> AuthorNames =
    {
        "STAR WARRIOR / MCNUGGIE",
        "THE VAGABOND",
        "NEOEXPERIENCES / MUSIC: COBALTBW"
    };

    bool SwapLevelSelect = false;
    bool LevelSelected = false;
    bool LevelSelectedWarpSoundPlayed = false;

    bool AreMenuPointsLoaded = false;

    int SceneLoadWaitTimer = 0;
    int SceneLoadWaitMax = 100;
    int SwapLevelSelectMax = 100;

    int MenuPos_X = 0;
    int MenuPos_Y = 0;

    int LastMenuPos_X = 0;
    int LastMenuPos_Y = 0;

    bool UpdateMenuScroll = false;

    int MLS_MenuMax_X = 8;
    int MLS_MenuMax_Y = 4;

    int Draw_StartX = 256;
    int Draw_StartY = 256;

    int Draw_SpacingX = 96;
    int Draw_SpacingY = 96;

    MenuPoint** MLS_MenuPoints;

    UIBackgroundDefinition BGColors = UIBackgroundDefinition(SonicMania::Color(102, 71, 95), SonicMania::Color(95, 38, 47), SonicMania::Color(24, 151, 31));


    void SetupMenuPoints()
    {
        Drawing::ReloadDrawables();

        InitDrawVariables(Draw_StartX, Draw_StartY, Draw_SpacingX, Draw_SpacingY);

        MLS_MenuPoints = new MenuPoint * [MLS_MenuMax_Y];
        for (int i = 0; i < MLS_MenuMax_Y; i++) MLS_MenuPoints[i] = new MenuPoint[MLS_MenuMax_X];

        int i = 0;

        MLS_MenuPoints[0][0] = CreateBlankMenuPoint(0, 1);
        MLS_MenuPoints[0][1] = CreateMenuPoint(0, 1, "CPCXMIIZ1", LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 0, false); i++;
        MLS_MenuPoints[0][2] = CreateMenuPoint(0, 2, "CPCXMAAZ", LevelTitles[i], LevelNames[i], AuthorNames[1], 1, 1, false); i++;
        MLS_MenuPoints[0][3] = CreateMenuPoint(0, 3, "CPCXMSSZ1", LevelTitles[i], LevelNames[i], AuthorNames[1], 1, 2, false); i++;
        MLS_MenuPoints[0][4] = CreateMenuPoint(0, 4, "CPCXMBBZ", LevelTitles[i], LevelNames[i], AuthorNames[1], 1, 3, false); i++;
        MLS_MenuPoints[0][5] = CreateMenuPoint(0, 5, "CPCXMMMZ1", LevelTitles[i], LevelNames[i], AuthorNames[1], 1, 4, false); i++;
        MLS_MenuPoints[0][6] = CreateMenuPoint(0, 6, "CPCXMTTZ1", LevelTitles[i], LevelNames[i], AuthorNames[2], 1, 5, false); i++;
        MLS_MenuPoints[0][7] = CreateBlankMenuPoint(7, 1);

        MLS_MenuPoints[1][0] = CreateMenuPoint(1, 0, "CPCLS", "CUSTOM", "", "", 2, 2, false);
        MLS_MenuPoints[1][0].YellowText = true;
        MLS_MenuPoints[1][1] = CreateMenuPoint(1, 1, "CPCXMIIZ1E", LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 0, true); i++;
        MLS_MenuPoints[1][2] = CreateMenuPoint(1, 2, "CPCXMAAZE", LevelTitles[i], LevelNames[i], AuthorNames[1], 1, 1, false); i++;
        MLS_MenuPoints[1][3] = CreateMenuPoint(1, 3, "CPCXMSSZ1E", LevelTitles[i], LevelNames[i], AuthorNames[1], 1, 2, false); i++;
        MLS_MenuPoints[1][4] = CreateMenuPoint(1, 4, "CPCXMBBZE", LevelTitles[i], LevelNames[i], AuthorNames[1], 1, 3, false); i++;
        MLS_MenuPoints[1][5] = CreateMenuPoint(1, 5, "CPCXMMMZ1E", LevelTitles[i], LevelNames[i], AuthorNames[1], 1, 4, false); i++;
        MLS_MenuPoints[1][6] = CreateMenuPoint(1, 6, "CPCXMTTZ1E", LevelTitles[i], LevelNames[i], AuthorNames[2], 1, 5, false); i++;
        MLS_MenuPoints[1][7] = CreateMenuPoint(1, 7, "SMCP_EXE_LS", "EXE", "", "", 2, 1, false);
        MLS_MenuPoints[1][7].YellowText = true;

        MLS_MenuPoints[2][0] = CreateBlankMenuPoint(0, 1);
        MLS_MenuPoints[2][1] = CreateMenuPoint(2, 1, (int)SceneExt::Scene_HCZ1, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 0, true); i++;
        MLS_MenuPoints[2][2] = CreateMenuPoint(2, 2, (int)SceneExt::Scene_HCZ2, LevelTitles[i], LevelNames[i], AuthorNames[1], 1, 1, true); i++;
        MLS_MenuPoints[2][3] = CreateMenuPoint(2, 3, (int)SceneExt::Scene_MSZ1, LevelTitles[i], LevelNames[i], AuthorNames[1], 1, 2, true); i++;
        MLS_MenuPoints[2][4] = CreateMenuPoint(2, 4, (int)SceneExt::Scene_MSZ2, LevelTitles[i], LevelNames[i], AuthorNames[1], 1, 3, true); i++;
        MLS_MenuPoints[2][5] = CreateMenuPoint(2, 5, (int)SceneExt::Scene_OOZ1, LevelTitles[i], LevelNames[i], AuthorNames[1], 1, 4, true); i++;
        MLS_MenuPoints[2][6] = CreateMenuPoint(2, 6, (int)SceneExt::Scene_OOZ2, LevelTitles[i], LevelNames[i], AuthorNames[2], 1, 5, true); i++;
        MLS_MenuPoints[2][7] = CreateBlankMenuPoint(7, 1);

        MLS_MenuPoints[3][0] = CreateBlankMenuPoint(0, 1);
        MLS_MenuPoints[3][1] = CreateMenuPoint(3, 1, (int)SceneExt::Scene_LRZ1, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 0, true); i++;
        MLS_MenuPoints[3][2] = CreateMenuPoint(3, 2, (int)SceneExt::Scene_LRZ2, LevelTitles[i], LevelNames[i], AuthorNames[1], 1, 1, true); i++;
        MLS_MenuPoints[3][3] = CreateMenuPoint(3, 3, (int)SceneExt::Scene_MMZ1, LevelTitles[i], LevelNames[i], AuthorNames[1], 1, 2, true); i++;
        MLS_MenuPoints[3][4] = CreateMenuPoint(3, 4, (int)SceneExt::Scene_MMZ2, LevelTitles[i], LevelNames[i], AuthorNames[1], 1, 3, true); i++;
        MLS_MenuPoints[3][5] = CreateMenuPoint(3, 5, (int)SceneExt::Scene_TMZ1, LevelTitles[i], LevelNames[i], AuthorNames[1], 1, 4, true); i++;
        MLS_MenuPoints[3][6] = CreateMenuPoint(3, 6, (int)SceneExt::Scene_TMZ2, LevelTitles[i], LevelNames[i], AuthorNames[2], 1, 5, true); i++;
        MLS_MenuPoints[3][7] = CreateBlankMenuPoint(7, 1);


        int reset_x = 1;
        int reset_y = 0;

        short start_x = MLS_MenuPoints[reset_y][reset_x].Position.X;
        short start_y = MLS_MenuPoints[reset_y][reset_x].Position.Y;



        ResetMenuPos(MenuPos_X, MenuPos_Y, reset_x, reset_y, LastMenuPos_X, LastMenuPos_Y, SwapLevelSelect);
        SetupPosition(start_x, start_y);

        SetUIBackgroundObject(BGColors);

        AreMenuPointsLoaded = true;
    }

    bool PaletteSaved = false;

    int* PaletteStorage3;
    int PaletteStorage3_Length;

    int* PaletteStorage2;
    int PaletteStorage2_Length;

    int* PaletteStorage1;
    int PaletteStorage1_Length;

    int* PaletteStorage0;
    int PaletteStorage0_Length;

    void StorePalette(int*& PaletteStorage, int& Length, int Source, int SourceLength)
    {
        Length = SourceLength;
        PaletteStorage = new int[Length];
        for (int i = 0; i < Length; i++)
        {
            PaletteStorage[i] = GetPaletteEntry(Source, i);
        }
    }

    void ApplyPalette(int*& PaletteStorage, int& Length, int Source)
    {
        for (int i = 0; i < Length; i++)
        {
            SetPaletteEntry(Source, i, PaletteStorage[i]);
        }
    }

    void EnforcePalette()
    {
        if (!PaletteSaved)
        {
            StorePalette(PaletteStorage0, PaletteStorage0_Length, 0, Palette0_Length);
            StorePalette(PaletteStorage1, PaletteStorage1_Length, 1, Palette1_Length);
            StorePalette(PaletteStorage2, PaletteStorage2_Length, 2, Palette2_Length);
            StorePalette(PaletteStorage3, PaletteStorage3_Length, 3, Palette3_Length);
            PaletteSaved = true;
        }
        else
        {
            ApplyPalette(PaletteStorage0, PaletteStorage0_Length, 0);
            ApplyPalette(PaletteStorage1, PaletteStorage1_Length, 1);
            ApplyPalette(PaletteStorage2, PaletteStorage2_Length, 2);
            ApplyPalette(PaletteStorage3, PaletteStorage3_Length, 3);
        }
    }

    bool isIconsLoaded = false;
    int IconsSpriteID = 0;

    void CheckForPointRefresh()
    {
        AreMenuPointsLoaded = false;
        PaletteSaved = false;
        isIconsLoaded = false;
        Drawing::ReloadDrawables();
    }

    void OnPreload()
    {
        EnforcePalette();
    }

    void OnDraw()
    {
        EnforcePalette();

        if (!AreMenuPointsLoaded) return;

        if (!isIconsLoaded)
        {
            IconsSpriteID = LoadAnimation("CP_LSelect/Icons_Chaotix.bin", Scope_Global);
            isIconsLoaded = true;
            return;
        }

        EntityTitleCard* Canvas = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);

        SonicMania::Vector2 CurrentPosition = SonicMania::Vector2(PosXCurrent + GetPositionOffsetX(), PosYCurrent + GetPositionOffsetY());
        int HalfSize = (WindowSizeX != 0 ? WindowSizeX / 2 : 0);

        int PanelBarsHeight = 30;

        int PanelOffset = 10;

        int TopPanelY = Draw_StartY - PanelBarsHeight - 50 + PanelOffset;
        int BottomPanelY = Draw_StartY + MLS_MenuMax_Y * Draw_SpacingY - PanelBarsHeight - 15 + PanelOffset;
        int CenterPanelHeight = BottomPanelY - TopPanelY;

        int LeftTextX = Draw_StartX - HalfSize + 25;


        Drawing::DrawTitleCardRect(CurrentPosition.X - HalfSize, TopPanelY, WindowSizeX, PanelBarsHeight, 0x000000, 255, InkEffect::Ink_Alpha);
        Drawing::DrawTitleCardRect(CurrentPosition.X - HalfSize, TopPanelY + PanelBarsHeight, WindowSizeX, CenterPanelHeight, 0x612724, 128, InkEffect::Ink_Alpha);
        Drawing::DrawTitleCardRect(CurrentPosition.X - HalfSize, BottomPanelY, WindowSizeX, PanelBarsHeight, 0x000000, 255, InkEffect::Ink_Alpha);

        Drawing::DrawDevTextSprite("CHAOTIX STAGES", Vector2(150, 190 + PanelOffset), false, 14, 0, 0, DevMenu_Alignment::Alignment_Right, false);
        Drawing::DrawDevTextSprite("WELCOME TO THE NEXT LEVEL", Vector2(150, 610 + PanelOffset), false, 14, 0, 0, DevMenu_Alignment::Alignment_Right, false);


        //Draw Zone Buttons
        for (int x = 0; x < MLS_MenuMax_X; x++)
        {
            for (int y = 0; y < MLS_MenuMax_Y; y++)
            {
                MenuPoint Point = MLS_MenuPoints[y][x];
                DrawEntryChaotix(Point, x, y, IconsSpriteID, MenuPos_X, MenuPos_Y, Canvas);
            }
        }
        //Draw Zone Selector
        DrawSelector(PosXCurrent, PosYCurrent, IconsSpriteID, Canvas, LevelSelected);

        //Draw Zone Text
        for (int x = 0; x < MLS_MenuMax_X; x++)
        {
            for (int y = 0; y < MLS_MenuMax_Y; y++)
            {
                MenuPoint Point = MLS_MenuPoints[y][x];
                DrawEntryText(Point, x, y);
            }
        }

        //Draw Zone Info Stuff
        MenuPoint Point = MLS_MenuPoints[MenuPos_Y][MenuPos_X];
        DrawZoneInfo(Point, Canvas);
    }

    bool CooldownActive = false;
    int TimeCurrent = 0;
    int TimeMax = 10;

    void CooldownLoop()
    {
        if (CooldownActive)
        {
            if (TimeCurrent >= TimeMax)
            {
                TimeCurrent = 0;
                CooldownActive = false;
            }
            else TimeCurrent++;
        }
    }

    void OnFrame()
    {
        CompPlus_Common::SetLastLevelSelect(0);
        UniversalLSelectLoop();
        if (!AreMenuPointsLoaded) SetupMenuPoints();

        if (!LevelSelected)
        {
            if (PlayerControllers[0].Up.Down && !CooldownActive)
            {
                if (MenuPos_Y > 0)
                {
                    LastMenuPos_Y = MenuPos_Y;
                    LastMenuPos_X = MenuPos_X;
                    MenuPos_Y = MenuPos_Y--;
                    UpdateMenuScroll = true;
                    PlayMenuMoveSoundFX(false);
                    CooldownActive = true;
                }
            }
            if (PlayerControllers[0].Down.Down && !CooldownActive)
            {
                if (MenuPos_Y < MLS_MenuMax_Y - 1)
                {
                    LastMenuPos_Y = MenuPos_Y;
                    LastMenuPos_X = MenuPos_X;
                    MenuPos_Y = MenuPos_Y++;
                    UpdateMenuScroll = true;
                    PlayMenuMoveSoundFX(false);
                    CooldownActive = true;
                }
            }
            if (PlayerControllers[0].Left.Down && !CooldownActive)
            {
                if (MenuPos_X > 0)
                {
                    LastMenuPos_Y = MenuPos_Y;
                    LastMenuPos_X = MenuPos_X;
                    MenuPos_X = MenuPos_X--;
                    UpdateMenuScroll = true;
                    PlayMenuMoveSoundFX(false);
                    CooldownActive = true;
                }
            }
            if (PlayerControllers[0].Right.Down && !CooldownActive)
            {
                if (MenuPos_X < MLS_MenuMax_X - 1)
                {
                    LastMenuPos_Y = MenuPos_Y;
                    LastMenuPos_X = MenuPos_X;
                    MenuPos_X = MenuPos_X++;
                    UpdateMenuScroll = true;
                    PlayMenuMoveSoundFX(false);
                    CooldownActive = true;
                }
            }

            UpdateLevelSelectScroll(MenuPos_X, MenuPos_Y, LastMenuPos_X, LastMenuPos_Y, UpdateMenuScroll, MLS_MenuPoints);

            if ((PlayerControllers[0].A.Press || PlayerControllers[0].C.Press || PlayerControllers[0].Start.Press || PlayerControllers[0].Select.Press) && !PlayerControllers[0].B.Press)
            {
                if (MLS_MenuPoints[MenuPos_Y][MenuPos_X].OnInteract() == MenuPointState_LoadStage)
                {
                    if (!LevelSelected && HasTransCompleted) LevelSelectDelay(true, LevelSelected);
                }
            }
            else if (PlayerControllers[0].B.Press && HasTransCompleted)
            {
                LevelSelected = true;
                SwapLevelSelect = true;
            }
        }

        CooldownLoop();

        if (LevelSelected)
        {
            if (!SwapLevelSelect) LevelSelectDelayLoop(0, MLS_MenuPoints[MenuPos_Y][MenuPos_X], SwapLevelSelect, SceneLoadWaitTimer, SceneLoadWaitMax, LevelSelected, LevelSelectedWarpSoundPlayed);
            else LevelSelectExitDelayLoop(0, "", SwapLevelSelect, SceneLoadWaitTimer, SwapLevelSelectMax, LevelSelected, LevelSelectedWarpSoundPlayed);
        }
    }

};