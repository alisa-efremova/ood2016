#pragma once
#include "State.h"

class CSoldOutState : public CState
{
public:
	CSoldOutState(IGumBallMachine & gumballMachine, std::ostream & out = std::cout);
	bool InsertQuarter() override;
	bool EjectQuarter() override;
	bool TurnCrank() override;
	bool Dispense() override;
	std::string ToString() const override;
};

