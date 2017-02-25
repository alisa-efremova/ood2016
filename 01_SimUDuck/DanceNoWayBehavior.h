#pragma once
#include "IDanceBehavior.h"

class DanceNoWayBehavior : public IDanceBehavior
{
public:
	DanceNoWayBehavior();
	virtual void Dance() override;
};