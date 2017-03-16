#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "math.h"

#include "RegularPolygon.h"
#include "ICanvas.h"
#include <iostream>

CRegularPolygon::CRegularPolygon(Color color, double vertexCount, SPoint center, double radius)
	: CShape(color)
	, m_vertexCount(vertexCount)
	, m_center(center)
	, m_radius(radius)
{
}

double CRegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}

SPoint CRegularPolygon::GetCenter() const
{
	return m_center;
}

double CRegularPolygon::GetRadius() const
{
	return m_radius;
}

void CRegularPolygon::Draw(ICanvas & canvas) const
{
	canvas.SetColor(m_color);

	SPoint fromPoint, toPoint;
	fromPoint.x = m_radius * cos(0) + m_center.x;
	fromPoint.y = m_radius * sin(0) + m_center.y;
	std::cout << "point( " << fromPoint.x << ", " << fromPoint.y << ")" << std::endl;
	for (int i = 1; i < m_vertexCount; i++)
	{
		double angle = 2 * M_PI * i / m_vertexCount;
		toPoint.x = m_radius * cos(angle) + m_center.x;
		toPoint.y = m_radius * sin(angle) + m_center.y;
		canvas.DrawLine(fromPoint, toPoint);
		fromPoint.x = toPoint.x;
		fromPoint.y = toPoint.y;
		std::cout << "point( " << round(fromPoint.x) << ", " << round(fromPoint.y) << ")" << std::endl;
	}
}
