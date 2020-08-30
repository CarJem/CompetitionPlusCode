#include "stdafx.h"
#include "SettingsMenu.h"
#include "SonicMania.h"
#include "ManiaExt.h"
#include "CompPlus_Core.h"
#include "CompSettings.h"
#include "GeneralSettings.h"
#include "PlayerConfiguration.h"
#include "CompPlus_Common.h"
#include <string>

namespace CompPlus_Settings_Base
{
	using namespace SonicMania;
	using namespace CompPlus_Core;
	using namespace CompPlus_Settings_CompetitionPage;
	using namespace CompPlus_Settings_GeneralPage;
	using namespace CompPlus_Settings_PlayerConfig;
	using namespace CompPlus_Common;

	static int OnScreenDrawReturn = baseAddress + 0x7FFE;
	bool IsInit = false;
	bool CanDraw = false;

	void DoMenuOnScreenDraw()
	{
		if (CanDraw) 
		{
			DrawRect(120, 120, 12, 12, 0x00, 250, Ink_Alpha, true);
			DrawTextSprite("HEY THERE", SonicMania::Vector2(50,10), true);
			DrawTextSprite("I don't suck!", SonicMania::Vector2(50, 20), true);

			//DrawCircle(0, 0, 40, 0x00, 250, Ink_Alpha, true);
			//DrawCircle(120, 120, 100, 0xFFFFFF, 0, Ink_None, true);
		}
	}

	void InitSettings() 
	{
		IsInit = true;
	}

	void UpdateSettingsMenu()
	{
		FixSummary();
		if (!IsInit) InitSettings();
	}
};