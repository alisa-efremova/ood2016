#pragma once
#include <string>

class CGumballMachine
{
public:
	enum class State
	{
		SoldOut,		// ������ �����������
		NoQuarter,		// ��� �������
		HasQuarter,		// ���� �������
		Sold,			// ������� ������
	};

	CGumballMachine(unsigned count);

	void InsertQuarter();
	void EjectQuarter();
	void TurnCrank();
	void Refill(unsigned numBalls);
	std::string ToString()const;

private:
	void Dispense();

	unsigned m_count;	// ���������� �������
	State m_state = State::SoldOut;
};