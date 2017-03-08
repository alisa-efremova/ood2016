#pragma once

#include "IBeverage.h"

class CBeverage : public IBeverage
{
public:
	CBeverage() {}

	std::string GetDescription() const override final
	{
		return m_description;
	}

protected:
	void SetDescription(const std::string & description)
	{
		m_description = description;
	}

private:
	std::string m_description;
};
