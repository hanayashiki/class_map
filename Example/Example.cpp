#include "pch.h"
#include <iostream>
#include "../ClassMap/class_map.h"

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

class Kitty : public Cat
{
	const char * color;
public:
	Kitty(const char * color) : color(color) {}
	virtual const char * whoami() { return "kitty"; }
};
CLASS_MAP(Kitty, "black")

void get_name_of_pets(class_map::indicator & i)
{
	std::cout << class_map::get<Pet>(i)->whoami() << std::endl;
}

int main()
{
	class_map::indicator subclass1 = class_map::make_indicator<Dog>();
	class_map::indicator subclass2 = class_map::make_indicator<Cat>();
	class_map::indicator subclass3 = class_map::make_indicator<Kitty>();

	get_name_of_pets(subclass1);
	get_name_of_pets(subclass2);
	get_name_of_pets(subclass3);

	std::cin.get();
}