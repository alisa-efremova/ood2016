#pragma once
#include "ConstDocumentItem.h"
#include "DocumentItem_fwd.h"

class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(IParagraphPtr paragraph);
	CDocumentItem(IImagePtr image);

	// ���������� ��������� �� ��������, ���� nullptr, ���� ������� �� �������� ����������
	IParagraphPtr GetParagraph();
	// ���������� ��������� �� �����������, ���� nullptr, ���� ������� �� �������� ������������
	IImagePtr GetImage();
};
