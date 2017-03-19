#pragma once
#include "Canvas.h"
#include <map>

class CCanvasSVG : public CCanvas
{
public:
	CCanvasSVG(std::ostream & ostream);
	void DrawLine(SPoint from, SPoint to) override;
	void DrawEllipse(SPoint center, double hRadius, double vRadius) override;
	void StartDrawing();
	void CompleteDrawing();
private:
	std::string GetColor(Color color)const;
};

