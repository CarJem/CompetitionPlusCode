#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/PointScrolling.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "SonicMania.h"
#include "Base.h"

namespace CompPlus_ManiaLevelSelect
{

	extern void SetManiaLSelectBGColors();

	extern void SetupManiaLSelectMenuPoints();

	extern void SetupManiaSelector();

	extern void OnFrame();

	extern void CheckForPointRefresh();
};



