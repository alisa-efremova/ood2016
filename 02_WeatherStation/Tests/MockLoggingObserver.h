#pragma once
#include "IObserver.h"
#include "WeatherData.h"
#include <vector>

typedef std::vector<const class CMockLoggingObserver *> ObserverVector;

class CMockLoggingObserver : public IObserver<CWeatherData>
{
public:
	CMockLoggingObserver(ObserverVector & updateQueue) 
		: m_updateQueue(updateQueue)
	{
	}

private:
	void Update(CWeatherData const& subject)
	{
		m_updateQueue.push_back(this);
	}
	
	ObserverVector & m_updateQueue;
};
