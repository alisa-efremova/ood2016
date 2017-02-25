#include "stdafx.h"
#include "DeckoyDuck.h"
#include <memory>
#include "FlyNoWayBehavior.h"
#include "MuteQuackBehavior.h"
#include "DanceNoWayBehavior.h"

using namespace std;

DeckoyDuck::DeckoyDuck()
	: Duck(make_unique<FlyNoWayBehavior>(), make_unique<MuteQuackBehavior>(), make_unique<DanceNoWayBehavior>())
{
}

void DeckoyDuck::Display() const
{
	cout << "I'm deckoy duck" << endl;
}