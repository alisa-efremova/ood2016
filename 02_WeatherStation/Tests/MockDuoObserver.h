#pragma once
#include "WeatherData.h"
#include "ProWeatherData.h"
#include "Display.h"
#include "WeatherStationLocation.h"
#include <vector>

typedef std::vector<WeatherStationLocation> LocationVector;

class CMockDuoObserver : public CDisplay
{
public:
	CMockDuoObserver() {}

	const LocationVector & GetUpdateQueue() const
	{
		return m_updateQueue;
	}

private:
	void Update(CWeatherData const& subject) override
	{
		m_updateQueue.push_back(subject.GetLocation());
	}

	void Update(CProWeatherData const& subject) override
	{
		m_updateQueue.push_back(subject.GetLocation());
	}

	LocationVector m_updateQueue;
};
