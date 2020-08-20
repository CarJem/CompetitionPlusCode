#include "stdafx.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "SonicMania.h"
#include "Common.h"

namespace CompPlus_GenericLogos
{
	using namespace SonicMania;
	using namespace CompPlus_Common;

	int SceneLoadWaitTimer = 0;
	int SceneLoadWaitMax = 300;
	int FadeWait = 50;
	int SceneSkipMin = (SceneLoadWaitMax / 3);

	bool FadeStarted = false;

	void SceneTransition(int LevelID, char* LevelKey, bool isIZ)
	{
		if (SceneLoadWaitTimer >= SceneLoadWaitMax + FadeWait)
		{
			if (isIZ) LoadLevel_IZ(LevelKey);
			else LoadLevel(LevelID);
			SceneLoadWaitTimer = 0;
			FadeStarted = false;
		}
		else
		{
			if (SceneLoadWaitTimer >= SceneLoadWaitMax && !FadeStarted)
			{
				FadeStarted = true;

				Entity* FXFade = SpawnObject(GetObjectIDFromType(ObjectType_FXFade), 0, Vector2(Player1.Position.X, Player1.Position.Y - 30));
				EntityFXFade* FxFadeR = (EntityFXFade*)FXFade;

				FxFadeR->Time = 0;
				FxFadeR->SpeedIn = 10;
				FxFadeR->Wait = 3;
				FxFadeR->SpeedOut = 0;
				FxFadeR->Color = 0x000000;
				FxFadeR->OneWay = true;
				FxFadeR->EventOnly = false;
				FxFadeR->Overhud = false;
				FxFadeR->FadeOutBlack = true;


			}
			SceneLoadWaitTimer++;
		}
	}

	void UpdateGenericLogos(int NextStageID, char* NextStageKey, bool isIZ)
	{
		CompPlus_Common::FixSummary();
		if (PlayerControllers[0].A.Press || PlayerControllers[0].B.Press || PlayerControllers[0].C.Press || PlayerControllers[0].X.Press || PlayerControllers[0].Y.Press || PlayerControllers[0].Z.Press || PlayerControllers[0].Start.Press || PlayerControllers[0].Select.Press)
		{
			if (SceneLoadWaitTimer >= SceneSkipMin) SceneLoadWaitTimer = SceneLoadWaitMax;
		}

		SceneTransition(NextStageID, NextStageKey, isIZ);
	}
};