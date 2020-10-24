#include "stdafx.h"
#include "TitleScreen.h"
#include "ManiaModLoader.h"
#include "CompPlus_Extensions/PointScrolling.h"
#include "CompPlus_Extensions/ManiaExt.h"
#include "SonicMania.h"
#include "CompPlus_Core/CompPlus_Common.h"
#include "CompPlus_Core/CompPlus_Patches.h"

namespace CompPlus_TitleScreen 
{
    using namespace SonicMania;

    bool CompPlusLogoLoaded = false;
    int CompPlusLogoID = -1;

    int CurrentLifespan = 0;
    int NeededLifespan = 70;
    int Idle = 0;

    bool StillDrawing = false;

    void OnDraw() 
    {

    }

    void SetBG() 
    {
        SonicMania::SetUIBG_BGColor(199, 235, 255);

        if (CurrentLifespan >= NeededLifespan) 
        {
            SonicMania::SetUIBG_FGLowColor(247, 146, 24);
            SonicMania::SetUIBG_FGHighColor(57, 178, 206);
        }
        else 
        {
            SonicMania::SetUIBG_FGLowColor(199, 235, 255);
            SonicMania::SetUIBG_FGHighColor(199, 235, 255);
        }
    }

    int OnPlusLogoDraw(EntityAnimationData* AnimData, Vector2* Position, BOOL ScreenRelative)
    {
        StillDrawing = true;
        Idle = 10;

        if (!CompPlusLogoLoaded)
        {
            CompPlusLogoID = LoadAnimation("Title/PlusLogoSMCP.bin", Scope_Stage);
            CompPlusLogoLoaded = true;
        }

        SetBG();



        EntityInfo->CurrentEntity->Base.DrawOrder = 1;

        if (CurrentLifespan >= NeededLifespan)
        {
            void* OriginalPtr = AnimData->Animationptr;
            short OriginalCurrentAnimation = AnimData->CurrentAnimation;
            short OriginalCurrentFrame = AnimData->CurrentFrame;
            short OriginalDuration = AnimData->Duration;
            short OriginalFrameCount = AnimData->FrameCount;
            short OriginalLastAnimation = AnimData->LastAnimation;
            short OriginalSpeed = AnimData->Speed;
            short OriginalUnknown0E = AnimData->Unknown0E;
            short Originalunknown14 = AnimData->unknown14;
            short OriginalUserFrameCount = AnimData->UserFrameCount;

            SonicMania::SetSpriteAnimation(CompPlusLogoID, OriginalCurrentAnimation, AnimData, true, OriginalCurrentFrame);
            SonicMania::Vector2 OurPosition = SonicMania::Vector2(EntityInfo->CurrentEntity->Base.Position.X, EntityInfo->CurrentEntity->Base.Position.Y + 20);
            DrawSprite(AnimData, &OurPosition, ScreenRelative);

            AnimData->Animationptr = OriginalPtr;
            AnimData->CurrentAnimation = OriginalCurrentAnimation;
            AnimData->CurrentFrame = OriginalCurrentFrame;
            AnimData->Duration = OriginalDuration;
            AnimData->FrameCount = OriginalFrameCount;
            AnimData->LastAnimation = OriginalLastAnimation;
            AnimData->Speed = OriginalSpeed;
            AnimData->Unknown0E = OriginalUnknown0E;
            AnimData->unknown14 = Originalunknown14;
            AnimData->UserFrameCount = OriginalUserFrameCount;
        }
        else CurrentLifespan++;
   
        return DrawSprite(AnimData, Position, ScreenRelative);

    }

    bool BeginKill = false;

    void OnFrame()
    {
        if (CurrentSceneInt == 1) SetBG();

        if (!StillDrawing)
        {
            Reload();
        }
        if (StillDrawing && Idle <= 0) StillDrawing = false;
        else Idle--;
    }

    void Reload() 
    {
        CurrentLifespan = 0;
        CompPlusLogoLoaded = false;
        CompPlusLogoID = -1;
    }
}