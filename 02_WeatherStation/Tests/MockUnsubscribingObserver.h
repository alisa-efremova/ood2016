#pragma once
#include "IObserver.h"
#include "WeatherData.h"

class CMockUnsubscribingObserver : public IObserver<CWeatherData>
{
public:
	CMockUnsubscribingObserver(CWeatherData & weatherData)
		: m_weatherData(weatherData)
	{
		m_weatherData.RegisterObserver(*this);
	}

private:
	void Update(CWeatherData const& data) override
	{
		m_weatherData.RemoveObserver(*this);
	}

	CWeatherData & m_weatherData;
};