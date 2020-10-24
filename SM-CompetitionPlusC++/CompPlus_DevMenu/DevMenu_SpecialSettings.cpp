#include "stdafx.h"
#include "CompPlus_Core/CompPlus_DevMenu.h"
#include "Base.h"
#include "ManiaModLoader.h"
#include "SonicMania.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Controllers.h"
#include "CompPlus_Extensions/Helpers.h"
#include "CompPlus_Extensions/ManiaExt.h"

namespace DevMenu_SpecialSettings
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
            if (CurrentY == 0) 
            {
                if (addValue) FrameMultiplier += 1;
                else FrameMultiplier -= 1;
            }
            else if (CurrentY == 6)
            {
                if (addValue) CurrentDevMenuIndex = 0;
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

        int CountX = 1;
        int CountY = 7;
        int optionColors[7][1];
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
        DevMenu_DrawText_(centerX, "Special Options", YPosition - 48, SonicMania::Alignment_Center, standard_text_color);

        DevMenu_DrawText_(centerX - 145, "Frame Skip-Rate", YPosition, SonicMania::Alignment_Left, optionColors[0][0]);
        DevMenu_DrawText_(centerX + 94, IntToString(FrameMultiplier).c_str(), YPosition, SonicMania::Alignment_Left, optionColors[0][0]);
        YPosition += 14;
        DevMenu_DrawText_(centerX - 145, "(Backspace Acceleration)", YPosition, SonicMania::Alignment_Left, optionColors[0][0]);
        YPosition += 14;
        DevMenu_DrawText_(centerX - 145, "????", YPosition, SonicMania::Alignment_Left, optionColors[1][0]);
        DevMenu_DrawText_(centerX + 94, "", YPosition, SonicMania::Alignment_Left, optionColors[1][0]);
        YPosition += 14;
        DevMenu_DrawText_(centerX - 145, "????", YPosition, SonicMania::Alignment_Left, optionColors[2][0]);
        DevMenu_DrawText_(centerX + 94, "", YPosition, SonicMania::Alignment_Left, optionColors[2][0]);
        YPosition += 14;
        DevMenu_DrawText_(centerX - 145, "????", YPosition, SonicMania::Alignment_Left, optionColors[3][0]);
        DevMenu_DrawText_(centerX + 94, "", YPosition, SonicMania::Alignment_Left, optionColors[3][0]);
        YPosition += 14;
        DevMenu_DrawText_(centerX - 145, "????", YPosition, SonicMania::Alignment_Left, optionColors[4][0]);
        DevMenu_DrawText_(centerX + 94, "", YPosition, SonicMania::Alignment_Left, optionColors[4][0]);
        YPosition += 14;
        DevMenu_DrawText_(centerX - 145, "????", YPosition, SonicMania::Alignment_Left, optionColors[5][0]);
        DevMenu_DrawText_(centerX + 94, "", YPosition, SonicMania::Alignment_Left, optionColors[5][0]);
        YPosition += 24;
        DevMenu_DrawText_(centerX - 145, "Back", YPosition, SonicMania::Alignment_Left, optionColors[6][0]);

        result = FourWayInputDetection(result, CurrentX_ScoringScreen, CurrentY_ScoringScreen, CountX, CountY);

        return result;
    }
}