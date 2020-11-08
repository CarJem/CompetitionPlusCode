#include "stdafx.h"
#include "TailsFlightCancel.h"
#include "include/ManiaAPI/SonicMania.h"
#include "ManiaModLoader.h"
#include "CompPlus_Core/CompPlus_Settings.h"

namespace CompPlus_TailsFlightCancel
{
    using namespace SonicMania;

    void UpdateFlightCancel(SonicMania::EntityPlayer* Player)
    {
        if (Player->Moveset == MOVESET_TAILS)
        {
            auto Controller = Player->GetController();
            if (Player->State == PLAYERSTATE_FLYING)
            {
                if (Controller.Down.Down && (Controller.A.Press || Controller.B.Press))
                {
                    SetSpriteAnimation(GetSpritePointer(0xAC6838, 0xa0C), 10, &Player->Animation, false, 0);
                    Player->State = PLAYERSTATE_JUMP;
                }
            }
        }
    }

    void OnFrame() 
    {
        if (CompPlus_Settings::TailsFlightCancel)
        {
            UpdateFlightCancel(&Player1);
            UpdateFlightCancel(&Player2);
            UpdateFlightCancel(&Player3);
            UpdateFlightCancel(&Player4);
        }
    }
}