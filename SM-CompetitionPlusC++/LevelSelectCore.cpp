#include "stdafx.h"
#include "LevelSelectCore.h"
#include "ManiaModLoader.h"
#include "PointScrolling.h"
#include "ManiaExt.h"
#include "SonicMania.h"
#include "Common.h"
#include <vector>


namespace CompPlus_LevelSelectCore
{
	using namespace CompPlus_Common;

	void LevelSelectDelayLoop(int selectorID, MenuPoint level, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
	{
		if (FastWarp && SceneLoadWaitTimer < 30)
		{
			SceneLoadWaitTimer = 30;
		}


		if (SceneLoadWaitTimer >= SceneLoadWaitMax)
		{
			if (level.isIZ)
			{
				CompPlus_Common::LoadLevel_IZ(level.LevelID_IZ);
			}
			else
			{
				CompPlus_Common::LoadLevel(level.LevelID);
			}

			SceneLoadWaitTimer = 0;
			LevelSelected = false;
			LevelSelectedWarpSoundPlayed = false;
		}
		else
		{
			if (SceneLoadWaitTimer >= 30 && !LevelSelectedWarpSoundPlayed)
			{
				PlaySoundFXS("Global/SpecialWarp.wav");
				LevelSelectedWarpSoundPlayed = true;

				Entity* FXFade = SpawnObject(GetObjectIDFromType(ObjectType_FXFade), 0, Vector2(Player1.Position.X, Player1.Position.Y - 30));
				EntityFXFade* FxFadeR = (EntityFXFade*)FXFade;

				if (FastWarp) 
				{
					PlaySoundFXS("Global/SpecialWarp.wav");
					LevelSelectedWarpSoundPlayed = true;

					FxFadeR->Time = 0;
					FxFadeR->SpeedIn = 20;
					FxFadeR->Wait = 0;
					FxFadeR->SpeedOut = 0;
					FxFadeR->Color = 0x000000;
					FxFadeR->OneWay = true;
					FxFadeR->EventOnly = false;
					FxFadeR->Overhud = false;
					FxFadeR->FadeOutBlack = true;
				}
				else 
				{
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


			}
			SceneLoadWaitTimer++;
		}

		stru_26B818[0].playStatus = 0;
		Entity& selector = *GetEntityFromSceneSlot<Entity>(selectorID);
		if (selector.Visible == 0) selector.Visible = 1;
		else selector.Visible = 0;

	}

	void UniversalLSelectLoop() 
	{
		SetScreenCount(1);
	}

	void LevelSelectDelayLoop(int selectorID, int levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
	{
		if (FastWarp && SceneLoadWaitTimer < 50)
		{
			SceneLoadWaitTimer = 50;
		}


		if (SceneLoadWaitTimer >= SceneLoadWaitMax)
		{
			LoadLevel(levelID);
			SceneLoadWaitTimer = 0;
			LevelSelected = false;
			LevelSelectedWarpSoundPlayed = false;
		}
		else
		{
			if (SceneLoadWaitTimer >= 50 && !LevelSelectedWarpSoundPlayed)
			{
				PlaySoundFXS("Global/SpecialWarp.wav");
				LevelSelectedWarpSoundPlayed = true;

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

		stru_26B818[0].playStatus = 0;
		Entity& selector = *GetEntityFromSceneSlot<Entity>(selectorID);
		if (selector.Visible == 0) selector.Visible = 1;
		else selector.Visible = 0;

	}

	void LevelSelectDelayLoop(int selectorID, const char* levelID, bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
	{
		if (FastWarp && SceneLoadWaitTimer < 50)
		{
			SceneLoadWaitTimer = 50;
		}


		if (SceneLoadWaitTimer >= SceneLoadWaitMax)
		{
			LoadLevel_IZ(levelID);
			SceneLoadWaitTimer = 0;
			LevelSelected = false;
			LevelSelectedWarpSoundPlayed = false;
		}
		else
		{
			if (SceneLoadWaitTimer >= 50 && !LevelSelectedWarpSoundPlayed)
			{
				PlaySoundFXS("Global/SpecialWarp.wav");
				LevelSelectedWarpSoundPlayed = true;

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

		stru_26B818[0].playStatus = 0;
		Entity& selector = *GetEntityFromSceneSlot<Entity>(selectorID);
		if (selector.Visible == 0) selector.Visible = 1;
		else selector.Visible = 0;

	}

	void LevelSelectDelay(bool isClassic, bool& LevelSelected)
	{
		PlayMenuAcceptSoundFX(isClassic);
		LevelSelected = true;
	}

	void ResetMenuPos(int& MenuPos_X, int& MenuPos_Y, int SMenuPos_X, int SMenuPos_Y, int& LastMenuPos_X, int& LastMenuPos_Y, bool& SwapLevelSelect)
	{
		MenuPos_X = SMenuPos_X;
		MenuPos_Y = SMenuPos_Y;

		LastMenuPos_X = SMenuPos_X;
		LastMenuPos_Y = SMenuPos_Y;

		SwapLevelSelect = false;
	}

	void ResetMenuPos(int& MenuPos_X, int& MenuPos_Y, int& LastMenuPos_X, int& LastMenuPos_Y, bool& SwapLevelSelect)
	{
		MenuPos_X = 0;
		MenuPos_Y = 0;

		LastMenuPos_X = 0;
		LastMenuPos_Y = 0;

		SwapLevelSelect = false;
	}

	void UpdateLevelSelectSelection(int& MenuPos_X, int& MenuPos_Y, int& MenuMax_X, int& MenuMax_Y, MenuPoint **MenuPoints)
	{
		for (int y = 0; y < MenuMax_Y; y++)
		{
			for (int x = 0; x < MenuMax_X; x++)
			{
				if ((y != MenuPos_Y || x != MenuPos_X) && !MenuPoints[y][x].isBlank)
				{
					EntityUIPicture& object = *MenuPoints[y][x].Object;
					object.AnimData.CurrentFrame = 0;
				}
			}
		}

		if (!MenuPoints[MenuPos_Y][MenuPos_X].isBlank)
		{
			EntityUIPicture& object = *MenuPoints[MenuPos_Y][MenuPos_X].Object;
			object.AnimData.CurrentFrame = 1;
		}


	}

	void UpdateLevelSelectScroll(int& MenuPos_X, int& MenuPos_Y, int& LastMenuPos_X, int& LastMenuPos_Y, bool& UpdateMenuScroll, int& UIControlSlot, int& SelectorImage, MenuPoint** MenuPoints)
	{
		if (MenuPoints[MenuPos_Y][MenuPos_X].isBlank)
		{
			MenuPos_X = MenuPoints[MenuPos_Y][MenuPos_X].RedirectX;
			MenuPos_Y = MenuPoints[MenuPos_Y][MenuPos_X].RedirectY;
		}

		short x1 = MenuPoints[MenuPos_Y][MenuPos_X].Position.X;
		short y1 = MenuPoints[MenuPos_Y][MenuPos_X].Position.Y;

		short x2 = MenuPoints[LastMenuPos_Y][LastMenuPos_X].Position.X;
		short y2 = MenuPoints[LastMenuPos_Y][LastMenuPos_X].Position.Y;

		ScrollToPosition(x1, y1, x2, y2, UIControlSlot, UpdateMenuScroll);
		ScrollToPosition(x1, y1, x2, y2, SelectorImage, UpdateMenuScroll);
		UpdateMenuScroll = false;
	}

	void UpdateLastPos(int& LastMenuPos_X, int& LastMenuPos_Y, int& MenuPos_X, int& MenuPos_Y)
	{
		LastMenuPos_Y = MenuPos_Y;
		LastMenuPos_X = MenuPos_X;
	}
};