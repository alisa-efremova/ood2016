#include "stdafx.h"
#include "CanvasSVG.h"
#include <boost/format.hpp>

using namespace std;

CCanvasSVG::CCanvasSVG(std::ostream & ostream)
	: CCanvas(ostream)
{
}

void CCanvasSVG::BeginDraw()
{
	m_ostream << "<svg version = \"1.1\" xmlns = \"http://www.w3.org/2000/svg\">" << endl;
}

void CCanvasSVG::EndDraw()
{
	if (m_drawingPath)
	{
		EndPath();
	}
	m_ostream << "</svg>" << endl;
}

void CCanvasSVG::MoveTo(double x, double y)
{
	if (!m_drawingPath)
	{
		StartPath();
	}
	m_ostream << boost::format("M %1$.3f %2$.3f ") % x % y;
}

void CCanvasSVG::LineTo(double x, double y)
{
	if (!m_drawingPath)
	{
		MoveTo(0, 0);
	}
	m_ostream << boost::format("L %1$.3f %2$.3f ") % x % y;
}

void CCanvasSVG::DrawEllipse(double x, double y, double hRadius, double vRadius)
{
	if (m_drawingPath)
	{
		EndPath();
	}
	m_ostream << "  <ellipse ";
	SetFillStyle();
	SetLineStyle();
	m_ostream << boost::format(R"(cx="%1$.3f" cy="%2$.3f" rx="%3$.3f" ry="%4$.3f" )") % x % y % hRadius % vRadius;
	m_ostream << " />" << endl;
}

void CCanvasSVG::SetLineWidth(size_t width)
{
	CCanvas::SetLineWidth(width);
	EndPath();
}

void CCanvasSVG::SetLineColor(CRGBAColor color)
{
	CCanvas::SetLineColor(color);
	EndPath();
}

void CCanvasSVG::BeginFill(CRGBAColor color)
{
	CCanvas::BeginFill(color);
	EndPath();
}

void CCanvasSVG::EndFill()
{
	CCanvas::EndFill();
	EndPath();
}

void CCanvasSVG::StartPath()
{
	if (!m_drawingPath)
	{
		m_drawingPath = true;
		m_ostream << "  <path ";
		SetLineStyle();
		SetFillStyle();
		m_ostream << "d=\"";
	}
}

void CCanvasSVG::EndPath()
{
	if (m_drawingPath)
	{
		m_drawingPath = false;
		m_ostream << "\" />" << endl;
	}
}

void CCanvasSVG::SetLineStyle()
{
	m_ostream << boost::format(R"(stroke="#%1$06X" stroke-width="%2%" )") % m_lineColor.rgbColor % m_lineWidth;
}

void CCanvasSVG::SetFillStyle()
{
	if (m_fillColor)
	{
		m_ostream << boost::format(R"(fill="#%1$06X" fill-opacity="%2$.3f" )") % m_fillColor->rgbColor % m_fillColor->opacity;
	}
	else
	{
		m_ostream << "fill=\"none\" ";
	}
}
