#include "stdafx.h"
#include "include/MemAccess.h"
#include "MetrotropicBeach.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/PointScrolling.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "include/ManiaAPI/SonicMania.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include <vector>
#include "CompPlus_Core/CompPlus_Scoring.h"
#include "CompPlus_Scenes/HUB World/HubCore.h"
#include "CompPlus_Extensions/Drawing.h"

namespace CompPlus_MetrotropicBeach
{
    bool PaletteSaved = false;

    std::string DayPaletteACT_FilePath;
    std::string NightPaletteACT_FilePath;
    std::string SunsetPaletteACT_FilePath;

    SHORT PaletteStorageDay[256];
    int PaletteStorageDay_Length;

    SHORT PaletteStorageSunset[256];
    int PaletteStorageSunset_Length;

    SHORT PaletteStorageNight[256];
    int PaletteStorageNight_Length;

    SHORT PaletteStorageMem[256];
    int PaletteStorageMem_Length;

    bool LastAct1_TimeChange = false;
    bool LastAct2_TimeChange = false;
    bool Act1_TimeChange = false;
    bool Act2_TimeChange = false;

    bool FadeChangeDone = false;
    bool NeedsFadeChange = false;
    int FadeTime = 0;
    int FadeTime2 = 0;
    int FadeSpeed = 1;

    void ApplyStagePalette(SHORT PaletteStorage[256], int PaletteStorage_Length)
    {
        for (int i = 127; i < PaletteStorage_Length; i++)
        {
            SonicMania::Palette4[i] = PaletteStorage[i];
        }

        if (NeedsFadeChange)
        {
            FadeTime2 = 0;
            FadeTime = 100;
            NeedsFadeChange = false;
        }

        if (!NeedsFadeChange && FadeTime <= 0)
        {
            for (int i = 127; i < PaletteStorage_Length; i++)
            {
                SonicMania::Palette0[i] = PaletteStorage[i];
                SonicMania::Palette1[i] = PaletteStorage[i];
                SonicMania::Palette2[i] = PaletteStorage[i];
                SonicMania::Palette3[i] = PaletteStorage[i];
                PaletteStorageMem[i] = PaletteStorage[i];
            }
        }
        else 
        {
            float Progress = (100 - FadeTime) * 0.01;
            for (int i = 127; i < PaletteStorage_Length; i++)
            {

                auto source = SonicMania::Color();
                source.FromRGB565(PaletteStorageMem[i]);

                auto target = SonicMania::Color();
                target.FromRGB565(PaletteStorage[i]);

                auto result = Drawing::InterpolateColors(source, target, Progress);

                SonicMania::Palette0[i] = result.ToRGB565();
                SonicMania::Palette1[i] = result.ToRGB565();
                SonicMania::Palette2[i] = result.ToRGB565();
                SonicMania::Palette3[i] = result.ToRGB565();
                SonicMania::Palette4[i] = result.ToRGB565();
            }
            if (FadeTime2 >= FadeSpeed) 
            {
                FadeTime -= 1;
                FadeTime2 = 0;
            }
            else 
            {
                FadeTime2 += 1;
            }

        }
    }

    void EnforcePalette(int ActID)
    {
        if (!PaletteSaved)
        {
            StorePalette(DayPaletteACT_FilePath, PaletteStorageDay, PaletteStorageDay_Length);
            StorePalette(SunsetPaletteACT_FilePath, PaletteStorageSunset, PaletteStorageSunset_Length);
            StorePalette(NightPaletteACT_FilePath, PaletteStorageNight, PaletteStorageNight_Length);
            PaletteSaved = true;
        }
        else
        {
            if (ActID == 1) 
            {
                if (Act1_TimeChange) ApplyStagePalette(PaletteStorageSunset, PaletteStorageSunset_Length);
                else ApplyStagePalette(PaletteStorageDay, PaletteStorageDay_Length);
            }
            else if (ActID == 2) 
            {
                if (Act2_TimeChange) ApplyStagePalette(PaletteStorageNight, PaletteStorageNight_Length);
                else ApplyStagePalette(PaletteStorageSunset, PaletteStorageSunset_Length);
            }
        }
    }

    void Restart() 
    {
        LastAct1_TimeChange = false;
        LastAct2_TimeChange = false;
        Act1_TimeChange = false;
        Act2_TimeChange = false;
        NeedsFadeChange = false;
        FadeTime = 0;
        FadeTime2 = 0;
    }

    void CheckPositions(int ActID) 
    {
        int x_position = 0x1989;

        if (ActID == 1) 
        {
            bool P1 = Player1.Position.X >= x_position;
            bool P2 = Player2.Position.X >= x_position;
            bool P3 = Player3.Position.X >= x_position;
            bool P4 = Player4.Position.X >= x_position;
            if (P1 || P2 || P3 || P4) 
            {
                Act1_TimeChange = true;
            }

            if (LastAct1_TimeChange != Act1_TimeChange)
            {
                NeedsFadeChange = true;
                LastAct1_TimeChange = Act1_TimeChange;
            }
        }
        else if (ActID == 2)
        {
            bool P1 = Player1.Position.X >= x_position;
            bool P2 = Player2.Position.X >= x_position;
            bool P3 = Player3.Position.X >= x_position;
            bool P4 = Player4.Position.X >= x_position;
            if (P1 || P2 || P3 || P4) 
            {
                Act2_TimeChange = true;
            }

            if (LastAct2_TimeChange != Act2_TimeChange) 
            {
                NeedsFadeChange = true;
                LastAct2_TimeChange = Act2_TimeChange;
            }
        }
    }

    void RunningStart(int ActID) 
    {
        if (ActID == 2) 
        {
            if (!SonicMania::Timer.Enabled) 
            {
                Player1.Right = true;
                Player2.Right = true;
                Player3.Right = true;
                Player4.Right = true;
            }
        }
    }

    void OnFrame(int ActID)
    {
        RunningStart(ActID);
        CheckPositions(ActID);
        EnforcePalette(ActID);
    }

    void Init(std::string modPath)
    {
        DayPaletteACT_FilePath = modPath + CompPlus_Common::Act_MBZ_Day;
        SunsetPaletteACT_FilePath = modPath + CompPlus_Common::Act_MBZ_Sunset;
        NightPaletteACT_FilePath = modPath + CompPlus_Common::Act_MBZ_Night;
    }
}