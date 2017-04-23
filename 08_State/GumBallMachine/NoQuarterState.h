#pragma once
#include "State.h"

class CNoQuarterState : public CState
{
public:
public:
	CNoQuarterState(IGumBallMachine & gumballMachine, std::ostream & out = std::cout);
	bool InsertQuarter() override;
	bool EjectQuarter() override;
	bool TurnCrank() override;
	bool Refill(unsigned numBalls) override;
	bool Dispense() override;
	std::string ToString() const override;
};

