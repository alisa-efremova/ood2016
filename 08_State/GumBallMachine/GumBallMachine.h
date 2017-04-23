#pragma once
#include "IGumBallMachine.h"
#include "IState.h"
#include <memory>
#include <iostream>

class CGumBallMachine : public IGumBallMachine
{
public:
	CGumBallMachine(std::ostream & out = std::cout, unsigned numBalls = 0);
	bool EjectQuarter();
	bool InsertQuarter();
	bool TurnCrank();
	unsigned GetBallCount() const override;

	std::string ToString()const;
	const IState & GetCurrentState()const;

private:
	void ReleaseBall() override;
	void SetSoldOutState() override;
	void SetNoQuarterState() override;
	void SetSoldState() override;
	void SetHasQuarterState() override;

	unsigned m_count = 0;
	std::unique_ptr<IState> m_currentState;
	std::ostream & m_out;
};

