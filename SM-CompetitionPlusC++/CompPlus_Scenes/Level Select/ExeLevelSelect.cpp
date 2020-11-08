#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/PointScrolling.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "include/ManiaAPI/SonicMania.h"
#include "Base.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "CoreLevelSelect.h"
#include "Base.h"
#include "CompPlus_Extensions/Drawing.h"
#include <vector>
#include <String>


namespace CompPlus_ExeLevelSelect
{
    using namespace SonicMania;
    using namespace CompPlus_Core;
    using namespace CompPlus_Common;
    using namespace CompPlus_CoreLevelSelect;


    std::vector<std::string> LevelTitles =
    {
        "HZ 1",
        "HZ 2",

        "CPZ 1",
        "CPZ 2",

        "SPZ 1",
        "SPZ 2",

        "FBZ 1",
        "FBZ 2",

        "PGZ 1",
        "PGZ 2",

        "SSZ 1",
        "SSZ 2",

        "HCZ 1",
        "HCZ 2",

        "MSZ 1K",
        "MSZ 2",

        "OOZ 1",
        "OOZ 2",

        "LRZ 1",
        "LRZ 2",

        "MMZ 1",
        "MMZ 2",

        "TMZ 1",
        "TMZ 2"
    };

    std::vector<std::string> LevelNames =
    {
        "HILL ZONE ACT 1",
        "HILL ZONE ACT 2",

        "CHEMICAL PLANT ZONE ACT 1",
        "CHEMICAL PLANT ZONE ACT 2",

        "STUDIOPOLIS ZONE ACT 1",
        "STUDIOPOLIS ZONE ACT 2",

        "FLYING BATTERY ZONE ACT 1",
        "FLYING BATTERY ZONE ACT 2",

        "PRESS GARDEN ZONE ACT 1",
        "PRESS GARDEN ZONE ACT 2",

        "STARDUST SPEEDWAY ZONE ACT 1",
        "STARDUST SPEEDWAY ZONE ACT 2",

        "HYRDOCITY ZONE ACT 1",
        "HYRDOCITY ZONE ACT 2",

        "MIRAGE SALOON ZONE ACT 1K",
        "MIRAGE SALOON ZONE ACT 2",

        "OIL OCEAN ZONE ACT 1",
        "OIL OCEAN ZONE ACT 2",

        "LAVA REEF ZONE ACT 1",
        "LAVA REEF ZONE ACT 2",

        "METALLIC MADNESS ZONE ACT 1",
        "METALLIC MADNESS ZONE ACT 2",

        "TITANIC MONARCH ZONE ACT 1",
        "TITANIC MONARCH ZONE ACT 2"
    };

    std::vector<std::string> AuthorNames =
    {
        "SEGA / MANIA TEAM",
        "SEGA / MANIA TEAM (EDITS: CARJEM GENERATIONS)",
        "SEGA / MANIA TEAM (EDITS: SONIKKO)"
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

    UIBackgroundDefinition BGColors = UIBackgroundDefinition(SonicMania::Color(40, 0, 0), SonicMania::Color(128, 0, 0), SonicMania::Color(32, 32, 32));


    void SetupMenuPoints()
    {
        InitDrawVariables(Draw_StartX, Draw_StartY, Draw_SpacingX, Draw_SpacingY);

        MLS_MenuPoints = new MenuPoint * [MLS_MenuMax_Y];
        for (int i = 0; i < MLS_MenuMax_Y; i++) MLS_MenuPoints[i] = new MenuPoint[MLS_MenuMax_X];

        int i = 0;


        MLS_MenuPoints[0][0] = CreateBlankMenuPoint(0, 1);
        MLS_MenuPoints[0][1] = CreateMenuPoint(0, 1, CompPlus_Common::SMCP_GHZ1_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 0, false); i++;
        MLS_MenuPoints[0][2] = CreateMenuPoint(0, 2, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 0, false); i++;
        MLS_MenuPoints[0][3] = CreateMenuPoint(0, 3, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 1, true); i++;
        MLS_MenuPoints[0][4] = CreateMenuPoint(0, 4, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 1, true); i++;
        MLS_MenuPoints[0][5] = CreateMenuPoint(0, 5, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 2, true); i++;
        MLS_MenuPoints[0][6] = CreateMenuPoint(0, 6, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 2, true); i++;
        MLS_MenuPoints[0][7] = CreateBlankMenuPoint(7, 1);

        MLS_MenuPoints[1][0] = CreateMenuPoint(1, 0, CompPlus_Common::LSelect_Chaotix, "CHAOTIX", "", "", 2, 2, false);
        MLS_MenuPoints[1][0].YellowText = true;
        MLS_MenuPoints[1][1] = CreateMenuPoint(1, 1, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 3, true); i++;
        MLS_MenuPoints[1][2] = CreateMenuPoint(1, 2, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[1], 1, 3, true); i++;
        MLS_MenuPoints[1][3] = CreateMenuPoint(1, 3, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[1], 1, 4, true); i++;
        MLS_MenuPoints[1][4] = CreateMenuPoint(1, 4, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 4, true); i++;
        MLS_MenuPoints[1][5] = CreateMenuPoint(1, 5, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 5, true); i++;
        MLS_MenuPoints[1][6] = CreateMenuPoint(1, 6, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 5, true); i++;
        MLS_MenuPoints[1][7] = CreateMenuPoint(1, 7, CompPlus_Common::LSelect_Mania, "MANIA", "", "", 2, 1, false);
        MLS_MenuPoints[1][7].YellowText = true;

        MLS_MenuPoints[2][0] = CreateBlankMenuPoint(0, 1);
        MLS_MenuPoints[2][1] = CreateMenuPoint(2, 1, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 6, true); i++;
        MLS_MenuPoints[2][2] = CreateMenuPoint(2, 2, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 6, true); i++;
        MLS_MenuPoints[2][3] = CreateMenuPoint(2, 3, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[2], 1, 7, true); i++;
        MLS_MenuPoints[2][4] = CreateMenuPoint(2, 4, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 7, true); i++;
        MLS_MenuPoints[2][5] = CreateMenuPoint(2, 5, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 8, true); i++;
        MLS_MenuPoints[2][6] = CreateMenuPoint(2, 6, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 8, true); i++;
        MLS_MenuPoints[2][7] = CreateBlankMenuPoint(7, 1);

        MLS_MenuPoints[3][0] = CreateBlankMenuPoint(0, 1);
        MLS_MenuPoints[3][1] = CreateMenuPoint(3, 1, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 9, true); i++;
        MLS_MenuPoints[3][2] = CreateMenuPoint(3, 2, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 9, true); i++;
        MLS_MenuPoints[3][3] = CreateMenuPoint(3, 3, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 10, true); i++;
        MLS_MenuPoints[3][4] = CreateMenuPoint(3, 4, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 10, true); i++;
        MLS_MenuPoints[3][5] = CreateMenuPoint(3, 5, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 11, true); i++;
        MLS_MenuPoints[3][6] = CreateMenuPoint(3, 6, CompPlus_Common::SMCP_GHZ2_EXE, LevelTitles[i], LevelNames[i], AuthorNames[0], 1, 11, true); i++;
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

    bool isIconsLoaded = false;
    int IconsSpriteID = 0;

    void Reload()
    {
        AreMenuPointsLoaded = false;
        PaletteSaved = false;
        isIconsLoaded = false;
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
            IconsSpriteID = LoadAnimation(CompPlus_Common::Anim_LSelectIcons_Exe, Scope_Stage);
            isIconsLoaded = true;
            return;
        }

        EntityTitleCard* Canvas = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);
        int DrawOrderOld = Canvas->DrawOrder;
        Canvas->DrawOrder = CompPlus_CoreLevelSelect::GeneralDrawOrder;

        SonicMania::Vector2 CurrentPosition = SonicMania::Vector2(PosXCurrent + GetPositionOffsetX(), PosYCurrent + GetPositionOffsetY());
        int HalfSize = (WindowSizeX != 0 ? WindowSizeX / 2 : 0);

        int PanelBarsHeight = 30;

        int PanelOffset = 10;

        int TopPanelY = Draw_StartY - PanelBarsHeight - 50 + PanelOffset;
        int BottomPanelY = Draw_StartY + MLS_MenuMax_Y * Draw_SpacingY - PanelBarsHeight - 15 + PanelOffset;
        int CenterPanelHeight = BottomPanelY - TopPanelY;

        int LeftTextX = Draw_StartX - HalfSize + 25;


        Drawing::DrawTitleCardRect(CurrentPosition.X - HalfSize, TopPanelY, WindowSizeX, PanelBarsHeight, 0x000000, 255, InkEffect::Ink_Alpha);
        Drawing::DrawTitleCardRect(CurrentPosition.X - HalfSize, TopPanelY + PanelBarsHeight, WindowSizeX, CenterPanelHeight, 0xFF0000, 128, InkEffect::Ink_Alpha);
        Drawing::DrawTitleCardRect(CurrentPosition.X - HalfSize, BottomPanelY, WindowSizeX, PanelBarsHeight, 0x000000, 255, InkEffect::Ink_Alpha);

        Drawing::DrawDevEXETextSprite("EXECUTOR STAGES", Vector2(150, 190 + PanelOffset), false, CompPlus_CoreLevelSelect::GeneralDrawOrder, 0, 0, DevMenu_Alignment::Alignment_Right, false);
        Drawing::DrawDevEXETextSprite("DO YOU WANT TO PLAY WITH ME", Vector2(150, 610 + PanelOffset), false, CompPlus_CoreLevelSelect::GeneralDrawOrder, 0, 0, DevMenu_Alignment::Alignment_Right, false);


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
                DrawEntryTextEXE(Point, x, y);
            }
        }

        //Draw Zone Info Stuff
        MenuPoint Point = MLS_MenuPoints[MenuPos_Y][MenuPos_X];
        DrawZoneInfo(Point, Canvas);
        Canvas->DrawOrder = DrawOrderOld;
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
        CompPlus_Common::SetLastLevelSelect(4);
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