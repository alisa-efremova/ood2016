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
	CStatsDisplay(IWeatherData & cr)
	{
		m_changeConnection = cr.DoOnChange(bind(&CStatsDisplay::OnChange, this, placeholders::_1));
	}

private:
	void OnChange(const CWeatherData * subject)
	{
		m_weatherInfo.temperatureStats.Update(subject->GetTemperature());
		m_weatherInfo.pressureStats.Update(subject->GetPressure());
		m_weatherInfo.humidityStats.Update(subject->GetHumidity());
		Print();
	}

	SStatsWeatherInfo m_weatherInfo;
	signals::scoped_connection m_changeConnection;

	void Print()
	{
		cout << "* STATS *" << endl;
		m_weatherInfo.Print();
		cout << "----------------------------------------------------------------" << endl;
	}
};