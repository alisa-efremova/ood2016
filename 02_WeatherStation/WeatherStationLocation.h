#pragma once
#include "iostream"

enum class WeatherStationLocation { IN = 1, OUT = 2 };

inline std::ostream& operator<<(std::ostream & os, WeatherStationLocation type)
{
	switch (type)
	{
	case WeatherStationLocation::IN:
		os << "in";
		break;
	case WeatherStationLocation::OUT:
		os << "out";
	}
	return os;
}