#pragma once

struct SWeatherInfo
{
	SWeatherInfo() {}
	SWeatherInfo(double temperature, double humidity, double pressure)
		: temperature(temperature)
		, humidity(humidity)
		, pressure(pressure)
	{
	}

	double temperature = 0.0;
	double humidity = 0.0;
	double pressure = 760.0;
};

struct SProWeatherInfo
{
	SProWeatherInfo() {}
	SProWeatherInfo(double temperature, double humidity, double pressure, double windSpeed, double windDirection)
		: temperature(temperature)
		, humidity(humidity)
		, pressure(pressure)
		, windSpeed(windSpeed)
		, windDirection(windDirection)
	{
	}

	double temperature = 0.0;
	double humidity = 0.0;
	double pressure = 760.0;
	double windSpeed = 0.0;
	double windDirection = 0;
};