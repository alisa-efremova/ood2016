#pragma once
#include "IObserver.h"
#include <boost/optional.hpp>

template <typename T, typename TEventType>
class IObservable
{
public:
	virtual ~IObservable() = default;

	//using OptionalEventType = boost::optional<TEventType>;

	// @param priority - 0 by default, priority is set only at first time (ignored at further registrations)
	// @param eventType - empty by default, means 'ALL events', otherwise concrete event type is expected
	virtual void RegisterObserver(IObserver<T> & observer, size_t priority, boost::optional<TEventType> eventType = {}) = 0;
	virtual void NotifyObservers(boost::optional<TEventType> eventType = {}) = 0;
	virtual void RemoveObserver(IObserver<T> & observer, boost::optional<TEventType> eventType = {}) = 0;
};