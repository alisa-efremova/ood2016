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

private:
	void OnInWeatherDataChange(const CWeatherData * subject);
	void OnOutWeatherDataChange(const CProWeatherData * subject);
	void Print()const;

	SStatsWeatherInfo m_inStats;
	SProStatsWeatherInfo m_outStats;
	signals::scoped_connection m_inWeatherDataConnection;
	signals::scoped_connection m_outWeatherDataConnection;
};