#include "stdafx.h"
#include "GumBallMachine.h"
#include "SoldOutState.h"
#include "HasQuarterState.h"
#include "NoQuarterState.h"
#include "SoldState.h"
#include <boost/format.hpp>

using namespace std;

CGumBallMachine::CGumBallMachine(ostream & out, unsigned numBalls)
	: m_out(out)
	, m_count(numBalls)
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

bool CGumBallMachine::EjectQuarter()
{
	return m_currentState->EjectQuarter();
}

bool CGumBallMachine::InsertQuarter()
{
	return m_currentState->InsertQuarter();
}

bool CGumBallMachine::TurnCrank()
{
	m_currentState->TurnCrank();
	return m_currentState->Dispense();
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

const IState & CGumBallMachine::GetCurrentState() const
{
	return *m_currentState;
}

void CGumBallMachine::ReleaseBall()
{
	if (m_count != 0)
	{
		m_out << "A gumball comes rolling out the slot...\n";
		--m_count;
	}
}

void CGumBallMachine::SetSoldOutState()
{
	m_currentState.reset(new CSoldOutState(*this, m_out));
}

void CGumBallMachine::SetNoQuarterState()
{
	m_currentState.reset(new CNoQuarterState(*this, m_out));
}

void CGumBallMachine::SetSoldState()
{
	m_currentState.reset(new CSoldState(*this, m_out));
}

void CGumBallMachine::SetHasQuarterState()
{
	m_currentState.reset(new CHasQuarterState(*this, m_out));
}
