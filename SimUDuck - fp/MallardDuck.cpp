#include "stdafx.h"
#include "MallardDuck.h"
#include <memory>

using namespace std;

MallardDuck::MallardDuck()
	: Duck(FlyBehavior::MakeFlyWithWings(), QuackBehavior::Quack, DanceBehavior::DanceWaltz)
{
}

void MallardDuck::Display() const
{
	cout << "I'm mallard duck" << endl;
}