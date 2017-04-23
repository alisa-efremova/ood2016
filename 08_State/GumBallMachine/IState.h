#pragma once
#include <string>

class IState
{
public:
	virtual bool InsertQuarter() = 0;
	virtual bool EjectQuarter() = 0;
	virtual bool TurnCrank() = 0;
	virtual bool Refill(unsigned numBalls) = 0;
	virtual bool Dispense() = 0;
	virtual std::string ToString()const = 0;
	virtual ~IState() = default;
};