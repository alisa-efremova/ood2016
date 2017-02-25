#pragma once
#include "IObserver.h"
#include "StatsCalc.h"
#include "WeatherData.h"

class CStatsDisplay : public IObserver<CWeatherData>
{
public:
	CStatsDisplay();
private:
	void Update(CWeatherData const& subject) override;
	CStatsCalc m_temperatureStats;
	CStatsCalc m_humidityStats;
	CStatsCalc m_pressureStats;
};

