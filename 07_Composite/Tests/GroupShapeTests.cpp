#include "stdafx.h"
#include "painter_lib\GroupShape.h"
#include "painter_lib\Rectangle.h"
#include "painter_lib\Triangle.h"
#include "painter_lib\Ellipse.h"
#include "painter_lib\LineStyle.h"
#include "painter_lib\Style.h"

using namespace std;

struct Group_shape_
{
	CGroupShape rootGroupShape;

	bool CompareFrames(const RectD & frame1, const RectD & frame2)
	{
		double maxDiff = 0.0001;
		return abs(frame1.left - frame2.left) < maxDiff &&
			abs(frame1.top - frame2.top) < maxDiff &&
			abs(frame1.width - frame2.width) < maxDiff &&
			abs(frame1.height - frame2.height) < maxDiff;
	}
};

BOOST_FIXTURE_TEST_SUITE(GroupShape, Group_shape_)

BOOST_AUTO_TEST_SUITE(by_default)
BOOST_AUTO_TEST_CASE(is_empty)
{
	BOOST_REQUIRE_EQUAL(rootGroupShape.GetShapesCount(), 0);
}
BOOST_AUTO_TEST_CASE(has_zero_frame)
{
	BOOST_REQUIRE(CompareFrames(rootGroupShape.GetFrame(), { 0, 0, 0, 0 }));
}
BOOST_AUTO_TEST_CASE(setting_frame_does_not_affect_anything)
{
	rootGroupShape.SetFrame({ 10, 10, 10, 10 });
	BOOST_REQUIRE(CompareFrames(rootGroupShape.GetFrame(), { 0, 0, 0, 0 }));
}
BOOST_AUTO_TEST_CASE(does_not_allow_to_get_or_remove_shape)
{
	BOOST_REQUIRE_THROW(rootGroupShape.GetShapeAtIndex(0), out_of_range);
	BOOST_REQUIRE_THROW(rootGroupShape.RemoveShapeAtIndex(0), out_of_range);
}
BOOST_AUTO_TEST_CASE(does_not_allow_to_get_styles)
{
	BOOST_REQUIRE_THROW(rootGroupShape.GetFillStyle(), runtime_error);
	BOOST_REQUIRE_THROW(rootGroupShape.GetOutlineStyle(), runtime_error);
}
BOOST_AUTO_TEST_SUITE_END()

struct after_adding_simple_shape_ : Group_shape_
{
	shared_ptr<IShape> sunShape = make_shared<CEllipse>(SPoint{ 450, 50 }, 50, 50);

	after_adding_simple_shape_()
	{
		rootGroupShape.InsertShape(sunShape);
	}
};

BOOST_FIXTURE_TEST_SUITE(after_adding_simple_shape, after_adding_simple_shape_)
BOOST_AUTO_TEST_CASE(has_one_simple_shape)
{
	BOOST_REQUIRE_EQUAL(rootGroupShape.GetShapesCount(), 1);
	BOOST_REQUIRE(rootGroupShape.GetShapeAtIndex(0)->GetGroup() == nullptr);
}
BOOST_AUTO_TEST_CASE(allow_removing_shape)
{
	BOOST_REQUIRE_NO_THROW(rootGroupShape.RemoveShapeAtIndex(0));
	BOOST_REQUIRE_EQUAL(rootGroupShape.GetShapesCount(), 0);
}
BOOST_AUTO_TEST_CASE(has_the_same_properties_as_simple_shape)
{
	BOOST_REQUIRE(CompareFrames(rootGroupShape.GetFrame(), sunShape->GetFrame()));
	BOOST_REQUIRE_EQUAL(rootGroupShape.GetFillStyle(), sunShape->GetFillStyle());
	BOOST_REQUIRE_EQUAL(rootGroupShape.GetOutlineStyle(), sunShape->GetOutlineStyle());
}
BOOST_AUTO_TEST_CASE(setting_frame_affects_child_frame)
{
	RectD newFrame{ 10, 20, 30, 40 };
	rootGroupShape.SetFrame(newFrame);
	BOOST_REQUIRE(CompareFrames(rootGroupShape.GetFrame(), newFrame));
	BOOST_REQUIRE(CompareFrames(sunShape->GetFrame(), newFrame));
}
BOOST_AUTO_TEST_CASE(changing_styles_affects_child_styles)
{
	auto fillStyle = make_shared<CStyle>(true, CRGBAColor());
	rootGroupShape.SetFillStyle(fillStyle);
	BOOST_REQUIRE_EQUAL(rootGroupShape.GetFillStyle(), fillStyle);
	BOOST_REQUIRE_EQUAL(sunShape->GetFillStyle(), fillStyle);

	auto outlineStyle = make_shared<CLineStyle>(true, CRGBAColor(), 1);
	rootGroupShape.SetOutlineStyle(outlineStyle);
	BOOST_REQUIRE_EQUAL(rootGroupShape.GetOutlineStyle(), outlineStyle);
	BOOST_REQUIRE_EQUAL(sunShape->GetOutlineStyle(), outlineStyle);
}
BOOST_AUTO_TEST_SUITE_END()

struct after_adding_simple_and_group_shape_ : after_adding_simple_shape_
{
	shared_ptr<IShape> rect = make_shared<CRectangle>(SPoint{ 0, 100 }, 300, 200);
	shared_ptr<IShape> triangle = make_shared<CTriangle>(SPoint{ 0, 100 }, SPoint{ 150, 0 }, SPoint{ 300, 100 });
	IGroupShapePtr houseGroupShape = make_shared<CGroupShape>();

	after_adding_simple_and_group_shape_()
	{
		houseGroupShape->InsertShape(rect);
		houseGroupShape->InsertShape(triangle);
		houseGroupShape->SetFillStyle(make_shared<CStyle>(true, CRGBAColor(0)));
		houseGroupShape->SetOutlineStyle(make_shared<CLineStyle>(true, CRGBAColor(0, 0.5)));
		rootGroupShape.InsertShape(houseGroupShape);
	}
};

BOOST_FIXTURE_TEST_SUITE(after_adding_simple_and_group_shape, after_adding_simple_and_group_shape_)
BOOST_AUTO_TEST_CASE(has_one_simple_shape_and_one_group_shape)
{
	BOOST_REQUIRE_EQUAL(rootGroupShape.GetShapesCount(), 2);
	BOOST_REQUIRE(rootGroupShape.GetShapeAtIndex(0)->GetGroup() == nullptr);
	BOOST_REQUIRE_EQUAL(rootGroupShape.GetShapeAtIndex(1)->GetGroup()->GetShapesCount(), houseGroupShape->GetShapesCount());
	BOOST_REQUIRE(CompareFrames(rootGroupShape.GetShapeAtIndex(1)->GetGroup()->GetFrame(), houseGroupShape->GetFrame()));
}
BOOST_AUTO_TEST_CASE(has_valid_frame)
{
	RectD expectedHouseFrame = { 0, 0, 300, 300 };
	RectD expectedSunFrame = { 400, 0, 100, 100 };
	RectD expectedRootGroupShapeFrame = { 0, 0, 500, 300 };

	BOOST_REQUIRE(CompareFrames(rootGroupShape.GetShapeAtIndex(0)->GetFrame(), expectedSunFrame));
	BOOST_REQUIRE(CompareFrames(rootGroupShape.GetShapeAtIndex(1)->GetFrame(), expectedHouseFrame));
	BOOST_REQUIRE(CompareFrames(rootGroupShape.GetFrame(), expectedRootGroupShapeFrame));
}
BOOST_AUTO_TEST_CASE(has_undefined_styles)
{
	BOOST_REQUIRE(rootGroupShape.GetFillStyle() == nullptr);
	BOOST_REQUIRE(rootGroupShape.GetOutlineStyle() == nullptr);
}
BOOST_AUTO_TEST_CASE(allow_removing_shape)
{
	BOOST_REQUIRE_NO_THROW(rootGroupShape.RemoveShapeAtIndex(1));
	BOOST_REQUIRE_EQUAL(rootGroupShape.GetShapesCount(), 1);
}
BOOST_AUTO_TEST_CASE(setting_frame_affects_children_frames)
{
	RectD newRootFrame = { 100, 200, 1500, 150 };
	RectD expectedSunFrame = { 1300, 200, 300, 50 };
	RectD expectedHouseFrame = { 100, 200, 900, 150 };

	rootGroupShape.SetFrame(newRootFrame);
	BOOST_REQUIRE(CompareFrames(rootGroupShape.GetFrame(), newRootFrame));
	BOOST_REQUIRE(CompareFrames(sunShape->GetFrame(), expectedSunFrame));
	BOOST_REQUIRE(CompareFrames(houseGroupShape->GetFrame(), expectedHouseFrame));
}
BOOST_AUTO_TEST_CASE(changing_styles_affects_children_styles)
{
	auto fillStyle = make_shared<CStyle>(true, CRGBAColor());
	rootGroupShape.SetFillStyle(fillStyle);
	BOOST_REQUIRE_EQUAL(rootGroupShape.GetFillStyle(), fillStyle);
	BOOST_REQUIRE_EQUAL(sunShape->GetFillStyle(), fillStyle);
	BOOST_REQUIRE_EQUAL(houseGroupShape->GetFillStyle(), fillStyle);

	auto outlineStyle = make_shared<CLineStyle>(true, CRGBAColor(), 1);
	rootGroupShape.SetOutlineStyle(outlineStyle);
	BOOST_REQUIRE_EQUAL(rootGroupShape.GetOutlineStyle(), outlineStyle);
	BOOST_REQUIRE_EQUAL(sunShape->GetOutlineStyle(), outlineStyle);
	BOOST_REQUIRE_EQUAL(houseGroupShape->GetOutlineStyle(), outlineStyle);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()