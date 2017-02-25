#pragma once
#include "IObserver.h"
#include "SWeatherInfo.h"
#include <vector>

typedef std::vector<const class CMockLoggingObserver *> ObserverVector;

class CMockLoggingObserver : public IObserver<SWeatherInfo>
{
public:
	CMockLoggingObserver(ObserverVector & updateQueue) 
		: m_updateQueue(updateQueue)
	{
	}

private:
	void Update(SWeatherInfo const& data)
	{
		m_updateQueue.push_back(this);
	}
	
	ObserverVector & m_updateQueue;
};
