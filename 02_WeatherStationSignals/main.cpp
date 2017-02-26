#include "stdafx.h"
#include "WeatherData.h"
#include "StatsDisplay.h"
#include "Display.h"

int main()
{
	CWeatherData wdIn;
	CProWeatherData wdOut;

	CStatsDisplay statsDisplay(wdIn, wdOut);
	wdIn.SetMeasurements(7.1, 2.5, 760);
	wdOut.SetMeasurements(-5.5, 3.5, 765, 2.2, 60);

	CDisplay display(wdIn, wdOut);
	wdIn.SetMeasurements(17.2, 10.3, 760);
	wdOut.SetMeasurements(-6.5, 3.5, 765, 2.2, 60);

	return 0;
}