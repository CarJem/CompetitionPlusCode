#include "GeneralTweaks.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "ManiaExt.h"

#include "SonicMania.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "CompPlus_Scoring.h"

namespace CompPlus_GeneralTweaks
{

    bool GustPlanetGravityEnabled = false;

    void UpdateSZ() 
    {
        if (!SonicMania::Timer.Enabled) 
        {
            SonicMania::Player1.Right = true;
            SonicMania::Player2.Right = true;
            SonicMania::Player3.Right = true;
            SonicMania::Player4.Right = true;
        }
    }

    void UpdateTSZ()
    {
        SonicMania::Player1.Right = true;
        SonicMania::Player2.Right = true;
        SonicMania::Player3.Right = true;
        SonicMania::Player4.Right = true;
    }

    void UpdateScenes(const char* CurrentScene) 
    {
        if (!strcmp(CurrentScene, "CPSZ")) UpdateSZ();
        else if (!strcmp(CurrentScene, "CPSZE")) UpdateSZ();    
        else if (!strcmp(CurrentScene, "CPTSZ")) UpdateTSZ();
    }
}