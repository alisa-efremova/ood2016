#include "stdafx.h"
#include "SoldOutState.h"

using namespace std;

CSoldOutState::CSoldOutState(IGumBallMachine & gumballMachine, ostream & out)
	: CState(gumballMachine, out)
{
}

bool CSoldOutState::InsertQuarter()
{
	m_out << "You can't insert a quarter, the machine is sold out\n";
	return false;
}

bool CSoldOutState::EjectQuarter()
{
	if (m_gumballMachine.GetQuarterCount() > 0)
	{
		m_gumballMachine.ReleaseQuaters();
		m_out << "Quarter returned\n";
		return true;
	}
	else
	{
		m_out << "You can't eject, you haven't inserted a quarter yet\n";
		return false;
	}
}

bool CSoldOutState::TurnCrank()
{
	m_out << "You turned but there's no gumballs\n";
	return false;
}

bool CSoldOutState::Refill(unsigned numBalls)
{
	if (numBalls == 0)
	{
		m_out << "Machine is empty\n";
	}
	else
	{
		m_out << "Machine is refilled\n";
		if (m_gumballMachine.GetQuarterCount() == 0)
		{
			m_gumballMachine.SetNoQuarterState();
		}
		else
		{
			m_gumballMachine.SetHasQuarterState();
		}
	}
	return true;
}

bool CSoldOutState::Dispense()
{
	m_out << "No gumball dispensed\n";
	return false;
}

string CSoldOutState::ToString() const
{
	return "sold out";
}