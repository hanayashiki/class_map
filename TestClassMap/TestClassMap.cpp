// TestClassMap.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "../ClassMap/class_map.h"
#include "classC.h"

#include <iostream>

class A : public Base {
public:
	A()
	{
	}
	A* Instance()
	{
		return new A();
	}
	virtual void Fuck() { std::cout << "A fuck\n"; }
};
CLASS_MAP(A)

class B : public Base {
public:
	B()
	{
	}
	virtual void Fuck() { std::cout << "B fuck\n"; }
};
CLASS_MAP(B)

class Pet
{
public:
	virtual const char * whoami() { return "pet"; }
};

class Dog : public Pet
{
public:
	virtual const char * whoami() { return "dog"; }
};
CLASS_MAP(Dog)

class Cat : public Pet
{
public:
	virtual const char * whoami() { return "cat"; }
};
CLASS_MAP(Cat)

void basic_test1()
{
	class_map::get<A>()->Fuck();
	class_map::get<B>()->Fuck();

	auto subclass1 = class_map::make_indicator<A>();
	class_map::get<Base>(subclass1)->Fuck();

	auto subclass2 = class_map::make_indicator<B>();
	class_map::get<Base>(subclass2)->Fuck();

	auto subclass3 = class_map::make_indicator<C>();
	class_map::get<Base>(subclass3)->Fuck();
}

void get_name_of_pets(class_map::indicator & i)
{
	std::cout << class_map::get<Pet>(i)->whoami() << std::endl;
}

int main()
{
	class_map::indicator subclass1 = class_map::make_indicator<Dog>();
	class_map::indicator subclass2 = class_map::make_indicator<Cat>();

	basic_test1();
	get_name_of_pets(subclass1);
	get_name_of_pets(subclass2);

	std::cin.get();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
