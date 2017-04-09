#include "stdafx.h"
#include "CanvasSVG.h"
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

	canvas.SetLineColor(0xFF2398);
	canvas.SetLineWidth(2);
	canvas.MoveTo(100, 100);
	canvas.LineTo(200, 300);
	canvas.LineTo(50, 300);
	canvas.LineTo(100, 100);
	canvas.BeginFill(0xFF0034);
	canvas.MoveTo(400, 100);
	canvas.LineTo(400, 200);
	canvas.LineTo(500, 200);
	canvas.LineTo(500, 100);
	canvas.DrawEllipse(100, 300, 10, 20);
	canvas.EndFill();
	canvas.EndDraw();

	ifs.close();
	return 0;
}

