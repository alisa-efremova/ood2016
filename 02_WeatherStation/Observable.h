#pragma once
#include "IObservable.h"
#include "Subscription.h"
#include <set>

template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType & observer, size_t priority = 0, size_t eventId = 0) override
	{
		auto itObs = std::find_if(m_subscriptions.begin(), m_subscriptions.end(), [&observer](const SubscriptionPtr & subscription) {
			return subscription->observer == &observer;
		});

		if (itObs != m_subscriptions.end())
		{
			(*itObs)->eventIds.insert(eventId);
		}
		else 
		{
			auto it = std::find_if(m_subscriptions.begin(), m_subscriptions.end(), [priority](const SubscriptionPtr & subscription) {
				return subscription->priority > priority;
			});
			m_subscriptions.insert(it, std::make_shared<Subscription<T>>(&observer, priority, eventId));
		}
	}

	void NotifyObservers(size_t eventId = 0) override
	{
		if (GetEventIds().empty())
		{
			// no updates
			return;
		}

		const T * subject = GetConcreteObservable();
		auto subscriptions = m_subscriptions;

		for (auto subscription : subscriptions)
		{
			if (NeedNotifyObserver(subscription->eventIds))
			{
				subscription->observer->Update(*subject);
			}
		}
	}

	void RemoveObserver(ObserverType & observer, size_t eventId = 0) override
	{
		auto it = std::find_if(m_subscriptions.begin(), m_subscriptions.end(), [&observer](const SubscriptionPtr & subscription) {
			return subscription->observer == &observer;
		});

		if (it != m_subscriptions.end())
		{
			if (eventId == 0)
			{
				m_subscriptions.erase(it);
			}
			else
			{
				(*it)->eventIds.erase(eventId);
				// if there no more events then remove subscription
				if ((*it)->eventIds.empty())
				{
					m_subscriptions.erase(it);
				}
			}
		}
	}

protected:
	virtual const T * GetConcreteObservable()const = 0;
	virtual const std::set<size_t> & GetEventIds()const = 0;

private:
	// Helper method
	bool NeedNotifyObserver(const std::set<size_t> &eventIds)
	{
		// check if observer is subscribed to all events and if any data was changed
		if (eventIds.find(0) != eventIds.end())
		{
			return true;
		}

		auto occurredEventIds = GetEventIds();

		for (size_t occurredEventId : occurredEventIds)
		{
			for (size_t eventId : eventIds)
			{
				if (occurredEventId == eventId)
				{
					return true;
				}
			}
		}
		return false;
	}

	typedef std::shared_ptr<Subscription<T>> SubscriptionPtr;
	std::list<SubscriptionPtr> m_subscriptions;
};
