#include "SizeLazer.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "Base.h"

#include "SonicMania.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "CompPlus_Extensions/Helpers.h"

#include "CompPlus_Core/CompPlus_Scoring.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Status.h"

namespace CompPlus_SizeLazer 
{
    using namespace SonicMania;

    struct SizeLazer : SonicMania::Entity
    {
        /* 0x00000058 */ void* State;
        /* 0x00000060 */ int Dummy4;
        /* 0x00000064 */ int Dummy3;
        /* 0x00000068 */ int Dummy2;
        /* 0x0000006C */ BYTE Extend;
    };

    bool RefreshChibiSprites = true;
    int FrameTimeOut = 5000;
    int CurrentTimeOut = 0;

    bool IsValidToRefresh() 
    {
        if (RefreshChibiSprites) 
        {
            if (CurrentTimeOut >= FrameTimeOut)
            {
                CurrentTimeOut = 0;
                return true;
            }
            else
            {
                CurrentTimeOut++;
                return false;
            }
        }
        else 
        {
            CurrentTimeOut = 0;
            return false;
        }
    }

    void LoadChibiSprites()
    {
        if (IsValidToRefresh() && CompPlus_Status::ForceLoadChibiSprites && SonicMania::Timer.Enabled)
        {
            if (GetAddress(baseAddress + 0xAC6758, 0x6E))
            {
                int ChibiSonic = LoadAnimation("Players/ChibiSonic.bin", Scope_Stage);
                *(BYTE*)GetAddress(baseAddress + 0xAC6758, 0x6E) = ChibiSonic;
            }
            if (GetAddress(baseAddress + 0xAC6758, 0x70))
            {
                int ChibiTails = LoadAnimation("Players/ChibiTails.bin", Scope_Stage);
                *(BYTE*)GetAddress(baseAddress + 0xAC6758, 0x70) = ChibiTails;
            }
            if (GetAddress(baseAddress + 0xAC6758, 0x72))
            {
                int CTailSprite = LoadAnimation("Players/CTailSprite.bin", Scope_Stage);
                *(BYTE*)GetAddress(baseAddress + 0xAC6758, 0x72) = CTailSprite;
            }
            if (GetAddress(baseAddress + 0xAC6758, 0x74))
            {
                int ChibiKnux = LoadAnimation("Players/ChibiKnux.bin", Scope_Stage);
                *(BYTE*)GetAddress(baseAddress + 0xAC6758, 0x74) = ChibiKnux;
            }
            if (GetAddress(baseAddress + 0xAC6758, 0x76))
            {
                int ChibiMighty = LoadAnimation("Players/ChibiMighty.bin", Scope_Stage);
                *(BYTE*)GetAddress(baseAddress + 0xAC6758, 0x76) = ChibiMighty;
            }
            if (GetAddress(baseAddress + 0xAC6758, 0x78))
            {
                int ChibiRay = LoadAnimation("Players/ChibiRay.bin", Scope_Stage);
                *(BYTE*)GetAddress(baseAddress + 0xAC6758, 0x78) = ChibiRay;
            }
            RefreshChibiSprites = false;
        }
    }

    void OnObject(int Index)
    {
        SizeLazer& Lazer = *SonicMania::GetEntityFromSceneSlot<SizeLazer>(Index);
        LoadChibiSprites();
    }
}