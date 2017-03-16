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
};