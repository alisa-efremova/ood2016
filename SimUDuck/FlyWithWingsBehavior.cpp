#include "stdafx.h"
#include "FlyWithWingsBehavior.h"

FlyWithWingsBehavior::FlyWithWingsBehavior()
	: m_flightCount(0)
{
}

FlyWithWingsBehavior::~FlyWithWingsBehavior()
{
}

void FlyWithWingsBehavior::Fly()
{
	m_flightCount++;
	cout << "I'm flying with wings! #" << m_flightCount << endl;
}