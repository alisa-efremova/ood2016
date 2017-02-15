#pragma once
#include "iostream"

enum class ObservableLocation { IN, OUT, UNDEFINED };

inline std::ostream& operator<<(std::ostream & os, ObservableLocation type)
{
	switch (type)
	{
	case ObservableLocation::IN:
		os << "in";
		break;
	case ObservableLocation::OUT:
		os << "out";
	}
	return os;
}