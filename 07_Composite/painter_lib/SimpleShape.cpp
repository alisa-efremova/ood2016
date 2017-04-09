#include "stdafx.h"
#include "SimpleShape.h"

using namespace std;

void CSimpleShape::SetOutlineStyle(unique_ptr<ILineStyle> && style)
{
	m_outlineStyle = move(style);
}

ILineStyle & CSimpleShape::GetOutlineStyle()
{
	return *m_outlineStyle;
}

const ILineStyle & CSimpleShape::GetOutlineStyle() const
{
	return *m_outlineStyle;
}

void CSimpleShape::SetFillStyle(unique_ptr<IStyle> && style)
{
	m_fillStyle = move(style);
}

IStyle & CSimpleShape::GetFillStyle()
{
	return *m_fillStyle;
}

const IStyle & CSimpleShape::GetFillStyle() const
{
	return *m_fillStyle;
}

std::shared_ptr<IGroupShape> CSimpleShape::GetGroup()
{
	return nullptr;
}

std::shared_ptr<const IGroupShape> CSimpleShape::GetGroup() const
{
	return nullptr;
}
