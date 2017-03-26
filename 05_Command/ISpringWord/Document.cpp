#include "stdafx.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "InsertItemCommand.h"
#include "DeleteItemCommand.h"
#include "Paragraph.h"

using namespace std;

void CDocument::SetTitle(const string & title)
{
	m_history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(m_title, title));
}

string CDocument::GetTitle() const
{
	return m_title;
}

IParagraphPtr CDocument::InsertParagraph(const string & text, boost::optional<size_t> position)
{
	auto paragraph = make_shared<CParagraph>(text, m_history);
	auto item = make_shared<CDocumentItem>(paragraph);
	m_history.AddAndExecuteCommand(make_unique<CInsertItemCommand>(m_items, item, position));
	return paragraph;
}

void CDocument::ReplaceText(size_t index, const string & text)
{
	if (index >= GetItemsCount())
	{
		throw out_of_range("Position is out of range");
	}
	
	auto item = *next(m_items.begin(), index);
	if (!item->GetParagraph())
	{
		throw invalid_argument("Can't replace text in non-text item");
	}

	item->GetParagraph()->SetText(text);
}

size_t CDocument::GetItemsCount() const
{
	return m_items.size();
}

CConstDocumentItem CDocument::GetItem(size_t index) const
{
	if (index >= GetItemsCount())
	{
		throw out_of_range("Position is out of range");
	}
	auto it = next(m_items.begin(), index);
	return *((*it).get());
}

CDocumentItem CDocument::GetItem(size_t index)
{
	if (index >= GetItemsCount())
	{
		throw out_of_range("");
	}
	auto it = next(m_items.begin(), index);
	return *((*it).get());
}

void CDocument::DeleteItem(size_t index)
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