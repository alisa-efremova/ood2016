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

void CHtmlConverter::Save(const fs::path & path)
{
	if (path.empty())
	{
		throw invalid_argument("Path is missing");
	}
	
	if (path.has_parent_path())
	{
		fs::create_directories(path.parent_path());
	}
	ofstream ofs(path.generic_wstring(), ofstream::out | ofstream::trunc);

	if (!ofs.is_open())
	{
		throw ios_base::failure("Cannot open file with path " + path.generic_string());
	}

	ofs << "<!DOCTYPE html>\n<html>\n<head>\n    <title>" << m_document.GetTitle() << "</title>\n</head>\n";
	ofs << "<body>\n" << CreateBody(path) << "</body>\n</html>";
	ofs.close();
}

string CHtmlConverter::CreateBody(const fs::path & path)
{
	string body;
	for (unsigned i = 0; i < m_document.GetItemsCount(); i++)
	{
		auto item = m_document.GetItem(i);
		if (item.GetParagraph())
		{
			body += "    <p>" + item.GetParagraph()->GetText() + "</p>\n";
		}
		else if (item.GetImage())
		{
			auto image = item.GetImage();
			auto imagePath = path.parent_path() / image->GetPath();
			image->Save(imagePath);
			body += "    <img src=\"" + image->GetPath().generic_string()
				+ "\" height=\"" + to_string(image->GetHeight())
				+ "\" width=\"" + to_string(image->GetWidth())
				+ "\">\n";
		}
	}
	return body;
}
