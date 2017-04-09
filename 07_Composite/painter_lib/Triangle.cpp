#include "stdafx.h"
#include "Triangle.h"
#include "ICanvas.h"

CTriangle::CTriangle(const SPoint & p1, const SPoint & p2, const SPoint & p3)
	: m_p1(p1)
	, m_p2(p2)
	, m_p3(p3)
{
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

	canvas.MoveTo(m_p1.x, m_p1.y);

	canvas.LineTo(m_p2.x, m_p2.y);
	canvas.LineTo(m_p3.x, m_p3.y);
	canvas.LineTo(m_p1.x, m_p1.y);

	if (isFillStyleEnabled)
	{
		canvas.EndFill();
	}
}

RectD CTriangle::GetFrame() const
{
	return {0,0,0,0};
}

void CTriangle::SetFrame(const RectD & rect)
{
}
