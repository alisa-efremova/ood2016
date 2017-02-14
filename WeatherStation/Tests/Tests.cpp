#include "stdafx.h"
#include "WeatherData.h"
#include "MockDisplay.h"

BOOST_AUTO_TEST_CASE(TestObserverUnsubscribtionWhenNotified)
{
	CWeatherData wd;
	CMockDisplay display1(wd);
	CMockDisplay display2(wd);
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(3, 0.7, 760));
	BOOST_CHECK_NO_THROW(wd.SetMeasurements(4, 0.8, 761));
}