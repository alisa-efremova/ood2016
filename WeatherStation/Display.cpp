#include "stdafx.h"
#include "Display.h"
#include "IObservable.h"

using namespace std;

void CDisplay::Update(SWeatherInfo const& data, const IObservable<SWeatherInfo> & subject)
{
	if (subject.GetLocation() != ObservableLocation::UNDEFINED)
	{
		cout << "Weather station '" << subject.GetLocation() << "' data:" << endl;
	}
	cout << "Current Temperature: " << data.temperature << endl;
	cout << "Current Humidity: " << data.humidity << endl;
	cout << "Current Pressure: " << data.pressure << endl;
	cout << "----------------" << endl;
}
