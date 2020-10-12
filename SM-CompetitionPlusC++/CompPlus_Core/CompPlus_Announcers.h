#pragma once
#include "SonicMania.h"
#include "CompPlus_Settings.h"

namespace CompPlus_Announcers
{
    extern bool ReloadRequired;

    extern void PlayAnnouncerChangeFX(CompPlus_Settings::AnnouncerType Selection);

    extern void LoadAnnouncerFX();

    extern void ReloadAnnouncerFX();

    extern void ChangeAnnouncer();
}