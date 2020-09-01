#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include <string>
#include <sstream>

// Functions
extern intptr_t GetAddressFromJump(intptr_t jmp);
extern int LoadFile(char* filename, fileinfo* info, void* unknown);
extern void* LoadAndReadFile(const char* filename, int* length);
extern int ReadBytesFromFile(fileinfo* file, void* buffer, int bytes);
extern int DecryptBytes(fileinfo* file, void* buffer, int bufferSize);
extern void ReplaceString(std::string& str, std::string& from, std::string& to);
extern void LogDebug(const char* name, const char* text, ...);
extern void LogError(const char* name, const char* text, ...);
extern void LogWarn(const char* name, const char* text, ...);
extern void LogInfo(const char* name, const char* text, ...);
extern std::string IntToString(int a);

inline BOOL ReplaceJNEwithJump(void* writeaddress, void* funcaddress)
{
    uint8_t data[6];
    data[0] = 0xE9; // JMP DWORD (relative)
    *(int32_t*)(data + 1) = (uint32_t)funcaddress - ((uint32_t)writeaddress + 5);
    data[6] = 0x90;
    return WriteData(writeaddress, data);
}
