#include "HubRanking.h"
#include "CompPlus_Core/CompPlus_Scoring.h"
#include "HubText.h"
#include "HubCore.h"

namespace CompPlus_HubRanking
{

    using namespace CompPlus_HubText;

    bool ExitSelected = false;

    int ExitRingSlot = 74;

    bool LevelSelected = false;
    bool LevelSelectedWarpSoundPlayed = false;
    int SceneLoadWaitTimer = 0;
    int SceneLoadWaitMax = 100;

    int RespawnObject_FirstPlace = 4;
    int RespawnObject_SecondPlace = 2;
    int RespawnObject_ThirdPlace = 3;
    int RespawnObject_FouthPlace = 5;
    int RespawnObject_NoPlace = 0;
    int RespawnObject_NoPodeium = 1;

    int PlayerSpawnSlotID = 65;

    int P1_WinsCounterText_Board = 14;
    int P2_WinsCounterText_Board = 17;
    int P3_WinsCounterText_Board = 16;
    int P4_WinsCounterText_Board = 19;

    int P1_TimeCounterText_Board = 18;
    int P2_TimeCounterText_Board = 21;
    int P3_TimeCounterText_Board = 20;
    int P4_TimeCounterText_Board = 23;

    int P1_ScoreCounterText_Board = 22;
    int P2_ScoreCounterText_Board = 25;
    int P3_ScoreCounterText_Board = 24;
    int P4_ScoreCounterText_Board = 27;

    int P1_RingsCounterText_Board = 26;
    int P2_RingsCounterText_Board = 29;
    int P3_RingsCounterText_Board = 28;
    int P4_RingsCounterText_Board = 31;

    int P1_TotalRingsCounterText_Board = 37;
    int P2_TotalRingsCounterText_Board = 36;
    int P3_TotalRingsCounterText_Board = 39;
    int P4_TotalRingsCounterText_Board = 38;

    int P1_ItemsCounterText_Board = 30;
    int P2_ItemsCounterText_Board = 33;
    int P3_ItemsCounterText_Board = 32;
    int P4_ItemsCounterText_Board = 35;


    int UpdateHUBRankingDisplays()
    {
        int StringIndex = 0;

        std::string winsP1 = std::to_string(CompPlus_Scoring::P1_WinsPlus);
        std::string winsP2 = std::to_string(CompPlus_Scoring::P2_WinsPlus);
        std::string winsP3 = std::to_string(CompPlus_Scoring::P3_WinsPlus);
        std::string winsP4 = std::to_string(CompPlus_Scoring::P4_WinsPlus);

        UpdateGeneralDisplay(P1_WinsCounterText_Board, (char*)winsP1.c_str(), winsP1.length(), 2, StringIndex);
        StringIndex++;
        UpdateGeneralDisplay(P2_WinsCounterText_Board, (char*)winsP2.c_str(), winsP2.length(), 2, StringIndex);
        StringIndex++;
        UpdateGeneralDisplay(P3_WinsCounterText_Board, (char*)winsP3.c_str(), winsP3.length(), 2, StringIndex);
        StringIndex++;
        UpdateGeneralDisplay(P4_WinsCounterText_Board, (char*)winsP4.c_str(), winsP4.length(), 2, StringIndex);
        StringIndex++;




        std::string timeP1 = std::to_string(CompPlus_Scoring::LastSession.TimeMinutes_P1) + "\'" + (CompPlus_Scoring::LastSession.TimeSeconds_P1 < 10 ? "0" : "") + std::to_string(CompPlus_Scoring::LastSession.TimeSeconds_P1) + "\"" + (CompPlus_Scoring::LastSession.TimeCentiseconds_P1 < 10 ? "0" : "") + std::to_string(CompPlus_Scoring::LastSession.TimeCentiseconds_P1);
        UpdateGeneralDisplay(P1_TimeCounterText_Board, (char*)timeP1.c_str(), timeP1.length(), 2, StringIndex);
        StringIndex++;
        std::string timeP2 = std::to_string(CompPlus_Scoring::LastSession.TimeMinutes_P2) + "\'" + (CompPlus_Scoring::LastSession.TimeSeconds_P2 < 10 ? "0" : "") + std::to_string(CompPlus_Scoring::LastSession.TimeSeconds_P2) + "\"" + (CompPlus_Scoring::LastSession.TimeCentiseconds_P2 < 10 ? "0" : "") + std::to_string(CompPlus_Scoring::LastSession.TimeCentiseconds_P2);
        UpdateGeneralDisplay(P2_TimeCounterText_Board, (char*)timeP2.c_str(), timeP2.length(), 2, StringIndex);
        StringIndex++;
        std::string timeP3 = std::to_string(CompPlus_Scoring::LastSession.TimeMinutes_P3) + "\'" + (CompPlus_Scoring::LastSession.TimeSeconds_P3 < 10 ? "0" : "") + std::to_string(CompPlus_Scoring::LastSession.TimeSeconds_P3) + "\"" + (CompPlus_Scoring::LastSession.TimeCentiseconds_P3 < 10 ? "0" : "") + std::to_string(CompPlus_Scoring::LastSession.TimeCentiseconds_P3);
        UpdateGeneralDisplay(P3_TimeCounterText_Board, (char*)timeP3.c_str(), timeP3.length(), 2, StringIndex);
        StringIndex++;
        std::string timeP4 = std::to_string(CompPlus_Scoring::LastSession.TimeMinutes_P4) + "\'" + (CompPlus_Scoring::LastSession.TimeSeconds_P4 < 10 ? "0" : "") + std::to_string(CompPlus_Scoring::LastSession.TimeSeconds_P4) + "\"" + (CompPlus_Scoring::LastSession.TimeCentiseconds_P4 < 10 ? "0" : "") + std::to_string(CompPlus_Scoring::LastSession.TimeCentiseconds_P4);
        UpdateGeneralDisplay(P4_TimeCounterText_Board, (char*)timeP4.c_str(), timeP4.length(), 2, StringIndex);
        StringIndex++;

        std::string scoreP1 = std::to_string(CompPlus_Scoring::LastSession.Score_P1);
        UpdateGeneralDisplay(P1_ScoreCounterText_Board, (char*)scoreP1.c_str(), scoreP1.length(), 2, StringIndex);
        StringIndex++;
        std::string scoreP2 = std::to_string(CompPlus_Scoring::LastSession.Score_P2);
        UpdateGeneralDisplay(P2_ScoreCounterText_Board, (char*)scoreP2.c_str(), scoreP2.length(), 2, StringIndex);
        StringIndex++;
        std::string scoreP3 = std::to_string(CompPlus_Scoring::LastSession.Score_P3);
        UpdateGeneralDisplay(P3_ScoreCounterText_Board, (char*)scoreP3.c_str(), scoreP3.length(), 2, StringIndex);
        StringIndex++;
        std::string scoreP4 = std::to_string(CompPlus_Scoring::LastSession.Score_P4);
        UpdateGeneralDisplay(P4_ScoreCounterText_Board, (char*)scoreP4.c_str(), scoreP4.length(), 2, StringIndex);
        StringIndex++;

        std::string ringsP1 = std::to_string(CompPlus_Scoring::LastSession.Rings_P1);
        UpdateGeneralDisplay(P1_RingsCounterText_Board, (char*)ringsP1.c_str(), ringsP1.length(), 2, StringIndex);
        StringIndex++;
        std::string ringsP2 = std::to_string(CompPlus_Scoring::LastSession.Rings_P2);
        UpdateGeneralDisplay(P2_RingsCounterText_Board, (char*)ringsP2.c_str(), ringsP2.length(), 2, StringIndex);
        StringIndex++;
        std::string ringsP3 = std::to_string(CompPlus_Scoring::LastSession.Rings_P3);
        UpdateGeneralDisplay(P3_RingsCounterText_Board, (char*)ringsP3.c_str(), ringsP3.length(), 2, StringIndex);
        StringIndex++;
        std::string ringsP4 = std::to_string(CompPlus_Scoring::LastSession.Rings_P4);
        UpdateGeneralDisplay(P4_RingsCounterText_Board, (char*)ringsP4.c_str(), ringsP4.length(), 2, StringIndex);
        StringIndex++;

        std::string itemsP1 = std::to_string(CompPlus_Scoring::LastSession.Items_P1);
        UpdateGeneralDisplay(P1_ItemsCounterText_Board, (char*)itemsP1.c_str(), itemsP1.length(), 2, StringIndex);
        StringIndex++;
        std::string itemsP2 = std::to_string(CompPlus_Scoring::LastSession.Items_P2);
        UpdateGeneralDisplay(P2_ItemsCounterText_Board, (char*)itemsP2.c_str(), itemsP2.length(), 2, StringIndex);
        StringIndex++;
        std::string itemsP3 = std::to_string(CompPlus_Scoring::LastSession.Items_P3);
        UpdateGeneralDisplay(P3_ItemsCounterText_Board, (char*)itemsP3.c_str(), itemsP3.length(), 2, StringIndex);
        StringIndex++;
        std::string itemsP4 = std::to_string(CompPlus_Scoring::LastSession.Items_P4);
        UpdateGeneralDisplay(P4_ItemsCounterText_Board, (char*)itemsP4.c_str(), itemsP4.length(), 2, StringIndex);
        StringIndex++;


        std::string totalringsP1 = std::to_string(CompPlus_Scoring::LastSession.TotalRings_P1);
        UpdateGeneralDisplay(P1_TotalRingsCounterText_Board, (char*)totalringsP1.c_str(), totalringsP1.length(), 2, StringIndex);
        StringIndex++;
        std::string totalringsP2 = std::to_string(CompPlus_Scoring::LastSession.TotalRings_P2);
        UpdateGeneralDisplay(P2_TotalRingsCounterText_Board, (char*)totalringsP2.c_str(), totalringsP2.length(), 2, StringIndex);
        StringIndex++;
        std::string totalringsP3 = std::to_string(CompPlus_Scoring::LastSession.TotalRings_P3);
        UpdateGeneralDisplay(P3_TotalRingsCounterText_Board, (char*)totalringsP3.c_str(), totalringsP3.length(), 2, StringIndex);
        StringIndex++;
        std::string totalringsP4 = std::to_string(CompPlus_Scoring::LastSession.TotalRings_P4);
        UpdateGeneralDisplay(P4_TotalRingsCounterText_Board, (char*)totalringsP4.c_str(), totalringsP4.length(), 2, StringIndex);
        StringIndex++;

        return StringIndex;
    }

    void SetSpawnPosition(SonicMania::EntityPlayer& Player, int Placement)
    {
        Entity& FirstPlacePodieumSpawn = *GetEntityFromSceneSlot<Entity>(RespawnObject_FirstPlace);
        Entity& SecondPlacePodieumSpawn = *GetEntityFromSceneSlot<Entity>(RespawnObject_SecondPlace);
        Entity& ThirdPlacePodieumSpawn = *GetEntityFromSceneSlot<Entity>(RespawnObject_ThirdPlace);
        Entity& ForthPlacePodieumSpawn = *GetEntityFromSceneSlot<Entity>(RespawnObject_FouthPlace);

        Entity& NoPosSpawn = *GetEntityFromSceneSlot<Entity>(RespawnObject_NoPlace);
        Entity& AltSpawn = *GetEntityFromSceneSlot<Entity>(RespawnObject_NoPodeium);

        if (Placement == 1)
        {
            Player.Position.X = FirstPlacePodieumSpawn.Position.X;
            Player.Position.Y = FirstPlacePodieumSpawn.Position.Y;
        }
        else if (Placement == 2)
        {
            Player.Position.X = SecondPlacePodieumSpawn.Position.X;
            Player.Position.Y = SecondPlacePodieumSpawn.Position.Y;
        }
        else if (Placement == 3)
        {
            Player.Position.X = ThirdPlacePodieumSpawn.Position.X;
            Player.Position.Y = ThirdPlacePodieumSpawn.Position.Y;
        }
        else if (Placement == 4)
        {
            Player.Position.X = ForthPlacePodieumSpawn.Position.X;
            Player.Position.Y = ForthPlacePodieumSpawn.Position.Y;
        }
        else if (CompPlus_Scoring::PodeiumSpawnActive)
        {
            Player.Position.X = NoPosSpawn.Position.X;
            Player.Position.Y = NoPosSpawn.Position.Y;
        }
        else
        {
            Player.Position.X = AltSpawn.Position.X;
            Player.Position.Y = AltSpawn.Position.Y;
        }

        if (Player.Camera != nullptr)
        {
            Player.Camera->Position.X = Player.Position.X;
            Player.Camera->Position.Y = Player.Position.Y;
        }
    }

    void SetSpawnPositions()
    {
        Entity& RespawnArea = *GetEntityFromSceneSlot<Entity>(PlayerSpawnSlotID);
        int x1 = RespawnArea.Position.X - 75;
        int y1 = RespawnArea.Position.Y - 75;
        int x2 = RespawnArea.Position.X + 75;
        int y2 = RespawnArea.Position.Y + 75;

        for (int RealID = 1; RealID <= 4; RealID++)
        {
            SonicMania::EntityPlayer* Player;
            int Position = 0;

            if (RealID == 1) 
            {
                Player = &Player1;
                Position = CompPlus_Scoring::P1_LastPlacement;
            }
            else if (RealID == 2)
            {
                Player = &Player2;
                Position = CompPlus_Scoring::P2_LastPlacement;
            }
            else if (RealID == 3)
            {
                Player = &Player3;
                Position = CompPlus_Scoring::P3_LastPlacement;
            }
            else if (RealID == 4)
            {
                Player = &Player4;
                Position = CompPlus_Scoring::P4_LastPlacement;
            }
            else 
            {
                Player = &Player1;
                Position = CompPlus_Scoring::P1_LastPlacement;
            }
            bool isPlayerInRange = Player->InRange(x1, y1, x2, y2);
            if (isPlayerInRange)
            {
                SetSpawnPosition(*Player, Position);
            }
        }

    }

    void SceneWarp()
    {
        int x1_exit = 1135;
        int y1_exit = 1005;
        int x2_exit = 1215;
        int y2_exit = 1175;

        int ExitCount = 0;

        int NumberOfPlayers = (SonicMania::Options->CompetitionSession.inMatch == 1 ? SonicMania::Options->CompetitionSession.NumberOfPlayers : 1);


        if (SonicMania::Player1.Camera != nullptr)
        {
            bool isPlayerInRangeOfExit = Player1.InRange(x1_exit, y1_exit, x2_exit, y2_exit);
            if (isPlayerInRangeOfExit) ExitCount += 1;
        }
        if (SonicMania::Player2.Camera != nullptr)
        {
            bool isPlayerInRangeOfExit = Player2.InRange(x1_exit, y1_exit, x2_exit, y2_exit);
            if (isPlayerInRangeOfExit) ExitCount += 1;
        }
        if (SonicMania::Player3.Camera != nullptr)
        {
            bool isPlayerInRangeOfExit = Player3.InRange(x1_exit, y1_exit, x2_exit, y2_exit);
            if (isPlayerInRangeOfExit) ExitCount += 1;
        }
        if (SonicMania::Player4.Camera != nullptr)
        {
            bool isPlayerInRangeOfExit = Player4.InRange(x1_exit, y1_exit, x2_exit, y2_exit);
            if (isPlayerInRangeOfExit) ExitCount += 1;
        }

        SpecialRing& ExitRing = *SonicMania::GetEntityFromSceneSlot<SpecialRing>(ExitRingSlot);


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
            CompPlus_Common::LoadHUBWorld();
            CompPlus_HubCore::ReturnDestination = 2;
        }
        else
        {
            if (SceneLoadWaitTimer >= 50 && !LevelSelectedWarpSoundPlayed)
            {
                SonicMania::PlaySoundFXS(CompPlus_Common::SFX_SpecialWarp);
                LevelSelectedWarpSoundPlayed = true;

                SonicMania::Entity* FXFade = SonicMania::SpawnObject(SonicMania::GetObjectIDFromType(SonicMania::ObjectType_FXFade), 0, SonicMania::Vector2(SonicMania::Player1.Position.X, SonicMania::Player1.Position.Y - 30));
                SonicMania::EntityFXFade* FxFadeR = (SonicMania::EntityFXFade*)FXFade;

                FxFadeR->Time = 0;
                FxFadeR->SpeedIn = 10;
                FxFadeR->Wait = 3;
                FxFadeR->SpeedOut = 0;
                FxFadeR->Color = 0x000000;
                FxFadeR->OneWay = true;
                FxFadeR->EventOnly = false;
                FxFadeR->Overhud = false;
                FxFadeR->FadeOutBlack = true;
                FxFadeR->DrawOrder = 14;

            }
            SceneLoadWaitTimer++;
        }

        SonicMania::stru_26B818[0].playStatus = 0;

    }

    void OnFrame() 
    {
        CompPlus_HubCore::SetHUBVisualSettings();
        SceneWarp();
        SetSpawnPositions();
        UpdateHUBRankingDisplays();
        if (ExitSelected) ExitWarpLoop(true, SceneLoadWaitTimer, SceneLoadWaitMax, ExitSelected, LevelSelectedWarpSoundPlayed);
    }
}