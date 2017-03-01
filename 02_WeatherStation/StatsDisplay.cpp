#include "stdafx.h"
#include "StatsDisplay.h"
#include "WeatherData.h"
#include "ProWeatherData.h"
#include "StatsWeaherInfo.h"
#include "StatsCalc.h"

using namespace std;

CStatsDisplay::CStatsDisplay()
{
}

void CStatsDisplay::Update(CWeatherData const & subject)
{
	m_inStats.temperatureStats.Update(subject.GetTemperature());
	m_inStats.humidityStats.Update(subject.GetHumidity());
	m_inStats.pressureStats.Update(subject.GetPressure());

	PrintWeatherData();
}

void CStatsDisplay::Update(CProWeatherData const& subject)
{
	m_outStats.temperatureStats.Update(subject.GetTemperature());
	m_outStats.humidityStats.Update(subject.GetHumidity());
	m_outStats.pressureStats.Update(subject.GetPressure());
	m_outStats.windSpeedStats.Update(subject.GetWindSpeed());
	m_outStats.windDirectionStats.Update(subject.GetWindDirection());

	PrintWeatherData();
}

void CStatsDisplay::PrintWeatherData() const
{
	cout << "* STATS INSIDE *" << endl;
	m_inStats.Print();
	cout << endl << "* STATS OUTSIDE *" << endl;
	m_outStats.Print();
	cout << "----------------------------------------------------------------" << endl;
}