#include "stdafx.h"
#include "CanvasSVG.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "LineStyle.h"
#include "Style.h"
#include "GroupShape.h"
#include <fstream>

using namespace std;

int main()
{
	try 
	{
		ofstream ifs("../result.svg");
		if (!ifs.is_open())
		{
			cout << "Error while openning the file." << endl;
			return 1;
		}

		CCanvasSVG canvas(ifs);
		canvas.BeginDraw();
#if 0
		CRectangle rectNominal({ 0, 0 }, 100, 100);
		rectNominal.Draw(canvas);
#endif
		CRectangle rect({ 100, 210 }, 300, 200);
		rect.SetFillStyle(make_shared<CStyle>(true, CRGBAColor(0x94631e)));
		rect.SetOutlineStyle(make_shared<CLineStyle>(true, CRGBAColor(0)));
		//rect.Draw(canvas);
#if 0
		rect.SetFrame({ 100, 200, 400, 200 });
		rect.SetFillStyle(make_shared<CStyle>(false));
		rect.Draw(canvas);

		CEllipse ellipse({ 600, 150 }, 70, 70);
		ellipse.SetFillStyle(make_shared<CStyle>(true, CRGBAColor(0xffd724)));
		ellipse.SetOutlineStyle(make_shared<CLineStyle>(true, CRGBAColor(0xFF7924)));
		ellipse.Draw(canvas);

		auto frameEllipse = ellipse.GetFrame();
		CRectangle rectEllipse({ frameEllipse.left, frameEllipse.top }, frameEllipse.width, frameEllipse.height);
		rectEllipse.Draw(canvas);

		ellipse.SetFrame({ frameEllipse.left - 10, frameEllipse.top - 10, 200, 140 });
		ellipse.SetFillStyle(make_shared<CStyle>(false));
		ellipse.Draw(canvas);
#endif
		CTriangle triangle({ 100, 200 }, { 250, 100 }, { 400, 200 });
		triangle.SetFillStyle(make_shared<CStyle>(true, CRGBAColor(0x96260d)));
		triangle.SetOutlineStyle(make_shared<CLineStyle>(true, CRGBAColor(0)));
		//triangle.Draw(canvas);

#if 1
		auto frame = triangle.GetFrame();
		CRectangle firstFrame({ frame.left, frame.top }, frame.width, frame.height);
		firstFrame.SetOutlineStyle(make_shared<CLineStyle>(true, CRGBAColor(0x79ff61)));
		//firstFrame.Draw(canvas);

		frame = { 50, 100, 400, 100 };
		CRectangle secondFrame({ frame.left, frame.top }, frame.width, frame.height);
		secondFrame.SetOutlineStyle(make_shared<CLineStyle>(true, CRGBAColor(0x2fba25)));
		//secondFrame.Draw(canvas);

		triangle.SetFrame(frame);
		//triangle.Draw(canvas);

#endif

		CGroupShape group;
		group.InsertShape(shared_ptr<CRectangle>(&rect), 0);
		group.InsertShape(shared_ptr<CTriangle>(&triangle), 1);
		group.Draw(canvas);

		frame = group.GetFrame();

		CRectangle groupFrame({ frame.left, frame.top }, frame.width, frame.height);
		groupFrame.SetOutlineStyle(make_shared<CLineStyle>(true, CRGBAColor(0xff2b0f)));
		groupFrame.Draw(canvas);

		frame.left += 500;
		frame.width *= 1.5;
		frame.height *= 0.3;
		frame.top -= 10;
		groupFrame.SetFrame(frame);
		groupFrame.Draw(canvas);

		group.SetFrame(frame);
		group.Draw(canvas);

		canvas.EndDraw();

		ifs.close();
	}
	catch (exception & e)
	{
		cout << "Error: " << e.what() << endl;
	}
	return 0;
}

