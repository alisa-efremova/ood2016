#include "stdafx.h"
#include "History.h"
#include "DocumentItem_fwd.h"
#include "DocumentItem.h"
#include "Paragraph.h"
#include "Image.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(DocumentItemsTests)

BOOST_AUTO_TEST_CASE(TestParagraph)
{
	CHistory history;
	IParagraphPtr paragraph = make_shared<CParagraph>("text", history);
	CDocumentItem item(paragraph);
	BOOST_REQUIRE(item.GetParagraph() == paragraph);
	BOOST_REQUIRE(item.GetImage() == nullptr);
}

BOOST_AUTO_TEST_CASE(TestImage)
{
	CHistory history;
	IImagePtr image = make_shared<CImage>();
	CDocumentItem item(image);
	BOOST_REQUIRE(item.GetParagraph() == nullptr);
	BOOST_REQUIRE(item.GetImage() == image);
}

BOOST_AUTO_TEST_SUITE_END()