#include "stdafx.h"
#include "Display.h"

using namespace std;

void CDisplay::Update(SWeatherInfo const& data)
{
	cout << "Current Temperature: " << data.temperature << endl;
	cout << "Current Humidity: " << data.humidity << endl;
	cout << "Current Pressure: " << data.pressure << endl;
	cout << "----------------" << endl;
}
