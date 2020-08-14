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

	void UpdateManiaMenu()
	{
		SonicMania::UIVsZoneButton& object = *GetEntityFromSceneSlot<SonicMania::UIVsZoneButton>(590);
		object.Disabled = false;
		object.Obfuscate = true;
		object.XOut = false;
		object.ZoneID = 11;
		object.Act = 101;

		SonicMania::UIVsZoneButton& object2 = *GetEntityFromSceneSlot<SonicMania::UIVsZoneButton>(591);
		object2.Disabled = false;
		object2.Obfuscate = true;
		object2.XOut = false;
		object2.ZoneID = 11;
		object2.Act = 102;

		SonicMania::UIVsZoneButton& object3 = *GetEntityFromSceneSlot<SonicMania::UIVsZoneButton>(592);
		object3.Disabled = false;
		object3.Obfuscate = true;
		object3.XOut = false;
		object3.ZoneID = 11;
		object3.Act = 103;

		SonicMania::UIVsZoneButton& object4 = *GetEntityFromSceneSlot<SonicMania::UIVsZoneButton>(593);
		object4.Disabled = true;
		object4.Obfuscate = true;
		object4.XOut = true;
		object4.ZoneID = 11;
		object4.Act = 104;
	}
};