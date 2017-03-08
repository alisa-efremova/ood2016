#include "stdafx.h"
#include "Coffee.h"
#include "Tea.h"
#include "Milkshake.h"
#include "Condiments.h"

using namespace std;

BOOST_AUTO_TEST_CASE(TestCoffeeConstruction)
{
	auto coffee = CCoffee();
	BOOST_CHECK_EQUAL(coffee.GetDescription(), "Coffee");
	BOOST_CHECK_EQUAL(coffee.GetCost(), 60);
}

BOOST_AUTO_TEST_CASE(TestLatteConstruction)
{
	auto latte = CLatte();
	BOOST_CHECK_EQUAL(latte.GetDescription(), "Latte");
	BOOST_CHECK_EQUAL(latte.GetCost(), 90);

	auto standardLatte = CLatte(CoffeePortionSize::Standard);
	BOOST_CHECK_EQUAL(standardLatte.GetDescription(), "Latte");
	BOOST_CHECK_EQUAL(standardLatte.GetCost(), 90);

	auto doubleLatte = CLatte(CoffeePortionSize::Double);
	BOOST_CHECK_EQUAL(doubleLatte.GetDescription(), "Double Latte");
	BOOST_CHECK_EQUAL(doubleLatte.GetCost(), 130);
}

BOOST_AUTO_TEST_CASE(TestCapuccinoConstruction)
{
	auto capuccino = CCapuccino();
	BOOST_CHECK_EQUAL(capuccino.GetDescription(), "Capuccino");
	BOOST_CHECK_EQUAL(capuccino.GetCost(), 80);

	auto standardCapuccion = CCapuccino(CoffeePortionSize::Standard);
	BOOST_CHECK_EQUAL(standardCapuccion.GetDescription(), "Capuccino");
	BOOST_CHECK_EQUAL(standardCapuccion.GetCost(), 80);

	auto doubleCapuccino = CCapuccino(CoffeePortionSize::Double);
	BOOST_CHECK_EQUAL(doubleCapuccino.GetDescription(), "Double Capuccino");
	BOOST_CHECK_EQUAL(doubleCapuccino.GetCost(), 120);
}

BOOST_AUTO_TEST_CASE(TestTeaConstruction)
{
	auto tea = CTea();
	BOOST_CHECK_EQUAL(tea.GetDescription(), "Black Tea");
	BOOST_CHECK_EQUAL(tea.GetCost(), 30);

	auto blackTea = CTea(TeaSort::Black);
	BOOST_CHECK_EQUAL(blackTea.GetDescription(), "Black Tea");
	BOOST_CHECK_EQUAL(blackTea.GetCost(), 30);

	auto greenTea = CTea(TeaSort::Green);
	BOOST_CHECK_EQUAL(greenTea.GetDescription(), "Green Tea");
	BOOST_CHECK_EQUAL(greenTea.GetCost(), 30);

	auto whiteTea = CTea(TeaSort::White);
	BOOST_CHECK_EQUAL(whiteTea.GetDescription(), "White Tea");
	BOOST_CHECK_EQUAL(whiteTea.GetCost(), 30);

	auto yellowTea = CTea(TeaSort::Yellow);
	BOOST_CHECK_EQUAL(yellowTea.GetDescription(), "Yellow Tea");
	BOOST_CHECK_EQUAL(yellowTea.GetCost(), 30);
}

BOOST_AUTO_TEST_CASE(TestMilkshakeConstruction)
{
	auto milkshake = CMilkshake();
	BOOST_CHECK_EQUAL(milkshake.GetDescription(), "Milkshake");
	BOOST_CHECK_EQUAL(milkshake.GetCost(), 60);

	auto standardMilkshake = CMilkshake(MilkshakePortionSize::Standard);
	BOOST_CHECK_EQUAL(milkshake.GetDescription(), "Milkshake");
	BOOST_CHECK_EQUAL(milkshake.GetCost(), 60);

	auto smallMilkshake = CMilkshake(MilkshakePortionSize::Small);
	BOOST_CHECK_EQUAL(smallMilkshake.GetDescription(), "Small Milkshake");
	BOOST_CHECK_EQUAL(smallMilkshake.GetCost(), 50);

	auto bigMilkshake = CMilkshake(MilkshakePortionSize::Big);
	BOOST_CHECK_EQUAL(bigMilkshake.GetDescription(), "Big Milkshake");
	BOOST_CHECK_EQUAL(bigMilkshake.GetCost(), 80);
}

BOOST_AUTO_TEST_CASE(TestBeverageWithCream)
{
	auto coffeeWithCream = CCream(move(make_unique<CCoffee>()));
	BOOST_CHECK_EQUAL(coffeeWithCream.GetDescription(), "Coffee, Cream");
	BOOST_CHECK_EQUAL(coffeeWithCream.GetCost(), 85);
}

BOOST_AUTO_TEST_CASE(TestBeverageWithChocolate)
{
	auto coffeeWithChocolate = CChocolate(move(make_unique<CCoffee>()));
	BOOST_CHECK_EQUAL(coffeeWithChocolate.GetDescription(), "Coffee, Pieces of chocolate x 1");
	BOOST_CHECK_EQUAL(coffeeWithChocolate.GetCost(), 70);

	auto coffeeWith5ChocolatePieces = CChocolate(move(make_unique<CCoffee>()), 5);
	BOOST_CHECK_EQUAL(coffeeWith5ChocolatePieces.GetDescription(), "Coffee, Pieces of chocolate x 5");
	BOOST_CHECK_EQUAL(coffeeWith5ChocolatePieces.GetCost(), 110);

	auto coffeeWith6ChocolatePieces = CChocolate(move(make_unique<CCoffee>()), 6);
	BOOST_CHECK_EQUAL(coffeeWith6ChocolatePieces.GetDescription(), "Coffee, Pieces of chocolate x 5");
	BOOST_CHECK_EQUAL(coffeeWith6ChocolatePieces.GetCost(), 110);
}

BOOST_AUTO_TEST_CASE(TestBeverageWithLiquor)
{
	auto coffeeWithChocolateLiquor = CLiquor(move(make_unique<CCoffee>()), LiquorType::Chocolate);
	BOOST_CHECK_EQUAL(coffeeWithChocolateLiquor.GetDescription(), "Coffee, Chocolate liquor");
	BOOST_CHECK_EQUAL(coffeeWithChocolateLiquor.GetCost(), 100);

	auto coffeeWithNutLiquor = CLiquor(move(make_unique<CCoffee>()), LiquorType::Nut);
	BOOST_CHECK_EQUAL(coffeeWithNutLiquor.GetDescription(), "Coffee, Nut liquor");
	BOOST_CHECK_EQUAL(coffeeWithNutLiquor.GetCost(), 100);
}
