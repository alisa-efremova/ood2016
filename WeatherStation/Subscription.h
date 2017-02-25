#pragma once
#include "IObserver.h"

template <class T>
class Subscription
{
public:
	Subscription(IObserver<T> * inpObserver, size_t inpPriority = 0, size_t inpEventId = 0)
	: observer(inpObserver)
	, priority(inpPriority)
	, eventId(inpEventId)
	{
	}

	IObserver<T> *observer = nullptr;
	size_t priority = 0;
	size_t eventId = 0;
};