#pragma once
namespace CompPlus_Controllers 
{
    extern bool DevMode_ControlPlayer1;
    extern bool DevMode_ControlPlayer2;
    extern bool DevMode_ControlPlayer3;
    extern bool DevMode_ControlPlayer4;

    extern bool DevMode_ControllerSwap;
    extern int DevMode_ControllerSwapPosition;

    extern void DevMode_WarpAllPlayersTo(int PlayerID);

    extern void OnFrame();
}