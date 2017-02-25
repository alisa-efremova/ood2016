#pragma once
#include "stdafx.h"
#include <memory>
#include <algorithm>
#include <functional>
#include "FlyBehavior.h"
#include "QuackBehavior.h"
#include "DanceBehavior.h"

class Duck
{
public:
	Duck(const std::function<void()>& fly, const std::function<void()>& quack, const std::function<void()>& dance);
	virtual ~Duck();
	void Quack() const;
	void Swim();
	void Fly();
	void Dance();
	void SetFlyBehavior(std::function<void()> fly);
	virtual void Display() const = 0;
private:
	std::function<void()> m_quack;
	std::function<void()> m_fly;
	std::function<void()> m_dance;
};
