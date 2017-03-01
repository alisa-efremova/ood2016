#include "stdafx.h"
#include "MockLoggingObserver.h"
#include "WeatherInfoType.h"

using namespace std;

BOOST_AUTO_TEST_CASE(TestObserversSubscribingToAllChanges)
{
	CWeatherData wd;
	shared_ptr<ObserverVector> updateQueue = make_shared<ObserverVector>();
	CMockLoggingObserver observer1(updateQueue);
	CMockLoggingObserver observer2(updateQueue);

	wd.RegisterObserver(observer1, 2, 0);
	wd.RegisterObserver(observer2, 1, 0);

	// update data
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(3, 0.7, 760));
	ObserverVector correctQueue = { &observer2, &observer1 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// update data one more time
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(4, 0.8, 761));
	correctQueue = { &observer2, &observer1, &observer2, &observer1 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// remove observer on unexisting event
	wd.RemoveObserver(observer2, 1);
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(3, 0.8, 761));
	correctQueue = { &observer2, &observer1, &observer2, &observer1, &observer2, &observer1 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// remove observer from all events
	wd.RemoveObserver(observer2);
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(4, 0.8, 761));
	correctQueue = { &observer2, &observer1, &observer2, &observer1, &observer2, &observer1, &observer1 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// update data with no changes
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(4, 0.8, 761));
	correctQueue = { &observer2, &observer1, &observer2, &observer1, &observer2, &observer1, &observer1 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// remove last observer
	wd.RemoveObserver(observer1);
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(3, 0.8, 761));
	correctQueue = { &observer2, &observer1, &observer2, &observer1, &observer2, &observer1, &observer1 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());
}

BOOST_AUTO_TEST_CASE(TestObserversSubscribingToTempChanges)
{
	CWeatherData wd;
	shared_ptr<ObserverVector> updateQueue = make_shared<ObserverVector>();
	CMockLoggingObserver observer1(updateQueue);
	CMockLoggingObserver observer2(updateQueue);

	wd.RegisterObserver(observer1, 0, (int)WeatherInfoType::TEMPERATURE);
	wd.RegisterObserver(observer2, 1, (int)WeatherInfoType::TEMPERATURE);

	// update data
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(3, 0.7, 760));
	ObserverVector correctQueue = { &observer1, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// update data one more time
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(4, 0.8, 761));
	correctQueue = { &observer1, &observer2, &observer1, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// update data with no change in temperature
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(4, 1.0, 761));
	correctQueue = { &observer1, &observer2, &observer1, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// remove observer from temperature changes
	wd.RemoveObserver(observer1, (int)WeatherInfoType::TEMPERATURE);
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(5, 1.0, 761));
	correctQueue = { &observer1, &observer2, &observer1, &observer2, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// remove observer from pressure changes
	wd.RemoveObserver(observer2, (int)WeatherInfoType::HUMIDITY);
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(6, 1.0, 761));
	correctQueue = { &observer1, &observer2, &observer1, &observer2, &observer2, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// remove observer from all changes
	wd.RemoveObserver(observer2);
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(7, 1.0, 761));
	correctQueue = { &observer1, &observer2, &observer1, &observer2, &observer2, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());
}

BOOST_AUTO_TEST_CASE(TestObserversSubscribingToPressureChanges)
{
	CWeatherData wd;
	shared_ptr<ObserverVector> updateQueue = make_shared<ObserverVector>();
	CMockLoggingObserver observer1(updateQueue);
	CMockLoggingObserver observer2(updateQueue);

	wd.RegisterObserver(observer1, 0, (int)WeatherInfoType::PRESSURE);
	wd.RegisterObserver(observer2, 1, (int)WeatherInfoType::PRESSURE);

	// update data
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(3, 0.7, 759));
	ObserverVector correctQueue = { &observer1, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// update data one more time
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(4, 0.8, 761));
	correctQueue = { &observer1, &observer2, &observer1, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// update data with no change in pressure
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(5, 0.8, 761));
	correctQueue = { &observer1, &observer2, &observer1, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// remove observer from pressure changes
	wd.RemoveObserver(observer1, (int)WeatherInfoType::PRESSURE);
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(5, 1.0, 760));
	correctQueue = { &observer1, &observer2, &observer1, &observer2, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// remove observer from temperature changes
	wd.RemoveObserver(observer2, (int)WeatherInfoType::TEMPERATURE);
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(6, 1.1, 761));
	correctQueue = { &observer1, &observer2, &observer1, &observer2, &observer2, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// remove observer from all changes
	wd.RemoveObserver(observer2);
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(7, 1.2, 760));
	correctQueue = { &observer1, &observer2, &observer1, &observer2, &observer2, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());
}

BOOST_AUTO_TEST_CASE(TestObserversSubscribingToHumidityChanges)
{
	CWeatherData wd;
	shared_ptr<ObserverVector> updateQueue = make_shared<ObserverVector>();
	CMockLoggingObserver observer1(updateQueue);
	CMockLoggingObserver observer2(updateQueue);

	wd.RegisterObserver(observer1, 0, (int)WeatherInfoType::HUMIDITY);
	wd.RegisterObserver(observer2, 1, (int)WeatherInfoType::HUMIDITY);

	// update data
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(3, 0.7, 760));
	ObserverVector correctQueue = { &observer1, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// update data one more time
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(4, 0.8, 761));
	correctQueue = { &observer1, &observer2, &observer1, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// update data with no change in humidity
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(5, 0.8, 761));
	correctQueue = { &observer1, &observer2, &observer1, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// remove observer from humidity changes
	wd.RemoveObserver(observer1, (int)WeatherInfoType::HUMIDITY);
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(5, 1.0, 761));
	correctQueue = { &observer1, &observer2, &observer1, &observer2, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// remove observer from temperature changes
	wd.RemoveObserver(observer2, (int)WeatherInfoType::TEMPERATURE);
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(6, 1.1, 761));
	correctQueue = { &observer1, &observer2, &observer1, &observer2, &observer2, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// remove observer from all changes
	wd.RemoveObserver(observer2);
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(7, 1.2, 761));
	correctQueue = { &observer1, &observer2, &observer1, &observer2, &observer2, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());
}

BOOST_AUTO_TEST_CASE(TestObserversSubscribingToSeveralDataTypes)
{
	CWeatherData wd;
	shared_ptr<ObserverVector> updateQueue = make_shared<ObserverVector>();
	CMockLoggingObserver observer1(updateQueue);
	CMockLoggingObserver observer2(updateQueue);

	wd.RegisterObserver(observer1, 1, (int)WeatherInfoType::HUMIDITY);
	wd.RegisterObserver(observer2, 2, (int)WeatherInfoType::PRESSURE);

	// update data
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(3, 0.7, 759));
	ObserverVector correctQueue = { &observer1, &observer2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// register also for temperature changes, new priority should be ignored
	wd.RegisterObserver(observer2, 0, (int)WeatherInfoType::TEMPERATURE);

	// update only temperature
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(2, 0.7, 759));
	correctQueue.push_back(&observer2);
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// update all data to check priority
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(4, 0.6, 760));
	correctQueue.push_back(&observer1);
	correctQueue.push_back(&observer2);
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// update only humidity
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(4, 0.7, 760));
	correctQueue.push_back(&observer1);
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// update only pressure
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(4, 0.7, 761));
	correctQueue.push_back(&observer2);
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// update pressure and temperature - test that observer will be notified only once
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(5, 0.7, 760));
	correctQueue.push_back(&observer2);
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// subscribe observer1 to pressure changes and update pressure
	wd.RegisterObserver(observer1, 0, (int)WeatherInfoType::PRESSURE);
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(5, 0.7, 761));
	correctQueue.push_back(&observer1);
	correctQueue.push_back(&observer2);
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// unsubscribe observer2 from pressure changes and update pressure
	wd.RemoveObserver(observer2, (int)WeatherInfoType::PRESSURE);
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(5, 0.7, 760));
	correctQueue.push_back(&observer1);
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());

	// unsubscribe observer1 from all and update all data (observer 2 is still subscribed to temperature changes)
	wd.RemoveObserver(observer1);
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(10, 0.6, 761));
	correctQueue.push_back(&observer2);
	BOOST_CHECK_EQUAL_COLLECTIONS(updateQueue->begin(), updateQueue->end(), correctQueue.begin(), correctQueue.end());
}