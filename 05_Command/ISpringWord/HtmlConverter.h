#pragma once
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

	const IDocument & m_document;
};

