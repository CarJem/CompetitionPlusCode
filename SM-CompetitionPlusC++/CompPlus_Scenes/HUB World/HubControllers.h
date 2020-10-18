#pragma once
namespace CompPlus_HubControllers
{

    extern int SettingWaitTimer;

    extern void SettingWaitTimerActivate();
    extern bool ToggleController(int ControlSlotID, bool OldValue, int RealID);
    extern bool ToggleController(int ControlSlotID, bool OldValue);
    extern int SingleUpDownController(int ControlSlotID, int OldValue, int Min, int Max, bool& isUp);
    extern int SingleUpDownController(int ControlSlotID, int OldValue, int Min, int Max);
    extern int UpDownController(int ControlSlotID, int OldValue, int Min, int Max, int RealID, bool& isUp);
    extern void ChangeCharacter(int PlayerID, int Value);
    extern void ChangeAbility(int PlayerID, int Value, bool isUp);
}