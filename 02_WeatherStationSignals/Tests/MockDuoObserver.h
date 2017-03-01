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
	CMockDuoObserver(CWeatherData & inWeatherData, CProWeatherData & outWeatherData)
	: CDisplay(inWeatherData, outWeatherData)
	{
	}

	const LocationVector & GetUpdateQueue() const
	{
		return m_updateQueue;
	}

private:
	void OnInWeatherDataChange(const CWeatherData * subject) override
	{
		m_updateQueue.push_back(subject->GetLocation());
	}

	void OnOutWeatherDataChange(const CProWeatherData * subject) override
	{
		m_updateQueue.push_back(subject->GetLocation());
	}

	LocationVector m_updateQueue;
};
