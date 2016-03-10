#pragma once
#include "Duck.h"
class ModelDuck : public Duck
{
public:
	ModelDuck();
	virtual ~ModelDuck();
	void Display() const override;
	void Dance() override;
};
