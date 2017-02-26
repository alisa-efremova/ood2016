#pragma once
#include "WeatherInfo.h"
#include "WeatherData.h"
#include <iostream>
#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>

using namespace std;

class CDisplay : boost::noncopyable
{
public:
	CDisplay(IWeatherData & cr)
	{
		m_changeConnection = cr.DoOnChange(bind(&CDisplay::OnChange, this, placeholders::_1));
	}

private:
	void OnChange(const CWeatherData * subject)
	{
		m_weatherInfo.temperature = subject->GetTemperature();
		m_weatherInfo.pressure = subject->GetPressure();
		m_weatherInfo.humidity = subject->GetHumidity();
		Print();
	}

	SWeatherInfo m_weatherInfo;
	signals::scoped_connection m_changeConnection;

	void Print()
	{
		cout << "* CURRENT *" << endl;
		cout << "Temperature:\t" << m_weatherInfo.temperature << endl;
		cout << "Humidity:\t" << m_weatherInfo.humidity << endl;
		cout << "Pressure:\t" << m_weatherInfo.pressure << endl;
		cout << "----------------------------------------------------------------" << endl;
	}
};