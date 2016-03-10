#pragma once
#include "Duck.h"

class RedheadDuck : public Duck
{
public:
	RedheadDuck();
	virtual ~RedheadDuck();
	void Display() const override;
};
