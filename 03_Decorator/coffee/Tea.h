#pragma once
#include "Beverage.h"

enum class TeaSort {
	Black,
	Green,
	White,
	Yellow
};

class CTea : public CBeverage
{
public:
	CTea(TeaSort sort = TeaSort::Black)
	{
		SetDescription(GetTeaSortDescription(sort) + " Tea");
	}

	double GetCost() const override
	{
		return 30;
	}

private:
	std::string GetTeaSortDescription(TeaSort sort) const
	{
		switch (sort)
		{
		case TeaSort::Black:
			return "Black";
		case TeaSort::Green:
			return "Green";
		case TeaSort::White:
			return "White";
		case TeaSort::Yellow:
			return "Yellow";
		default:
			return "";
		}
	}
};
