#pragma once
#include "Beverage.h"

enum class CoffeePortionSize
{
	STANDARD,
	DOUBLE
};

class CCoffee : public CBeverage
{
public:
	CCoffee()
	{
		SetDescription("Coffee");
	}

	double GetCost() const override
	{
		return 60;
	}

protected:
	CCoffee(std::string description, CoffeePortionSize size)
		:m_size(size)
	{
		SetDescription(GetCoffeePortionSizeDescription() + description);
	}

	CoffeePortionSize GetPortionSize() const
	{
		return m_size;
	}

private:
	std::string GetCoffeePortionSizeDescription() const
	{
		return m_size == CoffeePortionSize::DOUBLE ? "Double " : "";
	}

	CoffeePortionSize m_size = CoffeePortionSize::STANDARD;
};

class CCapuccino : public CCoffee
{
public:
	CCapuccino(CoffeePortionSize size = CoffeePortionSize::STANDARD)
		:CCoffee("Capuccino", size)
	{
	}

	double GetCost() const override
	{
		return GetPortionSize() == CoffeePortionSize::DOUBLE ? 120 : 80;
	}
};

class CLatte : public CCoffee
{
public:
	CLatte(CoffeePortionSize size = CoffeePortionSize::STANDARD)
		:CCoffee("Latte", size)
	{
	}

	double GetCost() const override
	{
		return GetPortionSize() == CoffeePortionSize::DOUBLE ? 130 : 90;
	}
};