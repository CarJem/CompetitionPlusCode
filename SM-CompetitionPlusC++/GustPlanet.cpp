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

                if (entity.ObjectID == 56)
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

    int SpeedShoesAcceleration = 6144;
    int SpeedShoesAirAcceleration = 12288;
    int SpeedShoesGravityStrength = 14336;
    int SpeedShoesJumpStrength = 425984;

    int NormalAcceleration = 3072;
    int NormalAirAcceleration = 6144;
    int NormalGravityStrength = 14336;
    int NormalJumpStrength = 425984;

    void ApplyAntiGravityToPlayer(SonicMania::EntityPlayer& Player, bool State)
    {
        if (State) 
        {
            if (Player.SpeedShoesTTL != 0)
            {
                Player.Acceleration = SpeedShoesAcceleration - 2000;
                Player.AirAcceleration = SpeedShoesAirAcceleration - 4000;
                Player.GravityStrength = SpeedShoesGravityStrength - 10168;
            }
            else
            {
                Player.Acceleration = NormalAcceleration - 2000;
                Player.AirAcceleration = NormalAirAcceleration - 4000;
                Player.GravityStrength = NormalGravityStrength - 10168;
            }

            Player.InkEffect = SonicMania::Ink_Alpha;
            Player.Alpha = 200;
        }
        else 
        {
            if (Player.SpeedShoesTTL != 0) 
            {
                Player.Acceleration = SpeedShoesAcceleration;
                Player.AirAcceleration = SpeedShoesAirAcceleration;
                Player.GravityStrength = SpeedShoesGravityStrength;
            }
            else 
            {
                Player.Acceleration = NormalAcceleration;
                Player.AirAcceleration = NormalAirAcceleration;
                Player.GravityStrength = NormalGravityStrength;
            }


            Player.InkEffect = SonicMania::Ink_None;
            Player.Alpha = 256;
        }
    }

    void ApplyAntiGravity() 
    {

        if (SonicMania::Player1.Position.Y <= -20) SonicMania::Player1.Position.Y = -20;
        if (SonicMania::Player2.Position.Y <= -20) SonicMania::Player2.Position.Y = -20;
        if (SonicMania::Player3.Position.Y <= -20) SonicMania::Player3.Position.Y = -20;
        if (SonicMania::Player4.Position.Y <= -20) SonicMania::Player4.Position.Y = -20;

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
