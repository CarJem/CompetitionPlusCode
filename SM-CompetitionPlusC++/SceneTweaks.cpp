#include "SceneTweaks.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "ManiaExt.h"

#include "SonicMania.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "CompPlus_Scoring.h"
#include "CompPlus_Common.h"

namespace CompPlus_SceneTweaks
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

    void UpdateTSZ()
    {
        SonicMania::Player1.Right = true;
        SonicMania::Player2.Right = true;
        SonicMania::Player3.Right = true;
        SonicMania::Player4.Right = true;
    }

    void LogoLinking()
    {
        if (SonicMania::CurrentSceneInt == 0) CompPlus_Common::LoadLevel_IZ("CPLOGOS");

        if (SonicMania::CurrentSceneInt == 1)
        {
            SetUIBG_BGColor(199, 235, 255);
            SetUIBG_FGLowColor(247, 146, 24);
            SetUIBG_FGHighColor(57, 178, 206);
        }
    }

    void UpdateScenes(const char* CurrentScene) 
    {
        if (!strcmp(CurrentScene, "0")) LogoLinking();
        else if (!strcmp(CurrentScene, "1")) LogoLinking();
        else if (!strcmp(CurrentScene, "CPSZ")) UpdateSZ();
        else if (!strcmp(CurrentScene, "CPSZE")) UpdateSZ();    
        else if (!strcmp(CurrentScene, "CPTSZ")) UpdateTSZ();
    }
}