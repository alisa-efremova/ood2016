#include "stdafx.h"
#include "DeleteItemCommand.h"

using namespace std;

CDeleteItemCommand::CDeleteItemCommand(list<DocumentItemPtr> & items, size_t position)
	: m_items(items)
	, m_position(position)
{
}

void CDeleteItemCommand::DoExecute()
{
	if (m_position > m_items.size())
	{
		throw out_of_range("Position is out of range.");
	}
	auto it = next(m_items.begin(), m_position);
	m_item = *it;
	m_items.erase(it);
}

void CDeleteItemCommand::DoUnexecute()
{
	if (m_position > m_items.size())
	{
		throw out_of_range("Position is out of range.");
	}
	auto it = next(m_items.begin(), m_position);
	m_items.insert(it, m_item);
}
