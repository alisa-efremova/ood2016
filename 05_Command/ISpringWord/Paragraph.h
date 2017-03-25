#pragma once
#include "IParagraph.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(const std::string & text);
	virtual std::string GetText()const override;
	virtual void SetText(const std::string & text) override;
private:
	std::string m_text;
};

