#include "EntityLoop.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/ManiaExt.h"

#include "SonicMania.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "RPlaneShifter.h"
#include "SizeLazer.h"
#include "FBZStorm.h"

#include "CompPlus_Extensions/Helpers.h"

#include "CompPlus_Core/CompPlus_Scoring.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Status.h"

#include "CompPlus_Functionality/Halloween2018.h"

namespace CompPlus_EntityLoop
{
    bool LastSizeLazerState = false;

    void OnFrame() 
    {
        bool HasSizeLazer = false;
        for (int i = 0; i < 2301; ++i)
        {
            SonicMania::Entity& entity = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(i);

            if (entity.ObjectID == SonicMania::GetObjectIDFromType(SonicMania::ObjectType_RPlaneShifter))
            {
                CompPlus_RPlaneShifter::OnObject(i);
            }
            else if (entity.ObjectID == SonicMania::GetObjectIDFromType(SonicMania::ObjectType_SizeLazer))
            {
                CompPlus_SizeLazer::OnObject(i);
                HasSizeLazer = true;
            }
            else if (entity.ObjectID == SonicMania::GetObjectIDFromType(SonicMania::ObjectType_FBZStorm))
            {
                CompPlus_FBZStorm::OnObject(i);
                HasSizeLazer = true;
            }
        }

        if (LastSizeLazerState != HasSizeLazer) 
        {
            CompPlus_Status::ForceLoadChibiSprites = HasSizeLazer;
            LastSizeLazerState = HasSizeLazer;
        }

        CompPlus_RPlaneShifter::OnFrame();
    }

    void OnFrameDraw() 
    {
        for (int i = 0; i < 2301; ++i)
        {
            SonicMania::Entity& entity = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(i);
        }
    }
}