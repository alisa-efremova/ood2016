#pragma once
#include "Beverage.h"

enum class MilkshakePortionSize
{
	SMALL,
	STANDARD,
	BIG
};

class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakePortionSize size = MilkshakePortionSize::STANDARD)
		:m_size(size)
	{
		SetDescription(GetPortionSizeDescription() + "Milkshake");
	}

	double GetCost() const override
	{
		switch (m_size)
		{
		case MilkshakePortionSize::SMALL:
			return 50;
		case MilkshakePortionSize::BIG:
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
		case MilkshakePortionSize::SMALL:
			return "Small ";
		case MilkshakePortionSize::BIG:
			return "Big ";
		default:
			return "";
		}
	}

	MilkshakePortionSize m_size;
};