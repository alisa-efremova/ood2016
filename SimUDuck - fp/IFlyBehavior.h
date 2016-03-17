#pragma once
#include "stdafx.h"

using namespace std;

class IFlyBehavior
{
public:
	IFlyBehavior() {};
	virtual ~IFlyBehavior() {};
	virtual void Fly() = 0;
};
