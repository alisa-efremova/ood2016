#pragma once
#include "IQuackBehavior.h"

class MuteQuackBehavior : public IQuackBehavior
{
public:
	MuteQuackBehavior();
	virtual void Quack() override;
};
