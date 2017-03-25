#include "stdafx.h"
#include "Paragraph.h"

using namespace std;

CParagraph::CParagraph(const std::string & text)
	: m_text(text)
{
}

string & CParagraph::GetText()
{
	return m_text;
}

void CParagraph::SetText(const string & text)
{
	m_text = text;
}
