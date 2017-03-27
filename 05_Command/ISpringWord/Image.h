#pragma once
#include "IImage.h"
#include "History.h"

class CImage : public IImage
{
public:
	CImage(const fs::path & path, unsigned width, unsigned height, CHistory & history);
	~CImage();

	fs::path GetPath()const override;
	unsigned GetWidth()const override;
	unsigned GetHeight()const override;
	void Resize(unsigned width, unsigned height) override;
	void Save(const fs::path & path)const override;

private:
	fs::path m_tempPath;
	std::string m_fileName;
	unsigned m_width;
	unsigned m_height;
	CHistory & m_history;
};