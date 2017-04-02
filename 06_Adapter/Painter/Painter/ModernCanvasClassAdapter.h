#pragma once
#include "graphics_lib\ICanvas.h"
#include "modern_graphics_lib\ModernGraphicsRenderer.h"

namespace app
{
	class CModernCanvasClassAdapter : public graphics_lib::ICanvas, private modern_graphics_lib::CModernGraphicsRenderer
	{
	public:
		
		CModernCanvasClassAdapter(std::ostream & strm);
		
		void MoveTo(int x, int y) override;
		void LineTo(int x, int y) override;
		void BeginDraw();
		void EndDraw();

	private:
		modern_graphics_lib::CPoint m_start = { 0, 0 };
	};
}
