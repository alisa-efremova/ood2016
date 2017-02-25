#pragma once
#include "stdafx.h"

class IQuackBehavior
{
public:
	virtual ~IQuackBehavior() {};
	virtual void Quack() = 0;
};