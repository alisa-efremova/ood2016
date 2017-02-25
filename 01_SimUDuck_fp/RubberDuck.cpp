#include "stdafx.h"
#include "RubberDuck.h"
#include <memory>

using namespace std;

RubberDuck::RubberDuck()
	: Duck(FlyBehavior::FlyNoWay, QuackBehavior::Squeak, DanceBehavior::DanceNoWay)
{
}

void RubberDuck::Display() const
{
	cout << "I'm rubber duck" << endl;
}