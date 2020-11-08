#pragma once
namespace CompPlus_HubCore
{
    struct INT_Position {

        int X;
        int Y;

        INT_Position(int _x, int _y)
        {
            X = _x;
            Y = _y;
        }

        INT_Position()
        {
            X = 0;
            Y = 0;
        }
    };

    extern bool isRestart;

    enum HubPlace : int
    {
        HubPlace_StartPosition = 0,
        HubPlace_Settings = 1,
        HubPlace_Ranking = 2,
        HubPlace_LevelSelect = 3
    };

    extern HubPlace ReturnDestination;

    extern void LoadDrawables();

    extern void OnDraw();

    extern void SetHUBVisualSettings();
}

