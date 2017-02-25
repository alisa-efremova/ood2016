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

void CStatsDisplay::Update(CWeatherData const & subject)
{
	m_temperatureStats.Update(subject.GetTemperature());
	m_humidityStats.Update(subject.GetHumidity());
	m_pressureStats.Update(subject.GetPressure());

	m_temperatureStats.Print();
	m_humidityStats.Print();
	m_pressureStats.Print();
}