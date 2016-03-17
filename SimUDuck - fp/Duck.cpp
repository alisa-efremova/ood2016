#include "stdafx.h"
#include "Duck.h"
#include <cassert>

using namespace std;

Duck::Duck(function<void()> fly, function<void()> quack, function<void()> dance)
	: m_quack(quack)
	, m_dance(dance)
{
	assert(m_quack);
	assert(m_dance);
	SetFlyBehavior(fly);
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
