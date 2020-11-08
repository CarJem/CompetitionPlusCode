#include "stdafx.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "include/ManiaAPI/SonicMania.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "CompPlus_Core/CompPlus_Status.h"
#include "HubControllers.h"
namespace CompPlus_HubControllers
{

    using namespace SonicMania;
    using namespace CompPlus_Common;

    bool isSettingChanged = false;	//Controller Press Detection
    int SettingWaitTimer = 100;

    int GetControllerX1()
    {
        return 3;
    }

    int GetControllerX2()
    {
        return 3;
    }

    int GetControllerY1()
    {
        return 10;
    }

    int GetControllerY2()
    {
        return 16;
    }

    void SettingWaitTimerActivate()
    {
        SettingWaitTimer = 10;
    }

    bool ToggleController(int ControlSlotID, bool OldValue)
    {
        Entity& Controller = *GetEntityFromSceneSlot<Entity>(ControlSlotID);

        int x1 = Controller.Position.X - GetControllerX1();
        int y1 = Controller.Position.Y - GetControllerY1();
        int x2 = Controller.Position.X + GetControllerX2();
        int y2 = Controller.Position.Y + GetControllerY2();
        bool NewValue = OldValue;

        for (int RealID = 1; RealID <= 4; RealID++)
        {
            SonicMania::EntityPlayer* Player;
            if (RealID == 1) Player = &Player1;
            else if (RealID == 2) Player = &Player2;
            else if (RealID == 3) Player = &Player3;
            else if (RealID == 4) Player = &Player4;
            else Player = &Player1;

            if (Player->InRange(x1, y1, x2, y2) && Player->Up && !isSettingChanged)
            {
                if (OldValue == true) NewValue = false;
                else NewValue = true;
                CompPlus_Common::PlayMenuMoveSoundFX(false);
                isSettingChanged = true;
                SettingWaitTimerActivate();
            }
            else if (Player->InRange(x1, y1, x2, y2) && Player->Down && !isSettingChanged)
            {
                if (OldValue == true) NewValue = false;
                else NewValue = true;
                CompPlus_Common::PlayMenuMoveSoundFX(false);
                isSettingChanged = true;
                SettingWaitTimerActivate();
            }
            else if (!Player->Up && !Player->Down && isSettingChanged)
            {
                if (SettingWaitTimer == 0) isSettingChanged = false;
            }

            if (isSettingChanged) return NewValue;
        }

        return NewValue;
    }

    int SingleUpDownController(int ControlSlotID, int OldValue, int Min, int Max, bool& isUp)
    {
        Entity& Controller = *GetEntityFromSceneSlot<Entity>(ControlSlotID);

        int x1 = Controller.Position.X - GetControllerX1();
        int y1 = Controller.Position.Y - GetControllerY1();
        int x2 = Controller.Position.X + GetControllerX2();
        int y2 = Controller.Position.Y + GetControllerY2();
        int NewValue = OldValue;

        for (int RealID = 1; RealID <= 4; RealID++)
        {
            SonicMania::EntityPlayer* Player;
            if (RealID == 1) Player = &Player1;
            else if (RealID == 2) Player = &Player2;
            else if (RealID == 3) Player = &Player3;
            else if (RealID == 4) Player = &Player4;
            else Player = &Player1;

            if (Player->InRange(x1, y1, x2, y2) && Player->Up && !isSettingChanged)
            {
                if (OldValue + 1 > Max) NewValue = Min;
                else NewValue = OldValue + 1;
                CompPlus_Common::PlayMenuMoveSoundFX(false);
                isSettingChanged = true;
                SettingWaitTimerActivate();
                isUp = true;
            }
            else if (Player->InRange(x1, y1, x2, y2) && Player->Down && !isSettingChanged)
            {
                if (OldValue - 1 < Min) NewValue = Max;
                else NewValue = OldValue - 1;
                CompPlus_Common::PlayMenuMoveSoundFX(false);
                isSettingChanged = true;
                SettingWaitTimerActivate();
                isUp = false;
            }
            else if (!Player->Up && !Player->Down && isSettingChanged)
            {
                if (SettingWaitTimer == 0) isSettingChanged = false;
            }

            if (isSettingChanged) return NewValue;
        }

        return NewValue;
    }

    int SingleUpDownController(int ControlSlotID, int OldValue, int Min, int Max)
    {
        bool Dummy = false;
        return SingleUpDownController(ControlSlotID, OldValue, Min, Max, Dummy);
    }

    bool ToggleController(int ControlSlotID, bool OldValue, int RealID)
    {
        Entity& Controller = *GetEntityFromSceneSlot<Entity>(ControlSlotID);

        int x1 = Controller.Position.X - GetControllerX1();
        int y1 = Controller.Position.Y - GetControllerY1();
        int x2 = Controller.Position.X + GetControllerX2();
        int y2 = Controller.Position.Y + GetControllerY2();
        bool NewValue = OldValue;

        SonicMania::EntityPlayer* Player;
        if (RealID == 1) Player = &Player1;
        else if (RealID == 2) Player = &Player2;
        else if (RealID == 3) Player = &Player3;
        else if (RealID == 4) Player = &Player4;
        else Player = &Player1;

        if (Player->InRange(x1, y1, x2, y2) && Player->Up && !isSettingChanged)
        {
            if (OldValue == true) NewValue = false;
            else NewValue = true;
            CompPlus_Common::PlayMenuMoveSoundFX(false);
            isSettingChanged = true;
            SettingWaitTimerActivate();
        }
        else if (Player->InRange(x1, y1, x2, y2) && Player->Down && !isSettingChanged)
        {
            if (OldValue == true) NewValue = false;
            else NewValue = true;
            CompPlus_Common::PlayMenuMoveSoundFX(false);
            isSettingChanged = true;
            SettingWaitTimerActivate();
        }
        else if (!Player->Up && !Player->Down && isSettingChanged)
        {
            if (SettingWaitTimer == 0) isSettingChanged = false;
        }

        return NewValue;
    }

    int UpDownController(int ControlSlotID, int OldValue, int Min, int Max, int RealID, bool& isUp)
    {
        Entity& Controller = *GetEntityFromSceneSlot<Entity>(ControlSlotID);

        int x1 = Controller.Position.X - GetControllerX1();
        int y1 = Controller.Position.Y - GetControllerY1();
        int x2 = Controller.Position.X + GetControllerX2();
        int y2 = Controller.Position.Y + GetControllerY2();
        int NewValue = OldValue;

        SonicMania::EntityPlayer* Player;
        if (RealID == 1) Player = &Player1;
        else if (RealID == 2) Player = &Player2;
        else if (RealID == 3) Player = &Player3;
        else if (RealID == 4) Player = &Player4;
        else Player = &Player1;

        if (Player->InRange(x1, y1, x2, y2) && Player->Up && !isSettingChanged)
        {
            if (OldValue + 1 > Max) NewValue = Min;
            else NewValue = OldValue + 1;
            CompPlus_Common::PlayMenuMoveSoundFX(false);
            isSettingChanged = true;
            SettingWaitTimerActivate();
            isUp = true;
        }
        else if (Player->InRange(x1, y1, x2, y2) && Player->Down && !isSettingChanged)
        {
            if (OldValue - 1 < Min) NewValue = Max;
            else NewValue = OldValue - 1;
            CompPlus_Common::PlayMenuMoveSoundFX(false);
            isSettingChanged = true;
            SettingWaitTimerActivate();
            isUp = false;
        }
        else if (!Player->Up && !Player->Down && isSettingChanged)
        {
            if (SettingWaitTimer == 0) isSettingChanged = false;
        }

        return NewValue;
    }

    void ChangeCharacter(int PlayerID, int Value)
    {
        CompPlus_Settings::UpdatePlayer(PlayerID, (CompPlus_Settings::ChosenPlayer)Value, CompPlus_Status::Abilities_CanDynamicallyChangeEffects);
        CompPlus_Settings::SetAbility(PlayerID, (CompPlus_Settings::PlayerAbility)Value, CompPlus_Status::Abilities_CanDynamicallyChangeEffects);
    }

    void ChangeAbility(int PlayerID, int Value, bool isUp)
    {
        bool CanForce = CompPlus_Status::Abilities_CanDynamicallyChangeEffects;

        CompPlus_Settings::PlayerAbility Ability = (CompPlus_Settings::PlayerAbility)Value;
        CompPlus_Settings::ChosenPlayer ChosenPlayer;

        if (PlayerID == 4) ChosenPlayer = CompPlus_Settings::Player4ChosenPlayer;
        if (PlayerID == 3) ChosenPlayer = CompPlus_Settings::Player3ChosenPlayer;
        if (PlayerID == 2) ChosenPlayer = CompPlus_Settings::Player2ChosenPlayer;
        else ChosenPlayer = CompPlus_Settings::Player1ChosenPlayer;

        CompPlus_Settings::SetAbility(PlayerID, Ability, CanForce);

        if (ChosenPlayer == CompPlus_Settings::ChosenPlayer_Sonic)
        {
            if (isUp)
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Compatibility, CanForce);
            }
            else
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
            }
        }
        if (ChosenPlayer == CompPlus_Settings::ChosenPlayer_Tails)
        {
            if (isUp)
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Tails, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Compatibility, CanForce);
            }
            else
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Tails, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Tails, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
            }
        }
        if (ChosenPlayer == CompPlus_Settings::ChosenPlayer_Knuckles)
        {
            if (isUp)
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Knuckles, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Knuckles, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Compatibility, CanForce);
            }
            else
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Knuckles, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
            }

        }
        if (ChosenPlayer == CompPlus_Settings::ChosenPlayer_Mighty)
        {
            if (isUp)
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Compatibility, CanForce);
            }
            else
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
            }
        }
        if (ChosenPlayer == CompPlus_Settings::ChosenPlayer_Ray)
        {
            if (isUp)
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Ray, CanForce);
            }
            else
            {
                if (Ability == CompPlus_Settings::AbilitySet_Sonic) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Tails) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Knuckles) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Sonic, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Mighty) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Mighty, CanForce);
                else if (Ability == CompPlus_Settings::AbilitySet_Ray) SetAbility(PlayerID, CompPlus_Settings::AbilitySet_Ray, CanForce);
            }
        }
    }

}