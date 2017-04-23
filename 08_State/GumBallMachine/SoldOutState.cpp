#include "stdafx.h"
#include "SoldOutState.h"
#include <iostream>

using namespace std;

CSoldOutState::CSoldOutState(IGumBallMachine & gumballMachine)
	:m_gumballMachine(gumballMachine)
{
}

void CSoldOutState::InsertQuarter()
{
	cout << "You can't insert a quarter, the machine is sold out\n";
}

void CSoldOutState::EjectQuarter()
{
	cout << "You can't eject, you haven't inserted a quarter yet\n";
}

void CSoldOutState::TurnCrank()
{
	cout << "You turned but there's no gumballs\n";
}

void CSoldOutState::Dispense()
{
	cout << "No gumball dispensed\n";
}

string CSoldOutState::ToString() const
{
	return "sold out";
}