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

    bool AllowUsage = true;

    const char* IZ_Anim_Compatibility_Sonic = "Data/Sprites/Players/Sonic.bin";
    const char* IZ_Anim_Compatibility_Tails = "Data/Sprites/Players/Tails.bin";
    const char* IZ_Anim_Compatibility_Knux = "Data/Sprites/Players/Knux.bin";
    const char* IZ_Anim_Compatibility_Ray = "Data/Sprites/Players/Ray.bin";
    const char* IZ_Anim_Compatibility_Mighty = "Data/Sprites/Players/Mighty.bin";

    const char* IZ_Anim_Compatibility_DropDash = "Data/Sprites/Players/DropDash.gif";
    const char* IZ_Anim_Compatibility_DrillDrop = "Data/Sprites/Players/DrillDive.gif";

    const char* IZ_Anim_Default_DropDash = "Data/Sprites/SMCP_Players/DropDash.gif";
    const char* IZ_Anim_Default_DrillDrop = "Data/Sprites/SMCP_Players/DrillDive.gif";

    const char* IZ_Anim_Default_Sonic = "Data/Sprites/SMCP_Players/Sonic.bin";
    const char* IZ_Anim_Default_Tails = "Data/Sprites/SMCP_Players/Tails.bin";
    const char* IZ_Anim_Default_Knux = "Data/Sprites/SMCP_Players/Knux.bin";
    const char* IZ_Anim_Default_Ray = "Data/Sprites/SMCP_Players/Ray.bin";
    const char* IZ_Anim_Default_Mighty = "Data/Sprites/SMCP_Players/Mighty.bin";

    const char* IZ_Anim_Dropdash_Tails = "Data/Sprites/SMCP_Players/TailsDD.bin";
    const char* IZ_Anim_Dropdash_Knux = "Data/Sprites/SMCP_Players/KnuxDD.bin";
    const char* IZ_Anim_Dropdash_Ray = "Data/Sprites/SMCP_Players/RayDD.bin";
    const char* IZ_Anim_Dropdash_Mighty = "Data/Sprites/SMCP_Players/MightyDD.bin";

    const char* IZ_Anim_DrillDive_Sonic = "Data/Sprites/SMCP_Players/SonicHD.bin";
    const char* IZ_Anim_DrillDive_Tails = "Data/Sprites/SMCP_Players/TailsHD.bin";
    const char* IZ_Anim_DrillDive_Knux = "Data/Sprites/SMCP_Players/KnuxHD.bin";
    const char* IZ_Anim_DrillDive_Ray = "Data/Sprites/SMCP_Players/RayHD.bin";

    SonicMania::Character CharacterP1 = SonicMania::Character::Character_Sonic;
    SonicMania::Character CharacterP2 = SonicMania::Character::Character_Tails;
    SonicMania::Character CharacterP3 = SonicMania::Character::Character_Knux;
    SonicMania::Character CharacterP4 = SonicMania::Character::Character_Mighty;

    int FrameTimeOut = 30;
    int CurrentTimeOut = 0;

    char* LastSceneDirectory;
    char* SceneDirectory = (char*)(baseAddress + 0xA5359C);
    bool LastSceneDirectory_IsValid = false;

    bool OnLoad = false;

    bool IsValidToRefresh()
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

    void TailFix() 
    {
        if (CompPlus_Settings::Player1ChosenPlayer == ChosenPlayer_Tails && SonicMania::OBJ_Player != nullptr) SonicMania::Player1.SpriteIndexTails = OBJ_Player->TailsTailsSpriteIndex;
        else SonicMania::Player1.SpriteIndexTails = 65535;

        if (CompPlus_Settings::Player2ChosenPlayer == ChosenPlayer_Tails && SonicMania::OBJ_Player != nullptr) SonicMania::Player2.SpriteIndexTails = OBJ_Player->TailsTailsSpriteIndex;
        else SonicMania::Player2.SpriteIndexTails = 65535;

        if (CompPlus_Settings::Player3ChosenPlayer == ChosenPlayer_Tails && SonicMania::OBJ_Player != nullptr) SonicMania::Player3.SpriteIndexTails = OBJ_Player->TailsTailsSpriteIndex;
        else SonicMania::Player3.SpriteIndexTails = 65535;

        if (CompPlus_Settings::Player4ChosenPlayer == ChosenPlayer_Tails && SonicMania::OBJ_Player != nullptr) SonicMania::Player4.SpriteIndexTails = OBJ_Player->TailsTailsSpriteIndex;
        else SonicMania::Player4.SpriteIndexTails = 65535;
    }

    void UpdatePlayer(int PlayerID, CompPlus_Settings::ChosenPlayer Player)
    {
        BYTE CharID = 1;
        if (Player == ChosenPlayer_Sonic) CharID = 1;
        else if (Player == ChosenPlayer_Tails) CharID = 2;
        else if (Player == ChosenPlayer_Knuckles) CharID = 4;
        else if (Player == ChosenPlayer_Mighty) CharID = 8;
        else if (Player == ChosenPlayer_Ray) CharID = 16;

        if (PlayerID == 1)
        {
            SonicMania::Options->CompetitionSession.CharacterFlags[0] = CharID;
            SonicMania::Options->CharacterFlags[0] = CharID;
            SonicMania::Player1.Character = CharacterP1;
        }
        else if (PlayerID == 2)
        {
            SonicMania::Options->CompetitionSession.CharacterFlags[1] = CharID;
            SonicMania::Options->CharacterFlags[1] = CharID;
            SonicMania::Player2.Character = CharacterP2;
        }
        else if (PlayerID == 3)
        {
            SonicMania::Options->CompetitionSession.CharacterFlags[2] = CharID;
            SonicMania::Options->CharacterFlags[2] = CharID;
            SonicMania::Player3.Character = CharacterP3;
        }
        else if (PlayerID == 4)
        {
            SonicMania::Options->CompetitionSession.CharacterFlags[3] = CharID;
            SonicMania::Options->CharacterFlags[3] = CharID;
            SonicMania::Player4.Character = CharacterP4;
        }


    }

    void SetPlayerAssetOverride(int PlayerID, CompPlus_Settings::ChosenPlayer Chosen, CompPlus_Settings::PlayerAbility Ability, const char* PlayerBasePath)
    {
        if (Chosen == CompPlus_Settings::ChosenPlayer_Sonic)
        {
            if (Ability == AbilitySet_Sonic) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Default_Sonic);
            else if (Ability == AbilitySet_Tails) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Default_Sonic);
            else if (Ability == AbilitySet_Knuckles) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Default_Sonic);
            else if (Ability == AbilitySet_Ray) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Default_Sonic);
            else if (Ability == AbilitySet_Mighty) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_DrillDive_Sonic);
            else if (Ability == AbilitySet_Compatibility) IZAPI::SetGlobalAsset(PlayerBasePath, nullptr);
        }
        else if (Chosen == CompPlus_Settings::ChosenPlayer_Tails)
        {
            if (Ability == AbilitySet_Sonic) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Dropdash_Tails);
            else if (Ability == AbilitySet_Tails) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Default_Tails);
            else if (Ability == AbilitySet_Knuckles) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Default_Tails);
            else if (Ability == AbilitySet_Ray) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Default_Tails);
            else if (Ability == AbilitySet_Mighty) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_DrillDive_Tails);
            else if (Ability == AbilitySet_Compatibility) IZAPI::SetGlobalAsset(PlayerBasePath, nullptr);
        }
        else if (Chosen == CompPlus_Settings::ChosenPlayer_Knuckles)
        {
            if (Ability == AbilitySet_Sonic) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Dropdash_Knux);
            else if (Ability == AbilitySet_Tails) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Default_Knux);
            else if (Ability == AbilitySet_Knuckles) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Default_Knux);
            else if (Ability == AbilitySet_Ray) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Default_Knux);
            else if (Ability == AbilitySet_Mighty) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_DrillDive_Knux);
            else if (Ability == AbilitySet_Compatibility) IZAPI::SetGlobalAsset(PlayerBasePath, nullptr);
        }
        else if (Chosen == CompPlus_Settings::ChosenPlayer_Ray)
        {
            if (Ability == AbilitySet_Sonic) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Dropdash_Ray);
            else if (Ability == AbilitySet_Tails) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Default_Ray);
            else if (Ability == AbilitySet_Knuckles) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Default_Ray);
            else if (Ability == AbilitySet_Ray) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Default_Ray);
            else if (Ability == AbilitySet_Mighty) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_DrillDive_Ray);
            else if (Ability == AbilitySet_Compatibility) IZAPI::SetGlobalAsset(PlayerBasePath, nullptr);
        }
        else if (Chosen == CompPlus_Settings::ChosenPlayer_Mighty)
        {
            if (Ability == AbilitySet_Sonic) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Dropdash_Mighty);
            else if (Ability == AbilitySet_Tails) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Default_Mighty);
            else if (Ability == AbilitySet_Knuckles) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Default_Mighty);
            else if (Ability == AbilitySet_Ray) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Default_Mighty);
            else if (Ability == AbilitySet_Mighty) IZAPI::SetGlobalAsset(PlayerBasePath, IZ_Anim_Default_Mighty);
            else if (Ability == AbilitySet_Compatibility) IZAPI::SetGlobalAsset(PlayerBasePath, nullptr);
        }

        UpdatePlayer(PlayerID, Chosen);
    }

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

    void OnFrame() 
    {
        if (AllowUsage)
        {
            if (OnLoad && IsValidToRefresh())
            {
                SonicMania::LoadAnimation(IZ_Anim_Compatibility_Sonic, Scope::Scope_None);
                SonicMania::LoadAnimation(IZ_Anim_Compatibility_Tails, Scope::Scope_None);
                SonicMania::LoadAnimation(IZ_Anim_Compatibility_Knux, Scope::Scope_None);
                SonicMania::LoadAnimation(IZ_Anim_Compatibility_Mighty, Scope::Scope_None);
                TailFix();
                OnLoad = false;
            }

            IZAPI::SetGlobalAsset(IZ_Anim_Compatibility_DropDash, IZ_Anim_Default_DropDash);
            IZAPI::SetGlobalAsset(IZ_Anim_Compatibility_DrillDrop, IZ_Anim_Default_DrillDrop);

            SetPlayerAssetOverride(1, CompPlus_Settings::Player1ChosenPlayer, CompPlus_Settings::Player1AbilitySet, IZ_Anim_Compatibility_Sonic);
            SetPlayerAssetOverride(2, CompPlus_Settings::Player2ChosenPlayer, CompPlus_Settings::Player2AbilitySet, IZ_Anim_Compatibility_Tails);
            SetPlayerAssetOverride(3, CompPlus_Settings::Player3ChosenPlayer, CompPlus_Settings::Player3AbilitySet, IZ_Anim_Compatibility_Knux);
            SetPlayerAssetOverride(4, CompPlus_Settings::Player4ChosenPlayer, CompPlus_Settings::Player4AbilitySet, IZ_Anim_Compatibility_Mighty);
        }

    }

    void Reload() 
    {
        if (AllowUsage)
        {
            OnLoad = true;
        }
    }
}