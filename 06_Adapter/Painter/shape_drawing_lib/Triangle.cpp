#include "stdafx.h"
#include "Triangle.h"

using namespace shape_drawing_lib;

CTriangle::CTriangle(const Point & p1, const Point & p2, const Point & p3)
	: m_p1(p1)
	, m_p2(p2)
	, m_p3(p3)
{
}

void CTriangle::Draw(graphics_lib::ICanvas & canvas) const
{
}
