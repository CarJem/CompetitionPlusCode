#include "stdafx.h"
#include "DynCam.h"
#include "include/ManiaAPI/SonicMania.h"
#include "include/MemAccess.h"
#include "ManiaModLoader.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Status.h"

namespace CompPlus_DynCam 
{
    static int Speed1 = 1;
    static int Speed2 = 3;

    char* LastSceneDirectory;
    char* SceneDirectory = (char*)(baseAddress + 0xA5359C);
    bool LastSceneDirectory_IsValid = false;

    bool AllowDynCam = false;

    bool IsValidDynCamScene()
    {
        if (LastSceneDirectory != SceneDirectory)
        {
            bool result = true;

            if (strcmp(SceneDirectory, "Pinball") == 0) result = false;
            else if (strcmp(SceneDirectory, "SpecialBS") == 0) result = false;
            else if (strcmp(SceneDirectory, "UFO1") == 0) result = false;
            else if (strcmp(SceneDirectory, "UFO2") == 0) result = false;
            else if (strcmp(SceneDirectory, "UFO3") == 0) result = false;
            else if (strcmp(SceneDirectory, "UFO4") == 0) result = false;
            else if (strcmp(SceneDirectory, "UFO5") == 0) result = false;
            else if (strcmp(SceneDirectory, "UFO6") == 0) result = false;
            else if (strcmp(SceneDirectory, "UFO7") == 0) result = false;

            LastSceneDirectory = SceneDirectory;
            LastSceneDirectory_IsValid = result;
            return LastSceneDirectory_IsValid;
        }
        else return LastSceneDirectory_IsValid;
    }

    void UpdateDynCam(SonicMania::EntityPlayer* Player)
    {
        if (Player->Camera != nullptr)
        {
            if (Player->Speed >= 400000)
            {
                if (Player->Camera->OffsetX < 0)
                    Player->Camera->OffsetX += Speed2;
                else if (Player->Camera->OffsetX <= 128)
                    Player->Camera->OffsetX += Speed1;
            }
            else if (Player->Speed <= -400000)
            {
                if (Player->Camera->OffsetX > 0)
                    Player->Camera->OffsetX -= Speed2;
                else if (Player->Camera->OffsetX >= -128)
                    Player->Camera->OffsetX -= Speed1;
            }
            else if (Player->Camera->OffsetX < 0)
                Player->Camera->OffsetX += Speed1;
            else if (Player->Camera->OffsetX > 0)
                Player->Camera->OffsetX -= Speed1;
        }

    }

    void OnFrame()
    {
        if (!CompPlus_Status::DisableDynCam && AllowDynCam)
        {
            if (CompPlus_Settings::Player1DynCam) UpdateDynCam(&SonicMania::Player1);
            if (CompPlus_Settings::Player2DynCam) UpdateDynCam(&SonicMania::Player2);
            if (CompPlus_Settings::Player3DynCam) UpdateDynCam(&SonicMania::Player3);
            if (CompPlus_Settings::Player4DynCam) UpdateDynCam(&SonicMania::Player4);
        }
    }

    void OnUnload() 
    {
        AllowDynCam = false;
    }

    void OnStartTimer() 
    {
        if (IsValidDynCamScene()) AllowDynCam = true;
        else AllowDynCam = false;
    }
}