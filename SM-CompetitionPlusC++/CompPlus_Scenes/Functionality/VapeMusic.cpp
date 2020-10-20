#include "VapeMusic.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/ManiaExt.h"

#include "SonicMania.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "CompPlus_Extensions/Helpers.h"

#include "CompPlus_Core/CompPlus_Scoring.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Status.h"

namespace CompPlus_VapeMusic
{     
    // UNUSED:
    // AIZ - "EAngelIsland2.ogg"
    // SSZ2 METAL - "EMetalSonic.ogg"
    // MSZ1 (ST) - "EMirageSaloon1.ogg"
    const char* Music_GHZ1E = "SMCP_Vape/EGreenHill1.ogg";
    const char* Music_GHZ2E = "SMCP_Vape/EGreenHill2.ogg";
    const char* Music_CPZ1E = "SMCP_Vape/EChemicalPlant1.ogg";
    const char* Music_CPZ2E = "SMCP_Vape/EChemicalPlant2.ogg";
    const char* Music_SPZ1E = "SMCP_Vape/EStudiopolis1.ogg";
    const char* Music_SPZ2E = "SMCP_Vape/EStudiopolis2.ogg";
    const char* Music_FBZ1E = "SMCP_Vape/EFlyingBattery1.ogg";
    const char* Music_FBZ2E = "SMCP_Vape/EFlyingBattery2.ogg";
    const char* Music_PGZ1E = "SMCP_Vape/EPulpSolstice1.ogg";
    const char* Music_PGZ2E = "SMCP_Vape/EPulpSolstice2.ogg";
    const char* Music_SSZ1E = "SMCP_Vape/EStardustSpeedway1.ogg";
    const char* Music_SSZ2E = "SMCP_Vape/EStardustSpeedway2.ogg";
    const char* Music_HCZ1E = "SMCP_Vape/EHydrocity1.ogg";
    const char* Music_HCZ2E = "SMCP_Vape/EHydrocity2.ogg";
    const char* Music_MSZ1E = "SMCP_Vape/EMirageSaloon1K.ogg";
    const char* Music_MSZ2E = "SMCP_Vape/EMirageSaloon2.ogg";
    const char* Music_OOZ1E = "SMCP_Vape/EOilOcean1.ogg";
    const char* Music_OOZ2E = "SMCP_Vape/EOilOcean2.ogg";
    const char* Music_LRZ1E = "SMCP_Vape/ELavaReef1.ogg";
    const char* Music_LRZ2E = "SMCP_Vape/ELavaReef2.ogg";
    const char* Music_MMZ1E = "SMCP_Vape/EMetallicMadness1.ogg";
    const char* Music_MMZ2E = "SMCP_Vape/EMetallicMadness2.ogg";
    const char* Music_TMZ1E = "SMCP_Vape/ETitanicMonarch1.ogg";
    const char* Music_TMZ2E = "SMCP_Vape/ETitanicMonarch2.ogg";

    const char* Music_GHZ1 = "GreenHill1.ogg";
    const char* Music_GHZ2 = "GreenHill2.ogg";
    const char* Music_CPZ1 = "ChemicalPlant1.ogg";
    const char* Music_CPZ2 = "ChemicalPlant2.ogg";
    const char* Music_SPZ1 = "Studiopolis1.ogg";
    const char* Music_SPZ2 = "Studiopolis2.ogg";
    const char* Music_FBZ1 = "FlyingBattery1.ogg";
    const char* Music_FBZ2 = "FlyingBattery2.ogg";
    const char* Music_PGZ1 = "PulpSolstice1.ogg";
    const char* Music_PGZ2 = "PulpSolstice2.ogg";
    const char* Music_SSZ1 = "StardustSpeedway1.ogg";
    const char* Music_SSZ2 = "StardustSpeedway2.ogg";
    const char* Music_HCZ1 = "Hydrocity1.ogg";
    const char* Music_HCZ2 = "Hydrocity2.ogg";
    const char* Music_MSZ1 = "MirageSaloon1K.ogg";
    const char* Music_MSZ2 = "MirageSaloon2.ogg";
    const char* Music_OOZ1 = "OilOcean1.ogg";
    const char* Music_OOZ2 = "OilOcean2.ogg";
    const char* Music_LRZ1 = "LavaReef1.ogg";
    const char* Music_LRZ2 = "LavaReef2.ogg";
    const char* Music_MMZ1 = "MetallicMadness1.ogg";
    const char* Music_MMZ2 = "MetallicMadness2.ogg";
    const char* Music_TMZ1 = "TitanicMonarch1.ogg";
    const char* Music_TMZ2 = "TitanicMonarch2.ogg";

    int GHZ1_TrackLoop = 776160;
    int GHZ2_TrackLoop = 775552;
    int CPZ1_TrackLoop = 680400;
    int CPZ2_TrackLoop = 680400;
    int SPZ1_TrackLoop = 1146600;
    int SPZ2_TrackLoop = 311142;
    int FBZ1_TrackLoop = 158760;
    int FBZ2_TrackLoop = 70560;
    int PGZ1_TrackLoop = 318316;
    int PGZ2_TrackLoop = 226625;
    int SSZ1_TrackLoop = 432894;
    int SSZ2_TrackLoop = 1;
    int HCZ1_TrackLoop = 1;
    int HCZ2_TrackLoop = 329797;
    int MSZ1_TrackLoop = 1007820;
    int MSZ2_TrackLoop = 179390;
    int OOZ1_TrackLoop = 358389;
    int OOZ2_TrackLoop = 176400;
    int LRZ1_TrackLoop = 497329;
    int LRZ2_TrackLoop = 769745;
    int MMZ1_TrackLoop = 470400;
    int MMZ2_TrackLoop = 296056;
    int TMZ1_TrackLoop = 184069;
    int TMZ2_TrackLoop = 384873;

    int GHZ1_TrackLoop_E = 1034880;
    int GHZ2_TrackLoop_E = 1034069;
    int CPZ1_TrackLoop_E = 907200;
    int CPZ2_TrackLoop_E = 907200;
    int SPZ1_TrackLoop_E = 1528800;
    int SPZ2_TrackLoop_E = 414856;
    int FBZ1_TrackLoop_E = 211680;
    int FBZ2_TrackLoop_E = 94080;
    int PGZ1_TrackLoop_E = 424421;
    int PGZ2_TrackLoop_E = 302167;
    int SSZ1_TrackLoop_E = 577192;
    int SSZ2_TrackLoop_E = 1;
    int HCZ1_TrackLoop_E = 1;
    int HCZ2_TrackLoop_E = 439729;
    int MSZ1_TrackLoop_E = 1343760;
    int MSZ2_TrackLoop_E = 239187;
    int OOZ1_TrackLoop_E = 477852;
    int OOZ2_TrackLoop_E = 235200;
    int LRZ1_TrackLoop_E = 663105;
    int LRZ2_TrackLoop_E = 1026327;
    int MMZ1_TrackLoop_E = 627200;
    int MMZ2_TrackLoop_E = 394741;
    int TMZ1_TrackLoop_E = 245425;
    int TMZ2_TrackLoop_E = 513164;

    void SetMusic(const char* NormalPath, const char* VapePath, int NormalLoop, int VapeLoop, const char*& name, unsigned int& a2, int& a3, unsigned int& loopstart, int& a5)
    {
        if (CompPlus_Settings::UseEncoreVapeMusic) 
        {
            name = VapePath;
            loopstart = VapeLoop;
        }
        else 
        {
            name = NormalPath;
            loopstart = NormalLoop;
        }
    }

    void OnLoad(char* CurrentScene, const char*& name, unsigned int& a2, int& a3, unsigned int& loopstart, int& a5)
    {
        if (CurrentScene) 
        {
            if (!strcmp(CurrentScene, CompPlus_Common::SMCP_GHZ1E)) SetMusic(Music_GHZ1, Music_GHZ1E, GHZ1_TrackLoop, GHZ1_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_GHZ2E)) SetMusic(Music_GHZ2, Music_GHZ2E, GHZ2_TrackLoop, GHZ2_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CPZ1E)) SetMusic(Music_CPZ1, Music_CPZ1E, CPZ1_TrackLoop, CPZ1_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_CPZ2E)) SetMusic(Music_CPZ2, Music_CPZ2E, CPZ2_TrackLoop, CPZ2_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SPZ1E)) SetMusic(Music_SPZ1, Music_SPZ1E, SPZ1_TrackLoop, SPZ1_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SPZ2E)) SetMusic(Music_SPZ2, Music_SPZ2E, SPZ2_TrackLoop, SPZ2_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_FBZ1E)) SetMusic(Music_FBZ1, Music_FBZ1E, FBZ1_TrackLoop, FBZ1_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_FBZ2E)) SetMusic(Music_FBZ2, Music_FBZ2E, FBZ2_TrackLoop, FBZ2_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_PGZ1E)) SetMusic(Music_PGZ1, Music_PGZ1E, PGZ1_TrackLoop, PGZ1_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_PGZ2E)) SetMusic(Music_PGZ2, Music_PGZ2E, PGZ2_TrackLoop, PGZ2_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SSZ1E)) SetMusic(Music_SSZ1, Music_SSZ1E, SSZ1_TrackLoop, SSZ1_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_SSZ2E)) SetMusic(Music_SSZ2, Music_SSZ2E, SSZ2_TrackLoop, SSZ2_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_HCZ1E)) SetMusic(Music_HCZ1, Music_HCZ1E, HCZ1_TrackLoop, HCZ1_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_HCZ2E)) SetMusic(Music_HCZ2, Music_HCZ2E, HCZ2_TrackLoop, HCZ2_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MSZ1E)) SetMusic(Music_MSZ1, Music_MSZ1E, MSZ1_TrackLoop, MSZ1_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MSZ2E)) SetMusic(Music_MSZ2, Music_MSZ2E, MSZ2_TrackLoop, MSZ2_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_OOZ1E)) SetMusic(Music_OOZ1, Music_OOZ1E, OOZ1_TrackLoop, OOZ1_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_OOZ2E)) SetMusic(Music_OOZ2, Music_OOZ2E, OOZ2_TrackLoop, OOZ2_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_LRZ1E)) SetMusic(Music_LRZ1, Music_LRZ1E, LRZ1_TrackLoop, LRZ1_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_LRZ2E)) SetMusic(Music_LRZ2, Music_LRZ2E, LRZ2_TrackLoop, LRZ2_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MMZ1E)) SetMusic(Music_MMZ1, Music_MMZ1E, MMZ1_TrackLoop, MMZ1_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_MMZ2E)) SetMusic(Music_MMZ2, Music_MMZ2E, MMZ2_TrackLoop, MMZ2_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_TMZ1E)) SetMusic(Music_TMZ1, Music_TMZ1E, TMZ1_TrackLoop, TMZ1_TrackLoop_E, name, a2, a3, loopstart, a5);
            else if (!strcmp(CurrentScene, CompPlus_Common::SMCP_TMZ2E)) SetMusic(Music_TMZ2, Music_TMZ2E, TMZ2_TrackLoop, TMZ2_TrackLoop_E, name, a2, a3, loopstart, a5);
        }
    }
}