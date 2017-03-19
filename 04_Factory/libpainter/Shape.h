#pragma once

#include "Color.h"
class ICanvas;

class CShape
{
public:
	CShape(Color color = Color::Black);
	virtual ~CShape();
	virtual void Draw(ICanvas & canvas)const = 0;
	virtual Color GetColor()const;

protected:
	Color m_color;
};

