#pragma once
#include "IQuackBehavior.h"

class SqueakBehavior : public IQuackBehavior
{
public:
	SqueakBehavior();
	virtual ~SqueakBehavior();
	virtual void Quack() override;
};
