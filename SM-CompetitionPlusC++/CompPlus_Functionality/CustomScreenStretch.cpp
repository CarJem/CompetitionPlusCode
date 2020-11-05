#include "CustomScreenStretch.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "include/SonicMania.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Status.h"

namespace CompPlus_CustomScreenStretch
{
    //DataPointer(int, WindowSizeX, 0xA530E4);
    //DataPointer(int, WindowSizeY, 0xA530E8);
    DataPointer(int, WindowSizeX, 0x43C6F4);
    DataPointer(int, WindowSizeY, 0x43C6F8);
    DataPointer(int, ViewPortSizeX, 0x43C70C);
    DataPointer(int, ViewPortSizeY, 0x43C710);
    DataPointer(int, ImageXPosition, 0x43C704);
    DataPointer(int, ImageYPosition, 0x43C708);
    DataPointer(BYTE, ScreenCount, 0xA530FC);

    bool ScreenSizeSaved = false;

    int OriginalImageXPosition = 0;
    int OriginalImageYPosition = 0;

    int ModifiedViewPortX = 1200;
    int ModifiedViewPortY = 960;
    int ModifiedImageXPosition = 300;
    int ModifiedImageYPosition = 0;

    void OnFrame()
    {
        if (SonicMania::Options->CompetitionSession.inMatch == 1)
        {
            if (ScreenCount != 1 && SonicMania::Options->CompetitionSession.ReadOnlyDisplayMode == 0 && SonicMania::Options->CompetitionSession.NumberOfPlayers == 2 && CompPlus_Settings::StrechEffectIntensity > 1)
            {
                int Intensity = CompPlus_Settings::StrechEffectIntensity + 1;
                if (WindowSizeX != 0 && WindowSizeY != 0 && Intensity != 0)
                {
                    ViewPortSizeX = WindowSizeX / 2 + (WindowSizeX / Intensity);
                    ViewPortSizeY = WindowSizeY;
                    int CenterX = (WindowSizeX - ViewPortSizeX);
                    ImageXPosition = (CenterX == 0 ? 0 : CenterX / 2);
                    ImageYPosition = 0;
                }
            }
            else
            {
                ViewPortSizeX = WindowSizeX;
                ViewPortSizeY = WindowSizeY;
                ImageXPosition = OriginalImageXPosition;
                ImageYPosition = OriginalImageYPosition;
            }
        }

    }
}