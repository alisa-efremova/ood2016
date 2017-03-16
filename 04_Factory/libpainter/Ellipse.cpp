#include "stdafx.h"
#include "Ellipse.h"
#include "ICanvas.h"

CEllipse::CEllipse(Color color, SPoint center, double hRadius, double vRadius)
	: CShape(color)
	, m_center(center)
	, m_hRadius(hRadius)
	, m_vRadius(vRadius)
{
}

SPoint CEllipse::GetCenter() const
{
	return m_center;
}

double CEllipse::GetHRadius() const
{
	return m_hRadius;
}

double CEllipse::GetVRadius() const
{
	return m_vRadius;
}

void CEllipse::Draw(ICanvas & canvas) const
{
	canvas.SetColor(m_color);
	canvas.DrawEllipse(m_center, m_hRadius, m_vRadius);
}
