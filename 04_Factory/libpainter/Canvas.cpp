#include "stdafx.h"
#include "Canvas.h"

CCanvas::CCanvas(std::ostream & ostream)
	: m_ostream(ostream)
{
}

void CCanvas::SetColor(Color color)
{
	m_color = color;
}
