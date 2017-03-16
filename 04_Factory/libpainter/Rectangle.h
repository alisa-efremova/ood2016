#pragma once
#include "Shape.h"
#include "SPoint.h"

class CRectangle : public CShape
{
public:
	CRectangle(Color color, SPoint leftTop, SPoint rightBottom);
	SPoint GetLeftTop()const;
	SPoint GetRightBottom()const;
	void Draw(ICanvas & canvas) const override;

private:
	SPoint m_leftTop;
	SPoint m_rightBottom;
};

