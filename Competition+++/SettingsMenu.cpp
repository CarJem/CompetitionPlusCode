#include "stdafx.h"
#include "SettingsMenu.h"
#include "SonicMania.h"
#include "ManiaExt.h"
#include "CompetitionPlus.h"
#include "CompSettings.h"
#include "GeneralSettings.h"
#include "PlayerConfiguration.h"

namespace CompPlus_Settings_Base
{
	using namespace SonicMania;
	using namespace CompetitionPlus;
	using namespace CompPlus_Settings_CompetitionPage;
	using namespace CompPlus_Settings_GeneralPage;
	using namespace CompPlus_Settings_PlayerConfig;

	int ViewPortID = 56;
	int GeneralPageID = 178;
	int CompetitionPageID = 69;

	int LastSceneID = 0;
	int CurrentPage = 0;


	void GetPage()
	{
		if (CurrentPage == 0)
		{			
			CompPlus_Settings_GeneralPage::UpdateSettingsMenu();
		}
		else if (CurrentPage == 1)
		{
			CompPlus_Settings_CompetitionPage::UpdateSettingsMenu();
		}
		else if (CurrentPage == 2) 
		{
			CompPlus_Settings_PlayerConfig::UpdateSettingsMenu();		
		}

	}

	void UpdateSettingsMenu()
	{
		FixSummary();
		GetPage();
	}

	void SetCurrentPage(int pageNum) 
	{
		CurrentPage = pageNum;
	}

	void CheckForPointRefresh()
	{

	}
};