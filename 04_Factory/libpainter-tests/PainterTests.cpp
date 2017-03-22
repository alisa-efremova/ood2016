#include "stdafx.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Ellipse.h"
#include "RegularPolygon.h"
#include "PictureDraft.h"
#include "Painter.h"
#include "MockCanvas.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Painter)
BOOST_AUTO_TEST_CASE(empty_draft)
{
	auto draft = CPictureDraft();
	auto canvas = CMockCanvas();
	auto painter = CPainter();
	painter.DrawPicture(draft, canvas);
	BOOST_CHECK_EQUAL(canvas.lines.size(), 0);
	BOOST_CHECK_EQUAL(canvas.ellipses.size(), 0);
}

BOOST_AUTO_TEST_CASE(draft_with_single_shape)
{
	auto draft = CPictureDraft();
	draft.AddShape(make_unique<CRectangle>(Color::Blue, SPoint(0, 10), SPoint(20, 30)));
	auto canvas = CMockCanvas();
	auto painter = CPainter();
	painter.DrawPicture(draft, canvas);
	BOOST_CHECK_EQUAL(canvas.lines.size(), 4);
	BOOST_CHECK_EQUAL(canvas.ellipses.size(), 0);
}

BOOST_AUTO_TEST_CASE(draft_with_several_shapes)
{
	auto draft = CPictureDraft();
	draft.AddShape(make_unique<CRectangle>(Color::Blue, SPoint(0, 10), SPoint(20, 30)));
	draft.AddShape(make_unique<CTriangle>(Color::Red, SPoint(0, 0), SPoint(1, 1), SPoint(0, 1)));
	draft.AddShape(make_unique<CEllipse>(Color::Yellow, SPoint(10, 10), 10, 20));
	auto canvas = CMockCanvas();
	auto painter = CPainter();
	painter.DrawPicture(draft, canvas);
	BOOST_CHECK_EQUAL(canvas.lines.size(), 7);
	BOOST_CHECK_EQUAL(canvas.ellipses.size(), 1);
	BOOST_CHECK(canvas.lines[0].color == Color::Blue);
	BOOST_CHECK(canvas.lines[1].color == Color::Blue);
	BOOST_CHECK(canvas.lines[2].color == Color::Blue);
	BOOST_CHECK(canvas.lines[3].color == Color::Blue);
	BOOST_CHECK(canvas.lines[4].color == Color::Red);
	BOOST_CHECK(canvas.lines[5].color == Color::Red);
	BOOST_CHECK(canvas.lines[6].color == Color::Red);
	BOOST_CHECK(canvas.ellipses[0].color == Color::Yellow);
}

BOOST_AUTO_TEST_SUITE_END()