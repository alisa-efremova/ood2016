#pragma once
#include "IFlyBehavior.h"

class FlyNoWayBehavior : public IFlyBehavior
{
public:
	FlyNoWayBehavior();
	virtual void Fly() override;
};
