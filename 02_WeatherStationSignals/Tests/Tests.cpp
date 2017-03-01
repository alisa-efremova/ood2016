#include "stdafx.h"
#include "MockDuoObserver.h"

using namespace std;

BOOST_AUTO_TEST_CASE(TestObserversThatSupportBothWeatherStations)
{
	CWeatherData wdIn;
	CProWeatherData wdOut;
	CMockDuoObserver observer(wdIn, wdOut);

	BOOST_CHECK_NO_THROW(wdIn.SetMeasurements(3, 0.7, 760));
	LocationVector correctQueue = { WeatherStationLocation::IN };
	BOOST_CHECK_EQUAL_COLLECTIONS(observer.GetUpdateQueue().begin(), observer.GetUpdateQueue().end(), correctQueue.begin(), correctQueue.end());

	BOOST_CHECK_NO_THROW(wdOut.SetMeasurements(5, 0.8, 760, 10, 90));
	correctQueue.push_back(WeatherStationLocation::OUT);
	BOOST_CHECK_EQUAL_COLLECTIONS(observer.GetUpdateQueue().begin(), observer.GetUpdateQueue().end(), correctQueue.begin(), correctQueue.end());

	BOOST_CHECK_NO_THROW(wdOut.SetMeasurements(6, 0.8, 760, 5, 80));
	correctQueue.push_back(WeatherStationLocation::OUT);
	BOOST_CHECK_EQUAL_COLLECTIONS(observer.GetUpdateQueue().begin(), observer.GetUpdateQueue().end(), correctQueue.begin(), correctQueue.end());
}	