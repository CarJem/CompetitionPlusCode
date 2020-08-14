#include "stdafx.h"
#include "PointScrolling.h"

using namespace SonicMania;

bool HasTransValsBeenDefined = true;
bool HasTransCompleted = true;

bool TransXDestReached = false;
bool TransYDestReached = false;

int PosXCurrent = 0;
int PosYCurrent = 0;

int TransXObjective = 0;
int TransYObjective = 0;




bool inRange(unsigned low, unsigned high, unsigned x)
{
	return (low <= x && x <= high);
}

void InitPosition(short x, short y)
{
	PosXCurrent = x;
	PosYCurrent = y;
}

void UpdateTransitionObjective(short x1, short y1, short x2, short y2)
{
	TransXObjective = x1;
	TransYObjective = y1;
	TransXDestReached = false;
	TransYDestReached = false;
	HasTransValsBeenDefined = true;
}

bool DestReached() 
{
	TransXDestReached = (PosXCurrent == TransXObjective);
	TransYDestReached = (PosYCurrent == TransYObjective);

	return TransXDestReached && TransYDestReached;
}

void UpdatePosXCurrent(int speed)
{
	if (TransXObjective > PosXCurrent) 
	{
		if (TransXObjective < PosXCurrent + speed)
		{
			PosXCurrent = PosXCurrent + 1;
		}
		else
		{
			PosXCurrent = PosXCurrent + speed;
		}
	}
	else if (TransXObjective < PosXCurrent) 
	{
		if (TransXObjective > PosXCurrent - speed)
		{
			PosXCurrent = PosXCurrent - 1;
		}
		else
		{
			PosXCurrent = PosXCurrent - speed;
		}
	}
	else
	{
		TransXDestReached = true;
	}
}

void UpdatePosYCurrent(int speed)
{
	if (TransYObjective > PosYCurrent)
	{
		if (TransYObjective < PosYCurrent + speed)
		{
			PosYCurrent = PosYCurrent + 1;
		}
		else 
		{
			PosYCurrent = PosYCurrent + speed;
		}
	}
	else if (TransYObjective < PosYCurrent)
	{
		if (TransYObjective > PosYCurrent - speed)
		{
			PosYCurrent = PosYCurrent - 1;
		}
		else
		{
			PosYCurrent = PosYCurrent - speed;
		}
	}
	else
	{
		TransYDestReached = true;
	}
}

void MoveTransition(int speed)
{
	if (!DestReached()) 
	{
		if (!TransXDestReached) UpdatePosXCurrent(speed);
		if (!TransYDestReached) UpdatePosYCurrent(speed);
	}
}


void ScrollToPosition(short x1, short y1, short x2, short y2, int viewSlotID, bool startFresh)
{
	Entity& view = *GetEntityFromSceneSlot<Entity>(viewSlotID);

	if (startFresh) 
	{
		HasTransValsBeenDefined = false;
		HasTransCompleted = false;
	}

	if (HasTransValsBeenDefined == false || HasTransCompleted == false)
	{
		if (HasTransValsBeenDefined == false) UpdateTransitionObjective(x1, y1, x2, y2);
		MoveTransition(7);

		view.Position.X = PosXCurrent;
		view.Position.Y = PosYCurrent;

		if (DestReached())
		{
			HasTransCompleted = true;
		}
	}
	else
	{
		view.Position.X = x1;
		view.Position.Y = y1;
	}
}