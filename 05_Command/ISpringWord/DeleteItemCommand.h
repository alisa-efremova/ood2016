#pragma once
#include "AbstractCommand.h"
#include "DocumentItem_fwd.h"

class CDeleteItemCommand : public CAbstractCommand
{
public:
	CDeleteItemCommand(std::list<DocumentItemPtr> & items, size_t index);
protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::list<DocumentItemPtr> & m_items;
	DocumentItemPtr m_item;
	size_t m_index;
};

