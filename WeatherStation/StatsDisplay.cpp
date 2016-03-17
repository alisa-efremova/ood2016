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

	cout << "Max Temp " << m_maxTemperature << endl;
	cout << "Min Temp " << m_minTemperature << endl;
	cout << "Average Temp " << (m_accTemperature / m_countAcc) << endl;
	cout << "----------------" << endl;
}