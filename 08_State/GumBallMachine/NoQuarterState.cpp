#include "stdafx.h"
#include "NoQuarterState.h"

using namespace std;

CNoQuarterState::CNoQuarterState(IGumBallMachine & gumballMachine, ostream & out)
	: CState(gumballMachine, out)
{
}

bool CNoQuarterState::InsertQuarter()
{
	m_out << "You inserted a quarter\n";
	m_gumballMachine.SetHasQuarterState();
	return true;
}

bool CNoQuarterState::EjectQuarter()
{
	m_out << "You haven't inserted a quarter\n";
	return false;
}

bool CNoQuarterState::TurnCrank()
{
	m_out << "You turned but there's no quarter\n";
	return false;
}

bool CNoQuarterState::Refill(unsigned numBalls)
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

bool CNoQuarterState::Dispense()
{
	m_out << "You need to pay first\n";
	return false;
}

string CNoQuarterState::ToString() const
{
	return "waiting for quarter";
}