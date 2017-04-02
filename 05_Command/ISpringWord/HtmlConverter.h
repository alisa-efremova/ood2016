#pragma once

#include "DocumentItem_fwd.h"
class IDocument;
namespace fs = boost::filesystem;

class CHtmlConverter
{
public:
	CHtmlConverter(const IDocument & document);
	~CHtmlConverter();

	void Save(const fs::path & path);
private:
	std::string CreateBody(const fs::path & path);
	std::string CreateParagraph(const IParagraphConstPtr & paragraph);
	std::string CreateImage(const IImageConstPtr & image, const fs::path & path);
	fs::path GetUniqueImageName(const std::string & imageName);
	std::string EncodeHtmlEntities(const std::string & text);

	const IDocument & m_document;
	std::map<std::string, unsigned> m_imageNameMap;
	std::map<char, std::string> m_htmlEntitiesMap;
};

