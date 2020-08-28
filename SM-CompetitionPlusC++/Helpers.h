#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include <string>
#include <sstream>

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

inline BOOL ReplaceJNEwithJump(void* writeaddress, void* funcaddress)
{
    uint8_t data[6];
    data[0] = 0xE9; // JMP DWORD (relative)
    *(int32_t*)(data + 1) = (uint32_t)funcaddress - ((uint32_t)writeaddress + 5);
    data[6] = 0x90;
    return WriteData(writeaddress, data);
}

std::string IntToString(int a)
{
    std::stringstream temp;
    temp << a;
    return temp.str();
}
