#include "SpotlightC.h"
#include "include/stdafx.h"
#include "include/ManiaModLoader.h"
#include "include/SonicMania.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Status.h"
#include "CompPlus_Scenes/Functionality/ZoneSpecifics.h"
#include "Base.h"
#include <vector>
#include <ctime>
#include <algorithm>

namespace CompPlus_SpotlightC
{
    using namespace SonicMania;


    // static int OriginalStandardSpotlightSize = 30;
    // static int OriginalSpotlightInnnerSizeA = OriginalStandardSpotlightSize + 75; //105
    // static int OriginalSpotlightInnnerSizeB = OriginalStandardSpotlightSize;      //30 : Plus Ring Count
    // static int OriginalSpotlightInnnerSizeC = OriginalStandardSpotlightSize + 10; //40 : Plus Ring Count
    // static int OriginalSpotLightWidth = 1000;
    // 
    // static int OriginalRingCountMin = 10;
    // static int OriginalRingCountMax = 50;
    // static int OriginalCounterMax = 60;

    static int StandardSpotlightSize = 30;
    static int SpotlightInnnerSizeA = StandardSpotlightSize + 75;
    static int SpotlightInnnerSizeB = StandardSpotlightSize;
    static int SpotlightInnnerSizeC = StandardSpotlightSize + 10;
    static int SpotLightWidth = 1000;

    static int RingCountMin = 10;
    static int RingCountMax = 50;
    static int CounterMax = 60;


    int Counter1P = 0;
    int Counter2P = 0;
    int Counter3P = 0;
    int Counter4P = 0;

    bool CanDrawP1 = false;
    bool CanDrawP2 = false;
    bool CanDrawP3 = false;
    bool CanDrawP4 = false;

    char* SceneDirectory = (char*)(baseAddress + 0xA5359C);
    const char* LastCheckedIZScene;
    bool LastCheckedIZScene_WasAcceptable = false;

    bool IsAcceptableScene() 
    {
        if (CompPlus_Core::CurrentStage.SceneKey)
        {
            const char* SceneKey = CompPlus_Core::CurrentStage.SceneKey;
            if (LastCheckedIZScene != SceneKey)
            {
                bool result = false;
                if (CompPlus_ZoneSpecifics::IsManiaStage(SceneKey)) result = true;
                else if (CompPlus_ZoneSpecifics::IsEncoreStage(SceneKey)) result = true;
                else if (CompPlus_ZoneSpecifics::IsCustomStage(SceneKey)) result = true;
                else if (CompPlus_ZoneSpecifics::IsChaotixStage(SceneKey)) result = true;
                else if (CompPlus_ZoneSpecifics::IsChaotixEncoreStage(SceneKey)) result = true;
                else if (CompPlus_ZoneSpecifics::IsExecutorStage(SceneKey)) result = true;

                LastCheckedIZScene = SceneKey;
                LastCheckedIZScene_WasAcceptable = result;
                return result;
            }
            else return LastCheckedIZScene_WasAcceptable;
        }
        else return false;
    }


    bool IsValidScene()
    {
        if (!strcmp(SceneDirectory, "Pinball")) return false;
        else if (!strcmp(SceneDirectory, "SpecialBS")) return false;
        else if (!strcmp(SceneDirectory, "UFO1")) return false;
        else if (!strcmp(SceneDirectory, "UFO2")) return false;
        else if (!strcmp(SceneDirectory, "UFO3")) return false;
        else if (!strcmp(SceneDirectory, "UFO4")) return false;
        else if (!strcmp(SceneDirectory, "UFO5")) return false;
        else if (!strcmp(SceneDirectory, "UFO6")) return false;
        else if (!strcmp(SceneDirectory, "UFO7")) return false;
        else return IsAcceptableScene();
    }

    int UpdatePlayerRings(EntityPlayer* Player, int Counter)
    {
        if (Player->RingCount > RingCountMin && Player->InputStatus == CONTROL_NORMAL)
        {
            if (Counter >= CounterMax)
            {
                if (Player->RingCount > RingCountMax)
                {
                    Player->RingCount--;
                }
                Player->RingCount--;
                Counter = 0;
            }
            else
            {
                Counter++;
            }

        }
        return Counter;
    }

    void UpdatePlayersRings()
    {
        if (GameState & GameState_Running && !(GameState & GameState_SoftPause))
        {
            Counter1P = UpdatePlayerRings(&Player1, Counter1P);
            Counter2P = UpdatePlayerRings(&Player2, Counter2P);
            Counter3P = UpdatePlayerRings(&Player3, Counter3P);
            Counter4P = UpdatePlayerRings(&Player4, Counter4P);
        }
    }

    void EndDraw(int pointer)
    {
        if (pointer == 0) CanDrawP1 = false;
        else if (pointer == 1) CanDrawP2 = false;
        else if (pointer == 2) CanDrawP3 = false;
        else if (pointer == 3) CanDrawP4 = false;
    }

    bool CanDraw(int pointer)
    {
        if (pointer == 0) return CanDrawP1;
        else if (pointer == 1) return CanDrawP2;
        else if (pointer == 2) return CanDrawP3;
        else if (pointer == 3) return CanDrawP4;
        else return false;
    }

    void OnPlayerDraw(EntityPlayer* ThisObject, Vector2 Position)
    {
        DrawCircleOutline(Position.X, Position.Y, SpotlightInnnerSizeA, SpotLightWidth, ToRGB888(GetPaletteEntry(0, 1)), 140, Ink_Alpha, true);
        DrawCircleOutline(Position.X, Position.Y, SpotlightInnnerSizeB + ThisObject->RingCount, SpotLightWidth, ToRGB888(GetPaletteEntry(0, 1)), 160, Ink_Alpha, true);
        DrawCircleOutline(Position.X, Position.Y, SpotlightInnnerSizeC + ThisObject->RingCount, SpotLightWidth, ToRGB888(GetPaletteEntry(0, 1)), 250, Ink_Alpha, true);
    }

    void OnDraw() 
    {
        if (CompPlus_Settings::SpotLightChallenge && IsValidScene()) 
        {
            ushort pointer = GetSpritePointer(0xAA7634, 0x14);
            int screen = 0;

            if (pointer == 0) screen = 0;
            else if (pointer == 1) screen = 1;
            else if (pointer == 2) screen = 2;
            else if (pointer == 3) screen = 3;

            if (CanDraw(screen))
            {
                int offset = 0x96030 * screen;

                if (Player1.Camera != nullptr && screen == 0)
                {
                    Vector2 position_p1 = Vector2((SonicMania::Player1.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player1.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)));
                    OnPlayerDraw(&Player1, position_p1);
                }
                if (Player2.Camera != nullptr && screen == 1)
                {
                    Vector2 position_p2 = Vector2((SonicMania::Player2.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player2.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)));
                    OnPlayerDraw(&Player2, position_p2);
                }
                if (Player3.Camera != nullptr && screen == 2)
                {
                    Vector2 position_p3 = Vector2((SonicMania::Player3.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player3.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)));
                    OnPlayerDraw(&Player3, position_p3);
                }
                if (Player4.Camera != nullptr && screen == 3)
                {
                    Vector2 position_p4 = Vector2((SonicMania::Player4.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player4.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)));
                    OnPlayerDraw(&Player4, position_p4);
                }

                EndDraw(screen);
            }
        }
    }

    void OnFrame()
    {
        if (CompPlus_Settings::SpotLightChallenge && IsValidScene())
        {
            CanDrawP1 = true;
            CanDrawP2 = true;
            CanDrawP3 = true;
            CanDrawP4 = true;

            UpdatePlayersRings();
        }
    }
}