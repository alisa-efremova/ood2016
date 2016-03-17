#include "stdafx.h"
#include "Duck.h"
#include <cassert>

Duck::Duck(function<void()> fly, function<void()> quack, function<void()> dance)
	: m_quack(quack)
	, m_fly(fly)
	, m_dance(dance)
{
	assert(m_quack);
	assert(m_dance);
	assert(m_fly);
	//SetFlyBehavior(move(flyBehavior));
}

Duck::~Duck()
{
}

void Duck::Quack() const
{
	m_quack();
}

void Duck::Swim()
{
	cout << "I'm swimming" << endl;
}

void Duck::Fly()
{
	m_fly();
}

void Duck::Dance()
{
	m_dance();
}

void Duck::SetFlyBehavior(function<void()> fly)
{
	assert(fly);
	m_fly = fly;
}
