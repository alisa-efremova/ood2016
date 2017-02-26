#pragma once
#include "IObserver.h"
#include "StatsWeaherInfo.h"
class CWeatherData;
class CProWeatherData;

class CStatsDisplay : public IObserver<CWeatherData>, public IObserver<CProWeatherData>
{
public:
	CStatsDisplay();
private:
	void Update(CWeatherData const& subject) override;
	void Update(CProWeatherData const& subject) override;
	void PrintWeatherData()const;

	SStatsWeatherInfo m_inStats;
	SProStatsWeatherInfo m_outStats;
};

