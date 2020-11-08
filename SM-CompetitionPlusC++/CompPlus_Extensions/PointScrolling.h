#pragma once
#include "include/ManiaAPI/SonicMania.h"

using namespace SonicMania;

extern bool HasTransValsBeenDefined;
extern bool HasTransCompleted;
extern bool TransXDestReached;
extern bool TransYDestReached;
extern int PosXCurrent;
extern int PosYCurrent;
extern int TransXObjective;
extern int TransYObjective;

extern bool inRange(unsigned low, unsigned high, unsigned x);
extern void InitPosition(short x, short y);
extern void UpdateTransitionObjective(short x1, short y1, short x2, short y2);
extern bool DestReached();
extern void UpdatePosXCurrent(int speed);
extern void UpdatePosYCurrent(int speed);
extern void MoveTransition(int speed);
extern void ScrollToPosition(short x1, short y1, short x2, short y2, int& DestX, int& DestY, bool startFresh);
extern void ScrollToPosition(short x1, short y1, short x2, short y2, int viewSlotID, bool startFresh);

