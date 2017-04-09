#pragma once
class ICanvas;

class IDrawable
{
public:
	virtual void Draw(const ICanvas & canvas) = 0;

	virtual ~IDrawable() = default;
};