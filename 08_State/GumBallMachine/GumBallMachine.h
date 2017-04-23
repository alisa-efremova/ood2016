#pragma once
#include "IGumBallMachine.h"
#include "IState.h"
#include <memory>

class CGumBallMachine : public IGumBallMachine
{
public:
	CGumBallMachine(unsigned numBalls);
	void EjectQuarter();
	void InsertQuarter();
	void TurnCrank();
	std::string ToString()const;

private:
	unsigned GetBallCount() const override;
	void ReleaseBall() override;
	void SetSoldOutState() override;
	void SetNoQuarterState() override;
	void SetSoldState() override;
	void SetHasQuarterState() override;

	unsigned m_count = 0;
	std::unique_ptr<IState> m_currentState;
};

