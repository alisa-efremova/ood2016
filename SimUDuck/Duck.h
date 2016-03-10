#pragma once
#include "stdafx.h"
#include <memory>
#include "IFlyBehavior.h"
#include "IQuackBehavior.h"
#include "IDanceBehavior.h"

using namespace std;

class Duck
{
public:
	Duck(unique_ptr<IFlyBehavior> && flyBehavior, unique_ptr<IQuackBehavior> && quackBehavior, unique_ptr<IDanceBehavior> && danceBehavior);
	virtual ~Duck();
	void Quack() const;
	void Swim();
	void Fly();
	void Dance();
	void SetFlyBehavior(unique_ptr<IFlyBehavior> && flyBehavior);
	virtual void Display() const = 0;

private:
	unique_ptr<IFlyBehavior> m_flyBehavior;
	unique_ptr<IQuackBehavior> m_quackBehavior;
	unique_ptr<IDanceBehavior> m_danceBehavior;
};
