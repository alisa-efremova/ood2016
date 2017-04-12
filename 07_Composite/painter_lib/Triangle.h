#pragma once
#include "SimpleShape.h"
#include "SPoint.h"
#include <vector>

class CTriangle : public CSimpleShape
{
public:
	CTriangle(const SPoint & p1, const SPoint & p2, const SPoint & p3);
	void Draw(ICanvas & canvas) override;
	
	RectD GetFrame()const override;
	void SetFrame(const RectD & rect) override;

private:
	void CalculateFrame() override;

	std::vector<SPoint> m_points;
};

