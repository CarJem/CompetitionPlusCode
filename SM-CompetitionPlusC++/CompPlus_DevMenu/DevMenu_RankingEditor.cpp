#include "stdafx.h"
#include "CompPlus_Core/CompPlus_DevMenu.h"
#include "Base.h"
#include "ManiaModLoader.h"
#include "SonicMania.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Controllers.h"
#include "CompPlus_Extensions/Helpers.h"

namespace DevMenu_RankingEditor 
{
    using namespace CompPlus_DevMenu;

    DataPointer(DWORD, dword_6F0AE4, 0x002FBB4C);
    DataPointer(BYTE, Key_Enter, 0x00441754);

    DataPointer(BYTE, Controller_A, 0x0044170C);
    DataPointer(BYTE, Controller_B, 0x00441718);

    DataPointer(BYTE, Key_Up, 0x004416D8);
    DataPointer(BYTE, Key_Down, 0x004416E4);
    DataPointer(BYTE, Key_Left, 0x004416F0);
    DataPointer(BYTE, Key_Right, 0x004416FC);

    DataPointer(HWND, MainWindowHandle, 0x00A53C10);


    int InputScreen_KeyDownIdleTime = 0;
    int InputScreen_KeyDownIdleTimeMax = 5;

    int CurrentX_ScoringScreen = 0;
    int CurrentY_ScoringScreen = 0;

    static int loc_DrawText = baseAddress + 0x1D58C0;
    static __declspec(naked) WORD DevMenu_DrawText_(int XPosition, const char* text, int YPosition, SonicMania::DevMenu_Alignment alignment, int color)
    {
        __asm
        {
            mov edx, [ESP + 4]
            mov ecx, [ESP + 8]
            push[ESP + 20]
            push[ESP + 20]
            push[ESP + 20]
            call loc_DrawText
            add esp, 12
            ret
        }
    }

    char InputMenuInputDection(char& result, int& CurrentX, int& CurrentY)
    {
        bool allowInput = false;
        bool addValue = false;

        if (SonicMania::PlayerControllers[0].A.Down && InputScreen_KeyDownIdleTime == 0)
        {
            InputScreen_KeyDownIdleTime = InputScreen_KeyDownIdleTimeMax;
            allowInput = true;
            addValue = true;
        }
        else if (SonicMania::PlayerControllers[0].B.Down && InputScreen_KeyDownIdleTime == 0)
        {
            InputScreen_KeyDownIdleTime = InputScreen_KeyDownIdleTimeMax;
            allowInput = true;
            addValue = false;
        }
        else
        {
            if (InputScreen_KeyDownIdleTime != 0) InputScreen_KeyDownIdleTime -= 1;
        }

        dword_6F0AE4 = 0;

        if (allowInput)
        {
            switch (CurrentY)
            {
            case 0: //Rings
                switch (CurrentX)
                {
                case 0: //ALL
                    if (addValue)
                    {
                        SonicMania::Options->CompetitionSession.Rings_P1 += 1;
                        SonicMania::Options->CompetitionSession.Rings_P2 += 1;
                        SonicMania::Options->CompetitionSession.Rings_P3 += 1;
                        SonicMania::Options->CompetitionSession.Rings_P4 += 1;
                    }
                    else
                    {
                        SonicMania::Options->CompetitionSession.Rings_P1 -= 1;
                        SonicMania::Options->CompetitionSession.Rings_P2 -= 1;
                        SonicMania::Options->CompetitionSession.Rings_P3 -= 1;
                        SonicMania::Options->CompetitionSession.Rings_P4 -= 1;
                    }
                    break;
                case 1: //P1
                    if (addValue) SonicMania::Options->CompetitionSession.Rings_P1 += 1;
                    else  SonicMania::Options->CompetitionSession.Rings_P1 -= 1;
                    break;
                case 2: //P2
                    if (addValue) SonicMania::Options->CompetitionSession.Rings_P2 += 1;
                    else  SonicMania::Options->CompetitionSession.Rings_P2 -= 1;
                    break;
                case 3: //P3
                    if (addValue) SonicMania::Options->CompetitionSession.Rings_P3 += 1;
                    else  SonicMania::Options->CompetitionSession.Rings_P3 -= 1;
                    break;
                case 4: //P4
                    if (addValue) SonicMania::Options->CompetitionSession.Rings_P4 += 1;
                    else  SonicMania::Options->CompetitionSession.Rings_P4 -= 1;
                    break;
                }
                break;
            case 1: //Total Rings
                switch (CurrentX)
                {
                case 0: //ALL
                    if (addValue)
                    {
                        SonicMania::Options->CompetitionSession.TotalRings_P1 += 1;
                        SonicMania::Options->CompetitionSession.TotalRings_P2 += 1;
                        SonicMania::Options->CompetitionSession.TotalRings_P3 += 1;
                        SonicMania::Options->CompetitionSession.TotalRings_P4 += 1;
                    }
                    else
                    {
                        SonicMania::Options->CompetitionSession.TotalRings_P1 -= 1;
                        SonicMania::Options->CompetitionSession.TotalRings_P2 -= 1;
                        SonicMania::Options->CompetitionSession.TotalRings_P3 -= 1;
                        SonicMania::Options->CompetitionSession.TotalRings_P4 -= 1;
                    }
                    break;
                case 1: //P1
                    if (addValue) SonicMania::Options->CompetitionSession.TotalRings_P1 += 1;
                    else  SonicMania::Options->CompetitionSession.TotalRings_P1 -= 1;
                    break;
                case 2: //P2
                    if (addValue) SonicMania::Options->CompetitionSession.TotalRings_P2 += 1;
                    else  SonicMania::Options->CompetitionSession.TotalRings_P2 -= 1;
                    break;
                case 3: //P3
                    if (addValue) SonicMania::Options->CompetitionSession.TotalRings_P3 += 1;
                    else  SonicMania::Options->CompetitionSession.TotalRings_P3 -= 1;
                    break;
                case 4: //P4
                    if (addValue) SonicMania::Options->CompetitionSession.TotalRings_P4 += 1;
                    else  SonicMania::Options->CompetitionSession.TotalRings_P4 -= 1;
                    break;
                }
                break;
            case 2: //Score
                switch (CurrentX)
                {
                case 0: //ALL
                    if (addValue)
                    {
                        SonicMania::Options->CompetitionSession.Score_P1 += 1;
                        SonicMania::Options->CompetitionSession.Score_P2 += 1;
                        SonicMania::Options->CompetitionSession.Score_P3 += 1;
                        SonicMania::Options->CompetitionSession.Score_P4 += 1;
                    }
                    else
                    {
                        SonicMania::Options->CompetitionSession.Score_P1 -= 1;
                        SonicMania::Options->CompetitionSession.Score_P2 -= 1;
                        SonicMania::Options->CompetitionSession.Score_P3 -= 1;
                        SonicMania::Options->CompetitionSession.Score_P4 -= 1;
                    }
                    break;
                case 1: //P1
                    if (addValue) SonicMania::Options->CompetitionSession.Score_P1 += 1;
                    else  SonicMania::Options->CompetitionSession.Score_P1 -= 1;
                    break;
                case 2: //P2
                    if (addValue) SonicMania::Options->CompetitionSession.Score_P2 += 1;
                    else  SonicMania::Options->CompetitionSession.Score_P2 -= 1;
                    break;
                case 3: //P3
                    if (addValue) SonicMania::Options->CompetitionSession.Score_P3 += 1;
                    else  SonicMania::Options->CompetitionSession.Score_P3 -= 1;
                    break;
                case 4: //P4
                    if (addValue) SonicMania::Options->CompetitionSession.Score_P4 += 1;
                    else  SonicMania::Options->CompetitionSession.Score_P4 -= 1;
                    break;
                }
                break;
            case 3: //Items
                switch (CurrentX)
                {
                case 0: //ALL
                    if (addValue)
                    {
                        SonicMania::Options->CompetitionSession.Items_P1 += 1;
                        SonicMania::Options->CompetitionSession.Items_P2 += 1;
                        SonicMania::Options->CompetitionSession.Items_P3 += 1;
                        SonicMania::Options->CompetitionSession.Items_P4 += 1;
                    }
                    else
                    {
                        SonicMania::Options->CompetitionSession.Items_P1 -= 1;
                        SonicMania::Options->CompetitionSession.Items_P2 -= 1;
                        SonicMania::Options->CompetitionSession.Items_P3 -= 1;
                        SonicMania::Options->CompetitionSession.Items_P4 -= 1;
                    }
                    break;
                case 1: //P1
                    if (addValue) SonicMania::Options->CompetitionSession.Items_P1 += 1;
                    else  SonicMania::Options->CompetitionSession.Items_P1 -= 1;
                    break;
                case 2: //P2
                    if (addValue) SonicMania::Options->CompetitionSession.Items_P2 += 1;
                    else  SonicMania::Options->CompetitionSession.Items_P2 -= 1;
                    break;
                case 3: //P3
                    if (addValue) SonicMania::Options->CompetitionSession.Items_P3 += 1;
                    else  SonicMania::Options->CompetitionSession.Items_P3 -= 1;
                    break;
                case 4: //P4
                    if (addValue) SonicMania::Options->CompetitionSession.Items_P4 += 1;
                    else  SonicMania::Options->CompetitionSession.Items_P4 -= 1;
                    break;
                }
                break;
            case 4: //Minutes
                switch (CurrentX)
                {
                case 0: //ALL
                    if (addValue)
                    {
                        SonicMania::Options->CompetitionSession.TimeMinutes_P1 += 1;
                        SonicMania::Options->CompetitionSession.TimeMinutes_P2 += 1;
                        SonicMania::Options->CompetitionSession.TimeMinutes_P3 += 1;
                        SonicMania::Options->CompetitionSession.TimeMinutes_P4 += 1;
                    }
                    else
                    {
                        SonicMania::Options->CompetitionSession.TimeMinutes_P1 -= 1;
                        SonicMania::Options->CompetitionSession.TimeMinutes_P2 -= 1;
                        SonicMania::Options->CompetitionSession.TimeMinutes_P3 -= 1;
                        SonicMania::Options->CompetitionSession.TimeMinutes_P4 -= 1;
                    }
                    break;
                case 1: //P1
                    if (addValue) SonicMania::Options->CompetitionSession.TimeMinutes_P1 += 1;
                    else  SonicMania::Options->CompetitionSession.TimeMinutes_P1 -= 1;
                    break;
                case 2: //P2
                    if (addValue) SonicMania::Options->CompetitionSession.TimeMinutes_P2 += 1;
                    else  SonicMania::Options->CompetitionSession.TimeMinutes_P2 -= 1;
                    break;
                case 3: //P3
                    if (addValue) SonicMania::Options->CompetitionSession.TimeMinutes_P3 += 1;
                    else  SonicMania::Options->CompetitionSession.TimeMinutes_P3 -= 1;
                    break;
                case 4: //P4
                    if (addValue) SonicMania::Options->CompetitionSession.TimeMinutes_P4 += 1;
                    else  SonicMania::Options->CompetitionSession.TimeMinutes_P4 -= 1;
                    break;
                }
                break;
            case 5: //Seconds
                switch (CurrentX)
                {
                case 0: //ALL
                    if (addValue)
                    {
                        SonicMania::Options->CompetitionSession.TimeSeconds_P1 += 1;
                        SonicMania::Options->CompetitionSession.TimeSeconds_P2 += 1;
                        SonicMania::Options->CompetitionSession.TimeSeconds_P3 += 1;
                        SonicMania::Options->CompetitionSession.TimeSeconds_P4 += 1;
                    }
                    else
                    {
                        SonicMania::Options->CompetitionSession.TimeSeconds_P1 -= 1;
                        SonicMania::Options->CompetitionSession.TimeSeconds_P2 -= 1;
                        SonicMania::Options->CompetitionSession.TimeSeconds_P3 -= 1;
                        SonicMania::Options->CompetitionSession.TimeSeconds_P4 -= 1;
                    }
                    break;
                case 1: //P1
                    if (addValue) SonicMania::Options->CompetitionSession.TimeSeconds_P1 += 1;
                    else  SonicMania::Options->CompetitionSession.TimeSeconds_P1 -= 1;
                    break;
                case 2: //P2
                    if (addValue) SonicMania::Options->CompetitionSession.TimeSeconds_P2 += 1;
                    else  SonicMania::Options->CompetitionSession.TimeSeconds_P2 -= 1;
                    break;
                case 3: //P3
                    if (addValue) SonicMania::Options->CompetitionSession.TimeSeconds_P3 += 1;
                    else  SonicMania::Options->CompetitionSession.TimeSeconds_P3 -= 1;
                    break;
                case 4: //P4
                    if (addValue) SonicMania::Options->CompetitionSession.TimeSeconds_P4 += 1;
                    else  SonicMania::Options->CompetitionSession.TimeSeconds_P4 -= 1;
                    break;
                }
                break;
            case 6: //Centiseconds
                switch (CurrentX)
                {
                case 0: //ALL
                    if (addValue)
                    {
                        SonicMania::Options->CompetitionSession.TimeCentiseconds_P1 += 1;
                        SonicMania::Options->CompetitionSession.TimeCentiseconds_P2 += 1;
                        SonicMania::Options->CompetitionSession.TimeCentiseconds_P3 += 1;
                        SonicMania::Options->CompetitionSession.TimeCentiseconds_P4 += 1;
                    }
                    else
                    {
                        SonicMania::Options->CompetitionSession.TimeCentiseconds_P1 -= 1;
                        SonicMania::Options->CompetitionSession.TimeCentiseconds_P2 -= 1;
                        SonicMania::Options->CompetitionSession.TimeCentiseconds_P3 -= 1;
                        SonicMania::Options->CompetitionSession.TimeCentiseconds_P4 -= 1;
                    }
                    break;
                case 1: //P1
                    if (addValue) SonicMania::Options->CompetitionSession.TimeCentiseconds_P1 += 1;
                    else  SonicMania::Options->CompetitionSession.TimeCentiseconds_P1 -= 1;
                    break;
                case 2: //P2
                    if (addValue) SonicMania::Options->CompetitionSession.TimeCentiseconds_P2 += 1;
                    else  SonicMania::Options->CompetitionSession.TimeCentiseconds_P2 -= 1;
                    break;
                case 3: //P3
                    if (addValue) SonicMania::Options->CompetitionSession.TimeCentiseconds_P3 += 1;
                    else  SonicMania::Options->CompetitionSession.TimeCentiseconds_P3 -= 1;
                    break;
                case 4: //P4
                    if (addValue) SonicMania::Options->CompetitionSession.TimeCentiseconds_P4 += 1;
                    else  SonicMania::Options->CompetitionSession.TimeCentiseconds_P4 -= 1;
                    break;
                }
                break;
            case 7: //EXIT
                if (CurrentX == 0) 
                {
                    if (addValue) CurrentDevMenuIndex = 0;
                }
                break;
            }
        }

        return result;
    }
    char FourWayInputDetection(char& result, int& CurrentX, int& CurrentY, int CountX, int CountY)
    {
        if (Key_Up)
        {
            if (!dword_6F0AE4)
            {
                --CurrentY;
                if (CurrentY < 0)
                {
                    CurrentY = CountY - 1;
                }
            }
            SonicMania::DevMenu_Option = 0;
            SonicMania::DevMenu_Scroll = 0;
            result = (dword_6F0AE4 + 1) & 7;
            dword_6F0AE4 = result;
        }
        else if (Key_Down)
        {
            if (!dword_6F0AE4)
            {
                ++CurrentY;
                if (CurrentY > CountY - 1)
                {
                    CurrentY = 0;
                }
            }
            SonicMania::DevMenu_Option = 0;
            SonicMania::DevMenu_Scroll = 0;
            result = (dword_6F0AE4 + 1) & 7;
            dword_6F0AE4 = result;
        }
        else if (Key_Left)
        {
            if (!dword_6F0AE4)
            {
                --CurrentX;
                if (CurrentX < 0)
                {
                    CurrentX = CountX - 1;
                }
            }
            SonicMania::DevMenu_Option = 0;
            SonicMania::DevMenu_Scroll = 0;
            result = (dword_6F0AE4 + 1) & 7;
            dword_6F0AE4 = result;
        }
        else if (Key_Right)
        {
            if (!dword_6F0AE4)
            {
                ++CurrentX;
                if (CurrentX > CountX - 1)
                {
                    CurrentX = 0;
                }
            }
            SonicMania::DevMenu_Option = 0;
            SonicMania::DevMenu_Scroll = 0;
            result = (dword_6F0AE4 + 1) & 7;
            dword_6F0AE4 = result;
        }
        else
        {
            result = InputMenuInputDection(result, CurrentX, CurrentY);
        }


        return result;
    }
    int UpdateDevMenu()
    {
        auto con = SonicMania::PlayerControllers[0];
        char result = Key_Enter | Controller_A;
        int centerX = *(_DWORD*)(SonicMania::dword_D3CC00 + 614416);
        int centerY = *(_DWORD*)(SonicMania::dword_D3CC00 + 614420);
        int YPosition = centerY - 84;

        int standard_text_color = 0xFFFFFF;

        int CountX = 5;
        int CountY = 8;
        int optionColors[8][5];
        for (int i = 0; i < CountX; ++i)
        {
            for (int j = 0; j < CountY; ++j)
            {
                optionColors[i][j] = 0xFFFFFF;
            }
        }

        optionColors[CurrentY_ScoringScreen][CurrentX_ScoringScreen] = 0xfff700;



        // Title
        YPosition += 6;
        YPosition += 14;
        YPosition += 20;



        SonicMania::DevMenu_DrawRect(0, 0, 1000, 1000, (CompPlus_Settings::DarkDevMenu ? 0x000000 : 0x009e52), 255, 0, 1);

        DevMenu_DrawText_(centerX, "Sonic Mania - Competition Plus", YPosition - 60, SonicMania::Alignment_Center, standard_text_color);
        DevMenu_DrawText_(centerX, "Competition Ranking Value Editor", YPosition - 48, SonicMania::Alignment_Center, standard_text_color);



        DevMenu_DrawText_(centerX - 20, "P1", YPosition - 20, SonicMania::Alignment_Center, standard_text_color);
        DevMenu_DrawText_(centerX - 20 + 45, "P2", YPosition - 20, SonicMania::Alignment_Center, standard_text_color);
        DevMenu_DrawText_(centerX - 20 + (45 * 2), "P3", YPosition - 20, SonicMania::Alignment_Center, standard_text_color);
        DevMenu_DrawText_(centerX - 20 + (45 * 3), "P4", YPosition - 20, SonicMania::Alignment_Center, standard_text_color);

        DevMenu_DrawText_(centerX - 145, "Rings", YPosition, SonicMania::Alignment_Left, optionColors[0][0]);
        DevMenu_DrawText_(centerX - 20, IntToString(SonicMania::Options->CompetitionSession.Rings_P1).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[0][1]);
        DevMenu_DrawText_(centerX - 20 + 45, IntToString(SonicMania::Options->CompetitionSession.Rings_P2).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[0][2]);
        DevMenu_DrawText_(centerX - 20 + (45 * 2), IntToString(SonicMania::Options->CompetitionSession.Rings_P3).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[0][3]);
        DevMenu_DrawText_(centerX - 20 + (45 * 3), IntToString(SonicMania::Options->CompetitionSession.Rings_P4).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[0][4]);
        YPosition += 14;
        DevMenu_DrawText_(centerX - 145, "Total Rings", YPosition, SonicMania::Alignment_Left, optionColors[1][0]);
        DevMenu_DrawText_(centerX - 20, IntToString(SonicMania::Options->CompetitionSession.TotalRings_P1).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[1][1]);
        DevMenu_DrawText_(centerX - 20 + 45, IntToString(SonicMania::Options->CompetitionSession.TotalRings_P2).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[1][2]);
        DevMenu_DrawText_(centerX - 20 + (45 * 2), IntToString(SonicMania::Options->CompetitionSession.TotalRings_P3).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[1][3]);
        DevMenu_DrawText_(centerX - 20 + (45 * 3), IntToString(SonicMania::Options->CompetitionSession.TotalRings_P4).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[1][4]);
        YPosition += 14;
        DevMenu_DrawText_(centerX - 145, "Score", YPosition, SonicMania::Alignment_Left, optionColors[2][0]);
        DevMenu_DrawText_(centerX - 20, IntToString(SonicMania::Options->CompetitionSession.Score_P1).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[2][1]);
        DevMenu_DrawText_(centerX - 20 + 45, IntToString(SonicMania::Options->CompetitionSession.Score_P2).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[2][2]);
        DevMenu_DrawText_(centerX - 20 + (45 * 2), IntToString(SonicMania::Options->CompetitionSession.Score_P3).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[2][3]);
        DevMenu_DrawText_(centerX - 20 + (45 * 3), IntToString(SonicMania::Options->CompetitionSession.Score_P4).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[2][4]);
        YPosition += 14;
        DevMenu_DrawText_(centerX - 145, "Items", YPosition, SonicMania::Alignment_Left, optionColors[3][0]);
        DevMenu_DrawText_(centerX - 20, IntToString(SonicMania::Options->CompetitionSession.Items_P1).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[3][1]);
        DevMenu_DrawText_(centerX - 20 + 45, IntToString(SonicMania::Options->CompetitionSession.Items_P2).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[3][2]);
        DevMenu_DrawText_(centerX - 20 + (45 * 2), IntToString(SonicMania::Options->CompetitionSession.Items_P3).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[3][3]);
        DevMenu_DrawText_(centerX - 20 + (45 * 3), IntToString(SonicMania::Options->CompetitionSession.Items_P4).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[3][4]);
        YPosition += 24;
        DevMenu_DrawText_(centerX - 145, "Time", YPosition, SonicMania::Alignment_Left, standard_text_color);
        YPosition += 24;
        DevMenu_DrawText_(centerX - 145, "Minutes", YPosition, SonicMania::Alignment_Left, optionColors[4][0]);
        DevMenu_DrawText_(centerX - 20, IntToString(SonicMania::Options->CompetitionSession.TimeMinutes_P1).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[4][1]);
        DevMenu_DrawText_(centerX - 20 + 45, IntToString(SonicMania::Options->CompetitionSession.TimeMinutes_P2).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[4][2]);
        DevMenu_DrawText_(centerX - 20 + (45 * 2), IntToString(SonicMania::Options->CompetitionSession.TimeMinutes_P3).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[4][3]);
        DevMenu_DrawText_(centerX - 20 + (45 * 3), IntToString(SonicMania::Options->CompetitionSession.TimeMinutes_P4).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[4][4]);
        YPosition += 14;
        DevMenu_DrawText_(centerX - 145, "Seconds", YPosition, SonicMania::Alignment_Left, optionColors[5][0]);
        DevMenu_DrawText_(centerX - 20, IntToString(SonicMania::Options->CompetitionSession.TimeSeconds_P1).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[5][1]);
        DevMenu_DrawText_(centerX - 20 + 45, IntToString(SonicMania::Options->CompetitionSession.TimeSeconds_P2).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[5][2]);
        DevMenu_DrawText_(centerX - 20 + (45 * 2), IntToString(SonicMania::Options->CompetitionSession.TimeSeconds_P3).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[5][3]);
        DevMenu_DrawText_(centerX - 20 + (45 * 3), IntToString(SonicMania::Options->CompetitionSession.TimeSeconds_P4).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[5][4]);
        YPosition += 14;
        DevMenu_DrawText_(centerX - 145, "Centiseconds", YPosition, SonicMania::Alignment_Left, optionColors[6][0]);
        DevMenu_DrawText_(centerX - 20, IntToString(SonicMania::Options->CompetitionSession.TimeCentiseconds_P1).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[6][1]);
        DevMenu_DrawText_(centerX - 20 + 45, IntToString(SonicMania::Options->CompetitionSession.TimeCentiseconds_P2).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[6][2]);
        DevMenu_DrawText_(centerX - 20 + (45 * 2), IntToString(SonicMania::Options->CompetitionSession.TimeCentiseconds_P3).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[6][3]);
        DevMenu_DrawText_(centerX - 20 + (45 * 3), IntToString(SonicMania::Options->CompetitionSession.TimeCentiseconds_P4).c_str(), YPosition, SonicMania::Alignment_Center, optionColors[6][4]);

        YPosition += 24;
        DevMenu_DrawText_(centerX - 145, "Back", YPosition, SonicMania::Alignment_Left, optionColors[7][0]);
        DevMenu_DrawText_(centerX - 20, "????", YPosition, SonicMania::Alignment_Center, optionColors[7][1]);
        DevMenu_DrawText_(centerX - 20 + (45 * 1), "????", YPosition, SonicMania::Alignment_Center, optionColors[7][2]);
        DevMenu_DrawText_(centerX - 20 + (45 * 2), "????", YPosition, SonicMania::Alignment_Center, optionColors[7][3]);
        DevMenu_DrawText_(centerX - 20 + (45 * 3), "????", YPosition, SonicMania::Alignment_Center, optionColors[7][4]);


        result = FourWayInputDetection(result, CurrentX_ScoringScreen, CurrentY_ScoringScreen, CountX, CountY);



        return result;
    }
}