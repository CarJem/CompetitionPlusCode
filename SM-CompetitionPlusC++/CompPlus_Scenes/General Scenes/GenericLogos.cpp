#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/PointScrolling.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "include/ManiaAPI/SonicMania.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "CompPlus_Core/CompPlus_Patches.h"
#include "CompPlus_Extensions/Drawing.h"

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

                CompPlus_Common::SpawnFadeOut(0, 10, 3, 0, 0x000000, true, false, false, true, 14);
			}
			SceneLoadWaitTimer++;
		}
	}

	void UpdateGenericLogos(bool AllowSkip, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, int NextStageID, char* NextStageKey, bool isIZ)
	{
		CompPlus_Patches::PatchSummaryFix();
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

    int ColorStorage[5];

    void FixColors(bool Mode)
    {
        if (Mode)
        {
            ColorStorage[0] = SonicMania::GetPaletteEntry(0, 1);
            SonicMania::SetPaletteEntry(0, 1, 0x000000);

            ColorStorage[1] = SonicMania::GetPaletteEntry(0, 41);
            SonicMania::SetPaletteEntry(0, 41, 0xFF0000);

            ColorStorage[2] = SonicMania::GetPaletteEntry(0, 37);
            SonicMania::SetPaletteEntry(0, 37, 0x98C0C8);

            ColorStorage[3] = SonicMania::GetPaletteEntry(0, 40);
            SonicMania::SetPaletteEntry(0, 40, 0xFFFFFF);

        }
        else
        {
            SonicMania::SetPaletteEntry(0, 1, ColorStorage[0]);
            SonicMania::SetPaletteEntry(0, 41, ColorStorage[1]);
            SonicMania::SetPaletteEntry(0, 37, ColorStorage[2]);
            SonicMania::SetPaletteEntry(0, 40, ColorStorage[3]);
        }
    }

    int NoticeAlpha = 0;

    void OnExSEGADraw() 
    {
        FixColors(true);

        int x = 424 / 2;
        int y = 0;

        EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);
        int OldDrawOrder = RingTemp->DrawOrder;
        RingTemp->Alpha = NoticeAlpha;
        RingTemp->DrawOrder = 0;
        RingTemp->InkEffect = Ink_Alpha;

        int DrawOrder = RingTemp->DrawOrder;

        DrawRect(0, 0, 424, 48, 0x000000, (NoticeAlpha == 0 ? 0 : NoticeAlpha / 4), Ink_Alpha, true);

        Drawing::DrawMenuTextSprite("NOTICE", Vector2(x, y + 16), true, DrawOrder, 0, 0, Alignment_Center);
        Drawing::DrawDevTextSprite("THIS IS A DEMO. EVERYTHING HERE IS NOT FINAL.", Vector2(x, y + 32), true, DrawOrder, 0, 0, Alignment_Center, false);
        Drawing::DrawDevTextSprite("ANY BUGS ARE NOT REPRESENTIVE OF THE FINAL PRODUCT.", Vector2(x, y + 40), true, DrawOrder, 0, 0, Alignment_Center, false);


        FixColors(false);

        RingTemp->DrawOrder =  OldDrawOrder;

        if (NoticeAlpha > 0) NoticeAlpha -= 2;
    }

    void OnSEGADraw() 
    {
        if (NoticeAlpha < 255) NoticeAlpha += 10;
        OnExSEGADraw();
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