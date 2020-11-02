#include "stdafx.h"
#include "ManiaModLoader.h"
#include "DAGarden.h"
#include "include/SonicMania.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "CompPlus_Extensions/Drawing.h"
#include "CompPlus_Scenes/Level Select/CoreLevelSelect.h"
#include <string>
#include <vector>


namespace CompPlus_DAGarden_Core 
{
    int NextGarden = 0;

    int WaitTimer = 0;
    int WaitTimerMax = 70;

    bool SoundPlayed = false;
    bool WarpQued = false;
    const char* DesiredDestination;

    void SwitchGarden(bool isForward, int CurrentGarden) 
    {
        if (WarpQued) return;

        if (isForward) CurrentGarden += 1;
        else CurrentGarden -= 1;

        if (CurrentGarden >= 5) CurrentGarden = 0;
        else if (CurrentGarden <= -1) CurrentGarden = 4;

        NextGarden = 0;
        DesiredDestination = (char*)CompPlus_Common::SMCP_DAGarden;

        switch (CurrentGarden) 
        {
            case 0:
                DesiredDestination = (char*)CompPlus_Common::SMCP_DAGarden;
                break;
            case 1:
                DesiredDestination = (char*)CompPlus_Common::SMCP_DAGarden_Mania;
                break;
            case 2:
                DesiredDestination = (char*)CompPlus_Common::SMCP_DAGarden_Encore;
                break;
            case 3:
                DesiredDestination = (char*)CompPlus_Common::SMCP_DAGarden_Custom;
                break;
            case 4:
                DesiredDestination = (char*)CompPlus_Common::SMCP_DAGarden_Chaotix;
                break;
        }
        WarpQued = true;
    }


    void OnFrame(int GardenID) 
    {
        if (GardenID != -1) 
        {
            if (PlayerControllers[0].B.Press && PlayerControllers[0].Right.Down) CompPlus_DAGarden_Core::SwitchGarden(true, GardenID);
            else if (PlayerControllers[0].B.Press && PlayerControllers[0].Left.Down) CompPlus_DAGarden_Core::SwitchGarden(false, GardenID);
            else if (PlayerControllers[0].B.Press && PlayerControllers[0].Up.Down) CompPlus_DAGarden_Core::SwitchGarden(false, GardenID);
            else if (PlayerControllers[0].B.Press && PlayerControllers[0].Down.Down) CompPlus_DAGarden_Core::SwitchGarden(false, GardenID);
        }


        SoundPlayed = true;

        if (WarpQued) 
        {
            CompPlus_CoreLevelSelect::LevelSelectDelayLoop(0, DesiredDestination, true, WaitTimer, WaitTimerMax, WarpQued, SoundPlayed);
        }
    }

    void OnFrame() 
    {
        OnFrame(-1);
    }

}

namespace CompPlus_DAGarden 
{
    using namespace SonicMania;

    std::vector<std::string> TrackDescriptors =
    {
        "Composed by Tee Lopes",
        "Composed by Xanman",
        "Composed by Tee Lopes",
        "Composed by Xanman",
        "Composed by Xanman",
        "Sonic 3 and Knuckles - Data Select",
        "Knuckles Chaotix - Character Select",
        "Sonic Advanced 3 - Chaos Angel"
    };

    std::vector<std::string> TrackDescriptors2 =
    {
        "Modified by CarJem Generations",
        "",
        "Modified by AngelTheGamer",
        "",
        "",
        "Remixed by S3 Mixed / Tri Amentia Sound Team",
        "Composed by Knuckles Chaotix Sound Team",
        "Remixed by Xanman"
    };

    int ExtraTextSlotID = 76;
    int ExtraExtraTextSlotID = 78;

    CompPlus_CoreLevelSelect::UIBackgroundDefinition BGColors = CompPlus_CoreLevelSelect::UIBackgroundDefinition(SonicMania::Color(199, 235, 255), SonicMania::Color(247, 146, 24), SonicMania::Color(57, 178, 206));

    static wchar_t* Strings[2];

    void UpdateGeneralDisplay(int SlotID, char* _text, int size, int Index)
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

        Label3.DrawOrder = 10;

        Label3.Text = (wchar_t*)Strings[Index];
        ConvertASCII2Unicode(Label3.Text, _text, strlen(_text), -32);
        Label3.TextLength = (WORD)size;
    }

    void UpdateSelectedElement(int Element) 
    {
        if (TrackDescriptors.size() > Element) 
        {
            UpdateGeneralDisplay(ExtraTextSlotID, (char*)TrackDescriptors[Element].c_str(), TrackDescriptors[Element].length(), 0);
        }
        else 
        {
            UpdateGeneralDisplay(ExtraTextSlotID, (char*)"", 0, 0);
        }

        if (TrackDescriptors2.size() > Element)
        {
            UpdateGeneralDisplay(ExtraExtraTextSlotID, (char*)TrackDescriptors2[Element].c_str(), TrackDescriptors2[Element].length(), 1);
        }
        else
        {
            UpdateGeneralDisplay(ExtraExtraTextSlotID, (char*)"", 0, 1);
        }
    }

    void OnFrame() 
    {
        int CurrentSelection = GetSpritePointer(0xAC66D8, 0x10);
        UpdateSelectedElement(CurrentSelection);
        CompPlus_DAGarden_Core::OnFrame(0);

        CompPlus_CoreLevelSelect::SetUIBackgroundObject(BGColors);
    }


    void Init()
    {
        for (int i = 0; i < sizeof(Strings); ++i)
            Strings[i] = (wchar_t*)malloc(128);
    }
}

namespace CompPlus_DAGarden_Mania
{

    CompPlus_CoreLevelSelect::UIBackgroundDefinition BGColors = CompPlus_CoreLevelSelect::UIBackgroundDefinition(SonicMania::Color(56, 176, 200), SonicMania::Color(240, 112, 40), SonicMania::Color(80, 216, 160));


    void OnFrame()
    {
        CompPlus_DAGarden_Core::OnFrame(1);

        EntityUIInfoLabel& Label1 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(76);
        Label1.DrawOrder = 10;

        EntityUIInfoLabel& Label2 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(78);
        Label2.DrawOrder = 10;

        CompPlus_CoreLevelSelect::SetUIBackgroundObject(BGColors);
    }


    void Init()
    {

    }
}

namespace CompPlus_DAGarden_Encore
{
    CompPlus_CoreLevelSelect::UIBackgroundDefinition BGColors = CompPlus_CoreLevelSelect::UIBackgroundDefinition(SonicMania::Color(168, 80, 240), SonicMania::Color(136, 200, 1), SonicMania::Color(1, 176, 240));


    void OnFrame()
    {
        CompPlus_DAGarden_Core::OnFrame(2);

        EntityUIInfoLabel& Label1 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(76);
        Label1.DrawOrder = 10;

        EntityUIInfoLabel& Label2 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(78);
        Label2.DrawOrder = 10;

        CompPlus_CoreLevelSelect::SetUIBackgroundObject(BGColors);
    }


    void Init()
    {

    }
}

namespace CompPlus_DAGarden_Custom
{
    using namespace SonicMania;

    std::vector<std::string> TrackDescriptors =
    {
        "South Island Theme - Sonic Freedom POC",
        "South Island Theme - Mania Inspired Remix",
        "High Flyer - Track 01 - Sea Legs",
        "High Flyer - Track 11 - High Flyer",
        "Sonic Adventure - Sand Hill",
        "Sonic TNL - It's Gonna Happen (SMCP Remix)",
        "Sonic Triple Trouble - Special Stage 1 Remastered (2013)",
        "Sonic 2 - Mystic Cave Zone (2P) / Orignal HPZ Track",
        "Sonic 2 - Track 10 / Unused HPZ Cutscene",
        "Sonic.exe - Hill Zone",
        "Sonic.exe - Hill Zone"
    };

    std::vector<std::string> TrackDescriptors2 =
    {
        "Composed By Sound of Shadow",
        "Remixed By Jahn Davis",
        "Composed By Karl & Will Bruggeman",
        "Composed By Karl & Will Bruggeman",
        "Composed By Kenichi Tokoi",
        "Original Track By Wez Clarke & Maxine Hardcastle",
        "Remixed by MikeBlastDude",
        "Remixed by CarJem Generations",
        "Remixed by CarJem Generations",
        "Remixed/Composed by SonicString",
        "Remixed/Composed by SonicString"
    };

    int ExtraTextSlotID = 76;
    int ExtraExtraTextSlotID = 78;

    CompPlus_CoreLevelSelect::UIBackgroundDefinition BGColors = CompPlus_CoreLevelSelect::UIBackgroundDefinition(SonicMania::Color(199, 235, 255), SonicMania::Color(255, 235, 0), SonicMania::Color(255, 0, 0));


    static wchar_t* Strings[2];

    void UpdateGeneralDisplay(int SlotID, char* _text, int size, int Index)
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

        Label3.DrawOrder = 10;

        Label3.Text = (wchar_t*)Strings[Index];
        ConvertASCII2Unicode(Label3.Text, _text, strlen(_text), -32);
        Label3.TextLength = (WORD)size;
    }

    void UpdateSelectedElement(int Element)
    {
        if (TrackDescriptors.size() > Element)
        {
            UpdateGeneralDisplay(ExtraTextSlotID, (char*)TrackDescriptors[Element].c_str(), TrackDescriptors[Element].length(), 0);
        }
        else
        {
            UpdateGeneralDisplay(ExtraTextSlotID, (char*)"", 0, 0);
        }

        if (TrackDescriptors2.size() > Element)
        {
            UpdateGeneralDisplay(ExtraExtraTextSlotID, (char*)TrackDescriptors2[Element].c_str(), TrackDescriptors2[Element].length(), 1);
        }
        else
        {
            UpdateGeneralDisplay(ExtraExtraTextSlotID, (char*)"", 0, 1);
        }
    }

    void OnFrame()
    {
        int CurrentSelection = GetSpritePointer(0xAC66D8, 0x10);
        UpdateSelectedElement(CurrentSelection);
        CompPlus_DAGarden_Core::OnFrame(3);

        CompPlus_CoreLevelSelect::SetUIBackgroundObject(BGColors);
    }


    void Init()
    {
        for (int i = 0; i < sizeof(Strings); ++i)
            Strings[i] = (wchar_t*)malloc(128);
    }
}

namespace CompPlus_DAGarden_Chaotix
{
    using namespace SonicMania;

    std::vector<std::string> TrackDescriptors =
    {
        "Knuckles Chaotix - Isolated Island",
        "Knuckles Chaotix - Amazing Arena",
        "Knuckles Chaotix - Speed Slider",
        "Knuckles Chaotix - Botanic Base",
        "Knuckles Chaotix - Marina Madness",
        "Knuckles Chaotix - Techno Tower"
    };

    std::vector<std::string> TrackDescriptors2 =
    {
        "Composed by Knuckles Chaotix Sound Team",
        "Composed by Knuckles Chaotix Sound Team",
        "Composed by Knuckles Chaotix Sound Team",
        "Composed by Knuckles Chaotix Sound Team",
        "Composed by Knuckles Chaotix Sound Team",
        "Remixed by CobaltBW"
    };

    int ExtraTextSlotID = 76;
    int ExtraExtraTextSlotID = 78;

    int FrameLoop = 0;
    int FrameIndex = 0;
    int FrameSpeed = 2;
    int SpriteID = 0;
    bool SpritesLoaded = false;

    CompPlus_CoreLevelSelect::UIBackgroundDefinition BGColors = CompPlus_CoreLevelSelect::UIBackgroundDefinition(SonicMania::Color(0, 2, 128), SonicMania::Color(95, 38, 47), SonicMania::Color(24, 151, 31));

    void LoadSprites() 
    {
        if (!SpritesLoaded) 
        {
            SpriteID = LoadAnimation(CompPlus_Common::Anim_DAGarden_Chaotix, Scope_Stage);
            SpritesLoaded = true;
        }
    }

    static wchar_t* Strings[2];

    void UpdateGeneralDisplay(int SlotID, char* _text, int size, int Index)
    {
        EntityUIInfoLabel& Label3 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

        Label3.DrawOrder = 10;

        Label3.Text = (wchar_t*)Strings[Index];
        ConvertASCII2Unicode(Label3.Text, _text, strlen(_text), -32);
        Label3.TextLength = (WORD)size;
    }

    void UpdateSelectedElement(int Element)
    {
        if (TrackDescriptors.size() > Element)
        {
            UpdateGeneralDisplay(ExtraTextSlotID, (char*)TrackDescriptors[Element].c_str(), TrackDescriptors[Element].length(), 0);
        }
        else
        {
            UpdateGeneralDisplay(ExtraTextSlotID, (char*)"", 0, 0);
        }

        if (TrackDescriptors2.size() > Element)
        {
            UpdateGeneralDisplay(ExtraExtraTextSlotID, (char*)TrackDescriptors2[Element].c_str(), TrackDescriptors2[Element].length(), 1);
        }
        else
        {
            UpdateGeneralDisplay(ExtraExtraTextSlotID, (char*)"", 0, 1);
        }
    }

    void Reload() 
    {
        SpriteID = 0;
        SpritesLoaded = false;
    }

    SHORT PaletteStorage[256];
    int PaletteStorage_Length = 256;

    void SetColors() 
    {
        memcpy(PaletteStorage, SonicMania::Palette0, PaletteStorage_Length * sizeof(SHORT));

        int i = 0;
        SonicMania::Palette0[i] = SonicMania::Color(0xFF00FF).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x105068).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x60A0B0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xA8D8D8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF0F0F0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000040).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x080860).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x0038C8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x2020B8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x3840D8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x6060D8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xA8A8F0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xD00101).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF05860).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF098A8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x0020B0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x0850D8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x0878F0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x98E0F0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x388098).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x88C0C8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x68F0F0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xC8F0F0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x803000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE05800).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE89018).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF0C018).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF0D808).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE8E8A0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x007800).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x00C808).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x383040).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x484868).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x587090).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x80A0B0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x98C0C8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xC8E8E0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x4030C8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x5870E0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x280000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x480000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x900000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xB00000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE00000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF098A8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xC06030).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF0B090).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF0D0C0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x680000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xB04020).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE09060).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF0C0A8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x00FF00).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x003808).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x005810).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x007008).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x189000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x30B800).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x50D000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF024F8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xC830C8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xA058A0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x788078).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x50A850).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x28D028).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x00F800).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x500038).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x480080).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000040).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000060).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000080).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x0000A0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x0000C0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x2000E0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x004000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x006000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x008000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x00A000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x00C000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x00E000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x3090F0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x38A8F0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x70C8F0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xA0E8E0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x280008).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x400800).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x682000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x782800).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x903800).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xA84800).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xC05800).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE08000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x8000A0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE00080).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x2000A0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x1820B8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x400060).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x600080).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xA000E0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE000E0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x105068).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x60A0B0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xA8D8D8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF0F0F0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000040).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000080).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x0038C8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x0068F0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x1888F0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x28A8F0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x68D0F0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xD00101).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF05860).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF098A8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x0020B0).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x520000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x080808).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x181818).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x730000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x950000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF81800).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x420800).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE8A385).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xA66142).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x632000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xC74100).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x421800).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x8D3800).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE86100).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x5A2800).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xC75900).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xA66121).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE8A363).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x854100).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE88300).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xB67900).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE89B00).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE8A310).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xFFD400).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE8C400).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xFFE431).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF8F400).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xA6E421).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x42A300).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x63C421).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x218300).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x106100).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x218321).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x004100).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x002000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x002800).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x006900).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x00DC00).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x21E421).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x214163).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x6383A6).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x101039).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x636185).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x4A495A).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xA6A3C7).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x8D8B9D).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x29005A).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x6B00A6).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xAE00FF).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xD720FF).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE849FF).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE8E4E8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x424142).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xFF71FF).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x858385).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x080008).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xA6A3A6).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x525152).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xFFC4FF).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xFF8BFF).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF8F4F8).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xFF00FF).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x630021).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xC70042).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF87185).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x851021).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF8304A).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xFF5163).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xB61021).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE82031).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xFFA3A6).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xF09395).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0xE8494A).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x210042).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
        SonicMania::Palette0[i] = SonicMania::Color(0x000000).ToRGB565(); i++;
    }

    void ResetColors() 
    {
        memcpy(SonicMania::Palette0, PaletteStorage, PaletteStorage_Length * sizeof(SHORT));
    }

    void OnDraw() 
    {
        if (SpritesLoaded) 
        {
            SetColors();

            EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);
            SetSpriteAnimation(SpriteID, 0, &RingTemp->ActNumbersData, true, FrameIndex);
            DrawSprite(&RingTemp->ActNumbersData, &SonicMania::Vector2(212, 144), true);

            ResetColors();
        }
    }

    void OnFrame()
    {
        if (FrameLoop >= FrameSpeed)
        {
            FrameLoop = 0;
            if (FrameIndex >= 2) FrameIndex = 0;
            else FrameIndex += 1;
        }
        else FrameLoop += 1;

        LoadSprites();
        int CurrentSelection = GetSpritePointer(0xAC66D8, 0x10);
        UpdateSelectedElement(CurrentSelection);
        CompPlus_DAGarden_Core::OnFrame(4);

        CompPlus_CoreLevelSelect::SetUIBackgroundObject(BGColors);
    }


    void Init()
    {
        for (int i = 0; i < sizeof(Strings); ++i)
            Strings[i] = (wchar_t*)malloc(128);
    }
}