#include "SpotlightC.h"
#include "include/stdafx.h"
#include "include/ManiaModLoader.h"
#include "include/SonicMania.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Status.h"
#include "CompPlus_Functionality/ZoneSpecifics.h"
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

    static int StandardSpotlightSize = 60;
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

    void OnPlayerDraw(EntityPlayer* ThisObject, Vector2 Position)
    {
        DrawCircleOutline(Position.X, Position.Y, SpotlightInnnerSizeA, SpotLightWidth, 0x000000, 140, Ink_Alpha, true);
        DrawCircleOutline(Position.X, Position.Y, SpotlightInnnerSizeB + ThisObject->RingCount, SpotLightWidth, 0x000000, 160, Ink_Alpha, true);
        DrawCircleOutline(Position.X, Position.Y, SpotlightInnnerSizeC + ThisObject->RingCount, SpotLightWidth, 0x000000, 250, Ink_Alpha, true);
    }

    void OnDraw() 
    {
        EntityTitleCard* Canvas = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);
        int OldDrawOrder = Canvas->DrawOrder;
        Canvas->DrawOrder = 8;

        ushort pointer = GetSpritePointer(0xAA7634, 0x14);
        int screen = 0;

        if (pointer == 0) screen = 0;
        else if (pointer == 1) screen = 1;
        else if (pointer == 2) screen = 2;
        else if (pointer == 3) screen = 3;

        int offset = 0x96030 * screen;

        if (CompPlus_Settings::SpotLightChallenge && IsValidScene()) 
        {
            if (screen == 0)
            {
                Vector2 position_p1 = Vector2((SonicMania::Player1.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player1.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)));
                OnPlayerDraw(&Player1, position_p1);
            }
            if (screen == 1)
            {
                Vector2 position_p2 = Vector2((SonicMania::Player2.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player2.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)));
                OnPlayerDraw(&Player2, position_p2);
            }
            if (screen == 2)
            {
                Vector2 position_p3 = Vector2((SonicMania::Player3.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player3.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)));
                OnPlayerDraw(&Player3, position_p3);
            }
            if (screen == 3)
            {
                Vector2 position_p4 = Vector2((SonicMania::Player4.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (Player4.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)));
                OnPlayerDraw(&Player4, position_p4);
            }
        }
        Canvas->DrawOrder = OldDrawOrder;
    }

    void OnFrame()
    {
        if (CompPlus_Settings::SpotLightChallenge && IsValidScene())
        {
            UpdatePlayersRings();
        }
    }
}