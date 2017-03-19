#include "stdafx.h"
#include "Designer.h"
#include "ShapeFactory.h"
#include "CanvasSVG.h"
#include "Painter.h"
#include "PictureDraft.h"
#include <fstream> 

using namespace std;

int main()
{
	cout << "Colors: green, red, blue, yellow, pink, black" << endl;
	cout << "Shapes:" << endl;
	cout << "rectangle color x1 y1 x2 y2" << endl;
	cout << "triangle color x1 y1 x2 y2 x3 y3" << endl;
	cout << "ellipse color x y hRadius vRadius" << endl;
	cout << "regular_polygon color vertexCount x y radius" << endl;
	cout << "---------------------------------------------" << endl;

	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);

	ifstream ifs("source.txt");
	if (!ifs.is_open())
	{
		cout << "Error while openning the input file." << endl;
		return 1;
	}
	CPictureDraft draft = designer.CreateDraft(ifs);
	
	ofstream ofs("result.svg", ofstream::out | ofstream::trunc);
	if (!ofs.is_open())
	{
		cout << "Error while openning the output file." << endl;
		return 1;
	}
	CCanvasSVG canvas(ofs);
	CPainter painter;
	painter.DrawPicture(draft, canvas);

	ofs.close();
	return 0;
}

