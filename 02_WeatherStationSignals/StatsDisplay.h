#pragma once
#include "StatsCalc.h"
#include "StatsWeatherInfo.h"
#include "WeatherData.h"
#include <iostream>
#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>

using namespace std;

class CStatsDisplay : boost::noncopyable
{
public:
	CStatsDisplay(CWeatherData & inWeatherData, CProWeatherData & outWeatherData)
	{
		m_inWeatherDataConnection = inWeatherData.DoOnChange(bind(&CStatsDisplay::OnInWeatherDataChange, this, placeholders::_1));
		m_outWeatherDataConnection = outWeatherData.DoOnChange(bind(&CStatsDisplay::OnOutWeatherDataChange, this, placeholders::_1));
	}

private:
	void OnInWeatherDataChange(const CWeatherData * subject)
	{
		m_inStats.temperatureStats.Update(subject->GetTemperature());
		m_inStats.pressureStats.Update(subject->GetPressure());
		m_inStats.humidityStats.Update(subject->GetHumidity());
		Print();
	}

	void OnOutWeatherDataChange(const CProWeatherData * subject)
	{
		m_outStats.temperatureStats.Update(subject->GetTemperature());
		m_outStats.pressureStats.Update(subject->GetPressure());
		m_outStats.humidityStats.Update(subject->GetHumidity());
		m_outStats.windSpeedStats.Update(subject->GetWindSpeed());
		m_outStats.windDirectionStats.Update(subject->GetWindDirection());
		Print();
	}

	SStatsWeatherInfo m_inStats;
	SProStatsWeatherInfo m_outStats;
	signals::scoped_connection m_inWeatherDataConnection;
	signals::scoped_connection m_outWeatherDataConnection;

	void Print()
	{
		cout << "* STATS INSIDE *" << endl;
		m_inStats.Print();
		cout << endl << "* STATS OUTSIDE *" << endl;
		m_outStats.Print();
		cout << "----------------------------------------------------------------" << endl;
	}
};