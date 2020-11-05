#include "SpecialRings.h"
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

namespace CompPlus_SpecialRings 
{
    bool RingSpritesLoaded = false;
    int RingSpriteID = 0;

    int HyperRingIndex = 0;
    int RotatePosition = 0;
    int RotateSpeed = 1;

    char GetHyperRingColor(int index)
    {
        char data[4];

        int colorOffset = 20;

        if (HyperRingIndex == 0)
        {
            //A0C0E0
            data[0] = 0xE0 - colorOffset;
            data[1] = 0xC0 - colorOffset;
            data[2] = 0xA0 - colorOffset;
            data[3] = 0x00;
        }
        else if (HyperRingIndex == 2)
        {
            //80E080
            data[0] = 0x80 - colorOffset;
            data[1] = 0xE0 - colorOffset;
            data[2] = 0x80 - colorOffset;
            data[3] = 0x00;
        }
        else if (HyperRingIndex == 4)
        {
            //E0C060
            data[0] = 0x60 - colorOffset;
            data[1] = 0xC0 - colorOffset;
            data[2] = 0xE0 - colorOffset;
            data[3] = 0x00;
        }
        else if (HyperRingIndex == 6)
        {
            //E0C0E0
            data[0] = 0xE0 - colorOffset;
            data[1] = 0xC0 - colorOffset;
            data[2] = 0xE0 - colorOffset;
            data[3] = 0x00;
        }
        else if (HyperRingIndex == 8)
        {
            //C0E060
            data[0] = 0x60 - colorOffset;
            data[1] = 0xE0 - colorOffset;
            data[2] = 0xC0 - colorOffset;
            data[3] = 0x00;
        }
        else
        {
            //E0E060
            data[0] = 0x60 - colorOffset;
            data[1] = 0xE0 - colorOffset;
            data[2] = 0xE0 - colorOffset;
            data[3] = 0x00;
        }

        if (index == 0) return data[0];
        else if (index == 1) return data[1];
        else if (index == 2) return data[2];
        else if (index == 3) return data[3];
        else return data[0];
    }

    void HyperSpecialRingColors()
    {
        //00F0F000
        char data[5];
        data[0] = 0x68;
        data[1] = GetHyperRingColor(0);
        data[2] = GetHyperRingColor(1);
        data[3] = GetHyperRingColor(2);
        data[4] = GetHyperRingColor(3);
        void* address = (void*)(baseAddress + 0x22016);
        WriteData(address, data);
        if (RotatePosition >= RotateSpeed)
        {
            RotatePosition = 0;
            if (HyperRingIndex >= 9) HyperRingIndex = 0;
            else HyperRingIndex += 2;
        }
        else RotatePosition++;

    }

    void NormalSpecialRingColors()
    {
        //00F0F000
        char data[5];
        data[0] = 0x68;
        data[1] = 0x00;
        data[2] = 0xF0;
        data[3] = 0xF0;
        data[4] = 0x00;
        void* address = (void*)(baseAddress + 0x22016);
        WriteData(address, data);
    }

    void EXESpecialRingColors()
    {
        char data[5];
        data[0] = 0x68;
        data[1] = 0x5A;
        data[2] = 0x59;
        data[3] = 0x39;
        data[4] = 0x00;
        void* address = (void*)(baseAddress + 0x22016);
        WriteData(address, data);
    }

    void EXESpecialRingColorsDeluxe()
    {
        char data[5];
        data[0] = 0x68;
        data[1] = 0x00;
        data[2] = 0x00;
        data[3] = 0xFF;
        data[4] = 0x00;
        void* address = (void*)(baseAddress + 0x22016);
        WriteData(address, data);
    }

    void UpdateSpecialRingVisuals() 
    {
        if (CompPlus_Status::InHolloweenHUB) EXESpecialRingColors();
        else if (!CompPlus_Status::InHolloweenHUB && CompPlus_Settings::CurrentSeason == CompPlus_Settings::Season_EXE) EXESpecialRingColorsDeluxe();
        else NormalSpecialRingColors();
    }

    void ReplaceSpecialRings() 
    {
        if (CompPlus_Status::ReplaceSpecialRings)
        {
            if (!RingSpritesLoaded)
            {
                RingSpriteID = SonicMania::LoadAnimation(CompPlus_Common::Anim_Ring_Normal, SonicMania::Scope_Stage);
                RingSpritesLoaded = true;
            }

            for (int i = 0; i < 2301; ++i)
            {
                SonicMania::Entity& entity = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(i);
                if (entity.ObjectID == SonicMania::GetObjectIDFromType(SonicMania::ObjectType_SSRing))
                {
                    SpecialRing& specialRing = *SonicMania::GetEntityFromSceneSlot<SpecialRing>(i);
                    if (specialRing.Visible)
                    {
                        specialRing.Enabled = false;
                        specialRing.Visible = false;

                        SonicMania::EntityRing& Temp = *(SonicMania::EntityRing*)SonicMania::SpawnObject(SonicMania::GetObjectIDFromType(SonicMania::ObjectType_Ring), 0, entity.Position);
                        Temp.ScaleX = 2;
                        Temp.ScaleY = 2;
                        Temp.Type = 1;
                        Temp.RingAmount = 5;
                        Temp.PlaneFilter = specialRing.PlaneFilter;
                        Temp.Priority = specialRing.Priority;
                        Temp.field_57 = 1;
                        SonicMania::SetSpriteAnimation(RingSpriteID, 1, &Temp.Animation, true, 0);
                    }
                }
            }
        }
    }

    void InitHUBSpecialRings() 
    {
        if (CompPlus_Status::EnableHUBSpecialRingFunctionality)
        {
            for (int i = 0; i < 2301; ++i)
            {
                SonicMania::Entity& entity = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(i);
                if (entity.ObjectID == SonicMania::GetObjectIDFromType(SonicMania::ObjectType_SSRing))
                {
                    SpecialRing& specialRing = *SonicMania::GetEntityFromSceneSlot<SpecialRing>(i);
                    specialRing.Enabled = true;
                }
            }
        }
    }

    void UpdateSpecialRings()
    {
        if (CompPlus_Status::SpecialRingsNeedRefresh)
        {
            RingSpritesLoaded = false;
            ReplaceSpecialRings();
            InitHUBSpecialRings();
            UpdateSpecialRingVisuals();
            CompPlus_Status::SpecialRingsNeedRefresh = false;
        }
    }

    void UnloadDrawables() 
    {
        RingSpritesLoaded = false;
    }
}