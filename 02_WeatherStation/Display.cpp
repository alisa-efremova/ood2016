#include "stdafx.h"
#include "Display.h"
#include "IObservable.h"
#include "WeatherData.h"
#include "ProWeatherData.h"

using namespace std;

void CDisplay::Update(CWeatherData const & subject)
{
	m_inWeatherInfo = SWeatherInfo(subject.GetTemperature(), subject.GetHumidity(), subject.GetPressure());
	PrintWeatherData();
}

void CDisplay::Update(CProWeatherData const & subject) {
	m_outWeatherInfo = SProWeatherInfo(subject.GetTemperature(), subject.GetHumidity(), subject.GetPressure(), subject.GetWindSpeed(), subject.GetWindDirection());
	PrintWeatherData();
}

void CDisplay::PrintWeatherData()const
{
	cout << "* CURRENT *" << endl;
	cout << "Temperature\tinside: " << m_inWeatherInfo.temperature << "\toutside: " << m_outWeatherInfo.temperature << endl;
	cout << "Humidity\tinside: " << m_inWeatherInfo.humidity << "\toutside: " << m_outWeatherInfo.humidity << endl;
	cout << "Pressure\tinside: " << m_inWeatherInfo.pressure << "\toutside: " << m_outWeatherInfo.pressure << endl;
	cout << "Wind speed: " << m_outWeatherInfo.windSpeed << endl;
	cout << "Wind direction: " << m_outWeatherInfo.windDirection << endl;
	cout << "----------------------------------------------------------------" << endl;
}