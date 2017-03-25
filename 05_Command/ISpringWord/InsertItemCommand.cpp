#include "stdafx.h"
#include "InsertItemCommand.h"

using namespace std;

CInsertItemCommand::CInsertItemCommand(list<DocumentItemPtr> & items, DocumentItemPtr item, boost::optional<size_t> position)
	: m_items(items)
	, m_item(item)
	, m_position(position)
{
}

void CInsertItemCommand::DoExecute()
{
	if (m_position)
	{
		if (*m_position > m_items.size())
		{
			throw out_of_range("Position is out of range.");
		}

		auto it = next(m_items.begin(), *m_position);
		m_items.insert(it, m_item);
	}
	else
	{
		m_items.push_back(m_item);
	}
}

void CInsertItemCommand::DoUnexecute()
{
	if (m_position)
	{
		if (*m_position > m_items.size())
		{
			throw out_of_range("Position is out of range.");
		}

		auto it = next(m_items.begin(), *m_position);
		m_items.erase(it);
	}
	else
	{
		m_items.pop_back();
	}
}
