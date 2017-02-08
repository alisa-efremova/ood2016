#include "stdafx.h"
#include "RedheadDuck.h"
#include <memory>

using namespace std;

RedheadDuck::RedheadDuck()
	: Duck(FlyBehavior::MakeFlyWithWings(), QuackBehavior::Quack, DanceBehavior::DanceMinuet)
{
}

void RedheadDuck::Display() const
{
	cout << "I'm redhead duck" << endl;
}
