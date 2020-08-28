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

	void UpdateManiaMenu(bool inZone)
	{
        if (inZone) 
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

            EntityUIControl& uiControlTest = *GetEntityFromSceneSlot<EntityUIControl>(UIControlSlotID);
            if (uiControlTest.SelectedElement == 0) 
            {
                uiControlTest.SelectedElement = 2;
            }
            else if (uiControlTest.SelectedElement == 1) 
            {
                uiControlTest.SelectedElement = 3;
            }

            if (SonicMania::Options->CompetitionSession.inMatch == 1)
            {
                if (!inMatch)
                {
                    CompPlusSettings::FixUnmatchingVSPlayers();
                    inMatch = true;
                }
            }
            else
            {
                inMatch = false;
            }

            if (SonicMania::Options->CompetitionSession.FinishFlags != 0 && !StoredResults)
            {
                CompPlusSettings::LastSession = SonicMania::Options->CompetitionSession;
                CompPlusSettings::SetLastMatchResults();
                StoredResults = true;
            }

            SetUIBG_BGColor(74, 211, 156);
            SetUIBG_FGLowColor(247, 146, 24);
            SetUIBG_FGHighColor(57, 178, 206);
        }
        else 
        {
            StoredResults = false;
        }

	}
};