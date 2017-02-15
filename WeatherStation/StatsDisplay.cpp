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
	m_temperatureStats.update(data.temperature);
	m_humidityStats.update(data.humidity);
	m_pressureStats.update(data.pressure);

	m_temperatureStats.print();
	m_humidityStats.print();
	m_pressureStats.print();
}