#pragma once
#include "include/stdafx.h"
#include "include/MemAccess.h"
#include "include/SonicMania.h"
namespace CompPlus_Patches
{
    struct WaterColorDefintion 
    {
        SonicMania::InkEffect InkEffect;
        int Alpha;
        SonicMania::Color Color;

        WaterColorDefintion() 
        {

        }

        WaterColorDefintion(SonicMania::Color color, int alpha, SonicMania::InkEffect effect) : WaterColorDefintion()
        {
            InkEffect = effect;
            Alpha = alpha;
            Color = color;
        }
    };


    extern void LoadSounds();
    extern void FixSummary();
    extern void DisableVSPointAddingAddress();
    extern void FixRayAndMighty2P();
    extern void DynamicPatchesOnFrame();
    extern void InitPatches();
}