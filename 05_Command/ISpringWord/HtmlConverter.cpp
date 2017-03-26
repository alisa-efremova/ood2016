#include "stdafx.h"
#include "HtmlConverter.h"
#include "IDocument.h"
#include "DocumentItem.h"
#include "IParagraph.h"
#include "IImage.h"
#include <fstream>

using namespace std;

CHtmlConverter::CHtmlConverter(const IDocument & document)
	: m_document(document)
{
}

CHtmlConverter::~CHtmlConverter()
{
}

void CHtmlConverter::Save(const string & path)
{
	ofstream ofs(path, ofstream::out | ofstream::trunc);
	if (!ofs.is_open())
	{
		throw ios_base::failure("Cannot open file with path " + path);
	}
	ofs << "<!DOCTYPE html>\n<html>\n<head>\n    <title>" << m_document.GetTitle() << "</title>\n</head>\n";
	ofs << "<body>\n" << CreateBody() << "</body>\n</html>";
}

string CHtmlConverter::CreateBody()
{
	string body;
	for (size_t i = 0; i < m_document.GetItemsCount(); i++)
	{
		auto item = m_document.GetItem(i);
		if (item.GetParagraph())
		{
			body += "    <p>" + item.GetParagraph()->GetText() + "</p>\n";
		}
		else if (item.GetImage())
		{

		}
	}
	return body;
}
