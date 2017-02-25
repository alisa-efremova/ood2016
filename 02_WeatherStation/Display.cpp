#include "stdafx.h"
#include "Display.h"
#include "IObservable.h"
#include "WeatherData.h"

using namespace std;

void CDisplay::Update(SWeatherInfo const & data)
{
	cout << "Current Temperature: " << data.weatherData->GetTemperature() << endl;
	cout << "Current Humidity: " << data.weatherData->GetHumidity() << endl;
	cout << "Current Pressure: " << data.weatherData->GetPressure() << endl;
	cout << "----------------" << endl;
}
