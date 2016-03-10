#pragma once
#include "Duck.h"
class DeckoyDuck : public Duck
{
public:
	DeckoyDuck();
	virtual ~DeckoyDuck();
	void Display() const override;
	void Dance() override;
};

