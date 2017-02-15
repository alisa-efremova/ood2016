#pragma once
#include "IObserver.h"
#include "SWeatherInfo.h"
#include "StatsCalc.h"

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay();
private:
	void Update(SWeatherInfo const& data, const IObservable<SWeatherInfo> & subject) override;
	CStatsCalc m_temperatureStats;
	CStatsCalc m_humidityStats;
	CStatsCalc m_pressureStats;
};

