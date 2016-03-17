#include "stdafx.h"
#include "RubberDuck.h"
#include <memory>

RubberDuck::RubberDuck()
	: Duck(&FlyBehavior::FlyNoWay, &QuackBehavior::Squeak, &DanceBehavior::DanceNoWay)
{
}

RubberDuck::~RubberDuck()
{
}

void RubberDuck::Display() const
{
	cout << "I'm rubber duck" << endl;
}