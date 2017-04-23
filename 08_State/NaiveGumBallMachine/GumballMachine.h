#pragma once
#include <iostream>

class CGumballMachine
{
public:
	enum class State
	{
		SoldOut,		// Жвачка закончилась
		NoQuarter,		// Нет монетки
		HasQuarter,		// Есть монетка
		Sold,			// Монетка выдана
	};

	CGumballMachine(std::ostream & out = std::cout, unsigned ballCount = 0);

	bool InsertQuarter();
	bool EjectQuarter();
	bool TurnCrank();
	void Refill(unsigned numBalls);

	std::string ToString()const;
	unsigned GetBallCount()const;
	unsigned GetQuarterCount()const;
	State GetCurrentState()const;

private:
	bool Dispense();

	unsigned m_ballCount;
	unsigned m_quarterCount = 0;
	const unsigned m_maxQuarterCount = 5;
	State m_state = State::SoldOut;
	std::ostream & m_out;
};