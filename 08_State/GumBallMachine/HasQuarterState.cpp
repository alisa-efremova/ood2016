#include "stdafx.h"
#include "HasQuarterState.h"
#include <iostream>

using namespace std;

CHasQuarterState::CHasQuarterState(IGumBallMachine & gumballMachine)
	:m_gumballMachine(gumballMachine)
{
}

void CHasQuarterState::InsertQuarter()
{
	cout << "You can't insert another quarter\n";
}

void CHasQuarterState::EjectQuarter()
{
	cout << "Quarter returned\n";
	m_gumballMachine.SetNoQuarterState();
}

void CHasQuarterState::TurnCrank()
{
	cout << "You turned...\n";
	m_gumballMachine.SetSoldState();
}

void CHasQuarterState::Dispense()
{
	cout << "No gumball dispensed\n";
}

string CHasQuarterState::ToString() const
{
	return "waiting for turn of crank";
}
