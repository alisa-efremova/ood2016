#include "stdafx.h"
#include "StatsCalc.h"

const double maxDiff = 0.0001;

BOOST_AUTO_TEST_CASE(TestCalcStats)
{
	CStatsCalc statsCalc;
	BOOST_CHECK(std::isinf(statsCalc.GetMin()));
	BOOST_CHECK(std::isinf(-statsCalc.GetMax()));
	BOOST_CHECK_CLOSE(statsCalc.GetAverage(), 0, maxDiff);
	
	statsCalc.Update(10);
	BOOST_CHECK_CLOSE(statsCalc.GetMin(), 10, maxDiff);
	BOOST_CHECK_CLOSE(statsCalc.GetMax(), 10, maxDiff);
	BOOST_CHECK_CLOSE(statsCalc.GetAverage(), 10, maxDiff);

	statsCalc.Update(4);
	BOOST_CHECK_CLOSE(statsCalc.GetMin(), 4, maxDiff);
	BOOST_CHECK_CLOSE(statsCalc.GetMax(), 10, maxDiff);
	BOOST_CHECK_CLOSE(statsCalc.GetAverage(), 7, maxDiff);

	statsCalc.Update(-2);
	BOOST_CHECK_CLOSE(statsCalc.GetMin(), -2, maxDiff);
	BOOST_CHECK_CLOSE(statsCalc.GetMax(), 10, maxDiff);
	BOOST_CHECK_CLOSE(statsCalc.GetAverage(), 4, maxDiff);

	statsCalc.Update(12);
	BOOST_CHECK_CLOSE(statsCalc.GetMin(), -2, maxDiff);
	BOOST_CHECK_CLOSE(statsCalc.GetMax(), 12, maxDiff);
	BOOST_CHECK_CLOSE(statsCalc.GetAverage(), 6, maxDiff);
}

BOOST_AUTO_TEST_CASE(TestWindDirectionStats)
{
	CWindDirectionStatsCalc statsCalc;
	BOOST_CHECK(std::isinf(statsCalc.GetMin()));
	BOOST_CHECK(std::isinf(-statsCalc.GetMax()));
	BOOST_CHECK_CLOSE(statsCalc.GetAverage(), 0, maxDiff);

	statsCalc.Update(0);
	BOOST_CHECK_CLOSE(statsCalc.GetMin(), 0, maxDiff);
	BOOST_CHECK_CLOSE(statsCalc.GetMax(), 0, maxDiff);
	BOOST_CHECK_CLOSE(statsCalc.GetAverage(), 0, maxDiff);

	statsCalc.Update(90);
	BOOST_CHECK_CLOSE(statsCalc.GetMin(), 0, maxDiff);
	BOOST_CHECK_CLOSE(statsCalc.GetMax(), 90, maxDiff);
	BOOST_CHECK_CLOSE(statsCalc.GetAverage(), 45, maxDiff);

	statsCalc.Update(-45);
	BOOST_CHECK_CLOSE(statsCalc.GetMin(), -45, maxDiff);
	BOOST_CHECK_CLOSE(statsCalc.GetMax(), 90, maxDiff);
	BOOST_CHECK_CLOSE(statsCalc.GetAverage(), 0, maxDiff);

	statsCalc.Update(300);
	BOOST_CHECK_CLOSE(statsCalc.GetMin(), -45, maxDiff);
	BOOST_CHECK_CLOSE(statsCalc.GetMax(), 300, maxDiff);
	BOOST_CHECK_CLOSE(statsCalc.GetAverage(), 330, maxDiff);

	statsCalc.Update(100);
	BOOST_CHECK_CLOSE(statsCalc.GetMin(), -45, maxDiff);
	BOOST_CHECK_CLOSE(statsCalc.GetMax(), 300, maxDiff);
	BOOST_CHECK_CLOSE(statsCalc.GetAverage(), 35, maxDiff);
}