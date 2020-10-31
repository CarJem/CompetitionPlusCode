#include "FBZ2.h"
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

namespace CompPlus_Scene_FBZ2
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
                //char JMP_Data[2];
                //JMP_Data[0] = 0xEB;
                //JMP_Data[1] = 0x13;
                //WriteData((void*)(baseAddress + 0x125809), JMP_Data);
                isFBZ2Init = true;
            }

            for (int i = 0; i < 2301; ++i)
            {
                SonicMania::Entity& entity = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(i);

                if (entity.ObjectID == 93)
                {
                    if (SonicMania::Timer.Enabled)
                    {
                        SonicMania::DespawnEntity(&entity);
                        //FBZStorm& storm = *SonicMania::GetEntityFromSceneSlot<FBZStorm>(i);
                        if (!InitStorm)
                        {
                            //storm.State = 128;
                            InitStorm = true;
                        }
                        else
                        {
                            //storm.State = (void*)(baseAddress + 0x125820);
                            //storm.DrawOrder = 0;
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
            //char JNE_Data[2];
            //JNE_Data[0] = 0x75;
            //JNE_Data[1] = 0x13;
            //WriteData((void*)(baseAddress + 0x125809), JNE_Data);
            isFBZ2Init = false;
        }
    }

    void OnFrame(const char* CurrentScene)
    {
        if (!strcmp(CurrentScene, CompPlus_Common::SMCP_FBZ2)) UpdateFBZ2(true);
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_FBZ2E)) UpdateFBZ2(true);
        else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_FBZ2_EXE)) UpdateFBZ2(true);
        else UpdateFBZ2(false);
    }
}