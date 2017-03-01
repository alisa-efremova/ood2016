#include "stdafx.h"
#include "StatsDisplay.h"
#include "WeatherData.h"
#include "ProWeatherData.h"

using namespace std;

CStatsDisplay::CStatsDisplay(CWeatherData & inWeatherData, CProWeatherData & outWeatherData)
{
	m_inWeatherDataConnection = inWeatherData.DoOnChange(bind(&CStatsDisplay::OnInWeatherDataChange, this, placeholders::_1));
	m_outWeatherDataConnection = outWeatherData.DoOnChange(bind(&CStatsDisplay::OnOutWeatherDataChange, this, placeholders::_1));
}


void CStatsDisplay::OnInWeatherDataChange(const CWeatherData * subject)
{
	m_inStats.temperatureStats.Update(subject->GetTemperature());
	m_inStats.pressureStats.Update(subject->GetPressure());
	m_inStats.humidityStats.Update(subject->GetHumidity());
	Print();
}

void CStatsDisplay::OnOutWeatherDataChange(const CProWeatherData * subject)
{
	m_outStats.temperatureStats.Update(subject->GetTemperature());
	m_outStats.pressureStats.Update(subject->GetPressure());
	m_outStats.humidityStats.Update(subject->GetHumidity());
	m_outStats.windSpeedStats.Update(subject->GetWindSpeed());
	m_outStats.windDirectionStats.Update(subject->GetWindDirection());
	Print();
}

void CStatsDisplay::Print() const
{
	cout << "* STATS INSIDE *" << endl;
	m_inStats.Print();
	cout << endl << "* STATS OUTSIDE *" << endl;
	m_outStats.Print();
	cout << "----------------------------------------------------------------" << endl;
}
