#include "stdafx.h"
#include "CompetitionManiaMenu.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "SonicMania.h"

namespace CompPlus_CompetitionMenu
{
    using namespace SonicMania;

	int UIVsRoundPickerSlotID = 228;

	void UpdateManiaMenu()
	{
		SonicMania::UIVsZoneButton& object = *GetEntityFromSceneSlot<SonicMania::UIVsZoneButton>(590);
		object.Disabled = false;
		object.Obfuscate = true;
		object.XOut = false;
		object.ZoneID = 11;
		object.Act = 106;

		SonicMania::UIVsZoneButton& object2 = *GetEntityFromSceneSlot<SonicMania::UIVsZoneButton>(591);
		object2.Disabled = false;
		object2.Obfuscate = true;
		object2.XOut = false;
		object2.ZoneID = 11;
		object2.Act = 107;

		EntityUIVsRoundPicker& roundPicker = *GetEntityFromSceneSlot<EntityUIVsRoundPicker>(232);
		roundPicker.MaxVal = 999;

		SetUIBG_BGColor(74, 211, 156);
		SetUIBG_FGLowColor(247, 146, 24);
		SetUIBG_FGHighColor(57, 178, 206);
	}
};