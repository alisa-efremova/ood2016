#pragma once
#include "ConstDocumentItem.h"
#include "DocumentItem_fwd.h"

class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(IParagraphPtr paragraph);
	CDocumentItem(IImagePtr image);

	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	IParagraphPtr GetParagraph();
	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	IImagePtr GetImage();
};
