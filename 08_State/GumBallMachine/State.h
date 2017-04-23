#pragma once
#include "IState.h"
#include "IGumBallMachine.h"
#include <iostream>

class CState : public IState
{
public:
	CState(IGumBallMachine & gumballMachine, std::ostream & out = std::cout)
		: m_gumballMachine(gumballMachine)
		, m_out(out)
	{
	}

protected:
	IGumBallMachine & m_gumballMachine;
	std::ostream & m_out;
};

