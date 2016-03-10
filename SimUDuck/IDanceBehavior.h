#pragma once
#include "stdafx.h"

using namespace std;

class IDanceBehavior
{
public:
	IDanceBehavior() {};
	virtual ~IDanceBehavior() {};
	virtual void Dance() = 0;
};
