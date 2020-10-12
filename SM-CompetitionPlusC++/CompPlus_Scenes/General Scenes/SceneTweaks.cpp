#include "SceneTweaks.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/ManiaExt.h"

#include "SonicMania.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "CompPlus_Extensions/Helpers.h"

#include "CompPlus_Core/CompPlus_Scoring.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Status.h"

namespace CompPlus_SceneTweaks
{
    bool isFBZ2Init = false;
    int StormSlot = 0;
    bool InitStorm = false;

    void UpdateFBZ2(bool inZone)
    {
        if (inZone)
        {
            if (!isFBZ2Init)
            {
                char JMP_Data[2];
                JMP_Data[0] = 0xEB;
                JMP_Data[1] = 0x13;
                WriteData((void*)(baseAddress + 0x125809), JMP_Data);
                isFBZ2Init = true;
            }

            for (int i = 0; i < 2301; ++i)
            {
                SonicMania::Entity& entity = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(i);

                if (entity.ObjectID == 93)
                {
                    if (SonicMania::Timer.Enabled)
                    {
                        FBZStorm& storm = *SonicMania::GetEntityFromSceneSlot<FBZStorm>(i);
                        if (!InitStorm)
                        {
                            storm.State = 128;
                            InitStorm = true;
                        }
                        else
                        {
                            storm.DrawOrder = 0;
                        }
                        
                    }
                    else 
                    {
                        InitStorm = false;
                    }

                }
            }


        }
        else if (isFBZ2Init)
        {
            char JNE_Data[2];
            JNE_Data[0] = 0x75;
            JNE_Data[1] = 0x13;
            WriteData((void*)(baseAddress + 0x125809), JNE_Data);
            isFBZ2Init = false;
        }
    }

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
            SonicMania::SetUIBG_BGColor(199, 235, 255);
            SonicMania::SetUIBG_FGLowColor(247, 146, 24);
            SonicMania::SetUIBG_FGHighColor(57, 178, 206);
        }
    }

    void UpdateScenes(const char* CurrentScene) 
    {
        if (!strcmp(CurrentScene, "SMCP_FBZ2")) UpdateFBZ2(true);
        else if (!strcmp(CurrentScene, "SMCP_FBZ2E")) UpdateFBZ2(true);
        else UpdateFBZ2(false);

        if (!strcmp(CurrentScene, "0")) LogoLinking();
        else if (!strcmp(CurrentScene, "1")) LogoLinking();
        else if (!strcmp(CurrentScene, "CPSZ")) UpdateSZ();
        else if (!strcmp(CurrentScene, "CPSZE")) UpdateSZ();    
        else if (!strcmp(CurrentScene, "CPTSZ")) UpdateTSZ();
    }
}