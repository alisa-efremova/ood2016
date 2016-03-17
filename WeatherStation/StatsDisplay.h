#pragma once
#include "IObserver.h"
#include "SWeatherInfo.h"
#include <climits>

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override;

	double m_minTemperature = std::numeric_limits<double>::infinity();
	double m_maxTemperature = -std::numeric_limits<double>::infinity();
	double m_accTemperature = 0;
	unsigned m_countAcc = 0;
};

