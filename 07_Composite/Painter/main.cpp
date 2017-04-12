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

		CRectangle rect({ 100, 210 }, 300, 200);
		auto fillStyle = make_shared<CStyle>(true, CRGBAColor(0x94631e));
		rect.SetFillStyle(fillStyle);
		rect.SetOutlineStyle(make_shared<CLineStyle>(true, CRGBAColor(0)));

#if 0
		CEllipse ellipse({ 600, 150 }, 70, 70);
		ellipse.SetFillStyle(make_shared<CStyle>(true, CRGBAColor(0xffd724)));
		ellipse.SetOutlineStyle(make_shared<CLineStyle>(true, CRGBAColor(0xFF7924)));
		ellipse.Draw(canvas);
#endif

		CTriangle triangle({ 100, 200 }, { 250, 100 }, { 400, 200 });
		triangle.SetFillStyle(make_shared<CStyle>(true, CRGBAColor(0x96260d)));
		triangle.SetOutlineStyle(make_shared<CLineStyle>(true, CRGBAColor(0)));
		triangle.SetFrame({ 50, 100, 400, 100 });

		CGroupShape group;
		group.InsertShape(shared_ptr<CRectangle>(&rect));
		group.InsertShape(shared_ptr<CTriangle>(&triangle));
		group.Draw(canvas);

		auto frame = group.GetFrame();

		CRectangle groupFrame({ 0, 0 }, 0, 0);
		groupFrame.SetFrame(frame);
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

