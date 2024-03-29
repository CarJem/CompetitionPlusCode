#include "stdafx.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "include/ManiaAPI/SonicMania.h"
#include "HubSettings.h"
#include "HubControllers.h"
#include "HubText.h"
#include "HubCore.h"

namespace CompPlus_HubSettings
{
    using namespace SonicMania;
    using namespace CompPlus_Common;
    using namespace CompPlus_HubCore;
    using namespace CompPlus_HubControllers;
    using namespace CompPlus_HubText;

    bool DummySetting = false;
    int DummyTextSlot = 217;
    int DummyControllerSlot = 582;

    bool CreditsSelected = false;
    bool ExitSelected = false;

    int ExitRingSlot = 866;

    bool LevelSelected = false;
    bool LevelSelectedWarpSoundPlayed = false;
    int SceneLoadWaitTimer = 0;
    int SceneLoadWaitMax = 100;

    int SwapPlayerController_P1 = 110;
    int SwapAbilityController_P1 = 115;
    int PeeloutController_P1 = 121;
    int DynCamController_P1 = 790;

    int SwapPlayerController_P2 = 869;
    int SwapAbilityController_P2 = 868;
    int PeeloutController_P2 = 871;
    int DynCamController_P2 = 870;

    int SwapPlayerController_P3 = 875;
    int SwapAbilityController_P3 = 874;
    int PeeloutController_P3 = 877;
    int DynCamController_P3 = 876;

    int SwapPlayerController_P4 = 881;
    int SwapAbilityController_P4 = 880;
    int PeeloutController_P4 = 883;
    int DynCamController_P4 = 882;

    int PlayerSettingsWarpEnterance = 797;

    int PlayerSettingsDestination_P1 = 817;
    int PlayerSettingsDestination_P2 = 819;
    int PlayerSettingsDestination_P3 = 793;
    int PlayerSettingsDestination_P4 = 799;

    int DropDashController = 117;
    int InstaSheildController = 119;
    int DevModeText = 138;
    int DebugModeText = 139;
    int DevModeController = 184;
    int DebugModeController = 185;

    int EncoreVapeMusicController = 977;
    int EncoreVapeMusicText = 982;

    int SpotlightModeController = 975;
    int SpotlightModeText = 983;

    int SeasonSwitchController = 976;
    int SeasonSwitchText = 993;

    int TailsFlightCancelController = 972;
    int TailsFlightCancelText = 987;

    int DynCamToggleText_P1 = 845;
    int DynCamToggleText_P2 = 826;
    int DynCamToggleText_P3 = 839;
    int DynCamToggleText_P4 = 827;

    int PeeloutToggleText_P1 = 143;
    int PeeloutToggleText_P2 = 135;
    int PeeloutToggleText_P3 = 129;
    int PeeloutToggleText_P4 = 128;

    int SwapPlayerText_P1 = 203;
    int SwapPlayerText_P2 = 125;
    int SwapPlayerText_P3 = 133;
    int SwapPlayerText_P4 = 126;

    int SwapAbilityText_P1 = 141;
    int SwapAbilityText_P2 = 131;
    int SwapAbilityText_P3 = 140;
    int SwapAbilityText_P4 = 137;

    int DropDashToggleText = 144;
    int InstaSheildToggleText = 142;

    int AnnouncerTypeController = 183;
    int InfiniteRoundsToggleController = 181;
    int VictoryMethodSwapperController = 182;
    int LivesNUDController = 178;
    int RemoveTimeToggleController = 179;
    int HurryTimerToggleController = 475;
    int ItemBoxModeController = 180;
    int NumberOfRoundsController = 352;
    int StrechIntensityNUDController = 479;
    int ShoesModNUDController = 974;
    int PlayerSettingsSaveModeController = 973;

    int AnnouncerTypeText = 132;
    int InfiniteRoundsToggleText = 136;
    int VictoryMethodSwapperText = 134;
    int LivesNUDText = 127;
    int RemoveTimeToggleText = 130;
    int HurryTimerToggleText = 478;
    int ItemBoxModeText = 206;
    int NumberOfRoundsText = 351;
    int StrechIntensityText = 480;
    int ShoesModText = 1020;
    int PlayerSettingsSaveModeText = 1021;

    int DeveloperSettingsBlockadeSlotID = 224;
    bool DeveloperWallInit = false;
    Vector2 DeveloperWallInitalPosition;


    void DeveloperSettingsBlockcade()
    {
        SonicMania::Entity& Wall = *GetEntityFromSceneSlot<Entity>(DeveloperSettingsBlockadeSlotID);

        if (!DeveloperWallInit)
        {
            DeveloperWallInitalPosition = Wall.Position;
            DeveloperWallInit = true;
        }

        if (CompPlus_Settings::EnableDevMode)
        {
            Wall.Position.X = -1000;
            Wall.Position.Y = -1000;
        }
        else
        {
            Wall.Position.X = DeveloperWallInitalPosition.X;
            Wall.Position.Y = DeveloperWallInitalPosition.Y;
        }
    }

    int UpdateHUBSettingDisplays()
    {
        int StringIndex = 0;

        //Dummy Display
        UpdateToggleDisplay(DummyTextSlot, DummySetting, 1, StringIndex);
        StringIndex++;

        //Character Select Display
        UpdatePlayerSwapperDisplay(SwapPlayerText_P1, CompPlus_Settings::Player1ChosenPlayer, 1, StringIndex);
        StringIndex++;
        UpdatePlayerSwapperDisplay(SwapPlayerText_P2, CompPlus_Settings::Player2ChosenPlayer, 1, StringIndex);
        StringIndex++;
        UpdatePlayerSwapperDisplay(SwapPlayerText_P3, CompPlus_Settings::Player3ChosenPlayer, 1, StringIndex);
        StringIndex++;
        UpdatePlayerSwapperDisplay(SwapPlayerText_P4, CompPlus_Settings::Player4ChosenPlayer, 1, StringIndex);
        StringIndex++;
        //Player Ability Display
        UpdateAbilitySwapperDisplay(SwapAbilityText_P1,  CompPlus_Settings::Player1AbilitySet, 1, StringIndex);
        StringIndex++;
        UpdateAbilitySwapperDisplay(SwapAbilityText_P2,  CompPlus_Settings::Player2AbilitySet, 1, StringIndex);
        StringIndex++;
        UpdateAbilitySwapperDisplay(SwapAbilityText_P3,  CompPlus_Settings::Player3AbilitySet, 1, StringIndex);
        StringIndex++;
        UpdateAbilitySwapperDisplay(SwapAbilityText_P4, CompPlus_Settings::Player4AbilitySet, 1, StringIndex);
        StringIndex++;
        //DynCam Display
        UpdateToggleDisplay(DynCamToggleText_P1, CompPlus_Settings::Player1DynCam, 1, StringIndex);
        StringIndex++;
        UpdateToggleDisplay(DynCamToggleText_P2, CompPlus_Settings::Player2DynCam, 1, StringIndex);
        StringIndex++;
        UpdateToggleDisplay(DynCamToggleText_P3, CompPlus_Settings::Player3DynCam, 1, StringIndex);
        StringIndex++;
        UpdateToggleDisplay(DynCamToggleText_P4, CompPlus_Settings::Player4DynCam, 1, StringIndex);
        StringIndex++;
        //Peelout Ability Display
        UpdatePeeloutDisplay(PeeloutToggleText_P1, CompPlus_Settings::Player1PeeloutAbility, 1, StringIndex);
        StringIndex++;
        UpdatePeeloutDisplay(PeeloutToggleText_P2, CompPlus_Settings::Player2PeeloutAbility, 1, StringIndex);
        StringIndex++;
        UpdatePeeloutDisplay(PeeloutToggleText_P3, CompPlus_Settings::Player3PeeloutAbility, 1, StringIndex);
        StringIndex++;
        UpdatePeeloutDisplay(PeeloutToggleText_P4,CompPlus_Settings::Player4PeeloutAbility, 1, StringIndex);
        StringIndex++;
        //Dropdash Display
        UpdateToggleDisplay(DropDashToggleText, CompPlus_Settings::DropdashAbility, 1, StringIndex);
        StringIndex++;
        //Insta-Sheild Display
        UpdateToggleDisplay(InstaSheildToggleText,  CompPlus_Settings::InstaSheildAbility, 1, StringIndex);
        StringIndex++;
        //Debug Mode Display
        UpdateToggleDisplay(DebugModeText, CompPlus_Settings::EnableDebugMode, 1, StringIndex);
        StringIndex++;
        //Dev Mode Display
        UpdateToggleDisplay(DevModeText,  CompPlus_Settings::EnableDevMode, 1, StringIndex);
        StringIndex++;
        //Lives Display
        UpdateLivesDisplay(LivesNUDText, 1, StringIndex);
        StringIndex++;
        //Remove Time Display
        UpdateToggleDisplay(RemoveTimeToggleText,  CompPlus_Settings::TimeLimit, 1, StringIndex);
        StringIndex++;
        //Hurry Timer Display
        UpdateToggleDisplayInverted(HurryTimerToggleText,  CompPlus_Settings::NoHurryUpTimer, 1, StringIndex);
        StringIndex++;
        //Infinite Rounds Display
        UpdateToggleDisplay(InfiniteRoundsToggleText,  CompPlus_Settings::EndlessRounds, 1, StringIndex);
        StringIndex++;
        //Announcer Type Display
        UpdateAnnouncerDisplay(AnnouncerTypeText, 1, StringIndex);
        StringIndex++;
        //Victory Method Display
        UpdateVictoryMethodDisplay(VictoryMethodSwapperText, 1, StringIndex);
        StringIndex++;
        //Item Box Mode Type Display
        UpdateItemBoxModeDisplay(ItemBoxModeText, 1, StringIndex);
        StringIndex++;
        //Number Of Rounds Display
        UpdateNumberOfRoundsDisplay(NumberOfRoundsText, 1, StringIndex);
        StringIndex++;
        //Strech Internsity Display
        UpdateIntDisplay(StrechIntensityText, CompPlus_Settings::StrechEffectIntensity, 1, StringIndex);
        StringIndex++;
        //Encore Vape Music Display
        UpdateToggleDisplay(EncoreVapeMusicText, CompPlus_Settings::UseEncoreVapeMusic, 1, StringIndex);
        StringIndex++;
        //Tails Flight Drop Display
        UpdateToggleDisplay(TailsFlightCancelText, CompPlus_Settings::TailsFlightCancel, 1, StringIndex);
        StringIndex++;
        //Spotlight Mode Display
        UpdateToggleDisplay(SpotlightModeText, CompPlus_Settings::SpotLightChallenge, 1, StringIndex);
        StringIndex++;
        //Season Switch Display
        UpdateSeasonDisplay(SeasonSwitchText, CompPlus_Settings::CurrentSeason, 1, StringIndex);
        StringIndex++;
        //Speed Shoes Mod Display
        UpdateShoesDisplay(ShoesModText, 1, StringIndex);
        StringIndex++;
        //Player Settings Save Mode Display
        UpdateSaveToggle(PlayerSettingsSaveModeText, CompPlus_Settings::PlayerSettingsSaveMode, 1, StringIndex);
        StringIndex++;

        return StringIndex;
    }

    void CheckSettings()
    {
        //Dummy Controller
        bool DummyStatus = ToggleController(DummyControllerSlot, DummySetting);
        if (DummyStatus != DummySetting) DummySetting = DummyStatus;

        //Debug Mode Toggle
        bool DebugStatus = ToggleController(DebugModeController, CompPlus_Settings::EnableDebugMode);
        if (DebugStatus != CompPlus_Settings::EnableDebugMode) CompPlus_Settings::EnableDebugMode = DebugStatus;

        //Dev Mode Toggle
        bool DevStatus = ToggleController(DevModeController, CompPlus_Settings::EnableDevMode);
        if (DevStatus != CompPlus_Settings::EnableDevMode) CompPlus_Settings::EnableDevMode = DevStatus;

        //Insta-Sheild Toggle
        bool InstaSheildStatus = ToggleController(InstaSheildController, CompPlus_Settings::InstaSheildAbility);
        if (InstaSheildStatus != CompPlus_Settings::InstaSheildAbility) CompPlus_Settings::SetInstaSheildAbility(InstaSheildStatus);

        //Dropdash Toggle
        bool DropdashStatus = ToggleController(DropDashController, CompPlus_Settings::DropdashAbility);
        if (DropdashStatus != CompPlus_Settings::DropdashAbility) CompPlus_Settings::SetDropdashAbility(DropdashStatus);

        //Character NUD
        bool isUp = false;
        int CharacterP1Status = SingleUpDownController(SwapPlayerController_P1, (int)CompPlus_Settings::Player1ChosenPlayer, 1, 5, isUp);
        if (CharacterP1Status != (int)CompPlus_Settings::Player1ChosenPlayer) ChangeCharacter(1, (CompPlus_Settings::ChosenPlayer)CharacterP1Status);
        int CharacterP2Status = SingleUpDownController(SwapPlayerController_P2, (int)CompPlus_Settings::Player2ChosenPlayer, 1, 5, isUp);
        if (CharacterP2Status != (int)CompPlus_Settings::Player2ChosenPlayer) ChangeCharacter(2, (CompPlus_Settings::ChosenPlayer)CharacterP2Status);
        int CharacterP3Status = SingleUpDownController(SwapPlayerController_P3, (int)CompPlus_Settings::Player3ChosenPlayer, 1, 5, isUp);
        if (CharacterP3Status != (int)CompPlus_Settings::Player3ChosenPlayer) ChangeCharacter(3, (CompPlus_Settings::ChosenPlayer)CharacterP3Status);
        int CharacterP4Status = SingleUpDownController(SwapPlayerController_P4, (int)CompPlus_Settings::Player4ChosenPlayer, 1, 5, isUp);
        if (CharacterP4Status != (int)CompPlus_Settings::Player4ChosenPlayer) ChangeCharacter(4, (CompPlus_Settings::ChosenPlayer)CharacterP4Status);

        //Ability NUD
        int AbilityP1Status = SingleUpDownController(SwapAbilityController_P1, (int)CompPlus_Settings::Player1AbilitySet, 0, 5, isUp);
        if (AbilityP1Status != (int)CompPlus_Settings::Player1AbilitySet) ChangeAbility(1, (CompPlus_Settings::PlayerAbility)AbilityP1Status, isUp);
        int AbilityP2Status = SingleUpDownController(SwapAbilityController_P2, (int)CompPlus_Settings::Player2AbilitySet, 0, 5, isUp);
        if (AbilityP2Status != (int)CompPlus_Settings::Player2AbilitySet) ChangeAbility(2, (CompPlus_Settings::PlayerAbility)AbilityP2Status, isUp);
        int AbilityP3Status = SingleUpDownController(SwapAbilityController_P3, (int)CompPlus_Settings::Player3AbilitySet, 0, 5, isUp);
        if (AbilityP3Status != (int)CompPlus_Settings::Player3AbilitySet) ChangeAbility(3, (CompPlus_Settings::PlayerAbility)AbilityP3Status, isUp);
        int AbilityP4Status = SingleUpDownController(SwapAbilityController_P4, (int)CompPlus_Settings::Player4AbilitySet, 0, 5, isUp);
        if (AbilityP4Status != (int)CompPlus_Settings::Player4AbilitySet) ChangeAbility(4, (CompPlus_Settings::PlayerAbility)AbilityP4Status, isUp);

        //DynCam Toggle
        bool DynCamStatus_P1 = SingleUpDownController(DynCamController_P1, (int)CompPlus_Settings::Player1DynCam, 0, 1, isUp);
        if (DynCamStatus_P1 != (int)CompPlus_Settings::Player1DynCam) CompPlus_Settings::SetDynCamMode(1, DynCamStatus_P1);
        bool DynCamStatus_P2 = SingleUpDownController(DynCamController_P2, (int)CompPlus_Settings::Player2DynCam, 0, 1, isUp);
        if (DynCamStatus_P2 != (int)CompPlus_Settings::Player2DynCam) CompPlus_Settings::SetDynCamMode(2, DynCamStatus_P2);
        bool DynCamStatus_P3 = SingleUpDownController(DynCamController_P3, (int)CompPlus_Settings::Player3DynCam, 0, 1, isUp);
        if (DynCamStatus_P3 != (int)CompPlus_Settings::Player3DynCam) CompPlus_Settings::SetDynCamMode(3, DynCamStatus_P3);
        bool DynCamStatus_P4 = SingleUpDownController(DynCamController_P4, (int)CompPlus_Settings::Player4DynCam, 0, 1, isUp);
        if (DynCamStatus_P4 != (int)CompPlus_Settings::Player4DynCam) CompPlus_Settings::SetDynCamMode(4, DynCamStatus_P4);

        //Peelout Toggle
        int PeeloutStateP1Status = SingleUpDownController(PeeloutController_P1, (int)CompPlus_Settings::Player1PeeloutAbility, 0, 2, isUp);
        if (PeeloutStateP1Status != (int)CompPlus_Settings::Player1PeeloutAbility) CompPlus_Settings::SetPeeloutAbility(1, (CompPlus_Settings::ThreeStateBool)PeeloutStateP1Status);
        int PeeloutStateP2Status = SingleUpDownController(PeeloutController_P2, (int)CompPlus_Settings::Player2PeeloutAbility, 0, 2, isUp);
        if (PeeloutStateP2Status != (int)CompPlus_Settings::Player2PeeloutAbility) CompPlus_Settings::SetPeeloutAbility(2, (CompPlus_Settings::ThreeStateBool)PeeloutStateP2Status);
        int PeeloutStateP3Status = SingleUpDownController(PeeloutController_P3, (int)CompPlus_Settings::Player3PeeloutAbility, 0, 2, isUp);
        if (PeeloutStateP3Status != (int)CompPlus_Settings::Player3PeeloutAbility) CompPlus_Settings::SetPeeloutAbility(3, (CompPlus_Settings::ThreeStateBool)PeeloutStateP3Status);
        int PeeloutStateP4Status = SingleUpDownController(PeeloutController_P4, (int)CompPlus_Settings::Player4PeeloutAbility, 0, 2, isUp);
        if (PeeloutStateP4Status != (int)CompPlus_Settings::Player4PeeloutAbility) CompPlus_Settings::SetPeeloutAbility(4, (CompPlus_Settings::ThreeStateBool)PeeloutStateP4Status);

        //Inital Lives NUD
        int LivesStatus = SingleUpDownController(LivesNUDController, CompPlus_Settings::InitalLives, 1, 100);
        if (LivesStatus != CompPlus_Settings::InitalLives) CompPlus_Settings::SetInitalLives(LivesStatus);

        //Strech Effect Intensity NUD
        int StrechStatus = SingleUpDownController(StrechIntensityNUDController, CompPlus_Settings::StrechEffectIntensity, 1, 10);
        if (StrechStatus != CompPlus_Settings::StrechEffectIntensity) CompPlus_Settings::SetStrechIntensity(StrechStatus);

        //Tails Flight Cancel Toggle
        bool TailsFlightCancelStatus = ToggleController(TailsFlightCancelController, CompPlus_Settings::TailsFlightCancel);
        if (TailsFlightCancelStatus != CompPlus_Settings::TailsFlightCancel) CompPlus_Settings::SetTailsFlightCancel(TailsFlightCancelStatus);

        //Encore Vape Music Toggle
        bool VapeStatus = ToggleController(EncoreVapeMusicController, CompPlus_Settings::UseEncoreVapeMusic);
        if (VapeStatus != CompPlus_Settings::UseEncoreVapeMusic) CompPlus_Settings::SetEncoreVapeMusic(VapeStatus);

        //Spotlight Mode Toggle
        bool SpotLightStatus = ToggleController(SpotlightModeController, CompPlus_Settings::SpotLightChallenge);
        if (SpotLightStatus != CompPlus_Settings::SpotLightChallenge) CompPlus_Settings::SetSpotlightChallenge(SpotLightStatus);

        //Season Switch NUD
        int SeasonalStatus = SingleUpDownController(SeasonSwitchController, CompPlus_Settings::CurrentSeason, 0, 1);
        if (SeasonalStatus != CompPlus_Settings::CurrentSeason) CompPlus_Settings::SetSeason((CompPlus_Settings::SeasonType)SeasonalStatus);

        //Infinite Time Toggle
        bool InfiniteTimeStatus = ToggleController(RemoveTimeToggleController, CompPlus_Settings::TimeLimit);
        if (InfiniteTimeStatus != CompPlus_Settings::TimeLimit) CompPlus_Settings::SetTimeLimit(InfiniteTimeStatus);

        //Hurry Timer Toggle
        bool HurryTimerStatus = ToggleController(HurryTimerToggleController, CompPlus_Settings::NoHurryUpTimer);
        if (HurryTimerStatus != CompPlus_Settings::NoHurryUpTimer) CompPlus_Settings::SetHurryTimer(HurryTimerStatus);

        //Infinite Rounds Toggle
        bool InfiniteRoundsStatus = ToggleController(InfiniteRoundsToggleController, CompPlus_Settings::EndlessRounds);
        if (InfiniteRoundsStatus != CompPlus_Settings::EndlessRounds) CompPlus_Settings::SetEndlessRounds(InfiniteRoundsStatus);

        //Announcer Type NUD
        int AnnouncerTypeStatus = SingleUpDownController(AnnouncerTypeController, (int)CompPlus_Settings::CurrentAnnouncer, 0, CompPlus_Settings::NumberOfAnnouncers - 1);
        if (AnnouncerTypeStatus != (int)CompPlus_Settings::CurrentAnnouncer) CompPlus_Settings::SetAnnouncer((CompPlus_Settings::AnnouncerType)AnnouncerTypeStatus);

        //Victory Type NUD
        int VictoryTypeStatus = SingleUpDownController(VictoryMethodSwapperController, (int)CompPlus_Settings::VictoryStyle, 0, 6);
        if (VictoryTypeStatus != (int)CompPlus_Settings::VictoryStyle) CompPlus_Settings::SetVictoryMethod((CompPlus_Settings::VictoryMode)VictoryTypeStatus);

        //Item Box Config NUD
        int ItemBoxStatus = SingleUpDownController(ItemBoxModeController, (int)CompPlus_Settings::MonitorTypes, 0, 2);
        if (ItemBoxStatus != (int)CompPlus_Settings::MonitorTypes) CompPlus_Settings::SetMonitorMode((CompPlus_Settings::ItemsConfig)ItemBoxStatus);

        //Number of Rounds NUD
        int NumberOfRoundsStatus = SingleUpDownController(NumberOfRoundsController, (int)CompPlus_Settings::NumberOfRounds, 2, 99);
        if (NumberOfRoundsStatus != (int)CompPlus_Settings::NumberOfRounds) CompPlus_Settings::SetNumberOfRounds(NumberOfRoundsStatus);

        //Speed Shoes Mode NUD
        int SpeedShoesModStatus = SingleUpDownController(ShoesModNUDController, (int)CompPlus_Settings::SpeedShoesMode, 0, 4);
        if (SpeedShoesModStatus != (int)CompPlus_Settings::SpeedShoesMode) CompPlus_Settings::SetSpeedShoesMode((CompPlus_Settings::SpeedShoesModification)SpeedShoesModStatus);

        //Player Settings Save NUD
        bool PlayerSettingsSaveModeStatus = ToggleController(PlayerSettingsSaveModeController, CompPlus_Settings::PlayerSettingsSaveMode);
        if (PlayerSettingsSaveModeStatus != CompPlus_Settings::PlayerSettingsSaveMode) CompPlus_Settings::SetPlayerSettingsSaveMode(PlayerSettingsSaveModeStatus);

        if (SettingWaitTimer != 0) SettingWaitTimer = SettingWaitTimer - 1;
    }

    void PlayerSettingsWarpSingle(SonicMania::EntityPlayer* Player, int ID) 
    {
        SonicMania::Entity& SettingsEnterance = *GetEntityFromSceneSlot<Entity>(PlayerSettingsWarpEnterance);

        SonicMania::Entity& P1_Destination = *GetEntityFromSceneSlot<Entity>(PlayerSettingsDestination_P1);
        SonicMania::Entity& P2_Destination = *GetEntityFromSceneSlot<Entity>(PlayerSettingsDestination_P2);
        SonicMania::Entity& P3_Destination = *GetEntityFromSceneSlot<Entity>(PlayerSettingsDestination_P3);
        SonicMania::Entity& P4_Destination = *GetEntityFromSceneSlot<Entity>(PlayerSettingsDestination_P4);

        if (Player->InRange(P1_Destination.Position.X - 16, P1_Destination.Position.Y - 16, P1_Destination.Position.X + 16, P1_Destination.Position.Y + 16))
        {
            WarpWithCamera(*Player, SettingsEnterance.Position.X - 32, SettingsEnterance.Position.Y);
        }
        if (Player->InRange(P2_Destination.Position.X - 16, P2_Destination.Position.Y - 16, P2_Destination.Position.X + 16, P2_Destination.Position.Y + 16))
        {
            WarpWithCamera(*Player, SettingsEnterance.Position.X - 32, SettingsEnterance.Position.Y);
        }
        if (Player->InRange(P3_Destination.Position.X - 16, P3_Destination.Position.Y - 16, P3_Destination.Position.X + 16, P3_Destination.Position.Y + 16))
        {
            WarpWithCamera(*Player, SettingsEnterance.Position.X - 32, SettingsEnterance.Position.Y);
        }
        if (Player->InRange(P4_Destination.Position.X - 16, P4_Destination.Position.Y - 16, P4_Destination.Position.X + 16, P4_Destination.Position.Y + 16))
        {
            WarpWithCamera(*Player, SettingsEnterance.Position.X - 32, SettingsEnterance.Position.Y);
        }
        if (Player->InRange(SettingsEnterance.Position.X - 16, SettingsEnterance.Position.Y - 16, SettingsEnterance.Position.X + 16, SettingsEnterance.Position.Y + 16))
        {
            if (ID == 1) WarpWithCamera(*Player, P1_Destination.Position.X + 32, P1_Destination.Position.Y);
            else if (ID == 2) WarpWithCamera(*Player, P2_Destination.Position.X + 32, P2_Destination.Position.Y);
            else if (ID == 3) WarpWithCamera(*Player, P3_Destination.Position.X + 32, P3_Destination.Position.Y);
            else if (ID == 4) WarpWithCamera(*Player, P4_Destination.Position.X + 32, P4_Destination.Position.Y);
        }
    }

    void PlayerSettingsWarp() 
    {
        PlayerSettingsWarpSingle(&Player1, 1);
        PlayerSettingsWarpSingle(&Player2, 2);
        PlayerSettingsWarpSingle(&Player3, 3);
        PlayerSettingsWarpSingle(&Player4, 4);
    }

    void SceneWarp()
    {
        int x1_credits = 2977;
        int y1_credits = 1228;
        int x2_credits = 3100;
        int y2_credits = 1407;

        int x1_exit = 127;
        int y1_exit = 895;
        int x2_exit = 191;
        int y2_exit = 1039;

        int ExitCount = 0;
        int CreditsCount = 0;

        int NumberOfPlayers = (SonicMania::Options->CompetitionSession.inMatch == 1 ? SonicMania::Options->CompetitionSession.NumberOfPlayers : 1);

        if (SonicMania::Player1.Camera != nullptr)
        {
            bool isPlayerInRangeOfCredits = Player1.InRange(x1_credits, y1_credits, x2_credits, y2_credits);
            bool isPlayerInRangeOfExit = Player1.InRange(x1_exit, y1_exit, x2_exit, y2_exit);
            if (isPlayerInRangeOfCredits) CreditsCount += 1;
            if (isPlayerInRangeOfExit) ExitCount += 1;
        }
        if (SonicMania::Player2.Camera != nullptr)
        {
            bool isPlayerInRangeOfCredits = Player2.InRange(x1_credits, y1_credits, x2_credits, y2_credits);
            bool isPlayerInRangeOfExit = Player2.InRange(x1_exit, y1_exit, x2_exit, y2_exit);
            if (isPlayerInRangeOfCredits) CreditsCount += 1;
            if (isPlayerInRangeOfExit) ExitCount += 1;
        }
        if (SonicMania::Player3.Camera != nullptr)
        {
            bool isPlayerInRangeOfCredits = Player3.InRange(x1_credits, y1_credits, x2_credits, y2_credits);
            bool isPlayerInRangeOfExit = Player3.InRange(x1_exit, y1_exit, x2_exit, y2_exit);
            if (isPlayerInRangeOfCredits) CreditsCount += 1;
            if (isPlayerInRangeOfExit) ExitCount += 1;
        }
        if (SonicMania::Player4.Camera != nullptr)
        {
            bool isPlayerInRangeOfCredits = Player4.InRange(x1_credits, y1_credits, x2_credits, y2_credits);
            bool isPlayerInRangeOfExit = Player4.InRange(x1_exit, y1_exit, x2_exit, y2_exit);
            if (isPlayerInRangeOfCredits) CreditsCount += 1;
            if (isPlayerInRangeOfExit) ExitCount += 1;
        }

        SpecialRing& ExitRing = *SonicMania::GetEntityFromSceneSlot<SpecialRing>(ExitRingSlot);


        if (CreditsCount >= NumberOfPlayers && !CreditsSelected) 
        {
            CreditsSelected = true;
        }

        if (ExitCount >= NumberOfPlayers)
        {
            ExitRing.Enabled = true;
        }
        else 
        {
            ExitRing.Enabled = false;
        }
        
        if (ExitRing.TriggeredState == 2 && !ExitSelected)
        {
            ExitSelected = true;
        }
        
    }

    void ExitWarpLoop(bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
    {
        if (FastWarp && SceneLoadWaitTimer < 50)
        {
            SceneLoadWaitTimer = 50;
        }

        if (SceneLoadWaitTimer >= SceneLoadWaitMax)
        {
            SceneLoadWaitTimer = 0;
            LevelSelected = false;
            LevelSelectedWarpSoundPlayed = false;
            if (SonicMania::Options->CompetitionSession.inMatch == 1) 
            {
                CompPlus_HubCore::ReturnDestination = CompPlus_HubCore::HubPlace_Settings;
                CompPlus_Common::LoadHUBWorld();
            }
            else 
            {
                CompPlus_Common::LoadLevel(2);
            }
        }
        else
        {
            if (SceneLoadWaitTimer >= 50 && !LevelSelectedWarpSoundPlayed)
            {
                SonicMania::PlaySoundFXS(CompPlus_Common::SFX_SpecialWarp);
                LevelSelectedWarpSoundPlayed = true;

                CompPlus_Common::SpawnFadeOut(0, 10, 3, 0, 0x000000, true, false, false, true, 14);
            }
            SceneLoadWaitTimer++;
        }

        SonicMania::stru_26B818[0].playStatus = 0;

    }

    void CreditsWarpLoop(bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
    {
        if (FastWarp && SceneLoadWaitTimer < 50)
        {
            SceneLoadWaitTimer = 50;
        }

        if (SceneLoadWaitTimer >= SceneLoadWaitMax)
        {
            SceneLoadWaitTimer = 0;
            LevelSelected = false;
            LevelSelectedWarpSoundPlayed = false;
            CompPlus_Common::LoadLevel_IZ(CompPlus_Common::SMCP_Credits);
        }
        else
        {
            if (SceneLoadWaitTimer >= 50 && !LevelSelectedWarpSoundPlayed)
            {
                SonicMania::PlaySoundFXS(CompPlus_Common::SFX_SpecialWarp);
                LevelSelectedWarpSoundPlayed = true;

                CompPlus_Common::SpawnFadeOut(0, 10, 3, 0, 0x000000, true, false, false, true, 14);
            }
            SceneLoadWaitTimer++;
        }

        SonicMania::stru_26B818[0].playStatus = 0;

    }

    void OnFrame() 
    {
        CompPlus_HubCore::SetHUBVisualSettings();
     
        if (SonicMania::Options->CompetitionSession.inMatch == 0)
        {
            SonicMania::Player2.InkEffect = SonicMania::Ink_Alpha;
            SonicMania::Player2.Alpha = 0;
            SonicMania::Player2.Position.X = 0;
            SonicMania::Player2.Position.Y = 0;
        }   

        DeveloperSettingsBlockcade();

        SceneWarp();
        PlayerSettingsWarp();

        if (CreditsSelected) CreditsWarpLoop(true, SceneLoadWaitTimer, SceneLoadWaitMax, CreditsSelected, LevelSelectedWarpSoundPlayed);
        if (ExitSelected) ExitWarpLoop(true, SceneLoadWaitTimer, SceneLoadWaitMax, ExitSelected, LevelSelectedWarpSoundPlayed);

        CheckSettings();
        UpdateHUBSettingDisplays();
    }
}