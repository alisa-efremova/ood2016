#include "stdafx.h"
#include "NoQuarterState.h"
#include <iostream>

using namespace std;

CNoQuarterState::CNoQuarterState(IGumBallMachine & gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void CNoQuarterState::InsertQuarter()
{
	cout << "You inserted a quarter\n";
	m_gumballMachine.SetHasQuarterState();
}

void CNoQuarterState::EjectQuarter()
{
	cout << "You haven't inserted a quarter\n";
}

void CNoQuarterState::TurnCrank()
{
	cout << "You turned but there's no quarter\n";
}

void CNoQuarterState::Dispense()
{
	cout << "You need to pay first\n";
}

string CNoQuarterState::ToString() const
{
	return "waiting for quarter";
}