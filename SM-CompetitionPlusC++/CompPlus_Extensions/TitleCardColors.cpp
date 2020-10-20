// ManiaTitleCardColours.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "TitleCardColors.h"
#include "CompPlus_Core/CompPlus_Status.h"
#include <ManiaModLoader.h>
#include "include/SonicMania.h"

namespace TileCardColors
{

    void WriteColour(BYTE*& address, BYTE red, BYTE green, BYTE blue)
    {
        // Writes all three colours into the buffer in BGR order
        *(int*)address = red << 16 | green << 8 | blue;
        // Offsets the Address for the next set
        address += 4;
    }

    void WriteWhiteColours(BYTE Red, BYTE Green, BYTE Blue)
    {
        int* ZoneQuad_1 = (int*)(baseAddress + 0x16A75);
        int* ZoneQuad_2 = (int*)(baseAddress + 0x1654F);
        int* ZoneQuad_3 = (int*)(baseAddress + 0x16323);

        BYTE blank = 0;
        BYTE Alpha = 255;

        WriteData((void*)(ZoneQuad_1), 
            { 
                (byte)0x68, (byte)Alpha, (byte)blank, (byte)blank, (byte)blank, 
                (byte)0x68, (byte)Blue, (byte)blank, (byte)blank, (byte)blank,
                (byte)0x68, (byte)Green, (byte)blank, (byte)blank, (byte)blank,
                (byte)0x68, (byte)Red, (byte)blank, (byte)blank, (byte)blank
            }
        );

        WriteData((void*)(ZoneQuad_2),
            {
                (byte)0x68, (byte)Alpha, (byte)blank, (byte)blank, (byte)blank,
                (byte)0x68, (byte)Blue, (byte)blank, (byte)blank, (byte)blank,
                (byte)0x68, (byte)Green, (byte)blank, (byte)blank, (byte)blank,
                (byte)0x68, (byte)Red, (byte)blank, (byte)blank, (byte)blank
            }
        );

        WriteData((void*)(ZoneQuad_3),
            {
                (byte)0x68, (byte)Alpha, (byte)blank, (byte)blank, (byte)blank,
                (byte)0x68, (byte)Blue, (byte)blank, (byte)blank, (byte)blank,
                (byte)0x68, (byte)Green, (byte)blank, (byte)blank, (byte)blank,
                (byte)0x68, (byte)Red, (byte)blank, (byte)blank, (byte)blank
            }
        );

    }



    void SetupTitleCardColours()
    {
        // TitleCard Pointer
        auto addr = *(BYTE**)(baseAddress + 0x00AA7634);
        // Is in Encore Mode
        bool encore = *(addr + 0x37) == 5;
        // Address to the Background Colour within the Buffer 
        addr = (BYTE*)((*(int*)addr) + 0x0374);

        // NOTE: 0x00RRGGBB
        if (CompPlus_Status::IsChaotixStageEncore) *(int*)addr = 0x00999999;
        else if (CompPlus_Status::IsChaotixStage) *(int*)addr = 0x00000100;
        else if (CompPlus_Status::UseEXETitleCard) *(int*)addr = 0x00280000; // Write EXE Background Colour
        else if (encore) *(int*)addr = 0x006BAE99; // Write Encore Mode Background Colour
        else *(int*)addr = 0x00F0C800; // Write Mania Mode Background Colour

        // Jump back
        addr -= 0x10;


        if (CompPlus_Status::UseEXETitleCard)
        {
            // Write EXE Colours
            WriteColour(addr, 32, 32, 32); //Orange
            WriteColour(addr, 192, 0, 0);  //Cyan
            WriteColour(addr, 255, 0, 0);  //Red
            WriteColour(addr, 128, 0, 0);  //Blue
            addr += 4;
            WriteColour(addr, 128, 0, 0);  //White
            WriteWhiteColours(128, 0, 0);
        }
        else if (CompPlus_Status::IsChaotixStageEncore)
        {
            // Write Encore Mode Colours (CHAOTIX)
            WriteColour(addr, 123, 83, 164); // NOTE: ADDR, R, G, B
            WriteColour(addr, 207, 206, 0);
            WriteColour(addr, 40, 122, 218);
            WriteColour(addr, 251, 56, 50);
            addr += 4;
            WriteColour(addr, 0, 0, 0);
            WriteWhiteColours(240, 240, 240);

        }
        else if (CompPlus_Status::IsChaotixStage)
        {
            // Write Mania Mode Colours (CHAOTIX)
            WriteColour(addr, 207, 206, 0); // NOTE: ADDR, R, G, B
            WriteColour(addr, 123, 83, 164);
            WriteColour(addr, 251, 56, 50);
            WriteColour(addr, 40, 122, 218);
            addr += 4;
            WriteColour(addr, 0, 0, 0);
            WriteWhiteColours(240, 240, 240);
        }
        else if (encore)
        {
            // Write Encore Mode Colours
            WriteColour(addr, 55, 81, 162); // NOTE: ADDR, R, G, B
            WriteColour(addr, 199, 82, 91);
            WriteColour(addr, 66, 143, 195);
            WriteColour(addr, 223, 177, 63);
            addr += 4;
            WriteColour(addr, 0, 0, 0);
            WriteWhiteColours(240, 240, 240);
        }
        else
        {
            // Write Mania Mode Colours
            WriteColour(addr, 240, 140, 24); // NOTE: ADDR, R, G, B
            WriteColour(addr, 96, 192, 160);
            WriteColour(addr, 240, 80, 48);
            WriteColour(addr, 64, 96, 176);
            addr += 4;
            WriteColour(addr, 0, 0, 0);
            WriteWhiteColours(240, 240, 240);
        }
    }

    void Init()
    {
        // Writes our hook into the function that handles what colours to use 
        WriteJump((void*)(baseAddress + 0x00015100), SetupTitleCardColours);
    }

}
