#pragma once
#include "Beverage.h"

enum class MilkshakePortionSize
{
	Small,
	Standard,
	Big
};

class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakePortionSize size = MilkshakePortionSize::Standard)
		:m_size(size)
	{
		SetDescription(GetPortionSizeDescription() + "Milkshake");
	}

	double GetCost() const override
	{
		switch (m_size)
		{
		case MilkshakePortionSize::Small:
			return 50;
		case MilkshakePortionSize::Big:
			return 80;
		default:
			return 60;
		}
	}
private:
	std::string GetPortionSizeDescription() const
	{
		switch (m_size)
		{
		case MilkshakePortionSize::Small:
			return "Small ";
		case MilkshakePortionSize::Big:
			return "Big ";
		default:
			return "";
		}
	}

	MilkshakePortionSize m_size;
};