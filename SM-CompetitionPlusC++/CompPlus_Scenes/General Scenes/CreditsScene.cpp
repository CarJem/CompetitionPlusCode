#include "stdafx.h"
#include "ManiaModLoader.h"
#include "CreditsScene.h"
#include "include/SonicMania.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "CompPlus_Scenes/Level Select/CoreLevelSelect.h"
#include "CompPlus_Core/CompPlus_Settings.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "CompPlus_Scenes/HUB World/HubCore.h"
#include "CompPlus_Extensions/Drawing.h"
#include <string>

namespace CompPlus_Credits
{
    using namespace SonicMania;

    #pragma region Variables

    struct CollectableChar 
    {
        Vector2 Position;
        bool Collected = false;
        int RingCount = 4;
        int RingVelocity = 4;
        const char* SoundFXPath = "Global/Destroy.wav";
        const char* SecondFXPath = "Global/HyperRing.wav";
        bool SecondFX = false;
        bool HasRotationEnded = false;
        int RotationLoopCount = 5;
        int RotationCurrentLoop = 0;
        int Rotation = 0;

        CollectableChar()
        {
            int RandomGen = Rand(0, 10);
            if (RandomGen != 4) 
            {
                RingCount = 0;
                RingVelocity = 0;
                SecondFX = false;
            }
            else 
            {
                RingCount = Rand(10, 15);
                RingVelocity = 6;
                SecondFX = true;
            }

        }

        CollectableChar(Vector2 _Pos) : CollectableChar()
        {
            Position = _Pos;
        }

        int GetRotation() 
        {       
            if (!HasRotationEnded)
            {
                if (RotationCurrentLoop >= RotationLoopCount) 
                {
                    HasRotationEnded = true;
                }
                else 
                {
                    if (Rotation >= 360) 
                    {
                        RotationCurrentLoop += 1;
                        Rotation = 0;
                    }
                    else 
                    {
                        Rotation += 16;
                    }
                }
            }

            double radians = (Rotation * M_PI) / 180;
            return (int)((radians) * (512 / (M_PI * 2)));
        }
    };

    struct CollectableText
    {
        int SlotID;
        bool PictureCollected = false;

        bool isText = true;
        std::wstring Text;
        bool isTextStored = false;
        std::vector<CollectableChar> Characters;

        const char* PictureSoundFXPath = "Global/Destroy.wav";
        int PictureRingCount = 15;
        int PictureRingVelocity = 4;


        CollectableText()
        {

        }

        CollectableText(int _SlotID) : CollectableText()
        {
            SlotID = _SlotID;
        }

        CollectableText(int _SlotID, int TextLength) : CollectableText() 
        {
            SlotID = _SlotID;
            isText = true;
        }

        CollectableText(int _SlotID, const char* _CustomPath) : CollectableText()
        {
            SlotID = _SlotID;
            PictureSoundFXPath = _CustomPath;
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
    int CameraSpeed = 1;

    //Object Slot ID
    int CameraLockedObjectID = 65;
    int ExitButtonSlotID = 252;
    int LHPZSecretButtonSlotID = 268;
    int LHPZSecretText1SlotID = 271;
    int LHPZSecretText2SlotID = 269;
    int WallRightID = 250;
    int WallLeftID = 251;
    int VersionDescriptorSlotID = 243;

    //Camera/Credit States
    bool HasReachedTheEndOfCredits = false;
    bool HasStartedRolling = false;
    bool isUnlockedCamera = false;

    //Timers
    int UnlockWait = 0;
    int UnlockWaitMax = 950;
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
        SonicMania::EntityButton& ButtonTrigger = *GetEntityFromSceneSlot<SonicMania::EntityButton>(LHPZSecretButtonSlotID);

        if (ButtonTrigger.Pressed && !LHPZSecretTriggered)
        {
            SonicMania::PlaySoundFXS(CompPlus_Common::SFX_LHPZSecret);
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
            CompPlus_Settings::SaveSettings();
        }


    }

    void ExitDelayLoop(bool FastWarp, int& SceneLoadWaitTimer, int& SceneLoadWaitMax, bool& LevelSelected, bool& LevelSelectedWarpSoundPlayed)
    {
        if (FastWarp && SceneLoadWaitTimer < 50)
        {
            SceneLoadWaitTimer = 50;
        }


        if (SceneLoadWaitTimer >= SceneLoadWaitMax)
        {
            CompPlus_Common::LoadLevel_IZ(CompPlus_Common::HUBSettings);
            SceneLoadWaitTimer = 0;
            LevelSelected = false;
            LevelSelectedWarpSoundPlayed = false;
        }
        else
        {
            if (SceneLoadWaitTimer >= 50 && !LevelSelectedWarpSoundPlayed)
            {
                PlaySoundFXS(CompPlus_Common::SFX_SpecialWarp);
                LevelSelectedWarpSoundPlayed = true;

                CompPlus_Common::SpawnFadeOut(0, 10, 3, 0, 0x000000, true, false, false, true, 14);

            }
            SceneLoadWaitTimer++;
        }

        stru_26B818[0].playStatus = 0;
    }

    void ExitButton()
    {
        SonicMania::EntityButton& ButtonTrigger = *GetEntityFromSceneSlot<SonicMania::EntityButton>(ExitButtonSlotID);

        if (ButtonTrigger.Pressed)
        {
            ExitDelayLoop(0, SceneLoadWaitTimer, SwapLevelSelectMax, LevelSelected, LevelSelectedWarpSoundPlayed);
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
                if (i == 271 || i == 269 || i == 270 || i == 253) continue;
                Entity& entity = *GetEntityFromSceneSlot<Entity>(i);

                if (entity.ObjectID == 88)
                {
                    EntityUIInfoLabel& Label = *GetEntityFromSceneSlot<EntityUIInfoLabel>(i);
                    CurrentSpawns.insert(CurrentSpawns.begin(), CollectableText(i, Label.TextLength));
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

    DataPointer(int, ScreenOffsetX, 0x782A98);
    DataPointer(int, WindowSizeX, 0x43C6F4);
    DataPointer(int, WindowSizeY, 0x43C6F6);

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

            bool isPlayerInRange = GetPlayer(RealID).InRange(x1, y1, x2, y2);
            bool FoundAlready = CurrentSpawns[i].PictureCollected;
            if (isPlayerInRange && !FoundAlready)
            {
                SonicMania::PlaySoundFXS(CurrentSpawns[i].PictureSoundFXPath);
                CurrentSpawns[i].PictureCollected = true;
                SpawnRingsAtPosition(Vector2(x, y), CurrentSpawns[i].PictureRingCount, CurrentSpawns[i].PictureRingVelocity);
                SpawnObject(GetObjectIDFromType(ObjectType_ScoreBonus), 0, Vector2(x, y));
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

        if (!entity.InBounds) return;
        for (int RealID = 1; RealID <= 4; RealID++)
        {
            int textLength = CurrentSpawns[i].Characters.size();
            for (int c = 0; c < textLength; c++) 
            {             
                int x = CurrentSpawns[i].Characters[c].Position.X;
                int y = CurrentSpawns[i].Characters[c].Position.Y;

                int x1 = x - 10;
                int x2 = x + 10;
                int y1 = y - 10;
                int y2 = y + 10;

                entity.InkEffect = Ink_Alpha;
                entity.Alpha = 0;

                bool isPlayerInRange = GetPlayer(RealID).InRange(x1, y1, x2, y2);
                bool FoundAlready = CurrentSpawns[i].Characters[c].Collected;
                if (isPlayerInRange && !FoundAlready)
                {
                    SonicMania::PlaySoundFXS(CurrentSpawns[i].Characters[c].SoundFXPath);
                    if (CurrentSpawns[i].Characters[c].SecondFX) SonicMania::PlaySoundFXS(CurrentSpawns[i].Characters[c].SecondFXPath);
                    CurrentSpawns[i].Characters[c].Collected = true;
                    SpawnRingsAtPosition(Vector2(x, y), CurrentSpawns[i].Characters[c].RingCount, CurrentSpawns[i].Characters[c].RingVelocity);
                }
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

    std::wstring ConvertMStringToWString(wchar_t* text, int length)
    {
        std::wstring dest;
        for (int i = 0; i < length; ++i)
            dest += text[i] + 32;
        return dest;
    }

    int ManiaFontSpriteID = 0;
    bool ManiaFontLoaded = false;

    void StoreText(int i, DevMenu_Alignment Alignment = Alignment_Right)
    {
        EntityUIInfoLabel& Label = *GetEntityFromSceneSlot<EntityUIInfoLabel>(CurrentSpawns[i].SlotID);
        std::wstring Name = ConvertMStringToWString(Label.Text, Label.TextLength);

        CurrentSpawns[i].Text = Name;
        CurrentSpawns[i].isTextStored = true;

        int SpriteFrame = 0;
        int RealSpriteFrame = 0;
        int BuildLength = 0;

        EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);

        Vector2 LocationStart = Label.Position;

        int Length = Name.length();

        for (int j = 0; j < Length; j++)
        {
            RealSpriteFrame = int(Name[j]);
            SpriteFrame = int(Name[j]) - 32;
            SetSpriteAnimation(ManiaFontSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
            Drawing::AnimationFrame Frame = *Drawing::GetAnimationFrameFromFrameID(RingTemp->ActNumbersData, RealSpriteFrame);
            BuildLength = BuildLength + Frame.Width;
        }

        if (Alignment == DevMenu_Alignment::Alignment_Left) LocationStart.X = LocationStart.X - BuildLength;
        else if (Alignment == DevMenu_Alignment::Alignment_Center) LocationStart.X = LocationStart.X - (BuildLength != 0 ? (BuildLength / 2) + BuildLength % 2 : 0);

        
        for (int j = 0; j < Length; j++)
        {
            RealSpriteFrame = int(Name[j]);
            SpriteFrame = int(Name[j]) - 32;
            SetSpriteAnimation(ManiaFontSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
            Drawing::AnimationFrame Frame = *Drawing::GetAnimationFrameFromFrameID(RingTemp->ActNumbersData, RealSpriteFrame);
            Vector2 FramePosition = Drawing::GetFramePosition(LocationStart, Frame);
            CurrentSpawns[i].Characters.insert(CurrentSpawns[i].Characters.end(), CollectableChar(FramePosition));
            LocationStart.X = LocationStart.X + Frame.Width;
        }
    }

    void DrawCreditsTextSprite(std::wstring Name, Vector2 LocationStart, CollectableText& Parent, bool ScreenRelative, DevMenu_Alignment Alignment = Alignment_Right)
    {
        if (!ManiaFontLoaded)
        {
            ManiaFontSpriteID = LoadAnimation(CompPlus_Common::Anim_Cred_UISmallFont, Scope_Stage);
            ManiaFontLoaded = true;
            return;
        }

        int SpriteFrame = 0;
        int RealSpriteFrame = 0;
        int BuildLength = 0;
        EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);;
        for (int i = 0; i < Name.length(); i++)
        {
            RealSpriteFrame = int(Name[i]);
            SpriteFrame = int(Name[i]) - 32;
            SetSpriteAnimation(ManiaFontSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
            Drawing::AnimationFrame Frame = *Drawing::GetAnimationFrameFromFrameID(RingTemp->ActNumbersData, RealSpriteFrame);
            BuildLength = BuildLength + Frame.Width;
        }
        if (Alignment == DevMenu_Alignment::Alignment_Left) LocationStart.X = LocationStart.X - BuildLength;
        else if (Alignment == DevMenu_Alignment::Alignment_Center) LocationStart.X = LocationStart.X - (BuildLength != 0 ? (BuildLength / 2) + BuildLength % 2 : 0);
        //Offset lenth to build to our point. 

        for (int i = 0; i < Name.length(); i++)
        {
            bool Collected = Parent.Characters[i].Collected;
            RealSpriteFrame = int(Name[i]);
            SpriteFrame = int(Name[i]) - 32;
            RingTemp->Alpha = (Collected ? 128 : 255);
            RingTemp->DrawFX = DrawingFX_Rotate;
            if (Collected)
            {
                int Rotation = Parent.Characters[i].GetRotation();
                RingTemp->Angle = Rotation;
                RingTemp->Rotation = Rotation;
            }
            else 
            {
                RingTemp->Angle = 0;
                RingTemp->Rotation = 0;
            }

            RingTemp->InkEffect = Ink_Alpha;
            RingTemp->DrawOrder = 5;
            SetSpriteAnimation(ManiaFontSpriteID, 0, &RingTemp->ActNumbersData, true, SpriteFrame);
            Drawing::AnimationFrame Frame = *Drawing::GetAnimationFrameFromFrameID(RingTemp->ActNumbersData, RealSpriteFrame);
            Vector2 FramePosition = Drawing::GetFramePosition(LocationStart, Frame);
            DrawSprite(&RingTemp->ActNumbersData, &FramePosition, ScreenRelative);
            LocationStart.X = LocationStart.X + Frame.Width;
        }
    }


    void OnDrawText() 
    {
        int Offset_X = GetPointer(0xAA7628, 0x96000);
        int Offset_Y = GetPointer(0xAA7628, 0x96004);

        for (int i = 0; i < CurrentSpawns.size(); ++i)
        {
            if (CurrentSpawns[i].isText) 
            {
                EntityUIInfoLabel& Label = *GetEntityFromSceneSlot<EntityUIInfoLabel>(CurrentSpawns[i].SlotID);
                Vector2 Position = Vector2(Label.Position.X - Offset_X, Label.Position.Y - Offset_Y);
                if (!CurrentSpawns[i].isTextStored) StoreText(i, Alignment_Center);
                DrawCreditsTextSprite(CurrentSpawns[i].Text, Label.Position, CurrentSpawns[i], false, Alignment_Center);
            }
        }
    }

    void OnDraw()
    {
        SonicMania::Entity& CameraObject = *GetEntityFromSceneSlot<SonicMania::Entity>(CameraLockedObjectID);

        SyncRingCount();

        int PlayerCount = SonicMania::Options->CompetitionSession.NumberOfPlayers;



        int center_x = ScreenOffsetX;
        int center_y = 245;

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

        EntityTitleCard* Canvas = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);;

        int SizeX = 208; //15
        int SizeY = 10;

        int offset_y = -10;

        Canvas->DrawOrder = 12;
        DrawCircle(ScreenOffsetX - (SizeX / 2), center_y - (SizeY / 2), SizeY, 0x000000, 255, InkEffect::Ink_Alpha, true);
        DrawCircle(ScreenOffsetX + (SizeX / 2), center_y - (SizeY / 2), SizeY, 0x000000, 255, InkEffect::Ink_Alpha, true);
        DrawRect(ScreenOffsetX - (SizeX / 2), center_y - (SizeY / 2) + offset_y, SizeX, SizeY, 0x000000, 255, InkEffect::Ink_Alpha, true);
        Drawing::DrawDevTextSprite(ringCounter, SonicMania::Vector2(center_x, center_y + offset_y), true, 12, 0, 0, SonicMania::DevMenu_Alignment::Alignment_Center, false);
        OnDrawText();
    }

    #pragma endregion

    #pragma region Update Camera Methods

    void UpdateCameraPositions()
    {
        int PlayerCount = SonicMania::Options->CompetitionSession.NumberOfPlayers;

        SonicMania::Entity& CameraObject = *GetEntityFromSceneSlot<SonicMania::Entity>(CameraLockedObjectID);
        SonicMania::Entity& WallR = *GetEntityFromSceneSlot<SonicMania::Entity>(WallRightID);
        SonicMania::Entity& WallL = *GetEntityFromSceneSlot<SonicMania::Entity>(WallLeftID);
        //EntityUIInfoLabel& Label1 = *GetEntityFromSceneSlot<EntityUIInfoLabel>(RingCounterSlotID);

        //Label1.Position.X = CameraXPos;
        //Label1.Position.Y = RingCounterYPos;

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
            if (!GetPlayer(1).InRange(x1, y1, x2, y2))
            {
                Player1.Position.X = CameraXPos;
                Player1.Position.Y = CameraYPos;
            }
        }
        if (PlayerCount >= 2)
        {
            if (!GetPlayer(2).InRange(x1, y1, x2, y2))
            {
                Player2.Position.X = CameraXPos;
                Player2.Position.Y = CameraYPos;
            }
        }
        if (PlayerCount >= 3)
        {
            if (!GetPlayer(3).InRange(x1, y1, x2, y2))
            {
                Player3.Position.X = CameraXPos;
                Player3.Position.Y = CameraYPos;
            }
        }
        if (PlayerCount >= 4)
        {
            if (!GetPlayer(4).InRange(x1, y1, x2, y2))
            {
                Player4.Position.X = CameraXPos;
                Player4.Position.Y = CameraYPos;
            }
        }
    }

    void IncrementCamera()
    {
        if (PlayerControllers[0].X.Down)
        {
            CameraXPos += 5;
            CameraSpeed = 5;
        }
        else
        {
            CameraXPos++;
            CameraSpeed = 1;
        }
        
    }

    void SetPlayerCamera()
    {
        if (!HasReachedTheEndOfCredits)
        {
            auto Cam = GetEntityFromSceneSlot<SonicMania::Entity>(CameraLockedObjectID);
            if (Player1.Camera != nullptr)
            {
                if (Player1.Camera->CameraTarget != Cam) 
                {
                    Player1.Camera->CameraTarget = Cam;
                }
                //Player1.Camera->Speed = CameraSpeed;
            }
            if (Player2.Camera != nullptr)
            {
                if (Player2.Camera->CameraTarget != Cam)
                {
                    Player2.Camera->CameraTarget = Cam;
                }
                //Player2.Camera->Speed = CameraSpeed;
            }
            if (Player3.Camera != nullptr)
            {
                if (Player3.Camera->CameraTarget != Cam)
                {
                    Player3.Camera->CameraTarget = Cam;
                }
                //Player3.Camera->Speed = CameraSpeed;
            }
            if (Player4.Camera != nullptr)
            {
                if (Player4.Camera->CameraTarget != Cam)
                {
                    Player4.Camera->CameraTarget = Cam;
                }
                //Player4.Camera->Speed = CameraSpeed;
            }
            if (Cam->Position.X != CameraXPos) Cam->Position.X += 1;
            Cam->Position.Y = CameraYPos;
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

        if (Timer.TimerSecond >= 8 && !HasStartedRolling)
        {
            if (HasStartedRolling == false) HasStartedRolling = true;
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

    #pragma region Text Update Methods

    void UpdateUIInfoLabel(std::string text, int index, int SlotID)
    {
        EntityUIInfoLabel& PositionLabel = *GetEntityFromSceneSlot<EntityUIInfoLabel>(SlotID);

        char* _text = (char*)text.c_str();
        PositionLabel.Text = (wchar_t*)Strings[index];
        ConvertASCII2Unicode(PositionLabel.Text, _text, strlen(_text), -32);
        PositionLabel.TextLength = text.length();
    }

    void UpdateVersionLabels()
    {
        std::string VersionNumber = CompPlus_Common::Internal_VersionNumber;
        std::string VersionName = CompPlus_Common::Internal_VersionName;

        std::string MainLabel = ("VERSION " + VersionNumber + " (" + VersionName + ")");
        UpdateUIInfoLabel(MainLabel, 3, VersionDescriptorSlotID);
    }

    #pragma endregion

    #pragma region Player Collision Assist Methods

    int IdleTimer1P = 0;
    int IdleTimer2P = 0;
    int IdleTimer3P = 0;
    int IdleTimer4P = 0;

    int DeCollisionizeTimer1P = 0;
    int DeCollisionizeTimer2P = 0;
    int DeCollisionizeTimer3P = 0;
    int DeCollisionizeTimer4P = 0;

    int OldCollisionLayers1P = 0;
    int OldCollisionLayers2P = 0;
    int OldCollisionLayers3P = 0;
    int OldCollisionLayers4P = 0;

    int IdleMax = 25;

    int DeCollisionizeMax = 15;

    void HelpPlayer(EntityPlayer* Player, int& IdleTimer, int& DeCollisionizeTimer, int& OldCollisionLayers)
    {
        int MaxY = 1024 - 32;
        bool inRange = Player->Position.Y < MaxY;
        bool inRangeX = Player->Position.X < CameraXEndPos;
        if (inRange && inRangeX && Player->GetController().Down.Down && Player->XVelocity == 0 && Player->YVelocity == 0 && Player->State == PLAYERSTATE_LOOKDOWN)
        {
            if (IdleTimer >= IdleMax)
            {
                if (OldCollisionLayers == 0) OldCollisionLayers = Player->CollisionLayers;
                Player->CollisionLayers = 0;
                SetSpriteAnimation(Player->SpriteIndex, 10, &Player->Animation, false, 0);
                Player->State = PLAYERSTATE_JUMP;
                DeCollisionizeTimer += 1;
            }
            else IdleTimer += 1;
        }
        else if (DeCollisionizeTimer >= 1) 
        {
            if (DeCollisionizeTimer >= DeCollisionizeMax)
            {
                if (OldCollisionLayers != 0) Player->CollisionLayers = OldCollisionLayers;
                OldCollisionLayers = 0;
                IdleTimer = 0;
                DeCollisionizeTimer = 0;
            }
            else 
            {
                DeCollisionizeTimer += 1;
            }
        }
        else 
        {
            if (OldCollisionLayers != 0) Player->CollisionLayers = OldCollisionLayers;
            OldCollisionLayers = 0;
            IdleTimer = 0;
            DeCollisionizeTimer = 0;
        }
    }

    void HelpPlayers() 
    {
        HelpPlayer(&Player1, IdleTimer1P, DeCollisionizeTimer1P, OldCollisionLayers1P);
        HelpPlayer(&Player2, IdleTimer2P, DeCollisionizeTimer2P, OldCollisionLayers2P);
        HelpPlayer(&Player3, IdleTimer3P, DeCollisionizeTimer3P, OldCollisionLayers3P);
        HelpPlayer(&Player4, IdleTimer4P, DeCollisionizeTimer4P, OldCollisionLayers4P);
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
        ManiaFontLoaded = false;
    }

    void OfflineLoop()
    {
        if (!DeIntZoneInitalized)
        {
            ResetScene();
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
        SonicMania::SetVSScreenCount(1);
    }

    void ZoneLoop()
    {
        ZoneLoopInit();
        RingSpawnLoop();
        LHPZButton();
        ExitButton();
        UpdateVersionLabels();
        HelpPlayers();

        SetPlayerCamera();
        UpdateCameraLoop();
        UpdateCameraPositions();
    }

    void OnFrame(bool inZone)
    {
        if (SonicMania::Timer.Enabled == false && HasStartedRolling) ResetScene();

        if (inZone) ZoneLoop();
        else OfflineLoop();
    }

    void Init()
    {
        for (int i = 0; i < 4; ++i)
            Strings[i] = (wchar_t*)malloc(128);
    }

    #pragma endregion




}