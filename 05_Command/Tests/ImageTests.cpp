#include "stdafx.h"
#include "Image.h"
#include "History.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ImageTests)

BOOST_AUTO_TEST_CASE(TestConstructor)
{
	CHistory history;
	CImage image(fs::path("images/1.png"), 10, 20, history);
	BOOST_REQUIRE_EQUAL(image.GetPath(), fs::path("images/1.png"));
	BOOST_REQUIRE_EQUAL(image.GetWidth(), 10);
	BOOST_REQUIRE_EQUAL(image.GetHeight(), 20);
	BOOST_REQUIRE(!history.CanRedo());
	BOOST_REQUIRE(!history.CanUndo());
}

BOOST_AUTO_TEST_CASE(TestConstructionWithInvalidPath)
{
	CHistory history;
	BOOST_REQUIRE_THROW(CImage image(fs::path("images"), 10, 20, history), invalid_argument);
	BOOST_REQUIRE_THROW(CImage image(fs::path("/"), 10, 20, history), invalid_argument);
	BOOST_REQUIRE_THROW(CImage image(fs::path("fake_path.png"), 10, 20, history), invalid_argument);
}

BOOST_AUTO_TEST_CASE(TestResizing)
{
	CHistory history;
	CImage image(fs::path("images/1.png"), 10, 20, history);

	image.Resize(5, 6);
	BOOST_REQUIRE_EQUAL(image.GetWidth(), 5);
	BOOST_REQUIRE_EQUAL(image.GetHeight(), 6);
	BOOST_REQUIRE(history.CanUndo());
	BOOST_REQUIRE(!history.CanRedo());

	image.Resize(0, 0);
	BOOST_REQUIRE_EQUAL(image.GetWidth(), 0);
	BOOST_REQUIRE_EQUAL(image.GetHeight(), 0);

	history.Undo();
	BOOST_REQUIRE_EQUAL(image.GetWidth(), 5);
	BOOST_REQUIRE_EQUAL(image.GetHeight(), 6);

	history.Undo();
	BOOST_REQUIRE_EQUAL(image.GetWidth(), 10);
	BOOST_REQUIRE_EQUAL(image.GetHeight(), 20);
	BOOST_REQUIRE(!history.CanUndo());
	BOOST_REQUIRE(history.CanRedo());

	history.Redo();
	BOOST_REQUIRE_EQUAL(image.GetWidth(), 5);
	BOOST_REQUIRE_EQUAL(image.GetHeight(), 6);

	history.Redo();
	BOOST_REQUIRE_EQUAL(image.GetWidth(), 0);
	BOOST_REQUIRE_EQUAL(image.GetHeight(), 0);
	BOOST_REQUIRE(!history.CanRedo());
}

BOOST_AUTO_TEST_SUITE_END()