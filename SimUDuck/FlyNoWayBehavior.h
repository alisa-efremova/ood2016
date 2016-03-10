#pragma once
#include "IFlyBehavior.h"

class FlyNoWayBehavior : public IFlyBehavior
{
public:
	FlyNoWayBehavior();
	virtual ~FlyNoWayBehavior();
	virtual void Fly() override;
};
