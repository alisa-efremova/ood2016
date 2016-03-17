#pragma once
#include "stdafx.h"
#include <memory>
#include <algorithm>
#include <functional>
#include "FlyBehavior.h"
#include "QuackBehavior.h"
#include "DanceBehavior.h"

using namespace std;

class Duck
{
public:
	Duck(function<void()> fly, function<void()> quack, function<void()> dance);
	virtual ~Duck();
	void Quack() const;
	void Swim();
	void Fly();
	void Dance();
	void SetFlyBehavior(function<void()> fly);
	virtual void Display() const = 0;
private:
	function<void()> m_quack;
	function<void()> m_fly;
	function<void()> m_dance;
};
