#pragma once
#include <cstdint>
#include <stdexcept>

class CRGBAColor
{
public:
	CRGBAColor(uint32_t rgbColor = 0, float opacity = 1.0)
		: rgbColor(rgbColor)
		, opacity(opacity)
	{
		if (opacity < 0.0 || opacity > 1.0)
		{
			throw std::invalid_argument("Opacity should have value between 0 and 1");
		}
	}

	uint32_t rgbColor;
	float opacity;
};