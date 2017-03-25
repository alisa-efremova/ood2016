#pragma once
#include "ICanvas.h"
#include <iostream>

class CCanvas : public ICanvas
{
public:
	CCanvas(std::ostream & ostream);

	void SetColor(Color color) override;
	virtual void DrawLine(SPoint from, SPoint to) override = 0;
	virtual void DrawEllipse(SPoint center, double hRadius, double vRadius) override = 0;

protected:
	Color m_color = Color::Black;
	std::ostream & m_ostream;
};

