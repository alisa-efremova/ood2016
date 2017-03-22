#pragma once
#include "ICanvas.h"
#include "SPoint.h"
#include "Color.h"
#include <vector>

class CMockCanvas : public ICanvas
{
public:
	struct SLine
	{
		SPoint from;
		SPoint to;
		Color color;
	};

	struct SEllipse
	{
		SPoint center;
		double hRadius;
		double vRaduis;
		Color color;
	};

	void SetColor(Color color)
	{
		m_color = color;
	}

	void DrawLine(SPoint from, SPoint to)
	{
		lines.push_back(SLine{ from, to, m_color });
	}

	void DrawEllipse(SPoint center, double hRadius, double vRadius)
	{
		ellipses.push_back(SEllipse{ center, hRadius, vRadius, m_color });
	}

	void StartDrawing() {};
	void CompleteDrawing() {};

	
	std::vector<SLine> lines;
	std::vector<SEllipse> ellipses;

private:
	Color m_color;
};