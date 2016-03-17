#include "stdafx.h"
#include "MallardDuck.h"
#include <memory>

MallardDuck::MallardDuck()
	: Duck(FlyBehavior::FlyWithWings(), QuackBehavior::Quack, DanceBehavior::DanceWaltz)
{
}

MallardDuck::~MallardDuck()
{
}

void MallardDuck::Display() const
{
	cout << "I'm mallard duck" << endl;
}