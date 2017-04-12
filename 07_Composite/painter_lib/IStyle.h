#pragma once
#include "RGBAColor.h"

class IStyle
{
public:
	virtual bool IsEnabled()const = 0;
	virtual void Enable(bool enable) = 0;

	virtual CRGBAColor GetColor()const = 0;
	virtual void SetColor(const CRGBAColor & color) = 0;

	virtual ~IStyle() = default;
};