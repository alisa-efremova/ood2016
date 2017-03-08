#pragma once
#include "IObserver.h"
#include <boost/optional.hpp>
#include <set>

template <class T, typename TEventType>
class Subscription
{
public:
	Subscription(IObserver<T> * inpObserver, size_t inpPriority = 0, boost::optional<TEventType> inpEventType = {})
	: observer(inpObserver)
	, priority(inpPriority)
	{
		eventTypes.insert(inpEventType);
	}

	IObserver<T> *observer = nullptr;
	size_t priority = 0;
	std::set<boost::optional<TEventType>> eventTypes;
};