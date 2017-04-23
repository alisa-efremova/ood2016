#pragma once
#include "State.h"

class CSoldState : public CState
{
public:
	CSoldState(IGumBallMachine & gumballMachine, std::ostream & out = std::cout);
	bool InsertQuarter() override;
	bool EjectQuarter() override;
	bool TurnCrank() override;
	bool Dispense() override;
	std::string ToString() const override;
};

