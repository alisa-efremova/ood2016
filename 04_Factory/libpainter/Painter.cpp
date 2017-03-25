#include "stdafx.h"
#include "Painter.h"
#include "ICanvas.h"
#include "PictureDraft.h"

using namespace std;

void CPainter::DrawPicture(const CPictureDraft & draft, ICanvas & canvas)
{
	for (auto & shape : draft)
	{
		shape.Draw(canvas);
	}
}
