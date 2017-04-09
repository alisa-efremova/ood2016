#include "stdafx.h"
#include "Style.h"

CStyle::CStyle(boost::optional<bool> isEnabled, boost::optional<CRGBAColor> color)
	: m_isEnabled(isEnabled)
	, m_color(color)
{
}

boost::optional<bool> CStyle::IsEnabled() const
{
	return m_isEnabled;
}

void CStyle::Enable(bool enable)
{
	m_isEnabled = enable;
}

boost::optional<CRGBAColor> CStyle::GetColor() const
{
	return m_color;
}

void CStyle::SetColor(CRGBAColor color)
{
	m_color = color;
}
