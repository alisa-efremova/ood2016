#include "stdafx.h"
#include "Duck.h"
#include <cassert>

Duck::Duck(unique_ptr<IFlyBehavior> && flyBehavior, unique_ptr<IQuackBehavior> && quackBehavior, unique_ptr<IDanceBehavior> && danceBehavior)
	: m_quackBehavior(move(quackBehavior))
	, m_danceBehavior(move(danceBehavior))
{
	assert(m_quackBehavior);
	assert(m_danceBehavior);
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
	m_danceBehavior->Dance();
}

void Duck::SetFlyBehavior(unique_ptr<IFlyBehavior> && flyBehavior)
{
	assert(flyBehavior);
	m_flyBehavior = move(flyBehavior);
}
