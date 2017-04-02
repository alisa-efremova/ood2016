#include "stdafx.h"
#include "Canvas.h"

using namespace graphics_lib;
using namespace std;

void CCanvas::MoveTo(int x, int y)
{
	cout << "MoveTo (" << x << ", " << y << ")" << endl;
}

void CCanvas::LineTo(int x, int y)
{
	cout << "LineTo (" << x << ", " << y << ")" << endl;
}

void CCanvas::SetColor(uint32_t rgbColor)
{
	cout << boost::format("SetColor (#%06X)") % rgbColor << endl;
}