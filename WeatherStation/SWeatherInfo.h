#pragma once
class CWeatherData;

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	const CWeatherData * weatherData = nullptr;
};