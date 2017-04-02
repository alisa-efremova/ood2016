#include "stdafx.h"
#include "Rectangle.h"

using namespace shape_drawing_lib;

CRectangle::CRectangle(const Point & leftTop, int width, int height, uint32_t rgbColor)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
	, m_rgbColor(rgbColor)
{
}

void CRectangle::Draw(graphics_lib::ICanvas & canvas) const
{
	canvas.SetColor(m_rgbColor);

	canvas.MoveTo(m_leftTop.x, m_leftTop.y);

	canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
	canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
	canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
	canvas.LineTo(m_leftTop.x, m_leftTop.y);
}
