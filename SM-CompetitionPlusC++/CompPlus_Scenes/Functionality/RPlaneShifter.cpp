#include "RPlaneShifter.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/ManiaExt.h"

#include "SonicMania.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "CompPlus_Extensions/Helpers.h"

#include "CompPlus_Core/CompPlus_Scoring.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Status.h"

namespace CompPlus_RPlaneShifter
{
    #define RPlaneShifter_Rotating (void*)(baseAddress + 0x1787B0)
    #define RPlaneShifter_SwitchingToBG (void*)(baseAddress + 0x1784B0)
    #define RPlaneShifter_SwitchingToFG (void*)(baseAddress + 0x178B30)

    #define RPlaneShifter_Player_Normal    (void*)(baseAddress + 0xCAD80)
    #define RPlaneShifter_Player_Rotating  (void*)(baseAddress + 0xCAD70)

    struct RPlaneShifter : SonicMania::Entity
    {
        /* 0x00000058 */ void* State;
    };

    bool Player1_HasBeenRotating = false;
    bool Player2_HasBeenRotating = false;
    bool Player3_HasBeenRotating = false;
    bool Player4_HasBeenRotating = false;

    bool Player1_HasCooldown = false;
    bool Player2_HasCooldown = false;
    bool Player3_HasCooldown = false;
    bool Player4_HasCooldown = false;

    int Player1_CooldownID = 0;
    int Player2_CooldownID = 0;
    int Player3_CooldownID = 0;
    int Player4_CooldownID = 0;

    bool Player1_isPositionLocked = false;
    bool Player2_isPositionLocked = false;
    bool Player3_isPositionLocked = false;
    bool Player4_isPositionLocked = false;

    int Player1_CurrentPlane = 0;
    int Player2_CurrentPlane = 0;
    int Player3_CurrentPlane = 0;
    int Player4_CurrentPlane = 0;

    bool Player1_PlaneSwitching = false;
    bool Player2_PlaneSwitching = false;
    bool Player3_PlaneSwitching = false;
    bool Player4_PlaneSwitching = false;

    SonicMania::Vector2 Player1_LockedPosition = SonicMania::Vector2();
    SonicMania::Vector2 Player2_LockedPosition = SonicMania::Vector2();
    SonicMania::Vector2 Player3_LockedPosition = SonicMania::Vector2();
    SonicMania::Vector2 Player4_LockedPosition = SonicMania::Vector2();

    void ChangePlane(SonicMania::EntityPlayer& Player, int Slot)
    {
        switch (Slot)
        {
            case 1:
                Player1_PlaneSwitching = true;
                if (Player.CollisionPlane != 0) Player1_CurrentPlane = 0;
                else Player1_CurrentPlane = 1;
                break;
            case 2:
                Player2_PlaneSwitching = true;
                if (Player.CollisionPlane != 0) Player2_CurrentPlane = 0;
                else Player2_CurrentPlane = 1;
                break;
            case 3:
                Player3_PlaneSwitching = true;
                if (Player.CollisionPlane != 0) Player3_CurrentPlane = 0;
                else Player3_CurrentPlane = 1;
                break;
            case 4:
                Player4_PlaneSwitching = true;
                if (Player.CollisionPlane != 0) Player4_CurrentPlane = 0;
                else Player4_CurrentPlane = 1;
                break;
        }
    }

    void EnforcePlane(SonicMania::EntityPlayer& Player, int Slot, bool State)
    {
        if (State) 
        {
            int SetPosition = 0;
            switch (Slot)
            {
                case 1:
                    if (Player1_CurrentPlane == 0) SetPosition = 0;
                    else SetPosition = 1;
                    break;
                case 2:
                    if (Player2_CurrentPlane == 0) SetPosition = 0;
                    else SetPosition = 1;
                    break;
                case 3:
                    if (Player3_CurrentPlane == 0) SetPosition = 0;
                    else SetPosition = 1;
                    break;
                case 4:
                    if (Player4_CurrentPlane == 0) SetPosition = 0;
                    else SetPosition = 1;
                    break;
            }
            
            if (SetPosition == 0)
            {
                Player.DrawOrder = SonicMania::OBJ_ZONE->DrawOrderLow;
                Player.CollisionPlane = 1;
            }
            else
            {
                Player.DrawOrder = SonicMania::OBJ_ZONE->DrawOrderHigh;
                Player.CollisionPlane = 0;
            }

        }
        else 
        {
            if (Slot == 1) Player1_PlaneSwitching = false;
            else if (Slot == 2) Player2_PlaneSwitching = false;
            else if (Slot == 3) Player3_PlaneSwitching = false;
            else if (Slot == 4) Player4_PlaneSwitching = false;
        }
    }

    void LockXY(SonicMania::EntityPlayer& Player, int Slot)
    {
        switch (Slot) 
        {
            case 1:
                if (Player1_isPositionLocked) return;
                Player1_isPositionLocked = true;
                Player1_LockedPosition.X = Player.Position.X;
                Player1_LockedPosition.Y = Player.Position.Y;
                break;
            case 2:
                if (Player2_isPositionLocked) return;
                Player2_isPositionLocked = true;
                Player2_LockedPosition.X = Player.Position.X;
                Player2_LockedPosition.Y = Player.Position.Y;
                break;
            case 3:
                if (Player3_isPositionLocked) return;
                Player3_isPositionLocked = true;
                Player3_LockedPosition.X = Player.Position.X;
                Player3_LockedPosition.Y = Player.Position.Y;
                break;
            case 4:
                if (Player4_isPositionLocked) return;
                Player4_isPositionLocked = true;
                Player4_LockedPosition.X = Player.Position.X;
                Player4_LockedPosition.Y = Player.Position.Y;
                break;
        }
    }

    void UnlockXY(SonicMania::EntityPlayer& Player, int Slot)
    {
        switch (Slot)
        {
            case 1:
                Player1_isPositionLocked = false;
                Player1_LockedPosition = SonicMania::Vector2();
                break;
            case 2:
                Player2_isPositionLocked = false;
                Player2_LockedPosition = SonicMania::Vector2();
                break;
            case 3:
                Player3_isPositionLocked = false;
                Player3_LockedPosition = SonicMania::Vector2();
                break;
            case 4:
                Player4_isPositionLocked = false;
                Player4_LockedPosition = SonicMania::Vector2();
                break;
        }
    }

    void ShifterFix(SonicMania::EntityPlayer &Player, RPlaneShifter &Shifter, bool &HasBeenRotating, bool &CooldownActive, int &CooldownID, int ShifterIndex, int PlayerID)
    {
        if (Shifter.State == RPlaneShifter_Rotating)
        {
            int x = Player.Position.X;
            int y = Player.Position.Y;

            int x1 = Shifter.Position.X;
            int y1 = Shifter.Position.Y - 32;
            int x2 = Shifter.Position.X;
            int y2 = Shifter.Position.Y;

            if (Player.InRange(x1, y1, x2, y2)) 
            {
                    if (Player.State == RPlaneShifter_Player_Rotating && !CooldownActive)
                {
                    HasBeenRotating = true;
                    LockXY(Player, PlayerID);
                    CooldownActive = true;
                    CooldownID = ShifterIndex;
                }
            }
        }
        else 
        {
            if (HasBeenRotating && CooldownID == ShifterIndex)
            {
                Player.State = RPlaneShifter_Player_Normal;
                HasBeenRotating = false;
                UnlockXY(Player, PlayerID);
                ChangePlane(Player, PlayerID);
            }
        }

        int x1 = Shifter.Position.X - 12;
        int y1 = Shifter.Position.Y - 32;
        int x2 = Shifter.Position.X + 12;
        int y2 = Shifter.Position.Y;

        if (!Player.InRange(x1, y1, x2, y2) && CooldownActive && CooldownID == ShifterIndex)
        {
            CooldownActive = false;
            CooldownID = 0;
            EnforcePlane(Player, PlayerID, false);
        }
        else if (Player.InRange(x1, y1, x2, y2) && CooldownActive && CooldownID == ShifterIndex)
        {
            EnforcePlane(Player, PlayerID, true);
        }
    }

    void OnObject(int Index) 
    {
        RPlaneShifter& Shifter = *SonicMania::GetEntityFromSceneSlot<RPlaneShifter>(Index);
        ShifterFix(SonicMania::Player1, Shifter, Player1_HasBeenRotating, Player1_HasCooldown, Player1_CooldownID, Index, 1);
        ShifterFix(SonicMania::Player2, Shifter, Player2_HasBeenRotating, Player2_HasCooldown, Player2_CooldownID, Index, 2);
        ShifterFix(SonicMania::Player3, Shifter, Player3_HasBeenRotating, Player3_HasCooldown, Player3_CooldownID, Index, 3);
        ShifterFix(SonicMania::Player4, Shifter, Player4_HasBeenRotating, Player4_HasCooldown, Player4_CooldownID, Index, 4);
    }

    void OnFrame() 
    {
        if (Player1_isPositionLocked) 
        {
            SonicMania::Player1.Position.X = Player1_LockedPosition.X;
            SonicMania::Player1.Position.Y = Player1_LockedPosition.Y;
        }
        if (Player2_isPositionLocked) 
        {
            SonicMania::Player2.Position.X = Player2_LockedPosition.X;
            SonicMania::Player2.Position.Y = Player2_LockedPosition.Y;
        }
        if (Player3_isPositionLocked)
        {
            SonicMania::Player3.Position.X = Player3_LockedPosition.X;
            SonicMania::Player3.Position.Y = Player3_LockedPosition.Y;
        }
        if (Player4_isPositionLocked) 
        {
            SonicMania::Player4.Position.X = Player4_LockedPosition.X;
            SonicMania::Player4.Position.Y = Player4_LockedPosition.Y;
        }
    }
}