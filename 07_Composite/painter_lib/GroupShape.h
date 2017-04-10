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

	void SetOutlineStyle(const std::shared_ptr<ILineStyle> & style) override;
	ILineStyle & GetOutlineStyle() override;
	const ILineStyle & GetOutlineStyle()const override;

	void SetFillStyle(const std::shared_ptr<IStyle> & style) override;
	IStyle & GetFillStyle() override;
	const IStyle & GetFillStyle()const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	size_t GetShapesCount()const override;
	void InsertShape(const std::shared_ptr<IShape> & shape, size_t position = std::numeric_limits<size_t>::max()) override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;

	void Draw(ICanvas & canvas) override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
	CLineStyle m_tmpStyle = CLineStyle();
};

