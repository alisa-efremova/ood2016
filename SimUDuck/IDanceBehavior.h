#pragma once
#include "stdafx.h"

class IDanceBehavior
{
public:
	virtual ~IDanceBehavior() {};
	virtual void Dance() = 0;
};
