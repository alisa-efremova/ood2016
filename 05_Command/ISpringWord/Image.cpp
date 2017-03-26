#include "stdafx.h"
#include "Image.h"
#include "ResizeImageCommand.h"

using namespace std;

CImage::CImage(const string & path, unsigned width, unsigned height, CHistory & history)
	: m_path(path)
	, m_width(width)
	, m_height(height)
	, m_history(history)
{
}

string CImage::GetPath() const
{
	return m_path;
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
