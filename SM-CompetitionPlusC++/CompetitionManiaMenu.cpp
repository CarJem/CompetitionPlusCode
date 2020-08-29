#include "stdafx.h"
#include "CompetitionManiaMenu.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "SonicMania.h"
#include "CompPlusSettings.h"

namespace CompPlus_CompetitionMenu
{
    using namespace SonicMania;

	int UIVsRoundPickerSlotID = 228;
    bool inMatch = false;
    bool StoredResults = false;
    int UIControlSlotID = 354;
    int UIButtonASlotID = 231;
    int UIButtonBSlotID = 232;
    int UIButtonScreenLayoutSlotID = 239;
    int UIVsResultsScreenUIControl = 357;
    int UIVsLevelSelectUIControl = 586;

    void UpdatePreMatchStuff() 
    {
        if (!inMatch)
        {
            CompPlusSettings::FixUnmatchingVSPlayers();
            inMatch = true;
        }
    }

	void UpdateManiaMenu()
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

        EntityUIVsRoundPicker& roundPicker = *GetEntityFromSceneSlot<EntityUIVsRoundPicker>(232);
        roundPicker.MaxVal = 999;

        EntityUIControl& CompetitionSettingsPage = *GetEntityFromSceneSlot<EntityUIControl>(UIControlSlotID);
        EntityUIControl& CompetitionResultsPage = *GetEntityFromSceneSlot<EntityUIControl>(UIVsResultsScreenUIControl);
        EntityUIControl& CompetitionLevelSelectPage = *GetEntityFromSceneSlot<EntityUIControl>(UIVsLevelSelectUIControl);
        
        if (CompetitionSettingsPage.SelectedElement == 0) CompetitionSettingsPage.SelectedElement = 2;
        else if (CompetitionSettingsPage.SelectedElement == 1) CompetitionSettingsPage.SelectedElement = 3;

        if (SonicMania::Options->CompetitionSession.inMatch == 1) UpdatePreMatchStuff();
        else inMatch = false;

        if (CompetitionResultsPage.Visible && StoredResults == false)
        {
            SonicMania::Options->CompetitionSession.FinishFlags = 0;
            StoredResults = true;
        }
        else 
        {
            StoredResults = false;
        }

        SetUIBG_BGColor(74, 211, 156);
        SetUIBG_FGLowColor(247, 146, 24);
        SetUIBG_FGHighColor(57, 178, 206);
	}
};