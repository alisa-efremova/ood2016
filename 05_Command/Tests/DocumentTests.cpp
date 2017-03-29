#include "stdafx.h"
#include "Document.h"
#include "DocumentItem.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(DocumentTests)

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
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "");

	// not empty paragraph insertion at the end
	document.InsertParagraph("alice");
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 2);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "");
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetParagraph()->GetText(), "alice");

	// insertion at first position
	document.InsertParagraph("bob", 0);
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 3);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "bob");
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetParagraph()->GetText(), "");
	BOOST_REQUIRE_EQUAL(document.GetItem(2).GetParagraph()->GetText(), "alice");

	// insertion at last position
	document.InsertParagraph("last", 3);
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 4);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "bob");
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetParagraph()->GetText(), "");
	BOOST_REQUIRE_EQUAL(document.GetItem(2).GetParagraph()->GetText(), "alice");
	BOOST_REQUIRE_EQUAL(document.GetItem(3).GetParagraph()->GetText(), "last");

	// insertion at middle position
	document.InsertParagraph("middle", 2);
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 5);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "bob");
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetParagraph()->GetText(), "");
	BOOST_REQUIRE_EQUAL(document.GetItem(2).GetParagraph()->GetText(), "middle");
	BOOST_REQUIRE_EQUAL(document.GetItem(3).GetParagraph()->GetText(), "alice");
	BOOST_REQUIRE_EQUAL(document.GetItem(4).GetParagraph()->GetText(), "last");

	// invalid position
	BOOST_REQUIRE_THROW(document.InsertParagraph("invalid", 10), out_of_range);
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 5);
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
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "second");

	// deletion of the paragraph in the middle of the list
	document.InsertParagraph("alice");
	document.InsertParagraph("bob");
	BOOST_REQUIRE_NO_THROW(document.DeleteItem(1));
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 2);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "second");
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetParagraph()->GetText(), "bob");

	// invalid position
	BOOST_REQUIRE_THROW(document.DeleteItem(5), out_of_range);
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 2);
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
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 0);

	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "first");

	// multiple paragraphs
	document.InsertParagraph("third", 1);
	document.InsertParagraph("second", 1);
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 3);

	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 2);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "first");
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetParagraph()->GetText(), "third");

	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "first");

	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 2);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "first");
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetParagraph()->GetText(), "third");

	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 3);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "first");
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetParagraph()->GetText(), "second");
	BOOST_REQUIRE_EQUAL(document.GetItem(2).GetParagraph()->GetText(), "third");

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
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 0);
	BOOST_REQUIRE(document.CanUndo());
	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "first");

	// multiple actions
	document.InsertParagraph("second");
	document.InsertParagraph("third");
	// delete item in the middle - second
	document.DeleteItem(1);
	// delete first item - first
	document.DeleteItem(0);
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "third");
	BOOST_REQUIRE(document.CanUndo());

	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 2);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "first");
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetParagraph()->GetText(), "third");

	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 3);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "first");
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetParagraph()->GetText(), "second");
	BOOST_REQUIRE_EQUAL(document.GetItem(2).GetParagraph()->GetText(), "third");

	BOOST_REQUIRE(document.CanRedo());
	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 2);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "first");
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetParagraph()->GetText(), "third");

	BOOST_REQUIRE(document.CanRedo());
	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "third");
}

BOOST_AUTO_TEST_CASE(TestReplacingTextUndoRedo)
{
	CDocument document;
	document.InsertParagraph("text");
	document.GetItem(0).GetParagraph()->SetText("new text");
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "new text");
	document.DeleteItem(0);
	document.InsertParagraph("other text");
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "other text");

	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 0);

	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "new text");

	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "text");

	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 0);
	BOOST_REQUIRE(!document.CanUndo());

	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "text");

	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "new text");

	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 0);

	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "other text");
	BOOST_REQUIRE(!document.CanRedo());
}

BOOST_AUTO_TEST_CASE(TestAddingImage)
{
	CDocument document;

	// invalid path
	BOOST_REQUIRE_THROW(document.InsertImage(fs::path("not_existing_item"), 100, 100), invalid_argument);
	// not existing path
	BOOST_REQUIRE_THROW(document.InsertImage(fs::path("not_existing_item.png"), 100, 100), invalid_argument);
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 0);

	// provide valid path for image
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/1.png"), 0, 0));
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath() , fs::path("images/1.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetWidth(), 0);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetHeight(), 0);

	// insertion at last position
	document.InsertImage(fs::path("images/2.png"), 10, 20, 1);
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 2);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/1.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetImage()->GetPath(), fs::path("images/2.png"));

	// insertion at middle position
	document.InsertImage(fs::path("images/3.png"), 30, 40, 1);
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 3);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/1.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetImage()->GetPath(), fs::path("images/3.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(2).GetImage()->GetPath(), fs::path("images/2.png"));

	// invalid position
	BOOST_REQUIRE_THROW(document.InsertImage(fs::path("images/3.png"), 0, 0, 10), out_of_range);
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 3);
}

BOOST_AUTO_TEST_CASE(TestDeletingImage)
{
	CDocument document;

	// single image deletion
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/1.png"), 10, 20));
	BOOST_REQUIRE_THROW(document.GetItem(1), out_of_range);
	BOOST_REQUIRE_NO_THROW(document.DeleteItem(0));
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 0);

	// deletion of the first image
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/1.png"), 10, 20));
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/2.png"), 30, 40));

	BOOST_REQUIRE_THROW(document.GetItem(2), out_of_range);
	BOOST_REQUIRE_NO_THROW(document.DeleteItem(0));
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/2.png"));

	// deletion of the image in the middle of the list
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/1.png"), 30, 40));
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/3.png"), 50, 60));
	BOOST_REQUIRE_NO_THROW(document.DeleteItem(1));
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 2);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/2.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetImage()->GetPath(), fs::path("images/3.png"));

	// invalid position
	BOOST_REQUIRE_THROW(document.DeleteItem(2), out_of_range);
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 2);
}

BOOST_AUTO_TEST_CASE(TestInsertingImageUndoRedo)
{
	CDocument document;

	// no history for invalid input
	BOOST_REQUIRE_THROW(document.InsertImage(fs::path("not_existing_item"), 100, 100), invalid_argument);
	BOOST_REQUIRE(!document.CanUndo());

	// single image
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/1.png"), 10, 20));
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE(document.CanUndo());
	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 0);

	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/1.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetWidth(), 10);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetHeight(), 20);

	// multiple images
	document.InsertImage(fs::path("images/2.png"), 30, 40, 1);
	document.InsertImage(fs::path("images/3.png"), 50, 70, 1);
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 3);

	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 2);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/1.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetImage()->GetPath(), fs::path("images/2.png"));

	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/1.png"));

	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 2);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/1.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetImage()->GetPath(), fs::path("images/2.png"));

	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 3);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/1.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetImage()->GetPath(), fs::path("images/3.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(2).GetImage()->GetPath(), fs::path("images/2.png"));

	BOOST_REQUIRE(!document.CanRedo());
}

BOOST_AUTO_TEST_CASE(TestDeletingImagesUndoRedo)
{
	CDocument document;

	// single image
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/1.png"), 10, 20));
	document.DeleteItem(0);
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 0);
	BOOST_REQUIRE(document.CanUndo());
	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/1.png"));

	// multiple actions
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/2.png"), 15, 25));
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/3.png"), 30, 40));
	// delete item in the middle - second
	document.DeleteItem(1);
	// delete first item - first
	document.DeleteItem(0);
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/3.png"));
	BOOST_REQUIRE(document.CanUndo());

	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 2);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/1.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetImage()->GetPath(), fs::path("images/3.png"));

	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 3);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/1.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetImage()->GetPath(), fs::path("images/2.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(2).GetImage()->GetPath(), fs::path("images/3.png"));

	BOOST_REQUIRE(document.CanRedo());
	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 2);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/1.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(1).GetImage()->GetPath(), fs::path("images/3.png"));

	BOOST_REQUIRE(document.CanRedo());
	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/3.png"));
}

BOOST_AUTO_TEST_CASE(TestResizingImageUndoRedo)
{
	CDocument document;
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/1.png"), 10, 20));
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/1.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetWidth(), 10);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetHeight(), 20);

	document.GetItem(0).GetImage()->Resize(50, 30);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/1.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetWidth(), 50);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetHeight(), 30);

	document.DeleteItem(0);
	BOOST_REQUIRE_NO_THROW(document.InsertImage(fs::path("images/2.png"), 100, 20));
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/2.png"));

	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 0);

	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/1.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetWidth(), 50);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetHeight(), 30);

	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/1.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetWidth(), 10);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetHeight(), 20);

	document.Undo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 0);
	BOOST_REQUIRE(!document.CanUndo());

	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/1.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetWidth(), 10);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetHeight(), 20);

	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/1.png"));
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetWidth(), 50);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetHeight(), 30);

	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 0);

	document.Redo();
	BOOST_REQUIRE_EQUAL(document.GetItemsCount(), 1);
	BOOST_REQUIRE_EQUAL(document.GetItem(0).GetImage()->GetPath(), fs::path("images/2.png"));
	BOOST_REQUIRE(!document.CanRedo());
}


BOOST_AUTO_TEST_SUITE_END()