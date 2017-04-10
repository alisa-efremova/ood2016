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

	CRectangle rectNominal({ 0, 0 }, 100, 100);
	rectNominal.Draw(canvas);

	CRectangle rect({ 100, 210 }, 300, 200);
	rect.SetFillStyle(make_unique<CStyle>(true, CRGBAColor(0x94631e)));
	rect.SetOutlineStyle(make_unique<CLineStyle>(true, CRGBAColor(0)));
	rect.Draw(canvas);

	rect.SetFrame({100, 200, 400, 200});
	rect.SetFillStyle(make_unique<CStyle>(false));
	rect.Draw(canvas);

	CEllipse ellipse({ 600, 150 }, 70, 70);
	ellipse.SetFillStyle(make_unique<CStyle>(true, CRGBAColor(0xffd724)));
	ellipse.SetOutlineStyle(make_unique<CLineStyle>(true, CRGBAColor(0xFF7924)));
	ellipse.Draw(canvas);

	auto frameEllipse = ellipse.GetFrame();
	CRectangle rectEllipse({ frameEllipse.left, frameEllipse.top }, frameEllipse.width, frameEllipse.height);
	rectEllipse.Draw(canvas);

	ellipse.SetFrame({ frameEllipse.left-10, frameEllipse.top-10, 200, 140 });
	ellipse.SetFillStyle(make_unique<CStyle>(false));
	ellipse.Draw(canvas);

	CTriangle triangle({ 100, 200 }, { 250, 100 }, { 400, 200 });
	triangle.SetFillStyle(make_unique<CStyle>(true, CRGBAColor(0x96260d)));
	triangle.SetOutlineStyle(make_unique<CLineStyle>(true, CRGBAColor(0)));
	triangle.Draw(canvas);
	
#if 1
	auto frame = triangle.GetFrame();
	CRectangle firstFrame({ frame.left, frame.top }, frame.width, frame.height);
	firstFrame.SetOutlineStyle(make_unique<CLineStyle>(true, CRGBAColor(0x79ff61)));
	firstFrame.Draw(canvas);

	frame = { 50, 100, 400, 100 };
	CRectangle secondFrame({ frame.left, frame.top }, frame.width, frame.height);
	secondFrame.SetOutlineStyle(make_unique<CLineStyle>(true, CRGBAColor(0x2fba25)));
	secondFrame.Draw(canvas);

	triangle.SetFrame(frame);
	triangle.Draw(canvas);

#endif

	canvas.EndDraw();

	ifs.close();
	return 0;
}

