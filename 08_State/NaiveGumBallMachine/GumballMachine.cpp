#include "stdafx.h"
#include "GumballMachine.h"
#include <boost/format.hpp>

using namespace std;

CGumballMachine::CGumballMachine(ostream & out, unsigned ballCount)
	: m_out(out)
	, m_ballCount(ballCount)
{
	m_state = m_ballCount == 0 ? State::SoldOut : State::NoQuarter;
}

bool CGumballMachine::InsertQuarter()
{
	bool result = false;
	switch (m_state)
	{
	case State::SoldOut:
		m_out << "You can't insert a quarter, the machine is sold out\n";
		break;
	case State::NoQuarter:
		m_out << "You inserted a quarter\n";
		m_state = State::HasQuarter;
		++m_quarterCount;
		result = true;
		break;
	case State::HasQuarter:
		if (m_quarterCount >= m_maxQuarterCount)
		{
			m_out << "You can't insert another quarter\n";
		}
		else
		{
			m_out << "You inserted a quarter\n";
			++m_quarterCount;
			result = true;
		}
		break;
	case State::Sold:
		m_out << "Please wait, we're already giving you a gumball\n";
		break;
	}
	return result;
}

bool CGumballMachine::EjectQuarter()
{
	bool result = false;
	switch (m_state)
	{
	case State::HasQuarter:
		m_out << "Quarter returned\n";
		m_quarterCount = 0;
		m_state = State::NoQuarter;
		result = true;
		break;
	case State::NoQuarter:
		m_out << "You haven't inserted a quarter\n";
		break;
	case State::Sold:
		m_out << "Sorry you already turned the crank\n";
		break;
	case State::SoldOut:
		if (m_quarterCount > 0)
		{
			m_out << "Quarter returned\n";
			m_quarterCount = 0;
			result = true;
		}
		else
		{
			m_out << "You can't eject, you haven't inserted a quarter yet\n";
		}
		break;
	}
	return result;
}

bool CGumballMachine::TurnCrank()
{
	bool result = false;
	switch (m_state)
	{
	case State::SoldOut:
		m_out << "You turned but there's no gumballs\n";
		break;
	case State::NoQuarter:
		m_out << "You turned but there's no quarter\n";
		break;
	case State::HasQuarter:
		m_out << "You turned...\n";
		m_state = State::Sold;
		--m_quarterCount;
		result = Dispense();
		break;
	case State::Sold:
		m_out << "Turning twice doesn't get you another gumball\n";
		break;
	}
	return result;
}

bool CGumballMachine::Refill(unsigned numBalls)
{
	bool result = false;

	switch (m_state)
	{
	case State::NoQuarter:
	case State::HasQuarter:
		m_ballCount = numBalls;
		if (numBalls == 0)
		{
			m_out << "Machine is empty\n";
			m_state = State::SoldOut;
		}
		else
		{
			m_out << "Machine is refilled\n";
		}
		result = true;
		break;
	case State::SoldOut:
		m_ballCount = numBalls;
		if (numBalls == 0)
		{
			m_out << "Machine is empty\n";
		}
		else
		{
			m_out << "Machine is refilled\n";
			m_state = m_quarterCount > 0 ? State::HasQuarter : State::NoQuarter;
		}
		result = true;
		break;
	case State::Sold:
		m_out << "Can't refill machine while dispensing a gumball\n";
		break;
	}

	if (m_state == State::Sold)
	{
		m_out << "Can't refill machine while dispensing a gumball\n";
	}
	else
	{
		m_ballCount = numBalls;
		result = true;
		if (m_ballCount == 0)
		{
			m_state = State::SoldOut;
		}
		else
		{
			if (m_quarterCount == 0)
			{
				m_state = State::NoQuarter;
			}
			else
			{
				m_state = State::HasQuarter;
			}
		}
	}
	return result;
}

string CGumballMachine::ToString()const
{
	string state =
		(m_state == State::SoldOut) ? "sold out" :
		(m_state == State::NoQuarter) ? "waiting for quarter" :
		(m_state == State::HasQuarter) ? "waiting for turn of crank"
		: "delivering a gumball";
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Machine is %3%
)");
	return (fmt % m_ballCount % (m_ballCount != 1 ? "s" : "") % state).str();
}

unsigned CGumballMachine::GetBallCount() const
{
	return m_ballCount;
}

unsigned CGumballMachine::GetQuarterCount() const
{
	return m_quarterCount;
}

CGumballMachine::State CGumballMachine::GetCurrentState() const
{
	return m_state;
}

bool CGumballMachine::Dispense()
{
	bool result = false;
	switch (m_state)
	{
	case State::Sold:
		m_out << "A gumball comes rolling out the slot\n";
		--m_ballCount;
		if (m_ballCount == 0)
		{
			m_out << "Oops, out of gumballs\n";
			m_state = State::SoldOut;
		}
		else
		{
			if (m_quarterCount > 0)
			{
				m_state = State::HasQuarter;
			}
			else
			{
				m_state = State::NoQuarter;
			}
		}
		result = true;
		break;
	case State::NoQuarter:
		m_out << "You need to pay first\n";
		break;
	case State::SoldOut:
	case State::HasQuarter:
		m_out << "No gumball dispensed\n";
		break;
	}
	return result;
}
