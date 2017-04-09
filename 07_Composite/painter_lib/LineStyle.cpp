#include "stdafx.h"
#include "LineStyle.h"

CLineStyle::CLineStyle(boost::optional<bool> isEnabled, boost::optional<CRGBAColor> color, size_t lineWidth)
	: m_isEnabled(isEnabled)
	, m_color(color)
	, m_lineWidth(lineWidth)
{
}

boost::optional<bool> CLineStyle::IsEnabled() const
{
	return m_isEnabled;
}

void CLineStyle::Enable(bool enable)
{
	m_isEnabled = enable;
}

boost::optional<CRGBAColor> CLineStyle::GetColor() const
{
	return m_color;
}

void CLineStyle::SetColor(CRGBAColor color)
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
