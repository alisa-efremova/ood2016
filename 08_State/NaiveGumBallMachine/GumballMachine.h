#pragma once
#include <string>

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

	CGumballMachine(unsigned count);

	void InsertQuarter();
	void EjectQuarter();
	void TurnCrank();
	void Refill(unsigned numBalls);
	std::string ToString()const;

private:
	void Dispense();

	unsigned m_count;	// Количество шариков
	State m_state = State::SoldOut;
};