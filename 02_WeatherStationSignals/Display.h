#pragma once
#include "SWeatherInfo.h"
class CWeatherData;
class CProWeatherData;

namespace signals = boost::signals2;

class CDisplay : boost::noncopyable
{
public:
	CDisplay(CWeatherData & inWeatherData, CProWeatherData & outWeatherData);

protected:
	void Print()const;

	SWeatherInfo m_inWeatherInfo;
	SProWeatherInfo m_outWeatherInfo;
};