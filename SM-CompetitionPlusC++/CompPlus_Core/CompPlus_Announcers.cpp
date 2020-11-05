#include "stdafx.h"
#include "include/SonicMania.h"
#include "CompPlus_Settings.h"
#include "include/ManiaModLoader.h"
#include "CompPlus_Extensions/Helpers.h"

namespace CompPlus_Announcers
{

    using namespace SonicMania;

     bool AllowReload = true;
     bool ReloadRequired = false;
     bool ShowLogging = false;

    #pragma region VO Memory Addresses

        int* Player1_MemoryAdd = (int*)(baseAddress + 0x1310D);
        int* Player2_MemoryAdd = (int*)(baseAddress + 0x13122);
        int* Player3_MemoryAdd = (int*)(baseAddress + 0x13137);
        int* Player4_MemoryAdd = (int*)(baseAddress + 0x1314C);

        int* Three_MemoryAdd = (int*)(baseAddress + 0x1324A);
        int* Two_MemoryAdd = (int*)(baseAddress + 0x1325F);
        int* One_MemoryAdd = (int*)(baseAddress + 0x13274);
        int* Go_MemoryAdd = (int*)(baseAddress + 0x13289);

        int* Goal_MemoryAdd = (int*)(baseAddress + 0x1329E);			//SonicMania.exe+1329D  { ("VO/Goal.wav") }
        int* Goal_MemoryAdd_2 = (int*)(baseAddress + 0x132FD);			//SonicMania.exe+132FC  { ("VO/Goal.wav") }


        int* Sonic_MemoryAdd = (int*)(baseAddress + 0x13093);			//SonicMania.exe+13092  { ("VO/Sonic.wav") }
        int* Tails_MemoryAdd = (int*)(baseAddress + 0x130A4);			//SonicMania.exe+130A3  { ("VO/Tails.wav") }
        int* Knuckles_MemoryAdd = (int*)(baseAddress + 0x130B9);		//SonicMania.exe+130B8  { ("VO/Knuckles.wav") }
        int* Mighty_MemoryAdd = (int*)(baseAddress + 0x130CE);			//SonicMania.exe+130CD  { ("VO/Mighty.wav") }
        int* Ray_MemoryAdd = (int*)(baseAddress + 0x130E3);				//SonicMania.exe+130E2  { ("VO/Ray.wav") }

        int* SonicWins_MemoryAdd = (int*)(baseAddress + 0x13161);			//SonicMania.exe+13160  { ("VO/SonicWins.wav") }
        int* TailsWins_MemoryAdd = (int*)(baseAddress + 0x13176);			//SonicMania.exe+13175  { ("VO/TailsWins.wav") }
        int* KnuxWins_MemoryAdd = (int*)(baseAddress + 0x1318B);			//SonicMania.exe+1318A  { ("VO/KnuxWins.wav") }
        int* MightyWins_MemoryAdd = (int*)(baseAddress + 0x131A0);			//SonicMania.exe+1319F  { ("VO/MightyWins.wav") }
        int* RayWins_MemoryAdd = (int*)(baseAddress + 0x131B5);				//SonicMania.exe+131B4  { ("VO/RayWins.wav") }

        int* TheWinnerIs_MemoryAdd = (int*)(baseAddress + 0x130F8);		//SonicMania.exe+130F7  { ("VO/TheWinnerIs.wav") }

        int* ItsADraw_MemoryAdd = (int*)(baseAddress + 0x131CA);			//SonicMania.exe+131C9  { ("VO/ItsADraw.wav") }
        int* ItsADraw_Set_MemoryAdd = (int*)(baseAddress + 0x131E2);		//SonicMania.exe+131E1  { ("VO/ItsADraw_Set.wav") }

        int* NewRecordMid_MemoryAdd = (int*)(baseAddress + 0x132D1);		//SonicMania.exe+132D0  { ("VO/NewRecordMid.wav") }
        int* NewRecordTop_MemoryAdd = (int*)(baseAddress + 0x132C0);		//SonicMania.exe+132BF  { ("VO/NewRecordTop.wav") }

    #pragma endregion

    #pragma region Stock VO Paths

        const char* Player1_Stock = "VO/Player1.wav";
        const char* Player2_Stock = "VO/Player2.wav";
        const char* Player3_Stock = "VO/Player3.wav";
        const char* Player4_Stock = "VO/Player4.wav";

        const char* Three_Stock = "VO/Three.wav";
        const char* Two_Stock = "VO/Two.wav";
        const char* One_Stock = "VO/One.wav";
        const char* Go_Stock = "VO/Go.wav";
        const char* Goal_Stock = "VO/Goal.wav";

        const char* Sonic_Stock = "VO/Sonic.wav";
        const char* SonicWins_Stock = "VO/SonicWins.wav";
        const char* Tails_Stock = "VO/Tails.wav";
        const char* TailsWins_Stock = "VO/TailsWins.wav";
        const char* Knuckles_Stock = "VO/Knuckles.wav";
        const char* KnuxWins_Stock = "VO/KnuxWins.wav";
        const char* Mighty_Stock = "VO/Mighty.wav";
        const char* MightyWins_Stock = "VO/MightyWins.wav";
        const char* Ray_Stock = "VO/Ray.wav";
        const char* RayWins_Stock = "VO/RayWins.wav";

        const char* TheWinnerIs_Stock = "VO/TheWinnerIs.wav";

        const char* ItsADraw_Stock = "VO/ItsADraw.wav";
        const char* ItsADraw_Set_Stock = "VO/ItsADraw_Set.wav";

        const char* NewRecordMid_Stock = "VO/NewRecordMid.wav";
        const char* NewRecordTop_Stock = "VO/NewRecordTop.wav";

    #pragma endregion

    #pragma region ATG VO Paths

        const char* Player1_ATG = "VO1/Player1.wav";
        const char* Player2_ATG = "VO1/Player2.wav";
        const char* Player3_ATG = "VO1/Player3.wav";
        const char* Player4_ATG = "VO1/Player4.wav";

        const char* Three_ATG = "VO1/Three.wav";
        const char* Two_ATG = "VO1/Two.wav";
        const char* One_ATG = "VO1/One.wav";
        const char* Go_ATG = "VO1/Go.wav";
        const char* Goal_ATG = "VO1/Goal.wav";

        const char* Sonic_ATG = "VO1/Sonic.wav";
        const char* SonicWins_ATG = "VO1/SonicWins.wav";
        const char* Tails_ATG = "VO1/Tails.wav";
        const char* TailsWins_ATG = "VO1/TailsWins.wav";
        const char* Knuckles_ATG = "VO1/Knuckles.wav";
        const char* KnuxWins_ATG = "VO1/KnuxWins.wav";
        const char* Mighty_ATG = "VO1/Mighty.wav";
        const char* MightyWins_ATG = "VO1/MightyWins.wav";
        const char* Ray_ATG = "VO1/Ray.wav";
        const char* RayWins_ATG = "VO1/RayWins.wav";

        const char* TheWinnerIs_ATG = "VO1/TheWinnerIs.wav";

        const char* ItsADraw_ATG = "VO1/ItsADraw.wav";
        const char* ItsADraw_Set_ATG = "VO1/ItsADraw_Set.wav";

        const char* NewRecordMid_ATG = "VO1/NewRecordMid.wav";
        const char* NewRecordTop_ATG = "VO1/NewRecordTop.wav";

    #pragma endregion

    #pragma region Garrulous64 VO Paths

        const char* Player1_Garrulous64 = "VO2/Player1.wav";
        const char* Player2_Garrulous64 = "VO2/Player2.wav";
        const char* Player3_Garrulous64 = "VO2/Player3.wav";
        const char* Player4_Garrulous64 = "VO2/Player4.wav";

        const char* Three_Garrulous64 = "VO2/Three.wav";
        const char* Two_Garrulous64 = "VO2/Two.wav";
        const char* One_Garrulous64 = "VO2/One.wav";
        const char* Go_Garrulous64 = "VO2/Go.wav";
        const char* Goal_Garrulous64 = "VO2/Goal.wav";

        const char* Sonic_Garrulous64 = "VO2/Sonic.wav";
        const char* SonicWins_Garrulous64 = "VO2/SonicWins.wav";
        const char* Tails_Garrulous64 = "VO2/Tails.wav";
        const char* TailsWins_Garrulous64 = "VO2/TailsWins.wav";
        const char* Knuckles_Garrulous64 = "VO2/Knuckles.wav";
        const char* KnuxWins_Garrulous64 = "VO2/KnuxWins.wav";
        const char* Mighty_Garrulous64 = "VO2/Mighty.wav";
        const char* MightyWins_Garrulous64 = "VO2/MightyWins.wav";
        const char* Ray_Garrulous64 = "VO2/Ray.wav";
        const char* RayWins_Garrulous64 = "VO2/RayWins.wav";

        const char* TheWinnerIs_Garrulous64 = "VO2/TheWinnerIs.wav";

        const char* ItsADraw_Garrulous64 = "VO2/ItsADraw.wav";
        const char* ItsADraw_Set_Garrulous64 = "VO2/ItsADraw_Set.wav";

        const char* NewRecordMid_Garrulous64 = "VO2/NewRecordMid.wav";
        const char* NewRecordTop_Garrulous64 = "VO2/NewRecordTop.wav";

    #pragma endregion

    #pragma region DanielUK VO Paths

        const char* Player1_DanielUK = "VO3/Player1.wav";
        const char* Player2_DanielUK = "VO3/Player2.wav";
        const char* Player3_DanielUK = "VO3/Player3.wav";
        const char* Player4_DanielUK = "VO3/Player4.wav";

        const char* Three_DanielUK = "VO3/Three.wav";
        const char* Two_DanielUK = "VO3/Two.wav";
        const char* One_DanielUK = "VO3/One.wav";
        const char* Go_DanielUK = "VO3/Go.wav";
        const char* Goal_DanielUK = "VO3/Goal.wav";

        const char* Sonic_DanielUK = "VO3/Sonic.wav";
        const char* SonicWins_DanielUK = "VO3/SonicWins.wav";
        const char* Tails_DanielUK = "VO3/Tails.wav";
        const char* TailsWins_DanielUK = "VO3/TailsWins.wav";
        const char* Knuckles_DanielUK = "VO3/Knuckles.wav";
        const char* KnuxWins_DanielUK = "VO3/KnuxWins.wav";
        const char* Mighty_DanielUK = "VO3/Mighty.wav";
        const char* MightyWins_DanielUK = "VO3/MightyWins.wav";
        const char* Ray_DanielUK = "VO3/Ray.wav";
        const char* RayWins_DanielUK = "VO3/RayWins.wav";

        const char* TheWinnerIs_DanielUK = "VO3/TheWinnerIs.wav";

        const char* ItsADraw_DanielUK = "VO3/ItsADraw.wav";
        const char* ItsADraw_Set_DanielUK = "VO3/ItsADraw_Set.wav";

        const char* NewRecordMid_DanielUK = "VO3/NewRecordMid.wav";
        const char* NewRecordTop_DanielUK = "VO3/NewRecordTop.wav";

    #pragma endregion

    #pragma region Memes VO Paths

        const char* Player1_Memes = "VO4/Player1.wav";
        const char* Player2_Memes = "VO4/Player2.wav";
        const char* Player3_Memes = "VO4/Player3.wav";
        const char* Player4_Memes = "VO4/Player4.wav";

        const char* Three_Memes = "VO4/Three.wav";
        const char* Two_Memes = "VO4/Two.wav";
        const char* One_Memes = "VO4/One.wav";
        const char* Go_Memes = "VO4/Go.wav";
        const char* Goal_Memes = "VO4/Goal.wav";

        const char* Sonic_Memes = "VO4/Sonic.wav";
        const char* SonicWins_Memes = "VO4/SonicWins.wav";
        const char* Tails_Memes = "VO4/Tails.wav";
        const char* TailsWins_Memes = "VO4/TailsWins.wav";
        const char* Knuckles_Memes = "VO4/Knuckles.wav";
        const char* KnuxWins_Memes = "VO4/KnuxWins.wav";
        const char* Mighty_Memes = "VO4/Mighty.wav";
        const char* MightyWins_Memes = "VO4/MightyWins.wav";
        const char* Ray_Memes = "VO4/Ray.wav";
        const char* RayWins_Memes = "VO4/RayWins.wav";

        const char* TheWinnerIs_Memes = "VO4/TheWinnerIs.wav";

        const char* ItsADraw_Memes = "VO4/ItsADraw.wav";
        const char* ItsADraw_Set_Memes = "VO4/ItsADraw_Set.wav";

        const char* NewRecordMid_Memes = "VO4/NewRecordMid.wav";
        const char* NewRecordTop_Memes = "VO4/NewRecordTop.wav";

    #pragma endregion

    #pragma region Classic VO Paths

        const char* Player1_Classic = "VO5/Player1.wav";
        const char* Player2_Classic = "VO5/Player2.wav";
        const char* Player3_Classic = "VO5/Player3.wav";
        const char* Player4_Classic = "VO5/Player4.wav";

        const char* Three_Classic = "VO5/Three.wav";
        const char* Two_Classic = "VO5/Two.wav";
        const char* One_Classic = "VO5/One.wav";
        const char* Go_Classic = "VO5/Go.wav";
        const char* Goal_Classic = "VO5/Goal.wav";

        const char* Sonic_Classic = "VO5/Sonic.wav";
        const char* SonicWins_Classic = "VO5/SonicWins.wav";
        const char* Tails_Classic = "VO5/Tails.wav";
        const char* TailsWins_Classic = "VO5/TailsWins.wav";
        const char* Knuckles_Classic = "VO5/Knuckles.wav";
        const char* KnuxWins_Classic = "VO5/KnuxWins.wav";
        const char* Mighty_Classic = "VO5/Mighty.wav";
        const char* MightyWins_Classic = "VO5/MightyWins.wav";
        const char* Ray_Classic = "VO5/Ray.wav";
        const char* RayWins_Classic = "VO5/RayWins.wav";

        const char* TheWinnerIs_Classic = "VO5/TheWinnerIs.wav";

        const char* ItsADraw_Classic = "VO5/ItsADraw.wav";
        const char* ItsADraw_Set_Classic = "VO5/ItsADraw_Set.wav";

        const char* NewRecordMid_Classic = "VO5/NewRecordMid.wav";
        const char* NewRecordTop_Classic = "VO5/NewRecordTop.wav";

    #pragma endregion

    #pragma region Blank VO Paths

        const char* Player1_Blank = "VO6/Player1.wav";
        const char* Player2_Blank = "VO6/Player2.wav";
        const char* Player3_Blank = "VO6/Player3.wav";
        const char* Player4_Blank = "VO6/Player4.wav";

        const char* Three_Blank = "VO6/Three.wav";
        const char* Two_Blank = "VO6/Two.wav";
        const char* One_Blank = "VO6/One.wav";
        const char* Go_Blank = "VO6/Go.wav";
        const char* Goal_Blank = "VO6/Goal.wav";

        const char* Sonic_Blank = "VO6/Sonic.wav";
        const char* SonicWins_Blank = "VO6/SonicWins.wav";
        const char* Tails_Blank = "VO6/Tails.wav";
        const char* TailsWins_Blank = "VO6/TailsWins.wav";
        const char* Knuckles_Blank = "VO6/Knuckles.wav";
        const char* KnuxWins_Blank = "VO6/KnuxWins.wav";
        const char* Mighty_Blank = "VO6/Mighty.wav";
        const char* MightyWins_Blank = "VO6/MightyWins.wav";
        const char* Ray_Blank = "VO6/Ray.wav";
        const char* RayWins_Blank = "VO6/RayWins.wav";

        const char* TheWinnerIs_Blank = "VO6/TheWinnerIs.wav";

        const char* ItsADraw_Blank = "VO6/ItsADraw.wav";
        const char* ItsADraw_Set_Blank = "VO6/ItsADraw_Set.wav";

        const char* NewRecordMid_Blank = "VO6/NewRecordMid.wav";
        const char* NewRecordTop_Blank = "VO6/NewRecordTop.wav";

    #pragma endregion

    #pragma region Stock VO Paths

        const char* Player1_KC3K = "VO_KC3K/Player1.wav";
        const char* Player2_KC3K = "VO_KC3K/Player2.wav";
        const char* Player3_KC3K = "VO_KC3K/Player3.wav";
        const char* Player4_KC3K = "VO_KC3K/Player4.wav";

        const char* Three_KC3K = "VO_KC3K/Three.wav";
        const char* Two_KC3K = "VO_KC3K/Two.wav";
        const char* One_KC3K = "VO_KC3K/One.wav";
        const char* Go_KC3K = "VO_KC3K/Go.wav";
        const char* Goal_KC3K = "VO_KC3K/Goal.wav";

        const char* Sonic_KC3K = "VO_KC3K/Sonic.wav";
        const char* SonicWins_KC3K = "VO_KC3K/SonicWins.wav";
        const char* Tails_KC3K = "VO_KC3K/Tails.wav";
        const char* TailsWins_KC3K = "VO_KC3K/TailsWins.wav";
        const char* Knuckles_KC3K = "VO_KC3K/Knuckles.wav";
        const char* KnuxWins_KC3K = "VO_KC3K/KnuxWins.wav";
        const char* Mighty_KC3K = "VO_KC3K/Mighty.wav";
        const char* MightyWins_KC3K = "VO_KC3K/MightyWins.wav";
        const char* Ray_KC3K = "VO_KC3K/Ray.wav";
        const char* RayWins_KC3K = "VO_KC3K/RayWins.wav";

        const char* TheWinnerIs_KC3K = "VO_KC3K/TheWinnerIs.wav";

        const char* ItsADraw_KC3K = "VO_KC3K/ItsADraw.wav";
        const char* ItsADraw_Set_KC3K = "VO_KC3K/ItsADraw_Set.wav";

        const char* NewRecordMid_KC3K = "VO_KC3K/NewRecordMid.wav";
        const char* NewRecordTop_KC3K = "VO_KC3K/NewRecordTop.wav";

    #pragma endregion


    bool HasAnnouncersLoaded = false;

    inline void SetWriteProtection()
    {
        DWORD PalettesMemory;
        VirtualProtect((void*)Three_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)Player1_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)Player2_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)Player3_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)Player4_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);

        VirtualProtect((void*)Three_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)Two_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)One_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)Go_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)Goal_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)Goal_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);

        VirtualProtect((void*)Sonic_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)SonicWins_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)Tails_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)TailsWins_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)Knuckles_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)KnuxWins_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)Mighty_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)MightyWins_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)Ray_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)RayWins_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);

        VirtualProtect((void*)TheWinnerIs_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);

        VirtualProtect((void*)ItsADraw_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)ItsADraw_Set_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);

        VirtualProtect((void*)NewRecordMid_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
        VirtualProtect((void*)NewRecordTop_MemoryAdd, 0x00178000, PAGE_EXECUTE_READWRITE, &PalettesMemory);
    }

    inline void SwapSound(int* Path, char* String)
    {
        if (ShowLogging) LogInfo("CompPlus_Announcers::SwapSound", "Swaping SoundFX: %s", String);
        *Path = (int)(&String[0]);
    }

    inline void LoadSound(const char* path, SonicMania::Scope scope)
    {
        if (ShowLogging) LogInfo("CompPlus_Announcers::LoadSoundFX", "Loading SoundFX: %s", path);
        LoadSoundFX(path, scope);
    }

    inline void UnloadSound(const char* path)
    {
        if (ShowLogging) LogInfo("CompPlus_Announcers::UnloadSound", "Unloading SoundFX: %s", path);
        short soundFXID = SonicMania::GetSoundFXID(path);
        if (soundFXID != -1)
        {
            intptr_t sfxPtr = (baseAddress + 0x00A5ACB5);
            *((Scope*)(sfxPtr - 0 + 32 * soundFXID)) = Scope_None;
            memset((void*)(sfxPtr - 13 + 32 * soundFXID), 0, 16);
            memset((void*)(sfxPtr - 29 + 32 * soundFXID), 0, 16);
        }
    }

    CompPlus_Settings::AnnouncerType LoadedAnnouncer;

    void PlayAnnouncerChangeFX(CompPlus_Settings::AnnouncerType Selection)
    {
        if (Selection == CompPlus_Settings::Announcer_Garrulous64)
        {
            PlaySoundFXS((char*)Go_Garrulous64);
        }
        else if (Selection == CompPlus_Settings::Announcer_Angelthegamer)
        {
            PlaySoundFXS((char*)Go_ATG);
        }
        else if (Selection == CompPlus_Settings::Announcer_Memes)
        {
            PlaySoundFXS((char*)Go_Memes);
        }
        else if (Selection == CompPlus_Settings::Announcer_Classic)
        {
            PlaySoundFXS((char*)Go_Classic);
        }
        else if (Selection == CompPlus_Settings::Announcer_KC3K)
        {
            PlaySoundFXS((char*)Go_KC3K);
        }
        else
        {
            PlaySoundFXS((char*)Go_Stock);
        }
    }

    void ChangeAnnouncer()
    {
        if (LoadedAnnouncer == CompPlus_Settings::Announcer_Garrulous64)
        {
            SwapSound(Player1_MemoryAdd, (char*)Player1_Garrulous64);
            SwapSound(Player2_MemoryAdd, (char*)Player2_Garrulous64);
            SwapSound(Player3_MemoryAdd, (char*)Player3_Garrulous64);
            SwapSound(Player4_MemoryAdd, (char*)Player4_Garrulous64);

            SwapSound(SonicWins_MemoryAdd, (char*)SonicWins_Garrulous64);
            SwapSound(TailsWins_MemoryAdd, (char*)TailsWins_Garrulous64);
            SwapSound(KnuxWins_MemoryAdd, (char*)KnuxWins_Garrulous64);
            SwapSound(MightyWins_MemoryAdd, (char*)MightyWins_Garrulous64);
            SwapSound(RayWins_MemoryAdd, (char*)RayWins_Garrulous64);

            SwapSound(ItsADraw_MemoryAdd, (char*)ItsADraw_Garrulous64);
            SwapSound(ItsADraw_Set_MemoryAdd, (char*)ItsADraw_Set_Garrulous64);

            SwapSound(Three_MemoryAdd, (char*)Three_Garrulous64);
            SwapSound(Two_MemoryAdd, (char*)Two_Garrulous64);
            SwapSound(One_MemoryAdd, (char*)One_Garrulous64);
            SwapSound(Go_MemoryAdd, (char*)Go_Garrulous64);

            SwapSound(Sonic_MemoryAdd, (char*)Sonic_Garrulous64);
            SwapSound(Tails_MemoryAdd, (char*)Tails_Garrulous64);
            SwapSound(Knuckles_MemoryAdd, (char*)Knuckles_Garrulous64);
            SwapSound(Mighty_MemoryAdd, (char*)Mighty_Garrulous64);
            SwapSound(Ray_MemoryAdd, (char*)Ray_Garrulous64);

            SwapSound(Goal_MemoryAdd, (char*)Goal_Garrulous64);
            SwapSound(Goal_MemoryAdd_2, (char*)Goal_Garrulous64);

            SwapSound(TheWinnerIs_MemoryAdd, (char*)TheWinnerIs_Garrulous64);

            SwapSound(NewRecordMid_MemoryAdd, (char*)NewRecordMid_Garrulous64);
            SwapSound(NewRecordTop_MemoryAdd, (char*)NewRecordTop_Garrulous64);
        }
        else if (LoadedAnnouncer == CompPlus_Settings::Announcer_Angelthegamer)
        {
            SwapSound(Player1_MemoryAdd, (char*)Player1_ATG);
            SwapSound(Player2_MemoryAdd, (char*)Player2_ATG);
            SwapSound(Player3_MemoryAdd, (char*)Player3_ATG);
            SwapSound(Player4_MemoryAdd, (char*)Player4_ATG);

            SwapSound(SonicWins_MemoryAdd, (char*)SonicWins_ATG);
            SwapSound(TailsWins_MemoryAdd, (char*)TailsWins_ATG);
            SwapSound(KnuxWins_MemoryAdd, (char*)KnuxWins_ATG);
            SwapSound(MightyWins_MemoryAdd, (char*)MightyWins_ATG);
            SwapSound(RayWins_MemoryAdd, (char*)RayWins_ATG);

            SwapSound(ItsADraw_MemoryAdd, (char*)ItsADraw_ATG);
            SwapSound(ItsADraw_Set_MemoryAdd, (char*)ItsADraw_Set_ATG);

            SwapSound(Three_MemoryAdd, (char*)Three_ATG);
            SwapSound(Two_MemoryAdd, (char*)Two_ATG);
            SwapSound(One_MemoryAdd, (char*)One_ATG);
            SwapSound(Go_MemoryAdd, (char*)Go_ATG);

            SwapSound(Sonic_MemoryAdd, (char*)Sonic_ATG);
            SwapSound(Tails_MemoryAdd, (char*)Tails_ATG);
            SwapSound(Knuckles_MemoryAdd, (char*)Knuckles_ATG);
            SwapSound(Mighty_MemoryAdd, (char*)Mighty_ATG);
            SwapSound(Ray_MemoryAdd, (char*)Ray_ATG);

            SwapSound(Goal_MemoryAdd, (char*)Goal_ATG);
            SwapSound(Goal_MemoryAdd_2, (char*)Goal_ATG);

            SwapSound(TheWinnerIs_MemoryAdd, (char*)TheWinnerIs_ATG);

            SwapSound(NewRecordMid_MemoryAdd, (char*)NewRecordMid_ATG);
            SwapSound(NewRecordTop_MemoryAdd, (char*)NewRecordTop_ATG);
        }
        else if (LoadedAnnouncer == CompPlus_Settings::Announcer_Memes)
        {
            SwapSound(Player1_MemoryAdd, (char*)Player1_Memes);
            SwapSound(Player2_MemoryAdd, (char*)Player2_Memes);
            SwapSound(Player3_MemoryAdd, (char*)Player3_Memes);
            SwapSound(Player4_MemoryAdd, (char*)Player4_Memes);

            SwapSound(SonicWins_MemoryAdd, (char*)SonicWins_Memes);
            SwapSound(TailsWins_MemoryAdd, (char*)TailsWins_Memes);
            SwapSound(KnuxWins_MemoryAdd, (char*)KnuxWins_Memes);
            SwapSound(MightyWins_MemoryAdd, (char*)MightyWins_Memes);
            SwapSound(RayWins_MemoryAdd, (char*)RayWins_Memes);

            SwapSound(ItsADraw_MemoryAdd, (char*)ItsADraw_Memes);
            SwapSound(ItsADraw_Set_MemoryAdd, (char*)ItsADraw_Set_Memes);

            SwapSound(Three_MemoryAdd, (char*)Three_Memes);
            SwapSound(Two_MemoryAdd, (char*)Two_Memes);
            SwapSound(One_MemoryAdd, (char*)One_Memes);
            SwapSound(Go_MemoryAdd, (char*)Go_Memes);

            SwapSound(Sonic_MemoryAdd, (char*)Sonic_Memes);
            SwapSound(Tails_MemoryAdd, (char*)Tails_Memes);
            SwapSound(Knuckles_MemoryAdd, (char*)Knuckles_Memes);
            SwapSound(Mighty_MemoryAdd, (char*)Mighty_Memes);
            SwapSound(Ray_MemoryAdd, (char*)Ray_Memes);

            SwapSound(Goal_MemoryAdd, (char*)Goal_Memes);
            SwapSound(Goal_MemoryAdd_2, (char*)Goal_Memes);

            SwapSound(TheWinnerIs_MemoryAdd, (char*)TheWinnerIs_Memes);

            SwapSound(NewRecordMid_MemoryAdd, (char*)NewRecordMid_Memes);
            SwapSound(NewRecordTop_MemoryAdd, (char*)NewRecordTop_Memes);
        }
        else if (LoadedAnnouncer == CompPlus_Settings::Announcer_Classic)
        {
            SwapSound(Player1_MemoryAdd, (char*)Player1_Classic);
            SwapSound(Player2_MemoryAdd, (char*)Player2_Classic);
            SwapSound(Player3_MemoryAdd, (char*)Player3_Classic);
            SwapSound(Player4_MemoryAdd, (char*)Player4_Classic);

            SwapSound(SonicWins_MemoryAdd, (char*)SonicWins_Classic);
            SwapSound(TailsWins_MemoryAdd, (char*)TailsWins_Classic);
            SwapSound(KnuxWins_MemoryAdd, (char*)KnuxWins_Classic);
            SwapSound(MightyWins_MemoryAdd, (char*)MightyWins_Classic);
            SwapSound(RayWins_MemoryAdd, (char*)RayWins_Classic);

            SwapSound(ItsADraw_MemoryAdd, (char*)ItsADraw_Classic);
            SwapSound(ItsADraw_Set_MemoryAdd, (char*)ItsADraw_Set_Classic);

            SwapSound(Three_MemoryAdd, (char*)Three_Classic);
            SwapSound(Two_MemoryAdd, (char*)Two_Classic);
            SwapSound(One_MemoryAdd, (char*)One_Classic);
            SwapSound(Go_MemoryAdd, (char*)Go_Classic);

            SwapSound(Sonic_MemoryAdd, (char*)Sonic_Classic);
            SwapSound(Tails_MemoryAdd, (char*)Tails_Classic);
            SwapSound(Knuckles_MemoryAdd, (char*)Knuckles_Classic);
            SwapSound(Mighty_MemoryAdd, (char*)Mighty_Classic);
            SwapSound(Ray_MemoryAdd, (char*)Ray_Classic);

            SwapSound(Goal_MemoryAdd, (char*)Goal_Classic);
            SwapSound(Goal_MemoryAdd_2, (char*)Goal_Classic);

            SwapSound(TheWinnerIs_MemoryAdd, (char*)TheWinnerIs_Classic);

            SwapSound(NewRecordMid_MemoryAdd, (char*)NewRecordMid_Classic);
            SwapSound(NewRecordTop_MemoryAdd, (char*)NewRecordTop_Classic);
        }
        else if (LoadedAnnouncer == CompPlus_Settings::Announcer_Default)
        {
            SwapSound(Player1_MemoryAdd, (char*)Player1_Stock);
            SwapSound(Player2_MemoryAdd, (char*)Player2_Stock);
            SwapSound(Player3_MemoryAdd, (char*)Player3_Stock);
            SwapSound(Player4_MemoryAdd, (char*)Player4_Stock);

            SwapSound(SonicWins_MemoryAdd, (char*)SonicWins_Stock);
            SwapSound(TailsWins_MemoryAdd, (char*)TailsWins_Stock);
            SwapSound(KnuxWins_MemoryAdd, (char*)KnuxWins_Stock);
            SwapSound(MightyWins_MemoryAdd, (char*)MightyWins_Stock);
            SwapSound(RayWins_MemoryAdd, (char*)RayWins_Stock);

            SwapSound(ItsADraw_MemoryAdd, (char*)ItsADraw_Stock);
            SwapSound(ItsADraw_Set_MemoryAdd, (char*)ItsADraw_Set_Stock);

            SwapSound(Three_MemoryAdd, (char*)Three_Stock);
            SwapSound(Two_MemoryAdd, (char*)Two_Stock);
            SwapSound(One_MemoryAdd, (char*)One_Stock);
            SwapSound(Go_MemoryAdd, (char*)Go_Stock);

            SwapSound(Sonic_MemoryAdd, (char*)Sonic_Stock);
            SwapSound(Tails_MemoryAdd, (char*)Tails_Stock);
            SwapSound(Knuckles_MemoryAdd, (char*)Knuckles_Stock);
            SwapSound(Mighty_MemoryAdd, (char*)Mighty_Stock);
            SwapSound(Ray_MemoryAdd, (char*)Ray_Stock);

            SwapSound(Goal_MemoryAdd, (char*)Goal_Stock);
            SwapSound(Goal_MemoryAdd_2, (char*)Goal_Stock);

            SwapSound(TheWinnerIs_MemoryAdd, (char*)TheWinnerIs_Stock);

            SwapSound(NewRecordMid_MemoryAdd, (char*)NewRecordMid_Stock);
            SwapSound(NewRecordTop_MemoryAdd, (char*)NewRecordTop_Stock);
        }
    }

    void UnloadAnnouncer()
    {
        if (LoadedAnnouncer == CompPlus_Settings::Announcer_Garrulous64)
        {
            UnloadSound((char*)Player1_Garrulous64);
            UnloadSound((char*)Player2_Garrulous64);
            UnloadSound((char*)Player3_Garrulous64);
            UnloadSound((char*)Player4_Garrulous64);

            UnloadSound((char*)SonicWins_Garrulous64);
            UnloadSound((char*)TailsWins_Garrulous64);
            UnloadSound((char*)KnuxWins_Garrulous64);
            UnloadSound((char*)MightyWins_Garrulous64);
            UnloadSound((char*)RayWins_Garrulous64);

            UnloadSound((char*)ItsADraw_Garrulous64);
            UnloadSound((char*)ItsADraw_Set_Garrulous64);

            UnloadSound((char*)Three_Garrulous64);
            UnloadSound((char*)Two_Garrulous64);
            UnloadSound((char*)One_Garrulous64);
            UnloadSound((char*)Go_Garrulous64);

            UnloadSound((char*)Sonic_Garrulous64);
            UnloadSound((char*)Tails_Garrulous64);
            UnloadSound((char*)Knuckles_Garrulous64);
            UnloadSound((char*)Mighty_Garrulous64);
            UnloadSound((char*)Ray_Garrulous64);

            UnloadSound((char*)Goal_Garrulous64);

            UnloadSound((char*)TheWinnerIs_Garrulous64);

            UnloadSound((char*)NewRecordMid_Garrulous64);
            UnloadSound((char*)NewRecordTop_Garrulous64);
        }
        else if (LoadedAnnouncer == CompPlus_Settings::Announcer_Angelthegamer)
        {
            UnloadSound((char*)Player1_ATG);
            UnloadSound((char*)Player2_ATG);
            UnloadSound((char*)Player3_ATG);
            UnloadSound((char*)Player4_ATG);

            UnloadSound((char*)SonicWins_ATG);
            UnloadSound((char*)TailsWins_ATG);
            UnloadSound((char*)KnuxWins_ATG);
            UnloadSound((char*)MightyWins_ATG);
            UnloadSound((char*)RayWins_ATG);

            UnloadSound((char*)ItsADraw_ATG);
            UnloadSound((char*)ItsADraw_Set_ATG);

            UnloadSound((char*)Three_ATG);
            UnloadSound((char*)Two_ATG);
            UnloadSound((char*)One_ATG);
            UnloadSound((char*)Go_ATG);

            UnloadSound((char*)Sonic_ATG);
            UnloadSound((char*)Tails_ATG);
            UnloadSound((char*)Knuckles_ATG);
            UnloadSound((char*)Mighty_ATG);
            UnloadSound((char*)Ray_ATG);

            UnloadSound((char*)Goal_ATG);

            UnloadSound((char*)TheWinnerIs_ATG);

            UnloadSound((char*)NewRecordMid_ATG);
            UnloadSound((char*)NewRecordTop_ATG);
        }
        else if (LoadedAnnouncer == CompPlus_Settings::Announcer_Memes)
        {
            UnloadSound((char*)Player1_Memes);
            UnloadSound((char*)Player2_Memes);
            UnloadSound((char*)Player3_Memes);
            UnloadSound((char*)Player4_Memes);

            UnloadSound((char*)SonicWins_Memes);
            UnloadSound((char*)TailsWins_Memes);
            UnloadSound((char*)KnuxWins_Memes);
            UnloadSound((char*)MightyWins_Memes);
            UnloadSound((char*)RayWins_Memes);

            UnloadSound((char*)ItsADraw_Memes);
            UnloadSound((char*)ItsADraw_Set_Memes);

            UnloadSound((char*)Three_Memes);
            UnloadSound((char*)Two_Memes);
            UnloadSound((char*)One_Memes);
            UnloadSound((char*)Go_Memes);

            UnloadSound((char*)Sonic_Memes);
            UnloadSound((char*)Tails_Memes);
            UnloadSound((char*)Knuckles_Memes);
            UnloadSound((char*)Mighty_Memes);
            UnloadSound((char*)Ray_Memes);

            UnloadSound((char*)Goal_Memes);

            UnloadSound((char*)TheWinnerIs_Memes);

            UnloadSound((char*)NewRecordMid_Memes);
            UnloadSound((char*)NewRecordTop_Memes);
        }
        else if (LoadedAnnouncer == CompPlus_Settings::Announcer_Classic)
        {
            UnloadSound((char*)Player1_Classic);
            UnloadSound((char*)Player2_Classic);
            UnloadSound((char*)Player3_Classic);
            UnloadSound((char*)Player4_Classic);

            UnloadSound((char*)SonicWins_Classic);
            UnloadSound((char*)TailsWins_Classic);
            UnloadSound((char*)KnuxWins_Classic);
            UnloadSound((char*)MightyWins_Classic);
            UnloadSound((char*)RayWins_Classic);

            UnloadSound((char*)ItsADraw_Classic);
            UnloadSound((char*)ItsADraw_Set_Classic);

            UnloadSound((char*)Three_Classic);
            UnloadSound((char*)Two_Classic);
            UnloadSound((char*)One_Classic);
            UnloadSound((char*)Go_Classic);

            UnloadSound((char*)Sonic_Classic);
            UnloadSound((char*)Tails_Classic);
            UnloadSound((char*)Knuckles_Classic);
            UnloadSound((char*)Mighty_Classic);
            UnloadSound((char*)Ray_Classic);

            UnloadSound((char*)Goal_Classic);

            UnloadSound((char*)TheWinnerIs_Classic);

            UnloadSound((char*)NewRecordMid_Classic);
            UnloadSound((char*)NewRecordTop_Classic);
        }
        else if (LoadedAnnouncer == CompPlus_Settings::Announcer_KC3K) 
        {
            SwapSound(Player1_MemoryAdd, (char*)Player1_KC3K);
            SwapSound(Player2_MemoryAdd, (char*)Player2_KC3K);
            SwapSound(Player3_MemoryAdd, (char*)Player3_KC3K);
            SwapSound(Player4_MemoryAdd, (char*)Player4_KC3K);

            SwapSound(SonicWins_MemoryAdd, (char*)SonicWins_KC3K);
            SwapSound(TailsWins_MemoryAdd, (char*)TailsWins_KC3K);
            SwapSound(KnuxWins_MemoryAdd, (char*)KnuxWins_KC3K);
            SwapSound(MightyWins_MemoryAdd, (char*)MightyWins_KC3K);
            SwapSound(RayWins_MemoryAdd, (char*)RayWins_KC3K);

            SwapSound(ItsADraw_MemoryAdd, (char*)ItsADraw_KC3K);
            SwapSound(ItsADraw_Set_MemoryAdd, (char*)ItsADraw_Set_KC3K);

            SwapSound(Three_MemoryAdd, (char*)Three_KC3K);
            SwapSound(Two_MemoryAdd, (char*)Two_KC3K);
            SwapSound(One_MemoryAdd, (char*)One_KC3K);
            SwapSound(Go_MemoryAdd, (char*)Go_KC3K);

            SwapSound(Sonic_MemoryAdd, (char*)Sonic_KC3K);
            SwapSound(Tails_MemoryAdd, (char*)Tails_KC3K);
            SwapSound(Knuckles_MemoryAdd, (char*)Knuckles_KC3K);
            SwapSound(Mighty_MemoryAdd, (char*)Mighty_KC3K);
            SwapSound(Ray_MemoryAdd, (char*)Ray_KC3K);

            SwapSound(Goal_MemoryAdd, (char*)Goal_KC3K);
            SwapSound(Goal_MemoryAdd_2, (char*)Goal_KC3K);

            SwapSound(TheWinnerIs_MemoryAdd, (char*)TheWinnerIs_KC3K);

            SwapSound(NewRecordMid_MemoryAdd, (char*)NewRecordMid_KC3K);
            SwapSound(NewRecordTop_MemoryAdd, (char*)NewRecordTop_KC3K);
        }
        else
        {
            UnloadSound((char*)Player1_Stock);
            UnloadSound((char*)Player2_Stock);
            UnloadSound((char*)Player3_Stock);
            UnloadSound((char*)Player4_Stock);

            UnloadSound((char*)SonicWins_Stock);
            UnloadSound((char*)TailsWins_Stock);
            UnloadSound((char*)KnuxWins_Stock);
            UnloadSound((char*)MightyWins_Stock);
            UnloadSound((char*)RayWins_Stock);

            UnloadSound((char*)ItsADraw_Stock);
            UnloadSound((char*)ItsADraw_Set_Stock);

            UnloadSound((char*)Three_Stock);
            UnloadSound((char*)Two_Stock);
            UnloadSound((char*)One_Stock);
            UnloadSound((char*)Go_Stock);

            UnloadSound((char*)Sonic_Stock);
            UnloadSound((char*)Tails_Stock);
            UnloadSound((char*)Knuckles_Stock);
            UnloadSound((char*)Mighty_Stock);
            UnloadSound((char*)Ray_Stock);

            UnloadSound((char*)Goal_Stock);

            UnloadSound((char*)TheWinnerIs_Stock);

            UnloadSound((char*)NewRecordMid_Stock);
            UnloadSound((char*)NewRecordTop_Stock);
        }

    }

    void LoadAnnouncerFX(bool ChangeAnnouncer = true)
    {
        if (!HasAnnouncersLoaded)
        {
            SetWriteProtection();
            UnloadAnnouncer();

            LoadedAnnouncer = CompPlus_Settings::CurrentAnnouncer;

            if (CompPlus_Settings::CurrentAnnouncer == CompPlus_Settings::Announcer_Garrulous64)
            {
                LoadSound(Player1_Garrulous64, Scope_Global);
                LoadSound(Player2_Garrulous64, Scope_Global);
                LoadSound(Player3_Garrulous64, Scope_Global);
                LoadSound(Player4_Garrulous64, Scope_Global);

                LoadSound(SonicWins_Garrulous64, Scope_Global);
                LoadSound(TailsWins_Garrulous64, Scope_Global);
                LoadSound(KnuxWins_Garrulous64, Scope_Global);
                LoadSound(MightyWins_Garrulous64, Scope_Global);
                LoadSound(RayWins_Garrulous64, Scope_Global);

                LoadSound(ItsADraw_Garrulous64, Scope_Global);
                LoadSound(ItsADraw_Set_Garrulous64, Scope_Global);

                LoadSound(Three_Garrulous64, Scope_Global);
                LoadSound(Two_Garrulous64, Scope_Global);
                LoadSound(One_Garrulous64, Scope_Global);

                LoadSound(Sonic_Garrulous64, Scope_Global);
                LoadSound(Tails_Garrulous64, Scope_Global);
                LoadSound(Knuckles_Garrulous64, Scope_Global);
                LoadSound(Mighty_Garrulous64, Scope_Global);
                LoadSound(Ray_Garrulous64, Scope_Global);

                LoadSound(Goal_Garrulous64, Scope_Global);

                LoadSound(TheWinnerIs_Garrulous64, Scope_Global);

                LoadSound(NewRecordMid_Garrulous64, Scope_Global);
                LoadSound(NewRecordTop_Garrulous64, Scope_Global);
            }
            else if (CompPlus_Settings::CurrentAnnouncer == CompPlus_Settings::Announcer_Angelthegamer)
            {
                LoadSound(Player1_ATG, Scope_Global);
                LoadSound(Player2_ATG, Scope_Global);
                LoadSound(Player3_ATG, Scope_Global);
                LoadSound(Player4_ATG, Scope_Global);

                LoadSound(SonicWins_ATG, Scope_Global);
                LoadSound(TailsWins_ATG, Scope_Global);
                LoadSound(KnuxWins_ATG, Scope_Global);
                LoadSound(MightyWins_ATG, Scope_Global);
                LoadSound(RayWins_ATG, Scope_Global);

                LoadSound(ItsADraw_ATG, Scope_Global);
                LoadSound(ItsADraw_Set_ATG, Scope_Global);

                LoadSound(Three_ATG, Scope_Global);
                LoadSound(Two_ATG, Scope_Global);
                LoadSound(One_ATG, Scope_Global);

                LoadSound(Sonic_ATG, Scope_Global);
                LoadSound(Tails_ATG, Scope_Global);
                LoadSound(Knuckles_ATG, Scope_Global);
                LoadSound(Mighty_ATG, Scope_Global);
                LoadSound(Ray_ATG, Scope_Global);

                LoadSound(Goal_ATG, Scope_Global);

                LoadSound(TheWinnerIs_ATG, Scope_Global);

                LoadSound(NewRecordMid_ATG, Scope_Global);
                LoadSound(NewRecordTop_ATG, Scope_Global);
            }
            else if (CompPlus_Settings::CurrentAnnouncer == CompPlus_Settings::Announcer_Memes)
            {
                LoadSound(Player1_Memes, Scope_Global);
                LoadSound(Player2_Memes, Scope_Global);
                LoadSound(Player3_Memes, Scope_Global);
                LoadSound(Player4_Memes, Scope_Global);

                LoadSound(SonicWins_Memes, Scope_Global);
                LoadSound(TailsWins_Memes, Scope_Global);
                LoadSound(KnuxWins_Memes, Scope_Global);
                LoadSound(MightyWins_Memes, Scope_Global);
                LoadSound(RayWins_Memes, Scope_Global);

                LoadSound(ItsADraw_Memes, Scope_Global);
                LoadSound(ItsADraw_Set_Memes, Scope_Global);

                LoadSound(Three_Memes, Scope_Global);
                LoadSound(Two_Memes, Scope_Global);
                LoadSound(One_Memes, Scope_Global);

                LoadSound(Sonic_Memes, Scope_Global);
                LoadSound(Tails_Memes, Scope_Global);
                LoadSound(Knuckles_Memes, Scope_Global);
                LoadSound(Mighty_Memes, Scope_Global);
                LoadSound(Ray_Memes, Scope_Global);

                LoadSound(Goal_Memes, Scope_Global);

                LoadSound(TheWinnerIs_Memes, Scope_Global);

                LoadSound(NewRecordMid_Memes, Scope_Global);
                LoadSound(NewRecordTop_Memes, Scope_Global);
            }
            else if (CompPlus_Settings::CurrentAnnouncer == CompPlus_Settings::Announcer_Classic)
            {
                LoadSound(Player1_Classic, Scope_Global);
                LoadSound(Player2_Classic, Scope_Global);
                LoadSound(Player3_Classic, Scope_Global);
                LoadSound(Player4_Classic, Scope_Global);

                LoadSound(SonicWins_Classic, Scope_Global);
                LoadSound(TailsWins_Classic, Scope_Global);
                LoadSound(KnuxWins_Classic, Scope_Global);
                LoadSound(MightyWins_Classic, Scope_Global);
                LoadSound(RayWins_Classic, Scope_Global);

                LoadSound(ItsADraw_Classic, Scope_Global);
                LoadSound(ItsADraw_Set_Classic, Scope_Global);

                LoadSound(Three_Classic, Scope_Global);
                LoadSound(Two_Classic, Scope_Global);
                LoadSound(One_Classic, Scope_Global);

                LoadSound(Sonic_Classic, Scope_Global);
                LoadSound(Tails_Classic, Scope_Global);
                LoadSound(Knuckles_Classic, Scope_Global);
                LoadSound(Mighty_Classic, Scope_Global);
                LoadSound(Ray_Classic, Scope_Global);

                LoadSound(Goal_Classic, Scope_Global);

                LoadSound(TheWinnerIs_Classic, Scope_Global);

                LoadSound(NewRecordMid_Classic, Scope_Global);
                LoadSound(NewRecordTop_Classic, Scope_Global);

            }
            else if (LoadedAnnouncer == CompPlus_Settings::Announcer_KC3K) 
            {
                LoadSound(Player1_KC3K, Scope_Global);
                LoadSound(Player2_KC3K, Scope_Global);
                LoadSound(Player3_KC3K, Scope_Global);
                LoadSound(Player4_KC3K, Scope_Global);

                LoadSound(SonicWins_KC3K, Scope_Global);
                LoadSound(TailsWins_KC3K, Scope_Global);
                LoadSound(KnuxWins_KC3K, Scope_Global);
                LoadSound(MightyWins_KC3K, Scope_Global);
                LoadSound(RayWins_KC3K, Scope_Global);

                LoadSound(ItsADraw_KC3K, Scope_Global);
                LoadSound(ItsADraw_Set_KC3K, Scope_Global);

                LoadSound(Three_KC3K, Scope_Global);
                LoadSound(Two_KC3K, Scope_Global);
                LoadSound(One_KC3K, Scope_Global);

                LoadSound(Sonic_KC3K, Scope_Global);
                LoadSound(Tails_KC3K, Scope_Global);
                LoadSound(Knuckles_KC3K, Scope_Global);
                LoadSound(Mighty_KC3K, Scope_Global);
                LoadSound(Ray_KC3K, Scope_Global);

                LoadSound(Goal_KC3K, Scope_Global);

                LoadSound(TheWinnerIs_KC3K, Scope_Global);

                LoadSound(NewRecordMid_KC3K, Scope_Global);
                LoadSound(NewRecordTop_KC3K, Scope_Global);
            }
            else if (CompPlus_Settings::CurrentAnnouncer == CompPlus_Settings::Announcer_Default)
            {          
                LoadSound(Player1_Stock, Scope_Global);
                LoadSound(Player2_Stock, Scope_Global);
                LoadSound(Player3_Stock, Scope_Global);
                LoadSound(Player4_Stock, Scope_Global);

                LoadSound(SonicWins_Stock, Scope_Global);
                LoadSound(TailsWins_Stock, Scope_Global);
                LoadSound(KnuxWins_Stock, Scope_Global);
                LoadSound(MightyWins_Stock, Scope_Global);
                LoadSound(RayWins_Stock, Scope_Global);

                LoadSound(ItsADraw_Stock, Scope_Global);
                LoadSound(ItsADraw_Set_Stock, Scope_Global);

                LoadSound(Three_Stock, Scope_Global);
                LoadSound(Two_Stock, Scope_Global);
                LoadSound(One_Stock, Scope_Global);

                LoadSound(Sonic_Stock, Scope_Global);
                LoadSound(Tails_Stock, Scope_Global);
                LoadSound(Knuckles_Stock, Scope_Global);
                LoadSound(Mighty_Stock, Scope_Global);
                LoadSound(Ray_Stock, Scope_Global);

                LoadSound(Goal_Stock, Scope_Global);

                LoadSound(TheWinnerIs_Stock, Scope_Global);

                LoadSound(NewRecordMid_Stock, Scope_Global);
                LoadSound(NewRecordTop_Stock, Scope_Global);
            }

            LoadSound(Go_Garrulous64, Scope_Global);
            LoadSound(Go_ATG, Scope_Global);
            LoadSound(Go_Memes, Scope_Global);
            LoadSound(Go_Classic, Scope_Global);
            LoadSound(Go_KC3K, Scope_Global);
            LoadSound(Go_Stock, Scope_Global);

            if (ChangeAnnouncer) CompPlus_Announcers::ChangeAnnouncer();

            HasAnnouncersLoaded = true;
        }
    }

    //This Would be what LoadSounds() Calls first
    void LoadAnnouncerFX()
    {
        LoadAnnouncerFX(true);
    }

    void ReloadAnnouncerFX()
    {
        if (AllowReload && ReloadRequired)
        {
            UnloadAnnouncer();
            HasAnnouncersLoaded = false;
            LoadAnnouncerFX(true);
            ReloadRequired = false;
        }
    }
}