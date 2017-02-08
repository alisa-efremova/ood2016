#include "stdafx.h"
#include "FlyBehavior.h"

using namespace std;

namespace FlyBehavior
{
	void FlyNoWay()
	{
	}

    function<void()> MakeFlyWithWings() 
	{
		int flightCount = 0;
		return[flightCount]()mutable{
			++flightCount;
			std::cout << "I'm flying with wings " << flightCount << " time" << endl;
		};
	}
}