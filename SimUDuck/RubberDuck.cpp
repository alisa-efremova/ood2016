#include "stdafx.h"
#include "RubberDuck.h"
#include <memory>
#include "FlyNoWayBehavior.h"
#include "SqueakBehavior.h"
#include "DanceNoWayBehavior.h"

RubberDuck::RubberDuck()
	: Duck(make_unique<FlyNoWayBehavior>(), make_unique<SqueakBehavior>(), make_unique<DanceNoWayBehavior>())
{
}

RubberDuck::~RubberDuck()
{
}

void RubberDuck::Display() const
{
	cout << "I'm rubber duck" << endl;
}