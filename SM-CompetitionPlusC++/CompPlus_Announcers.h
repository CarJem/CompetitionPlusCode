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

	#pragma region DanielUK VO Paths

			const char* Player1_DanielUK = "VO_DanielUK/Player1.wav";
			const char* Player2_DanielUK = "VO_DanielUK/Player2.wav";
			const char* Player3_DanielUK = "VO_DanielUK/Player3.wav";
			const char* Player4_DanielUK = "VO_DanielUK/Player4.wav";

			const char* Three_DanielUK = "VO_DanielUK/Three.wav";
			const char* Two_DanielUK = "VO_DanielUK/Two.wav";
			const char* One_DanielUK = "VO_DanielUK/One.wav";
			const char* Go_DanielUK = "VO_DanielUK/Go.wav";
			const char* Goal_DanielUK = "VO_DanielUK/Goal.wav";

			const char* Sonic_DanielUK = "VO_DanielUK/Sonic.wav";
			const char* SonicWins_DanielUK = "VO_DanielUK/SonicWins.wav";
			const char* Tails_DanielUK = "VO_DanielUK/Tails.wav";
			const char* TailsWins_DanielUK = "VO_DanielUK/TailsWins.wav";
			const char* Knuckles_DanielUK = "VO_DanielUK/Knuckles.wav";
			const char* KnuxWins_DanielUK = "VO_DanielUK/KnuxWins.wav";
			const char* Mighty_DanielUK = "VO_DanielUK/Mighty.wav";
			const char* MightyWins_DanielUK = "VO_DanielUK/MightyWins.wav";
			const char* Ray_DanielUK = "VO_DanielUK/Ray.wav";
			const char* RayWins_DanielUK = "VO_DanielUK/RayWins.wav";

			const char* TheWinnerIs_DanielUK = "VO_DanielUK/TheWinnerIs.wav";

			const char* ItsADraw_DanielUK = "VO_DanielUK/ItsADraw.wav";
			const char* ItsADraw_Set_DanielUK = "VO_DanielUK/ItsADraw_Set.wav";

			const char* NewRecordMid_DanielUK = "VO_DanielUK/NewRecordMid.wav";
			const char* NewRecordTop_DanielUK = "VO_DanielUK/NewRecordTop.wav";

	#pragma endregion

	#pragma region Memes VO Paths

				const char* Player1_Memes = "VO_Memes/Player1.wav";
				const char* Player2_Memes = "VO_Memes/Player2.wav";
				const char* Player3_Memes = "VO_Memes/Player3.wav";
				const char* Player4_Memes = "VO_Memes/Player4.wav";

				const char* Three_Memes = "VO_Memes/Three.wav";
				const char* Two_Memes = "VO_Memes/Two.wav";
				const char* One_Memes = "VO_Memes/One.wav";
				const char* Go_Memes = "VO_Memes/Go.wav";
				const char* Goal_Memes = "VO_Memes/Goal.wav";

				const char* Sonic_Memes = "VO_Memes/Sonic.wav";
				const char* SonicWins_Memes = "VO_Memes/SonicWins.wav";
				const char* Tails_Memes = "VO_Memes/Tails.wav";
				const char* TailsWins_Memes = "VO_Memes/TailsWins.wav";
				const char* Knuckles_Memes = "VO_Memes/Knuckles.wav";
				const char* KnuxWins_Memes = "VO_Memes/KnuxWins.wav";
				const char* Mighty_Memes = "VO_Memes/Mighty.wav";
				const char* MightyWins_Memes = "VO_Memes/MightyWins.wav";
				const char* Ray_Memes = "VO_Memes/Ray.wav";
				const char* RayWins_Memes = "VO_Memes/RayWins.wav";

				const char* TheWinnerIs_Memes = "VO_Memes/TheWinnerIs.wav";

				const char* ItsADraw_Memes = "VO_Memes/ItsADraw.wav";
				const char* ItsADraw_Set_Memes = "VO_Memes/ItsADraw_Set.wav";

				const char* NewRecordMid_Memes = "VO_Memes/NewRecordMid.wav";
				const char* NewRecordTop_Memes = "VO_Memes/NewRecordTop.wav";

	#pragma endregion

	#pragma region Sonic 2/3 VO Paths

			const char* Player1_Sonic3 = "VO_Sonic3/Player1.wav";
			const char* Player2_Sonic3 = "VO_Sonic3/Player2.wav";
			const char* Player3_Sonic3 = "VO_Sonic3/Player3.wav";
			const char* Player4_Sonic3 = "VO_Sonic3/Player4.wav";

			const char* Three_Sonic3 = "VO_Sonic3/Three.wav";
			const char* Two_Sonic3 = "VO_Sonic3/Two.wav";
			const char* One_Sonic3 = "VO_Sonic3/One.wav";
			const char* Go_Sonic3 = "VO_Sonic3/Go.wav";
			const char* Goal_Sonic3 = "VO_Sonic3/Goal.wav";

			const char* Sonic_Sonic3 = "VO_Sonic3/Sonic.wav";
			const char* SonicWins_Sonic3 = "VO_Sonic3/SonicWins.wav";
			const char* Tails_Sonic3 = "VO_Sonic3/Tails.wav";
			const char* TailsWins_Sonic3 = "VO_Sonic3/TailsWins.wav";
			const char* Knuckles_Sonic3 = "VO_Sonic3/Knuckles.wav";
			const char* KnuxWins_Sonic3 = "VO_Sonic3/KnuxWins.wav";
			const char* Mighty_Sonic3 = "VO_Sonic3/Mighty.wav";
			const char* MightyWins_Sonic3 = "VO_Sonic3/MightyWins.wav";
			const char* Ray_Sonic3 = "VO_Sonic3/Ray.wav";
			const char* RayWins_Sonic3 = "VO_Sonic3/RayWins.wav";

			const char* TheWinnerIs_Sonic3 = "VO_Sonic3/TheWinnerIs.wav";

			const char* ItsADraw_Sonic3 = "VO_Sonic3/ItsADraw.wav";
			const char* ItsADraw_Set_Sonic3 = "VO_Sonic3/ItsADraw_Set.wav";

			const char* NewRecordMid_Sonic3 = "VO_Sonic3/NewRecordMid.wav";
			const char* NewRecordTop_Sonic3 = "VO_Sonic3/NewRecordTop.wav";

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

	void LogInfo(const char* name, const char* text, ...)
	{
		if (!ConsoleEnabled)
			return;
		char buffer[512];
		va_list ap;
		va_start(ap, text);
		_vsprintf_p(buffer, 512, text, ap);
		va_end(ap);
		printf("[INFO]  [%s] %s\n", name, buffer);
	}

	inline void SwapSound(int* Path, char* String)
	{
		LogInfo("CompPlus_Announcers::SwapSound", "Swaping SoundFX: %s", String);
		*Path = (int)(&String[0]);
	}

	inline void LoadSoundFX_Debug(const char* path, SonicMania::Scope scope) 
	{
		LogInfo("CompPlus_Announcers::LoadSoundFX", "Loading SoundFX: %s", path);
		LoadSoundFX(path, scope);
	}

	inline void ChangeAnnouncer() 
	{
		if (CompPlusSettings::CurrentAnnouncer == CompPlusSettings::Announcer_Garrulous64)
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
		else if (CompPlusSettings::CurrentAnnouncer == CompPlusSettings::Announcer_Angelthegamer)
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
		else if (CompPlusSettings::CurrentAnnouncer == CompPlusSettings::Announcer_Memes)
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
		else if (CompPlusSettings::CurrentAnnouncer == CompPlusSettings::Announcer_Daniel)
		{
			SwapSound(Player1_MemoryAdd, (char*)Player1_DanielUK);
			SwapSound(Player2_MemoryAdd, (char*)Player2_DanielUK);
			SwapSound(Player3_MemoryAdd, (char*)Player3_DanielUK);
			SwapSound(Player4_MemoryAdd, (char*)Player4_DanielUK);

			SwapSound(SonicWins_MemoryAdd, (char*)SonicWins_DanielUK);
			SwapSound(TailsWins_MemoryAdd, (char*)TailsWins_DanielUK);
			SwapSound(KnuxWins_MemoryAdd, (char*)KnuxWins_DanielUK);
			SwapSound(MightyWins_MemoryAdd, (char*)MightyWins_DanielUK);
			SwapSound(RayWins_MemoryAdd, (char*)RayWins_DanielUK);

			SwapSound(ItsADraw_MemoryAdd, (char*)ItsADraw_DanielUK);
			SwapSound(ItsADraw_Set_MemoryAdd, (char*)ItsADraw_Set_DanielUK);

			SwapSound(Three_MemoryAdd, (char*)Three_DanielUK);
			SwapSound(Two_MemoryAdd, (char*)Two_DanielUK);
			SwapSound(One_MemoryAdd, (char*)One_DanielUK);
			SwapSound(Go_MemoryAdd, (char*)Go_DanielUK);

			SwapSound(Sonic_MemoryAdd, (char*)Sonic_DanielUK);
			SwapSound(Tails_MemoryAdd, (char*)Tails_DanielUK);
			SwapSound(Knuckles_MemoryAdd, (char*)Knuckles_DanielUK);
			SwapSound(Mighty_MemoryAdd, (char*)Mighty_DanielUK);
			SwapSound(Ray_MemoryAdd, (char*)Ray_DanielUK);

			SwapSound(Goal_MemoryAdd, (char*)Goal_DanielUK);
			SwapSound(Goal_MemoryAdd_2, (char*)Goal_DanielUK);

			SwapSound(TheWinnerIs_MemoryAdd, (char*)TheWinnerIs_DanielUK);

			SwapSound(NewRecordMid_MemoryAdd, (char*)NewRecordMid_DanielUK);
			SwapSound(NewRecordTop_MemoryAdd, (char*)NewRecordTop_DanielUK);
		}
		else if (CompPlusSettings::CurrentAnnouncer == CompPlusSettings::Announcer_Sonic2)
		{
			SwapSound(Player1_MemoryAdd, (char*)Player1_Sonic3);
			SwapSound(Player2_MemoryAdd, (char*)Player2_Sonic3);
			SwapSound(Player3_MemoryAdd, (char*)Player3_Sonic3);
			SwapSound(Player4_MemoryAdd, (char*)Player4_Sonic3);

			SwapSound(SonicWins_MemoryAdd, (char*)SonicWins_Sonic3);
			SwapSound(TailsWins_MemoryAdd, (char*)TailsWins_Sonic3);
			SwapSound(KnuxWins_MemoryAdd, (char*)KnuxWins_Sonic3);
			SwapSound(MightyWins_MemoryAdd, (char*)MightyWins_Sonic3);
			SwapSound(RayWins_MemoryAdd, (char*)RayWins_Sonic3);

			SwapSound(ItsADraw_MemoryAdd, (char*)ItsADraw_Sonic3);
			SwapSound(ItsADraw_Set_MemoryAdd, (char*)ItsADraw_Set_Sonic3);

			SwapSound(Three_MemoryAdd, (char*)Three_Sonic3);
			SwapSound(Two_MemoryAdd, (char*)Two_Sonic3);
			SwapSound(One_MemoryAdd, (char*)One_Sonic3);
			SwapSound(Go_MemoryAdd, (char*)Go_Sonic3);

			SwapSound(Sonic_MemoryAdd, (char*)Sonic_Sonic3);
			SwapSound(Tails_MemoryAdd, (char*)Tails_Sonic3);
			SwapSound(Knuckles_MemoryAdd, (char*)Knuckles_Sonic3);
			SwapSound(Mighty_MemoryAdd, (char*)Mighty_Sonic3);
			SwapSound(Ray_MemoryAdd, (char*)Ray_Sonic3);

			SwapSound(Goal_MemoryAdd, (char*)Goal_Sonic3);
			SwapSound(Goal_MemoryAdd_2, (char*)Goal_Sonic3);

			SwapSound(TheWinnerIs_MemoryAdd, (char*)TheWinnerIs_Sonic3);

			SwapSound(NewRecordMid_MemoryAdd, (char*)NewRecordMid_Sonic3);
			SwapSound(NewRecordTop_MemoryAdd, (char*)NewRecordTop_Sonic3);
		}
		else
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

	inline void LoadAnnouncerFX()
	{
		if (!HasAnnouncersLoaded)
		{
			SetWriteProtection();

			if (CompPlusSettings::CurrentAnnouncer == CompPlusSettings::Announcer_Garrulous64)
			{
				LoadSoundFX_Debug(Player1_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(Player2_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(Player3_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(Player4_Garrulous64, Scope_Global);

				LoadSoundFX_Debug(Three_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(Two_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(One_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(Go_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(Goal_Garrulous64, Scope_Global);

				LoadSoundFX_Debug(Sonic_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(SonicWins_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(Tails_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(TailsWins_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(Knuckles_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(KnuxWins_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(Mighty_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(MightyWins_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(Ray_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(RayWins_Garrulous64, Scope_Global);

				LoadSoundFX_Debug(TheWinnerIs_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(ItsADraw_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(ItsADraw_Set_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(NewRecordMid_Garrulous64, Scope_Global);
				LoadSoundFX_Debug(NewRecordTop_Garrulous64, Scope_Global);
			}
			else if (CompPlusSettings::CurrentAnnouncer == CompPlusSettings::Announcer_Angelthegamer)
			{
				LoadSoundFX_Debug(Player1_ATG, Scope_Global);
				LoadSoundFX_Debug(Player2_ATG, Scope_Global);
				LoadSoundFX_Debug(Player3_ATG, Scope_Global);
				LoadSoundFX_Debug(Player4_ATG, Scope_Global);

				LoadSoundFX_Debug(Three_ATG, Scope_Global);
				LoadSoundFX_Debug(Two_ATG, Scope_Global);
				LoadSoundFX_Debug(One_ATG, Scope_Global);
				LoadSoundFX_Debug(Go_ATG, Scope_Global);
				LoadSoundFX_Debug(Goal_ATG, Scope_Global);

				LoadSoundFX_Debug(Sonic_ATG, Scope_Global);
				LoadSoundFX_Debug(SonicWins_ATG, Scope_Global);
				LoadSoundFX_Debug(Tails_ATG, Scope_Global);
				LoadSoundFX_Debug(TailsWins_ATG, Scope_Global);
				LoadSoundFX_Debug(Knuckles_ATG, Scope_Global);
				LoadSoundFX_Debug(KnuxWins_ATG, Scope_Global);
				LoadSoundFX_Debug(Mighty_ATG, Scope_Global);
				LoadSoundFX_Debug(MightyWins_ATG, Scope_Global);
				LoadSoundFX_Debug(Ray_ATG, Scope_Global);
				LoadSoundFX_Debug(RayWins_ATG, Scope_Global);

				LoadSoundFX_Debug(TheWinnerIs_ATG, Scope_Global);
				LoadSoundFX_Debug(ItsADraw_ATG, Scope_Global);
				LoadSoundFX_Debug(ItsADraw_Set_ATG, Scope_Global);
				LoadSoundFX_Debug(NewRecordMid_ATG, Scope_Global);
				LoadSoundFX_Debug(NewRecordTop_ATG, Scope_Global);
			}
			else if (CompPlusSettings::CurrentAnnouncer == CompPlusSettings::Announcer_Memes)
			{
				LoadSoundFX_Debug(Player1_Memes, Scope_Global);
				LoadSoundFX_Debug(Player2_Memes, Scope_Global);
				LoadSoundFX_Debug(Player3_Memes, Scope_Global);
				LoadSoundFX_Debug(Player4_Memes, Scope_Global);

				LoadSoundFX_Debug(Three_Memes, Scope_Global);
				LoadSoundFX_Debug(Two_Memes, Scope_Global);
				LoadSoundFX_Debug(One_Memes, Scope_Global);
				LoadSoundFX_Debug(Go_Memes, Scope_Global);
				LoadSoundFX_Debug(Goal_Memes, Scope_Global);

				LoadSoundFX_Debug(Sonic_Memes, Scope_Global);
				LoadSoundFX_Debug(SonicWins_Memes, Scope_Global);
				LoadSoundFX_Debug(Tails_Memes, Scope_Global);
				LoadSoundFX_Debug(TailsWins_Memes, Scope_Global);
				LoadSoundFX_Debug(Knuckles_Memes, Scope_Global);
				LoadSoundFX_Debug(KnuxWins_Memes, Scope_Global);
				LoadSoundFX_Debug(Mighty_Memes, Scope_Global);
				LoadSoundFX_Debug(MightyWins_Memes, Scope_Global);
				LoadSoundFX_Debug(Ray_Memes, Scope_Global);
				LoadSoundFX_Debug(RayWins_Memes, Scope_Global);

				LoadSoundFX_Debug(TheWinnerIs_Memes, Scope_Global);
				LoadSoundFX_Debug(ItsADraw_Memes, Scope_Global);
				LoadSoundFX_Debug(ItsADraw_Set_Memes, Scope_Global);
				LoadSoundFX_Debug(NewRecordMid_Memes, Scope_Global);
				LoadSoundFX_Debug(NewRecordTop_Memes, Scope_Global);
			}
			else if (CompPlusSettings::CurrentAnnouncer == CompPlusSettings::Announcer_Daniel)
			{
				LoadSoundFX_Debug(Player1_DanielUK, Scope_Global);
				LoadSoundFX_Debug(Player2_DanielUK, Scope_Global);
				LoadSoundFX_Debug(Player3_DanielUK, Scope_Global);
				LoadSoundFX_Debug(Player4_DanielUK, Scope_Global);

				LoadSoundFX_Debug(Three_DanielUK, Scope_Global);
				LoadSoundFX_Debug(Two_DanielUK, Scope_Global);
				LoadSoundFX_Debug(One_DanielUK, Scope_Global);
				LoadSoundFX_Debug(Go_DanielUK, Scope_Global);
				LoadSoundFX_Debug(Goal_DanielUK, Scope_Global);

				LoadSoundFX_Debug(Sonic_DanielUK, Scope_Global);
				LoadSoundFX_Debug(SonicWins_DanielUK, Scope_Global);
				LoadSoundFX_Debug(Tails_DanielUK, Scope_Global);
				LoadSoundFX_Debug(TailsWins_DanielUK, Scope_Global);
				LoadSoundFX_Debug(Knuckles_DanielUK, Scope_Global);
				LoadSoundFX_Debug(KnuxWins_DanielUK, Scope_Global);
				LoadSoundFX_Debug(Mighty_DanielUK, Scope_Global);
				LoadSoundFX_Debug(MightyWins_DanielUK, Scope_Global);
				LoadSoundFX_Debug(Ray_DanielUK, Scope_Global);
				LoadSoundFX_Debug(RayWins_DanielUK, Scope_Global);

				LoadSoundFX_Debug(TheWinnerIs_DanielUK, Scope_Global);
				LoadSoundFX_Debug(ItsADraw_DanielUK, Scope_Global);
				LoadSoundFX_Debug(ItsADraw_Set_DanielUK, Scope_Global);
				LoadSoundFX_Debug(NewRecordMid_DanielUK, Scope_Global);
				LoadSoundFX_Debug(NewRecordTop_DanielUK, Scope_Global);
			}
			else if (CompPlusSettings::CurrentAnnouncer == CompPlusSettings::Announcer_Sonic2)
			{
				LoadSoundFX_Debug(Player1_Sonic3, Scope_Global);
				LoadSoundFX_Debug(Player2_Sonic3, Scope_Global);
				LoadSoundFX_Debug(Player3_Sonic3, Scope_Global);
				LoadSoundFX_Debug(Player4_Sonic3, Scope_Global);

				LoadSoundFX_Debug(Three_Sonic3, Scope_Global);
				LoadSoundFX_Debug(Two_Sonic3, Scope_Global);
				LoadSoundFX_Debug(One_Sonic3, Scope_Global);
				LoadSoundFX_Debug(Go_Sonic3, Scope_Global);
				LoadSoundFX_Debug(Goal_Sonic3, Scope_Global);

				LoadSoundFX_Debug(Sonic_Sonic3, Scope_Global);
				LoadSoundFX_Debug(SonicWins_Sonic3, Scope_Global);
				LoadSoundFX_Debug(Tails_Sonic3, Scope_Global);
				LoadSoundFX_Debug(TailsWins_Sonic3, Scope_Global);
				LoadSoundFX_Debug(Knuckles_Sonic3, Scope_Global);
				LoadSoundFX_Debug(KnuxWins_Sonic3, Scope_Global);
				LoadSoundFX_Debug(Mighty_Sonic3, Scope_Global);
				LoadSoundFX_Debug(MightyWins_Sonic3, Scope_Global);
				LoadSoundFX_Debug(Ray_Sonic3, Scope_Global);
				LoadSoundFX_Debug(RayWins_Sonic3, Scope_Global);

				LoadSoundFX_Debug(TheWinnerIs_Sonic3, Scope_Global);
				LoadSoundFX_Debug(ItsADraw_Sonic3, Scope_Global);
				LoadSoundFX_Debug(ItsADraw_Set_Sonic3, Scope_Global);
				LoadSoundFX_Debug(NewRecordMid_Sonic3, Scope_Global);
				LoadSoundFX_Debug(NewRecordTop_Sonic3, Scope_Global);

			}

			CompPlus_Announcers::ChangeAnnouncer();

			HasAnnouncersLoaded = true;
		}
	}
}