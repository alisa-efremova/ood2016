#include "stdafx.h"
#include "GroupShape.h"

using namespace std;
#if 0
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
	m_shapes.at(position) = shape;
}

shared_ptr<IShape> CGroupShape::GetShapeAtIndex(size_t index)
{
	return shared_ptr<IShape>();
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

RectD CGroupShape::GetFrame() const
{
	return RectD();
}

void CGroupShape::SetFrame(const RectD & rect)
{
}

void CGroupShape::SetOutlineStyle(unique_ptr<ILineStyle> && style)
{
	for (auto & shape : m_shapes)
	{
		shape->SetOutlineStyle(move(style));
	}
}

ILineStyle & CGroupShape::GetOutlineStyle()
{
	if (m_shapes.empty())
	{

	}
}

const ILineStyle & CGroupShape::GetOutlineStyle() const
{
	// TODO: insert return statement here
}

void CGroupShape::SetFillStyle(unique_ptr<IStyle> && style)
{
	for (auto & shape : m_shapes)
	{
		shape->SetFillStyle(move(style));
	}
}

IStyle & CGroupShape::GetFillStyle()
{
	// TODO: insert return statement here
}

const IStyle & CGroupShape::GetFillStyle() const
{
	// TODO: insert return statement here
}

#endif