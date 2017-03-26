#pragma once
#include "IImage.h"
#include "History.h"

class CImage : public IImage
{
public:
	CImage(const std::string & path, unsigned width, unsigned height, CHistory & history);

	std::string GetPath()const override;
	unsigned GetWidth()const override;
	unsigned GetHeight()const override;
	void Resize(unsigned width, unsigned height) override;
private:
	std::string m_path;
	unsigned m_width;
	unsigned m_height;
	CHistory & m_history;
};