#pragma once
#include "IStyle.h"

class CStyle : public IStyle
{
public:
	CStyle(bool isEnabled = false, const CRGBAColor & color = CRGBAColor());

	bool IsEnabled()const override;
	void Enable(bool enable) override;

	CRGBAColor GetColor()const override;
	void SetColor(const CRGBAColor & color) override;

private:
	bool m_isEnabled;
	CRGBAColor m_color;
};

