#include "stdafx.h"
#include "CoreLevelSelect.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/PointScrolling.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "SonicMania.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include <vector>
#include "CompPlus_Core/CompPlus_Scoring.h"
#include "CompPlus_Scenes/HUB World/HubCore.h"
#include "CompPlus_Extensions/Drawing.h"


namespace CompPlus_CoreLevelSelect
{
    using namespace CompPlus_Common;

    std::string PaletteACT_FilePath;
    bool PaletteSaved = false;
    std::vector<SHORT> PaletteStorage;
    int PaletteStorage_Length;

    int CurrentDraw_StartX = 0;
    int CurrentDraw_StartY = 0;
    int CurrentDraw_SpacingX = 0;
    int CurrentDraw_SpacingY = 0;

    bool isSelectorVisible = false;

    void LevelSelectDelayLoop(int selectorID, MenuPoint level, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
    {
        if (FastWarp && SceneLoadWaitTimer < 30)
        {
            SceneLoadWaitTimer = 30;
        }


        if (SceneLoadWaitTimer >= SceneLoadWaitMax)
        {
            if (level.isIZ)
            {
                CompPlus_Scoring::LastZone = level.CP_Name.c_str();
                CompPlus_Common::LoadLevel_IZ(level.LevelID_IZ.c_str());
            }
            else
            {
                CompPlus_Scoring::LastZone = level.CP_Name.c_str();
                CompPlus_Common::LoadLevel(level.LevelID);
            }

            SceneLoadWaitTimer = 0;
            LevelSelected = false;
            LevelSelectedWarpSoundPlayed = false;
        }
        else
        {
            if (SceneLoadWaitTimer >= 30 && !LevelSelectedWarpSoundPlayed)
            {
                PlaySoundFXS(CompPlus_Common::SFX_SpecialWarp);
                LevelSelectedWarpSoundPlayed = true;

                Entity* FXFade = SpawnObject(GetObjectIDFromType(ObjectType_FXFade), 0, Vector2(Player1.Position.X, Player1.Position.Y - 30));
                EntityFXFade* FxFadeR = (EntityFXFade*)FXFade;

                if (FastWarp)
                {
                    PlaySoundFXS(CompPlus_Common::SFX_SpecialWarp);
                    LevelSelectedWarpSoundPlayed = true;

                    FxFadeR->Time = 0;
                    FxFadeR->SpeedIn = 20;
                    FxFadeR->Wait = 0;
                    FxFadeR->SpeedOut = 0;
                    FxFadeR->Color = 0x000000;
                    FxFadeR->OneWay = true;
                    FxFadeR->EventOnly = false;
                    FxFadeR->Overhud = false;
                    FxFadeR->FadeOutBlack = true;
                }
                else
                {
                    FxFadeR->Time = 0;
                    FxFadeR->SpeedIn = 10;
                    FxFadeR->Wait = 3;
                    FxFadeR->SpeedOut = 0;
                    FxFadeR->Color = 0x000000;
                    FxFadeR->OneWay = true;
                    FxFadeR->EventOnly = false;
                    FxFadeR->Overhud = false;
                    FxFadeR->FadeOutBlack = true;
                }


            }
            SceneLoadWaitTimer++;
        }

        stru_26B818[0].playStatus = 0;
    }

    void UniversalLSelectLoop()
    {
        SonicMania::SetVSScreenCount(1);
    }

    void LevelSelectDelayLoop(int selectorID, int levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
    {
        if (FastWarp && SceneLoadWaitTimer < 50)
        {
            SceneLoadWaitTimer = 50;
        }


        if (SceneLoadWaitTimer >= SceneLoadWaitMax)
        {
            LoadLevel(levelID);
            SceneLoadWaitTimer = 0;
            LevelSelected = false;
            LevelSelectedWarpSoundPlayed = false;
        }
        else
        {
            if (SceneLoadWaitTimer >= 50 && !LevelSelectedWarpSoundPlayed)
            {
                PlaySoundFXS(CompPlus_Common::SFX_SpecialWarp);
                LevelSelectedWarpSoundPlayed = true;

                Entity* FXFade = SpawnObject(GetObjectIDFromType(ObjectType_FXFade), 0, Vector2(Player1.Position.X, Player1.Position.Y - 30));
                EntityFXFade* FxFadeR = (EntityFXFade*)FXFade;

                FxFadeR->Time = 0;
                FxFadeR->SpeedIn = 10;
                FxFadeR->Wait = 3;
                FxFadeR->SpeedOut = 0;
                FxFadeR->Color = 0x000000;
                FxFadeR->OneWay = true;
                FxFadeR->EventOnly = false;
                FxFadeR->Overhud = false;
                FxFadeR->FadeOutBlack = true;

            }
            SceneLoadWaitTimer++;
        }

        stru_26B818[0].playStatus = 0;
    }

    void LevelSelectExitDelayLoop(int selectorID, const char* levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
    {
        if (FastWarp && SceneLoadWaitTimer < 50)
        {
            SceneLoadWaitTimer = 50;
        }


        if (SceneLoadWaitTimer >= SceneLoadWaitMax)
        {
            CompPlus_HubCore::ReturnDestination = 3;
            CompPlus_Common::LoadHUBWorld();
            SceneLoadWaitTimer = 0;
            LevelSelected = false;
            LevelSelectedWarpSoundPlayed = false;
        }
        else
        {
            if (SceneLoadWaitTimer >= 50 && !LevelSelectedWarpSoundPlayed)
            {
                PlaySoundFXS(CompPlus_Common::SFX_SpecialWarp);
                LevelSelectedWarpSoundPlayed = true;

                Entity* FXFade = SpawnObject(GetObjectIDFromType(ObjectType_FXFade), 0, Vector2(Player1.Position.X, Player1.Position.Y - 30));
                EntityFXFade* FxFadeR = (EntityFXFade*)FXFade;

                FxFadeR->Time = 0;
                FxFadeR->SpeedIn = 10;
                FxFadeR->Wait = 3;
                FxFadeR->SpeedOut = 0;
                FxFadeR->Color = 0x000000;
                FxFadeR->OneWay = true;
                FxFadeR->EventOnly = false;
                FxFadeR->Overhud = false;
                FxFadeR->FadeOutBlack = true;

            }
            SceneLoadWaitTimer++;
        }

        stru_26B818[0].playStatus = 0;
    }

    void LevelSelectDelayLoop(int selectorID, const char* levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
    {
        if (FastWarp && SceneLoadWaitTimer < 30)
        {
            SceneLoadWaitTimer = 30;
        }


        if (SceneLoadWaitTimer >= SceneLoadWaitMax)
        {
            CompPlus_Common::LoadLevel_IZ(levelID);
            SceneLoadWaitTimer = 0;
            LevelSelected = false;
            LevelSelectedWarpSoundPlayed = false;
        }
        else
        {
            if (SceneLoadWaitTimer >= 30 && !LevelSelectedWarpSoundPlayed)
            {
                PlaySoundFXS(CompPlus_Common::SFX_SpecialWarp);
                LevelSelectedWarpSoundPlayed = true;

                Entity* FXFade = SpawnObject(GetObjectIDFromType(ObjectType_FXFade), 0, Vector2(Player1.Position.X, Player1.Position.Y - 30));
                EntityFXFade* FxFadeR = (EntityFXFade*)FXFade;

                if (FastWarp)
                {
                    PlaySoundFXS(CompPlus_Common::SFX_SpecialWarp);
                    LevelSelectedWarpSoundPlayed = true;

                    FxFadeR->Time = 0;
                    FxFadeR->SpeedIn = 20;
                    FxFadeR->Wait = 0;
                    FxFadeR->SpeedOut = 0;
                    FxFadeR->Color = 0x000000;
                    FxFadeR->OneWay = true;
                    FxFadeR->EventOnly = false;
                    FxFadeR->Overhud = false;
                    FxFadeR->FadeOutBlack = true;
                }
                else
                {
                    FxFadeR->Time = 0;
                    FxFadeR->SpeedIn = 10;
                    FxFadeR->Wait = 3;
                    FxFadeR->SpeedOut = 0;
                    FxFadeR->Color = 0x000000;
                    FxFadeR->OneWay = true;
                    FxFadeR->EventOnly = false;
                    FxFadeR->Overhud = false;
                    FxFadeR->FadeOutBlack = true;
                }


            }
            SceneLoadWaitTimer++;
        }

        stru_26B818[0].playStatus = 0;
    }

    void LevelSelectDelay(bool isClassic, bool& LevelSelected)
    {
        PlayMenuAcceptSoundFX(isClassic);
        LevelSelected = true;
    }

    void ApplyPalette() 
    {
        for (int i = 0; i < PaletteStorage_Length; i++) 
        {
            SonicMania::Palette0[i] = PaletteStorage[i];
            SonicMania::Palette1[i] = PaletteStorage[i];
            SonicMania::Palette2[i] = PaletteStorage[i];
            SonicMania::Palette3[i] = PaletteStorage[i];
        }
    }  

    void TempStorePalette() 
    {
        int i = 0;
        std::vector<SHORT> Palette = std::vector<SHORT>(256);
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0x000000); i++;
        Palette[i] = SonicMania::ToRGB565(0x000080); i++;
        Palette[i] = SonicMania::ToRGB565(0x0038C0); i++;
        Palette[i] = SonicMania::ToRGB565(0x0068F0); i++;
        Palette[i] = SonicMania::ToRGB565(0x1888F0); i++;
        Palette[i] = SonicMania::ToRGB565(0x30A0F0); i++;
        Palette[i] = SonicMania::ToRGB565(0x68D0F0); i++;
        Palette[i] = SonicMania::ToRGB565(0x185868); i++;
        Palette[i] = SonicMania::ToRGB565(0x60A0B0); i++;
        Palette[i] = SonicMania::ToRGB565(0x98C8C8); i++;
        Palette[i] = SonicMania::ToRGB565(0xA0E0E0); i++;
        Palette[i] = SonicMania::ToRGB565(0xC06830); i++;
        Palette[i] = SonicMania::ToRGB565(0xE09060); i++;
        Palette[i] = SonicMania::ToRGB565(0xF0B090); i++;
        Palette[i] = SonicMania::ToRGB565(0xF0D0C0); i++;
        Palette[i] = SonicMania::ToRGB565(0x400000); i++;
        Palette[i] = SonicMania::ToRGB565(0x900000); i++;
        Palette[i] = SonicMania::ToRGB565(0xE00000); i++;
        Palette[i] = SonicMania::ToRGB565(0x800000); i++;
        Palette[i] = SonicMania::ToRGB565(0xB03000); i++;
        Palette[i] = SonicMania::ToRGB565(0xE07000); i++;
        Palette[i] = SonicMania::ToRGB565(0xE0A000); i++;
        Palette[i] = SonicMania::ToRGB565(0xE0C000); i++;
        Palette[i] = SonicMania::ToRGB565(0x200008); i++;
        Palette[i] = SonicMania::ToRGB565(0x700010); i++;
        Palette[i] = SonicMania::ToRGB565(0xE00020); i++;
        Palette[i] = SonicMania::ToRGB565(0xE84848); i++;
        Palette[i] = SonicMania::ToRGB565(0xE87878); i++;
        Palette[i] = SonicMania::ToRGB565(0xE89898); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0x282028); i++;
        Palette[i] = SonicMania::ToRGB565(0x383040); i++;
        Palette[i] = SonicMania::ToRGB565(0x484868); i++;
        Palette[i] = SonicMania::ToRGB565(0x587090); i++;
        Palette[i] = SonicMania::ToRGB565(0x80A0B0); i++;
        Palette[i] = SonicMania::ToRGB565(0x98C0C8); i++;
        Palette[i] = SonicMania::ToRGB565(0xB0D0D0); i++;
        Palette[i] = SonicMania::ToRGB565(0xC0E0E0); i++;
        Palette[i] = SonicMania::ToRGB565(0xE0E0E0); i++;
        Palette[i] = SonicMania::ToRGB565(0xF0F0F0); i++;
        Palette[i] = SonicMania::ToRGB565(0x401000); i++;
        Palette[i] = SonicMania::ToRGB565(0x883800); i++;
        Palette[i] = SonicMania::ToRGB565(0xB86800); i++;
        Palette[i] = SonicMania::ToRGB565(0xF0B000); i++;
        Palette[i] = SonicMania::ToRGB565(0xF0D800); i++;
        Palette[i] = SonicMania::ToRGB565(0xF0F000); i++;
        Palette[i] = SonicMania::ToRGB565(0x200000); i++;
        Palette[i] = SonicMania::ToRGB565(0x480008); i++;
        Palette[i] = SonicMania::ToRGB565(0x900010); i++;
        Palette[i] = SonicMania::ToRGB565(0xE00000); i++;
        Palette[i] = SonicMania::ToRGB565(0xA02040); i++;
        Palette[i] = SonicMania::ToRGB565(0x604080); i++;
        Palette[i] = SonicMania::ToRGB565(0xA0A0C0); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xE070C0); i++;
        Palette[i] = SonicMania::ToRGB565(0xF0B0C0); i++;
        Palette[i] = SonicMania::ToRGB565(0xF0D8C0); i++;
        Palette[i] = SonicMania::ToRGB565(0xF0F0C0); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0x7F0300); i++;
        Palette[i] = SonicMania::ToRGB565(0xAC1A00); i++;
        Palette[i] = SonicMania::ToRGB565(0xCD4F00); i++;
        Palette[i] = SonicMania::ToRGB565(0xDC7800); i++;
        Palette[i] = SonicMania::ToRGB565(0xE48E00); i++;
        Palette[i] = SonicMania::ToRGB565(0xECA600); i++;
        Palette[i] = SonicMania::ToRGB565(0x005800); i++;
        Palette[i] = SonicMania::ToRGB565(0x00A000); i++;
        Palette[i] = SonicMania::ToRGB565(0x00C800); i++;
        Palette[i] = SonicMania::ToRGB565(0xD8D020); i++;
        Palette[i] = SonicMania::ToRGB565(0x580018); i++;
        Palette[i] = SonicMania::ToRGB565(0x980030); i++;
        Palette[i] = SonicMania::ToRGB565(0xD00040); i++;
        Palette[i] = SonicMania::ToRGB565(0xE82858); i++;
        Palette[i] = SonicMania::ToRGB565(0xF06080); i++;
        Palette[i] = SonicMania::ToRGB565(0xF08088); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0x501010); i++;
        Palette[i] = SonicMania::ToRGB565(0x882020); i++;
        Palette[i] = SonicMania::ToRGB565(0xA83030); i++;
        Palette[i] = SonicMania::ToRGB565(0xC84040); i++;
        Palette[i] = SonicMania::ToRGB565(0xE06868); i++;
        Palette[i] = SonicMania::ToRGB565(0xF09098); i++;
        Palette[i] = SonicMania::ToRGB565(0xA86020); i++;
        Palette[i] = SonicMania::ToRGB565(0xD08840); i++;
        Palette[i] = SonicMania::ToRGB565(0xE8A860); i++;
        Palette[i] = SonicMania::ToRGB565(0xF0D090); i++;
        Palette[i] = SonicMania::ToRGB565(0x000000); i++;
        Palette[i] = SonicMania::ToRGB565(0x780000); i++;
        Palette[i] = SonicMania::ToRGB565(0xA80000); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0x883000); i++;
        Palette[i] = SonicMania::ToRGB565(0xA06800); i++;
        Palette[i] = SonicMania::ToRGB565(0xB88810); i++;
        Palette[i] = SonicMania::ToRGB565(0xD0A810); i++;
        Palette[i] = SonicMania::ToRGB565(0xE0C020); i++;
        Palette[i] = SonicMania::ToRGB565(0xE8D038); i++;
        Palette[i] = SonicMania::ToRGB565(0xF0E078); i++;
        Palette[i] = SonicMania::ToRGB565(0x000000); i++;
        Palette[i] = SonicMania::ToRGB565(0xB05000); i++;
        Palette[i] = SonicMania::ToRGB565(0xC87048); i++;
        Palette[i] = SonicMania::ToRGB565(0xE8A078); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xD0F0F0); i++;
        Palette[i] = SonicMania::ToRGB565(0x2001A0); i++;
        Palette[i] = SonicMania::ToRGB565(0x101028); i++;
        Palette[i] = SonicMania::ToRGB565(0x010140); i++;
        Palette[i] = SonicMania::ToRGB565(0xE7484D); i++;
        Palette[i] = SonicMania::ToRGB565(0x260206); i++;
        Palette[i] = SonicMania::ToRGB565(0xE86880); i++;
        Palette[i] = SonicMania::ToRGB565(0xCE0F42); i++;
        Palette[i] = SonicMania::ToRGB565(0x740531); i++;
        Palette[i] = SonicMania::ToRGB565(0x530026); i++;
        Palette[i] = SonicMania::ToRGB565(0x100108); i++;
        Palette[i] = SonicMania::ToRGB565(0x97236A); i++;
        Palette[i] = SonicMania::ToRGB565(0xB80A89); i++;
        Palette[i] = SonicMania::ToRGB565(0xE76DD2); i++;
        Palette[i] = SonicMania::ToRGB565(0xCB01CB); i++;
        Palette[i] = SonicMania::ToRGB565(0x100810); i++;
        Palette[i] = SonicMania::ToRGB565(0x181018); i++;
        Palette[i] = SonicMania::ToRGB565(0xE0A0E0); i++;
        Palette[i] = SonicMania::ToRGB565(0xE5DBE5); i++;
        Palette[i] = SonicMania::ToRGB565(0x87018B); i++;
        Palette[i] = SonicMania::ToRGB565(0x400B41); i++;
        Palette[i] = SonicMania::ToRGB565(0x200128); i++;
        Palette[i] = SonicMania::ToRGB565(0x8204C6); i++;
        Palette[i] = SonicMania::ToRGB565(0x4E0E8F); i++;
        Palette[i] = SonicMania::ToRGB565(0x5814C0); i++;
        Palette[i] = SonicMania::ToRGB565(0x180040); i++;
        Palette[i] = SonicMania::ToRGB565(0x310E6A); i++;
        Palette[i] = SonicMania::ToRGB565(0x8975BB); i++;
        Palette[i] = SonicMania::ToRGB565(0x212024); i++;
        Palette[i] = SonicMania::ToRGB565(0x180168); i++;
        Palette[i] = SonicMania::ToRGB565(0xCDC7EC); i++;
        Palette[i] = SonicMania::ToRGB565(0x030112); i++;
        Palette[i] = SonicMania::ToRGB565(0x181058); i++;
        Palette[i] = SonicMania::ToRGB565(0x100858); i++;
        Palette[i] = SonicMania::ToRGB565(0x2A1BB3); i++;
        Palette[i] = SonicMania::ToRGB565(0x010120); i++;
        Palette[i] = SonicMania::ToRGB565(0x080848); i++;
        Palette[i] = SonicMania::ToRGB565(0x080840); i++;
        Palette[i] = SonicMania::ToRGB565(0x101038); i++;
        Palette[i] = SonicMania::ToRGB565(0xF0F0F1); i++;
        Palette[i] = SonicMania::ToRGB565(0x010889); i++;
        Palette[i] = SonicMania::ToRGB565(0x0113C2); i++;
        Palette[i] = SonicMania::ToRGB565(0x272A41); i++;
        Palette[i] = SonicMania::ToRGB565(0x1F41C9); i++;
        Palette[i] = SonicMania::ToRGB565(0x96A1CA); i++;
        Palette[i] = SonicMania::ToRGB565(0x5A6890); i++;
        Palette[i] = SonicMania::ToRGB565(0x97999F); i++;
        Palette[i] = SonicMania::ToRGB565(0x001038); i++;
        Palette[i] = SonicMania::ToRGB565(0x314A82); i++;
        Palette[i] = SonicMania::ToRGB565(0x065BEF); i++;
        Palette[i] = SonicMania::ToRGB565(0x011028); i++;
        Palette[i] = SonicMania::ToRGB565(0x0A3272); i++;
        Palette[i] = SonicMania::ToRGB565(0x678BBF); i++;
        Palette[i] = SonicMania::ToRGB565(0x4390EB); i++;
        Palette[i] = SonicMania::ToRGB565(0x46515D); i++;
        Palette[i] = SonicMania::ToRGB565(0x2671B6); i++;
        Palette[i] = SonicMania::ToRGB565(0xB1CEE2); i++;
        Palette[i] = SonicMania::ToRGB565(0x0090E0); i++;
        Palette[i] = SonicMania::ToRGB565(0x1192D9); i++;
        Palette[i] = SonicMania::ToRGB565(0x083048); i++;
        Palette[i] = SonicMania::ToRGB565(0x67BCED); i++;
        Palette[i] = SonicMania::ToRGB565(0x90CEEB); i++;
        Palette[i] = SonicMania::ToRGB565(0x002C36); i++;
        Palette[i] = SonicMania::ToRGB565(0x00BCE0); i++;
        Palette[i] = SonicMania::ToRGB565(0xC8E3E7); i++;
        Palette[i] = SonicMania::ToRGB565(0xB3E9EF); i++;
        Palette[i] = SonicMania::ToRGB565(0x154C47); i++;
        Palette[i] = SonicMania::ToRGB565(0xAABEB9); i++;
        Palette[i] = SonicMania::ToRGB565(0x09995B); i++;
        Palette[i] = SonicMania::ToRGB565(0x29D078); i++;
        Palette[i] = SonicMania::ToRGB565(0x012B10); i++;
        Palette[i] = SonicMania::ToRGB565(0x70F090); i++;
        Palette[i] = SonicMania::ToRGB565(0xBAE0BD); i++;
        Palette[i] = SonicMania::ToRGB565(0x9AEB9C); i++;
        Palette[i] = SonicMania::ToRGB565(0x68B868); i++;
        Palette[i] = SonicMania::ToRGB565(0x056401); i++;
        Palette[i] = SonicMania::ToRGB565(0x198501); i++;
        Palette[i] = SonicMania::ToRGB565(0x0E4101); i++;
        Palette[i] = SonicMania::ToRGB565(0x8DD665); i++;
        Palette[i] = SonicMania::ToRGB565(0x64CA05); i++;
        Palette[i] = SonicMania::ToRGB565(0x4B9504); i++;
        Palette[i] = SonicMania::ToRGB565(0x80E002); i++;
        Palette[i] = SonicMania::ToRGB565(0xE0E000); i++;
        Palette[i] = SonicMania::ToRGB565(0xE6E6A6); i++;
        Palette[i] = SonicMania::ToRGB565(0xC4B213); i++;
        Palette[i] = SonicMania::ToRGB565(0xE7D22C); i++;
        Palette[i] = SonicMania::ToRGB565(0xA48F16); i++;
        Palette[i] = SonicMania::ToRGB565(0x6A633B); i++;
        Palette[i] = SonicMania::ToRGB565(0xECD562); i++;
        Palette[i] = SonicMania::ToRGB565(0xE3DDBD); i++;
        Palette[i] = SonicMania::ToRGB565(0xE6A900); i++;
        Palette[i] = SonicMania::ToRGB565(0xE6AE25); i++;
        Palette[i] = SonicMania::ToRGB565(0xD09818); i++;
        Palette[i] = SonicMania::ToRGB565(0xCB9E3F); i++;
        Palette[i] = SonicMania::ToRGB565(0xD1C6B4); i++;
        Palette[i] = SonicMania::ToRGB565(0x99600A); i++;
        Palette[i] = SonicMania::ToRGB565(0xDF7E00); i++;
        Palette[i] = SonicMania::ToRGB565(0x6B4005); i++;
        Palette[i] = SonicMania::ToRGB565(0x462D0F); i++;
        Palette[i] = SonicMania::ToRGB565(0xD48020); i++;
        Palette[i] = SonicMania::ToRGB565(0xE5811E); i++;
        Palette[i] = SonicMania::ToRGB565(0xD65C02); i++;
        Palette[i] = SonicMania::ToRGB565(0xED924F); i++;
        Palette[i] = SonicMania::ToRGB565(0x612E0A); i++;
        Palette[i] = SonicMania::ToRGB565(0x867468); i++;
        Palette[i] = SonicMania::ToRGB565(0x3E1403); i++;
        Palette[i] = SonicMania::ToRGB565(0x9E1907); i++;
        Palette[i] = SonicMania::ToRGB565(0x6E0E04); i++;
        Palette[i] = SonicMania::ToRGB565(0x612724); i++;
        Palette[i] = SonicMania::ToRGB565(0xDF0000); i++;
        Palette[i] = SonicMania::ToRGB565(0x402020); i++;
        Palette[i] = SonicMania::ToRGB565(0x010101); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFF00FF); i++;
        Palette[i] = SonicMania::ToRGB565(0xFFFFFF); i++;

        PaletteStorage = Palette;
        PaletteStorage_Length = 256;
    }

    void StorePalette(std::string filepath)
    {
        unsigned int size = 0;

        // Open file
        std::ifstream file(filepath);

        // Get size and allocate memory
        file.seekg(0, std::ios::end);
        size = static_cast<unsigned int>(file.tellg());
        char* act = (char*)malloc(size);
        file.seekg(0, std::ios::beg);

        // Read file
        file.read(act, size * 3);

        int actCount = size / 3;
        std::vector<SHORT> palette = std::vector<SHORT>(256);
        BOOL paletteMask[256];
        memset(paletteMask, 0, sizeof(paletteMask));
        for (int i = 0; i < actCount; ++i)
        {
            int color = *(int*)(act + (i * 3)) & 0xFFFFFF;
            int red = (int)act[i * 3 + 0];
            int green = (int)act[i * 3 + 1];
            int blue = (int)act[i * 3 + 2];
            paletteMask[i] = !(color == 0xFF00FF);
            palette[i] = SonicMania::ToRGB565(red, green, blue);
        }

        PaletteStorage = palette;
        PaletteStorage_Length = actCount;
    }

    void EnforcePalette()
    {
        if (!PaletteSaved)
        {
            TempStorePalette();
            //StorePalette(PaletteACT_FilePath);
            PaletteSaved = true;
        }
        else
        {
            ApplyPalette();
        }
    }

    int GetPositionOffsetX()
    {
        return (ScreenOffsetX != 0 ? ScreenOffsetX : 0);
    }

    int GetPositionOffsetY()
    {
        return (ScreenOffsetY != 0 ? ScreenOffsetY / 2 : 0);
    }

    void SetUIBackgroundObject(UIBackgroundDefinition Definition) 
    {
        SetUIBG_BGColor(Definition.BG.Red, Definition.BG.Green, Definition.BG.Blue);
        SetUIBG_FGLowColor(Definition.FG1.Red, Definition.FG1.Green, Definition.FG1.Blue);
        SetUIBG_FGHighColor(Definition.FG2.Red, Definition.FG2.Green, Definition.FG2.Blue);
    }

    void InitDrawVariables(int StartX, int StartY, int SpacingX, int SpacingY)
    {
        CurrentDraw_StartX = StartX;
        CurrentDraw_StartY = StartY;
        CurrentDraw_SpacingX = SpacingX;
        CurrentDraw_SpacingY = SpacingY;
    }

    void DrawZoneInfo(MenuPoint Point, EntityTitleCard* Canvas) 
    {
        if (!Point.isBlank)
        {
            SonicMania::Vector2 CurrentPosition = SonicMania::Vector2(PosXCurrent + GetPositionOffsetX(), PosYCurrent + GetPositionOffsetY());
            int StartY = CurrentPosition.Y + 86;

            int HalfSize = (WindowSizeX != 0 ? WindowSizeX / 2 : 0);
            int TopSize = (WindowSizeY != 0 ? WindowSizeY / 2 : 0);

            int NameY = StartY + 16 - 4;
            int AuthorY = StartY + 30 - 4;
            int ExtrasY = StartY + 46 - 4;


            Canvas->DrawOrder = 12;
            Drawing::DrawTitleCardRect(CurrentPosition.X - HalfSize, StartY + 4, WindowSizeX, 60, 0x000000, 150, InkEffect::Ink_Alpha);

            Drawing::DrawMenuTextSprite(Point.CP_Name, SonicMania::Vector2(CurrentPosition.X, NameY), false, 10, 0, 0, DevMenu_Alignment::Alignment_Center);
            Drawing::DrawMenuTextSprite(Point.CP_Author, SonicMania::Vector2(CurrentPosition.X, AuthorY), false, 10, 0, 0, DevMenu_Alignment::Alignment_Center);
            Drawing::DrawMenuTextSprite(Point.CP_Extra, SonicMania::Vector2(CurrentPosition.X, ExtrasY), false, 10, 0, 0, DevMenu_Alignment::Alignment_Center);
        }

    }

    void DrawEntryChaotix(MenuPoint Point, int x, int y, int IconsSpriteID, int MenuPos_X, int MenuPos_Y, EntityTitleCard* Canvas)
    {
        if (!Point.isBlank)
        {
            if (MenuPos_Y == y && MenuPos_X == x) SonicMania::SetSpriteAnimation(IconsSpriteID, 0, &Canvas->ActNumbersData, true, 1);
            else SonicMania::SetSpriteAnimation(IconsSpriteID, 0, &Canvas->ActNumbersData, true, 0);
            DrawSprite(&Canvas->ActNumbersData, &SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY), false);
            SonicMania::SetSpriteAnimation(IconsSpriteID, Point.ImageAnimID, &Canvas->ActNumbersData, true, Point.ImageFrameID);
            DrawSprite(&Canvas->ActNumbersData, &SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY), false);
            if (Point.isLocked) 
            {
                SonicMania::SetSpriteAnimation(IconsSpriteID, 2, &Canvas->ActNumbersData, true, 3);
                DrawSprite(&Canvas->ActNumbersData, &SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY), false);
            }
        }
    }

    void DrawEntry(MenuPoint Point, int x, int y, int IconsSpriteID, int MenuPos_X, int MenuPos_Y, EntityTitleCard* Canvas)
    {
        if (!Point.isBlank)
        {
            if (MenuPos_Y == y && MenuPos_X == x) SonicMania::SetSpriteAnimation(IconsSpriteID, 0, &Canvas->ActNumbersData, true, 1);
            else SonicMania::SetSpriteAnimation(IconsSpriteID, 0, &Canvas->ActNumbersData, true, 0);
            DrawSprite(&Canvas->ActNumbersData, &SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY), false);
            SonicMania::SetSpriteAnimation(IconsSpriteID, Point.ImageAnimID, &Canvas->ActNumbersData, true, Point.ImageFrameID);
            DrawSprite(&Canvas->ActNumbersData, &SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY), false);
        }
    }

    void DrawEntryText(MenuPoint Point, int x, int y) 
    {
        int TextOffsetY = 40;
        if (!Point.isBlank)
        {
            if (Point.YellowText)  Drawing::DrawDevTextSprite(Point.CP_Title, SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY + TextOffsetY), false, 10, 0, 0, DevMenu_Alignment::Alignment_Center, true);
            else Drawing::DrawDevTextSprite(Point.CP_Title, SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY + TextOffsetY), false, 10, 0, 0, DevMenu_Alignment::Alignment_Center, false);

        }
    }

    void DrawEntryTextEXE(MenuPoint Point, int x, int y)
    {
        int TextOffsetY = 40;
        if (!Point.isBlank)
        {
            if (Point.YellowText)  Drawing::DrawDevEXETextSprite(Point.CP_Title, SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY + TextOffsetY), false, 10, 0, 0, DevMenu_Alignment::Alignment_Center, true);
            else Drawing::DrawDevEXETextSprite(Point.CP_Title, SonicMania::Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY + TextOffsetY), false, 10, 0, 0, DevMenu_Alignment::Alignment_Center, false);

        }
    }

    void DrawSelector(int x, int y, int IconsSpriteID, EntityTitleCard* Canvas, bool IsSelected)
    {
        if (IsSelected)
        {
            if (isSelectorVisible) isSelectorVisible = false;
            else isSelectorVisible = true;
        }
        else isSelectorVisible = true;

        if (isSelectorVisible) 
        {
            SonicMania::SetSpriteAnimation(IconsSpriteID, 0, &Canvas->ActNumbersData, true, 3);
            DrawSprite(&Canvas->ActNumbersData, &SonicMania::Vector2(PosXCurrent + GetPositionOffsetX(), PosYCurrent + GetPositionOffsetY()), false);
        }
    }

    MenuPoint CreateBlankMenuPoint(int x, int y)
    {
        MenuPoint Point = MenuPoint(true, x, y);
        Point.Position = Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY);
        return Point;
    }

    MenuPoint CreateMenuPoint(int y, int x, std::string SceneID, std::string Title, std::string Name, std::string Author, int AnimID, int FrameID, bool isLocked)
    {
        MenuPoint Point = MenuPoint();
        Point.Position = Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY);
        Point.CP_Title = Title.c_str();
        Point.CP_Name = Name.c_str();
        Point.CP_Author = Author.c_str();
        Point.isIZ = true;
        Point.LevelID_IZ = SceneID;
        Point.ImageAnimID = AnimID;
        Point.ImageFrameID = FrameID;
        Point.isLocked = isLocked;
        return Point;
    }

    MenuPoint CreateMenuPoint(int y, int x, int LevelID, std::string Title, std::string Name, std::string Author, int AnimID, int FrameID, bool isLocked)
    {
        MenuPoint Point = MenuPoint();
        Point.Position = Vector2(CurrentDraw_StartX + x * CurrentDraw_SpacingX, CurrentDraw_StartY + y * CurrentDraw_SpacingY);
        Point.CP_Title = Title.c_str();
        Point.CP_Name = Name.c_str();
        Point.CP_Author = Author.c_str();
        Point.isIZ = false;
        Point.LevelID = LevelID;
        Point.ImageAnimID = AnimID;
        Point.ImageFrameID = FrameID;
        Point.isLocked = isLocked;
        return Point;
    }

    void SetupPosition(short MenuPos_X, short MenuPos_Y)
    {
        MenuPos_X -= GetPositionOffsetX();
        MenuPos_Y -= GetPositionOffsetY();
        InitPosition(MenuPos_X, MenuPos_Y);
    }

    void ResetMenuPos(int& MenuPos_X, int& MenuPos_Y, int SMenuPos_X, int SMenuPos_Y, int& LastMenuPos_X, int& LastMenuPos_Y, bool& SwapLevelSelect)
    {
        MenuPos_X = SMenuPos_X;
        MenuPos_Y = SMenuPos_Y;

        LastMenuPos_X = SMenuPos_X;
        LastMenuPos_Y = SMenuPos_Y;

        SwapLevelSelect = false;
    }

    void ResetMenuPos(int& MenuPos_X, int& MenuPos_Y, int& LastMenuPos_X, int& LastMenuPos_Y, bool& SwapLevelSelect)
    {
        MenuPos_X = 0;
        MenuPos_Y = 0;

        LastMenuPos_X = 0;
        LastMenuPos_Y = 0;

        SwapLevelSelect = false;
    }

    void UpdateLevelSelectScroll(int& MenuPos_X, int& MenuPos_Y, int& LastMenuPos_X, int& LastMenuPos_Y, bool& UpdateMenuScroll, MenuPoint** MenuPoints)
    {
        if (MenuPoints[MenuPos_Y][MenuPos_X].isBlank)
        {
            MenuPos_X = MenuPoints[MenuPos_Y][MenuPos_X].RedirectX;
            MenuPos_Y = MenuPoints[MenuPos_Y][MenuPos_X].RedirectY;
        }

        short x1 = MenuPoints[MenuPos_Y][MenuPos_X].Position.X - GetPositionOffsetX();
        short y1 = MenuPoints[MenuPos_Y][MenuPos_X].Position.Y - GetPositionOffsetY();

        short x2 = MenuPoints[LastMenuPos_Y][LastMenuPos_X].Position.X - GetPositionOffsetX();
        short y2 = MenuPoints[LastMenuPos_Y][LastMenuPos_X].Position.Y - GetPositionOffsetY();

        ScrollToPosition(x1, y1, x2, y2, WorldViewX, WorldViewY, UpdateMenuScroll);
        UpdateMenuScroll = false;
    }

    void UpdateLastPos(int& LastMenuPos_X, int& LastMenuPos_Y, int& MenuPos_X, int& MenuPos_Y)
    {
        LastMenuPos_Y = MenuPos_Y;
        LastMenuPos_X = MenuPos_X;
    }

    void Init(std::string modPath) 
    {
        PaletteACT_FilePath = modPath + CompPlus_Common::Act_LSelect;
    }
};