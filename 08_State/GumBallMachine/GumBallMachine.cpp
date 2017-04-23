#include "stdafx.h"
#include "GumBallMachine.h"
#include "SoldOutState.h"
#include "HasQuarterState.h"
#include "NoQuarterState.h"
#include "SoldState.h"
#include <iostream>
#include <boost/format.hpp>

using namespace std;

CGumBallMachine::CGumBallMachine(unsigned numBalls)
	: m_count(numBalls)
{
	if (m_count > 0)
	{
		SetNoQuarterState();
	}
	else
	{
		SetSoldOutState();
	}
}

void CGumBallMachine::EjectQuarter()
{
	m_currentState->EjectQuarter();
}

void CGumBallMachine::InsertQuarter()
{
	m_currentState->InsertQuarter();
}

void CGumBallMachine::TurnCrank()
{
	m_currentState->TurnCrank();
	m_currentState->Dispense();
}

string CGumBallMachine::ToString()const
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
)");
	return (fmt % m_count % (m_count != 1 ? "s" : "") % m_currentState->ToString()).str();
}

unsigned CGumBallMachine::GetBallCount() const
{
	return m_count;
}

void CGumBallMachine::ReleaseBall()
{
	if (m_count != 0)
	{
		cout << "A gumball comes rolling out the slot...\n";
		--m_count;
	}
}

void CGumBallMachine::SetSoldOutState()
{
	m_currentState.reset(new CSoldOutState(*this));
}

void CGumBallMachine::SetNoQuarterState()
{
	m_currentState.reset(new CNoQuarterState(*this));
}

void CGumBallMachine::SetSoldState()
{
	m_currentState.reset(new CSoldState(*this));
}

void CGumBallMachine::SetHasQuarterState()
{
	m_currentState.reset(new CHasQuarterState(*this));
}
