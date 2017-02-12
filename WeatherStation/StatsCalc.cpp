#include "stdafx.h"
#include "StatsCalc.h"

using namespace std;

CStatsCalc::CStatsCalc(const std::string& title)
	:m_title(title)
{
}

void CStatsCalc::update(double newVal)
{
	if (m_minVal > newVal)
	{
		m_minVal = newVal;
	}
	if (m_maxVal < newVal)
	{
		m_maxVal = newVal;
	}
	m_accVal += newVal;
	++m_count;
}

void CStatsCalc::print() const
{
	cout << "* " << m_title << " stats *" << endl;
	cout << "Max: " << m_maxVal << endl;
	cout << "Min: " << m_minVal << endl;
	cout << "Average: " << (m_accVal / m_count) << endl;
	cout << "----------------" << endl;
}
