﻿#include "stdafx.h"
#include "Beverages.h"
#include "Condiments.h"

using namespace std;

/*
Возвращает функцию, декорирующую напиток определенной добавкой

Параметры шаблона: 
	Condiment - класс добавки, конструктор которого в качестве первого аргумента
				принимает IBeveragePtr&& оборачиваемого напитка
	Args - список типов прочих параметров конструктора (возможно, пустой)
*/
template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&...args)
{
	// Возвращаем функцию, декорирующую напиток, переданный ей в качестве аргумента
	// Дополнительные аргументы декоратора, захваченные лямбда-функцией, передаются
	// конструктору декоратора через make_unique
	return [=](auto && b) {
		// Функции make_unique передаем b вместе со списком аргументов внешней функции
		return make_unique<Condiment>(forward<decltype(b)>(b), args...);
	};
}

template <typename Component, typename Decorator>
auto operator << (Component && component, const Decorator & decorate)
{
	return decorate(forward<Component>(component));
}

int main()
{
	{
		// Наливаем чашечку латте
		auto latte = make_unique<CLatte>();
		// добавляем корицы
		auto cinnamon = make_unique<CCinnamon>(move(latte));
		// добавляем пару долек лимона
		auto lemon = make_unique<CLemon>(move(cinnamon), 2);
		// добавляем пару кубиков льда
		auto iceCubes = make_unique<CIceCubes>(move(lemon), 2, IceCubeType::Dry);
		// добавляем 2 грамма шоколадной крошки
		auto beverage = make_unique<CChocolateCrumbs>(move(iceCubes), 2);

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	{
		auto beverage =
			make_unique<CChocolateCrumbs>(			// Внешний слой: шоколадная крошка
				make_unique<CIceCubes>(				// | под нею - кубики льда
					make_unique<CLemon>(			// | | еще ниже лимон
						make_unique<CCinnamon>(		// | | | слоем ниже - корица
							make_unique<CLatte>()),	// | | |   в самом сердце - Латте
						2),							// | | 2 дольки лимона
					2, IceCubeType::Dry),			// | 2 кубика сухого льда
				2);									// 2 грамма шоколадной крошки

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	// Подробнее рассмотрим работу MakeCondiment и оператора <<
	{
		// lemon - функция, добавляющая "2 дольки лимона" к любому напитку
		auto lemon2 = MakeCondiment<CLemon>(2);
		// iceCubes - функция, добавляющая "3 кусочка льда" к любому напитку
		auto iceCubes3 = MakeCondiment<CIceCubes>(3, IceCubeType::Water);
		
		auto tea = make_unique<CTea>();

		// декорируем чай двумя дольками лимона и тремя кусочками льда
		auto lemonIceTea = iceCubes3(lemon2(move(tea)));	
		/* Предыдущая строка выполняет те же действия, что и следующий код:
		auto lemonIceTea = 
			make_unique<CIceCubes>(
				make_unique<CLemon>(
					move(tea), 
					2), 
				2, IceCubeType::Water);
		*/
		
		auto oneMoreLemonIceTea =
			make_unique<CTea>()	// Берем чай
			<< MakeCondiment<CLemon>(2)	// добавляем пару долек лимона
			<< MakeCondiment<CIceCubes>(3, IceCubeType::Water); // и 3 кубика льда
		/*
		Предыдущая конструкция делает то же самое, что и следующая:
		auto oneMoreLemonIceTea =
			MakeCondiment<CIceCubes>(3, IceCubeType::Water)(
				MakeCondiment<CLemon>(2)(make_unique<CTea>())
				);
		*/
	}

	// Аналог предыдущего решения с добавкой синтаксического сахара
	// обеспечиваемого операторами << и функцией MakeCondiment
	{
		auto beverage = 
			make_unique<CLatte>()							// Наливаем чашечку латте,
			<< MakeCondiment<CCinnamon>()					// оборачиваем корицей,
			<< MakeCondiment<CLemon>(2)						// добавляем пару долек лимона
			<< MakeCondiment<CIceCubes>(2, IceCubeType::Dry)// брасаем пару кубиков сухого льда
			<< MakeCondiment<CChocolateCrumbs>(2);			// посыпаем шоколадной крошкой

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	{
		auto beverage = 
			make_unique<CMilkshake>()					// Наливаем молочный коктейль
			<< MakeCondiment<CSyrup>(SyrupType::Maple)	// заливаем кленовым сиропом
			<< MakeCondiment<CCoconutFlakes>(8);		// посыпаем кокосовой стружкой

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}
}
