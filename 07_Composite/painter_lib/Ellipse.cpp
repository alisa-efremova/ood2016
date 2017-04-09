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
}

void CEllipse::Draw(ICanvas & canvas)
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

	canvas.DrawEllipse(m_center.x, m_center.y, m_hRadius, m_vRadius);

	if (isFillStyleEnabled)
	{
		canvas.EndFill();
	}
}

RectD CEllipse::GetFrame() const
{
	return { m_center.x - m_hRadius, m_center.y - m_vRadius, 2 * m_vRadius, 2 * m_hRadius };
}

void CEllipse::SetFrame(const RectD & rect)
{
	m_center.x = rect.left + rect.width / 2;
	m_center.y = rect.top + rect.height / 2;
	m_hRadius = rect.width / 2;
	m_vRadius = rect.height / 2;
}
