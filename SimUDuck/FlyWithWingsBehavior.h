#pragma once
#include "IFlyBehavior.h"

class FlyWithWingsBehavior : public IFlyBehavior
{
public:
	FlyWithWingsBehavior();
	virtual ~FlyWithWingsBehavior();
	virtual void Fly() override;
private:
	unsigned int m_flightCount;
};
