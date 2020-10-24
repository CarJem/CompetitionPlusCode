#include "stdafx.h"
#include "CompPlus_Core/CompPlus_DevMenu.h"
#include "Base.h"
#include "ManiaModLoader.h"
#include "SonicMania.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Controllers.h"
#include "CompPlus_Extensions/Helpers.h"
namespace DevMenu_InputMapping
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

    int CurrentX_InputScreen = 0;

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

    int UpdateDevMenu()
    {
        auto con = SonicMania::PlayerControllers[0];
        char result = Key_Enter | Controller_A;
        int centerX = *(_DWORD*)(SonicMania::dword_D3CC00 + 614416);
        int centerY = *(_DWORD*)(SonicMania::dword_D3CC00 + 614420);
        int YPosition = centerY - 84;

        int standard_text_color = 0xFFFFFF;

        int count = 6;
        int optionColors[6];
        for (int i = 0; i < count; ++i)
            optionColors[i] = 0xFFFFFF;
        optionColors[CurrentX_InputScreen] = 0xfff700;


        // Title

        YPosition += 6;
        YPosition += 14;
        YPosition += 20;



        SonicMania::DevMenu_DrawRect(0, 0, 1000, 1000, (CompPlus_Settings::DarkDevMenu ? 0x000000 : 0x009e52), 255, 0, 1);

        DevMenu_DrawText_(centerX, "Sonic Mania - Competition Plus", YPosition - 60, SonicMania::Alignment_Center, standard_text_color);
        DevMenu_DrawText_(centerX, "Input Mapping Editor", YPosition - 48, SonicMania::Alignment_Center, standard_text_color);

        DevMenu_DrawText_(centerX, "Forced Controller Binding:", YPosition, SonicMania::Alignment_Center, standard_text_color);
        YPosition += 14;
        DevMenu_DrawText_(centerX - 96, "Player 1", YPosition, SonicMania::Alignment_Left, optionColors[0]);
        DevMenu_DrawText_(centerX + 96, (CompPlus_Controllers::DevMode_ControlPlayer1 ? "On" : "Off"), YPosition, SonicMania::Alignment_Right, optionColors[0]);
        YPosition += 14;
        DevMenu_DrawText_(centerX - 96, "Player 2", YPosition, SonicMania::Alignment_Left, optionColors[1]);
        DevMenu_DrawText_(centerX + 96, (CompPlus_Controllers::DevMode_ControlPlayer2 ? "On" : "Off"), YPosition, SonicMania::Alignment_Right, optionColors[1]);
        YPosition += 14;
        DevMenu_DrawText_(centerX - 96, "Player 3", YPosition, SonicMania::Alignment_Left, optionColors[2]);
        DevMenu_DrawText_(centerX + 96, (CompPlus_Controllers::DevMode_ControlPlayer3 ? "On" : "Off"), YPosition, SonicMania::Alignment_Right, optionColors[2]);
        YPosition += 14;
        DevMenu_DrawText_(centerX - 96, "Player 4", YPosition, SonicMania::Alignment_Left, optionColors[3]);
        DevMenu_DrawText_(centerX + 96, (CompPlus_Controllers::DevMode_ControlPlayer4 ? "On" : "Off"), YPosition, SonicMania::Alignment_Right, optionColors[3]);
        YPosition += 14;
        DevMenu_DrawText_(centerX, "Other Tweaks:", YPosition, SonicMania::Alignment_Center, standard_text_color);
        YPosition += 14;
        DevMenu_DrawText_(centerX - 96, "Controller Swap", YPosition, SonicMania::Alignment_Left, optionColors[4]);
        DevMenu_DrawText_(centerX + 96, (CompPlus_Controllers::DevMode_ControllerSwap ? "On" : "Off"), YPosition, SonicMania::Alignment_Right, optionColors[4]);
        YPosition += 14;
        DevMenu_DrawText_(centerX - 96, "(CTRL + S)", YPosition, SonicMania::Alignment_Left, optionColors[4]);
        YPosition += 24;
        DevMenu_DrawText_(centerX - 96, "Back", YPosition, SonicMania::Alignment_Left, optionColors[5]);

        if (Key_Up)
        {
            if (!dword_6F0AE4)
            {
                --CurrentX_InputScreen;
                if (CurrentX_InputScreen < 0)
                {
                    CurrentX_InputScreen = count - 1;
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
                ++CurrentX_InputScreen;
                if (CurrentX_InputScreen > count - 1)
                {
                    CurrentX_InputScreen = 0;
                }
            }
            SonicMania::DevMenu_Option = 0;
            SonicMania::DevMenu_Scroll = 0;
            result = (dword_6F0AE4 + 1) & 7;
            dword_6F0AE4 = result;
        }
        else
        {
            result = Key_Enter | Controller_A;
            dword_6F0AE4 = 0;

            if ((Key_Enter | Controller_A) == 1)
            {
                switch (CurrentX_InputScreen)
                {
                case 0:
                    //SonicMania::PlaySoundFXS("Stage/Fail.wav");
                    if (CompPlus_Controllers::DevMode_ControlPlayer1) CompPlus_Controllers::DevMode_ControlPlayer1 = false;
                    else CompPlus_Controllers::DevMode_ControlPlayer1 = true;
                    break;
                case 1:
                    if (CompPlus_Controllers::DevMode_ControlPlayer2) CompPlus_Controllers::DevMode_ControlPlayer2 = false;
                    else CompPlus_Controllers::DevMode_ControlPlayer2 = true;
                    break;
                case 2:
                    if (CompPlus_Controllers::DevMode_ControlPlayer3) CompPlus_Controllers::DevMode_ControlPlayer3 = false;
                    else CompPlus_Controllers::DevMode_ControlPlayer3 = true;
                    break;
                case 3:
                    if (CompPlus_Controllers::DevMode_ControlPlayer4) CompPlus_Controllers::DevMode_ControlPlayer4 = false;
                    else CompPlus_Controllers::DevMode_ControlPlayer4 = true;
                    break;
                case 4:
                    if (CompPlus_Controllers::DevMode_ControllerSwap) CompPlus_Controllers::DevMode_ControllerSwap = false;
                    else CompPlus_Controllers::DevMode_ControllerSwap = true;
                    break;
                case 5: 
                    CurrentDevMenuIndex = 0;
                    CurrentX_InputScreen = 0;
                    break;
                default:
                    break;
                }
            }
            else if (Controller_B)
            {
                CurrentDevMenuIndex = 0;
                CurrentX_InputScreen = 0;
            }
        }


        return result;
    }
}