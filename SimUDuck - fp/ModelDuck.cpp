#include "stdafx.h"
#include "ModelDuck.h"
#include <memory>

ModelDuck::ModelDuck()
	: Duck(&FlyBehavior::FlyNoWay, &QuackBehavior::Quack, &DanceBehavior::DanceNoWay)
{
}

ModelDuck::~ModelDuck()
{
}

void ModelDuck::Display() const
{
	cout << "I'm model duck" << endl;
}