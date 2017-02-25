#include "stdafx.h"
#include "MallardDuck.h"
#include <memory>
#include "FlyWithWingsBehavior.h"
#include "QuackBehavior.h"
#include "DanceWaltzBehavior.h"

using namespace std;

MallardDuck::MallardDuck()
	: Duck(make_unique<FlyWithWingsBehavior>(), make_unique<QuackBehavior>(), make_unique<DanceWaltzBehavior>())
{
}

void MallardDuck::Display() const
{
	cout << "I'm mallard duck" << endl;
}