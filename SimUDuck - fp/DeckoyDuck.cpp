#include "stdafx.h"
#include "DeckoyDuck.h"
#include <memory>

DeckoyDuck::DeckoyDuck()
	: Duck(FlyBehavior::FlyNoWay, QuackBehavior::MuteQuack, DanceBehavior::DanceNoWay)
{
}

DeckoyDuck::~DeckoyDuck()
{
}

void DeckoyDuck::Display() const
{
	cout << "I'm deckoy duck" << endl;
}