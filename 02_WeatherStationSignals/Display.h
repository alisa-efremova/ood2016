#pragma once
#include "SWeatherInfo.h"
class CWeatherData;
class CProWeatherData;

namespace signals = boost::signals2;

class CDisplay : boost::noncopyable
{
public:
	CDisplay(CWeatherData & inWeatherData, CProWeatherData & outWeatherData);

private:
	void OnInWeatherDataChange(const CWeatherData * subject);
	void OnOutWeatherDataChange(const CProWeatherData * subject);
	void Print()const;

	SWeatherInfo m_inWeatherInfo;
	SProWeatherInfo m_outWeatherInfo;
	signals::scoped_connection m_inWeatherDataConnection;
	signals::scoped_connection m_outWeatherDataConnection;
};