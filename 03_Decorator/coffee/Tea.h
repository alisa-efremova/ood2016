#pragma once
#include "Beverage.h"

enum class TeaSort {
	BLACK,
	GREEN,
	WHITE,
	YELLOW
};

class CTea : public CBeverage
{
public:
	CTea(TeaSort sort = TeaSort::BLACK)
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
		case TeaSort::BLACK:
			return "Black";
		case TeaSort::GREEN:
			return "Green";
		case TeaSort::WHITE:
			return "White";
		case TeaSort::YELLOW:
			return "Yellow";
		default:
			return "";
		}
	}
};
