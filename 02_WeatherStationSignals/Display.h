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
	CDisplay(CWeatherData & inWeatherData, CProWeatherData & outWeatherData)
	{
		m_inWeatherDataConnection = inWeatherData.DoOnChange(bind(&CDisplay::OnInWeatherDataChange, this, placeholders::_1));
		m_outWeatherDataConnection = outWeatherData.DoOnChange(bind(&CDisplay::OnOutWeatherDataChange, this, placeholders::_1));
	}

private:
	void OnInWeatherDataChange(const CWeatherData * subject)
	{
		m_inWeatherInfo.temperature = subject->GetTemperature();
		m_inWeatherInfo.pressure = subject->GetPressure();
		m_inWeatherInfo.humidity = subject->GetHumidity();
		Print();
	}

	void OnOutWeatherDataChange(const CProWeatherData * subject)
	{
		m_outWeatherInfo.temperature = subject->GetTemperature();
		m_outWeatherInfo.pressure = subject->GetPressure();
		m_outWeatherInfo.humidity = subject->GetHumidity();
		m_outWeatherInfo.windSpeed = subject->GetWindSpeed();
		m_outWeatherInfo.windDirection = subject->GetWindDirection();
		Print();
	}

	SWeatherInfo m_inWeatherInfo;
	SProWeatherInfo m_outWeatherInfo;
	signals::scoped_connection m_inWeatherDataConnection;
	signals::scoped_connection m_outWeatherDataConnection;

	void Print()
	{
		cout << "* CURRENT *" << endl;
		cout << "Temperature\tinside: " << m_inWeatherInfo.temperature << "\toutside: " << m_outWeatherInfo.temperature << endl;
		cout << "Humidity\tinside: " << m_inWeatherInfo.humidity << "\toutside: " << m_outWeatherInfo.humidity << endl;
		cout << "Pressure\tinside: " << m_inWeatherInfo.pressure << "\toutside: " << m_outWeatherInfo.pressure << endl;
		cout << "Wind speed: " << m_outWeatherInfo.windSpeed << endl;
		cout << "Wind direction: " << m_outWeatherInfo.windDirection << endl;
		cout << "----------------------------------------------------------------" << endl;
	}
};