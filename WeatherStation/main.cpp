#include "stdafx.h"
#include "WeatherData.h"
#include "Display.h"
#include "StatsDisplay.h"

using namespace std;

void weatherStation();
void duoWeatherStation();

int main()
{
	weatherStation();
	cout << endl << endl;
	duoWeatherStation();
	return 0;
}

void weatherStation()
{
	cout << "-- Weather station --" << endl;
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 1);

	wd.SetMeasurements(3, 0.7, 760);
	wd.SetMeasurements(4, 0.8, 761);

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761);
	wd.SetMeasurements(-10, 0.8, 761);
}

void duoWeatherStation()
{
	cout << "-- Duo weather station --" << endl;

	CWeatherData wdIn;
	CWeatherData wdOut;

	CDisplay display;
	wdIn.RegisterObserver(display);
	wdOut.RegisterObserver(display);

	wdIn.SetMeasurements(3, 0.7, 760);
	wdOut.SetMeasurements(10, 0.8, 761);
}