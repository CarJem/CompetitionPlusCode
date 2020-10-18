#include "stdafx.h"
#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/PointScrolling.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "SonicMania.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "Base.h"

namespace CompPlus_GenericLogos
{
	using namespace SonicMania;
	using namespace CompPlus_Common;

	int GR_SceneLoadWaitTimer = 0;
	int GR_SceneLoadWaitMax = 300;

	int CJ_SceneLoadWaitTimer = 0;
	int CJ_SceneLoadWaitMax = 175;

	int ATG_SceneLoadWaitTimer = 0;
	int ATG_SceneLoadWaitMax = 125;

	int IZ_SceneLoadWaitTimer = 0;
	int IZ_SceneLoadWaitMax = 375;

	int FadeWait = 50;
	int SceneSkipMin = 50;


    bool WantsToSkip = false;
	bool FadeStarted = false;



	void SceneTransition(int& SceneLoadWaitTimer, int& SceneLoadWaitMax, int LevelID, char* LevelKey, bool isIZ)
	{
		if (SceneLoadWaitTimer >= SceneLoadWaitMax + FadeWait)
		{
            if (WantsToSkip) 
            {
                LoadLevel(1);
            }
            else 
            {
                if (isIZ) LoadLevel_IZ(LevelKey);
                else LoadLevel(LevelID);
            }
			SceneLoadWaitTimer = 0;
			FadeStarted = false;
            WantsToSkip = false;
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

	void UpdateGenericLogos(bool AllowSkip, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, int NextStageID, char* NextStageKey, bool isIZ)
	{
		CompPlus_Internal::FixSummary();
		if (AllowSkip) 
		{
			if (PlayerControllers[0].A.Press || PlayerControllers[0].B.Press || PlayerControllers[0].C.Press || PlayerControllers[0].X.Press || PlayerControllers[0].Y.Press || PlayerControllers[0].Z.Press || PlayerControllers[0].Start.Press || PlayerControllers[0].Select.Press)
			{
                WantsToSkip = true;
				if (SceneLoadWaitTimer <= SceneLoadWaitMax)
				{
					if (SceneLoadWaitTimer >= SceneSkipMin) SceneLoadWaitTimer = SceneLoadWaitMax;
				}
			}
		}


		SceneTransition(SceneLoadWaitTimer, SceneLoadWaitMax, NextStageID, NextStageKey, isIZ);
	}


	int IZ_Logo_SlotID = 219;
	int IZ_Logo2_SlotID = 221;
	int IZ_Logo3_SlotID = 223;

	int IZ_LogoText_SlotID = 225;
	int IZ_LogoText2_SlotID = 114;
	int IZ_LogoText3_SlotID = 226;

	void ApplyIZEffect(int SlotID, bool isText) 
	{
		Entity& Part1 = *GetEntityFromSceneSlot<EntityUIPicture>(SlotID);

		Part1.InkEffect = Ink_Alpha;

		int _alpha = 0;

		if (IZ_SceneLoadWaitTimer >= 250)
		{
			int atMax = (IZ_SceneLoadWaitTimer * 2 >= 200 ? 200 : IZ_SceneLoadWaitTimer * 2);
			int timePassed = (IZ_SceneLoadWaitTimer - 250) * 2;
			int fadeOut = atMax - timePassed;
			_alpha = (fadeOut <= 0 ? 0 : fadeOut);
		}
		else 
		{
			_alpha = (IZ_SceneLoadWaitTimer >= 200 ? 200 : IZ_SceneLoadWaitTimer);
		}

		Part1.Alpha = _alpha;

		if (isText) 
		{
			Part1.DrawOrder = 14;
		}
	}

	void UpdateIZLogos() 
	{
		ApplyIZEffect(IZ_Logo_SlotID, false);
		ApplyIZEffect(IZ_Logo2_SlotID, false);
		ApplyIZEffect(IZ_Logo3_SlotID, true);
		ApplyIZEffect(IZ_LogoText_SlotID, true);
		ApplyIZEffect(IZ_LogoText2_SlotID, true);
		ApplyIZEffect(IZ_LogoText3_SlotID, true);

		UpdateGenericLogos(false, IZ_SceneLoadWaitTimer, IZ_SceneLoadWaitMax, 1, (char*)"", false);
	}

	void UpdateATGLogos() 
	{
		UpdateGenericLogos(true, ATG_SceneLoadWaitTimer, ATG_SceneLoadWaitMax, 0, (char*)CompPlus_Common::SMCP_Logos3, true);
	}

	void UpdateCJLogos() 
	{
		UpdateGenericLogos(true, CJ_SceneLoadWaitTimer, CJ_SceneLoadWaitMax, 0, (char*)CompPlus_Common::SMCP_Logos4, true);
	}


};