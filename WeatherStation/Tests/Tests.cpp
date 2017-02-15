#include "stdafx.h"
#include "WeatherData.h"
#include "MockUnsubscribingObserver.h"
#include "MockPrioritizedObserver.h"
#include <vector>

using namespace std;

BOOST_AUTO_TEST_CASE(TestObserverUnsubscribtionWhenNotified)
{
	CWeatherData wd;
	CMockUnsubscribingObserver observer1(wd);
	CMockUnsubscribingObserver observer2(wd);
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(3, 0.7, 760));
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(4, 0.8, 761));
}

BOOST_AUTO_TEST_CASE(TestNotifyingObserversAccordingToPriority)
{
	CWeatherData wd;
	vector<int> updateQueue;
	BOOST_CHECK(updateQueue.empty());

	CMockPrioritizedObserver observer1(wd, 10, updateQueue);
	CMockPrioritizedObserver observer2(wd, 5, updateQueue);
	CMockPrioritizedObserver observer3(wd, 4, updateQueue);

	BOOST_CHECK_NO_THROW(wd.SetMeasurements(3, 0.7, 760));

	std::vector<int> correctQueue = { 4, 5, 10 };
	BOOST_CHECK_EQUAL(updateQueue.size(), correctQueue.size());
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue.begin(), updateQueue.end(), correctQueue.begin(), correctQueue.end());
}