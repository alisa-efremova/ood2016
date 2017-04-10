#include "stdafx.h"
#include "GroupShape.h"
#include <algorithm>


using namespace std;

shared_ptr<IGroupShape> CGroupShape::GetGroup()
{
	return make_shared<CGroupShape>(*this);
}

shared_ptr<const IGroupShape> CGroupShape::GetGroup() const
{
	return make_shared<CGroupShape>(*this);
}

size_t CGroupShape::GetShapesCount() const
{
	return m_shapes.size();
}

void CGroupShape::InsertShape(const shared_ptr<IShape> & shape, size_t position)
{
	m_shapes.push_back(shape);
	//m_shapes.at(position) = shape;
}

shared_ptr<IShape> CGroupShape::GetShapeAtIndex(size_t index)
{
	return m_shapes.at(index);
}

void CGroupShape::RemoveShapeAtIndex(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw out_of_range("Index is out of range");
	}

	auto it = m_shapes.begin();
	advance(it, index);
	m_shapes.erase(it);
}

void CGroupShape::Draw(ICanvas & canvas)
{
	for (auto & shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

RectD CGroupShape::GetFrame() const
{
	double minX = numeric_limits<double>::infinity();
	double minY = numeric_limits<double>::infinity();
	double maxX = -numeric_limits<double>::infinity();
	double maxY = -numeric_limits<double>::infinity();

	for (auto const& shape : m_shapes)
	{
		auto const& frame = shape->GetFrame();
		minX = min(minX, frame.left);
		minY = min(minY, frame.top);
		maxX = max(maxX, frame.left + frame.width);
		maxY = max(maxY, frame.top + frame.height);
	}

	return {minX, minY, maxX - minX, maxY - minY};
}

void CGroupShape::SetFrame(const RectD & rect)
{
	auto oldFrame = GetFrame();
	for (auto & shape : m_shapes)
	{
		auto shapeFrame = shape->GetFrame();
		shapeFrame.left = rect.left + (shapeFrame.left - oldFrame.left) / oldFrame.width * rect.width;
		shapeFrame.top = rect.top + (shapeFrame.top - oldFrame.top) / oldFrame.height * rect.height;
		shapeFrame.width *= rect.width / oldFrame.width;
		shapeFrame.height *= rect.height / oldFrame.height;
		shape->SetFrame(shapeFrame);
	}
}

void CGroupShape::SetOutlineStyle(const shared_ptr<ILineStyle> & style)
{
	for (auto & shape : m_shapes)
	{
		shape->SetOutlineStyle(style);
	}
}

ILineStyle & CGroupShape::GetOutlineStyle()
{
	return m_tmpStyle;
}

const ILineStyle & CGroupShape::GetOutlineStyle() const
{
	return m_tmpStyle;
}

void CGroupShape::SetFillStyle(const shared_ptr<IStyle> & style)
{
	for (auto & shape : m_shapes)
	{
		shape->SetFillStyle(style);
	}
}

IStyle & CGroupShape::GetFillStyle()
{
	return m_tmpStyle;

}

const IStyle & CGroupShape::GetFillStyle() const
{
	return m_tmpStyle;

}
