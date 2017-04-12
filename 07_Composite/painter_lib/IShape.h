#pragma once
#include "Rect.h"
#include "IDrawable.h"
#include <memory>
class IStyle;
class ILineStyle;
class IGroupShape;

typedef std::shared_ptr<IStyle> IStylePtr;
typedef std::shared_ptr<const IStyle> IStyleConstPtr;

typedef std::shared_ptr<ILineStyle> ILineStylePtr;
typedef std::shared_ptr<const ILineStyle> ILineStyleConstPtr;

typedef std::shared_ptr<IGroupShape> IGroupShapePtr;
typedef std::shared_ptr<const IGroupShape> IGroupShapeConstPtr;

class IShape : public IDrawable
{
public:
	virtual RectD GetFrame()const = 0;
	virtual void SetFrame(const RectD & rect) = 0;

	virtual void SetOutlineStyle(const ILineStylePtr & style) = 0;
	virtual ILineStylePtr GetOutlineStyle() = 0;
	virtual ILineStyleConstPtr GetOutlineStyle()const = 0;

	virtual void SetFillStyle(const IStylePtr & style) = 0;
	virtual IStylePtr GetFillStyle() = 0;
	virtual IStyleConstPtr GetFillStyle()const = 0;

	virtual IGroupShapePtr GetGroup() = 0;
	virtual IGroupShapeConstPtr GetGroup() const = 0;

	virtual ~IShape() = default;
};