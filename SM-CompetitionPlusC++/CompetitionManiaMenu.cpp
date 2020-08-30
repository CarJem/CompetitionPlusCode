#include "stdafx.h"
#include "CompetitionManiaMenu.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "CompPlusSettings.h"
#include "SonicMania.h"
#include "CompPlus_Scoring.h"

namespace CompPlus_CompetitionMenu
{
    using namespace SonicMania;


    int LastMenuModWriteState = 0;
	int UIVsRoundPickerSlotID = 228;
    bool inMatch = false;
    bool StoredResults = false;
    int UIControlSlotID = 354;
    int UIButtonASlotID = 231;
    int UIButtonBSlotID = 232;
    int UIButtonScreenLayoutSlotID = 239;
    int UIVsResultsScreenUIControl = 357;
    int UIVsLevelSelectUIControl = 586;
    int UIVsPlayerSelectUIControl = 352;

    int EntityUIVsResultsP1_SlotID = 241;
    int EntityUIVsResultsP2_SlotID = 242;
    int EntityUIVsResultsP3_SlotID = 243;
    int EntityUIVsResultsP4_SlotID = 244;


    void UpdatePreMatchStuff() 
    {
        if (!inMatch)
        {
            CompPlusSettings::FixUnmatchingVSPlayers();
            inMatch = true;
        }
    }

    void UpdateGlobalBGColors() 
    {
        SetUIBG_BGColor(74, 211, 156);
        SetUIBG_FGLowColor(247, 146, 24);
        SetUIBG_FGHighColor(57, 178, 206);
    }

    void UpdateOptionsPage() 
    {
        EntityUIVsRoundPicker& roundPicker = *GetEntityFromSceneSlot<EntityUIVsRoundPicker>(232);
        roundPicker.MaxVal = 999;

        EntityUIControl& CompetitionSettingsPage = *GetEntityFromSceneSlot<EntityUIControl>(UIControlSlotID);
        EntityUIControl& CompetitionLevelSelectPage = *GetEntityFromSceneSlot<EntityUIControl>(UIVsLevelSelectUIControl);

        if (CompetitionSettingsPage.SelectedElement == 0) CompetitionSettingsPage.SelectedElement = 2;
        else if (CompetitionSettingsPage.SelectedElement == 1) CompetitionSettingsPage.SelectedElement = 3;
    }

    void UpdateMiscStuff() 
    {
        if (SonicMania::Options->CompetitionSession.inMatch == 1) UpdatePreMatchStuff();
        else inMatch = false;
    }

    void UpdateResultsPage() 
    {
        EntityUIVsResults& P1_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(EntityUIVsResultsP1_SlotID);
        EntityUIVsResults& P2_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(EntityUIVsResultsP2_SlotID);
        EntityUIVsResults& P3_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(EntityUIVsResultsP3_SlotID);
        EntityUIVsResults& P4_Results = *GetEntityFromSceneSlot<EntityUIVsResults>(EntityUIVsResultsP4_SlotID);

        EntityUIControl& CompetitionResultsPage = *GetEntityFromSceneSlot<EntityUIControl>(UIVsResultsScreenUIControl);

        if (CompetitionResultsPage.Visible && StoredResults == false)
        {
            CompPlus_Scoring::SyncLastResults();
            SonicMania::Options->CompetitionSession.FinishFlags = 0;
            StoredResults = true;
        }
    }

    void UpdatePlayerSelectPage() 
    {
        EntityUIControl& CompetitionPlayerSelect = *GetEntityFromSceneSlot<EntityUIControl>(UIVsPlayerSelectUIControl);
        if (CompetitionPlayerSelect.Visible)
        {
            CompPlus_Scoring::ClearMatchResults();
        }
    }

    void UpdateLevelSelect() 
    {
        SonicMania::UIVsZoneButton& object = *GetEntityFromSceneSlot<SonicMania::UIVsZoneButton>(590);
        object.Disabled = false;
        //object.Obfuscate = true;
        object.XOut = false;
        object.ZoneID = 11;
        object.Act = 106;

        SonicMania::UIVsZoneButton& object2 = *GetEntityFromSceneSlot<SonicMania::UIVsZoneButton>(591);
        object2.Disabled = false;
        //object2.Obfuscate = true;
        object2.XOut = false;
        object2.ZoneID = 11;
        object2.Act = 107;

        EntityUIControl& CompetitionLevelSelect = *GetEntityFromSceneSlot<EntityUIControl>(UIVsLevelSelectUIControl);

        if (CompetitionLevelSelect.Visible) 
        {
            CompPlus_Scoring::ClearInternalWins();
        }
    }

	void UpdateManiaMenu()
	{
        UpdateLevelSelect();
        UpdateGlobalBGColors();
        UpdateOptionsPage();
        UpdateMiscStuff();
        UpdateResultsPage();
	}
};