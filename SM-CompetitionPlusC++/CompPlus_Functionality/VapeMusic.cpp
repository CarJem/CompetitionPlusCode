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
    using namespace CompPlus_Common;

    void SetMusic(const char* NormalPath, const char* VapePath, int NormalLoop, int VapeLoop, const char*& name, unsigned int& a2, int& a3, unsigned int& loopstart, int& a5)
    {
        if (a2 == 0) 
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