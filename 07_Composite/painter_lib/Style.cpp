#include "stdafx.h"
#include "Style.h"

CStyle::CStyle(bool isEnabled, const CRGBAColor & color)
	: m_isEnabled(isEnabled)
	, m_color(color)
{
}

bool CStyle::IsEnabled() const
{
	return m_isEnabled;
}

void CStyle::Enable(bool enable)
{
	m_isEnabled = enable;
}

CRGBAColor CStyle::GetColor() const
{
	return m_color;
}

void CStyle::SetColor(const CRGBAColor & color)
{
	m_color = color;
}
