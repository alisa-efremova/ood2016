#pragma once
#include <iostream>

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
	double m_maxVal = -std::numeric_limits<double>::infinity();
	double m_accVal = 0;
	double m_count = 0;
};