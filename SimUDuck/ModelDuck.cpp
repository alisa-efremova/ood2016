#include "stdafx.h"
#include "ModelDuck.h"
#include <memory>
#include "FlyNoWayBehavior.h"
#include "QuackBehavior.h"
#include "DanceNoWayBehavior.h"

ModelDuck::ModelDuck()
	: Duck(make_unique<FlyNoWayBehavior>(), make_unique<QuackBehavior>(), make_unique<DanceNoWayBehavior>())
{
}

ModelDuck::~ModelDuck()
{
}

void ModelDuck::Display() const
{
	cout << "I'm model duck" << endl;
}