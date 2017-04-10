#pragma once
#include "IGroupShape.h"
#include <vector>

class CGroupShape : public IGroupShape
{
public:
#if 0
	RectD GetFrame()const override;
	void SetFrame(const RectD & rect) override;

	void SetOutlineStyle(std::unique_ptr<ILineStyle> && style) override;
	ILineStyle & GetOutlineStyle() override;
	const ILineStyle & GetOutlineStyle()const override;

	void SetFillStyle(std::unique_ptr<IStyle> && style) override;
	IStyle & GetFillStyle() override;
	const IStyle & GetFillStyle()const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	size_t GetShapesCount()const override;
	void InsertShape(const std::shared_ptr<IShape> & shape, size_t position = std::numeric_limits<size_t>::max()) override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
#endif
};

