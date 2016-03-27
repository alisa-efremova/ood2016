#pragma once
#include "IDanceBehavior.h"

class DanceWaltzBehavior : public IDanceBehavior
{
public:
	DanceWaltzBehavior();
	virtual void Dance() override;
};