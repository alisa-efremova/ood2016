#pragma once
#include "stdafx.h"

using namespace std;

class QuackBehavior
{
public:
	void static Quack()
	{
		cout << "Quack quack!" << endl;
	}

	void static Squeak()
	{
		cout << "Squeak!" << endl;
	}

	void static MuteQuack()
	{
	}
};