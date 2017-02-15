#pragma once
#include "IObserver.h"
#include "ObservableLocation.h"

template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer, int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;

	virtual ObservableLocation GetLocation()const = 0;
};