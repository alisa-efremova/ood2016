#include "stdafx.h"
#include "Triangle.h"
#include "ICanvas.h"

CTriangle::CTriangle(const SPoint & p1, const SPoint & p2, const SPoint & p3)
{
	m_points.push_back(p1);
	m_points.push_back(p2);
	m_points.push_back(p3);
}

void CTriangle::Draw(ICanvas & canvas)
{
	bool isFillStyleEnabled = m_fillStyle && m_fillStyle->IsEnabled() && m_fillStyle->GetColor();
	if (isFillStyleEnabled)
	{
		canvas.BeginFill(*(m_fillStyle->GetColor()));
	}

	if (m_outlineStyle && m_outlineStyle->IsEnabled() && m_outlineStyle->GetColor())
	{
		canvas.SetLineColor(*(m_outlineStyle->GetColor()));
	}

	canvas.MoveTo(m_points[2].x, m_points[2].y);

	for (auto & point : m_points)
	{
		canvas.LineTo(point.x, point.y);
	}

	if (isFillStyleEnabled)
	{
		canvas.EndFill();
	}
}

RectD CTriangle::GetFrame() const
{
	auto minmax_x = std::minmax_element(m_points.begin(), m_points.end(),
		[](SPoint const& lhs, SPoint const& rhs) {return lhs.x < rhs.x; });
	auto minmax_y = std::minmax_element(m_points.begin(), m_points.end(),
		[](SPoint const& lhs, SPoint const& rhs) {return lhs.y < rhs.y; });

	return { minmax_x.first->x, minmax_y.first->y, minmax_x.second->x - minmax_x.first->x, minmax_y.second->y - minmax_y.first->y };
}

void CTriangle::SetFrame(const RectD & rect)
{
	auto oldFrame = GetFrame();
	for (auto & point : m_points)
	{
		point.x = rect.left + (point.x - oldFrame.left) / oldFrame.width * rect.width;
		point.y = rect.top + (point.y - oldFrame.top) / oldFrame.height * rect.height;
	}
}
