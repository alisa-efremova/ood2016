#include "stdafx.h"
#include "ModernCanvasClassAdapter.h"

using namespace app;
using namespace std;

CModernCanvasClassAdapter::CModernCanvasClassAdapter(ostream & strm)
	: CModernGraphicsRenderer(strm)
{
}

void CModernCanvasClassAdapter::MoveTo(int x, int y)
{
	m_start = { x, y };
}

void CModernCanvasClassAdapter::LineTo(int x, int y)
{
	DrawLine(m_start, { x, y }, m_color);
	MoveTo(x, y);
}

void CModernCanvasClassAdapter::SetColor(uint32_t rgbColor)
{
	m_color.r = (float)((rgbColor >> 16) & 0xFF) / 255;
	m_color.g = (float)((rgbColor >> 8) & 0xFF) / 255;
	m_color.b = (float)((rgbColor) & 0xFF) / 255;
	m_color.a = 1.0;
}

void CModernCanvasClassAdapter::BeginDraw()
{
	CModernGraphicsRenderer::BeginDraw();
}

void CModernCanvasClassAdapter::EndDraw()
{
	CModernGraphicsRenderer::EndDraw();
}
