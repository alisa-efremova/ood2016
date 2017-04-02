#include "stdafx.h"
#include "ModernCanvasAdapter.h"

using namespace app;

CModernCanvasAdapter::CModernCanvasAdapter(modern_graphics_lib::CModernGraphicsRenderer & renderer)
	: m_renderer(renderer)
{
}

void CModernCanvasAdapter::LineTo(int x, int y)
{
	m_renderer.DrawLine(m_start, { x, y }, m_color);
	MoveTo(x, y);
}

void CModernCanvasAdapter::SetColor(uint32_t rgbColor)
{
	m_color.r = (float)((rgbColor >> 16) & 0xFF) / 255;
	m_color.g = (float)((rgbColor >> 8) & 0xFF) / 255;
	m_color.b = (float)((rgbColor) & 0xFF) / 255;
	m_color.a = 1.0;
}

void CModernCanvasAdapter::MoveTo(int x, int y)
{
	m_start = { x, y };
}

