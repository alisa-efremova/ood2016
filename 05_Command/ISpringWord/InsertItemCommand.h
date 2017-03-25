#pragma once
#include "AbstractCommand.h"
#include "IParagraph.h"
#include "DocumentItem_fwd.h"

class CInsertItemCommand : public CAbstractCommand
{
public:
	CInsertItemCommand(std::list<DocumentItemPtr> & items, DocumentItemPtr item, boost::optional<size_t> position);
protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::list<DocumentItemPtr> & m_items;
	DocumentItemPtr m_item;
	boost::optional<size_t> m_position;
};

