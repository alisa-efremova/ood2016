#pragma once
#include "ICanvas.h"
#include <iostream>

class CCanvas : public ICanvas
{
public:
	CCanvas(std::ostream & ostream);

	void SetColor(Color color) override;
	void DrawLine(SPoint from, SPoint to) override;
	void DrawEllipse(SPoint center, double hRadius, double vRadius) override;

protected:
	Color m_color = Color::Black;
	std::ostream & m_ostream;
};

