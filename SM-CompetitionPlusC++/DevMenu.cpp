#include "stdafx.h"
#include "DevMenu.h"
#include "ManiaModLoader.h"
#include "SonicMania.h"
#include "CompPlusSettings.h"

DataPointer(DWORD, dword_6F0AE4, 0x002FBB4C);
DataPointer(BYTE, Key_Enter, 0x00441754);
DataPointer(BYTE, Controller_A, 0x0044170C);
DataPointer(BYTE, Key_Up, 0x004416D8);
DataPointer(BYTE, Key_Down, 0x004416E4);
DataPointer(HWND, MainWindowHandle, 0x00A53C10);

static bool TrackerP, TrackerS, Tracker1, Tracker2, Tracker3, Tracker4;

void* OriginalDevMenu;
bool OriginalDevMenuSaved = false;
bool InCompetitionPlusDevMenu = false;
bool KeyHeld = false;
bool Key1Held = false;
bool Key2Held = false;
bool Key3Held = false;
bool Key4Held = false;
bool KeySHeld = false;
bool KeyPHeld = false;

int currentPlace = 0;

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

bool GetCtrlKeyState()
{
    if (MainWindowHandle == GetActiveWindow())
        return GetAsyncKeyState(VK_LCONTROL) & 1 << 15 || GetAsyncKeyState(VK_RCONTROL) & 1 << 15;
    return false;
}

bool CheckKey(char key, bool state, bool* tracker)
{
    state &= static_cast<bool>(GetAsyncKeyState(key) & 1 << 15);
    if (*tracker && !state)
        *tracker = false;
    if (!*tracker && state)
    {
        *tracker = true;
        return true;
    }
    return false;
}

void PatchCompetitionPlusDevMenu()
{
    OriginalDevMenu = SonicMania::GetAbsAddress<void>(baseAddress + 0x001C25DB);
    OriginalDevMenuSaved = true;
    WriteCall((void*)(baseAddress + 0x001C25DB), CompetitionPlus_MainDevMenu);
}

void PatchOriginalDevMenu()
{
    WriteCall((void*)(baseAddress + 0x001C25DB), OriginalDevMenu);
}

void UpdateCompPlusDevMenu()
{
    bool keyState = GetCtrlKeyState();

    if (CheckKey('P', keyState, &TrackerP) && CompPlusSettings::EnableDevMode && !KeyPHeld)
    {
        if (!InCompetitionPlusDevMenu)
        {
            SonicMania::PlaySoundFXS("Global/BlueShield.wav");
            PatchCompetitionPlusDevMenu();
            InCompetitionPlusDevMenu = true;
        }
        else
        {
            SonicMania::PlaySoundFXS("Global/Hurt.wav");
            if (OriginalDevMenuSaved) PatchOriginalDevMenu();
            InCompetitionPlusDevMenu = false;
        }
        KeyPHeld = true;
    }
    else KeyPHeld = false;

    if (CheckKey('S', keyState, &TrackerS) && CompPlusSettings::DevMode_ControllerSwap && CompPlusSettings::EnableDevMode && !KeySHeld)
    {
        SonicMania::PlaySoundFXS("Global/Swap.wav");
        CompPlusSettings::DevMode_ControlPlayer1 = false;
        CompPlusSettings::DevMode_ControlPlayer2 = false;
        CompPlusSettings::DevMode_ControlPlayer3 = false;
        CompPlusSettings::DevMode_ControlPlayer4 = false;
        CompPlusSettings::DevMode_ControllerSwapPosition++;
        if (CompPlusSettings::DevMode_ControllerSwapPosition > 3) CompPlusSettings::DevMode_ControllerSwapPosition = 0;
        switch (CompPlusSettings::DevMode_ControllerSwapPosition)
        {
            case 0:
                CompPlusSettings::DevMode_ControlPlayer1 = true;
                SonicMania::PlaySoundFXS("VO/Player1.wav");
                break;
            case 1:
                CompPlusSettings::DevMode_ControlPlayer2 = true;
                SonicMania::PlaySoundFXS("VO/Player2.wav");
                break;
            case 2:
                CompPlusSettings::DevMode_ControlPlayer3 = true;
                SonicMania::PlaySoundFXS("VO/Player3.wav");
                break;
            case 3:
                CompPlusSettings::DevMode_ControlPlayer4 = true;
                SonicMania::PlaySoundFXS("VO/Player4.wav");
                break;
        }
        KeySHeld = true;
    }
    else KeySHeld = false;

    if (CheckKey('1', keyState, &Tracker1) && CompPlusSettings::EnableDevMode && !Key1Held)
    {
        SonicMania::PlaySoundFXS("Global/Teleport.wav");
        CompPlusSettings::DevMode_WarpAllPlayersTo(1);
        Key1Held = true;
    }
    else Key1Held = false;
    if (CheckKey('2', keyState, &Tracker1) && CompPlusSettings::EnableDevMode && !Key2Held)
    {
        SonicMania::PlaySoundFXS("Global/Teleport.wav");
        CompPlusSettings::DevMode_WarpAllPlayersTo(2);
        Key2Held = true;
    }
    else Key2Held = false;
    if (CheckKey('3', keyState, &Tracker1) && CompPlusSettings::EnableDevMode && !Key3Held)
    {
        SonicMania::PlaySoundFXS("Global/Teleport.wav");
        CompPlusSettings::DevMode_WarpAllPlayersTo(3);
        Key3Held = true;
    }
    else Key3Held = false;
    if (CheckKey('4', keyState, &Tracker1) && CompPlusSettings::EnableDevMode && !Key4Held)
    {
        SonicMania::PlaySoundFXS("Global/Teleport.wav");
        CompPlusSettings::DevMode_WarpAllPlayersTo(4);
        Key4Held = true;
    }
    else Key4Held = false;
}

int CompetitionPlus_MainDevMenu()
{
    auto con = SonicMania::PlayerControllers[0];
    char result = Key_Enter | Controller_A;
    int centerX = *(_DWORD*)(SonicMania::dword_D3CC00 + 614416);
    int centerY = *(_DWORD*)(SonicMania::dword_D3CC00 + 614420);
    int YPosition = centerY - 84;

    int standard_text_color = 0xFFFFFF;

    int count = 5;
    int optionColors[5];
    for (int i = 0; i < count; ++i)
        optionColors[i] = 0xFFFFFF;
    optionColors[currentPlace] = 0xfff700;


    // Title

    YPosition += 6;
    YPosition += 14;
    YPosition += 20;



    SonicMania::DevMenu_DrawRect(0, 0, 1000, 1000, (CompPlusSettings::DarkDevMenu ? 0x000000 : 0x009e52), 255, 0, 1);

    DevMenu_DrawText_(centerX, "Sonic Mania - Competition Plus", YPosition - 60, SonicMania::Alignment_Center, standard_text_color);
    DevMenu_DrawText_(centerX, "Version 5.0.0 (SAGE DEMO)", YPosition - 48, SonicMania::Alignment_Center, standard_text_color);

    DevMenu_DrawText_(centerX, "Player Binding:", YPosition, SonicMania::Alignment_Center, standard_text_color);
    YPosition += 14;
    DevMenu_DrawText_(centerX - 96, "Player 1", YPosition, SonicMania::Alignment_Left, optionColors[0]);
    DevMenu_DrawText_(centerX + 96, (CompPlusSettings::DevMode_ControlPlayer1 ? "On" : "Off"), YPosition, SonicMania::Alignment_Right, optionColors[0]);
    YPosition += 14;
    DevMenu_DrawText_(centerX - 96, "Player 2", YPosition, SonicMania::Alignment_Left, optionColors[1]);
    DevMenu_DrawText_(centerX + 96, (CompPlusSettings::DevMode_ControlPlayer2 ? "On" : "Off"), YPosition, SonicMania::Alignment_Right, optionColors[1]);
    YPosition += 14;
    DevMenu_DrawText_(centerX - 96, "Player 3", YPosition, SonicMania::Alignment_Left, optionColors[2]);
    DevMenu_DrawText_(centerX + 96, (CompPlusSettings::DevMode_ControlPlayer3 ? "On" : "Off"), YPosition, SonicMania::Alignment_Right, optionColors[2]);
    YPosition += 14;
    DevMenu_DrawText_(centerX - 96, "Player 4", YPosition, SonicMania::Alignment_Left, optionColors[3]);
    DevMenu_DrawText_(centerX + 96, (CompPlusSettings::DevMode_ControlPlayer4 ? "On" : "Off"), YPosition, SonicMania::Alignment_Right, optionColors[3]);
    YPosition += 14;
    DevMenu_DrawText_(centerX, "Options:", YPosition, SonicMania::Alignment_Center, standard_text_color);
    YPosition += 14;
    DevMenu_DrawText_(centerX - 96, "Controller Swap", YPosition, SonicMania::Alignment_Left, optionColors[4]);
    DevMenu_DrawText_(centerX + 96, (CompPlusSettings::DevMode_ControllerSwap ? "On" : "Off"), YPosition, SonicMania::Alignment_Right, optionColors[4]);
    YPosition += 14;
    DevMenu_DrawText_(centerX - 96, "(CTRL + S)", YPosition, SonicMania::Alignment_Left, optionColors[4]);
    YPosition += 30;
    DevMenu_DrawText_(centerX, "(CTRL + P) - Swap Between Dev Menus", YPosition, SonicMania::Alignment_Center, standard_text_color);
    YPosition += 14;
    DevMenu_DrawText_(centerX, "(CTRL + [1-4]) - Warp Everyone to Specified Player", YPosition, SonicMania::Alignment_Center, standard_text_color);
    if (Key_Up)
    {
        if (!dword_6F0AE4)
        {
            --currentPlace;
            if (currentPlace < 0)
            {
                currentPlace = count - 1;
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
            ++currentPlace;
            if (currentPlace > count - 1)
            {
                currentPlace = 0;
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
            switch (currentPlace)
            {
                case 0:
                    SonicMania::PlaySoundFXS("Stage/Fail.wav");
                    //if (CompPlusSettings::DevMode_ControlPlayer1) CompPlusSettings::DevMode_ControlPlayer1 = false;
                    //else CompPlusSettings::DevMode_ControlPlayer1 = true;
                    break;
                case 1:
                    if (CompPlusSettings::DevMode_ControlPlayer2) CompPlusSettings::DevMode_ControlPlayer2 = false;
                    else CompPlusSettings::DevMode_ControlPlayer2 = true;
                    break;
                case 2:
                    if (CompPlusSettings::DevMode_ControlPlayer3) CompPlusSettings::DevMode_ControlPlayer3 = false;
                    else CompPlusSettings::DevMode_ControlPlayer3 = true;
                    break;
                case 3:
                    if (CompPlusSettings::DevMode_ControlPlayer4) CompPlusSettings::DevMode_ControlPlayer4 = false;
                    else CompPlusSettings::DevMode_ControlPlayer4 = true;
                    break;
                case 4:
                    if (CompPlusSettings::DevMode_ControllerSwap) CompPlusSettings::DevMode_ControllerSwap = false;
                    else CompPlusSettings::DevMode_ControllerSwap = true;
                    break;
                default:
                    break;
            }
        }
    }


    return result;
}