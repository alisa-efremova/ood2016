#pragma once

class IImage
{
public:
#if 0
	// ���������� ���� ������������ �������� ���������
	virtual std::string GetPath()const = 0;

	// ������ ����������� � ��������
	virtual int GetWidth()const = 0;
	// ������ ����������� � ��������
	virtual int GetHeight()const = 0;

	// �������� ������ �����������
	virtual void Resize(int width, int height) = 0;
#endif
	virtual ~IImage() = default;
};
