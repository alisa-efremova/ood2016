#include "stdafx.h"
#include "StatsDisplay.h"
#include "WeatherData.h"
#include "ProWeatherData.h"

using namespace std;

CStatsDisplay::CStatsDisplay(CWeatherData & inWeatherData, CProWeatherData & outWeatherData)
{
	auto makeHandler = [this](CStatsCalc & statsCalc)->std::function<void(double)>{
		return[&, this](double value){
			statsCalc.Update(value);
			Print();
		};
	};

	inWeatherData.DoOnTemperatureChange(makeHandler(m_inStats.temperatureStats));
	inWeatherData.DoOnHumidityChange(makeHandler(m_inStats.humidityStats));
	inWeatherData.DoOnPressureChange(makeHandler(m_inStats.pressureStats));

	outWeatherData.DoOnTemperatureChange(makeHandler(m_outStats.temperatureStats));
	outWeatherData.DoOnHumidityChange(makeHandler(m_outStats.humidityStats));
	outWeatherData.DoOnPressureChange(makeHandler(m_outStats.pressureStats));
	outWeatherData.DoOnWindSpeedChange(makeHandler(m_outStats.windSpeedStats));
	outWeatherData.DoOnWindDirectionChange(makeHandler(m_outStats.windDirectionStats));
}

void CStatsDisplay::Print() const
{
	cout << "* STATS INSIDE *" << endl;
	m_inStats.Print();
	cout << endl << "* STATS OUTSIDE *" << endl;
	m_outStats.Print();
	cout << "----------------------------------------------------------------" << endl;
}
