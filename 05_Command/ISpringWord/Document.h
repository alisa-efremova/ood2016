#pragma once
#include "IDocument.h"
#include "History.h"

class CDocument : public IDocument
{
public:
	void SetTitle(const std::string & title) override;
	std::string GetTitle() const override;

	IParagraphPtr InsertParagraph(const std::string & text, boost::optional<size_t> position = boost::none) override;
	void Save(const std::string & path)const;

	size_t GetItemsCount()const override;
	CConstDocumentItem GetItem(size_t index)const override;
	CDocumentItem GetItem(size_t index) override;
	void DeleteItem(size_t index) override;

	bool CanUndo() const override;
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;

private:
	std::string m_title;
	CHistory m_history;
	std::list<DocumentItemPtr> m_items;
};