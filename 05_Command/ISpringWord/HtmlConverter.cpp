#include "stdafx.h"
#include "HtmlConverter.h"
#include "IDocument.h"
#include "DocumentItem.h"
#include "IParagraph.h"
#include "IImage.h"
#include <fstream>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

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
	fs::path smartPath(path);
	fs::create_directories(smartPath.parent_path());
	ofstream ofs(smartPath.generic_wstring(), ofstream::out | ofstream::trunc);

	if (!ofs.is_open())
	{
		throw ios_base::failure("Cannot open file with path " + smartPath.generic_string());
	}

	ofs << "<!DOCTYPE html>\n<html>\n<head>\n    <title>" << m_document.GetTitle() << "</title>\n</head>\n";
	ofs << "<body>\n" << CreateBody() << "</body>\n</html>";
	ofs.close();
}

string CHtmlConverter::CreateBody()
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
			body += "    <img src=\"" + image->GetPath()
				+ "\" height=\"" + to_string(image->GetHeight())
				+ "\" width=\"" + to_string(image->GetWidth())
				+ "\">\n";
		}
	}
	return body;
}
