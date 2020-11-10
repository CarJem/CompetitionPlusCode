#include "PlayerSkins.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/ManiaExt.h"

#include "include/ManiaAPI/SonicMania.h"
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

    bool SpritesLoaded = true;

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

    int LastP1SpriteIndex = 0;
    int LastP2SpriteIndex = 0;
    int LastP3SpriteIndex = 0;
    int LastP4SpriteIndex = 0;

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

    void SetPlayerSpritePointer(int PlayerID, SonicMania::EntityPlayer* Player, CompPlus_Settings::ChosenPlayer Chosen, CompPlus_Settings::PlayerAbility Ability)
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

        if (PlayerID == 1) LastP1SpriteIndex = Player->SpriteIndex;
        else if (PlayerID == 2) LastP2SpriteIndex = Player->SpriteIndex;
        else if (PlayerID == 3) LastP3SpriteIndex = Player->SpriteIndex;
        else if (PlayerID == 4) LastP4SpriteIndex = Player->SpriteIndex;

        //UpdatePlayer(PlayerID, Chosen);
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

    void OnFrame_IZ() 
    {
        if (OnLoad && IsValidToRefresh())
        {
            SonicMania::LoadAnimation(IZ_Anim_Compatibility_Sonic, Scope::Scope_None);
            SonicMania::LoadAnimation(IZ_Anim_Compatibility_Tails, Scope::Scope_None);
            SonicMania::LoadAnimation(IZ_Anim_Compatibility_Knux, Scope::Scope_None);
            SonicMania::LoadAnimation(IZ_Anim_Compatibility_Mighty, Scope::Scope_None);
            //TailFix();
            OnLoad = false;
        }

        IZAPI::SetGlobalAsset(IZ_Anim_Compatibility_DropDash, IZ_Anim_Default_DropDash);
        IZAPI::SetGlobalAsset(IZ_Anim_Compatibility_DrillDrop, IZ_Anim_Default_DrillDrop);

        SetPlayerAssetOverride(1, CompPlus_Settings::Player1ChosenPlayer, CompPlus_Settings::Player1AbilitySet, IZ_Anim_Compatibility_Sonic);
        SetPlayerAssetOverride(2, CompPlus_Settings::Player2ChosenPlayer, CompPlus_Settings::Player2AbilitySet, IZ_Anim_Compatibility_Tails);
        SetPlayerAssetOverride(3, CompPlus_Settings::Player3ChosenPlayer, CompPlus_Settings::Player3AbilitySet, IZ_Anim_Compatibility_Knux);
        SetPlayerAssetOverride(4, CompPlus_Settings::Player4ChosenPlayer, CompPlus_Settings::Player4AbilitySet, IZ_Anim_Compatibility_Mighty);
    }

    void OnFrame_Normal() 
    {
        if (OnLoad && IsValidToRefresh())
        {
            LoadSprites();
            OnLoad = false;
        }

        if (SpritesLoaded)
        {
            SetPlayerSpritePointer(1, &SonicMania::Player1, CompPlus_Settings::Player1ChosenPlayer, CompPlus_Settings::Player1AbilitySet);
            SetPlayerSpritePointer(2, &SonicMania::Player2, CompPlus_Settings::Player2ChosenPlayer, CompPlus_Settings::Player2AbilitySet);
            SetPlayerSpritePointer(3, &SonicMania::Player3, CompPlus_Settings::Player3ChosenPlayer, CompPlus_Settings::Player3AbilitySet);
            SetPlayerSpritePointer(4, &SonicMania::Player4, CompPlus_Settings::Player4ChosenPlayer, CompPlus_Settings::Player4AbilitySet);
        }
    }

    int OnSetSpriteAnimation(int SpriteIndex) 
    {
        if (IsValidToRefresh() && SpritesLoaded) 
        {
            int SonicSpriteIndex = GetSpritePointer(0xAC6758, 0xA08);
            int TailsSpriteIndex = GetSpritePointer(0xAC6758, 0xA0C);
            int KnuxSpriteIndex = GetSpritePointer(0xAC6758, 0xA10);
            int MightySpriteIndex = GetSpritePointer(0xAC6758, 0xA12);

            if (SpriteIndex == SonicSpriteIndex) SpriteIndex = LastP1SpriteIndex;
            else if (SpriteIndex == TailsSpriteIndex) SpriteIndex = LastP2SpriteIndex;
            else if (SpriteIndex == KnuxSpriteIndex) SpriteIndex = LastP3SpriteIndex;
            else if (SpriteIndex == MightySpriteIndex) SpriteIndex = LastP4SpriteIndex;
        }

        return SpriteIndex;
    }

    void OnDraw() 
    {

    }

    void OnFrame() 
    {
        if (CompPlus_Status::Abilities_EnableSkins) 
        {
            OnFrame_Normal();
        }
    }

    void Reload() 
    {
        if (CompPlus_Status::Abilities_EnableSkins)
        {
            SpritesLoaded = false;
            OnLoad = true;
        }
    }
}