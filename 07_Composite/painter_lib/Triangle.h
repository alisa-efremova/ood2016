#pragma once
#include "SimpleShape.h"
#include "SPoint.h"

class CTriangle : public CSimpleShape
{
public:
	CTriangle(const SPoint & p1, const SPoint & p2, const SPoint & p3);
	void Draw(ICanvas & canvas) override;
	
	RectD GetFrame()const override;
	void SetFrame(const RectD & rect) override;

private:
	SPoint m_p1;
	SPoint m_p2;
	SPoint m_p3;
};

