#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/ManiaExt.h"

#include "include/SonicMania.h"
#include <iostream>
#include <fstream>
#include <vector>

#include "LHPZ.h"
namespace CompPlus_Scene_LHPZ
{

    void SetSpringSpeed(int slot, int speed)
    {
        *(int*)(baseAddress + 0x0047B010 + (slot * 0x458) + 0x14) = speed;
    }

    void WaterSlidePhysics(int x1, int y1, int x2, int y2, SonicMania::EntityPlayer& player)
    {
        if (x1 > x2)
        {
            int tempX1 = y1;
            x1 = x2;
            x2 = tempX1;
        }
        if (y1 > y2)
        {
            int tempY1 = y1;
            y1 = y2;
            y2 = tempY1;
        }

        if (player.Position.X >= x1 && player.Position.X <= x2 && player.Position.Y >= y1 && player.Position.Y <= y2) 
        {
            if (player.Grounded)  
            {
                player.Direction = 0;
                player.State = PLAYERSTATE_HCZSlide;
                int speed = 550000;
                player.SetVelocity(speed, speed);
            }
        }
    }

    void WaterSlideSetting(int x1, int y1, int x2, int y2)
    {
        WaterSlidePhysics(x1, y1, x2, y2, SonicMania::Player1);
        WaterSlidePhysics(x1, y1, x2, y2, SonicMania::Player2);
        WaterSlidePhysics(x1, y1, x2, y2, SonicMania::Player3);
        WaterSlidePhysics(x1, y1, x2, y2, SonicMania::Player4);

    }

    void LHPZWaterSlides()
    {
        WaterSlideSetting(3720, 2466, 4856, 2602); //Slide 1

        WaterSlideSetting(8960, 1450, 9981, 1628); //Slide 2a
        WaterSlideSetting(9981, 1450, 10017, 1513); //Slide 2b

        WaterSlideSetting(16768, 624, 18432, 740); //Slide 3

        WaterSlideSetting(25964, 1203, 27132, 1353); //Slide 4

        WaterSlideSetting(17519, 852, 18163, 1064); //Slide 5a
        WaterSlideSetting(18163, 962, 19287, 1277); //Slide 5b
        WaterSlideSetting(19287, 1102, 19831, 1320); //Slide 5c
    }

    void OnWait() 
    {
        if (SonicMania::Timer.Enabled == false) 
        {
            SonicMania::Player1.GravityStrength = 0;
            SonicMania::Player2.GravityStrength = 0;
            SonicMania::Player3.GravityStrength = 0;
            SonicMania::Player4.GravityStrength = 0;
        }
        else if (SonicMania::Player1.GravityStrength == 0) 
        {
            SonicMania::Player1.GravityStrength = 14336;
            SonicMania::Player2.GravityStrength = 14336;
            SonicMania::Player3.GravityStrength = 14336;
            SonicMania::Player4.GravityStrength = 14336;
        }

    }

    void OnKill()
    {
        if (SonicMania::Player1.KillFlag != 0) {}
        if (SonicMania::Player2.KillFlag != 0) {}
        if (SonicMania::Player3.KillFlag != 0) {}
        if (SonicMania::Player4.KillFlag != 0) {}
    }

    void OnReset()
    {

    }

    void OnFrame()
    {
        OnWait();
        OnKill();
        LHPZWaterSlides();
        SetSpringSpeed(50, -700000);
    }
}
