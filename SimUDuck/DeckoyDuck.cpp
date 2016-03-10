#include "stdafx.h"
#include "DeckoyDuck.h"
#include <memory>
#include "FlyNoWayBehavior.h"
#include "MuteQuackBehavior.h"

DeckoyDuck::DeckoyDuck()
	: Duck(make_unique<FlyNoWayBehavior>(), make_unique<MuteQuackBehavior>())
{
}

DeckoyDuck::~DeckoyDuck()
{
}

void DeckoyDuck::Display() const
{
	cout << "I'm deckoy duck" << endl;
}

void DeckoyDuck::Dance()
{
}