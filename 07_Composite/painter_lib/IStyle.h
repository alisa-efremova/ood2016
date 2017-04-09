#pragma once
#include "RGBAColor.h"
#include <boost/optional/optional.hpp>

class IStyle
{
public:
	virtual boost::optional<bool> IsEnabled()const = 0;
	virtual void Enable(bool enable) = 0;

	virtual boost::optional<CRGBAColor> GetColor()const = 0;
	virtual void SetColor(CRGBAColor color) = 0;

	virtual ~IStyle() = default;
};