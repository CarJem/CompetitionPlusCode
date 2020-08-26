#include "GeneralTweaks.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "ManiaExt.h"

#include "SonicMania.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>

namespace CompPlus_GeneralTweaks
{
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

    void UpdateScenes(const char* CurrentScene) 
    {
        if (!strcmp(CurrentScene, "CPSZ")) UpdateSZ();
        else if (!strcmp(CurrentScene, "CPSZE")) UpdateSZ();    
    }
}