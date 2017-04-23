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

	CGumballMachine(std::ostream & out = std::cout, unsigned count = 0);

	bool InsertQuarter();
	bool EjectQuarter();
	bool TurnCrank();
	void Refill(unsigned numBalls);

	std::string ToString()const;
	unsigned GetBallCount()const;
	State GetCurrentState()const;

private:
	bool Dispense();

	unsigned m_count;	// Количество шариков
	State m_state = State::SoldOut;
	std::ostream & m_out;
};