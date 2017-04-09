#include "stdafx.h"
#include "Painter\ModernCanvasClassAdapter.h"
#include "modern_graphics_lib\ModernGraphicsRenderer.h"
#include "shape_drawing_lib\Triangle.h"
#include "shape_drawing_lib\Rectangle.h"

using boost::test_tools::output_test_stream;

using namespace std;

namespace ClassAdapter
{

struct Renderer_adapter_
{
	output_test_stream outStream;
	app::CModernCanvasClassAdapter canvas = app::CModernCanvasClassAdapter(outStream);

	struct SPoint
	{
		int x, y;
	};

	struct SRGBA
	{
		float r, g, b, a;
	};

	string GetRenderedLine(SPoint p1, SPoint p2, SRGBA color = { 0, 0, 0, 1 })
	{
		stringstream ss;
		ss << boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%">)") % p1.x % p1.y % p2.x % p2.y << endl;
		ss << boost::format(R"(    <color r="%1$.3f" g="%2$.3f" b="%3$.3f" a="%4$.3f" />)") % color.r % color.g % color.b % color.a << endl;
		ss << "  </line>" << endl;
		return ss.str();
	}
};

BOOST_FIXTURE_TEST_SUITE(ModernCanvasClassAdapter, Renderer_adapter_)

	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_REQUIRE(outStream.is_empty());
		}
		BOOST_AUTO_TEST_CASE(line_cannot_be_drawn_until_BeginDraw_is_invoked)
		{
			BOOST_REQUIRE_THROW(canvas.LineTo(0, 0), logic_error);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct after_begin_drawing_ : Renderer_adapter_
	{
		after_begin_drawing_()
		{
			canvas.BeginDraw();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(after_begin_drawing, after_begin_drawing_)
		BOOST_AUTO_TEST_CASE(draw_tag_is_printed)
		{
			BOOST_REQUIRE(outStream.is_equal("<draw>\n"));
		}
		BOOST_AUTO_TEST_CASE(line_can_be_drawn)
		{
			BOOST_REQUIRE_NO_THROW(canvas.LineTo(0, 0));
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct after_end_drawing_ : after_begin_drawing_
	{
		after_end_drawing_()
		{
			outStream.flush();
			canvas.EndDraw();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(after_end_drawing, after_end_drawing_)
		BOOST_AUTO_TEST_CASE(closing_draw_tag_is_printed)
		{
			BOOST_REQUIRE(outStream.is_equal("</draw>\n"));
		}
		BOOST_AUTO_TEST_CASE(line_cannot_be_drawn_anymore)
		{
			BOOST_REQUIRE_THROW(canvas.LineTo(0, 0), logic_error);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct when_ready_to_draw_ : Renderer_adapter_
	{
		when_ready_to_draw_()
		{
			canvas.BeginDraw();
			outStream.flush();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_ready_to_draw, when_ready_to_draw_)

		BOOST_AUTO_TEST_CASE(can_draw_lines_and_move_to_specified_point)
		{
			// line without command move to
			canvas.LineTo(2, 2);
			BOOST_REQUIRE(outStream.is_equal(GetRenderedLine({ 0, 0 }, { 2, 2 })));

			canvas.MoveTo(3, 1);
			BOOST_REQUIRE(outStream.is_empty());

			canvas.LineTo(4, 0);
			BOOST_REQUIRE(outStream.is_equal(GetRenderedLine({ 3, 1 }, { 4, 0 })));

			canvas.LineTo(10, 20);
			BOOST_REQUIRE(outStream.is_equal(GetRenderedLine({ 4, 0 }, { 10, 20 })));
		}

		BOOST_AUTO_TEST_CASE(can_set_and_change_color_dynamically)
		{
			canvas.SetColor(0);
			BOOST_REQUIRE(outStream.is_empty());
			canvas.LineTo(1, 1);
			BOOST_REQUIRE(outStream.is_equal(GetRenderedLine({ 0, 0 }, { 1, 1 }, { 0, 0, 0, 1 })));

			canvas.SetColor(0xFF10AB);
			canvas.LineTo(2, 2);
			BOOST_REQUIRE(outStream.is_equal(GetRenderedLine({ 1, 1 }, { 2, 2 }, { 1, 0.063f, 0.671f, 1 })));

			canvas.SetColor(0xFFFFFF);
			canvas.LineTo(3, 3);
			BOOST_REQUIRE(outStream.is_equal(GetRenderedLine({ 2, 2 }, { 3, 3 }, { 1, 1, 1, 1 })));
		}

		BOOST_AUTO_TEST_CASE(triangle_can_be_drawn_on_canvas)
		{
			shape_drawing_lib::CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0xE3B71A);
			triangle.Draw(canvas);
			SRGBA color = { 0.89f, 0.718f, 0.102f, 1 };
			string expectedString = GetRenderedLine({ 10, 15 }, { 100, 200 }, color) +
				GetRenderedLine({ 100, 200 }, { 150, 250 }, color) +
				GetRenderedLine({ 150, 250 }, { 10, 15 }, color);
			BOOST_REQUIRE(outStream.is_equal(expectedString));
		}

		BOOST_AUTO_TEST_CASE(rectangle_can_be_drawn_on_canvas)
		{
			shape_drawing_lib::CRectangle rectangle({ 10, 20 }, 100, 50, 0xE3B71A);
			rectangle.Draw(canvas);
			SRGBA color = { 0.89f, 0.718f, 0.102f, 1 };
			string expectedString = GetRenderedLine({ 10, 20 }, { 110, 20 }, color) +
				GetRenderedLine({ 110, 20 }, { 110, 70 }, color) +
				GetRenderedLine({ 110, 70 }, { 10, 70 }, color) +
				GetRenderedLine({ 10, 70 }, { 10, 20 }, color);
			BOOST_REQUIRE(outStream.is_equal(expectedString));
		}

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
}