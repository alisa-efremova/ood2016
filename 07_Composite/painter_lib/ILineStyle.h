#pragma once
#include "IStyle.h"

class ILineStyle : public IStyle
{
public:
	virtual size_t GetLineWidth()const = 0;
	virtual void SetLineWidth(size_t width) = 0;
};