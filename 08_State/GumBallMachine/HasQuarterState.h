#pragma once
#include "State.h"

class CHasQuarterState : public CState
{
public:
	CHasQuarterState(IGumBallMachine & gumballMachine, std::ostream & out = std::cout);
	bool InsertQuarter() override;
	bool EjectQuarter() override;
	bool TurnCrank() override;
	bool Dispense() override;
	bool Refill(unsigned numBalls) override;
	std::string ToString() const override;
};

