#include "stdafx.h"
#include "CanvasSVG.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "LineStyle.h"
#include "Style.h"
#include "Slide.h"
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

		CSlide slide;

		CCanvasSVG canvas(ifs);
		canvas.BeginDraw();

		// add house as group
		auto houseBlock = make_shared<CRectangle>( SPoint{ 100, 310 }, 300, 200);
		houseBlock->SetFillStyle(make_shared<CStyle>(true, CRGBAColor(0x94631e)));
		houseBlock->SetOutlineStyle(make_shared<CLineStyle>(true, CRGBAColor(0)));

		auto roof = make_shared<CTriangle>( SPoint{ 100, 300 }, SPoint{ 250, 200 }, SPoint{ 400, 300 });
		roof->SetFillStyle(make_shared<CStyle>(true, CRGBAColor(0x96260d)));
		roof->SetOutlineStyle(make_shared<CLineStyle>(true, CRGBAColor(0)));
		roof->SetFrame({ 50, 200, 400, 100 });

		auto house = make_shared<CGroupShape>();
		house->InsertShape(houseBlock);
		house->InsertShape(roof);
		slide.GetShapes().InsertShape(house);

		slide.Draw(canvas);

		// add sun
		auto sun = make_shared<CEllipse>(SPoint{ 100, 100 }, 70, 70);
		sun->SetFillStyle(make_shared<CStyle>(true, CRGBAColor(0xffd724)));
		sun->SetOutlineStyle(make_shared<CLineStyle>(true, CRGBAColor(0xFF7924)));
		slide.GetShapes().InsertShape(sun);

		// demonstrate frame changes for group
		auto frame = house->GetFrame();

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

		house->SetFrame(frame);

		slide.Draw(canvas);

		canvas.EndDraw();
		ifs.close();
	}
	catch (exception & e)
	{
		cout << "Error: " << e.what() << endl;
	}
	return 0;
}

