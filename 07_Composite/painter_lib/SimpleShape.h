#pragma once
#include "IShape.h"
#include "Style.h"
#include "LineStyle.h"
class ICanvas;

class CSimpleShape : public IShape
{
public:
	CSimpleShape();

	void SetOutlineStyle(const ILineStylePtr & style) override;
	ILineStylePtr GetOutlineStyle() override;
	ILineStyleConstPtr GetOutlineStyle()const override;

	void SetFillStyle(const IStylePtr & style) override;
	IStylePtr GetFillStyle() override;
	IStyleConstPtr GetFillStyle()const override;

	IGroupShapePtr GetGroup() override;
	IGroupShapeConstPtr GetGroup() const override;

protected:
	void BeginDraw(ICanvas & canvas);
	void EndDraw(ICanvas & canvas);

	virtual void CalculateFrame() = 0;

	std::shared_ptr<ILineStyle> m_outlineStyle;
	std::shared_ptr<IStyle> m_fillStyle;
	RectD m_frame = { 0, 0, 0, 0 };
};

