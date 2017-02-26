#include "stdafx.h"
#include "WeatherData.h"
#include "ProWeatherData.h"
#include "LightDisplay.h"
#include "Display.h"
#include "StatsDisplay.h"
#include "WeatherInfoType.h"

using namespace std;

void WeatherStation();
void LightWeatherStation();

int main()
{
	WeatherStation();
	cout << "\n\n\n";
	LightWeatherStation();
	return 0;
}

void LightWeatherStation()
{
	CProWeatherData wdOut;

	CLightDisplay display;
	wdOut.RegisterObserver(display, 0, (size_t)WeatherInfoType::TEMPERATURE);
	wdOut.RegisterObserver(display, 0, (size_t)WeatherInfoType::PRESSURE);

	wdOut.SetMeasurements(4.5, 0.8, 761, 8.5, 90.6);

	cout << "-- change humidity and wind info --" << endl;
	wdOut.SetMeasurements(4.5, 0.9, 761, 5.5, 350);

	cout << "-- change temp and pressure -- display update expected --" << endl;
	wdOut.SetMeasurements(5.5, 1.2, 760, 5.5, 350);

	cout << "-- unsubscribe from pressure and change it  --" << endl;
	wdOut.RemoveObserver(display, (size_t)WeatherInfoType::PRESSURE);
	wdOut.SetMeasurements(5.5, 1.2, 763, 5.5, 350);

	cout << "-- change temperature -- display update expected --" << endl;
	wdOut.SetMeasurements(-6.5, 1.2, 763, 5.5, 350);
}

void WeatherStation()
{
	CWeatherData wdIn;
	CProWeatherData wdOut;

	CDisplay display;
	wdIn.RegisterObserver(display);
	wdOut.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	wdIn.RegisterObserver(statsDisplay);
	wdOut.RegisterObserver(statsDisplay);

	wdIn.SetMeasurements(3.5, 0.7, 760);
	wdOut.SetMeasurements(4.5, 0.8, 761, 8.5, 90.6);
	wdOut.SetMeasurements(4.5, 0.8, 761, 5.5, 350);

	wdIn.RemoveObserver(statsDisplay);
	wdOut.RemoveObserver(statsDisplay);
	cout << "-- removed stats display --\n\n";

	wdIn.SetMeasurements(10.0, 0.8, 761);
	wdOut.SetMeasurements(-10.0, 0.8, 761, 2.5, 60);
}