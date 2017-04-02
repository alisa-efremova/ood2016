#include "stdafx.h"
#include "ModernCanvasAdapter.h"

using namespace app;

CModernCanvasAdapter::CModernCanvasAdapter(modern_graphics_lib::CModernGraphicsRenderer & renderer)
	: m_renderer(renderer)
{
}

void CModernCanvasAdapter::LineTo(int x, int y)
{
	m_renderer.DrawLine(m_start, { x, y });
	MoveTo(x, y);
}

void CModernCanvasAdapter::MoveTo(int x, int y)
{
	m_start = { x, y };
}

