#include "stdafx.h"
#include "DeleteItemCommand.h"

using namespace std;

CDeleteItemCommand::CDeleteItemCommand(list<DocumentItemPtr> & items, size_t index)
	: m_items(items)
	, m_index(index)
{
}

void CDeleteItemCommand::DoExecute()
{
	if (m_index > m_items.size())
	{
		throw out_of_range("Position is out of range.");
	}
	auto it = next(m_items.begin(), m_index);
	m_item = *it;
	m_items.erase(it);
}

void CDeleteItemCommand::DoUnexecute()
{
	if (m_index > m_items.size())
	{
		throw out_of_range("Position is out of range.");
	}
	auto it = next(m_items.begin(), m_index);
	m_items.insert(it, m_item);
}
