#include "stdafx.h"
#include "Canvas.h"

CCanvas::CCanvas(std::ostream & ostream)
	: m_ostream(ostream)
{
}

void CCanvas::SetColor(Color color)
{
	m_color = color;
}

void CCanvas::DrawLine(SPoint from, SPoint to)
{
	from;
	to;
}

void CCanvas::DrawEllipse(SPoint center, double hRadius, double vRadius)
{
	center;
	hRadius;
	vRadius;
}
