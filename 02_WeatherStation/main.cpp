#include "stdafx.h"
#include "WeatherData.h"
#include "ProWeatherData.h"
#include "Display.h"
#include "StatsDisplay.h"

using namespace std;

void WeatherStation();

int main()
{
	WeatherStation();
	return 0;
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