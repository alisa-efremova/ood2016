#include "stdafx.h"
#include "StatsDisplay.h"

using namespace std;

void CStatsDisplay::Update(SWeatherInfo const& data)
{
	if (m_minTemperature > data.temperature)
	{
		m_minTemperature = data.temperature;
	}
	if (m_maxTemperature < data.temperature)
	{
		m_maxTemperature = data.temperature;
	}
	m_accTemperature += data.temperature;
	++m_countAcc;

	cout << "* Temperature stats *" << endl;
	cout << "Max: " << m_maxTemperature << endl;
	cout << "Min: " << m_minTemperature << endl;
	cout << "Average: " << (m_accTemperature / m_countAcc) << endl;
	cout << "----------------" << endl;
}