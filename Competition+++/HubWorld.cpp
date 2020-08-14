#include "stdafx.h"
#include "HubWorld.h"
#include "ManiaExt.h"
#include "SonicMania.h"
#include "CompetitionPlus.h"
#include "Common.h"
#include <string>
#include <sstream>

namespace CompPlus_HubWorld
{
	using namespace SonicMania;
	using namespace CompetitionPlus;
	using namespace CompPlus_Common;

	int EnterLSelectButton = 67;

	int SwapPlayerController1 = 110;
	int SwapPlayerController2 = 128;
	int SwapPlayerController3 = 143;
	int SwapPlayerController4 = 158;

	//Character Swap Detection
	bool isSwapPlayer1Pressed = false;
	bool isSwapPlayer2Pressed = false;
	bool isSwapPlayer3Pressed = false;
	bool isSwapPlayer4Pressed = false;

	bool LevelSelected = false;
	bool LevelSelectedWarpSoundPlayed = false;
	int SceneLoadWaitTimer = 0;
	int SceneLoadWaitMax = 100;



	bool ChangeCharacter(int ControlSlotID, int DisplaySlotID, SonicMania::EntityPlayer* Player, bool isSwapPlayerPressed)
	{
		Entity& Controller = *GetEntityFromSceneSlot<Entity>(ControlSlotID);

		int x1 = Controller.Position.X - 32;
		int y1 = Controller.Position.Y - 32;
		int x2 = Controller.Position.X + 32;
		int y2 = Controller.Position.Y + 32;
		if (PlayerInRange(Player, x1, y1, x2, y2) && Player->Up && !isSwapPlayerPressed)
		{
			if (Player->Character == Character_Sonic && !isSwapPlayerPressed)
			{
				SonicMania::FastChangeCharacter(Player, SonicMania::Character_Tails);

				isSwapPlayerPressed = true;
			}
			else if (Player->Character == Character_Tails && !isSwapPlayerPressed)
			{
				SonicMania::FastChangeCharacter(Player, SonicMania::Character_Knux);

				isSwapPlayerPressed = true;
			}
			else if (Player->Character == Character_Knux && !isSwapPlayerPressed)
			{
				SonicMania::FastChangeCharacter(Player, SonicMania::Character_Mighty);

				isSwapPlayerPressed = true;
			}
			else if (Player->Character == Character_Mighty && !isSwapPlayerPressed)
			{
				SonicMania::FastChangeCharacter(Player, SonicMania::Character_Ray);

				isSwapPlayerPressed = true;
			}
			else if (Player->Character == Character_Ray && !isSwapPlayerPressed)
			{
				SonicMania::FastChangeCharacter(Player, SonicMania::Character_Sonic);

				isSwapPlayerPressed = true;
			}
		}
		else if (!Player->Up && isSwapPlayerPressed)
		{
			isSwapPlayerPressed = false;
		}

		return isSwapPlayerPressed;
	}



	void UpdateHUBWorld() 
	{	
		Button& ConfirmButton = *GetEntityFromSceneSlot<Button>(EnterLSelectButton);

		isSwapPlayer1Pressed = ChangeCharacter(SwapPlayerController1, 0, &Player1, isSwapPlayer1Pressed);
		isSwapPlayer2Pressed = ChangeCharacter(SwapPlayerController2, 0, &Player2, isSwapPlayer2Pressed);
		isSwapPlayer3Pressed = ChangeCharacter(SwapPlayerController3, 0, &Player3, isSwapPlayer3Pressed);
		isSwapPlayer4Pressed = ChangeCharacter(SwapPlayerController4, 0, &Player4, isSwapPlayer4Pressed);

		if (ConfirmButton.Pressed) LevelSelected = true;
		
		if (LevelSelected) EnterLevelSelectLoop(true, SceneLoadWaitTimer, SceneLoadWaitMax, LevelSelected, LevelSelectedWarpSoundPlayed);
	}

	void EnterLevelSelectLoop(bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
	{
		if (FastWarp && SceneLoadWaitTimer < 50)
		{
			SceneLoadWaitTimer = 50;
		}


		if (SceneLoadWaitTimer >= SceneLoadWaitMax)
		{
			LoadLevel_IZ("CPMLS");
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

	}
}