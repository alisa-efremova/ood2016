#pragma once
#include "IDocument.h"
#include "History.h"

class CDocument : public IDocument
{
public:
	void SetTitle(const std::string & title) override;
	std::string GetTitle() const override;

	IParagraphPtr InsertParagraph(const std::string & text, boost::optional<unsigned> position = boost::none) override;
	IImagePtr InsertImage(const fs::path & path, unsigned width, unsigned height,
		boost::optional<unsigned> position = boost::none) override;
	void Save(const fs::path & path)const;

	size_t GetItemsCount()const override;
	CConstDocumentItem GetItem(unsigned index)const override;
	CDocumentItem GetItem(unsigned index) override;
	void DeleteItem(unsigned index) override;

	bool CanUndo() const override;
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;

private:
	CDocumentItem & FindItem(unsigned index)const;

	std::string m_title;
	CHistory m_history;
	std::list<DocumentItemPtr> m_items;
};