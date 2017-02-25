#include "stdafx.h"
#include "ModelDuck.h"
#include <memory>
#include "FlyNoWayBehavior.h"
#include "QuackBehavior.h"
#include "DanceNoWayBehavior.h"

using namespace std;

ModelDuck::ModelDuck()
	: Duck(make_unique<FlyNoWayBehavior>(), make_unique<QuackBehavior>(), make_unique<DanceNoWayBehavior>())
{
}

void ModelDuck::Display() const
{
	cout << "I'm model duck" << endl;
}