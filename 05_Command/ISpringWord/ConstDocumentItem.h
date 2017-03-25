#pragma once
#include "IParagraph.h"
#include "IImage.h"
#include "DocumentItem_fwd.h"

class CConstDocumentItem
{
public:
	CConstDocumentItem(IParagraphPtr paragraph);
	CConstDocumentItem(IImagePtr image);
	// Возвращает указатель на константное изображение, либо nullptr,
	// если элемент не является изображением
	IImageConstPtr GetImage()const;
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	IParagraphConstPtr GetParagraph()const;
	virtual ~CConstDocumentItem() = default;
protected:
	IParagraphPtr m_paragraph;
	IImagePtr m_image;
};
