#include "stdafx.h"
#include "Rectangle.h"
#include "ICanvas.h"

CRectangle::CRectangle(const SPoint & leftTop, double width, double height)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
	CalculateFrame();
}

void CRectangle::Draw(ICanvas & canvas)
{
	BeginDraw(canvas);

	canvas.MoveTo(m_leftTop.x, m_leftTop.y);

	canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
	canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
	canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
	canvas.LineTo(m_leftTop.x, m_leftTop.y);

	EndDraw(canvas);
}

RectD CRectangle::GetFrame() const
{
	return m_frame;
}

void CRectangle::SetFrame(const RectD & rect)
{
	m_leftTop = { rect.left, rect.top };
	m_width = rect.width;
	m_height = rect.height;
	CalculateFrame();
}

void CRectangle::CalculateFrame()
{
	m_frame = { m_leftTop.x, m_leftTop.y, m_width, m_height };
}
