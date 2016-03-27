#include "stdafx.h"
#include "FlyBehavior.h"

using namespace std;

namespace FlyBehavior
{
	void FlyWithWings::operator () ()
	{
		++m_flightCount;
		cout << "I'm flying with wings " << m_flightCount << " time" << endl;
	}

	void FlyNoWay()
	{
	}
}