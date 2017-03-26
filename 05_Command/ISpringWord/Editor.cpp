#include "stdafx.h"
#include "Editor.h"

CEditor::CEditor()
	:m_document(make_unique<CDocument>())
{
	m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
	m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
	AddMenuItem("setTitle", "Change title. Args: <new title>", &CEditor::SetTitle);
	AddMenuItem("insertParagraph", "Add paragraph to the position. Args: <position>|end <text>", &CEditor::AddParagraph);
	AddMenuItem("deleteItem", "Delete item at position. Args: <position>", &CEditor::DeleteItem);
	AddMenuItem("replaceText", "Replace text at position. Args: <position>", &CEditor::ReplaceText);
	AddMenuItem("save", "Save html document to path. Args: <path>", &CEditor::Save);
	AddMenuItem("list", "Show document", &CEditor::List);
	AddMenuItem("undo", "Undo command", &CEditor::Undo);
	AddMenuItem("redo", "Redo undone command", &CEditor::Redo);
}

void CEditor::Start()
{
	m_menu.Run();
}

void CEditor::AddMenuItem(const string & shortcut, const string & description, MenuHandler handler)
{
	m_menu.AddItem(shortcut, description, bind(handler, this, _1));
}

void CEditor::SetTitle(istream & in)
{
	string title;
	getline(in >> ws, title);
	m_document->SetTitle(title);
}

void CEditor::AddParagraph(istream & in)
{
	boost::optional<size_t> position = boost::none;
	size_t index;
	if (in >> index)
	{
		position = index;
	}
	else
	{
		in.clear();
		string pos;
		in >> pos;
		if (pos != "end")
		{
			cout << "Invalid position" << endl;
			return;
		}
	}

	string text;
	getline(in >> ws, text);
	try
	{
		m_document->InsertParagraph(text, position);
	}
	catch (exception & e)
	{
		cout << e.what() << endl;
	}
}

void CEditor::DeleteItem(istream & in)
{
	size_t index;
	if (!(in >> index))
	{
		cout << "Invalid position" << endl;
		return;
	}
	try
	{
		m_document->DeleteItem(index);
	}
	catch (exception & e)
	{
		cout << e.what() << endl;
	}
}

void CEditor::ReplaceText(istream & in)
{
	size_t index;
	if (!(in >> index))
	{
		cout << "Invalid position" << endl;
		return;
	}

	string text;
	getline(in >> ws, text);
	
	try
	{
		auto item = m_document->GetItem(index);
		if (!item.GetParagraph())
		{
			throw invalid_argument("Can't replace text in non-text item");
		}

		item.GetParagraph()->SetText(text);
	}
	catch (exception & e)
	{
		cout << e.what() << endl;
	}
}

void CEditor::Save(istream & in)
{
	string path;
	in >> path;
	if (path == "")
	{
		cout << "Path is missing" << endl;
	}
	else
	{
		m_document->Save(path);
	}
}

void CEditor::List(istream &)
{
	cout << "-------------" << endl;
	cout << m_document->GetTitle() << endl;
	for (size_t i = 0; i < m_document->GetItemsCount(); i++)
	{
		auto item = m_document->GetItem(i);
		if (item.GetParagraph())
		{
			cout << i << ". Paragraph: " << item.GetParagraph()->GetText() << endl;
		}
		else
		{
			cout << "Image" << endl;
		}
	}
	cout << "-------------" << endl;
}

void CEditor::Undo(istream &)
{
	if (m_document->CanUndo())
	{
		m_document->Undo();
	}
	else
	{
		cout << "Can't undo" << endl;
	}
}

void CEditor::Redo(istream &)
{
	if (m_document->CanRedo())
	{
		m_document->Redo();
	}
	else
	{
		cout << "Can't redo" << endl;
	}
}

