#pragma once
#include "IObservable.h"
#include <list>
#include <iterator>

template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	CObservable()
	{
	}

	CObservable(ObservableLocation location)
		: m_location(location)
	{
	}

	void RegisterObserver(ObserverType & observer, int priority = 0) override
	{
		bool isObserverSaved = false;

		for (auto it = m_observers.begin(); it != m_observers.end(); ++it)
		{
			if (it->first > priority)
			{
				m_observers.insert(it, std::make_pair(priority, &observer));
				isObserverSaved = true;
				break;
			}
		}
		if (!isObserverSaved) {
			m_observers.push_back(std::make_pair(priority, &observer));
		}
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto observers = m_observers;
		
		for (auto it = observers.begin(); it != observers.end(); ++it)
		{
			it->second->Update(data, *this);
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		for (auto it = m_observers.begin(); it != m_observers.end(); ++it) {
			if (it->second == &observer) {
				m_observers.erase(it);
				break;
			}
		}
	}

	ObservableLocation GetLocation() const override
	{
		return m_location;
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::list<std::pair<int, ObserverType *>> m_observers;
	ObservableLocation m_location = ObservableLocation::UNDEFINED;
};
