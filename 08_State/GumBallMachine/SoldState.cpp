#include "stdafx.h"
#include "SoldState.h"

using namespace std;

CSoldState::CSoldState(IGumBallMachine & gumballMachine, ostream & out)
	: CState(gumballMachine, out)
{
}

bool CSoldState::InsertQuarter()
{
	m_out << "Please wait, we're already giving you a gumball\n";
	return false;
}

bool CSoldState::EjectQuarter()
{
	m_out << "Sorry you already turned the crank\n";
	return false;
}

bool CSoldState::TurnCrank()
{
	m_out << "Turning twice doesn't get you another gumball\n";
	return false;
}

bool CSoldState::Dispense()
{
	m_gumballMachine.ReleaseBall();
	if (m_gumballMachine.GetBallCount() == 0)
	{
		m_out << "Oops, out of gumballs\n";
		m_gumballMachine.SetSoldOutState();
	}
	else if (m_gumballMachine.GetQuarterCount() > 0)
	{
		m_gumballMachine.SetHasQuarterState();
	} else
	{
		m_gumballMachine.SetNoQuarterState();
	}
	return true;
}

string CSoldState::ToString() const
{
	return "delivering a gumball";
}
