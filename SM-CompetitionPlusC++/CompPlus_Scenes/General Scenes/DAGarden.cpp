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
        "",
    };

    std::vector<std::string> TrackDescriptors2 =
    {
        ""
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
        "",
    };

    std::vector<std::string> TrackDescriptors2 =
    {
        ""
    };

    int ExtraTextSlotID = 76;
    int ExtraExtraTextSlotID = 78;

    CompPlus_CoreLevelSelect::UIBackgroundDefinition BGColors = CompPlus_CoreLevelSelect::UIBackgroundDefinition(SonicMania::Color(102, 71, 95), SonicMania::Color(95, 38, 47), SonicMania::Color(24, 151, 31));


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
        CompPlus_DAGarden_Core::OnFrame(4);

        CompPlus_CoreLevelSelect::SetUIBackgroundObject(BGColors);
    }


    void Init()
    {
        for (int i = 0; i < sizeof(Strings); ++i)
            Strings[i] = (wchar_t*)malloc(128);
    }
}