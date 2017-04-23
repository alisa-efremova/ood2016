#include "stdafx.h"
#include "SoldState.h"
#include <iostream>

using namespace std;

CSoldState::CSoldState(IGumBallMachine & gumballMachine)
	:m_gumballMachine(gumballMachine)
{
}

void CSoldState::InsertQuarter()
{
	cout << "Please wait, we're already giving you a gumball\n";
}

void CSoldState::EjectQuarter()
{
	cout << "Sorry you already turned the crank\n";
}

void CSoldState::TurnCrank()
{
	cout << "Turning twice doesn't get you another gumball\n";
}

void CSoldState::Dispense()
{
	m_gumballMachine.ReleaseBall();
	if (m_gumballMachine.GetBallCount() == 0)
	{
		cout << "Oops, out of gumballs\n";
		m_gumballMachine.SetSoldOutState();
	}
	else
	{
		m_gumballMachine.SetNoQuarterState();
	}
}

string CSoldState::ToString() const
{
	return "delivering a gumball";
}
