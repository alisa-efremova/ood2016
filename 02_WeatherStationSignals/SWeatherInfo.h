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

struct SProWeatherInfo : SWeatherInfo
{
	SProWeatherInfo() {}
	SProWeatherInfo(double temperature, double humidity, double pressure, double windSpeed, double windDirection)
		: SWeatherInfo(temperature, humidity, pressure)
		, windSpeed(windSpeed)
		, windDirection(windDirection)
	{
	}

	double windSpeed = 0.0;
	double windDirection = 0;
};