#pragma once
#include "include/SonicMania.h"

namespace CompPlus_Announcers
{



	#pragma region VO Memory Addresses

	    int* Player1_MemoryAdd = (int*)(baseAddress + 0x1310D);
		int* Player2_MemoryAdd = (int*)(baseAddress + 0x13122);
		int* Player3_MemoryAdd = (int*)(baseAddress + 0x13137);	
		int* Player4_MemoryAdd = (int*)(baseAddress + 0x1314C);			

		int* Three_MemoryAdd = (int*)(baseAddress + 0x1324A);
		int* Two_MemoryAdd = (int*)(baseAddress + 0x1325F);
		int* One_MemoryAdd = (int*)(baseAddress + 0x13274);
		int* Go_MemoryAdd = (int*)(baseAddress + 0x13289);

		int* Goal_MemoryAdd = (int*)(baseAddress + 0x1329F);
		int* Goal_MemoryAdd_2 = (int*)(baseAddress + 0x132FD);

		int* Sonic_MemoryAdd = (int*)(baseAddress + 0x13093);			//SonicMania.exe+13092  { ("VO/Sonic.wav") }
		int* Tails_MemoryAdd = (int*)(baseAddress + 0x130A4);			//SonicMania.exe+130A3  { ("VO/Tails.wav") }
		int* Knuckles_MemoryAdd = (int*)(baseAddress + 0x130B9);		//SonicMania.exe+130B8  { ("VO/Knuckles.wav") }
		int* Mighty_MemoryAdd = (int*)(baseAddress + 0x130CE);			//SonicMania.exe+130CD  { ("VO/Mighty.wav") }
		int* Ray_MemoryAdd = (int*)(baseAddress + 0xD430E3);			//SonicMania.exe+130E2  { ("VO/Ray.wav") }

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

	const char* Player1_ATG = "VO_ATG/Player1.wav";
	const char* Player2_ATG = "VO_ATG/Player2.wav";
	const char* Player3_ATG = "VO_ATG/Player3.wav";
	const char* Player4_ATG = "VO_ATG/Player4.wav";

	const char* Three_ATG = "VO_ATG/Three.wav";
	const char* Two_ATG = "VO_ATG/Two.wav";
	const char* One_ATG = "VO_ATG/One.wav";
	const char* Go_ATG = "VO_ATG/Go.wav";
	const char* Goal_ATG = "VO_ATG/Goal.wav";

	const char* Sonic_ATG = "VO_ATG/Sonic.wav";
	const char* SonicWins_ATG = "VO_ATG/SonicWins.wav";
	const char* Tails_ATG = "VO_ATG/Tails.wav";
	const char* TailsWins_ATG = "VO_ATG/TailsWins.wav";
	const char* Knuckles_ATG = "VO_ATG/Knuckles.wav";
	const char* KnuxWins_ATG = "VO_ATG/KnuxWins.wav";
	const char* Mighty_ATG = "VO_ATG/Mighty.wav";
	const char* MightyWins_ATG = "VO_ATG/MightyWins.wav";
	const char* Ray_ATG = "VO_ATG/Ray.wav";
	const char* RayWins_ATG = "VO_ATG/RayWins.wav";

	const char* TheWinnerIs_ATG = "VO_ATG/TheWinnerIs.wav";

	const char* ItsADraw_ATG = "VO_ATG/ItsADraw.wav";
	const char* ItsADraw_Set_ATG = "VO_ATG/ItsADraw_Set.wav";

	const char* NewRecordMid_ATG = "VO_ATG/NewRecordMid.wav";
	const char* NewRecordTop_ATG = "VO_ATG/NewRecordTop.wav";

	#pragma endregion

	#pragma region Garrulous64 VO Paths

		const char* Player1_Garrulous64 = "VO_Garrulous64/Player1.wav";
		const char* Player2_Garrulous64 = "VO_Garrulous64/Player2.wav";
		const char* Player3_Garrulous64 = "VO_Garrulous64/Player3.wav";
		const char* Player4_Garrulous64 = "VO_Garrulous64/Player4.wav";

		const char* Three_Garrulous64 = "VO_Garrulous64/Three.wav";
		const char* Two_Garrulous64 = "VO_Garrulous64/Two.wav";
		const char* One_Garrulous64 = "VO_Garrulous64/One.wav";
		const char* Go_Garrulous64 = "VO_Garrulous64/Go.wav";
		const char* Goal_Garrulous64 = "VO_Garrulous64/Goal.wav";

		const char* Sonic_Garrulous64 = "VO_Garrulous64/Sonic.wav";
		const char* SonicWins_Garrulous64 = "VO_Garrulous64/SonicWins.wav";
		const char* Tails_Garrulous64 = "VO_Garrulous64/Tails.wav";
		const char* TailsWins_Garrulous64 = "VO_Garrulous64/TailsWins.wav";
		const char* Knuckles_Garrulous64 = "VO_Garrulous64/Knuckles.wav";
		const char* KnuxWins_Garrulous64 = "VO_Garrulous64/KnuxWins.wav";
		const char* Mighty_Garrulous64 = "VO_Garrulous64/Mighty.wav";
		const char* MightyWins_Garrulous64 = "VO_Garrulous64/MightyWins.wav";
		const char* Ray_Garrulous64 = "VO_Garrulous64/Ray.wav";
		const char* RayWins_Garrulous64 = "VO_Garrulous64/RayWins.wav";

		const char* TheWinnerIs_Garrulous64 = "VO_Garrulous64/TheWinnerIs.wav";

		const char* ItsADraw_Garrulous64 = "VO_Garrulous64/ItsADraw.wav";
		const char* ItsADraw_Set_Garrulous64 = "VO_Garrulous64/ItsADraw_Set.wav";

		const char* NewRecordMid_Garrulous64 = "VO_Garrulous64/NewRecordMid.wav";
		const char* NewRecordTop_Garrulous64 = "VO_Garrulous64/NewRecordTop.wav";

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
		*Path = (int)(&String[0]);
	}

	inline void LoadAnnouncerFX()
	{
		if (!HasAnnouncersLoaded)
		{
			SetWriteProtection();

			#pragma region VO Garrulous64

			LoadSoundFX((char*)Player1_Garrulous64, Scope_Global);
			LoadSoundFX((char*)Player2_Garrulous64, Scope_Global);
			LoadSoundFX((char*)Player3_Garrulous64, Scope_Global);
			LoadSoundFX((char*)Player4_Garrulous64, Scope_Global);

			LoadSoundFX((char*)Three_Garrulous64, Scope_Global);
			LoadSoundFX((char*)Two_Garrulous64, Scope_Global);
			LoadSoundFX((char*)One_Garrulous64, Scope_Global);
			LoadSoundFX((char*)Go_Garrulous64, Scope_Global);
			LoadSoundFX((char*)Goal_Garrulous64, Scope_Global);

			LoadSoundFX((char*)Sonic_Garrulous64, Scope_Global);
			LoadSoundFX((char*)SonicWins_Garrulous64, Scope_Global);
			LoadSoundFX((char*)Tails_Garrulous64, Scope_Global);
			LoadSoundFX((char*)TailsWins_Garrulous64, Scope_Global);
			LoadSoundFX((char*)Knuckles_Garrulous64, Scope_Global);
			LoadSoundFX((char*)KnuxWins_Garrulous64, Scope_Global);
			LoadSoundFX((char*)Mighty_Garrulous64, Scope_Global);
			LoadSoundFX((char*)MightyWins_Garrulous64, Scope_Global);
			LoadSoundFX((char*)Ray_Garrulous64, Scope_Global);
			LoadSoundFX((char*)RayWins_Garrulous64, Scope_Global);

			LoadSoundFX((char*)TheWinnerIs_Garrulous64, Scope_Global);
			LoadSoundFX((char*)ItsADraw_Garrulous64, Scope_Global);
			LoadSoundFX((char*)ItsADraw_Set_Garrulous64, Scope_Global);
			LoadSoundFX((char*)NewRecordMid_Garrulous64, Scope_Global);
			LoadSoundFX((char*)NewRecordTop_Garrulous64, Scope_Global);

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
			
			#pragma endregion

			//ChangeAnnouncer();
			HasAnnouncersLoaded = true;
		}
	}



}