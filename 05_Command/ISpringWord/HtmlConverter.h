#pragma once
class IDocument;

class CHtmlConverter
{
public:
	CHtmlConverter(const IDocument & document);
	~CHtmlConverter();

	void Save(const std::string & path);
private:
	std::string CreateBody();

	const IDocument & m_document;
};

