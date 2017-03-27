#pragma once
namespace fs = boost::filesystem;

class IImage
{
public:
	// ���������� ���� ������������ �������� ���������
	virtual fs::path GetPath()const = 0;

	// ������ ����������� � ��������
	virtual unsigned GetWidth()const = 0;
	// ������ ����������� � ��������
	virtual unsigned GetHeight()const = 0;

	virtual void Save(const fs::path & path)const = 0;


	// �������� ������ �����������
	virtual void Resize(unsigned width, unsigned height) = 0;

	virtual ~IImage() = default;
};
