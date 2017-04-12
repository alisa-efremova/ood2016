#include "stdafx.h"
#include "Triangle.h"
#include "ICanvas.h"
#include <algorithm>
#include <limits>

using namespace std;

CTriangle::CTriangle(const SPoint & p1, const SPoint & p2, const SPoint & p3)
{
	m_points.push_back(p1);
	m_points.push_back(p2);
	m_points.push_back(p3);
	CalculateFrame();
}

void CTriangle::Draw(ICanvas & canvas)
{
	BeginDraw(canvas);

	canvas.MoveTo(m_points[2].x, m_points[2].y); // last point
	for (auto & point : m_points)
	{
		canvas.LineTo(point.x, point.y);
	}
	
	EndDraw(canvas);
}

RectD CTriangle::GetFrame() const
{
	return m_frame;
}

void CTriangle::SetFrame(const RectD & rect)
{
	auto oldFrame = GetFrame();
	for (auto & point : m_points)
	{
		point.x = rect.left + (point.x - oldFrame.left) / oldFrame.width * rect.width;
		point.y = rect.top + (point.y - oldFrame.top) / oldFrame.height * rect.height;
	}
	CalculateFrame();
}

void CTriangle::CalculateFrame()
{
	double minX = numeric_limits<double>::infinity();
	double minY = numeric_limits<double>::infinity();
	double maxX = -numeric_limits<double>::infinity();
	double maxY = -numeric_limits<double>::infinity();

	for (auto & point : m_points)
	{
		minX = min(minX, point.x);
		minY = min(minY, point.y);
		maxX = max(maxX, point.x);
		maxY = max(maxY, point.y);
	}
	m_frame = { minX, minY, maxX - minX, maxY - minY };
}
