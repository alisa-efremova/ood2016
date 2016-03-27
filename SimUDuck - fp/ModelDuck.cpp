#include "stdafx.h"
#include "ModelDuck.h"
#include <memory>

using namespace std;

ModelDuck::ModelDuck()
	: Duck(FlyBehavior::FlyNoWay, QuackBehavior::Quack, DanceBehavior::DanceNoWay)
{
}

void ModelDuck::Display() const
{
	cout << "I'm model duck" << endl;
}