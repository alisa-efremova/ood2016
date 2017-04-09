#pragma once
#include "IStyle.h"

class CStyle : public IStyle
{
public:
	CStyle(boost::optional<bool> isEnabled = boost::none, boost::optional<CRGBAColor> color = boost::none);

	boost::optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	boost::optional<CRGBAColor> GetColor()const override;
	void SetColor(CRGBAColor color) override;

private:
	boost::optional<bool> m_isEnabled;
	boost::optional<CRGBAColor> m_color;
};

