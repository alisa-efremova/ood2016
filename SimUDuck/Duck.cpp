#include "stdafx.h"
#include "Duck.h"
#include <cassert>


Duck::Duck(unique_ptr<IFlyBehavior> && flyBehavior, unique_ptr<IQuackBehavior> && quackBehavior)
	: m_quackBehavior(move(quackBehavior))
{
	assert(m_quackBehavior);
	SetFlyBehavior(move(flyBehavior));
}


Duck::~Duck()
{
}

void Duck::Quack() const
{
	m_quackBehavior->Quack();
}

void Duck::Swim()
{
	cout << "I'm swimming" << endl;
}

void Duck::Fly()
{
	m_flyBehavior->Fly();
}

void Duck::Dance()
{
	cout << "I'm Dancing" << endl;
}

void Duck::SetFlyBehavior(unique_ptr<IFlyBehavior> && flyBehavior)
{
	assert(flyBehavior);
	m_flyBehavior = move(flyBehavior);
}
