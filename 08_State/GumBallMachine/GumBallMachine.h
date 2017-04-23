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
	unsigned GetBallCount()const override;
	unsigned GetQuarterCount()const override;

	std::string ToString()const;
	const IState & GetCurrentState()const;

private:
	void ReleaseBall() override;
	void ReleaseQuaters() override;

	void SetSoldOutState() override;
	void SetNoQuarterState() override;
	void SetSoldState() override;
	void SetHasQuarterState() override;

	unsigned m_ballCount = 0;
	unsigned m_quarterCount = 0;
	const unsigned m_maxQuarterCount = 5;
	std::unique_ptr<IState> m_currentState;
	std::ostream & m_out;
};

