#pragma once
#include "Canvas.h"
#include <string>

class CCanvasSVG : public CCanvas
{
public:
	CCanvasSVG(std::ostream & ostream);
	void BeginDraw();
	void EndDraw();

	void MoveTo(double x, double y) override;
	void LineTo(double x, double y) override;
	void DrawEllipse(double x, double y, double hRadius, double vRadius) override;

	void SetLineWidth(size_t width) override;
	void SetLineColor(CRGBAColor color) override;
	void BeginFill(CRGBAColor color) override;
	void EndFill() override;

private:
	void StartPath();
	void EndPath();
	void SetLineStyle();
	void SetFillStyle();

	bool m_drawingPath = false;
	
};

