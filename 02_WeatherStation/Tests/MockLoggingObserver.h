#pragma once
#include "IObserver.h"
#include "WeatherData.h"
#include <vector>
#include <memory>

typedef std::vector<const class CMockLoggingObserver *> ObserverVector;

class CMockLoggingObserver : public IObserver<CWeatherData>
{
public:
	CMockLoggingObserver(std::shared_ptr<ObserverVector> updateQueue)
		: m_updateQueue(updateQueue)
	{
	}

private:
	void Update(CWeatherData const& subject)
	{
		m_updateQueue->push_back(this);
	}
	
	std::shared_ptr<ObserverVector> m_updateQueue;
};
