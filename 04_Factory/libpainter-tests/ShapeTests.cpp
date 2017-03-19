#include "stdafx.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Ellipse.h"
#include "RegularPolygon.h"
#include "MockCanvas.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Point)
BOOST_AUTO_TEST_CASE(empty_constructor)
{
	auto point = SPoint();
	BOOST_CHECK_EQUAL(point.x, 0);
	BOOST_CHECK_EQUAL(point.y, 0);
}

BOOST_AUTO_TEST_CASE(valid_constructor)
{
	auto point = SPoint(10.0, 20.0);
	BOOST_CHECK_EQUAL(point.x, 10.0);
	BOOST_CHECK_EQUAL(point.y, 20.0);
}

BOOST_AUTO_TEST_CASE(assign_operator)
{
	auto point1 = SPoint(10.0, 20.0);
	auto point2 = point1;
	BOOST_CHECK_EQUAL(point2.x, 10.0);
	BOOST_CHECK_EQUAL(point2.y, 20.0);
}

BOOST_AUTO_TEST_CASE(compare_operator)
{
	auto point = SPoint(10.0, 20.0);
	auto pointEqual = SPoint(10.0, 20.0);
	BOOST_CHECK(point == pointEqual);

	auto pointDiffX = SPoint(10.1, 20.0);
	BOOST_CHECK(!(point == pointDiffX));

	auto pointDiffY = SPoint(10.0, 20.1);
	BOOST_CHECK(!(point == pointDiffY));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(Rectangle)
BOOST_AUTO_TEST_CASE(valid)
{
	auto rect = CRectangle(Color::Green, SPoint(10, 10), SPoint(20, 20));
	BOOST_CHECK(rect.GetColor() == Color::Green);
	BOOST_CHECK(rect.GetLeftTop() == SPoint(10, 10));
	BOOST_CHECK(rect.GetRightBottom() == SPoint(20, 20));
}

BOOST_AUTO_TEST_CASE(invalid)
{
	BOOST_CHECK_THROW(CRectangle(Color::Black, SPoint(10, 10), SPoint(10, 10)), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(draw)
{
	SPoint v1 = SPoint(10, 10);
	SPoint v3 = SPoint(20, 20);
	auto rect = CRectangle(Color::Green, v1, v3);
	auto canvas = CMockCanvas();
	rect.Draw(canvas);
	BOOST_CHECK(canvas.penColor == Color::Green);
	BOOST_CHECK_EQUAL(canvas.lines.size(), 4);
	BOOST_CHECK_EQUAL(canvas.ellipses.size(), 0);

	SPoint v2 = SPoint(20, 10);
	SPoint v4 = SPoint(10, 20);
	BOOST_CHECK(canvas.lines[0].from == v1);
	BOOST_CHECK(canvas.lines[0].to == v2);
	BOOST_CHECK(canvas.lines[1].from == v2);
	BOOST_CHECK(canvas.lines[1].to == v3);
	BOOST_CHECK(canvas.lines[2].from == v3);
	BOOST_CHECK(canvas.lines[2].to == v4);
	BOOST_CHECK(canvas.lines[3].from == v4);
	BOOST_CHECK(canvas.lines[3].to == v1);
}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(Triangle)
BOOST_AUTO_TEST_CASE(valid)
{
	auto triangle = CTriangle(Color::Red, SPoint(10, 10), SPoint(20, 20), SPoint(5, 15));
	BOOST_CHECK(triangle.GetColor() == Color::Red);
	BOOST_CHECK(triangle.GetVertex1() == SPoint(10, 10));
	BOOST_CHECK(triangle.GetVertex2() == SPoint(20, 20));
	BOOST_CHECK(triangle.GetVertex3() == SPoint(5, 15));
}

BOOST_AUTO_TEST_CASE(draw)
{
	SPoint v1 = SPoint(10, 10);
	SPoint v2 = SPoint(20, 20);
	SPoint v3 = SPoint(5, 15);
	auto triangle = CTriangle(Color::Red, v1, v2, v3);
	auto canvas = CMockCanvas();
	triangle.Draw(canvas);
	BOOST_CHECK(canvas.penColor == Color::Red);
	BOOST_CHECK_EQUAL(canvas.lines.size(), 3);
	BOOST_CHECK_EQUAL(canvas.ellipses.size(), 0);

	BOOST_CHECK(canvas.lines[0].from == v1);
	BOOST_CHECK(canvas.lines[0].to == v2);
	BOOST_CHECK(canvas.lines[1].from == v2);
	BOOST_CHECK(canvas.lines[1].to == v3);
	BOOST_CHECK(canvas.lines[2].from == v3);
	BOOST_CHECK(canvas.lines[2].to == v1);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Ellipse)
BOOST_AUTO_TEST_CASE(valid)
{
	auto ellipse = CEllipse(Color::Green, SPoint(0, 0), 10, 15);
	BOOST_CHECK(ellipse.GetColor() == Color::Green);
	BOOST_CHECK(ellipse.GetCenter() == SPoint(0, 0));
	BOOST_CHECK(ellipse.GetHRadius() == 10);
	BOOST_CHECK(ellipse.GetVRadius() == 15);
}

BOOST_AUTO_TEST_CASE(invalid)
{
	BOOST_CHECK_THROW(CEllipse(Color::Black, SPoint(10, 10), 0, 1), std::invalid_argument);
	BOOST_CHECK_THROW(CEllipse(Color::Black, SPoint(10, 10), 10, 0), std::invalid_argument);
	BOOST_CHECK_THROW(CEllipse(Color::Black, SPoint(10, 10), -5, 1), std::invalid_argument);
	BOOST_CHECK_THROW(CEllipse(Color::Black, SPoint(10, 10), 6, -1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(draw)
{
	auto ellipse = CEllipse(Color::Green, SPoint(10, 0), 10, 15);
	auto canvas = CMockCanvas();
	ellipse.Draw(canvas);
	BOOST_CHECK(canvas.penColor == Color::Green);
	BOOST_CHECK_EQUAL(canvas.lines.size(), 0);
	BOOST_CHECK_EQUAL(canvas.ellipses.size(), 1);

	BOOST_CHECK(canvas.ellipses[0].center == SPoint(10, 0));
	BOOST_CHECK(canvas.ellipses[0].hRadius == 10);
	BOOST_CHECK(canvas.ellipses[0].vRaduis == 15);
}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(RegularPolygon)
BOOST_AUTO_TEST_CASE(valid)
{
	auto regPol = CRegularPolygon(Color::Yellow, 5, SPoint(10, 10), 50);
	BOOST_CHECK(regPol.GetColor() == Color::Yellow);
	BOOST_CHECK(regPol.GetCenter() == SPoint(10, 10));
	BOOST_CHECK(regPol.GetVertexCount() == 5);
	BOOST_CHECK(regPol.GetRadius() == 50);
}

BOOST_AUTO_TEST_CASE(invalid)
{
	BOOST_CHECK_THROW(CRegularPolygon(Color::Yellow, 0, SPoint(10, 10), 50), std::invalid_argument);
	BOOST_CHECK_THROW(CRegularPolygon(Color::Yellow, 10, SPoint(10, 10), -50), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(draw)
{
	auto regPol = CRegularPolygon(Color::Yellow, 4, SPoint(0, 0), 10);
	auto canvas = CMockCanvas();
	regPol.Draw(canvas);
	BOOST_CHECK(canvas.penColor == Color::Yellow);
	BOOST_CHECK_EQUAL(canvas.lines.size(), 4);
	BOOST_CHECK_EQUAL(canvas.ellipses.size(), 0);

	SPoint v1 = SPoint(10, 0);
	SPoint v2 = SPoint(0, 10);
	SPoint v3 = SPoint(-10, 0);
	SPoint v4 = SPoint(0, -10);
	BOOST_CHECK(canvas.lines[0].from == v1);
	BOOST_CHECK(canvas.lines[0].to == v2);
	BOOST_CHECK(canvas.lines[1].from == v2);
	BOOST_CHECK(canvas.lines[1].to == v3);
	BOOST_CHECK(canvas.lines[2].from == v3);
	BOOST_CHECK(canvas.lines[2].to == v4);
	BOOST_CHECK(canvas.lines[3].from == v4);
	BOOST_CHECK(canvas.lines[3].to == v1);
}
BOOST_AUTO_TEST_SUITE_END()