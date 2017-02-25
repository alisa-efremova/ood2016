#pragma once
#include "IObservable.h"
#include "Subscription.h"

template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType & observer, size_t priority = 0, size_t eventId = 0) override
	{
		auto it = std::find_if(m_subscriptions.begin(), m_subscriptions.end(), [priority](const SubscriptionPtr & subscription) {
			return subscription->priority > priority;
		});
		m_subscriptions.insert(it, std::make_shared<Subscription<T>>(&observer, priority));
	}

	void NotifyObservers(size_t eventId = 0) override
	{
		T data = GetChangedData();
		auto subscriptions = m_subscriptions;
		for (auto subscription : subscriptions)
		{
			subscription->observer->Update(data);
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		auto it = std::find_if(m_subscriptions.begin(), m_subscriptions.end(), [&observer](const SubscriptionPtr & subscription) {
			return subscription->observer == &observer;
		});

		if (it != m_subscriptions.end())
		{
			m_subscriptions.erase(it);
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	typedef std::shared_ptr<Subscription<T>> SubscriptionPtr;
	std::list<SubscriptionPtr> m_subscriptions;
};
