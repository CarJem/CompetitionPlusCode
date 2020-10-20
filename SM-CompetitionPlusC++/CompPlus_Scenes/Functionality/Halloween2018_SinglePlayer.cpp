#include "stdafx.h"
#include "ManiaModLoader.h"
#include "SonicMania.h"
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include "CompPlus_Core/CompPlus_Common.h"
#include "CompPlus_Core/CompPlus_Status.h"

namespace CompPlus_Halloween2018_SinglePlayer
{
    using namespace SonicMania;

    int offsetX = 0;
    int offsetY = 0;
    int Timeout = 0;

    int EXEAnimID = 0;


    void LoadSprites()
    {
        EXEAnimID = LoadAnimation(CompPlus_Common::Anim_EXE_Sprites, Scope_Stage);
    }

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

    bool EXEActive = false;
    int exetime = 0;
    int EXESpeedMod = 0;
    int exetouch = 0;

    void DoChase()
    {
        exetime = 0;
        EntityPlayer* ThisObject = (EntityPlayer*)GetAddress(baseAddress + 0xAA7634, 0, 0);
        EntityRing* RingTemp2 = (EntityRing*)ThisObject;
        if ((ThisObject->Position.X - Player1.Position.X) > 0)
        {
            printf("Setsprite Left \n");
            SetSpriteAnimation(EXEAnimID, 5, &RingTemp2->Animation, true, 1);
        }
        else
        {
            printf("Setsprite Right. \n");
            SetSpriteAnimation(EXEAnimID, 5, &RingTemp2->Animation, true, 0);
        }
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
        ThisObject->DrawOrder = Player1.DrawOrder;

        ThisObject->Position.Y = workingY;
        ThisObject->dword200 = angle;
        //ThisObject->Position.X = ThisObject->dword20C;
        ThisObject->dword218 = Counter;
        ThisObject->dword21C = Direction;


        //ThisObject->Position.Y = workingY;
        if (ThisObject->Position.CalculateDistance(Player1.Position) < 140)
        {
            ThisObject->dword208 = 1;
            printf("IS IN RANGE! \n");

        }
        if (ThisObject->dword208 == 1)
        {
            //You Set it off! 
            //MoveToPoint(Vector2(ThisObject->Position.X, ThisObject->Position.Y), Player1.Position, 5);
            Vector2 Temp = Vector2(0, 0);
            ThisObject->Position = MoveToPoint(Vector2(ThisObject->dword20C, workingY), Player1.Position, (4 + EXESpeedMod));
            ThisObject->dword20C = ThisObject->Position.X;
            ThisObject->dword210 = ThisObject->Position.Y;
            EntityRing* RingTemp = (EntityRing*)ThisObject;

            printf("SHOULD BE FOLLOWING \n");
        }
        if (ThisObject->Position.CalculateDistance(Player1.Position) < 10)
        {
            if (Player1.RingCount > 0 && exetouch < 3)
            {
                Player1.RingCount = 0;
                PlaySoundFXS("Global/Hurt.wav");
                Player1.State = PLAYERSTATE_HURT;
                switch (Player1.Character)
                {
                case Characters_Sonic:
                    SetSpriteAnimation(GetSpritePointer(0xAC6838, 0xA08), 18, &Player1.Animation, false, 0);
                    break;
                case Characters_Tails:
                    SetSpriteAnimation(GetSpritePointer(0xAC6838, 0xA0C), 18, &Player1.Animation, false, 0);
                    break;
                case Characters_Knuckles:
                    SetSpriteAnimation(GetSpritePointer(0xAC6838, 0xA10), 18, &Player1.Animation, false, 0);
                    break;
                case Characters_Mighty:
                    SetSpriteAnimation(GetSpritePointer(0xAC6838, 0xA12), 18, &Player1.Animation, false, 0);
                    break;
                case Characters_Ray:
                    SetSpriteAnimation(GetSpritePointer(0xAC6838, 0xA14), 18, &Player1.Animation, false, 0);
                    break;
                }
                Player1.XVelocity = (Player1.XVelocity * -1);
                Player1.Grounded = 0;
                Player1.YVelocity = -400000;
                exetouch++;
            }
            else
            {
                Player1.Kill();
                PlaySoundFXS(CompPlus_Common::SFX_EXE_KYS);
                exetouch = 0;
            }
            EXEActive = false;
            if (EXESpeedMod < 6)
            {
                EXESpeedMod++;
            }

            DespawnEntity(ThisObject);

        }
    }

    void ActiveObjectMoveUp()
    {
        EntityPlayer* ThisObject = (EntityPlayer*)GetAddress(baseAddress + 0xAA7634, 0, 0);

        //ThisObject->dword210 = ThisObject->dword210 - 1;

        if (EXEActive == true)
        {
            ThisObject->Alpha = TransparencyFlag_Transparent;
        }
        else
        {
            ThisObject->Alpha = TransparencyFlag_Opaque;
            ThisObject->DrawOrder = Player1.DrawOrder;
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

            if (ThisObject->dword208 == 0)
            {
                //ThisObject->dword210--;
                EntityRing* RingTemp = (EntityRing*)ThisObject;

                if ((ThisObject->Position.X - Player1.Position.X) > 0)
                {
                    SetSpriteAnimation(EXEAnimID, 4, &RingTemp->Animation, true, 1);
                }
                else
                {
                    SetSpriteAnimation(EXEAnimID, 4, &RingTemp->Animation, true, 0);
                }
            }


            ThisObject->DrawOrder = 14;

            ThisObject->Position.Y = workingY;
            ThisObject->dword200 = angle;
            //ThisObject->Position.X = ThisObject->dword20C;
            ThisObject->dword218 = Counter;
            ThisObject->dword21C = Direction;
            //ThisObject->Position.Y = workingY;
            if (ThisObject->Position.CalculateDistance(Player1.Position) < 140)
            {
                ThisObject->dword208 = 1;
                printf("IS IN RANGE! THEN CHANGE STATE \n");
                ThisObject->State = DoChase;
                ThisObject->Alpha = TransparencyFlag_Opaque;
                EXEActive = true;
                PlaySoundFXS(CompPlus_Common::SFX_EXE_Laugh);
            }
        }

        return;

    }

    int RandomNumber(int min, int max)
    {
        return rand() % (max - min) + min;
    }

    void ReplaceEntityCustom()
    {
        Entity* ClosestEntity = nullptr;
        for (int i = 0; i < 2301; ++i)
        {
            auto entity = GetEntityFromSceneSlot<Entity>(i);
            // Skip itself
            if (entity == &Player1)
                continue;


            if (entity->ObjectID != GetObjectIDFromType(ObjectType_Ring))
                continue;

            if (((EntityRing*)entity)->Type != 2)
                continue;
            printf("Called Changed Entity \n");
            int TempXlocation = entity->Position.X;
            int TempYlocation = entity->Position.Y;

            printf("X: %d \n", TempXlocation);
            printf("Y: %d \n", TempYlocation);
            EntityPlayer* Spawned = (EntityPlayer*)SpawnObject(GetObjectIDFromType(ObjectType_Ring), 0, Vector2(TempXlocation, TempYlocation));

            Spawned->State = ActiveObjectMoveUp;
            //Spawned->Status = 0x00000000;
            Spawned->dword20C = TempXlocation;
            Spawned->dword210 = TempYlocation;
            EntityRing* RingTemp = (EntityRing*)Spawned;
            //SetSpriteAnimation(EXEAnimID, 4, &RingTemp->Animation, false, 0);
            float angle = 0;
            Spawned->dword200 = RandomNumber(1, 358);;//Angle
            Spawned->dword204 = RandomNumber(0, 2);//Type
            Spawned->dword208 = 0; // Chase Enabled 
            Spawned->dword214 = RandomNumber(4, 32);//Radius
            Spawned->dword218 = 0; //count
            Spawned->dword21C = 0; //Direction

            DespawnEntity(entity);
        }

    }

    void DoOnStartTimer()
    {
        if (CompPlus_Status::IsExecutorStage)
        {
            LoadSprites();
            ReplaceEntityCustom();
        }
        EXEActive = false;
        exetime = 0;
        EXESpeedMod = 0;
        exetouch = 0;
    }

    static int HookStartTimerAddyJMPBACK = baseAddress + 0x016034;

    static __declspec(naked) void HookTimer()
    {
        __asm
        {
            mov[eax + 0x30], 0x00000001
            pushad;

        }
        DoOnStartTimer();
        __asm
        {
            popad;
            jmp HookStartTimerAddyJMPBACK
        }
    }

    void PatchHookOnStartTimer()
    {
        WriteData<7>((void*)(baseAddress + 0x01602D), 0x90);
        WriteJump((void*)(baseAddress + 0x01602D), HookTimer);
    }

    void Init()
    {
        // LB
        BYTE LBPatch[6]{ (BYTE)0x09, (BYTE)0x42, (BYTE)0x4C, (BYTE)0x90, (BYTE)0x90, (BYTE)0x90 };
        WriteData((BYTE*)(baseAddress + 0x001E6358), LBPatch, 6);
        // RB
        BYTE RBPatch[6]{ (BYTE)0x09, (BYTE)0x42, (BYTE)0x70, (BYTE)0x90, (BYTE)0x90, (BYTE)0x90 };
        WriteData((BYTE*)(baseAddress + 0x001E6362), RBPatch, 6);

        //Unbind C
        //WriteData<3>((void*)(baseAddress + 0x000C3EB7), 0x90);
        DWORD PatchOnTimerStart;
        int PatchOnTimerCode = baseAddress + 0x16000;
        VirtualProtect((void*)PatchOnTimerCode, 0x00178000, PAGE_EXECUTE_READWRITE, &PatchOnTimerStart);
        PatchHookOnStartTimer();
    }

    void OnFrame()
    {
        if (CompPlus_Status::IsExecutorStage)
        {
            if (GameState & GameState_Running && !(GameState & GameState_SoftPause))
            {
                if (Player1.State == PLAYERSTATE_DIE)
                {
                    EXEActive = false;
                    exetime = 0;
                    EXESpeedMod = 0;
                    exetouch = 0;
                }
                if (EXEActive)
                {
                    if (exetime > 60)
                    {
                        exetime = 0;
                        EXEActive = false;
                        if (EXESpeedMod < 6)
                        {
                            EXESpeedMod++;
                        }
                    }
                    else
                    {
                        exetime++;
                    }
                }
            }
        }
    }









}