#pragma once
#include "IState.h"
#include "IGumBallMachine.h"

class CSoldState : public IState
{
public:
	CSoldState(IGumBallMachine & gumballMachine);
	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;
	std::string ToString() const override;

private:
	IGumBallMachine & m_gumballMachine;
};

