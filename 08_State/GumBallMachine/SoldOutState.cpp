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
	m_out << "You can't eject, you haven't inserted a quarter yet\n";
	return false;
}

bool CSoldOutState::TurnCrank()
{
	m_out << "You turned but there's no gumballs\n";
	return false;
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