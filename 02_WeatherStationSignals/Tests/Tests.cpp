#include "stdafx.h"
#include "WeatherData.h"
#include "ProWeatherData.h"

using namespace std;

BOOST_AUTO_TEST_CASE(TestInWeatherDataPressureNotification)
{
	CWeatherData wdIn;

	double expectedPressure = 765;
	bool pressureChanged = false;
	wdIn.DoOnPressureChange([&](double t){
		BOOST_CHECK(t == expectedPressure);
		pressureChanged = true;
	});

	wdIn.SetMeasurements(20, 100, expectedPressure);
	BOOST_CHECK(pressureChanged);
	pressureChanged = false;

	wdIn.SetMeasurements(21, 80, expectedPressure);
	BOOST_CHECK(!pressureChanged);
}

BOOST_AUTO_TEST_CASE(TestInWeatherDataHumidityNotification)
{
	CWeatherData wdIn;

	double expectedHumidity = 100;
	bool humidityChanged = false;
	wdIn.DoOnHumidityChange([&](double t){
		BOOST_CHECK(t == expectedHumidity);
		humidityChanged = true;
	});

	wdIn.SetMeasurements(20, expectedHumidity, 760);
	BOOST_CHECK(humidityChanged);
	humidityChanged = false;

	wdIn.SetMeasurements(21, expectedHumidity, 763);
	BOOST_CHECK(!humidityChanged);
}

BOOST_AUTO_TEST_CASE(TestInWeatherDataTemperatureNotification)
{
	CWeatherData wdIn;

	double expectedTemp = 43;
	bool tempChanged = false;
	wdIn.DoOnTemperatureChange([&](double t){
		BOOST_CHECK(t == expectedTemp);
		tempChanged = true;
	});

	wdIn.SetMeasurements(expectedTemp, 100, 760);
	BOOST_CHECK(tempChanged);
	tempChanged = false;

	wdIn.SetMeasurements(expectedTemp, 101, 763);
	BOOST_CHECK(!tempChanged);
}

BOOST_AUTO_TEST_CASE(TestOutWeatherDataPressureNotification)
{
	CProWeatherData wdOut;

	double expectedPressure = 765;
	bool pressureChanged = false;
	wdOut.DoOnPressureChange([&](double t){
		BOOST_CHECK(t == expectedPressure);
		pressureChanged = true;
	});

	wdOut.SetMeasurements(20, 100, expectedPressure, 3, 0);
	BOOST_CHECK(pressureChanged);
	pressureChanged = false;

	wdOut.SetMeasurements(21, 80, expectedPressure, 2, 3);
	BOOST_CHECK(!pressureChanged);
}

BOOST_AUTO_TEST_CASE(TestOutWeatherDataHumidityNotification)
{
	CProWeatherData wdOut;

	double expectedHumidity = 100;
	bool humidityChanged = false;
	wdOut.DoOnHumidityChange([&](double t){
		BOOST_CHECK(t == expectedHumidity);
		humidityChanged = true;
	});

	wdOut.SetMeasurements(20, expectedHumidity, 760, 3, 0);
	BOOST_CHECK(humidityChanged);
	humidityChanged = false;

	wdOut.SetMeasurements(21, expectedHumidity, 763, 2, 3);
	BOOST_CHECK(!humidityChanged);
}

BOOST_AUTO_TEST_CASE(TestOutWeatherDataTemperatureNotification)
{
	CProWeatherData wdOut;

	double expectedTemp = 43;
	bool tempChanged = false;
	wdOut.DoOnTemperatureChange([&](double t){
		BOOST_CHECK(t == expectedTemp);
		tempChanged = true;
	});

	wdOut.SetMeasurements(expectedTemp, 100, 760, 3, 0);
	BOOST_CHECK(tempChanged); 
	tempChanged = false;

	wdOut.SetMeasurements(expectedTemp, 101, 763, 2, 3);
	BOOST_CHECK(!tempChanged);
}

BOOST_AUTO_TEST_CASE(TestOutWeatherDataWindSpeedNotification)
{
	CProWeatherData wdOut;

	double expectedWindSpeed = 43;
	bool windSpeedChanged = false;
	wdOut.DoOnWindSpeedChange([&](double t){
		BOOST_CHECK(t == expectedWindSpeed);
		windSpeedChanged = true;
	});

	wdOut.SetMeasurements(5, 100, 760, expectedWindSpeed, 0);
	BOOST_CHECK(windSpeedChanged);
	windSpeedChanged = false;

	wdOut.SetMeasurements(6, 101, 763, expectedWindSpeed, 3);
	BOOST_CHECK(!windSpeedChanged);
}

BOOST_AUTO_TEST_CASE(TestOutWeatherDataWindDirectionNotification)
{
	CProWeatherData wdOut;

	double expectedWindDirection = 90;
	bool windDirectionChanged = false;
	wdOut.DoOnWindDirectionChange([&](double t){
		BOOST_CHECK(t == expectedWindDirection);
		windDirectionChanged = true;
	});

	wdOut.SetMeasurements(5, 100, 760, 3, expectedWindDirection);
	BOOST_CHECK(windDirectionChanged);
	windDirectionChanged = false;

	wdOut.SetMeasurements(6, 101, 763, 2, expectedWindDirection);
	BOOST_CHECK(!windDirectionChanged);
}