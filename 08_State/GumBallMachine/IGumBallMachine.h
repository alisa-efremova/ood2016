#pragma once
#include "IState.h"

class IGumBallMachine
{
public:
	virtual void ReleaseBall() = 0;
	virtual void ReleaseQuaters() = 0;
	virtual unsigned GetBallCount()const = 0;
	virtual unsigned GetQuarterCount()const = 0;

	virtual void SetSoldOutState() = 0;
	virtual void SetNoQuarterState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetHasQuarterState() = 0;

	virtual ~IGumBallMachine() = default;
};