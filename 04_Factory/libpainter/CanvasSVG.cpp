#include "stdafx.h"
#include "CanvasSVG.h"

using namespace std;

CCanvasSVG::CCanvasSVG(ostream & ostream) 
	: CCanvas(ostream)
{
}

void CCanvasSVG::DrawLine(SPoint from, SPoint to)
{
	m_ostream << "<line x1=\"" << from.x << "\" y1=\"" << from.y << "\" x2=\"" << to.x << "\" y2=\"" << to.y << "\" stroke-width=\"1\" stroke=\"" << GetColor(m_color) << "\"/> " << endl;
}

void CCanvasSVG::DrawEllipse(SPoint center, double hRadius, double vRadius)
{
	m_ostream << "<ellipse cx=\"" << center.x << "\" cy=\"" << center.y << "\" rx=\"" << hRadius << "\" ry=\"" << vRadius << "\" fill=\"none\" stroke-width=\"1\" stroke=\"" << GetColor(m_color) << "\"/>" << endl;
}

void CCanvasSVG::StartDrawing()
{
	m_ostream << "<svg version = \"1.1\" xmlns = \"http://www.w3.org/2000/svg\">" << endl;
}

void CCanvasSVG::CompleteDrawing()
{
	m_ostream << "</svg>" << endl;
}

string CCanvasSVG::GetColor(Color color) const
{
	switch (color)
	{
		case Color::Green:
			return "green";
		case Color::Red:
			return "red";
		case Color::Blue:
			return "blue";
		case Color::Yellow:
			return "yellow";
		case Color::Pink:
			return "pink";
		case Color::Black:
			return "black";
		default:
			return "none";
	}
}

