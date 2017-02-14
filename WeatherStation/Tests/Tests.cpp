#include "stdafx.h"
#include "WeatherData.h"
#include "MockUnsubscribingObserver.h"

BOOST_AUTO_TEST_CASE(TestObserverUnsubscribtionWhenNotified)
{
	CWeatherData wd;
	CMockUnsubscribingObserver observer1(wd);
	CMockUnsubscribingObserver observer2(wd);
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(3, 0.7, 760));
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(4, 0.8, 761));
}