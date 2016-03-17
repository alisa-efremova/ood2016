#include "stdafx.h"
#include "Display.h"

using namespace std;

void CDisplay::Update(SWeatherInfo const& data)
{
	cout << "Current Temp " << data.temperature << endl;
	cout << "Current Hum " << data.humidity << endl;
	cout << "Current Pressure " << data.pressure << endl;
	cout << "----------------" << endl;
}
