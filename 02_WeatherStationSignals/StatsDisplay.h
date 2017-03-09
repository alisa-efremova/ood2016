#pragma once
#include "StatsCalc.h"
#include "StatsWeatherInfo.h"
class CWeatherData;
class CProWeatherData;

namespace signals = boost::signals2;

class CStatsDisplay : boost::noncopyable
{
public:
	CStatsDisplay(CWeatherData & inWeatherData, CProWeatherData & outWeatherData);

protected:
	void Print()const;

	SStatsWeatherInfo m_inStats;
	SProStatsWeatherInfo m_outStats;
};