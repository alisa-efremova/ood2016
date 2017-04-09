#pragma once
#include "ICanvas.h"
#include <iostream>
#include <boost/optional.hpp>

class CCanvas : public ICanvas
{
public:
	CCanvas(std::ostream & ostream)
		: m_ostream(ostream)
	{
	}

	virtual void SetLineWidth(size_t width) override
	{
		m_lineWidth = width;
	}

	virtual void SetLineColor(CRGBAColor color) override
	{
		m_lineColor = color;
	}

	virtual void BeginFill(CRGBAColor color) override
	{
		m_fillColor = color;
	}

	virtual void EndFill() override
	{
		m_fillColor = boost::none;
	}

protected:
	size_t m_lineWidth = 1;
	CRGBAColor m_lineColor;
	boost::optional<CRGBAColor> m_fillColor;
	std::ostream & m_ostream;
};

