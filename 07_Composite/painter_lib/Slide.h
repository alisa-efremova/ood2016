#pragma once
#include "ISlide.h"
#include "GroupShape.h"

class CSlide : public ISlide
{
public:
	double GetWidth()const override;
	double GetHeight()const override;

	IShapes & GetShapes() override;

	void Draw(ICanvas & canvas) override;

private:
	CGroupShape m_shapes;
};