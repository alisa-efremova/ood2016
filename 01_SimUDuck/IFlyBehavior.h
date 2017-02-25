#pragma once
#include "stdafx.h"

class IFlyBehavior
{
public:
	virtual ~IFlyBehavior() {};
	virtual void Fly() = 0;
};
