#include "stdafx.h"
#include "HasQuarterState.h"

using namespace std;

CHasQuarterState::CHasQuarterState(IGumBallMachine & gumballMachine, ostream & out)
	: CState(gumballMachine, out)
{
}

bool CHasQuarterState::InsertQuarter()
{
	m_out << "You inserted a quarter\n";
	m_gumballMachine.SetHasQuarterState();
	return true;
}

bool CHasQuarterState::EjectQuarter()
{
	m_out << "Quarter returned\n";
	m_gumballMachine.ReleaseQuaters();
	m_gumballMachine.SetNoQuarterState();
	return true;
}

bool CHasQuarterState::TurnCrank()
{
	m_out << "You turned...\n";
	m_gumballMachine.SetSoldState();
	return true;
}

bool CHasQuarterState::Dispense()
{
	m_out << "No gumball dispensed\n";
	return false;
}

bool CHasQuarterState::Refill(unsigned numBalls)
{
	if (numBalls == 0)
	{
		m_out << "Machine is empty\n";
		m_gumballMachine.SetSoldOutState();
	}
	else
	{
		m_out << "Machine is refilled\n";
	}
	return true;
}

string CHasQuarterState::ToString() const
{
	return "waiting for turn of crank";
}
