#pragma once
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/PointScrolling.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "SonicMania.h"
#include "Base.h"

namespace CompPlus_ExeLevelSelect
{

    extern void OnPreload();

    extern void SetupMenuPoints();

    extern void OnDraw();

    extern void OnFrame();

    extern void CheckForPointRefresh();
};



