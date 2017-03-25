// ISpringWord.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Menu.h"
#include "Document.h"

using namespace std;
using namespace std::placeholders;

namespace
{

class CEditor
{
public:
	CEditor()  //-V730
		:m_document(make_unique<CDocument>())
	{
		m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
		m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
		AddMenuItem("setTitle", "Changes title. Args: <new title>", &CEditor::SetTitle);
		AddMenuItem("insertParagraph", "Adds paragraph to the position. Args: <position>|end <text>", &CEditor::AddParagraph);
		AddMenuItem("deleteItem", "Delete item at position. Args: <position>", &CEditor::DeleteItem);
		AddMenuItem("replaceText", "Replace text at position. Args: <position>", &CEditor::ReplaceText);
		AddMenuItem("list", "Show document", &CEditor::List);
		AddMenuItem("undo", "Undo command", &CEditor::Undo);
		AddMenuItem("redo", "Redo undone command", &CEditor::Redo);
	}

	void Start()
	{
		m_menu.Run();
	}

private:
	// Указатель на метод класса CEditor, принимающий istream& и возвращающий void
	typedef void (CEditor::*MenuHandler)(istream & in);

	void AddMenuItem(const string & shortcut, const string & description, MenuHandler handler)
	{
		m_menu.AddItem(shortcut, description, bind(handler, this, _1));
	}

	// TODO: скипнуть первый пробел элегантнее
	void SetTitle(istream & in)
	{
		string title;
		getline(in >> ws, title);
		m_document->SetTitle(title);
	}

	void AddParagraph(istream & in)
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

	void DeleteItem(istream & in)
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

	void ReplaceText(istream & in)
	{

	}

	void List(istream &)
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

	void Undo(istream &)
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

	void Redo(istream &)
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

	CMenu m_menu;
	unique_ptr<IDocument> m_document;
};

}

int main()
{
	CEditor editor;
	editor.Start();
	return 0;
}

