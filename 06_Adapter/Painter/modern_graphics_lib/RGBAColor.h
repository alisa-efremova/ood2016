#pragma once

namespace modern_graphics_lib
{
	// Цвет в формате RGBA, каждый компонент принимает значения от 0.0f до 1.0f
	class CRGBAColor
	{
	public:
		CRGBAColor(float r, float g, float b, float a) 
			: r(r), g(g), b(b), a(a) 
		{
			if (!isValidParam(r) || !isValidParam(g) || !isValidParam(b) || !isValidParam(a))
			{
				throw std::invalid_argument("Invalid parameter for RGBA color, should be between 0.0 and 1.0");
			}
		}

		float r, g, b, a;

	private:
		bool isValidParam(float param)
		{
			return (param >= 0.0 && param <= 1.0);
		}
	};
}