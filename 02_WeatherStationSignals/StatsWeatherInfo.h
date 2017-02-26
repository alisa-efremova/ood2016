#pragma once
#include "StatsCalc.h"
#include <iostream>

struct SStatsWeatherInfo
{
	CStatsCalc temperatureStats;
	CStatsCalc humidityStats;
	CStatsCalc pressureStats;

	void Print()const
	{
		std::cout << "Temperature\t";
		temperatureStats.Print();
		std::cout << "Humidity\t";
		humidityStats.Print();
		std::cout << "Pressure\t";
		pressureStats.Print();
	}
};
