#include "stdafx.h"
#include "CompPlus_Extensions/IZAPI.h"
#include "Base.h"
#include "SonicMania.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "depends/tinyxml2/tinyxml2.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "CompPlus_Extensions/Helpers.h"
#include "CompPlus_Settings.h"

namespace CompPlus_Controllers 
{
    using namespace SonicMania;

    int DevMode_ControllerSwapPosition = 0;
    bool DevMode_ControllerSwap = false;

    bool DevMode_ControlPlayer1 = true;
    bool DevMode_ControlPlayer2 = false;
    bool DevMode_ControlPlayer3 = false;
    bool DevMode_ControlPlayer4 = false;

    Controller InitalInputP1;
    Controller InitalInputP2;
    Controller InitalInputP3;
    Controller InitalInputP4;

    bool P1_InputSaved = false;
    bool P2_InputSaved = false;
    bool P3_InputSaved = false;
    bool P4_InputSaved = false;

    void DevMode_WarpAllPlayersTo(int PlayerID)
    {
        int x, y;
        if (PlayerID == 4)
        {
            x = Player4.Position.X;
            y = Player4.Position.Y;
        }
        else if (PlayerID == 3)
        {
            x = Player3.Position.X;
            y = Player3.Position.Y;
        }
        else if (PlayerID == 2)
        {
            x = Player2.Position.X;
            y = Player2.Position.Y;
        }
        else
        {
            x = Player1.Position.X;
            y = Player1.Position.Y;
        }

        Player1.Position.X = x;
        Player1.Position.Y = y;

        Player2.Position.X = x;
        Player2.Position.Y = y;

        Player3.Position.X = x;
        Player3.Position.Y = y;

        Player4.Position.X = x;
        Player4.Position.Y = y;
    }

    void DevMode_BindPlayer1()
    {
        if (DevMode_ControlPlayer1 || !CompPlus_Settings::EnableDevMode)
        {
            if (P1_InputSaved)
            {
                SonicMania::PlayerControllers[1] = InitalInputP1;
                P1_InputSaved = false;
            }
            InitalInputP1 = SonicMania::PlayerControllers[1];
        }

        if (!DevMode_ControlPlayer1)
        {
            if (!P1_InputSaved)
            {
                InitalInputP1 = SonicMania::PlayerControllers[1];
                P1_InputSaved = true;

                SonicMania::PlayerControllers[1].A.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].B.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].C.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].X.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Y.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Z.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Up.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Down.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Left.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Right.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Start.Key = (DWORD)0x0;
                SonicMania::PlayerControllers[1].Select.Key = (DWORD)0x0;
            }

        }
    }

    void DevMode_BindController(int TargetPlayerID)
    {
        switch (TargetPlayerID)
        {
        case 2:
            if (!P2_InputSaved)
            {
                InitalInputP2 = SonicMania::PlayerControllers[TargetPlayerID];
                P2_InputSaved = true;
            }
            break;
        case 3:
            if (!P3_InputSaved)
            {
                InitalInputP3 = SonicMania::PlayerControllers[TargetPlayerID];
                P3_InputSaved = true;
            }
            break;
        case 4:
            if (!P4_InputSaved)
            {
                InitalInputP4 = SonicMania::PlayerControllers[TargetPlayerID];
                P4_InputSaved = true;
            }
            break;
        }

        SonicMania::PlayerControllers[TargetPlayerID].A.Key = InitalInputP1.A.Key;
        SonicMania::PlayerControllers[TargetPlayerID].B.Key = InitalInputP1.B.Key;
        SonicMania::PlayerControllers[TargetPlayerID].C.Key = InitalInputP1.C.Key;
        SonicMania::PlayerControllers[TargetPlayerID].X.Key = InitalInputP1.X.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Y.Key = InitalInputP1.Y.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Z.Key = InitalInputP1.Z.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Up.Key = InitalInputP1.Up.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Down.Key = InitalInputP1.Down.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Left.Key = InitalInputP1.Left.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Right.Key = InitalInputP1.Right.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Start.Key = InitalInputP1.Start.Key;
        SonicMania::PlayerControllers[TargetPlayerID].Select.Key = InitalInputP1.Select.Key;

    }

    void DevMode_RestoreController(int TargetPlayerID)
    {
        switch (TargetPlayerID)
        {
        case 2:
            if (P2_InputSaved)
            {
                SonicMania::PlayerControllers[TargetPlayerID] = InitalInputP2;
                P2_InputSaved = false;
            }
            break;
        case 3:
            if (P3_InputSaved)
            {
                SonicMania::PlayerControllers[TargetPlayerID] = InitalInputP3;
                P3_InputSaved = false;
            }
            break;
        case 4:
            if (P4_InputSaved)
            {
                SonicMania::PlayerControllers[TargetPlayerID] = InitalInputP4;
                P4_InputSaved = false;
            }
            break;
        }
    }

    void OnFrame()
    {
        if (CompPlus_Settings::EnableDebugMode)
        {
            DebugEnabled = 1;
        }

        DevMode_BindPlayer1();

        if (CompPlus_Settings::EnableDevMode)
        {
            if (DevMode_ControlPlayer2) DevMode_BindController(2);
            else DevMode_RestoreController(2);

            if (DevMode_ControlPlayer3) DevMode_BindController(3);
            else DevMode_RestoreController(3);

            if (DevMode_ControlPlayer4) DevMode_BindController(4);
            else DevMode_RestoreController(4);
        }
        else
        {
            DevMode_RestoreController(2);
            DevMode_RestoreController(3);
            DevMode_RestoreController(4);
        }
    }
}