#include "stdafx.h"
#include "History.h"
#include "MockCommand.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(HistoryTests)

BOOST_AUTO_TEST_CASE(TestConstructor)
{
	CHistory history;
	BOOST_REQUIRE(!history.CanUndo());
	BOOST_REQUIRE(!history.CanRedo());
}

BOOST_AUTO_TEST_CASE(TestCanUndoCanRedo)
{
	CHistory history;
	vector<SCommandInfo> commandHistory;

	// no commands to redo or undo
	BOOST_REQUIRE(!history.CanUndo());
	history.Undo();
	BOOST_REQUIRE_EQUAL(commandHistory.size(), 0);

	BOOST_REQUIRE(!history.CanRedo());
	history.Redo();
	BOOST_REQUIRE_EQUAL(commandHistory.size(), 0);

	// can undo after adding command, but cannot redo
	history.AddAndExecuteCommand(make_unique<CMockCommand>(0, commandHistory));
	BOOST_REQUIRE(!history.CanRedo());
	history.Redo();
	BOOST_REQUIRE_EQUAL(commandHistory.size(), 1);

	BOOST_REQUIRE(history.CanUndo());
	history.Undo();
	BOOST_REQUIRE_EQUAL(commandHistory.size(), 2);

	BOOST_REQUIRE(!history.CanUndo());
	history.Undo();
	BOOST_REQUIRE_EQUAL(commandHistory.size(), 2);
}

BOOST_AUTO_TEST_CASE(TestAddingCommand)
{
	CHistory history;
	vector<SCommandInfo> commandHistory;
	
	history.AddAndExecuteCommand(make_unique<CMockCommand>(0, commandHistory));
	BOOST_REQUIRE_EQUAL(commandHistory.size(), 1);
	BOOST_REQUIRE(commandHistory[0] == SCommandInfo(0, true));

	history.Undo();
	BOOST_REQUIRE_EQUAL(commandHistory.size(), 2);
	BOOST_REQUIRE(commandHistory[1] == SCommandInfo(0, false));

	history.Redo();
	BOOST_REQUIRE_EQUAL(commandHistory.size(), 3);
	BOOST_REQUIRE(commandHistory[2] == SCommandInfo(0, true));
}

BOOST_AUTO_TEST_CASE(TestAddingMultipleCommands)
{
	CHistory history;
	vector<SCommandInfo> commandHistory;

	history.AddAndExecuteCommand(make_unique<CMockCommand>(1, commandHistory));
	history.AddAndExecuteCommand(make_unique<CMockCommand>(2, commandHistory));
	history.AddAndExecuteCommand(make_unique<CMockCommand>(3, commandHistory));

	BOOST_REQUIRE_EQUAL(commandHistory.size(), 3);
	BOOST_REQUIRE(commandHistory[0] == SCommandInfo(1, true));
	BOOST_REQUIRE(commandHistory[1] == SCommandInfo(2, true));
	BOOST_REQUIRE(commandHistory[2] == SCommandInfo(3, true));

	history.Undo();
	BOOST_REQUIRE_EQUAL(commandHistory.size(), 4);
	BOOST_REQUIRE(commandHistory[3] == SCommandInfo(3, false));

	history.Undo();
	BOOST_REQUIRE_EQUAL(commandHistory.size(), 5);
	BOOST_REQUIRE(commandHistory[4] == SCommandInfo(2, false));

	history.Undo();
	BOOST_REQUIRE_EQUAL(commandHistory.size(), 6);
	BOOST_REQUIRE(commandHistory[5] == SCommandInfo(1, false));

	BOOST_REQUIRE(!history.CanUndo());

	history.Redo();
	BOOST_REQUIRE_EQUAL(commandHistory.size(), 7);
	BOOST_REQUIRE(commandHistory[6] == SCommandInfo(1, true));

	history.Redo();
	BOOST_REQUIRE_EQUAL(commandHistory.size(), 8);
	BOOST_REQUIRE(commandHistory[7] == SCommandInfo(2, true));

	history.Redo();
	BOOST_REQUIRE_EQUAL(commandHistory.size(), 9);
	BOOST_REQUIRE(commandHistory[8] == SCommandInfo(3, true));

	BOOST_REQUIRE(!history.CanRedo());
}

BOOST_AUTO_TEST_CASE(TestRewritingHistory)
{
	CHistory history;
	vector<SCommandInfo> commandHistory;

	history.AddAndExecuteCommand(make_unique<CMockCommand>(1, commandHistory));
	history.AddAndExecuteCommand(make_unique<CMockCommand>(2, commandHistory));
	history.AddAndExecuteCommand(make_unique<CMockCommand>(3, commandHistory));

	history.Undo();
	BOOST_REQUIRE(history.CanRedo());

	history.AddAndExecuteCommand(make_unique<CMockCommand>(4, commandHistory));
	BOOST_REQUIRE_EQUAL(commandHistory.size(), 5);
	BOOST_REQUIRE(commandHistory[4] == SCommandInfo(4, true));

	BOOST_REQUIRE(!history.CanRedo());
	history.Redo();
	BOOST_REQUIRE_EQUAL(commandHistory.size(), 5);
	BOOST_REQUIRE(commandHistory[4] == SCommandInfo(4, true));
}

BOOST_AUTO_TEST_SUITE_END()


