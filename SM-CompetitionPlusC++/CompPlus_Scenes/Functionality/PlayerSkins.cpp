#include "PlayerSkins.h"
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

namespace CompPlus_PlayerSkins 
{
    using namespace SonicMania;
    using namespace CompPlus_Settings;

    bool AllowUsage = false;

    bool SpritesLoaded = false;

    int SonicDefaultID = 0;
    int TailsDefaultID = 0;
    int KnuxDefaultID = 0;
    int RayDefaultID = 0;
    int MightyDefaultID = 01;

    int SonicStockID = 0;
    int TailsStockID = 0;
    int KnuxStockID = 0;
    int RayStockID = 0;
    int MightyStockID = 0;

    int SonicDrillDiveID = 0;
    int TailsDrillDiveID = 0;
    int KnuxDrillDiveID = 0;
    int RayDrillDiveID = 0;

    int TailsDropDashID = 0;
    int KnuxDropDashID = 0;
    int RayDropDashID = 0;
    int MightyDropDashID = 0;

    const char* Anim_Default_Sonic = "SMCP_Players/Sonic.bin";
    const char* Anim_Default_Tails = "SMCP_Players/Tails.bin";
    const char* Anim_Default_Knux = "SMCP_Players/Knux.bin";
    const char* Anim_Default_Ray = "SMCP_Players/Ray.bin";
    const char* Anim_Default_Mighty = "SMCP_Players/Mighty.bin";

    const char* Anim_Dropdash_Tails = "SMCP_Players/TailsDD.bin";
    const char* Anim_Dropdash_Knux = "SMCP_Players/KnuxDD.bin";
    const char* Anim_Dropdash_Ray = "SMCP_Players/RayDD.bin";
    const char* Anim_Dropdash_Mighty = "SMCP_Players/MightyDD.bin";

    const char* Anim_DrillDive_Sonic = "SMCP_Players/SonicHD.bin";
    const char* Anim_DrillDive_Tails = "SMCP_Players/TailsHD.bin";
    const char* Anim_DrillDive_Knux = "SMCP_Players/KnuxHD.bin";
    const char* Anim_DrillDive_Ray = "SMCP_Players/RayHD.bin";


    int FrameTimeOut = 30;
    int CurrentTimeOut = 0;

    bool IsValidToRefresh()
    {
        if (!SpritesLoaded)
        {
            if (CurrentTimeOut >= FrameTimeOut)
            {
                CurrentTimeOut = 0;
                return true;
            }
            else
            {
                CurrentTimeOut++;
                return false;
            }
        }
        else
        {
            CurrentTimeOut = 0;
            return false;
        }
    }

    void LoadSprites() 
    {
        if (!SpritesLoaded) 
        {
            SonicStockID = SonicMania::LoadAnimation(Anim_Default_Sonic, SonicMania::Scope_Stage);
            TailsStockID = SonicMania::LoadAnimation(Anim_Default_Tails, SonicMania::Scope_Stage);
            KnuxStockID = SonicMania::LoadAnimation(Anim_Default_Knux, SonicMania::Scope_Stage);
            RayStockID = SonicMania::LoadAnimation(Anim_Default_Ray, SonicMania::Scope_Stage);
            MightyStockID = SonicMania::LoadAnimation(Anim_Default_Mighty, SonicMania::Scope_Stage);

            TailsDropDashID = SonicMania::LoadAnimation(Anim_Dropdash_Tails, SonicMania::Scope_Stage);
            KnuxDropDashID = SonicMania::LoadAnimation(Anim_Dropdash_Knux, SonicMania::Scope_Stage);
            RayDropDashID = SonicMania::LoadAnimation(Anim_Dropdash_Ray, SonicMania::Scope_Stage);
            MightyDropDashID = SonicMania::LoadAnimation(Anim_Dropdash_Mighty, SonicMania::Scope_Stage);

            SonicDrillDiveID = SonicMania::LoadAnimation(Anim_DrillDive_Sonic, SonicMania::Scope_Stage);
            TailsDrillDiveID = SonicMania::LoadAnimation(Anim_DrillDive_Tails, SonicMania::Scope_Stage);
            KnuxDrillDiveID = SonicMania::LoadAnimation(Anim_DrillDive_Knux, SonicMania::Scope_Stage);
            RayDrillDiveID = SonicMania::LoadAnimation(Anim_DrillDive_Ray, SonicMania::Scope_Stage);
            
            SpritesLoaded = true;
        }
    }

    void SetPlayerSpritePointer(SonicMania::EntityPlayer* Player, CompPlus_Settings::ChosenPlayer Chosen, CompPlus_Settings::PlayerAbility Ability) 
    {
        if (Chosen == CompPlus_Settings::ChosenPlayer_Sonic)
        {
            if (Ability == AbilitySet_Sonic) Player->SpriteIndex = SonicStockID;
            else if (Ability == AbilitySet_Tails) Player->SpriteIndex = SonicStockID;
            else if (Ability == AbilitySet_Knuckles) Player->SpriteIndex = SonicStockID;
            else if (Ability == AbilitySet_Ray) Player->SpriteIndex = SonicStockID;
            else if (Ability == AbilitySet_Mighty) Player->SpriteIndex = SonicDrillDiveID;
            else if (Ability == AbilitySet_Compatibility) Player->SpriteIndex = SonicStockID;
        }
        else if (Chosen == CompPlus_Settings::ChosenPlayer_Tails)
        {
            if (Ability == AbilitySet_Sonic) Player->SpriteIndex = TailsDropDashID;
            else if (Ability == AbilitySet_Tails) Player->SpriteIndex = TailsStockID;
            else if (Ability == AbilitySet_Knuckles) Player->SpriteIndex = TailsStockID;
            else if (Ability == AbilitySet_Ray) Player->SpriteIndex = TailsStockID;
            else if (Ability == AbilitySet_Mighty) Player->SpriteIndex = TailsDrillDiveID;
            else if (Ability == AbilitySet_Compatibility) Player->SpriteIndex = TailsStockID;
        }
        else if (Chosen == CompPlus_Settings::ChosenPlayer_Knuckles)
        {
            if (Ability == AbilitySet_Sonic) Player->SpriteIndex = KnuxDropDashID;
            else if (Ability == AbilitySet_Tails) Player->SpriteIndex = KnuxStockID;
            else if (Ability == AbilitySet_Knuckles) Player->SpriteIndex = KnuxStockID;
            else if (Ability == AbilitySet_Ray) Player->SpriteIndex = KnuxStockID;
            else if (Ability == AbilitySet_Mighty) Player->SpriteIndex = KnuxDrillDiveID;
            else if (Ability == AbilitySet_Compatibility) Player->SpriteIndex = KnuxStockID;
        }
        else if (Chosen == CompPlus_Settings::ChosenPlayer_Ray)
        {
            if (Ability == AbilitySet_Sonic) Player->SpriteIndex = RayDropDashID;
            else if (Ability == AbilitySet_Tails) Player->SpriteIndex = RayStockID;
            else if (Ability == AbilitySet_Knuckles) Player->SpriteIndex = RayStockID;
            else if (Ability == AbilitySet_Ray) Player->SpriteIndex = RayStockID;
            else if (Ability == AbilitySet_Mighty) Player->SpriteIndex = RayDrillDiveID;
            else if (Ability == AbilitySet_Compatibility) Player->SpriteIndex = RayStockID;
        }
        else if (Chosen == CompPlus_Settings::ChosenPlayer_Mighty)
        {
            if (Ability == AbilitySet_Sonic) Player->SpriteIndex = MightyDropDashID;
            else if (Ability == AbilitySet_Tails) Player->SpriteIndex = MightyStockID;
            else if (Ability == AbilitySet_Knuckles) Player->SpriteIndex = MightyStockID;
            else if (Ability == AbilitySet_Ray) Player->SpriteIndex = MightyStockID;
            else if (Ability == AbilitySet_Mighty) Player->SpriteIndex = MightyStockID;
            else if (Ability == AbilitySet_Compatibility) Player->SpriteIndex = MightyStockID;
        }
    }

    char* LastSceneDirectory;
    char* SceneDirectory = (char*)(baseAddress + 0xA5359C);
    bool LastSceneDirectory_IsValid = false;

    bool IsValidScene()
    {
        if (SceneDirectory)
        {
            if (LastSceneDirectory != SceneDirectory)
            {
                bool result = true;

                if (strcmp(SceneDirectory, "Pinball") == 0) result = false;
                else if (strcmp(SceneDirectory, "SpecialBS") == 0) result = false;
                else if (strcmp(SceneDirectory, "UFO1") == 0) result = false;
                else if (strcmp(SceneDirectory, "UFO2") == 0) result = false;
                else if (strcmp(SceneDirectory, "UFO3") == 0) result = false;
                else if (strcmp(SceneDirectory, "UFO4") == 0) result = false;
                else if (strcmp(SceneDirectory, "UFO5") == 0) result = false;
                else if (strcmp(SceneDirectory, "UFO6") == 0) result = false;
                else if (strcmp(SceneDirectory, "UFO7") == 0) result = false;

                LastSceneDirectory = SceneDirectory;
                LastSceneDirectory_IsValid = result;
                return LastSceneDirectory_IsValid;
            }
            else return LastSceneDirectory_IsValid;
        }
        else return false;
    }

    bool OnLoad = false;

    void OnFrame() 
    {
        if (AllowUsage) 
        {
            if (OnLoad && IsValidToRefresh())
            {
                LoadSprites();
                OnLoad = false;
            }

            if (SpritesLoaded)
            {
                SetPlayerSpritePointer(&SonicMania::Player1, CompPlus_Settings::Player1ChosenPlayer, CompPlus_Settings::Player1AbilitySet);
                SetPlayerSpritePointer(&SonicMania::Player2, CompPlus_Settings::Player2ChosenPlayer, CompPlus_Settings::Player2AbilitySet);
                SetPlayerSpritePointer(&SonicMania::Player3, CompPlus_Settings::Player3ChosenPlayer, CompPlus_Settings::Player3AbilitySet);
                SetPlayerSpritePointer(&SonicMania::Player4, CompPlus_Settings::Player4ChosenPlayer, CompPlus_Settings::Player4AbilitySet);
            }
        }

    }

    void Reload() 
    {
        if (AllowUsage)
        {
            SpritesLoaded = false;
            OnLoad = true;
        }
    }
}