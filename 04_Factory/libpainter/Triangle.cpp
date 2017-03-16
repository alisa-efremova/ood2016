#include "stdafx.h"
#include "Triangle.h"
#include "ICanvas.h"

CTriangle::CTriangle(Color color, SPoint vertex1, SPoint vertex2, SPoint vertex3)
	: CShape(color)
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

SPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

SPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

SPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

void CTriangle::Draw(ICanvas & canvas) const
{
	canvas.SetColor(m_color);
	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex2, m_vertex3);
	canvas.DrawLine(m_vertex3, m_vertex1);
}