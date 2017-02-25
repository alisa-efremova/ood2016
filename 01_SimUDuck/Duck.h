#pragma once
#include "stdafx.h"
#include <memory>
#include "IFlyBehavior.h"
#include "IQuackBehavior.h"
#include "IDanceBehavior.h"

class Duck
{
public:
	Duck(std::unique_ptr<IFlyBehavior> && flyBehavior, std::unique_ptr<IQuackBehavior> && quackBehavior, std::unique_ptr<IDanceBehavior> && danceBehavior);
	virtual ~Duck();
	void Quack() const;
	void Swim();
	void Fly();
	void Dance();
	void SetFlyBehavior(std::unique_ptr<IFlyBehavior> && flyBehavior);
	virtual void Display() const = 0;

private:
	std::unique_ptr<IFlyBehavior> m_flyBehavior;
	std::unique_ptr<IQuackBehavior> m_quackBehavior;
	std::unique_ptr<IDanceBehavior> m_danceBehavior;
};
