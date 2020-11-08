#include "stdafx.h"
#include <string>
#include <algorithm>
#include <vector>
#include <chrono>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <ManiaModLoader.h>
#include "include/Trampoline.h"
#include "include/ManiaAPI/SonicMania.h"

namespace NextGeneration_ManiaAPI
{
    #pragma region Defines

    using namespace SonicMania;
    using namespace std;
    using namespace std::chrono;
    using namespace std::chrono_literals;

    #define DataTruePointer(type, name, address) \ static type* name = (type *)(baseAddress + address)
    #define EXPORT __declspec(dllexport)
    #define DefineDLLFunc(name, ARGS) int(__cdecl *name)ARGS;
    #define LoadDLLFunc(name) name = (decltype(name))GetProcAddress(ChatVS_DLL, #name);
    //#define RegistryObjectCount *(Uint16*)(baseAddress + 0x83D56C - 0x400000)

    typedef signed char Sint8;
    typedef unsigned char Uint8;
    typedef signed short Sint16;
    typedef unsigned short Uint16;
    typedef signed int Sint32;
    typedef unsigned int Uint32;
    typedef void* VoidPtr;

    #pragma endregion

    #pragma region Structures

    struct Hash 
    {
        Uint32 A;
        Uint32 B;
        Uint32 C;
        Uint32 D;
    };
    struct AnimationFrame 
    {
        Sint16 X;
        Sint16 Y;
        Sint16 Width;
        Sint16 Height;
        Sint16 OffX;
        Sint16 OffY;
        Uint16 Duration;
        Uint16 Unk_Duration;
        Sint8  ImageIndex;
        Uint8  Unk_0x11;
        Uint8  Unk_0x12;
        Uint8  Unk_0x13;
        Uint16 Unk_0x14;
        Uint16 Unk_0x16;
        Uint16 Unks[29];
    };
    struct AnimationEntry 
    {
        Hash Hash;
        Sint32 FirstFrameIndex;
        Uint16 FrameCount;
        Uint16 AnimationSpeed;
        Uint8 FrameToLoop;
        Uint8 RotationFlag;
        Uint8 Padding_0x1A[2];
    };
    struct ResourceAnimation 
    {
        Hash Hash;
        AnimationFrame* Frames;
        AnimationEntry* Entries;
        Uint8 EntryCount;
        Uint8 Scope;
        Uint8 Padding_0x1A[2];
    };
    struct ResourceImage 
    {
        Hash Hash;
        Uint8 *Data;
        Uint32 Width;
        Uint32 Height;
        Uint32 WidthInBits;
        Uint32 HeightInBits;
        Uint8  Scope;
        Uint8  Padding_0x25[3];
    };
    struct AnimationData 
    {
        AnimationFrame* FramePtr;
        Uint32 FrameIndex;
        Uint16 AnimationIndex;
        Uint16 PrevAnimationIndex;
        Uint16 AnimationSpeed;
        Uint16 PrevFrameIndex;
        Uint16 FrameDuration;
        Uint16 FrameCount;
        Uint8 FrameToLoop;
        Uint8 RotationFlag;
        Uint8 Padding_0x16[2];
    };
    struct RegistryObject_Item
    {
        Uint32 HashA;
        Uint32 HashB;
        Uint32 HashC;
        Uint32 HashD;
        Uint32 Unk_0x10;
        Uint32 Unk_0x14;
        Uint32 Unk_0x18;
        Uint32 Unk_0x1C;
        Uint32 Unk_0x20;
        Uint32 LoadFunc;
        Uint32 Unk_0x28;
        Uint32 Unk_0x2C;
        Uint32 PropertyFunc;
        short** ObjectTypeInfo;
        Uint32 ObjectMemSize;
        Uint32 ObjectTypeInfoSize;
    };

    ResourceAnimation* ResourceAnimationListStart = NULL;
    ResourceAnimation* ResourceAnimationListEnd = NULL;
    ResourceImage* ResourceImageListStart = NULL;
    ResourceImage* ResourceImageListEnd = NULL;

    #pragma endregion

    #pragma region Internal Stuff
    static void ChatVS_Print(int sev, const char* format, ...) 
    {
        char string[1024];

        va_list args;
        va_start(args, format);
        vsnprintf(string, 1024, format, args);

        int ColorCode = 0x07;
        switch (sev) 
        {
            case -1: ColorCode = 0x0D; break;
            case  0: ColorCode = 0x08; break;
            case  1: ColorCode = 0x0E; break;
            case  2: ColorCode = 0x0C; break;
            case  3: ColorCode = 0x0B; break;
        }

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) 
        {
            SetConsoleTextAttribute(hStdOut, (csbi.wAttributes & 0xF0) | ColorCode);
        }

        printf("[SpriteLoading] ");

        SetConsoleTextAttribute(hStdOut, (csbi.wAttributes & 0xF0) | 0x07);

        printf(string);
    }
    int(__cdecl*PlayMusicFile_BASS)(const char*, unsigned int, int, unsigned int, int) = NULL;
    int(__thiscall*LinkGameLogic)(int*) = NULL;

	// Should be in SonicMania.h
	void MD5_Hasher(const char* string, Uint32* HashA, Uint32* HashB, Uint32* HashC, Uint32* HashD) 
    {
        #define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

		Uint32 r[] = {
            7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
			5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
			4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
			6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
        };
		Uint32 k[] = {
			0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
			0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
			0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
			0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
			0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
			0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
			0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
			0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
			0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
			0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
			0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
			0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
			0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
			0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
			0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
			0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
        };
		Uint8* msg = NULL;
		size_t initial_len = strlen(string);

		*HashA = 0x67452301;
		*HashB = 0xEFCDAB89;
		*HashC = 0x98BADCFE;
		*HashD = 0x10325476;

		int new_len = ((((initial_len + 8) >> 6) + 1) << 6) - 8;

		msg = (Uint8*)calloc(new_len + 64, 1);
		memcpy(msg, string, initial_len);
		msg[initial_len] = 128;

		Uint32 bits_len = 8 * initial_len;
		memcpy(msg + new_len, &bits_len, 4);

		int offset;
		for (offset = 0; offset < new_len; offset += (512 >> 3)) {
			// Break chunk into sixteen 32-bit words w[j], 0 = j = 15
			Uint32* w = (Uint32*)(msg + offset);

			// Initialize hash value for this chunk:
			Uint32 a = *HashA;
			Uint32 b = *HashB;
			Uint32 c = *HashC;
			Uint32 d = *HashD;

			// Main loop:
			Uint32 i;
			for (i = 0; i < 64; i++) {
				Uint32 f, g;

				if (i < 16) {
					f = (b & c) | ((~b) & d);
					g = i;
				}
				else if (i < 32) {
					f = (d & b) | ((~d) & c);
					g = (5 * i + 1) % 16;
				}
				else if (i < 48) {
					f = b ^ c ^ d;
					g = (3 * i + 5) % 16;
				}
				else {
					f = c ^ (b | (~d));
					g = (7 * i) % 16;
				}

				Uint32 temp = d;
				d = c;
				c = b;
				// printf("rotateLeft(%x + %x + %x + %x, %d)\n", a, f, k[i], w[g], r[i]);
				b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
				a = temp;
			}

			// Add this chunk's hash to result so far:
			*HashA += a;
			*HashB += b;
			*HashC += c;
			*HashD += d;
		}

		// Cleanup
		free(msg);

        #undef LEFTROTATE
	}
	RegistryObject_Item* FindRegistryObjectItem(const char* string) {
		Uint16* RegistryObject_ListCount;
		RegistryObject_Item* RegistryObject_List;

		RegistryObject_ListCount = (Uint16*)(baseAddress + 0x83D56C - 0x400000);
		RegistryObject_List = (RegistryObject_Item*)(baseAddress + 0xE78F68 - 0x400000);

		Uint32 hashA, hashB, hashC, hashD;
		MD5_Hasher(string, &hashA, &hashB, &hashC, &hashD);

		for (int i = 0; i < *RegistryObject_ListCount; i++) {
			RegistryObject_Item* item = &RegistryObject_List[i];
			if (item->HashA == hashA && item->HashB == hashB && item->HashC == hashC && item->HashD == hashD)
				return item;
		}
		return NULL;
	}
	void DummyTypeObject(const char* string) {
		RegistryObject_Item* item = FindRegistryObjectItem(string);
		RegistryObject_Item* RegistryObject_List = (RegistryObject_Item*)(baseAddress + 0xE78F68 - 0x400000);
		if (!item) 
        {
			ChatVS_Print(2, "No item for %s!\n", string);
			return;
		}

		short** ah1 = item->ObjectTypeInfo;
		if (!*ah1)
			*ah1 = (short*)malloc(item->ObjectTypeInfoSize);

		(*ah1)[0] = 104;
	}
	void AddToGameConfigObjects(const char* string) {
		RegistryObject_Item* item = FindRegistryObjectItem(string);
		RegistryObject_Item* RegistryObject_List = (RegistryObject_Item*)(baseAddress + 0xE78F68 - 0x400000);
		if (!item) {
			ChatVS_Print(2, "No item for %s!\n", string);
			return;
		}

		int index = item - RegistryObject_List;

		Uint16* GlobalObjectList;
		Uint16* GlobalObjectCount;
		GlobalObjectList = (Uint16*)(baseAddress + 0xAEC810 - 0x400000);
		GlobalObjectCount = (Uint16*)(baseAddress + 0x869A0C - 0x400000);

		// printf("index: %d\n", index);

		bool isIn = false;
		for (int i = 0; i < *GlobalObjectCount; i++) {
			if (GlobalObjectList[i] == index) {
				isIn = true;
				break;
			}
		}
		if (!isIn) {
			ChatVS_Print(0, "Adding \"%s\" (%d) at index %d.\n", string, index, *GlobalObjectCount);
			GlobalObjectList[(*GlobalObjectCount)++] = index;
		}
	}
    static void* GetAddressFromJump(int jmp) {
        int r = *(int*)(jmp + 1);
        int abs = jmp + r + 5;
        return (void*)abs;
    }

    #pragma endregion

    #pragma region Helper Functions

	int RuntimePointerToIDA(int ptr) 
    {
		return ptr - baseAddress + 0x400000;
	}
	int IDAToRuntimePointer(int ptr) 
    {
		return baseAddress + ptr - 0x400000;
	}
    int RuntimePointer270000(int ptr) 
    {
		return ptr - 0x270000 + baseAddress;
	}
    int WriteDataInt(void* writeaddress, const void* data) 
    {
		DWORD Controls;
		VirtualProtect((void*)((int)writeaddress - 0x10), 0x40, PAGE_EXECUTE_READWRITE, &Controls);
		// ChatVS_Print(3, "writeaddress 0x%X (value: 0x%X, writing: 0x%X)\n", (int)writeaddress - baseAddress, *(int*)writeaddress, (int)data);
		return WriteProcessMemory(curproc, writeaddress, &data, 4, NULL);
    }
    void InterceptFunction(void** gameFunc, void* interceptFunc, void** backup) 
    {
        *backup = *gameFunc;
        *gameFunc = interceptFunc;
    }
	void InterceptJump(void** instructionAddr, void* interceptFunc, void** backup) 
    {
		int instructionOp_Ptr = (int)instructionAddr + 1;
		int instructionEnd_Ptr = (int)instructionAddr + 5;
		*backup = (void**)(instructionEnd_Ptr + *(int*)instructionOp_Ptr);
		*(int*)instructionOp_Ptr = (int)interceptFunc - instructionEnd_Ptr;
		// *(int*)instructionOp_Ptr = RuntimePointer270000(0x42D550) - instructionEnd_Ptr;
		// *(int*)instructionOp_Ptr = *(int*)instructionOp_Ptr;

		printf("jump instruction | op: %p value: %X \n", (int*)instructionOp_Ptr, *(int*)instructionOp_Ptr);
		printf("og: %p | dist: %X | backup: %p\n", RuntimePointer270000(0x42D550), RuntimePointer270000(0x42D550) - instructionEnd_Ptr, *backup);
		printf("interceptFunc: %p | distance from operand value: %X \n\n\n", interceptFunc, (int)interceptFunc - instructionEnd_Ptr);
		printf("dword_CE8C98: %X", *(int*)RuntimePointer270000(0xCE8C98));
	}

    #pragma endregion

    #pragma region Patching, Intercepts, and Detours

    // Patches: Function
    // Intercepts: Functions that replace a function pointer with intercept function
    // Detours: Patches a specific function call towards detour function

	void   (*SetupFunctionsPtr)();
    int    (*FindNextObjectPtr)(Uint16 objectID, Entity** entity);
    Sint16 (*RSDK_LoadImagePtr)(const char *filename, int unloadType);
    Sint16 (*RSDK_LoadAnimationPtr)(const char *filename, int unloadType);

	void ResourceImageList_PATCHES() 
    {
		DWORD OutD1;
		DWORD OutD2;

		// Patch EVERY single reference of the image resource list
		WriteDataInt((void*)RuntimePointer270000(0x444C26 + 3), &ResourceImageListStart[0].Hash.A);
		WriteDataInt((void*)RuntimePointer270000(0x444F17 + 4), &ResourceImageListStart[0].Hash.A);
		WriteDataInt((void*)RuntimePointer270000(0x271135 + 1), &ResourceImageListStart[0].Hash.C);
		WriteDataInt((void*)RuntimePointer270000(0x444DD7 + 1), &ResourceImageListStart[0].Hash.C);
		WriteDataInt((void*)RuntimePointer270000(0x444C4B + 2), &ResourceImageListStart[0].Data);
		WriteDataInt((void*)RuntimePointer270000(0x444F38 + 3), &ResourceImageListStart[0].Data);
		WriteDataInt((void*)RuntimePointer270000(0x445BF2 + 3), &ResourceImageListStart[0].Data);
		WriteDataInt((void*)RuntimePointer270000(0x446162 + 3), &ResourceImageListStart[0].Data);
		WriteDataInt((void*)RuntimePointer270000(0x4466DC + 3), &ResourceImageListStart[0].Data);
		WriteDataInt((void*)RuntimePointer270000(0x446C5C + 3), &ResourceImageListStart[0].Data);
		WriteDataInt((void*)RuntimePointer270000(0x447603 + 3), &ResourceImageListStart[0].Data);
		WriteDataInt((void*)RuntimePointer270000(0x448052 + 3), &ResourceImageListStart[0].Data);
		WriteDataInt((void*)RuntimePointer270000(0x44C535 + 2), &ResourceImageListStart[0].Data);
		WriteDataInt((void*)RuntimePointer270000(0x444C2D + 2), &ResourceImageListStart[0].Width);
		WriteDataInt((void*)RuntimePointer270000(0x444EFE + 3), &ResourceImageListStart[0].Width);
		WriteDataInt((void*)RuntimePointer270000(0x445BDC + 3), &ResourceImageListStart[0].Width);
		WriteDataInt((void*)RuntimePointer270000(0x44614E + 3), &ResourceImageListStart[0].Width);
		WriteDataInt((void*)RuntimePointer270000(0x4466C2 + 3), &ResourceImageListStart[0].Width);
		WriteDataInt((void*)RuntimePointer270000(0x446C3E + 3), &ResourceImageListStart[0].Width);
		WriteDataInt((void*)RuntimePointer270000(0x44808F + 3), &ResourceImageListStart[0].Width);
		WriteDataInt((void*)RuntimePointer270000(0x44C4F2 + 2), &ResourceImageListStart[0].Width);
		WriteDataInt((void*)RuntimePointer270000(0x444C37 + 2), &ResourceImageListStart[0].Height);
		WriteDataInt((void*)RuntimePointer270000(0x444F05 + 3), &ResourceImageListStart[0].Height);
		WriteDataInt((void*)RuntimePointer270000(0x44809A + 3), &ResourceImageListStart[0].Height);
		WriteDataInt((void*)RuntimePointer270000(0x444C41 + 2), &ResourceImageListStart[0].WidthInBits);
		WriteDataInt((void*)RuntimePointer270000(0x444F0C + 3), &ResourceImageListStart[0].WidthInBits);
		WriteDataInt((void*)RuntimePointer270000(0x444F2E + 3), &ResourceImageListStart[0].WidthInBits);
		WriteDataInt((void*)RuntimePointer270000(0x4475FC + 3), &ResourceImageListStart[0].WidthInBits);
		WriteDataInt((void*)RuntimePointer270000(0x4480A5 + 3), &ResourceImageListStart[0].WidthInBits);
		WriteDataInt((void*)RuntimePointer270000(0x44C53B + 2), &ResourceImageListStart[0].WidthInBits);
		WriteDataInt((void*)RuntimePointer270000(0x444C1F + 2), &ResourceImageListStart[0].Scope);
		WriteDataInt((void*)RuntimePointer270000(0x444E01 + 1), &ResourceImageListStart[0].Scope);
		WriteDataInt((void*)RuntimePointer270000(0x444EF7 + 3), &ResourceImageListStart[0].Scope);
		WriteDataInt((void*)RuntimePointer270000(0x45F2CC + 1), &ResourceImageListStart[0].Scope);

        //These were originally Indexed at 1
		WriteDataInt((void*)RuntimePointer270000(0x444C9A + 3), &ResourceImageListStart[0].Hash.A);
		WriteDataInt((void*)RuntimePointer270000(0x444CBF + 2), &ResourceImageListStart[0].Data);
		WriteDataInt((void*)RuntimePointer270000(0x444CA1 + 2), &ResourceImageListStart[0].Width);
		WriteDataInt((void*)RuntimePointer270000(0x444CAB + 2), &ResourceImageListStart[0].Height);
		WriteDataInt((void*)RuntimePointer270000(0x444CB5 + 2), &ResourceImageListStart[0].WidthInBits);
		WriteDataInt((void*)RuntimePointer270000(0x444C93 + 2), &ResourceImageListStart[0].Scope);

		// Some of these are the start of a different list
		// WriteDataInt((void*)RuntimePointer270000(0x44EE63 + 1), &ResourceImageListEnd[0].Hash.A);
		// WriteDataInt((void*)RuntimePointer270000(0x44EE87 + 2), &ResourceImageListEnd[0].Hash.A);
		// WriteDataInt((void*)RuntimePointer270000(0x44EEB7 + 2), &ResourceImageListEnd[0].Hash.A);
		// WriteDataInt((void*)RuntimePointer270000(0x44EEE7 + 2), &ResourceImageListEnd[0].Hash.A);
		// WriteDataInt((void*)RuntimePointer270000(0x44EF49 + 1), &ResourceImageListEnd[0].Hash.A);
		// WriteDataInt((void*)RuntimePointer270000(0x44F673 + 2), &ResourceImageListEnd[0].Hash.A);
		// WriteDataInt((void*)RuntimePointer270000(0x44FF2C + 2), &ResourceImageListEnd[0].Hash.A);
		// WriteDataInt((void*)RuntimePointer270000(0x2711B5 + 1), &ResourceImageListEnd[0].Hash.C);
        // WriteDataInt((void*)RuntimePointer270000(0x44ED12 + 1), &ResourceImageListEnd[0].Hash.C);
        // WriteDataInt((void*)RuntimePointer270000(0x44EDCD + 3), &ResourceImageListEnd[0].Hash.A);
        // WriteDataInt((void*)RuntimePointer270000(0x44EDDB + 2), &ResourceImageListEnd[0].Padding_0x25);
        // WriteDataInt((void*)RuntimePointer270000(0x44EDF8 + 2), &ResourceImageListEnd[0].Width);
        // WriteDataInt((void*)RuntimePointer270000(0x44EE24 + 2), &ResourceImageListEnd[0].Height);
        // WriteDataInt((void*)RuntimePointer270000(0x44EE07 + 2), &ResourceImageListEnd[0].WidthInBits);.
        // WriteDataInt((void*)RuntimePointer270000(0x44EDC7 + 2), &ResourceImageListEnd[0].Data);
        // WriteDataInt((void*)RuntimePointer270000(0x44EDE5 + 2), &ResourceImageListEnd[0].Scope);

        // These are actually used
		WriteDataInt((void*)RuntimePointer270000(0x444DF8 + 1), &ResourceImageListEnd[0].Hash.C);
		WriteDataInt((void*)RuntimePointer270000(0x444E0F + 1), &ResourceImageListEnd[0].Scope);
		WriteDataInt((void*)RuntimePointer270000(0x45F2EC + 1), &ResourceImageListEnd[0].Scope);
	}
	void SetupFunctions_INTERCEPT() 
    {
		// IMPORTANT: This needs to be done before SetupFunctions is called
		bool customResourceImageList = true;

		// Hook resources
		ResourceAnimationListStart = (ResourceAnimation*)RuntimePointer270000(0xCC3C98);
		ResourceAnimationListEnd = (ResourceAnimation*)RuntimePointer270000(0xCF9968);

		// Hook resource images
		ResourceImageListStart = (ResourceImage*)RuntimePointer270000(0xCF8F68);
		ResourceImageListEnd = (ResourceImage*)RuntimePointer270000(0xCF9968);

		if (customResourceImageList) {
			// Make custom Image list, and patch it all over
			ResourceImageListStart = (ResourceImage*)calloc(0x400, sizeof(ResourceImage));
			ResourceImageListEnd = ResourceImageListStart + 0x400;

			DWORD Controls;
			VirtualProtect((void*)ResourceImageListStart, 0x400 * sizeof(ResourceImage), PAGE_EXECUTE_READWRITE, &Controls);

			memcpy(ResourceImageListStart, (ResourceImage*)RuntimePointer270000(0xCF8F68), sizeof(ResourceImage) * 64);
			ResourceImageList_PATCHES();

			ChatVS_Print(3, "baseAddress int: 0x%X\n", *(int*)(baseAddress + 0x1136));
			// ChatVS_Print(3, "ResourceImageListStart 0x%X\n", ResourceImageListStart);
			// for (int i = 0; i < 0x80; i++) {
			// 	ResourceImage* image = &((ResourceImage*)RuntimePointer270000(0xCF8F68))[i];
			// 	ChatVS_Print(0, "Image (Hash %X%X%X%X Data 0x%X W %d H %d WiB %d Scp %d)\n",
			// 		image->Hash.A, image->Hash.B, image->Hash.C, image->Hash.D,
			// 		image->Data, image->Width, image->Height, image->WidthInBits, image->Scope);
			// }
			// ChatVS_Print(3, "ResourceImageListEnd 0x%X\n", ResourceImageListEnd);
		}
	}
	int FindNextObject_INTERCEPT(Uint16 objectID, Entity** entity) 
    {
		if (objectID == 0)
			return 0;

		return FindNextObjectPtr(objectID, entity);
	}
    Sint16 RSDK_LoadImage_INTERCEPT(const char *filename, int unloadType) 
    {
        ChatVS_Print(0, "starting load Image \"%s\" with unloadType %d\n", filename, unloadType);
        Sint16 index = RSDK_LoadImagePtr(filename, unloadType);
		ChatVS_Print(index < 0 ? 2 : index >= 64 ? 1 : 0, "Loaded Image \"%s\" at index %d\n", filename, index);
		if (index > -1) 
        {
			ResourceImage* image = &ResourceImageListStart[index];

            if (image->Data == 0)
            {
                ChatVS_Print(0, "Couldn't Load Image \"%s\" with unloadType %d. Culling.\n", filename, unloadType);
                image->Data = (Uint8*)calloc(1, image->Width * image->Height);
            }

            DWORD Controls;
            VirtualProtect((void*)image->Data, image->Width * image->Height, PAGE_EXECUTE_READWRITE, &Controls);

            ChatVS_Print(1, "Image (Hash %X%X%X%X Data 0x%X W %d H %d WiB %d Scp %d)\n",
                image->Hash.A, image->Hash.B, image->Hash.C, image->Hash.D,
                image->Data, image->Width, image->Height, image->WidthInBits, image->Scope);
        }
        return index;
    }
    Sint16 RSDK_LoadAnimation_INTERCEPT(const char *filename, int unloadType) 
    {
        Sint16 index = RSDK_LoadAnimationPtr(filename, unloadType);

        if (index > -1) {
			if (ResourceAnimationListStart) {
				int maxImageIndex = 0;
				int minImageIndex = 0xFFFF;
				for (int e = 0; e < ResourceAnimationListStart[index].EntryCount; e++) {
					AnimationEntry* entry = ResourceAnimationListStart[index].Entries + e;
					for (int f = entry->FirstFrameIndex; f < entry->FirstFrameIndex + entry->FrameCount; f++) {
						AnimationFrame* frame = ResourceAnimationListStart[index].Frames + e;
						if (maxImageIndex < frame->ImageIndex)
							maxImageIndex = frame->ImageIndex;
						if (minImageIndex > frame->ImageIndex)
							minImageIndex = frame->ImageIndex;
					}
				}
				ChatVS_Print(3, "Loaded Animation \"%s\" at index %d\n", filename, index);
			}
			else {
				//ChatVS_Print(3, "Loaded Animation \"%s\" at index %d\n", filename, index);
			}
        }
		else {
			//ChatVS_Print(3, "Loaded Animation \"%s\" at index %d\n", filename, index);
		}

        return index;
    }
	int LinkGameLogic_PATCH(int v1) 
    {
		SetupFunctions_INTERCEPT();

		int ret = LinkGameLogic(&v1);

		ChatVS_Print(3, "baseAddress: 0x%X\n", baseAddress);

        // Intercept functions
        InterceptFunction((void**)IDAToRuntimePointer(0xEA773C), FindNextObject_INTERCEPT, (void**)&FindNextObjectPtr);
        InterceptFunction((void**)RuntimePointer270000(0xD178E8), RSDK_LoadAnimation_INTERCEPT, (void**)&RSDK_LoadAnimationPtr);

        InterceptFunction((void**)RuntimePointer270000(0xD17860), RSDK_LoadImage_INTERCEPT, (void**)&RSDK_LoadImagePtr);
        int data = ((int)(void*)&RSDK_LoadImage_INTERCEPT - RuntimePointer270000(0x4224A3 + 5));
		ChatVS_Print(3, "data: 0x%X\n", data);
        WriteDataInt((void*)RuntimePointer270000(0x4224A3 + 1), (void*)data);

        // Turn off game console logging
        *(Uint8*)RuntimePointer270000(0x4DBB1B) = 0;
        // 0x4DBB1B

        /*
		const char* PatchedGlobalObjects[] = {
			// Spikeball
			"BuckwildBall",
            "Drillerdroid",

			// Bumper
			"CircleBumper",

			// DeepFreeze
			"HeavyShinobi",
			"Ice",
		};
		// Spike ball
		DummyTypeObject("Iwamodoki");
		DummyTypeObject("Fireworm");
		DummyTypeObject("Toxomister");

		size_t totalMemSize = 0;
		size_t totalInfoSize = 0;
		for (int i = 0; i < sizeof(PatchedGlobalObjects) / sizeof(*PatchedGlobalObjects) && false; i++) {
            if (PatchedGlobalObjects[i] == NULL)
                continue;

			if (RegistryObject_Item* item = FindRegistryObjectItem(PatchedGlobalObjects[i])) {
				totalMemSize += item->ObjectMemSize;
				totalInfoSize += item->ObjectTypeInfoSize;
			}
			AddToGameConfigObjects(PatchedGlobalObjects[i]);
		}
		size_t maxMemSize = 0x800;
		size_t maxInfoSize = 0x292;
		ChatVS_Print(totalMemSize > maxMemSize ? 2 : 3, "Total Added Object Size: 0x%X / 0x%X\n", totalMemSize, maxMemSize);
		ChatVS_Print(totalInfoSize > maxInfoSize ? 2 : 3, "Total Added Info Size: 0x%X / 0x%X\n", totalInfoSize, maxInfoSize);
        */
		return ret;
	}

    #pragma endregion

    void Init() 
    {
        LinkGameLogic = (int(__thiscall*)(int*))IDAToRuntimePointer(0x5A6E20);
        WriteCall((void*)IDAToRuntimePointer(0x5D3045), LinkGameLogic_PATCH);
    }
}
