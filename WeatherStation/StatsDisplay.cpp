#include "stdafx.h"
#include "StatsDisplay.h"

using namespace std;

CStatsDisplay::CStatsDisplay()
	: m_temperatureStats("TEMPERATURE")
	, m_humidityStats("HUMIDITY")
	, m_pressureStats("PRESSURE")
{
}

void CStatsDisplay::Update(SWeatherInfo const & data, const IObservable<SWeatherInfo> & subject)
{
	m_temperatureStats.Update(data.temperature);
	m_humidityStats.Update(data.humidity);
	m_pressureStats.Update(data.pressure);

	m_temperatureStats.Print();
	m_humidityStats.Print();
	m_pressureStats.Print();
}