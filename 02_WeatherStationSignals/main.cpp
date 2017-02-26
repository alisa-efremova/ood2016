#include "stdafx.h"
#include "WeatherData.h"
#include "StatsDisplay.h"
#include "Display.h"

int main()
{
	CWeatherData weatherData;

	CStatsDisplay statsDisplay(weatherData);
	weatherData.SetMeasurements(7.1, 2.5, 760);

	CDisplay display(weatherData);
	weatherData.SetMeasurements(17.2, 10.3, 760);

	return 0;
}