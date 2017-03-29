#include "stdafx.h"
#include "ConstDocumentItem.h"
#include "DocumentItem.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "InsertItemCommand.h"
#include "DeleteItemCommand.h"
#include "Paragraph.h"
#include "Image.h"
#include "HtmlConverter.h"
namespace fs = boost::filesystem;

using namespace std;

void CDocument::SetTitle(const string & title)
{
	m_history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(m_title, title));
}

string CDocument::GetTitle() const
{
	return m_title;
}

IParagraphPtr CDocument::InsertParagraph(const string & text, boost::optional<unsigned> position)
{
	auto paragraph = make_shared<CParagraph>(text, m_history);
	auto item = make_shared<CDocumentItem>(paragraph);
	m_history.AddAndExecuteCommand(make_unique<CInsertItemCommand>(m_items, item, position));
	return paragraph;
}

IImagePtr CDocument::InsertImage(const fs::path & path, unsigned width, unsigned height, boost::optional<unsigned> position)
{
	auto image = make_shared<CImage>(path, width, height, m_history);
	auto item = make_shared<CDocumentItem>(image);
	m_history.AddAndExecuteCommand(make_unique<CInsertItemCommand>(m_items, item, position));
	return image;
}

void CDocument::Save(const fs::path & path) const
{
	CHtmlConverter converter(*this);
	converter.Save(path);
}

size_t CDocument::GetItemsCount() const
{
	return m_items.size();
}

CConstDocumentItem CDocument::GetItem(unsigned index) const
{
	return FindItem(index);
}

CDocumentItem CDocument::GetItem(unsigned index)
{
	return FindItem(index);
}

void CDocument::DeleteItem(unsigned index)
{
	m_history.AddAndExecuteCommand(make_unique<CDeleteItemCommand>(m_items, index));
}

bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	m_history.Undo();
}

bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	m_history.Redo();
}

CDocumentItem & CDocument::FindItem(unsigned index)const
{
	if (index >= GetItemsCount())
	{
		throw out_of_range("Index of item is out of range");
	}
	auto it = next(m_items.begin(), index);
	return *((*it).get());
}
