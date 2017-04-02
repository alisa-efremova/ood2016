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
	DrawLine(m_start, { x, y });
}

void CModernCanvasClassAdapter::BeginDraw()
{
	CModernGraphicsRenderer::BeginDraw();
}

void CModernCanvasClassAdapter::EndDraw()
{
	CModernGraphicsRenderer::EndDraw();
}
