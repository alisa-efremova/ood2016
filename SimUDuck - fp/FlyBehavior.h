#pragma once

using namespace std;

namespace FlyBehavior
{
	class FlyWithWings
	{
	public:
		void operator () ();
	private:
		unsigned m_flightCount = 0;
	};

	void FlyNoWay();
};