#pragma once
namespace fs = boost::filesystem;

class IImage
{
public:
	// Возвращает имя картинки
	virtual std::string GetName()const = 0;

	// Ширина изображения в пикселях
	virtual unsigned GetWidth()const = 0;
	// Высота изображения в пикселях
	virtual unsigned GetHeight()const = 0;

	virtual void Save(const fs::path & path)const = 0;


	// Изменяет размер изображения
	virtual void Resize(unsigned width, unsigned height) = 0;

	virtual ~IImage() = default;
};
