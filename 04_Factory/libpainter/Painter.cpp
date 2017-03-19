#include "stdafx.h"
#include "Painter.h"
#include "ICanvas.h"
#include "PictureDraft.h"

using namespace std;

void CPainter::DrawPicture(const CPictureDraft & draft, ICanvas & canvas)
{
	canvas.StartDrawing();
	for (auto it = draft.begin(); it < draft.end(); it++)
	{
		it->Draw(canvas);
	}
	canvas.CompleteDrawing();
}
