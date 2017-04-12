#include "stdafx.h"
#include "Ellipse.h"
#include "ICanvas.h"

CEllipse::CEllipse(SPoint center, double hRadius, double vRadius)
	: m_center(center)
{
	if (hRadius <= 0 || vRadius <= 0)
	{
		throw std::invalid_argument("Radius should be positive number.");
	}

	m_hRadius = hRadius;
	m_vRadius = vRadius;
	CalculateFrame();
}

void CEllipse::Draw(ICanvas & canvas)
{
	BeginDraw(canvas);
	canvas.DrawEllipse(m_center.x, m_center.y, m_hRadius, m_vRadius);
	EndDraw(canvas);
}

RectD CEllipse::GetFrame() const
{
	return m_frame;
}

void CEllipse::SetFrame(const RectD & rect)
{
	m_center.x = rect.left + rect.width / 2;
	m_center.y = rect.top + rect.height / 2;
	m_hRadius = rect.width / 2;
	m_vRadius = rect.height / 2;
	CalculateFrame();
}

void CEllipse::CalculateFrame()
{
	m_frame = { m_center.x - m_hRadius, m_center.y - m_vRadius, 2 * m_vRadius, 2 * m_hRadius };
}
