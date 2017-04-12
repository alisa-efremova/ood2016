#pragma once
#include "ILineStyle.h"

class CLineStyle : public ILineStyle
{
public:
	CLineStyle(bool isEnabled = false, const CRGBAColor & color = CRGBAColor(), size_t lineWidth = 1);
	
	bool IsEnabled()const override;
	void Enable(bool enable) override;

	CRGBAColor GetColor()const override;
	void SetColor(const CRGBAColor & color) override;

	size_t GetLineWidth()const override;
	void SetLineWidth(size_t width) override;

private:
	bool m_isEnabled;
	CRGBAColor m_color;
	size_t m_lineWidth;
};

