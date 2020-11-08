#include "FBZStorm.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/ManiaExt.h"

#include "include/ManiaAPI/SonicMania.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "CompPlus_Extensions/Helpers.h"

#include "CompPlus_Core/CompPlus_Scoring.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Status.h"

namespace CompPlus_FBZStorm
{
    bool StormABrewing = false;

    int StormTimer = 2750;
    int StormInit = 2750;

    bool LightStriking = false;
    int LightAlpha = 128;
    bool SoundPlayed = false;
    int LightAlphaInit = 128;

    void DrawLight() 
    {
        SonicMania::DrawRect(0, 0, 1000, 1000, 0xFFFFFF, LightAlpha, SonicMania::Ink_Alpha, true);
    }

    void OnDrawLightning() 
    {
        if (LightAlpha <= 0) 
        {
            LightAlpha = LightAlphaInit;
            SoundPlayed = false;
            LightStriking = false;
        }
        else 
        {
            if (!SoundPlayed) 
            {
                SonicMania::PlaySoundFXS(CompPlus_Common::SFX_FBZ_Thunder);
                SoundPlayed = true;
            }
            DrawLight();
            LightAlpha -= 1;
        }
    }

    void OnDraw()
    {
        if (StormABrewing) 
        {
            if (StormTimer <= 0)
            {
                LightStriking = true;
                StormTimer = StormInit;
            }
            else if (!LightStriking) StormTimer -= 1;
            if (LightStriking) OnDrawLightning();
        }
    }

    void OnObject(int i)
    {
        //SonicMania::Entity& entity = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(i);
        //SonicMania::DespawnEntity(&entity);
    }

    void OnFrame() 
    {
        //StormABrewing = true;
    }

    void OnReset() 
    {
        StormABrewing = false;
        SoundPlayed = false;
        LightStriking = false;
        StormTimer = StormInit;
    }
}