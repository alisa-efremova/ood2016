#include "stdafx.h"
#include "Image.h"
#include "ResizeImageCommand.h"

using namespace std;

CImage::CImage(const fs::path & path, unsigned width, unsigned height, CHistory & history)
	: m_width(width)
	, m_height(height)
	, m_history(history)
{
	m_fileName = path.filename().generic_string();
	if (m_fileName == "." || !path.has_extension() || !fs::exists(path))
	{
		throw invalid_argument("Invalid image path");
	}

	m_tempPath = fs::temp_directory_path() / fs::unique_path();
	fs::copy_file(path, m_tempPath);
}

CImage::~CImage()
{
	fs::remove(m_tempPath);
}

fs::path CImage::GetPath() const
{
	return fs::path("images") / m_fileName;
}

unsigned CImage::GetWidth() const
{
	return m_width;
}

unsigned CImage::GetHeight() const
{
	return m_height;
}

void CImage::Resize(unsigned width, unsigned height)
{
	m_history.AddAndExecuteCommand(make_unique<CResizeImageCommand>(m_width, m_height, width, height));
}

void CImage::Save(const fs::path & path) const
{
	if (path.has_parent_path())
	{
		fs::create_directories(path.parent_path());
	}
	fs::copy_file(m_tempPath, path, fs::copy_option::overwrite_if_exists);
}
