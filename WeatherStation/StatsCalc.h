#pragma once
#include <string>

class CStatsCalc
{
public:
	CStatsCalc(const std::string & title);
	void update(double newVal);
	void print()const;
private:
	std::string m_title;
	double m_minVal = std::numeric_limits<double>::infinity();
	double m_maxVal = - std::numeric_limits<double>::infinity();
	double m_accVal = 0;
	double m_count = 0;
};
