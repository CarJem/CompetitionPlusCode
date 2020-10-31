#include "stdafx.h"
#include "ManiaModLoader.h"
#include "SonicMania.h"
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include "CompPlus_Core/CompPlus_Common.h"
#include "CompPlus_Core/CompPlus_Status.h"

namespace CompPlus_Halloween2018
{
    using namespace SonicMania;

    #pragma region Variables

    DataPointer(int, IsPlayerInDebugMode, 0x31F9AC);

    bool DisableTouchKill = true;

    std::vector<Vector2> SpawnPositions;

    int DespawnRange = 2000;

    int EXEAnimID = 0;

    bool EXEActiveP1 = false;
    bool EXEActiveP2 = false;
    bool EXEActiveP3 = false;
    bool EXEActiveP4 = false;

    bool EXERespawnP1 = false;
    bool EXERespawnP2 = false;
    bool EXERespawnP3 = false;
    bool EXERespawnP4 = false;

    int exetimeP1 = 0;
    int exetimeP2 = 0;
    int exetimeP3 = 0;
    int exetimeP4 = 0;

    int EXESpeedModP1 = 0;
    int EXESpeedModP2 = 0;
    int EXESpeedModP3 = 0;
    int EXESpeedModP4 = 0;

    int exetouchP1 = 0;
    int exetouchP2 = 0;
    int exetouchP3 = 0;
    int exetouchP4 = 0;

    bool CanDrawP1 = false;
    bool CanDrawP2 = false;
    bool CanDrawP3 = false;
    bool CanDrawP4 = false;

    int ColorStorage[16] = {};
    int ColorStorage2[16] = {};

    #pragma endregion

    #pragma region Helper Methods

    Vector2 MoveToPoint(Vector2 CurrentPosition, Vector2 GoalPosition, int Speed)
    {
        //Working Values
        float delta_x;
        float delta_y;
        float goal_dist;
        float ratio;
        float y_move;
        float x_move;

        //Get diffrence by subtracting X Goal & X Current, Do the Same with Y, then use Square to figure out the 
        //real distance between the X,Y of Goal & X,Y of Current.
        delta_x = GoalPosition.X - CurrentPosition.X;
        delta_y = GoalPosition.Y - CurrentPosition.Y;
        goal_dist = sqrt((delta_x * delta_x) + (delta_y * delta_y));

        //If Current Goal is would take longer then our steps then do more math to figure out the next point.
        if (goal_dist > 3)
        {
            ratio = Speed / goal_dist;
            x_move = ratio * delta_x;
            y_move = ratio * delta_y;

            Vector2 NextPosition = Vector2((int)x_move + CurrentPosition.X, (int)y_move + CurrentPosition.Y);
            return NextPosition;
        }
        else
        {
            //Length to small, just move to Goal.
            return GoalPosition;

        }
        return GoalPosition;
    }

    int RandomNumber(int min, int max)
    {
        return rand() % (max - min) + min;
    }

    #pragma endregion

    #pragma region Draw Methods

    void AllowDraw() 
    {

    }

    void LoadEXESprites()
    {
        EXEAnimID = LoadAnimation(CompPlus_Common::Anim_EXE_Sprites, Scope_Stage);
    }

    void DrawEXE(SonicMania::EntityPlayer Player, Vector2 LocationStart, bool ScreenRelative, int AnimID, int FrameID)
    {
        if (ScreenRelative)
        {
            int x = SonicMania::OBJ_Camera->XPos;
            int y = SonicMania::OBJ_Camera->YPos;

            LocationStart = Vector2(x + LocationStart.GetFullX(), y + LocationStart.GetFullY());
        }

        EntityTitleCard* RingTemp = (EntityTitleCard*)GetAddress(baseAddress + 0xAA7634, 0, 0);

        //RingTemp->DrawOrder = Player.DrawOrder;
        RingTemp->DrawFX = SonicMania::DrawingFX_Rotate;
        RingTemp->ActiveScreens = Player.ActiveScreens;
        RingTemp->Rotation = Player.Rotation;
        RingTemp->Angle = Player.Angle;
        SetSpriteAnimation(EXEAnimID, AnimID, &RingTemp->ActNumbersData, true, FrameID);
        DrawSprite(&RingTemp->ActNumbersData, &LocationStart, true);
    }

    void SetTempColors()
    {
        ColorStorage[0] = Palette0[208];
        ColorStorage[1] = Palette0[209];
        ColorStorage[2] = Palette0[210];
        ColorStorage[3] = Palette0[211];
        ColorStorage[4] = Palette0[212];
        ColorStorage[5] = Palette0[213];
        ColorStorage[6] = Palette0[214];
        ColorStorage[7] = Palette0[215];
        ColorStorage[8] = Palette0[216];
        ColorStorage[9] = Palette0[217];
        ColorStorage[10] = Palette0[218];
        ColorStorage[11] = Palette0[219];
        ColorStorage[12] = Palette0[220];
        ColorStorage[13] = Palette0[221];
        ColorStorage[14] = Palette0[222];
        ColorStorage[15] = Palette0[223];

        ColorStorage2[0] = Palette1[208];
        ColorStorage2[1] = Palette1[209];
        ColorStorage2[2] = Palette1[210];
        ColorStorage2[3] = Palette1[211];
        ColorStorage2[4] = Palette1[212];
        ColorStorage2[5] = Palette1[213];
        ColorStorage2[6] = Palette1[214];
        ColorStorage2[7] = Palette1[215];
        ColorStorage2[8] = Palette1[216];
        ColorStorage2[9] = Palette1[217];
        ColorStorage2[10] = Palette1[218];
        ColorStorage2[11] = Palette1[219];
        ColorStorage2[12] = Palette1[220];
        ColorStorage2[13] = Palette1[221];
        ColorStorage2[14] = Palette1[222];
        ColorStorage2[15] = Palette1[223];

        Palette0[208] = SonicMania::ToRGB565(0x000058);
        Palette0[209] = SonicMania::ToRGB565(0x00386F);
        Palette0[210] = SonicMania::ToRGB565(0x006872);
        Palette0[211] = SonicMania::ToRGB565(0x188896);
        Palette0[212] = SonicMania::ToRGB565(0x30A0A5);
        Palette0[213] = SonicMania::ToRGB565(0x68D0BB);
        Palette0[214] = SonicMania::ToRGB565(0x18585A);
        Palette0[215] = SonicMania::ToRGB565(0x60A099);
        Palette0[216] = SonicMania::ToRGB565(0xA0E0CD);
        Palette0[217] = SonicMania::ToRGB565(0xE0E0C2);
        Palette0[218] = SonicMania::ToRGB565(0x400000);
        Palette0[219] = SonicMania::ToRGB565(0x902800);
        Palette0[220] = SonicMania::ToRGB565(0xE03700);
        Palette0[221] = SonicMania::ToRGB565(0x9F6830);
        Palette0[222] = SonicMania::ToRGB565(0xBD9060);
        Palette0[223] = SonicMania::ToRGB565(0xCDB090);

        Palette2[208] = SonicMania::ToRGB565(0x000058);
        Palette2[209] = SonicMania::ToRGB565(0x00386F);
        Palette2[210] = SonicMania::ToRGB565(0x006872);
        Palette2[211] = SonicMania::ToRGB565(0x188896);
        Palette2[212] = SonicMania::ToRGB565(0x30A0A5);
        Palette2[213] = SonicMania::ToRGB565(0x68D0BB);
        Palette2[214] = SonicMania::ToRGB565(0x18585A);
        Palette2[215] = SonicMania::ToRGB565(0x60A099);
        Palette2[216] = SonicMania::ToRGB565(0xA0E0CD);
        Palette2[217] = SonicMania::ToRGB565(0xE0E0C2);
        Palette2[218] = SonicMania::ToRGB565(0x400000);
        Palette2[219] = SonicMania::ToRGB565(0x902800);
        Palette2[220] = SonicMania::ToRGB565(0xE03700);
        Palette2[221] = SonicMania::ToRGB565(0x9F6830);
        Palette2[222] = SonicMania::ToRGB565(0xBD9060);
        Palette2[223] = SonicMania::ToRGB565(0xCDB090);
    }

    void ResetColors()
    {
        Palette0[208] = ColorStorage[0];
        Palette0[209] = ColorStorage[1];
        Palette0[210] = ColorStorage[2];
        Palette0[211] = ColorStorage[3];
        Palette0[212] = ColorStorage[4];
        Palette0[213] = ColorStorage[5];
        Palette0[214] = ColorStorage[6];
        Palette0[215] = ColorStorage[7];
        Palette0[216] = ColorStorage[8];
        Palette0[217] = ColorStorage[9];
        Palette0[218] = ColorStorage[10];
        Palette0[219] = ColorStorage[11];
        Palette0[220] = ColorStorage[12];
        Palette0[221] = ColorStorage[13];
        Palette0[222] = ColorStorage[14];
        Palette0[223] = ColorStorage[15];

        Palette2[208] = ColorStorage2[0];
        Palette2[209] = ColorStorage2[1];
        Palette2[210] = ColorStorage2[2];
        Palette2[211] = ColorStorage2[3];
        Palette2[212] = ColorStorage2[4];
        Palette2[213] = ColorStorage2[5];
        Palette2[214] = ColorStorage2[6];
        Palette2[215] = ColorStorage2[7];
        Palette2[216] = ColorStorage2[8];
        Palette2[217] = ColorStorage2[9];
        Palette2[218] = ColorStorage2[10];
        Palette2[219] = ColorStorage2[11];
        Palette2[220] = ColorStorage2[12];
        Palette2[221] = ColorStorage2[13];
        Palette2[222] = ColorStorage2[14];
        Palette2[223] = ColorStorage2[15];
    }


    #pragma endregion

    #pragma region Get / Set Methods

    void EndDraw(int pointer)
    {
        if (pointer == 0) CanDrawP1 = false;
        else if (pointer == 1) CanDrawP2 = false;
        else if (pointer == 2) CanDrawP3 = false;
        else if (pointer == 3) CanDrawP4 = false;
    }

    bool CanDraw(int pointer)
    {
        if (pointer == 0) return CanDrawP1;
        else if (pointer == 1) return CanDrawP2;
        else if (pointer == 2) return CanDrawP3;
        else if (pointer == 3) return CanDrawP4;
        else return false;
    }

    bool GetEXERespawn(int PlayerID)
    {
        if (PlayerID == 1) return EXERespawnP1;
        else if (PlayerID == 2) return EXERespawnP2;
        else if (PlayerID == 3) return EXERespawnP3;
        else if (PlayerID == 4) return EXERespawnP4;
        else return false;
    }

    void SetEXERespawn(bool value, int PlayerID)
    {
        if (PlayerID == 1) EXERespawnP1 = value;
        else if (PlayerID == 2) EXERespawnP2 = value;
        else if (PlayerID == 3) EXERespawnP3 = value;
        else if (PlayerID == 4) EXERespawnP4 = value;
    }

    bool GetEXEActive(int PlayerID)
    {
        if (PlayerID == 1) return EXEActiveP1;
        else if (PlayerID == 2) return EXEActiveP2;
        else if (PlayerID == 3) return EXEActiveP3;
        else if (PlayerID == 4) return EXEActiveP4;
        else return false;
    }

    void SetEXEActive(bool value, int PlayerID)
    {
        if (PlayerID == 1) EXEActiveP1 = value;
        else if (PlayerID == 2) EXEActiveP2 = value;
        else if (PlayerID == 3) EXEActiveP3 = value;
        else if (PlayerID == 4) EXEActiveP4 = value;
    }

    int GetEXETouch(int PlayerID)
    {
        if (PlayerID == 1) return exetouchP1;
        else if (PlayerID == 2) return exetouchP2;
        else if (PlayerID == 3) return exetouchP3;
        else if (PlayerID == 4) return exetouchP4;
        else return 0;
    }

    void SetEXETouch(int value, int PlayerID)
    {
        if (PlayerID == 1) exetouchP1 = value;
        else if (PlayerID == 2) exetouchP2 = value;
        else if (PlayerID == 3) exetouchP3 = value;
        else if (PlayerID == 4) exetouchP4 = value;
    }

    void SetEXESpeedMod(int value, int PlayerID)
    {
        if (PlayerID == 1) EXESpeedModP1 = value;
        else if (PlayerID == 2) EXESpeedModP2 = value;
        else if (PlayerID == 3) EXESpeedModP3 = value;
        else if (PlayerID == 4) EXESpeedModP4 = value;
    }

    int GetEXESpeedMod(int PlayerID)
    {
        if (PlayerID == 1) return EXESpeedModP1;
        else if (PlayerID == 2) return EXESpeedModP2;
        else if (PlayerID == 3) return EXESpeedModP3;
        else if (PlayerID == 4) return EXESpeedModP4;
        else return 0;
    }

    int GetEXETime(int PlayerID)
    {
        if (PlayerID == 1) return exetimeP1;
        else if (PlayerID == 2) return exetimeP2;
        else if (PlayerID == 3) return exetimeP3;
        else if (PlayerID == 4) return exetimeP4;
        else return 0;
    }

    void SetEXETime(int value, int PlayerID)
    {
        if (PlayerID == 1) exetimeP1 = value;
        else if (PlayerID == 2) exetimeP2 = value;
        else if (PlayerID == 3) exetimeP3 = value;
        else if (PlayerID == 4) exetimeP4 = value;
    }

    #pragma endregion

    #pragma region EXE Methods


    void DespawnEXE(int PlayerID) 
    {
        std::vector<int> DespawnableSlots;

        for (int i = 0; i < 2301; ++i)
        {
            EntityPlayer* entity = GetEntityFromSceneSlot<EntityPlayer>(i);
            if (entity->field_30 == 1 && entity->dword140 == PlayerID && entity->ObjectID == GetObjectIDFromType(ObjectType_Ring))
            {
                DespawnableSlots.insert(DespawnableSlots.begin(), i);
            }
        }

        for (int i = 0; i < DespawnableSlots.size(); ++i)
        {
            EntityPlayer* entity = GetEntityFromSceneSlot<EntityPlayer>(DespawnableSlots[i]);
            DespawnEntity(entity);
        }
    }

    bool CanActivate(EntityPlayer Player, int PlayerID)
    {
        if (PlayerID == 1 && IsPlayerInDebugMode != 0) return false;
        else
        {
            SonicMania::PlayerStatus PlayerState = (SonicMania::PlayerStatus)Player.State;
            if (PlayerState == PLAYERSTATE_DIE) return false;
            else return true;
        }
    }

    bool CanEXEKill(EntityPlayer Player, int PlayerID)
    {
        if (PlayerID == 1 && IsPlayerInDebugMode != 0) return false;
        else
        {
            SonicMania::PlayerStatus PlayerState = (SonicMania::PlayerStatus)Player.State;
            if (PlayerState == PLAYERSTATE_TransportTube_CPZ) return false;
            else return true;
        }
    }

    #pragma endregion


    #pragma region PlayerState DoChase Calls

    void DoChase(EntityPlayer* Player, int PlayerID)
    {
        SetEXETime(0, PlayerID);
        EntityPlayer* ThisObject = (EntityPlayer*)GetAddress(baseAddress + 0xAA7634, 0, 0);
        EntityRing* RingTemp2 = (EntityRing*)ThisObject;
        float angle = ThisObject->dword200;
        int radius = 4;
        int Counter = ThisObject->dword218;
        Counter++;
        int Direction = ThisObject->dword218;
        angle = angle + 0.1;  // or some other value.  Higher numbers = circles faster
        if (angle >= 360)
        {
            angle = 0;


        }
        if (Direction == 1)
        {
            radius++;
        }
        else
        {
            radius--;
        }
        if (radius > 60)
        {
            Direction = 0;
        }
        if (radius < 3)
        {
            Direction = 1;
        }
        int workingX = cos(angle) * radius;
        int workingY = sin(angle) * radius;
        //workingX += ThisObject->dword20C;
        workingY += ThisObject->dword210;



        ThisObject->Direction = false;
        ThisObject->DrawOrder = Player->DrawOrder;

        ThisObject->Position.Y = workingY;
        ThisObject->dword200 = angle;
        //ThisObject->Position.X = ThisObject->dword20C;
        ThisObject->dword218 = Counter;
        ThisObject->dword21C = Direction;


        //ThisObject->Position.Y = workingY;
        if (ThisObject->Position.CalculateDistance(Player->Position) < 140)
        {
            ThisObject->dword208 = 1;
            //printf("IS IN RANGE! \n");

        }
        if (ThisObject->dword208 == 1 && CanActivate(*Player, PlayerID))
        {
            //You Set it off! 
            //MoveToPoint(Vector2(ThisObject->Position.X, ThisObject->Position.Y), Player->Position, 5);
            Vector2 Temp = Vector2(0, 0);
            ThisObject->Position = MoveToPoint(Vector2(ThisObject->dword20C, workingY), Player->Position, (5 + GetEXESpeedMod(PlayerID)));
            ThisObject->dword20C = ThisObject->Position.X;
            ThisObject->dword210 = ThisObject->Position.Y;
            EntityRing* RingTemp = (EntityRing*)ThisObject;

            //printf("SHOULD BE FOLLOWING \n");

            if (Player->Position.CalculateDistance(Player->Position) > DespawnRange)
            {
                SetEXEActive(false, PlayerID);
                DespawnEntity(ThisObject);
            }

        }
        if (ThisObject->Position.CalculateDistance(Player->Position) < 10 && CanEXEKill(*Player, PlayerID))
        {
            
            if (Player->RingCount > 0 && GetEXETouch(PlayerID) < 3)
            {
                Player->RingCount = 0;
                PlaySoundFXS("Global/Hurt.wav");
                Player->State = PLAYERSTATE_HURT;
                switch (Player->Character)
                {
                case Characters_Sonic:
                    SetSpriteAnimation(GetSpritePointer(0xAC6838, 0xA08), 18, &Player->Animation, false, 0);
                    break;
                case Characters_Tails:
                    SetSpriteAnimation(GetSpritePointer(0xAC6838, 0xA0C), 18, &Player->Animation, false, 0);
                    break;
                case Characters_Knuckles:
                    SetSpriteAnimation(GetSpritePointer(0xAC6838, 0xA10), 18, &Player->Animation, false, 0);
                    break;
                case Characters_Mighty:
                    SetSpriteAnimation(GetSpritePointer(0xAC6838, 0xA12), 18, &Player->Animation, false, 0);
                    break;
                case Characters_Ray:
                    SetSpriteAnimation(GetSpritePointer(0xAC6838, 0xA14), 18, &Player->Animation, false, 0);
                    break;
                }
                Player->XVelocity = (Player->XVelocity * -1);
                Player->Grounded = 0;
                Player->YVelocity = -400000;
                SetEXETouch(GetEXETouch(PlayerID) + 1, PlayerID);
            }
            else
            {
                Player->Kill();
                PlaySoundFXS(CompPlus_Common::SFX_EXE_KYS);
                SetEXETouch(0, PlayerID);
            }
            SetEXEActive(false, PlayerID);
            if (GetEXESpeedMod(PlayerID) < 6)
            {
                SetEXESpeedMod(GetEXESpeedMod(PlayerID) + 1, PlayerID);
            }

            DespawnEntity(ThisObject);

        }
    }

    void DoChase1P()
    {
        DoChase(&Player1, 1);
    }

    void DoChase2P()
    {
        DoChase(&Player2, 2);
    }

    void DoChase3P()
    {
        DoChase(&Player3, 3);
    }

    void DoChase4P()
    {
        DoChase(&Player4, 4);
    }

    #pragma endregion

    #pragma region PlayerState ActiveObjectMoveUp Calls

    void ActiveObjectMoveUp(EntityPlayer* Player, int PlayerID)
        {
            EntityPlayer* ThisObject = (EntityPlayer*)GetAddress(baseAddress + 0xAA7634, 0, 0);

            //ThisObject->dword210 = ThisObject->dword210 - 1;

            //if (GetEXEActive(PlayerID) == true)
            //{
            //    ThisObject->Alpha = TransparencyFlag_Transparent;
            //}
            //else
            {
                ThisObject->Alpha = TransparencyFlag_Opaque;
                ThisObject->DrawOrder = Player->DrawOrder;
                float angle = ThisObject->dword200;
                int radius = 4;
                int Counter = ThisObject->dword218;
                Counter++;
                int Direction = ThisObject->dword218;
                angle = angle + 0.1;  // or some other value.  Higher numbers = circles faster
                if (angle >= 360)
                {
                    angle = 0;
                }
                if (Direction == 1)
                {
                    radius++;
                }
                else
                {
                    radius--;
                }
                if (radius > 60)
                {
                    Direction = 0;
                }
                if (radius < 3)
                {
                    Direction = 1;
                }
                int workingX = cos(angle) * radius;
                int workingY = sin(angle) * radius;
                //workingX += ThisObject->dword20C;
                workingY += ThisObject->dword210;


                //ThisObject->DrawOrder = 14;

                ThisObject->Position.Y = workingY;
                ThisObject->dword200 = angle;
                //ThisObject->Position.X = ThisObject->dword20C;
                ThisObject->dword218 = Counter;
                ThisObject->dword21C = Direction;
                //ThisObject->Position.Y = workingY;
                if (ThisObject->Position.CalculateDistance(Player->Position) < 140 && CanActivate(*Player, PlayerID))
                {
                    ThisObject->dword208 = 1;
                    //printf("IS IN RANGE! THEN CHANGE STATE \n");

                    if (PlayerID == 1) ThisObject->State = DoChase1P;
                    else if (PlayerID == 2) ThisObject->State = DoChase2P;
                    else if (PlayerID == 3) ThisObject->State = DoChase3P;
                    else if (PlayerID == 4) ThisObject->State = DoChase4P;

                    ThisObject->Alpha = TransparencyFlag_Opaque;
                    SetEXEActive(true, PlayerID);
                    PlaySoundFXS(CompPlus_Common::SFX_EXE_Laugh);
                }
            }

            return;

        }

    void ActiveObjectMoveUp1P()
    {
        if (IsPlayerInDebugMode == 0) ActiveObjectMoveUp(&Player1, 1);
    }

    void ActiveObjectMoveUp2P()
    {
        ActiveObjectMoveUp(&Player2, 2);
    }

    void ActiveObjectMoveUp3P()
    {
        ActiveObjectMoveUp(&Player3, 3);
    }

    void ActiveObjectMoveUp4P()
    {
        ActiveObjectMoveUp(&Player4, 4);
    }

    #pragma endregion

    #pragma region Boolean Validators

    bool IsActiveObjectMoveUp(EntityPlayer* Player, int PlayerID)
    {
        if (PlayerID == 1 && Player->State == ActiveObjectMoveUp1P) return true;
        else if (PlayerID == 2 && Player->State == ActiveObjectMoveUp2P) return true;
        else if (PlayerID == 3 && Player->State == ActiveObjectMoveUp3P) return true;
        else if (PlayerID == 4 && Player->State == ActiveObjectMoveUp4P) return true;
        return false;
    }

    bool IsDoChase(EntityPlayer* Player, int PlayerID)
    {
        if (PlayerID == 1 && Player->State == DoChase1P) return true;
        else if (PlayerID == 2 && Player->State == DoChase2P) return true;
        else if (PlayerID == 3 && Player->State == DoChase3P) return true;
        else if (PlayerID == 4 && Player->State == DoChase4P) return true;
        return false;
    }

    #pragma endregion

    #pragma region General Logic Methods

    void ResetEXE(int PlayerID = -1) 
    {
        if (PlayerID != -1) 
        {
            SetEXEActive(false, PlayerID);
            SetEXETime(0, PlayerID);
            SetEXESpeedMod(0, PlayerID);
            SetEXETouch(0, PlayerID);
            SetEXERespawn(true, PlayerID);
            DespawnEXE(PlayerID);
        }
        else 
        {
            for (int i = 1; i <= 4; i++)
            {
                SetEXEActive(false, i);
                SetEXETime(0, i);
                SetEXESpeedMod(0, i);
                SetEXETouch(0, i);
                SetEXERespawn(true, i);
            }
        }

    }

    void SpawnEXE(int TempXlocation, int TempYlocation, int PlayerID)
    {
        int NumberOfPlayers = SonicMania::Options->CompetitionSession.NumberOfPlayers;

        if (PlayerID == 2 && NumberOfPlayers < 2) return;
        if (PlayerID == 3 && NumberOfPlayers < 3) return;
        if (PlayerID == 4 && NumberOfPlayers < 4) return;


        EntityPlayer* Spawned = (EntityPlayer*)SpawnObject(GetObjectIDFromType(ObjectType_Ring), 0, Vector2(TempXlocation, TempYlocation));


        if (PlayerID == 1) Spawned->State = ActiveObjectMoveUp1P;
        else if (PlayerID == 2) Spawned->State = ActiveObjectMoveUp2P;
        else if (PlayerID == 3) Spawned->State = ActiveObjectMoveUp3P;
        else if (PlayerID == 4) Spawned->State = ActiveObjectMoveUp4P;


        Spawned->InkEffect = Ink_Alpha;
        Spawned->Alpha = 0;


        //Spawned->Status = 0x00000000;
        Spawned->dword20C = TempXlocation;
        Spawned->dword210 = TempYlocation;
        EntityRing* RingTemp = (EntityRing*)Spawned;
        //SetSpriteAnimation(EXEAnimID, 4, &RingTemp->Animation, false, 0);
        float angle = 0;
        Spawned->dword200 = RandomNumber(1, 358);; //Angle
        Spawned->dword204 = RandomNumber(0, 2); //Type
        Spawned->dword208 = 0; // Chase Enabled 
        Spawned->dword214 = RandomNumber(4, 32);//Radius
        Spawned->dword218 = 0; //count
        Spawned->dword21C = 0; //Direction
        Spawned->field_30 = 1; //IsEXE
        Spawned->dword140 = PlayerID; //PlayerID
    }

    void LoadEntityCustom(int PlayerID = -1) 
    {
        bool AllowRespawnP1 = (PlayerID == -1 ? true : PlayerID == 1 && GetEXERespawn(PlayerID));
        bool AllowRespawnP2 = (PlayerID == -1 ? true : PlayerID == 2 && GetEXERespawn(PlayerID));
        bool AllowRespawnP3 = (PlayerID == -1 ? true : PlayerID == 3 && GetEXERespawn(PlayerID));
        bool AllowRespawnP4 = (PlayerID == -1 ? true : PlayerID == 4 && GetEXERespawn(PlayerID));

        for (int i = 0; i < SpawnPositions.size(); ++i)
        {
            auto Position = SpawnPositions[i];

            printf("Loading EXE Object (");
            int TempXlocation = Position.X;
            int TempYlocation = Position.Y;

            printf("X: %d, ", TempXlocation);
            printf("Y: %d)\n", TempYlocation);

            if (AllowRespawnP1) SpawnEXE(TempXlocation, TempYlocation, 1);
            if (AllowRespawnP2) SpawnEXE(TempXlocation, TempYlocation, 2);
            if (AllowRespawnP3) SpawnEXE(TempXlocation, TempYlocation, 3);
            if (AllowRespawnP4) SpawnEXE(TempXlocation, TempYlocation, 4);
        }

        if (PlayerID == -1)
        {
            SetEXERespawn(false, 1);
            SetEXERespawn(false, 2);
            SetEXERespawn(false, 3);
            SetEXERespawn(false, 4);
        }
        else SetEXERespawn(false, PlayerID);

    }

    void ReplaceEntityCustom()
    {
        SpawnPositions.clear();
        Entity* ClosestEntity = nullptr;
        for (int i = 0; i < 2301; ++i)
        {
            auto entity = GetEntityFromSceneSlot<Entity>(i);

            if (entity->ObjectID != GetObjectIDFromType(ObjectType_Ring))
                continue;

            if (((EntityRing*)entity)->Type != 1)
                continue;

            if (((EntityRing*)entity)->field_57 != 0)
                continue;

            SpawnPositions.insert(SpawnPositions.begin(), Vector2(entity->Position.X, entity->Position.Y));
            DespawnEntity(entity);
        }

    }

    #pragma endregion

    #pragma region General Player Methods

    void OnPlayerDraw(EntityPlayer EXE, EntityPlayer* Player, int offset)
    {
        Vector2 Position = Vector2((EXE.Position.X - GetPointer(0xAA7628, 0x96000 + offset)), (EXE.Position.Y - GetPointer(0xAA7628, 0x96004 + offset)));
        if (EXE.dword208 == 1)
        {
            if ((EXE.Position.X - Player->Position.X) > 0) DrawEXE(*Player, Position, false, 5, 1);
            else DrawEXE(*Player, Position, false, 5, 0);
        }
        else if (EXE.dword208 == 0)
        {
            if ((EXE.Position.X - Player->Position.X) > 0) DrawEXE(*Player, Position, false, 4, 1);
            else DrawEXE(*Player, Position, false, 4, 0);
        }
    }

    void OnPlayerFrame(EntityPlayer* Player, int PlayerID)
    {
        if (Player->State == PLAYERSTATE_DIE)
        {
            ResetEXE(PlayerID);
        }
        else if (GetEXERespawn(PlayerID)) 
        {
            LoadEntityCustom(PlayerID);
        }

        if (GetEXEActive(PlayerID))
        {
            if (GetEXETime(PlayerID) > 60)
            {
                SetEXETime(0, PlayerID);
                SetEXEActive(false, PlayerID);
                if (GetEXESpeedMod(PlayerID) < 6)
                {
                    SetEXESpeedMod(GetEXESpeedMod(PlayerID) + 1, PlayerID);
                }
            }
            else
            {
                SetEXETime(GetEXETime(PlayerID) + 1, PlayerID);
            }
        }
    }

    #pragma endregion

    #pragma region General Methods

    void OnFrame()
    {
        if (CompPlus_Status::IsExecutorStage)
        {
            CanDrawP1 = true;
            CanDrawP2 = true;
            CanDrawP3 = true;
            CanDrawP4 = true;
            if (GameState & GameState_Running && !(GameState & GameState_SoftPause))
            {
                OnPlayerFrame(&Player1, 1);
                OnPlayerFrame(&Player2, 2);
                OnPlayerFrame(&Player3, 3);
                OnPlayerFrame(&Player4, 4);
            }
        }
    }

    void OnDraw()
    {
        ushort pointer = GetSpritePointer(0xAA7634, 0x14);
        int screen = 0;

        if (pointer == 0) screen = 0;
        else if (pointer == 1) screen = 1;
        else if (pointer == 2) screen = 2;
        else if (pointer == 3) screen = 3;

        if (CompPlus_Status::IsExecutorStage)
        {
            if (CanDraw(screen))
            {
                SetTempColors();
                int offset = 0x96030 * screen;
                for (int i = 0; i < 2301; ++i)
                {
                    SonicMania::Entity& entity = *SonicMania::GetEntityFromSceneSlot<SonicMania::Entity>(i);

                    if (entity.field_30 == 1 && entity.Alpha == 0)
                    {
                        EntityPlayer* Spawned = SonicMania::GetEntityFromSceneSlot<SonicMania::EntityPlayer>(i);

                        if (Spawned->dword140 == 1 && screen == 0) OnPlayerDraw(*Spawned, &Player1, offset);
                        else if (Spawned->dword140 == 2 && screen == 1) OnPlayerDraw(*Spawned, &Player2, offset);
                        else if (Spawned->dword140 == 3 && screen == 2) OnPlayerDraw(*Spawned, &Player3, offset);
                        else if (Spawned->dword140 == 4 && screen == 3) OnPlayerDraw(*Spawned, &Player4, offset);
                    }
                }
                ResetColors();
            }
        }

        EndDraw(screen);
    }

    void OnStartTimer()
    {
        ResetEXE();
        if (CompPlus_Status::IsExecutorStage)
        {
            LoadEXESprites();
            ReplaceEntityCustom();
            LoadEntityCustom();
        }
    }

    void Init()
    {

    }

    #pragma endregion













}