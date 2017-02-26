#pragma once

#define _USE_MATH_DEFINES
#include "math.h"
#include <string>


class CStatsCalc
{
public:
	CStatsCalc() {}
	virtual ~CStatsCalc() {}

	void Update(double newVal)
	{
		UpdateMin(newVal);
		UpdateMax(newVal);
		UpdateAverage(newVal);
	}

	void Print()const
	{
		std::cout << "max: " << m_maxVal << "\tmin: " << m_minVal << "\tavg: " << GetAverage() << std::endl;
	}

	double GetMin()const
	{
		return m_minVal;
	}

	double GetMax()const
	{
		return m_maxVal;
	}

	virtual double GetAverage()const
	{
		return m_count == 0 ? 0 : m_accVal / m_count;
	}

protected:
	void UpdateMin(double newVal)
	{
		if (m_minVal > newVal)
		{
			m_minVal = newVal;
		}
	}

	void UpdateMax(double newVal)
	{
		if (m_maxVal < newVal)
		{
			m_maxVal = newVal;
		}
	}

	virtual void UpdateAverage(double newVal)
	{
		m_accVal += newVal;
		++m_count;
	}

	double m_minVal = std::numeric_limits<double>::infinity();
	double m_maxVal = - std::numeric_limits<double>::infinity();
	double m_accVal = 0;
	double m_count = 0;
};

class CWindDirectionStatsCalc : public CStatsCalc
{
public:
	CWindDirectionStatsCalc()
		:CStatsCalc()
	{
	}

	virtual double GetAverage()const override
	{
		double avg = atan2(m_accY, m_accX) * 180 / M_PI;
		return avg >= 0 ? avg : 360 + avg;
	}

private:
	void UpdateAverage(double newVal) override
	{
		m_accX += cos(newVal * M_PI / 180);
		m_accY += sin(newVal * M_PI / 180);
		double length = sqrt(m_accX * m_accX + m_accY * m_accY);
		if (length != 0)
		{
			// normalize coordinates
			m_accX /= length;
			m_accY /= length;
		}
	}

	double m_accX = 0;
	double m_accY = 0;
};