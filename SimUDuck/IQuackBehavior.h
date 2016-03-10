#pragma once
#include "stdafx.h"

using namespace std;

class IQuackBehavior
{
public:
	IQuackBehavior() {};
	virtual ~IQuackBehavior() {};
	virtual void Quack() = 0;
};