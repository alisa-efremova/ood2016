#pragma once
#include "IObserver.h"

template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;

	// @param priority - 0 by default, the highest possible priority
	// @param eventId - 0 by default, 0 reserved for defining 'ALL events', otherwise id of concrete event is expected
	virtual void RegisterObserver(IObserver<T> & observer, size_t priority, size_t eventId) = 0;
	virtual void NotifyObservers(size_t eventId) = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};