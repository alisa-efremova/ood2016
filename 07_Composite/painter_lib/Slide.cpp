#include "stdafx.h"
#include "Slide.h"
#include "ICanvas.h"

double CSlide::GetWidth() const
{
	return m_shapes.GetFrame().width;
}

double CSlide::GetHeight() const
{
	return m_shapes.GetFrame().height;
}

IShapes & CSlide::GetShapes()
{
	return m_shapes;
}

void CSlide::Draw(ICanvas & canvas)
{
	m_shapes.Draw(canvas);
}
