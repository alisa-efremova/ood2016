#include "stdafx.h"
#include "Coffee.h"
#include "Tea.h"
#include "Milkshake.h"

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

	auto standardLatte = CLatte(CoffeePortionSize::STANDARD);
	BOOST_CHECK_EQUAL(standardLatte.GetDescription(), "Latte");
	BOOST_CHECK_EQUAL(standardLatte.GetCost(), 90);

	auto doubleLatte = CLatte(CoffeePortionSize::DOUBLE);
	BOOST_CHECK_EQUAL(doubleLatte.GetDescription(), "Double Latte");
	BOOST_CHECK_EQUAL(doubleLatte.GetCost(), 130);
}

BOOST_AUTO_TEST_CASE(TestCapuccinoConstruction)
{
	auto capuccino = CCapuccino();
	BOOST_CHECK_EQUAL(capuccino.GetDescription(), "Capuccino");
	BOOST_CHECK_EQUAL(capuccino.GetCost(), 80);

	auto standardCapuccion = CCapuccino(CoffeePortionSize::STANDARD);
	BOOST_CHECK_EQUAL(standardCapuccion.GetDescription(), "Capuccino");
	BOOST_CHECK_EQUAL(standardCapuccion.GetCost(), 80);

	auto doubleCapuccino = CCapuccino(CoffeePortionSize::DOUBLE);
	BOOST_CHECK_EQUAL(doubleCapuccino.GetDescription(), "Double Capuccino");
	BOOST_CHECK_EQUAL(doubleCapuccino.GetCost(), 120);
}

BOOST_AUTO_TEST_CASE(TestTeaConstruction)
{
	auto tea = CTea();
	BOOST_CHECK_EQUAL(tea.GetDescription(), "Black Tea");
	BOOST_CHECK_EQUAL(tea.GetCost(), 30);

	auto blackTea = CTea(TeaSort::BLACK);
	BOOST_CHECK_EQUAL(blackTea.GetDescription(), "Black Tea");
	BOOST_CHECK_EQUAL(blackTea.GetCost(), 30);

	auto greenTea = CTea(TeaSort::GREEN);
	BOOST_CHECK_EQUAL(greenTea.GetDescription(), "Green Tea");
	BOOST_CHECK_EQUAL(greenTea.GetCost(), 30);

	auto whiteTea = CTea(TeaSort::WHITE);
	BOOST_CHECK_EQUAL(whiteTea.GetDescription(), "White Tea");
	BOOST_CHECK_EQUAL(whiteTea.GetCost(), 30);

	auto yellowTea = CTea(TeaSort::YELLOW);
	BOOST_CHECK_EQUAL(yellowTea.GetDescription(), "Yellow Tea");
	BOOST_CHECK_EQUAL(yellowTea.GetCost(), 30);
}

BOOST_AUTO_TEST_CASE(TestMilkshakeConstruction)
{
	auto milkshake = CMilkshake();
	BOOST_CHECK_EQUAL(milkshake.GetDescription(), "Milkshake");
	BOOST_CHECK_EQUAL(milkshake.GetCost(), 60);

	auto standardMilkshake = CMilkshake(MilkshakePortionSize::STANDARD);
	BOOST_CHECK_EQUAL(milkshake.GetDescription(), "Milkshake");
	BOOST_CHECK_EQUAL(milkshake.GetCost(), 60);

	auto smallMilkshake = CMilkshake(MilkshakePortionSize::SMALL);
	BOOST_CHECK_EQUAL(smallMilkshake.GetDescription(), "Small Milkshake");
	BOOST_CHECK_EQUAL(smallMilkshake.GetCost(), 50);

	auto bigMilkshake = CMilkshake(MilkshakePortionSize::BIG);
	BOOST_CHECK_EQUAL(bigMilkshake.GetDescription(), "Big Milkshake");
	BOOST_CHECK_EQUAL(bigMilkshake.GetCost(), 80);
}