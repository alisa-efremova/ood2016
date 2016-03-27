#include "stdafx.h"
#include "DeckoyDuck.h"
#include <memory>

using namespace std;

DeckoyDuck::DeckoyDuck()
	: Duck(FlyBehavior::FlyNoWay, QuackBehavior::MuteQuack, DanceBehavior::DanceNoWay)
{
}

void DeckoyDuck::Display() const
{
	cout << "I'm deckoy duck" << endl;
}