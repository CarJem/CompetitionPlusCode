#pragma once
#include <string>
namespace CompPlus_MetrotropicBeach
{
    extern void Restart();

    extern void OnFrame(int ActID);

    extern void Init(std::string modPath);
}