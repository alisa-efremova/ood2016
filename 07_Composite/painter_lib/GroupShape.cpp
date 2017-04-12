#include "stdafx.h"
#include "GroupShape.h"
#include <algorithm>
#include <limits>

using namespace std;

IGroupShapePtr CGroupShape::GetGroup()
{
	return make_shared<CGroupShape>(*this);
}

IGroupShapeConstPtr CGroupShape::GetGroup() const
{
	return make_shared<CGroupShape>(*this);
}

size_t CGroupShape::GetShapesCount() const
{
	return m_shapes.size();
}

void CGroupShape::InsertShape(const shared_ptr<IShape> & shape)
{
	m_shapes.push_back(shape);
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

IStylePtr CGroupShape::CalculateFillStyle() const
{
	if (m_shapes.empty())
	{
		throw runtime_error("No shapes in the group");
	}

	auto & style = m_shapes.at(0)->GetFillStyle();
	bool hasSameStyle = true;
	for (auto & shape : m_shapes)
	{
		if (shape->GetFillStyle() != style)
		{
			hasSameStyle = false;
			break;
		}
	}

	return hasSameStyle ? style : nullptr;
}

ILineStylePtr CGroupShape::CalculateOutlineStyle() const
{
	if (m_shapes.empty())
	{
		throw runtime_error("No shapes in the group");
	}

	auto & style = m_shapes.at(0)->GetOutlineStyle();
	bool hasSameStyle = true;
	for (auto & shape : m_shapes)
	{
		if (shape->GetOutlineStyle() != style)
		{
			hasSameStyle = false;
			break;
		}
	}

	return hasSameStyle ? style : nullptr;
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

void CGroupShape::SetOutlineStyle(const ILineStylePtr & style)
{
	for (auto & shape : m_shapes)
	{
		shape->SetOutlineStyle(style);
	}
}

ILineStylePtr CGroupShape::GetOutlineStyle()
{
	return CalculateOutlineStyle();
}

ILineStyleConstPtr CGroupShape::GetOutlineStyle() const
{
	return CalculateOutlineStyle();
}

void CGroupShape::SetFillStyle(const IStylePtr & style)
{
	for (auto & shape : m_shapes)
	{
		shape->SetFillStyle(style);
	}
}

IStylePtr CGroupShape::GetFillStyle()
{
	return CalculateFillStyle();

}

IStyleConstPtr CGroupShape::GetFillStyle() const
{
	return CalculateFillStyle();
}
