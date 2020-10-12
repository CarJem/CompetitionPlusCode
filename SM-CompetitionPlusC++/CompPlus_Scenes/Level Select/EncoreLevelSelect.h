#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/PointScrolling.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "SonicMania.h"
#include "Base.h"

namespace CompPlus_EncoreLevelSelect
{
	extern void SetEncoreLSelectBGColors();
	extern void SetupEncoreLSelectMenuPoints();
	extern void SetupEncoreSelector();
	extern void OnFrame();
	extern void CheckForPointRefresh();
};
