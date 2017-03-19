#pragma once
class CPictureDraft;
class ICanvas;

class CPainter
{
public:
	void DrawPicture(const CPictureDraft & draft, ICanvas & canvas);
};

