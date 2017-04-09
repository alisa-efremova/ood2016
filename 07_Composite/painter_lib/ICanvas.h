#pragma once
#include "RGBAColor.h"

class ICanvas
{
public:
	virtual void MoveTo(double x, double y) = 0;
	virtual void LineTo(double x, double y) = 0;
	virtual void DrawEllipse(double x, double y, double hRadius, double vRadius) = 0;
	virtual void SetLineWidth(size_t width) = 0;
	virtual void SetLineColor(CRGBAColor color) = 0;
	virtual void BeginFill(CRGBAColor color) = 0;
	virtual void EndFill() = 0;

	virtual ~ICanvas() = default;
};