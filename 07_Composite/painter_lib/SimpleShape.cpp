#include "stdafx.h"
#include "SimpleShape.h"
#include "ICanvas.h"

using namespace std;

CSimpleShape::CSimpleShape()
{
	m_fillStyle = make_shared<CStyle>();
	m_outlineStyle = make_shared<CLineStyle>(true, 0);
}

void CSimpleShape::SetOutlineStyle(const ILineStylePtr & style)
{
	m_outlineStyle = style;
}

ILineStylePtr CSimpleShape::GetOutlineStyle()
{
	return m_outlineStyle;
}

ILineStyleConstPtr CSimpleShape::GetOutlineStyle() const
{
	return m_outlineStyle;
}

void CSimpleShape::SetFillStyle(const IStylePtr & style)
{
	m_fillStyle = style;
}

IStylePtr CSimpleShape::GetFillStyle()
{
	return m_fillStyle;
}

IStyleConstPtr CSimpleShape::GetFillStyle() const
{
	return m_fillStyle;
}

IGroupShapePtr CSimpleShape::GetGroup()
{
	return nullptr;
}

IGroupShapeConstPtr CSimpleShape::GetGroup() const
{
	return nullptr;
}

void CSimpleShape::BeginDraw(ICanvas & canvas)
{
	if (m_fillStyle->IsEnabled())
	{
		canvas.BeginFill(m_fillStyle->GetColor());
	}

	if (m_outlineStyle->IsEnabled())
	{
		canvas.SetLineColor(m_outlineStyle->GetColor());
	}
}

void CSimpleShape::EndDraw(ICanvas & canvas)
{
	if (m_fillStyle->IsEnabled())
	{
		canvas.EndFill();
	}
}
