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

struct SProStatsWeatherInfo
{
	CStatsCalc temperatureStats;
	CStatsCalc humidityStats;
	CStatsCalc pressureStats;
	CStatsCalc windSpeedStats;
	CWindDirectionStatsCalc windDirectionStats;

	void Print()const
	{
		std::cout << "Temperature\t";
		temperatureStats.Print();
		std::cout << "Humidity\t";
		humidityStats.Print();
		std::cout << "Pressure\t";
		pressureStats.Print();
		std::cout << "Wind speed\t";
		windSpeedStats.Print();
		std::cout << "Wind direction\t";
		windDirectionStats.Print();
	}
};