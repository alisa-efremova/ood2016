#pragma once
#include "IShape.h"
#include "Style.h"
#include "LineStyle.h"

class CSimpleShape : public IShape
{
public:
	void SetOutlineStyle(const std::shared_ptr<ILineStyle> & style) override;
	ILineStyle & GetOutlineStyle() override;
	const ILineStyle & GetOutlineStyle()const override;

	void SetFillStyle(const std::shared_ptr<IStyle> & style) override;
	IStyle & GetFillStyle() override;
	const IStyle & GetFillStyle()const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

protected:
	std::shared_ptr<ILineStyle> m_outlineStyle;
	std::shared_ptr<IStyle> m_fillStyle;
};

