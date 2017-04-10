#include "stdafx.h"
#include "Rectangle.h"
#include "ICanvas.h"

CRectangle::CRectangle(const SPoint & leftTop, double width, double height)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}

void CRectangle::Draw(ICanvas & canvas)
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

	canvas.MoveTo(m_leftTop.x, m_leftTop.y);

	canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
	canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
	canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
	canvas.LineTo(m_leftTop.x, m_leftTop.y);

	if (isFillStyleEnabled)
	{
		canvas.EndFill();
	}
}

RectD CRectangle::GetFrame() const
{
	return { m_leftTop.x, m_leftTop.y, m_width, m_height };
}

void CRectangle::SetFrame(const RectD & rect)
{
	m_leftTop = { rect.left, rect.top };
	m_width = rect.width;
	m_height = rect.height;
}
