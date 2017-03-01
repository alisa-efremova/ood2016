#include "stdafx.h"
#include "MockUnsubscribingObserver.h"
#include "MockPrioritizedObserver.h"

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
	shared_ptr<vector<int>> updateQueue = make_shared<vector<int>>();
	BOOST_CHECK(updateQueue->empty());

	CMockPrioritizedObserver observer1(wd, 10, updateQueue);
	CMockPrioritizedObserver observer2(wd, 5, updateQueue);
	CMockPrioritizedObserver observer3(wd, 4, updateQueue);

	BOOST_CHECK_NO_THROW(wd.SetMeasurements(3, 0.7, 760));

	std::vector<int> correctQueue = { 4, 5, 10 };
	BOOST_CHECK_EQUAL(updateQueue->size(), correctQueue.size());
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());
}

BOOST_AUTO_TEST_CASE(TestRemoveObserverFromTheEnd)
{
	CWeatherData wd;
	shared_ptr<vector<int>> updateQueue = make_shared<vector<int>>();
	BOOST_CHECK(updateQueue->empty());

	CMockPrioritizedObserver observer1(wd, 10, updateQueue);
	CMockPrioritizedObserver observer2(wd, 5, updateQueue);
	CMockPrioritizedObserver observer3(wd, 4, updateQueue);
	wd.RemoveObserver(observer1);

	BOOST_CHECK_NO_THROW(wd.SetMeasurements(3, 0.7, 760));
	std::vector<int> correctQueue = { 4, 5 };
	BOOST_CHECK_EQUAL(updateQueue->size(), correctQueue.size());
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());
}

BOOST_AUTO_TEST_CASE(TestRemoveObserverFromTheBegining)
{
	CWeatherData wd;
	shared_ptr<vector<int>> updateQueue = make_shared<vector<int>>();
	BOOST_CHECK(updateQueue->empty());

	CMockPrioritizedObserver observer1(wd, 10, updateQueue);
	CMockPrioritizedObserver observer2(wd, 5, updateQueue);
	CMockPrioritizedObserver observer3(wd, 4, updateQueue);
	wd.RemoveObserver(observer3);

	BOOST_CHECK_NO_THROW(wd.SetMeasurements(3, 0.7, 760));
	std::vector<int> correctQueue = { 5, 10 };
	BOOST_CHECK_EQUAL(updateQueue->size(), correctQueue.size());
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());
}

BOOST_AUTO_TEST_CASE(TestRemoveObserverFromTheMiddle)
{
	CWeatherData wd;
	shared_ptr<vector<int>> updateQueue = make_shared<vector<int>>();
	BOOST_CHECK(updateQueue->empty());

	CMockPrioritizedObserver observer1(wd, 10, updateQueue);
	CMockPrioritizedObserver observer2(wd, 5, updateQueue);
	CMockPrioritizedObserver observer3(wd, 4, updateQueue);
	wd.RemoveObserver(observer2);

	BOOST_CHECK_NO_THROW(wd.SetMeasurements(3, 0.7, 760));
	std::vector<int> correctQueue = { 4, 10 };
	BOOST_CHECK_EQUAL(updateQueue->size(), correctQueue.size());
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());
}