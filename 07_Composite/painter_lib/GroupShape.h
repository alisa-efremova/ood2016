#pragma once
#include "IGroupShape.h"
#include <vector>
#include "LineStyle.h"
#include "Style.h"
#include "SPoint.h"
#include "Rect.h"

class CGroupShape : public IGroupShape
{
public:

	RectD GetFrame()const override;
	void SetFrame(const RectD & rect) override;

	void SetOutlineStyle(const ILineStylePtr & style) override;
	ILineStylePtr GetOutlineStyle() override;
	ILineStyleConstPtr GetOutlineStyle()const override;

	void SetFillStyle(const IStylePtr & style) override;
	IStylePtr GetFillStyle() override;
	IStyleConstPtr GetFillStyle()const override;

	IGroupShapePtr GetGroup() override;
	IGroupShapeConstPtr GetGroup() const override;

	size_t GetShapesCount()const override;
	void InsertShape(const std::shared_ptr<IShape> & shape) override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;

	void Draw(ICanvas & canvas) override;

private:
	IStylePtr CalculateFillStyle()const;
	ILineStylePtr CalculateOutlineStyle()const;

	std::vector<std::shared_ptr<IShape>> m_shapes;
};

