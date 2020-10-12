// ManiaTitleCardColours.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "TitleCardColors.h"
#include "CompPlus_Core/CompPlus_Status.h"
#include <ManiaModLoader.h>

namespace TileCardColors
{

    void WriteColour(BYTE*& address, BYTE red, BYTE green, BYTE blue)
    {
        // Writes all three colours into the buffer in BGR order
        *(int*)address = red << 16 | green << 8 | blue;
        // Offsets the Address for the next set
        address += 4;
    }

    void SetupTitleCardColours()
    {
        // TitleCard Pointer
        auto addr = *(BYTE**)(baseAddress + 0x00AA7634);
        // Is in Encore Mode
        bool encore = *(addr + 0x37) == 5;
        // Address to the Background Colour within the Buffer 
        addr = (BYTE*)((*(int*)addr) + 0x0374);

        // Background Colour
        // NOTE: 0x00RRGGBB
            
        if (CompPlus_Status::UseEXETitleCard)
        {
            *(int*)addr = 0x00280000; // Write EXE Background Colour
        }
        else if (encore) 
        {
            *(int*)addr = 0x006BAE99; // Write Encore Mode Background Colour
        }
        else 
        {
            *(int*)addr = 0x00F0C800; // Write Mania Mode Background Colour
        }
        // Jump back
        addr -= 0x10;

        if (CompPlus_Status::UseEXETitleCard)
        {
            // Write EXE Colours
            WriteColour(addr, 32, 32, 32); //Orange
            WriteColour(addr, 192, 0, 0); //Cyan
            WriteColour(addr, 255, 0, 0); //Red
            WriteColour(addr, 128, 0, 0); //Blue
            addr += 4;
            WriteColour(addr, 128, 0, 0); //White
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
        }
    }

    void Init()
    {
        // Writes our hook into the function that handles what colours to use 
        WriteJump((void*)(baseAddress + 0x00015100), SetupTitleCardColours);
    }

}
