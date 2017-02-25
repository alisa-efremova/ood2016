#include "stdafx.h"
#include "Duck.h"
#include "MallardDuck.h"
#include "RedheadDuck.h"
#include "RubberDuck.h"
#include "DeckoyDuck.h"
#include "ModelDuck.h"
#include <memory>
#include "FlyBehavior.h"

using namespace std;

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck & duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Dance();
	duck.Fly();
	duck.Fly();
	cout << "----------" << endl;
}

void main()
{
	MallardDuck mallarDuck;
	PlayWithDuck(mallarDuck);
	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);
	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);
	DeckoyDuck deckoyDuck;
	PlayWithDuck(deckoyDuck);
	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(FlyBehavior::MakeFlyWithWings());
	PlayWithDuck(modelDuck);
}