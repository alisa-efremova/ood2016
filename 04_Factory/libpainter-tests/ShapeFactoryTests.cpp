#include "stdafx.h"
#include "ShapeFactory.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Ellipse.h"
#include "RegularPolygon.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Shape_Factory)

BOOST_AUTO_TEST_CASE(Create_shape_with_uknown_type)
{
	auto shapeFactory = CShapeFactory();
	BOOST_CHECK_THROW(shapeFactory.CreateShape("line blue 10 15 100"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(Create_shape_with_uknown_color)
{
	auto shapeFactory = CShapeFactory();
	BOOST_CHECK_THROW(shapeFactory.CreateShape("rectangle orange 10 15 100 200"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(Create_valid_rectangle)
{
	auto shapeFactory = CShapeFactory();
	auto shapePtr = shapeFactory.CreateShape("rectangle blue 10 15 100 200");
	CRectangle * rectPtr = dynamic_cast<CRectangle *>(shapePtr.get());
	BOOST_CHECK(rectPtr->GetColor() == Color::Blue);
	BOOST_CHECK(rectPtr->GetLeftTop() == SPoint(10, 15));
	BOOST_CHECK(rectPtr->GetRightBottom() == SPoint(100, 200));
}

BOOST_AUTO_TEST_CASE(Create_invalid_rectangle)
{
	auto shapeFactory = CShapeFactory();
	BOOST_CHECK_THROW(shapeFactory.CreateShape("rectangle blue 10 15 100"), std::runtime_error);
	BOOST_CHECK_THROW(shapeFactory.CreateShape("rectangle 10 15 100 1000"), std::runtime_error);
	BOOST_CHECK_THROW(shapeFactory.CreateShape("rectangle blue 10 15 10 15"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(Create_valid_triangle)
{
	auto shapeFactory = CShapeFactory();
	auto shapePtr = shapeFactory.CreateShape("triangle green 1 2 3 4 5 6");
	CTriangle * trianglePtr = dynamic_cast<CTriangle *>(shapePtr.get());
	BOOST_CHECK(trianglePtr->GetColor() == Color::Green);
	BOOST_CHECK(trianglePtr->GetVertex1() == SPoint(1, 2));
	BOOST_CHECK(trianglePtr->GetVertex2() == SPoint(3, 4));
	BOOST_CHECK(trianglePtr->GetVertex3() == SPoint(5, 6));
}

BOOST_AUTO_TEST_CASE(Create_invalid_triangle)
{
	auto shapeFactory = CShapeFactory();
	BOOST_CHECK_THROW(shapeFactory.CreateShape("triangle green 1 2 3 4 5"), std::runtime_error);
	BOOST_CHECK_THROW(shapeFactory.CreateShape("triangle 1 2 3 4 5 6"), std::runtime_error);
}


BOOST_AUTO_TEST_CASE(Create_valid_ellipse)
{
	auto shapeFactory = CShapeFactory();
	auto shapePtr = shapeFactory.CreateShape("ellipse pink 1 2 10 20");
	CEllipse * ellipsePtr = dynamic_cast<CEllipse *>(shapePtr.get());
	BOOST_CHECK(ellipsePtr->GetColor() == Color::Pink);
	BOOST_CHECK(ellipsePtr->GetCenter() == SPoint(1, 2));
	BOOST_CHECK(ellipsePtr->GetHRadius() == 10);
	BOOST_CHECK(ellipsePtr->GetVRadius() == 20);
}

BOOST_AUTO_TEST_CASE(Create_invalid_ellipse)
{
	auto shapeFactory = CShapeFactory();
	BOOST_CHECK_THROW(shapeFactory.CreateShape("ellipse pink 1 2 3"), std::runtime_error);
	BOOST_CHECK_THROW(shapeFactory.CreateShape("ellipse 1 2 3 4"), std::runtime_error);
	BOOST_CHECK_THROW(shapeFactory.CreateShape("ellipse 1 2 -10 4"), std::runtime_error);
	BOOST_CHECK_THROW(shapeFactory.CreateShape("ellipse 1 2 3 0"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(Create_valid_regular_poligon)
{
	auto shapeFactory = CShapeFactory();
	auto shapePtr = shapeFactory.CreateShape("regular_polygon red 4 0 1 20");
	CRegularPolygon * regPolPtr = dynamic_cast<CRegularPolygon *>(shapePtr.get());
	BOOST_CHECK(regPolPtr->GetColor() == Color::Red);
	BOOST_CHECK(regPolPtr->GetCenter() == SPoint(0, 1));
	BOOST_CHECK(regPolPtr->GetVertexCount() == 4);
	BOOST_CHECK(regPolPtr->GetRadius() == 20);
}

BOOST_AUTO_TEST_CASE(Create_regular_poligon)
{
	auto shapeFactory = CShapeFactory();
	BOOST_CHECK_THROW(shapeFactory.CreateShape("regular_polygon red 1 2 3"), std::runtime_error);
	BOOST_CHECK_THROW(shapeFactory.CreateShape("regular_popygon red 1.1 2 3 10"), std::runtime_error);
	BOOST_CHECK_THROW(shapeFactory.CreateShape("regular_popygon red 1 2 3 -5"), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()