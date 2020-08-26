#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"

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
