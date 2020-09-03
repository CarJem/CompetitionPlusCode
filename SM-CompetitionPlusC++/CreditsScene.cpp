#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CreditsScene.h"
#include "include/SonicMania.h"
#include "ManiaExt.h"
#include "LevelSelectCore.h"
#include "CompPlus_Settings.h"

namespace CompPlus_Credits
{
    using namespace SonicMania;

    #pragma region Variables

    struct CollectableText
    {
        int SlotID;
        bool Collected = false;
        bool isText = true;
        const char* SoundFXPath = "Global/Destroy.wav";
        int RingCount = 15;
        int RingVelocity = 4;

        CollectableText()
        {

        }

        CollectableText(int _SlotID) : CollectableText()
        {
            SlotID = _SlotID;
        }

        CollectableText(int _SlotID, const char* _CustomPath) : CollectableText()
        {
            SlotID = _SlotID;
            SoundFXPath = _CustomPath;
            isText = false;
        }
    };

    //Positions
    int CameraXPos = 208;
    int CameraYPos = 904;
    int CameraXPosInit = 208;
    int CameraYPosInit = 904;
    int CameraXEndPos = 8960;
    int CameraYEndPos = 904;
    int RingCounterYPos = 1023;

    //Object Slot ID
    int RingCounterSlotID = 273;
    int CameraLockedObjectID = 65;
    int ExitButtonSlotID = 252;
    int LHPZSecretButtonSlotID = 268;
    int LHPZSecretText1SlotID = 271;
    int LHPZSecretText2SlotID = 269;
    int WallRightID = 250;
    int WallLeftID = 251;

    //Camera/Credit States
    bool HasReachedTheEndOfCredits = false;
    bool HasStartedRolling = false;
    bool isUnlockedCamera = false;

    //Timers
    int UnlockWait = 0;
    int UnlockWaitMax = 750;
    int IncrementWait = 0;
    int IncrementWaitMax = 1;
    int SceneLoadWaitTimer = 0;
    int SwapLevelSelectMax = 100;

    //Ring Counters
    int RingCountP1 = 0;
    int RingCountP2 = 0;
    int RingCountP3 = 0;
    int RingCountP4 = 0;

    //Button States
    bool LevelSelectedWarpSoundPlayed = false;
    bool LevelSelected = false;
    bool LHPZSecretTriggered = false;

    //Init States
    bool RingProvidersInit = false;
    bool DeIntZoneInitalized = true;

    //Buffers/Vectors
    static wchar_t* Strings[3];
    std::vector<CollectableText> CurrentSpawns;

    #pragma endregion

    #pragma region Button Trigger Methods

    void LHPZButton()
    {
        Button& ButtonTrigger = *GetEntityFromSceneSlot<Button>(LHPZSecretButtonSlotID);

        if (ButtonTrigger.Pressed && !LHPZSecretTriggered)
        {
            SonicMania::PlaySoundFXS("CompPlus/LHPZSecret.wav");
            //TODO - Add Secret Trigger
            char* TextPart1 = (char*)"GO TO THE LOST...";
            char* TextPart2 = (char*)"HIDDEN PALACE!";
            EntityUIInfoLabel& Label1 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(LHPZSecretText1SlotID);
            EntityUIInfoLabel& Label2 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(LHPZSecretText2SlotID);

            Label1.Text = (wchar_t*)Strings[0];
            ConvertASCII2Unicode(Label1.Text, TextPart1, strlen(TextPart1), -32);
            Label1.TextLength = (WORD)17;


            Label2.Text = (wchar_t*)Strings[1];
            ConvertASCII2Unicode(Label2.Text, TextPart2, strlen(TextPart2), -32);
            Label2.TextLength = (WORD)15;
            CompPlus_Settings::LHPZ_SecretUnlocked = true;
            LHPZSecretTriggered = true;
        }


    }

    void ExitButton()
    {
        Button& ButtonTrigger = *GetEntityFromSceneSlot<Button>(ExitButtonSlotID);

        if (ButtonTrigger.Pressed)
        {
            CompPlus_LevelSelectCore::LevelSelectDelayLoop(0, "CPHW", true, SceneLoadWaitTimer, SwapLevelSelectMax, LevelSelected, LevelSelectedWarpSoundPlayed);
        }
    }

    #pragma endregion

    #pragma region Text Interaction Methods

    void CollectRingProviders()
    {
        if (!RingProvidersInit)
        {
            for (int i = 0; i < 2301; ++i)
            {
                Entity& entity = *GetEntityFromSceneSlot<Entity>(i);

                if (entity.ObjectID == 89 && i != RingCounterSlotID)
                {
                    CurrentSpawns.insert(CurrentSpawns.begin(), i);
                }
            }
            RingProvidersInit = true;
        }
    }

    void SyncRingCount() 
    {
        RingCountP1 += Player1.RingCount;
        RingCountP2 += Player2.RingCount;
        RingCountP3 += Player3.RingCount;
        RingCountP4 += Player4.RingCount;

        Player1.RingCount = 0;
        Player2.RingCount = 0;
        Player3.RingCount = 0;
        Player4.RingCount = 0;
    }

    void RingCountHUD()
    {
        int PlayerCount = SonicMania::Options->CompetitionSession.NumberOfPlayers;

        SyncRingCount();

        std::string ringCounter = "";
        ringCounter += std::to_string(RingCountP1);
        if (PlayerCount >= 2) 
        {
            ringCounter += " : ";
            ringCounter += std::to_string(RingCountP2);
        }
        if (PlayerCount >= 3)
        {
            ringCounter += " : ";
            ringCounter += std::to_string(RingCountP3);
        }
        if (PlayerCount >= 4)
        {
            ringCounter += " : ";
            ringCounter += std::to_string(RingCountP4);
        }

        EntityUIInfoLabel& Label1 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(RingCounterSlotID);

        Label1.DrawOrder = 12;
        Label1.Position.X = CameraXPos;
        Label1.Position.Y = RingCounterYPos;

        Label1.Text = (wchar_t*)Strings[2];
        ConvertASCII2Unicode(Label1.Text, (char*)ringCounter.c_str(), strlen(ringCounter.c_str()), -32);
        Label1.TextLength = (WORD)ringCounter.length();
    }

    void SpawnRingsAtPosition(Vector2 Position, int Num, int Speed)
    {
        float AngleD = 101.25;
        float AngleR = 0;
        EntityRing* Temp;

        bool Doflip = false;
        for (int i = 0; i < Num; i++)
        {
            Temp = (EntityRing*)SpawnObject(GetObjectIDFromType(ObjectType_Ring), 0, Position);
            Temp->State = (PlayerStatus)(baseAddress + 0x934D0);
            AngleR = (float)((AngleD * 3.14159265) / 180);
            Temp->YVelocity = (int)(sin(AngleR) * Speed);
            Temp->XVelocity = (int)(cos(AngleR) * Speed);
            Temp->YVelocity = Temp->YVelocity * 0x10000;
            Temp->XVelocity = Temp->XVelocity * 0x10000;
            if (Doflip)
            {
                int InvertX = Temp->XVelocity * -1;
                Temp->XVelocity = InvertX;
                Doflip = false;
            }
            else
            {
                Doflip = true;
            }
            AngleD = (float)(AngleD + 22.5);
            if (i == 16)
            {
                Speed = 4;
                AngleD = 101.25;
            }
        }
    }

    void RingSpawnTrigger_UIPicture(int i)
    {
        EntityUIPicture& entity = *GetEntityFromSceneSlot<EntityUIPicture>(CurrentSpawns[i].SlotID);

        for (int RealID = 1; RealID <= 4; RealID++)
        {
            int x = entity.Position.X;
            int y = entity.Position.Y;

            int x1 = x - 20;
            int x2 = x + 20;
            int y1 = y - 20;
            int y2 = y + 20;

            bool isPlayerInRange = PlayerInRange(RealID, x1, y1, x2, y2);
            bool FoundAlready = CurrentSpawns[i].Collected;
            if (isPlayerInRange && !FoundAlready)
            {
                SonicMania::PlaySoundFXS(CurrentSpawns[i].SoundFXPath);
                CurrentSpawns[i].Collected = true;
                SpawnRingsAtPosition(Vector2(x, y), CurrentSpawns[i].RingCount, CurrentSpawns[i].RingVelocity);
            }

            if (FoundAlready)
            {
                entity.InkEffect = Ink_Alpha;
                entity.Alpha = 150;
            }
        }
    }

    void RingSpawnTrigger_Text(int i) 
    {
        EntityUIInfoLabel& entity = *GetEntityFromSceneSlot<EntityUIInfoLabel>(CurrentSpawns[i].SlotID);

        for (int RealID = 1; RealID <= 4; RealID++)
        {

            int x = entity.Position.X;
            int y = entity.Position.Y;

            int width = entity.TextLength / 2;

            int x1 = x - 20;
            int x2 = x + 20;
            int y1 = y - 20;
            int y2 = y + 20;

            bool isPlayerInRange = PlayerInRange(RealID, x1, y1, x2, y2);
            bool FoundAlready = CurrentSpawns[i].Collected;
            if (isPlayerInRange && !FoundAlready)
            {
                SonicMania::PlaySoundFXS(CurrentSpawns[i].SoundFXPath);
                CurrentSpawns[i].Collected = true;
                SpawnRingsAtPosition(Vector2(x, y), CurrentSpawns[i].RingCount, CurrentSpawns[i].RingVelocity);
            }

            if (FoundAlready)
            {
                entity.InkEffect = Ink_Alpha;
                entity.Alpha = 150;
            }
        }
    }

    void RingSpawnLoop()
    {
        CollectRingProviders();
        int length = CurrentSpawns.size();
        for (int i = 0; i < length; ++i)
        {
            if (CurrentSpawns[i].isText) RingSpawnTrigger_Text(i);
            else RingSpawnTrigger_UIPicture(i);
        }
    }

    #pragma endregion

    #pragma region Update Camera Methods

    void UpdateCameraPositions()
    {
        int PlayerCount = SonicMania::Options->CompetitionSession.NumberOfPlayers;

        SonicMania::Entity& CameraObject = *GetEntityFromSceneSlot<SonicMania::Entity>(CameraLockedObjectID);
        SonicMania::Entity& WallR = *GetEntityFromSceneSlot<SonicMania::Entity>(WallRightID);
        SonicMania::Entity& WallL = *GetEntityFromSceneSlot<SonicMania::Entity>(WallLeftID);
        EntityUIInfoLabel& Label1 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(RingCounterSlotID);

        Label1.Position.X = CameraXPos;
        Label1.Position.Y = RingCounterYPos;

        CameraObject.Position.X = CameraXPos;
        CameraObject.Position.Y = CameraYPos;

        WallR.Position.X = CameraXPos + 232;
        WallL.Position.X = CameraXPos - 232;

        WallR.Position.Y = CameraYPos;
        WallL.Position.Y = CameraYPos;

        int x1 = CameraXPos - 232;
        int y1 = CameraYPos - 128;
        int x2 = CameraXPos + 232;
        int y2 = CameraYPos + 128;

        if (PlayerCount >= 1)
        {
            if (!PlayerInRange(1, x1, y1, x2, y2))
            {
                Player1.Position.X = CameraXPos;
                Player1.Position.Y = CameraYPos;
            }
        }
        if (PlayerCount >= 2)
        {
            if (!PlayerInRange(2, x1, y1, x2, y2))
            {
                Player2.Position.X = CameraXPos;
                Player2.Position.Y = CameraYPos;
            }
        }
        if (PlayerCount >= 3)
        {
            if (!PlayerInRange(3, x1, y1, x2, y2))
            {
                Player3.Position.X = CameraXPos;
                Player3.Position.Y = CameraYPos;
            }
        }
        if (PlayerCount >= 4)
        {
            if (!PlayerInRange(4, x1, y1, x2, y2))
            {
                Player4.Position.X = CameraXPos;
                Player4.Position.Y = CameraYPos;
            }
        }
    }

    void IncrementCamera()
    {
        if (PlayerControllers[0].Y.Down)
        {
            CameraXPos += 1;
        }
        else
        {
            CameraXPos++;
        }
    }

    void SetPlayerCamera()
    {
        if (!HasReachedTheEndOfCredits)
        {
            if (Player1.Camera != nullptr)
            {
                Player1.Camera->CameraTarget = GetEntityFromSceneSlot<SonicMania::Entity>(CameraLockedObjectID);
                Player1.Camera->Position.X = CameraXPos;
                Player1.Camera->Position.Y = CameraYPos;
            }
            if (Player2.Camera != nullptr)
            {
                Player2.Camera->CameraTarget = GetEntityFromSceneSlot<SonicMania::Entity>(CameraLockedObjectID);
                Player2.Camera->Position.X = CameraXPos;
                Player2.Camera->Position.Y = CameraYPos;
            }
            if (Player3.Camera != nullptr)
            {
                Player3.Camera->CameraTarget = GetEntityFromSceneSlot<SonicMania::Entity>(CameraLockedObjectID);
                Player3.Camera->Position.X = CameraXPos;
                Player3.Camera->Position.Y = CameraYPos;
            }
            if (Player4.Camera != nullptr)
            {
                Player4.Camera->CameraTarget = GetEntityFromSceneSlot<SonicMania::Entity>(CameraLockedObjectID);
                Player4.Camera->Position.X = CameraXPos;
                Player4.Camera->Position.Y = CameraYPos;
            }
        }
        else if (isUnlockedCamera)
        {
            Entity& PlayerTarget = Player1;
            if (Player1.Camera != nullptr)
            {
                Player1.Camera->CameraTarget = &PlayerTarget;
                Player1.Camera->Position.Y = CameraYPos;
            }
            if (Player2.Camera != nullptr)
            {
                Player2.Camera->CameraTarget = &PlayerTarget;
                Player2.Camera->Position.Y = CameraYPos;
            }
            if (Player3.Camera != nullptr)
            {
                Player3.Camera->CameraTarget = &PlayerTarget;
                Player3.Camera->Position.Y = CameraYPos;
            }
            if (Player4.Camera != nullptr)
            {
                Player4.Camera->CameraTarget = &PlayerTarget;
                Player4.Camera->Position.Y = CameraYPos;
            }
        }
    }

    void UpdateCameraLoop()
    {
        if (HasReachedTheEndOfCredits)
        {
            if (isUnlockedCamera)
            {
                CameraXPos = Player1.Position.X;
            }
            else
            {
                CameraXPos = CameraXEndPos;
                if (UnlockWait >= UnlockWaitMax)
                {
                    isUnlockedCamera = true;
                }
                else
                {
                    UnlockWait++;
                }
            }

        }

        if (Timer.TimerSecond >= 3)
        {
            if (HasStartedRolling == false) HasStartedRolling = true;
            if (Timer.TimerSecond >= 4) Timer.ResetTimer();
        }

        if (HasStartedRolling)
        {
            if (HasReachedTheEndOfCredits == false)
            {
                if (IncrementWait >= IncrementWaitMax)
                {
                    IncrementWait = 0;
                    IncrementCamera();
                }
                else
                {
                    IncrementWait++;
                }

            }
        }

        if (CameraXPos >= CameraXEndPos)
        {
            HasReachedTheEndOfCredits = true;
        }
    }

    #pragma endregion

    #pragma region General Methods

    void ResetScene()
    {
        HasReachedTheEndOfCredits = false;
        HasStartedRolling = false;
        CameraXPos = CameraXPosInit;
        CameraYPos = CameraYPosInit;
        UnlockWait = 0;
        IncrementWait = 0;
        CurrentSpawns.clear();

        RingCountP1 = 0;
        RingCountP2 = 0;
        RingCountP3 = 0;
        RingCountP4 = 0;

        RingProvidersInit = false;
    }

    void OfflineLoop()
    {
        if (!DeIntZoneInitalized)
        {
            ResetScene();
            CompPlus_Settings::isVSControllerInputUnlocked = false;
            DeIntZoneInitalized = true;
        }
    }

    void ZoneLoopInit()
    {
        DeIntZoneInitalized = false;
        if (SonicMania::Timer.Enabled == false) 
        {
            CompPlus_Settings::RefreshSettings();
            SonicMania::Timer.Enabled = true;
        }
        SetScreenCount(1);
        CompPlus_Settings::isVSControllerInputUnlocked = true;
    }

    void ZoneLoop()
    {
        ZoneLoopInit();
        RingCountHUD();
        RingSpawnLoop();
        LHPZButton();
        ExitButton();

        SetPlayerCamera();
        UpdateCameraLoop();
        UpdateCameraPositions();
    }

    void OnFrame(bool inZone)
    {
        if (inZone) ZoneLoop();
        else OfflineLoop();
    }

    void Init()
    {
        for (int i = 0; i < 3; ++i)
            Strings[i] = (wchar_t*)malloc(128);
    }

    #pragma endregion




}