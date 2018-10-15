#pragma once
#include "pch.h"
#include <iostream>

class C : public Base {
public:
	C()
	{
	}
	virtual void Fuck() { std::cout << "C fuck\n"; }
};