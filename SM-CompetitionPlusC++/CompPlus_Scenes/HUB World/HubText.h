#pragma once
#include "stdafx.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "include/ManiaAPI/SonicMania.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "Base.h"
#include <string>
#include <sstream>
#include "HubCore.h"

namespace CompPlus_HubText
{
    extern void UpdatePeeloutDisplay(int SlotID, CompPlus_Settings::ThreeStateBool State, int StageIndex, int Index);

    extern void UpdateAbilitySwapperDisplay(int SlotID, CompPlus_Settings::PlayerAbility Ability, int StageIndex, int Index);

    extern void UpdatePlayerSwapperDisplay(int SlotID, CompPlus_Settings::ChosenPlayer Player, int StageIndex, int Index);

    extern void UpdateSeasonDisplay(int SlotID, CompPlus_Settings::SeasonType Season, int StageIndex, int Index);

    extern void UpdateLevelSelectStatusDisplay(int State, int StageIndex, int Index, int SlotID);

    extern void UpdateSaveToggle(int SlotID, bool State, int StageIndex, int Index);

    extern void UpdateToggleDisplay(int SlotID, bool State, int StageIndex, int Index);

    extern void UpdateToggleDisplayInverted(int SlotID, bool State, int StageIndex, int Index);

    extern void UpdateGeneralDisplay(int SlotID, char* _text, int size, int StageIndex, int Index);

    extern void UpdateGeneralDisplay(SonicMania::EntityUIInfoLabel& Label3, char* _text, int size, int StageIndex, int Index);

    extern void UpdateAnnouncerDisplay(int SlotID, int StageIndex, int Index);

    extern void UpdateVictoryMethodDisplay(int SlotID, int StageIndex, int Index);

    extern void UpdateIntDisplay(int SlotID, int value, int StageIndex, int Index);

    extern void UpdateLivesDisplay(int SlotID, int StageIndex, int Index);

    extern void UpdateNumberOfRoundsDisplay(int SlotID, int StageIndex, int Index);

    extern void UpdateShoesDisplay(int SlotID, int StageIndex, int Index);

    extern void UpdateItemBoxModeDisplay(int SlotID, int StageIndex, int Index);

    extern void UpdateWinsTallyDisplay(int SlotID, int StageIndex, int Index);

    extern void UpdateVSModeDisplay(int SlotID, int StageIndex, int Index);

    extern void Init();
}