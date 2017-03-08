#pragma once
#include "IObservable.h"
#include "Subscription.h"
#include <set>

template <class T, typename TEventType>
class CObservable : public IObservable<T, TEventType>
{
public:
	void RegisterObserver(ObserverType & observer, size_t priority = 0, OptionalEventType eventType = {}) override final
	{
		auto itObs = std::find_if(m_subscriptions.begin(), m_subscriptions.end(), [&observer](const SubscriptionPtr & subscription) {
			return subscription->observer == &observer;
		});

		if (itObs != m_subscriptions.end())
		{
			(*itObs)->eventTypes.insert(eventType);
		}
		else 
		{
			auto it = std::find_if(m_subscriptions.begin(), m_subscriptions.end(), [priority](const SubscriptionPtr & subscription) {
				return subscription->priority > priority;
			});
			m_subscriptions.insert(it, std::make_shared<Subscription<T, TEventType>>(&observer, priority, eventType));
		}
	}

	void NotifyObservers(OptionalEventType eventType = {}) override final
	{
		if (GetEventTypes().empty())
		{
			// no updates
			return;
		}

		const T * subject = GetConcreteObservable();
		auto subscriptions = m_subscriptions;

		for (auto subscription : subscriptions)
		{
			if (NeedNotifyObserver(subscription->eventTypes))
			{
				subscription->observer->Update(*subject);
			}
		}
	}

	void RemoveObserver(ObserverType & observer, OptionalEventType eventType = {}) override final
	{
		auto it = std::find_if(m_subscriptions.begin(), m_subscriptions.end(), [&observer](const SubscriptionPtr & subscription) {
			return subscription->observer == &observer;
		});

		if (it != m_subscriptions.end())
		{
			if (!eventType)
			{
				m_subscriptions.erase(it);
			}
			else
			{
				(*it)->eventTypes.erase(eventType);
				// if there no more events then remove subscription
				if ((*it)->eventTypes.empty())
				{
					m_subscriptions.erase(it);
				}
			}
		}
	}

protected:
	virtual const T * GetConcreteObservable()const = 0;
	virtual const std::set<OptionalEventType> & GetEventTypes()const = 0;

private:
	// Helper method
	bool NeedNotifyObserver(std::set<OptionalEventType> & eventTypes)
	{
		// check if observer is subscribed to all events
		if (eventTypes.find(boost::optional<TEventType>()) != eventTypes.end())
		{
			return true;
		}
		
		auto occurredEventTypes = GetEventTypes();

		for (auto occurredEventTypes : occurredEventTypes)
		{
			for (auto eventType : eventTypes)
			{
				if (occurredEventTypes == eventType)
				{
					return true;
				}
			}
		}
		return false;
	}
	
	typedef std::shared_ptr<Subscription<T, TEventType>> SubscriptionPtr;
	std::list<SubscriptionPtr> m_subscriptions;
};
