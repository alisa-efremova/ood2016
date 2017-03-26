#pragma once
#include "AbstractCommand.h"

struct SCommandInfo
{
	unsigned commandId;
	bool isExecuted;

	SCommandInfo() {};
	SCommandInfo(unsigned commandId, bool isExecuted)
		: commandId(commandId)
		, isExecuted(isExecuted)
	{}

	bool operator ==(const SCommandInfo& a) const
	{
		return commandId == a.commandId && isExecuted == a.isExecuted;
	}
};

class CMockCommand : public CAbstractCommand
{
public:
	CMockCommand(unsigned commandId, std::vector<SCommandInfo> & commandHistory)
		: m_id(commandId)
		, m_commandHistory(commandHistory)
	{}
protected:
	void DoExecute() override
	{
		m_commandHistory.push_back({ m_id, true });
	}
	void DoUnexecute() override
	{
		m_commandHistory.push_back({ m_id, false });
	}
private:
	unsigned m_id;
	std::vector<SCommandInfo> & m_commandHistory;
};