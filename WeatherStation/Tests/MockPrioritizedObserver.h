#pragma once
#include "IObserver.h"
#include "WeatherData.h"
#include "SWeatherInfo.h"

class CMockPrioritizedObserver : public IObserver<SWeatherInfo>
{
public:
	CMockPrioritizedObserver(CWeatherData & weatherData, int priority, std::vector<int> & updateQueue)
		: m_weatherData(weatherData)
		, m_priority(priority)
		, m_updateQueue(updateQueue)
	{
		m_weatherData.RegisterObserver(*this, priority);
	}

private:
	void Update(SWeatherInfo const& data) override
	{
		m_updateQueue.push_back(m_priority);
	}

	CWeatherData & m_weatherData;
	std::vector<int> & m_updateQueue;
	int m_priority;
};