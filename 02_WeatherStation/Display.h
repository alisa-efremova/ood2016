#pragma once
#include "IObserver.h"
#include "SWeatherInfo.h"
class CWeatherData;
class CProWeatherData;

class CDisplay : public IObserver<CWeatherData>, public IObserver<CProWeatherData>
{
private:
	void Update(CWeatherData const& subject) override;
	void Update(CProWeatherData const& subject) override;
	void PrintWeatherData()const;

	SWeatherInfo m_inWeatherInfo;
	SProWeatherInfo m_outWeatherInfo;
};

