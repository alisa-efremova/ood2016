#include "stdafx.h"
#include "LineStyle.h"

CLineStyle::CLineStyle(bool isEnabled, const CRGBAColor & color, size_t lineWidth)
	: m_isEnabled(isEnabled)
	, m_color(color)
	, m_lineWidth(lineWidth)
{
}

bool CLineStyle::IsEnabled() const
{
	return m_isEnabled;
}

void CLineStyle::Enable(bool enable)
{
	m_isEnabled = enable;
}

CRGBAColor CLineStyle::GetColor() const
{
	return m_color;
}

void CLineStyle::SetColor(const CRGBAColor & color)
{
	m_color = color;
}

size_t CLineStyle::GetLineWidth() const
{
	return m_lineWidth;
}

void CLineStyle::SetLineWidth(size_t width)
{
	m_lineWidth = width;
}
