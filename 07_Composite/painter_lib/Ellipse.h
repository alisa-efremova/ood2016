#pragma once
#include "SimpleShape.h"
#include "SPoint.h"

class CEllipse : public CSimpleShape
{
public:
	CEllipse(SPoint center, double hRadius, double vRadius);
	void Draw(ICanvas & canvas) override;

	RectD GetFrame()const override;
	void SetFrame(const RectD & rect) override;

private:
	void CalculateFrame() override;
	
	SPoint m_center;
	double m_hRadius;
	double m_vRadius;
};

