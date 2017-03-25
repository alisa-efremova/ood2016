#pragma once
#include "Menu.h"
#include "Document.h"

using namespace std;
using namespace std::placeholders;

class CEditor
{
public:
	CEditor();
	void Start();

private:
	// Указатель на метод класса CEditor, принимающий istream& и возвращающий void
	typedef void (CEditor::*MenuHandler)(istream & in);

	void AddMenuItem(const string & shortcut, const string & description, MenuHandler handler);

	void SetTitle(istream & in);
	void AddParagraph(istream & in);
	void DeleteItem(istream & in);
	void ReplaceText(istream & in);
	void List(istream &);
	void Undo(istream &);
	void Redo(istream &);

	CMenu m_menu;
	unique_ptr<IDocument> m_document;
};
