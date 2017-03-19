#pragma once
#include "ICanvas.h"
#include "SPoint.h"
#include <vector>

class CMockCanvas : public ICanvas
{
public:
	struct SLine
	{
		SPoint from;
		SPoint to;
	};

	struct SEllipse
	{
		SPoint center;
		double hRadius;
		double vRaduis;
	};

	void SetColor(Color color)
	{
		penColor = color;
	}

	void DrawLine(SPoint from, SPoint to)
	{
		lines.push_back(SLine{ from, to });
	}

	void DrawEllipse(SPoint center, double hRadius, double vRadius)
	{
		ellipses.push_back(SEllipse{ center, hRadius, vRadius });
	}

	void StartDrawing() {};
	void CompleteDrawing() {};

	Color penColor;
	std::vector<SLine> lines;
	std::vector<SEllipse> ellipses;
};