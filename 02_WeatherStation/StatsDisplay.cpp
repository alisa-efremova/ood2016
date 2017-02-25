#include "stdafx.h"
#include "StatsDisplay.h"
#include "WeatherData.h"

using namespace std;

CStatsDisplay::CStatsDisplay()
	: m_temperatureStats("TEMPERATURE")
	, m_humidityStats("HUMIDITY")
	, m_pressureStats("PRESSURE")
{
}

void CStatsDisplay::Update(SWeatherInfo const & data)
{
	m_temperatureStats.Update(data.weatherData->GetTemperature());
	m_humidityStats.Update(data.weatherData->GetHumidity());
	m_pressureStats.Update(data.weatherData->GetPressure());

	m_temperatureStats.Print();
	m_humidityStats.Print();
	m_pressureStats.Print();
}