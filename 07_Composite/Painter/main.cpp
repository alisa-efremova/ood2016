#include "stdafx.h"
#include "CanvasSVG.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "LineStyle.h"
#include "Style.h"
#include <fstream>

using namespace std;

int main()
{
	ofstream ifs("../result.svg");
	if (!ifs.is_open())
	{
		cout << "Error while openning the file." << endl;
		return 1;
	}

	CCanvasSVG canvas(ifs);
	canvas.BeginDraw();

	CRectangle rect({ 100, 200 }, 300, 200);
	rect.SetFillStyle(make_unique<CStyle>(true, CRGBAColor(0x94631e)));
	rect.SetOutlineStyle(make_unique<CLineStyle>(true, CRGBAColor(0)));

	CEllipse ellipse({ 600, 150 }, 70, 70);
	ellipse.SetFillStyle(make_unique<CStyle>(true, CRGBAColor(0xffd724)));
	ellipse.SetOutlineStyle(make_unique<CLineStyle>(true, CRGBAColor(0xFF7924)));

	CTriangle triangle({ 100, 200 }, { 250, 100 }, { 400, 200 });
	triangle.SetFillStyle(make_unique<CStyle>(true, CRGBAColor(0x96260d)));
	triangle.SetOutlineStyle(make_unique<CLineStyle>(true, CRGBAColor(0)));

	rect.Draw(canvas);
	ellipse.Draw(canvas);
	triangle.Draw(canvas);

	canvas.EndDraw();

	ifs.close();
	return 0;
}

