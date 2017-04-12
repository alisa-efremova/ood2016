#pragma once
#include "SimpleShape.h"
#include "SPoint.h"

class CRectangle : public CSimpleShape
{
public:
	CRectangle(const SPoint & leftTop, double width, double height);
	void Draw(ICanvas & canvas) override;

	RectD GetFrame()const override;
	void SetFrame(const RectD & rect) override;

private:
	void CalculateFrame() override;

	SPoint m_leftTop;
	double m_width;
	double m_height;
};

