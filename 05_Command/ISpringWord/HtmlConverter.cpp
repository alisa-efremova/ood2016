#include "stdafx.h"
#include "HtmlConverter.h"
#include "IDocument.h"
#include "DocumentItem.h"
#include "IParagraph.h"
#include "IImage.h"
#include <fstream>

using namespace std;

static string IMAGES_DIR = "images";

CHtmlConverter::CHtmlConverter(const IDocument & document)
	: m_document(document)
{
	m_htmlEntitiesMap.insert({ '<', "&lt;" });
	m_htmlEntitiesMap.insert({ '>', "&gt;" });
	m_htmlEntitiesMap.insert({ '&', "&amp;" });
	m_htmlEntitiesMap.insert({ '"', "&quot;" });
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
		auto & item = m_document.GetItem(i);
		if (item.GetParagraph())
		{
			body += CreateParagraph(item.GetParagraph());
		}
		else if (item.GetImage())
		{
			body += CreateImage(item.GetImage(), path);
		}
	}
	return body;
}

string CHtmlConverter::CreateParagraph(const IParagraphConstPtr & paragraph)
{
	return "    <p>" + EncodeHtmlEntities(paragraph->GetText()) + "</p>\n";
}

string CHtmlConverter::CreateImage(const IImageConstPtr & image, const fs::path & path)
{
	auto relativePath = fs::path(IMAGES_DIR) / GetUniqueImageName(image->GetName());
	image->Save(path.parent_path() / relativePath);
	return "    <img src=\"" + relativePath.generic_string()
		+ "\" height=\"" + to_string(image->GetHeight())
		+ "\" width=\"" + to_string(image->GetWidth())
		+ "\">\n";
}

fs::path CHtmlConverter::GetUniqueImageName(const string & imageName)
{
	auto it = m_imageNameMap.find(imageName);
	if (it == m_imageNameMap.end())
	{
		m_imageNameMap.insert({ imageName, 0});
		return imageName;
	}
	else
	{
		it->second++;
		auto path = fs::path(imageName);
		return fs::path(path.stem().string() + to_string(it->second) + path.extension().string());
	}
}

string CHtmlConverter::EncodeHtmlEntities(const string & text)
{
	string encodedText;
	for (int i = 0; i < text.length(); i++)
	{
		auto it = m_htmlEntitiesMap.find(text[i]);
		if (it == m_htmlEntitiesMap.end())
		{
			encodedText += text[i];
		}
		else
		{
			encodedText += it->second;
		}
	}
	return encodedText;
}
