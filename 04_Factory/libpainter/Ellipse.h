#pragma once
#include "Shape.h"
#include "SPoint.h"

class CEllipse : public CShape
{
public:
	CEllipse(Color color, SPoint center, double hRadius, double vRadius);
	SPoint GetCenter()const;
	double GetHRadius()const;
	double GetVRadius()const;
	void Draw(ICanvas & canvas)const override;

private:
	SPoint m_center;
	double m_hRadius = 0;
	double m_vRadius = 0;
};

