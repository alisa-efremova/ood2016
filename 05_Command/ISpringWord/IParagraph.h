#pragma once

class IParagraph
{
public:
	virtual std::string & GetText() = 0;
	virtual void SetText(const std::string & text) = 0;
	virtual ~IParagraph() = default;
};
