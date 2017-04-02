#include "stdafx.h"
#include "Document.h"
#include "DocumentItem.h"

using namespace std;

struct Document_
{
	void CheckParagraphItems(const CDocument & document, const vector<string> & items)
	{
		BOOST_REQUIRE_EQUAL(document.GetItemsCount(), items.size());
		for (int i = 0; i < items.size(); i++)
		{
			BOOST_REQUIRE_EQUAL(document.GetItem(i).GetParagraph()->GetText(), items[i]);
		}
	}

	struct SImageInfo
	{
		string name;
		unsigned width;
		unsigned height;
	};

	void CheckImageItems(const CDocument & document, const vector<SImageInfo> & items)
	{
		BOOST_REQUIRE_EQUAL(document.GetItemsCount(), items.size());
		for (int i = 0; i < items.size(); i++)
		{
			BOOST_REQUIRE_EQUAL(document.GetItem(i).GetImage()->GetName(), items[i].name);
			BOOST_REQUIRE_EQUAL(document.GetItem(i).GetImage()->GetWidth(), items[i].width);
			BOOST_REQUIRE_EQUAL(document.GetItem(i).GetImage()->GetHeight(), items[i].height);
		}
	}
};

BOOST_FIXTURE_TEST_SUITE(DocumentTests, Document_)

BOOST_AUTO_TEST_CASE(TestConstructor)
{
	CDocument document;
	BOOST_REQUIRE_EQUAL(document.GetTitle(), "");
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 0);
	BOOST_REQUIRE(!document.CanRedo());
	BOOST_REQUIRE(!document.CanUndo());
}

BOOST_AUTO_TEST_CASE(TestSettingTitle)
{
	CDocument document;
	document.SetTitle("");
	BOOST_REQUIRE_EQUAL(document.GetTitle(), "");

	document.SetTitle("title");
	BOOST_REQUIRE_EQUAL(document.GetTitle(), "title");

	document.SetTitle("multi\nline");
	BOOST_REQUIRE_EQUAL(document.GetTitle(), "multi\nline");
}

BOOST_AUTO_TEST_CASE(TestAddingParagraph)
{
	CDocument document;

	// empty paragraph
	document.InsertParagraph("");
	CheckParagraphItems(document, { "" });

	// not empty paragraph insertion at the end
	document.InsertParagraph("alice");
	CheckParagraphItems(document, { "", "alice" });

	// insertion at first position
	document.InsertParagraph("bob", 0);
	CheckParagraphItems(document, { "bob", "", "alice" });

	// insertion at last position
	document.InsertParagraph("last", 3);
	CheckParagraphItems(document, { "bob", "", "alice", "last" });

	// insertion at middle position
	document.InsertParagraph("middle", 2);
	CheckParagraphItems(document, { "bob", "", "middle", "alice", "last" });

	// invalid position
	BOOST_REQUIRE_THROW(document.InsertParagraph("invalid", 10), out_of_range);
	CheckParagraphItems(document, { "bob", "", "middle", "alice", "last" });
}

BOOST_AUTO_TEST_CASE(TestDeletingParagraph)
{
	CDocument document;

	BOOST_REQUIRE_THROW(document.DeleteItem(0), out_of_range);

	// single paragraph deletion
	document.InsertParagraph("");
	BOOST_REQUIRE_THROW(document.GetItem(1), out_of_range);
	BOOST_REQUIRE_NO_THROW(document.DeleteItem(0));
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 0);

	// deletion of the first paragraph
	document.InsertParagraph("first");
	document.InsertParagraph("second");
	BOOST_REQUIRE_THROW(document.GetItem(2), out_of_range);
	BOOST_REQUIRE_NO_THROW(document.DeleteItem(0));
	CheckParagraphItems(document, { "second" });

	// deletion of the paragraph in the middle of the list
	document.InsertParagraph("alice");
	document.InsertParagraph("bob");
	BOOST_REQUIRE_NO_THROW(document.DeleteItem(1));
	CheckParagraphItems(document, { "second", "bob" });

	// invalid position
	BOOST_REQUIRE_THROW(document.DeleteItem(5), out_of_range);
	CheckParagraphItems(document, { "second", "bob" });
}

BOOST_AUTO_TEST_CASE(TestSettingTitleUndoRedo)
{
	CDocument document;
	BOOST_REQUIRE(!document.CanRedo());
	BOOST_REQUIRE(!document.CanUndo());

	document.SetTitle("title");
	BOOST_REQUIRE(!document.CanRedo());
	BOOST_REQUIRE(document.CanUndo());

	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetTitle(), "");
	BOOST_REQUIRE(!document.CanUndo());
	BOOST_REQUIRE(document.CanRedo());

	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetTitle(), "title");

	// undo and rewrite
	document.Undo();
	document.SetTitle("new title");
	BOOST_REQUIRE(!document.CanRedo());
	BOOST_REQUIRE_EQUAL(document.GetTitle(), "new title");

	document.SetTitle("the newest title");
	BOOST_REQUIRE_EQUAL(document.GetTitle(), "the newest title");

	// check stack
	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetTitle(), "new title");

	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetTitle(), "");
}

BOOST_AUTO_TEST_CASE(TestInsertingParagraphUndoRedo)
{
	CDocument document;

	// no history for invalid input
	BOOST_REQUIRE_THROW(document.InsertParagraph("invalid", 10), out_of_range);
	BOOST_REQUIRE(!document.CanUndo());

	// single paragraph
	document.InsertParagraph("first");
	BOOST_REQUIRE(document.CanUndo());
	document.Undo();
	CheckParagraphItems(document, {});

	document.Redo();
	CheckParagraphItems(document, { "first" });

	// multiple paragraphs
	document.InsertParagraph("third", 1);
	document.InsertParagraph("second", 1);
	CheckParagraphItems(document, { "first", "second", "third" });

	document.Undo();
	CheckParagraphItems(document, { "first", "third" });

	document.Undo();
	CheckParagraphItems(document, { "first" });

	document.Redo();
	CheckParagraphItems(document, { "first", "third" });

	document.Redo();
	CheckParagraphItems(document, { "first", "second", "third" });

	BOOST_REQUIRE(!document.CanRedo());
}

BOOST_AUTO_TEST_CASE(TestDeletingParagraphUndoRedo)
{
	CDocument document;

	// no history for invalid input
	BOOST_REQUIRE_THROW(document.DeleteItem(10), out_of_range);
	BOOST_REQUIRE(!document.CanUndo());

	// single paragraph
	document.InsertParagraph("first");
	document.DeleteItem(0);
	CheckParagraphItems(document, {});

	document.Undo();
	CheckParagraphItems(document, { "first" });

	// multiple actions
	document.InsertParagraph("second");
	document.InsertParagraph("third");
	CheckParagraphItems(document, { "first", "second", "third" });

	// delete item in the middle - second
	document.DeleteItem(1);
	CheckParagraphItems(document, { "first", "third" });

	// delete first item - first
	document.DeleteItem(0);
	CheckParagraphItems(document, { "third" });

	document.Undo();
	CheckParagraphItems(document, { "first", "third" });

	document.Undo();
	CheckParagraphItems(document, { "first", "second", "third" });

	document.Redo();
	CheckParagraphItems(document, { "first", "third" });

	document.Redo();
	CheckParagraphItems(document, { "third" });
}

BOOST_AUTO_TEST_CASE(TestReplacingTextUndoRedo)
{
	CDocument document;

	document.InsertParagraph("text");
	document.GetItem(0).GetParagraph()->SetText("new text");
	CheckParagraphItems(document, { "new text" });

	document.DeleteItem(0);
	document.InsertParagraph("other text");
	CheckParagraphItems(document, { "other text" });

	document.Undo();
	CheckParagraphItems(document, {});

	document.Undo();
	CheckParagraphItems(document, { "new text" });

	document.Undo();
	CheckParagraphItems(document, { "text" });

	document.Undo();
	CheckParagraphItems(document, {});

	document.Redo();
	CheckParagraphItems(document, { "text" });

	document.Redo();
	CheckParagraphItems(document, { "new text" });

	document.Redo();
	CheckParagraphItems(document, {});

	document.Redo();
	CheckParagraphItems(document, { "other text" });
	BOOST_REQUIRE(!document.CanRedo());
}

BOOST_AUTO_TEST_CASE(TestAddingImage)
{
	CDocument document;

	// invalid path
	BOOST_REQUIRE_THROW(document.InsertImage(fs::path("not_existing_item"), 100, 100), invalid_argument);
	// not existing path
	BOOST_REQUIRE_THROW(document.InsertImage(fs::path("not_existing_item.png"), 100, 100), invalid_argument);
	CheckImageItems(document, {});

	// provide valid path for image
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/1.png"), 0, 0));
	CheckImageItems(document, { { "1.png", 0, 0 } });

	// insertion at last position
	document.InsertImage(fs::path("images/2.png"), 10, 20, 1);
	CheckImageItems(document, { { "1.png", 0, 0 }, { "2.png", 10, 20 } });

	// insertion at middle position
	document.InsertImage(fs::path("images/3.png"), 30, 40, 1);
	CheckImageItems(document, { { "1.png", 0, 0 }, { "3.png", 30, 40 }, { "2.png", 10, 20 } });

	// invalid position
	BOOST_REQUIRE_THROW(document.InsertImage(fs::path("images/3.png"), 0, 0, 10), out_of_range);
	CheckImageItems(document, { { "1.png", 0, 0 }, { "3.png", 30, 40 }, { "2.png", 10, 20 } });
}

BOOST_AUTO_TEST_CASE(TestDeletingImage)
{
	CDocument document;

	// single image deletion
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/1.png"), 10, 20));
	BOOST_REQUIRE_THROW(document.GetItem(1), out_of_range);
	BOOST_REQUIRE_NO_THROW(document.DeleteItem(0));
	CheckImageItems(document, {});

	// deletion of the first image
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/1.png"), 10, 20));
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/2.png"), 30, 40));
	CheckImageItems(document, { { "1.png", 10, 20 }, { "2.png", 30, 40 } });

	BOOST_REQUIRE_NO_THROW(document.DeleteItem(0));
	CheckImageItems(document, { { "2.png", 30, 40 } });

	// deletion of the image in the middle of the list
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/1.png"), 30, 40));
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/3.png"), 50, 60));
	CheckImageItems(document, { { "2.png", 30, 40 }, { "1.png", 30, 40 }, { "3.png", 50, 60 } });

	BOOST_REQUIRE_NO_THROW(document.DeleteItem(1));
	CheckImageItems(document, { { "2.png", 30, 40 }, { "3.png", 50, 60 } });

	// invalid position
	BOOST_REQUIRE_THROW(document.DeleteItem(2), out_of_range);
	CheckImageItems(document, { { "2.png", 30, 40 }, { "3.png", 50, 60 } });
}

BOOST_AUTO_TEST_CASE(TestInsertingImageUndoRedo)
{
	CDocument document;

	// no history for invalid input
	BOOST_REQUIRE_THROW(document.InsertImage(fs::path("not_existing_item"), 100, 100), invalid_argument);
	BOOST_REQUIRE(!document.CanUndo());

	// single image
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/1.png"), 10, 20));
	CheckImageItems(document, { { "1.png", 10, 20 } });

	BOOST_REQUIRE(document.CanUndo());
	document.Undo();
	CheckImageItems(document, {});

	document.Redo();
	CheckImageItems(document, { { "1.png", 10, 20 } });

	// multiple images
	document.InsertImage(fs::path("images/2.png"), 30, 40, 1);
	document.InsertImage(fs::path("images/3.png"), 50, 70, 1);
	CheckImageItems(document, { { "1.png", 10, 20 }, { "3.png", 50, 70 }, { "2.png", 30, 40 } });

	document.Undo();
	CheckImageItems(document, { { "1.png", 10, 20 }, { "2.png", 30, 40 } });

	document.Undo();
	CheckImageItems(document, { { "1.png", 10, 20 } });

	document.Redo();
	CheckImageItems(document, { { "1.png", 10, 20 }, { "2.png", 30, 40 } });

	document.Redo();
	CheckImageItems(document, { { "1.png", 10, 20 }, { "3.png", 50, 70 }, { "2.png", 30, 40 } });

	BOOST_REQUIRE(!document.CanRedo());
}

BOOST_AUTO_TEST_CASE(TestDeletingImagesUndoRedo)
{
	CDocument document;

	// single image
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/1.png"), 10, 20));
	document.DeleteItem(0);
	CheckImageItems(document, {});

	BOOST_REQUIRE(document.CanUndo());
	document.Undo();
	CheckImageItems(document, { { "1.png", 10, 20 } });

	// multiple actions
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/2.png"), 15, 25));
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/3.png"), 30, 40));
	CheckImageItems(document, { { "1.png", 10, 20 }, { "2.png", 15, 25 }, { "3.png", 30, 40 } });

	// delete item in the middle - second
	document.DeleteItem(1);
	CheckImageItems(document, { { "1.png", 10, 20 }, { "3.png", 30, 40 } });

	// delete first item - first
	document.DeleteItem(0);
	CheckImageItems(document, { { "3.png", 30, 40 } });
	BOOST_REQUIRE(document.CanUndo());

	document.Undo();
	CheckImageItems(document, { { "1.png", 10, 20 }, { "3.png", 30, 40 } });

	document.Undo();
	CheckImageItems(document, { { "1.png", 10, 20 }, { "2.png", 15, 25 }, { "3.png", 30, 40 } });

	BOOST_REQUIRE(document.CanRedo());
	document.Redo();
	CheckImageItems(document, { { "1.png", 10, 20 }, { "3.png", 30, 40 } });

	BOOST_REQUIRE(document.CanRedo());
	document.Redo();
	CheckImageItems(document, { { "3.png", 30, 40 } });
}

BOOST_AUTO_TEST_CASE(TestResizingImageUndoRedo)
{
	CDocument document;

	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/1.png"), 10, 20));
	CheckImageItems(document, { { "1.png", 10, 20 } });

	document.GetItem(0).GetImage()->Resize(50, 30);
	CheckImageItems(document, { { "1.png", 50, 30 } });

	document.DeleteItem(0);
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/2.png"), 100, 20));
	CheckImageItems(document, { { "2.png", 100, 20 } });

	document.Undo();
	CheckImageItems(document, {});

	document.Undo();
	CheckImageItems(document, { { "1.png", 50, 30 } });

	document.Undo();
	CheckImageItems(document, { { "1.png", 10, 20 } });

	document.Undo();
	CheckImageItems(document, {});
	BOOST_REQUIRE(!document.CanUndo());

	document.Redo();
	CheckImageItems(document, { { "1.png", 10, 20 } });

	document.Redo();
	CheckImageItems(document, { { "1.png", 50, 30 } });

	document.Redo();
	CheckImageItems(document, {});

	document.Redo();
	CheckImageItems(document, { { "2.png", 100, 20 } });
	BOOST_REQUIRE(!document.CanRedo());
}

BOOST_AUTO_TEST_SUITE_END()
