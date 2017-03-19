#pragma once

struct SPoint
{
	SPoint()
		: x(0.0), y(0.0)
	{
	}

	SPoint(double x, double y)
		: x(x), y(y)
	{
	}

	double x = 0.0;
	double y = 0.0;

	SPoint & operator =(const SPoint & a)
	{
		x = a.x;
		y = a.y;
		return *this;
	}

	bool operator ==(const SPoint& a) const
	{
		return (x == a.x && y == a.y);
	}
};