#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "SonicMania.h"

#include "ManiaLevelSelect.h"

#include "IZAPI.h"

namespace CompetitionPlus
{
	enum SceneExt : short
	{
		Scene_CompPlus_ManiaLSelect = 133,
		Scene_CompPlus_EncoreLSelect = 134,
		Scene_CompPlus_CustomLSelect = 135,
		Scene_CompPlus_PhantomLSelect = 136,
		Scene_CompPlus_SettingsMenu = 137,
		Scene_CompPlus_HubWorld = 138
	};

	extern bool RequirePointRefresh;
	extern int IdleTime;

	//extern IZAPI::StageInfo GetCurrentStage();
	//typedef void(__cdecl* IZChangeStage_Type)(const char*);
	//
	extern void IZChangeStage(const char* key);

	extern void MultiColorMods();
	extern void UpdateMenus();

	extern void OnStageLoad(IZAPI::StageInfo info);
	extern void OnStageUnload(IZAPI::StageInfo info);
};

