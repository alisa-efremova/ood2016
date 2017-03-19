#include "stdafx.h"
#include "Rectangle.h"
#include "ICanvas.h"
#include <exception>
#include <iostream>

CRectangle::CRectangle(Color color, SPoint leftTop, SPoint rightBottom)
	: CShape(color)
{
	if (leftTop == rightBottom)
	{
		throw std::invalid_argument("Left top and right bottom points should not be equal.");
	}
	m_leftTop = leftTop;
	m_rightBottom = rightBottom;
}

SPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

SPoint CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}

void CRectangle::Draw(ICanvas & canvas) const
{
	canvas.SetColor(m_color);
	
	SPoint leftBottom = { m_leftTop.x, m_rightBottom.y };
	SPoint rightTop = { m_rightBottom.x, m_leftTop.y };

	canvas.DrawLine(m_leftTop, rightTop);
	canvas.DrawLine(rightTop, m_rightBottom);
	canvas.DrawLine(m_rightBottom, leftBottom);
	canvas.DrawLine(leftBottom, m_leftTop);
}