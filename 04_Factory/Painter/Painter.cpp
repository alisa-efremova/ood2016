// Painter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Designer.h"
#include "ShapeFactory.h"
#include "Canvas.h"

using namespace std;

int main()
{

	//CDesigner designer;
	CShapeFactory factory = CShapeFactory();

	try
	{
		//factory.CreateShape("rectangle green 10 10 10 10");
		//factory.CreateShape("triangle red 0 0 1 1 2 2");
		//factory.CreateShape("ellipse yellow 0 0 10 20");
		auto shape = factory.CreateShape("regular_polygon red 4 0 0 2");
		CCanvas canvas(cout);
		shape->Draw(canvas);
	}
	catch (const exception & e)
	{
		cout << "Exception: " << e.what() << endl;
	}
	

	return 0;
}

