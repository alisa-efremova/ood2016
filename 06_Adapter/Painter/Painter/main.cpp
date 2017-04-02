#include "stdafx.h"
#include "shape_drawing_lib\CanvasPainter.h"
#include "shape_drawing_lib\Rectangle.h"
#include "shape_drawing_lib\Triangle.h"
#include "graphics_lib\Canvas.h"
#include "modern_graphics_lib\ModernGraphicsRenderer.h"
#include "ModernCanvasAdapter.h"
#include "ModernCanvasClassAdapter.h"

using namespace std;

namespace app
{
	void PaintPicture(shape_drawing_lib::CCanvasPainter & painter)
	{
		using namespace shape_drawing_lib;

		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0xE3B71A);
		CRectangle rectangle({ 30, 40 }, 18, 24, 0xFF10AB);

		painter.Draw(triangle);
		painter.Draw(rectangle);
	}

	void PaintPictureOnCanvas()
	{
		graphics_lib::CCanvas simpleCanvas;
		shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
		PaintPicture(painter);
	}

	void PaintPictureOnModernGraphicsRenderer()
	{
		modern_graphics_lib::CModernGraphicsRenderer renderer(cout);
		renderer.BeginDraw();
		
		CModernCanvasAdapter canvas(renderer);
		shape_drawing_lib::CCanvasPainter painter(canvas);
		PaintPicture(painter);
		
		renderer.EndDraw();
	}

	void PaintPictureOnModernGraphicsRendererClassAdapter()
	{
		CModernCanvasClassAdapter canvas(cout);
		canvas.BeginDraw();

		shape_drawing_lib::CCanvasPainter painter(canvas);
		PaintPicture(painter);

		canvas.EndDraw();
	}
}

int main()
{
	cout << "Should we use new API (y)? ";
	string userInput;
	if (getline(cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		app::PaintPictureOnModernGraphicsRendererClassAdapter();
	}
	else
	{
		app::PaintPictureOnCanvas();
	}

	return 0;
}