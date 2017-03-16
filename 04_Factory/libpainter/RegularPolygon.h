#pragma once
#include "Shape.h"
#include "SPoint.h"

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(Color color, double vertexCount, SPoint center, double radius);
	double GetVertexCount()const;
	SPoint GetCenter()const;
	double GetRadius()const;
	void Draw(ICanvas & canvas) const override;

private:
	double m_vertexCount;
	SPoint m_center;
	double m_radius;
};

