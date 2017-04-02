#include "stdafx.h"
#include "shape_drawing_lib\CanvasPainter.h"
#include "shape_drawing_lib\Rectangle.h"
#include "shape_drawing_lib\Triangle.h"
#include "graphics_lib\Canvas.h"
#include "modern_graphics_lib\ModernGraphicsRenderer.h"

using namespace std;

namespace app
{
	void PaintPicture(shape_drawing_lib::CCanvasPainter & painter)
	{
		using namespace shape_drawing_lib;

		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
		CRectangle rectangle({ 30, 40 }, 18, 24);

		// TODO: нарисовать прямоугольник и треугольник при помощи painter
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
		(void)&renderer; // устраняем предупреждение о неиспользуемой переменной

						 // TODO: при помощи существующей функции PaintPicture() нарисовать
						 // картину на renderer
						 // Подсказка: используйте паттерн "Адаптер"
	}
}

int main()
{
	cout << "Should we use new API (y)?";
	string userInput;
	if (getline(cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		app::PaintPictureOnModernGraphicsRenderer();
	}
	else
	{
		app::PaintPictureOnCanvas();
	}

	return 0;
}