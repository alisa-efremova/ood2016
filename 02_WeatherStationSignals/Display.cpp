#include "stdafx.h"
#include "Display.h"
#include "WeatherData.h"
#include "ProWeatherData.h"

using namespace std;

CDisplay::CDisplay(CWeatherData & inWeatherData, CProWeatherData & outWeatherData)
{
	auto makeHandler = [this](double & var)->std::function<void(double)>{
		return[&, this](double value){
			var = value;
			Print();
		};
	};

	inWeatherData.DoOnTemperatureChange(makeHandler(m_inWeatherInfo.temperature));
	inWeatherData.DoOnHumidityChange(makeHandler(m_inWeatherInfo.humidity));
	inWeatherData.DoOnPressureChange(makeHandler(m_inWeatherInfo.pressure));

	outWeatherData.DoOnTemperatureChange(makeHandler(m_outWeatherInfo.temperature));
	outWeatherData.DoOnHumidityChange(makeHandler(m_outWeatherInfo.humidity));
	outWeatherData.DoOnPressureChange(makeHandler(m_outWeatherInfo.pressure));
	outWeatherData.DoOnWindSpeedChange(makeHandler(m_outWeatherInfo.windSpeed));
	outWeatherData.DoOnWindDirectionChange(makeHandler(m_outWeatherInfo.windDirection));
}

void CDisplay::Print() const
{
	cout << "* CURRENT *" << endl;
	cout << "Temperature\tinside: " << m_inWeatherInfo.temperature << "\toutside: " << m_outWeatherInfo.temperature << endl;
	cout << "Humidity\tinside: " << m_inWeatherInfo.humidity << "\toutside: " << m_outWeatherInfo.humidity << endl;
	cout << "Pressure\tinside: " << m_inWeatherInfo.pressure << "\toutside: " << m_outWeatherInfo.pressure << endl;
	cout << "Wind speed: " << m_outWeatherInfo.windSpeed << endl;
	cout << "Wind direction: " << m_outWeatherInfo.windDirection << endl;
	cout << "----------------------------------------------------------------" << endl;
}