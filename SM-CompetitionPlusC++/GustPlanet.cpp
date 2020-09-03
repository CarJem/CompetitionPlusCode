#include "stdafx.h"
#include "GeneralTweaks.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "ManiaExt.h"

#include "include/SonicMania.h"
#include <iostream>
#include <fstream>
#include <vector>

#include "GustPlanet.h"
namespace CompPlus_Scene_GustPlanet 
{

    bool P1_HasAntiGrav = false;
    bool P2_HasAntiGrav = false;
    bool P3_HasAntiGrav = false;
    bool P4_HasAntiGrav = false;

    bool ButtonProvidersInit = false;
    std::vector<int> CurrentSpawns;

    void SwapGravity(int Player, bool State) 
    {
        if (Player == 1) 
        {
            P1_HasAntiGrav = State;
        }
        else if (Player == 2)
        {
            P2_HasAntiGrav = State;
        }
        else if (Player == 3)
        {
            P3_HasAntiGrav = State;
        }
        else if (Player == 4)
        {
            P4_HasAntiGrav = State;
        }
    }

    void ButtonCheckSingle(int i) 
    {
        Button& entity = *SonicMania::GetEntityFromSceneSlot<Button>(CurrentSpawns[i]);

        for (int RealID = 1; RealID <= 4; RealID++)
        {

            int x = entity.Position.X;
            int y = entity.Position.Y;

            int x1 = x - 30;
            int x2 = x + 30;
            int y1 = y - 30;
            int y2 = y + 30;

            bool isPlayerInRange = PlayerInRange(RealID, x1, y1, x2, y2);
            if (isPlayerInRange && entity.Pressed)
            {
                entity.Pressed = false;
                SonicMania::PlaySoundFXS("CompPlus/GPZ_Button.wav");
                if (RealID == 1) SwapGravity(RealID, !P1_HasAntiGrav);
                else if (RealID == 2) SwapGravity(RealID, !P2_HasAntiGrav);
                else if (RealID == 3) SwapGravity(RealID, !P3_HasAntiGrav);
                else if (RealID == 4) SwapGravity(RealID, !P4_HasAntiGrav);

            }
        }
    }

    void CollectAllButtons()
    {
        if (!ButtonProvidersInit)
        {
            for (int i = 0; i < 2301; ++i)
            {
                SonicMania::Entity& entity = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(i);

                if (entity.ObjectID == 57)
                {
                    CurrentSpawns.insert(CurrentSpawns.begin(), i);
                }
            }
            ButtonProvidersInit = true;
        }
    }

    void ButtonCheckLoop()
    {
        CollectAllButtons();
        int length = CurrentSpawns.size();
        for (int i = 0; i < length; ++i) ButtonCheckSingle(i);
    }

    void ApplyAntiGravityToPlayer(SonicMania::EntityPlayer& Player, bool State)
    {
        if (State) 
        {
            Player.GravityStrength = 4168;
            Player.Acceleration = 1072;
            Player.AirAcceleration = 2144;
            Player.InkEffect = SonicMania::Ink_Alpha;
            Player.Alpha = 200;
        }
        else 
        {
            Player.GravityStrength = 14336;
            Player.Acceleration = 3072;
            Player.AirAcceleration = 6144;
            Player.InkEffect = SonicMania::Ink_None;
            Player.Alpha = 256;
        }
    }

    void ApplyAntiGravity() 
    {
        ApplyAntiGravityToPlayer(SonicMania::Player1, P1_HasAntiGrav);
        ApplyAntiGravityToPlayer(SonicMania::Player2, P2_HasAntiGrav);
        ApplyAntiGravityToPlayer(SonicMania::Player3, P3_HasAntiGrav);
        ApplyAntiGravityToPlayer(SonicMania::Player4, P4_HasAntiGrav);
    }

    void OnKill()
    {
        if (SonicMania::Player1.KillFlag != 0) SwapGravity(1, false);
        if (SonicMania::Player2.KillFlag != 0) SwapGravity(2, false);
        if (SonicMania::Player3.KillFlag != 0) SwapGravity(3, false);
        if (SonicMania::Player4.KillFlag != 0) SwapGravity(4, false);
    }

    void OnReset()
    {
        ButtonProvidersInit = false;
        P1_HasAntiGrav = false;
        P2_HasAntiGrav = false;
        P3_HasAntiGrav = false;
        P4_HasAntiGrav = false;
    }

    void OnFrame()
    {
        if (SonicMania::Timer.Enabled == false) OnReset();
        ButtonCheckLoop();
        OnKill();
        ApplyAntiGravity();
    }
}
