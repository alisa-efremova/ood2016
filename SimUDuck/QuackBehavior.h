#pragma once
#include "IQuackBehavior.h"

class QuackBehavior : public IQuackBehavior
{
public:
	QuackBehavior();
	virtual void Quack() override;
};

