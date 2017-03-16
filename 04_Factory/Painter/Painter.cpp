// Painter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "ShapeFactory.h"


using namespace std;

int main()
{

	//CDesigner designer;
	CShapeFactory factory = CShapeFactory();
	factory.CreateShape("rectangle orange");

	return 0;
}

