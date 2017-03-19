#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "math.h"

#include <exception>
#include "RegularPolygon.h"
#include "ICanvas.h"

CRegularPolygon::CRegularPolygon(Color color, unsigned vertexCount, SPoint center, double radius)
	: CShape(color)
	, m_center(center)
{
	if (vertexCount < 3)
	{
		std::invalid_argument("Polygon should have at least 3 vertexes.");
	}

	if (radius <= 0)
	{
		std::invalid_argument("Radius should be positive number.");
	}

	m_vertexCount = vertexCount;
	m_radius = radius;
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

	for (int i = 1; i <= m_vertexCount; i++)
	{
		double angle = 2 * M_PI * i / m_vertexCount;
		toPoint.x = m_radius * cos(angle) + m_center.x;
		toPoint.y = m_radius * sin(angle) + m_center.y;
		canvas.DrawLine(fromPoint, toPoint);
		fromPoint = toPoint;
	}
}
