#pragma once
#include "IDanceBehavior.h"

class DanceMinuetBehavior : public IDanceBehavior
{
public:
	DanceMinuetBehavior();
	virtual ~DanceMinuetBehavior();
	virtual void Dance() override;
};