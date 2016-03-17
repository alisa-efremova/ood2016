#include "stdafx.h"
#include "RedheadDuck.h"
#include <memory>

RedheadDuck::RedheadDuck()
	: Duck(FlyBehavior::FlyWithWings(), QuackBehavior::Quack, DanceBehavior::DanceMinuet)
{
}

RedheadDuck::~RedheadDuck()
{
}

void RedheadDuck::Display() const
{
	cout << "I'm redhead duck" << endl;
}
