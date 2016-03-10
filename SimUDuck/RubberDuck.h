#pragma once
#include "Duck.h"
class RubberDuck : public Duck
{
public:
	RubberDuck();
	virtual ~RubberDuck();
	void Display() const override;
	void Dance() override;
};
