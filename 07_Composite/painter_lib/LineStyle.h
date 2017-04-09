#pragma once
#include "ILineStyle.h"

class CLineStyle : public ILineStyle
{
public:
	CLineStyle(boost::optional<bool> isEnabled = boost::none, boost::optional<CRGBAColor> color = boost::none, size_t lineWidth = 1);
	
	boost::optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	boost::optional<CRGBAColor> GetColor()const override;
	void SetColor(CRGBAColor color) override;

	size_t GetLineWidth()const override;
	void SetLineWidth(size_t width) override;

private:
	boost::optional<bool> m_isEnabled;
	boost::optional<CRGBAColor> m_color;
	size_t m_lineWidth;
};

