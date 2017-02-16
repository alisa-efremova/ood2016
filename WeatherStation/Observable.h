#pragma once
#include "IObservable.h"

template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType & observer, int priority = 0) override
	{
		auto it = std::find_if(m_observers.begin(), m_observers.end(), [priority](const ObserverInfo& observerInfo) { 
			return observerInfo.first > priority;
		});
		m_observers.insert(it, std::make_pair(priority, &observer));
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto observers = m_observers;
		
		for (auto it = observers.begin(); it != observers.end(); ++it)
		{
			it->second->Update(data);
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		auto it = std::find_if(m_observers.begin(), m_observers.end(), [&observer](const ObserverInfo& observerInfo) {
			return observerInfo.second == &observer;
		});

		if (it != m_observers.end())
		{
			m_observers.erase(it);
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	typedef std::pair<int, ObserverType *> ObserverInfo;
	std::list<ObserverInfo> m_observers;
};
