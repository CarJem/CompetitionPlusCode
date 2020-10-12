#include "stdafx.h"
#include "CompPlus_DevMenu.h"
#include "Base.h"
#include "ManiaModLoader.h"
#include "SonicMania.h"
#include "CompPlus_Settings.h"
#include "CompPlus_Controllers.h"
#include "CompPlus_DevMenu/DevMenu_MainMenu.h"
#include "CompPlus_DevMenu/DevMenu_InputMapping.h"
#include "CompPlus_DevMenu/DevMenu_RankingEditor.h"
#include "CompPlus_DevMenu/DevMenu_SpecialSettings.h"
#include "CompPlus_Extensions/Helpers.h"

DataPointer(DWORD, dword_6F0AE4, 0x002FBB4C);
DataPointer(BYTE, Key_Enter, 0x00441754);

DataPointer(BYTE, Controller_A, 0x0044170C);
DataPointer(BYTE, Controller_B, 0x00441718);

DataPointer(BYTE, Key_Up, 0x004416D8);
DataPointer(BYTE, Key_Down, 0x004416E4);
DataPointer(BYTE, Key_Left, 0x004416F0);
DataPointer(BYTE, Key_Right, 0x004416FC);

DataPointer(HWND, MainWindowHandle, 0x00A53C10);

static bool TrackerP, TrackerS, Tracker1, Tracker2, Tracker3, Tracker4, TrackerO;

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

int CurrentDevMenuIndex = 0;
int LastDevMenuIndex = 0;

int InputScreen_KeyDownIdleTime = 0;
int InputScreen_KeyDownIdleTimeMax = 5;

int CurrentX_InputScreen = 0;

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
    if (CompPlus_Settings::EnableDevMode) 
    {
        bool keyState = GetCtrlKeyState();

        if (CheckKey('P', keyState, &TrackerP) && !KeyPHeld)
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
        if (CheckKey('S', keyState, &TrackerS) && CompPlus_Controllers::DevMode_ControllerSwap && !KeySHeld)
        {
            SonicMania::PlaySoundFXS("Global/Swap.wav");
            CompPlus_Controllers::DevMode_ControlPlayer1 = false;
            CompPlus_Controllers::DevMode_ControlPlayer2 = false;
            CompPlus_Controllers::DevMode_ControlPlayer3 = false;
            CompPlus_Controllers::DevMode_ControlPlayer4 = false;
            CompPlus_Controllers::DevMode_ControllerSwapPosition++;
            if (CompPlus_Controllers::DevMode_ControllerSwapPosition > 3) CompPlus_Controllers::DevMode_ControllerSwapPosition = 0;
            switch (CompPlus_Controllers::DevMode_ControllerSwapPosition)
            {
            case 0:
                CompPlus_Controllers::DevMode_ControlPlayer1 = true;
                SonicMania::PlaySoundFXS("VO/Player1.wav");
                break;
            case 1:
                CompPlus_Controllers::DevMode_ControlPlayer2 = true;
                SonicMania::PlaySoundFXS("VO/Player2.wav");
                break;
            case 2:
                CompPlus_Controllers::DevMode_ControlPlayer3 = true;
                SonicMania::PlaySoundFXS("VO/Player3.wav");
                break;
            case 3:
                CompPlus_Controllers::DevMode_ControlPlayer4 = true;
                SonicMania::PlaySoundFXS("VO/Player4.wav");
                break;
            }
            KeySHeld = true;
        }
        else KeySHeld = false;
        if (CheckKey('O', keyState, &TrackerO))
        {
            CompPlus_Settings::LoadSettings();
        }
        if (CheckKey('1', keyState, &Tracker1) && !Key1Held)
        {
            SonicMania::PlaySoundFXS("Global/Teleport.wav");
            CompPlus_Controllers::DevMode_WarpAllPlayersTo(1);
            Key1Held = true;
        }
        else Key1Held = false;
        if (CheckKey('2', keyState, &Tracker1) && !Key2Held)
        {
            SonicMania::PlaySoundFXS("Global/Teleport.wav");
            CompPlus_Controllers::DevMode_WarpAllPlayersTo(2);
            Key2Held = true;
        }
        else Key2Held = false;
        if (CheckKey('3', keyState, &Tracker1) && !Key3Held)
        {
            SonicMania::PlaySoundFXS("Global/Teleport.wav");
                CompPlus_Controllers::DevMode_WarpAllPlayersTo(3);
                Key3Held = true;
        }
        else Key3Held = false;
        if (CheckKey('4', keyState, &Tracker1) && !Key4Held)
        {
            SonicMania::PlaySoundFXS("Global/Teleport.wav");
                CompPlus_Controllers::DevMode_WarpAllPlayersTo(4);
                Key4Held = true;
        }
        else Key4Held = false;
    }
}

int CompetitionPlus_MainDevMenu()
{
    if (LastDevMenuIndex != CurrentDevMenuIndex) 
    {
        DevMenu_RankingEditor::InputScreen_KeyDownIdleTime = DevMenu_RankingEditor::InputScreen_KeyDownIdleTimeMax;
        DevMenu_SpecialSettings::InputScreen_KeyDownIdleTime = DevMenu_SpecialSettings::InputScreen_KeyDownIdleTimeMax;
        LastDevMenuIndex = CurrentDevMenuIndex;
    }

    if (CurrentDevMenuIndex == 3) return DevMenu_SpecialSettings::UpdateDevMenu();
    else if (CurrentDevMenuIndex == 2) return DevMenu_RankingEditor::UpdateDevMenu();
    else if (CurrentDevMenuIndex == 1) return DevMenu_InputMapping::UpdateDevMenu();
    else return DevMenu_MainMenu::UpdateDevMenu();
}