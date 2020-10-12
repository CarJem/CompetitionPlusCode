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

    extern int ReturnDestination;

    extern void OnDraw();

    extern void SetHUBVisualSettings();
}

