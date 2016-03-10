#include "stdafx.h"
#include "RedheadDuck.h"
#include <memory>
#include "FlyWithWingsBehavior.h"
#include "QuackBehavior.h"

RedheadDuck::RedheadDuck()
	: Duck(make_unique<FlyWithWingsBehavior>(), make_unique<QuackBehavior>())
{
}

RedheadDuck::~RedheadDuck()
{
}

void RedheadDuck::Display() const
{
	cout << "I'm redhead duck" << endl;
}
