#include "stdafx.h"
#include "FlyWithWingsBehavior.h"

using namespace std;

FlyWithWingsBehavior::FlyWithWingsBehavior()
	: m_flightCount(0)
{
}

void FlyWithWingsBehavior::Fly()
{
	m_flightCount++;
	cout << "I'm flying with wings! #" << m_flightCount << endl;
}