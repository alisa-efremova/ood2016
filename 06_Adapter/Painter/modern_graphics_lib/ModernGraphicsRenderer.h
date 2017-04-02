#pragma once
#include "Point.h"
#include "RGBAColor.h"

namespace modern_graphics_lib
{
	class CModernGraphicsRenderer
	{
	public:
		CModernGraphicsRenderer(std::ostream & strm);
		~CModernGraphicsRenderer();

		void BeginDraw();
		void DrawLine(const CPoint & start, const CPoint & end, const CRGBAColor & color = CRGBAColor(0, 0, 0, 1));
		void EndDraw();
	private:
		std::ostream & m_out;
		bool m_drawing = false;
	};
}
