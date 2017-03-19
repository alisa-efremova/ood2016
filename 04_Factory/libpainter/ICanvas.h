#pragma once
#include "Color.h"
#include "SPoint.h"

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(SPoint from, SPoint to) = 0;
	virtual void DrawEllipse(SPoint center, double hRadius, double vRadius) = 0;
	virtual void StartDrawing() = 0;
	virtual void CompleteDrawing() = 0;
};