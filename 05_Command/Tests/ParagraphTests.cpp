#include "stdafx.h"
#include "Paragraph.h"
#include "History.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ParagraphTests)

BOOST_AUTO_TEST_CASE(TestConstructor)
{
	CHistory history;
	CParagraph paragraph("", history);
	BOOST_REQUIRE_EQUAL(paragraph.GetText(), "");
	BOOST_REQUIRE(!history.CanRedo());
	BOOST_REQUIRE(!history.CanUndo());
}

BOOST_AUTO_TEST_CASE(TestSettingText)
{
	CHistory history;
	CParagraph paragraph("", history);
	paragraph.SetText("alice");
	BOOST_REQUIRE_EQUAL(paragraph.GetText(), "alice");
	BOOST_REQUIRE(history.CanUndo());
	BOOST_REQUIRE(!history.CanRedo());

	paragraph.SetText("bob");
	BOOST_REQUIRE_EQUAL(paragraph.GetText(), "bob");

	history.Undo();
	BOOST_REQUIRE_EQUAL(paragraph.GetText(), "alice");

	history.Undo();
	BOOST_REQUIRE_EQUAL(paragraph.GetText(), "");
	BOOST_REQUIRE(!history.CanUndo());
	BOOST_REQUIRE(history.CanRedo());

	history.Redo();
	BOOST_REQUIRE_EQUAL(paragraph.GetText(), "alice");

	history.Redo();
	BOOST_REQUIRE_EQUAL(paragraph.GetText(), "bob");
	BOOST_REQUIRE(!history.CanRedo());
}

BOOST_AUTO_TEST_SUITE_END()