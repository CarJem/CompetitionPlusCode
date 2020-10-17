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

#include "CompPlus_Extensions/Helpers.h"

#include "CompPlus_Core/CompPlus_Scoring.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Status.h"

namespace CompPlus_EntityLoop
{
    void OnFrame() 
    {
        for (int i = 0; i < 2301; ++i)
        {
            SonicMania::Entity& entity = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(i);

            if (entity.ObjectID == SonicMania::GetObjectIDFromType(SonicMania::ObjectType_RPlaneShifter))
            {
                CompPlus_RPlaneShifter::OnObject(i);
            }
            if (entity.ObjectID == SonicMania::GetObjectIDFromType(SonicMania::ObjectType_SizeLazer))
            {
                CompPlus_SizeLazer::OnObject(i);
            }
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