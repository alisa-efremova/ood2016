#pragma once
#include "IDanceBehavior.h"

class DanceWaltzBehavior : public IDanceBehavior
{
public:
	DanceWaltzBehavior();
	virtual ~DanceWaltzBehavior();
	virtual void Dance() override;
};