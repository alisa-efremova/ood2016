#include "stdafx.h"
#include "Rectangle.h"

using namespace shape_drawing_lib;

CRectangle::CRectangle(const Point & leftTop, int width, int height)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}

void CRectangle::Draw(graphics_lib::ICanvas & canvas) const
{
}
