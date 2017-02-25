#include "stdafx.h"
#include "Display.h"
#include "IObservable.h"
#include "WeatherData.h"

using namespace std;

void CDisplay::Update(CWeatherData const & subject)
{
	cout << "Current Temperature: " << subject.GetTemperature() << endl;
	cout << "Current Humidity: " << subject.GetHumidity() << endl;
	cout << "Current Pressure: " << subject.GetPressure() << endl;
	cout << "----------------" << endl;
}
