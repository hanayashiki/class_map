# class_map

## Overall 
This is a very easy tool for C++, requiring at least C++14 standard, and should work on VS2017.

It can allow us to pass indicator of type information as a immutable object, for example:

We define a base type `Pet`

```
class Pet
{
public:
	virtual const char * whoami() { return "pet"; }
};
```

which has 2 subclasses: 

```
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
```

Notice that the macro `CLASS_MAP(type)` belongs to `class_map.h`. It will tell `class_map.h` to record the class, and later we can use `class_map::indicator` for the class.

See how we use `class_map::indicator`:

```
void get_name_of_pets(class_map::indicator & i)
{
	std::cout << class_map::get<Pet>(i)->whoami() << std::endl;
}

int main()
{
	class_map::indicator subclass1 = class_map::make_indicator<Dog>();
	class_map::indicator subclass2 = class_map::make_indicator<Cat>();

	get_name_of_pets(subclass1);
	get_name_of_pets(subclass2);

	std::cin.get();
}
```

from this example, we see we can dynamically make `class_map::indicator` for any class that is mapped by macro `CLASS_MAP(type)` in a very convenient fashion. 

To explain, 

```
class_map::indicator subclass1 = class_map::make_indicator<Dog>();
```

This makes a indicator of class `Dog` and stores it in object `class_map::indicator`. The same applies to the second statement.

And we can pass objects of `class_map::indicator` to a function `get_name_of_pets`, which is a simple wrapper of 

```
class_map::get<Pet>(class_map::indicator & i)
```

This function `class_map::get<Type>` will retrieve the object instance by indicator `i`, and returns the pointer of the object, and cast it to `Pet*`. So we can treat the return value as a pointer to the instance.

## How to use

Very simple. Find `class_map.h` and `class_map.c`, make sure you include `class_map.h` and compile `class_map.c`, then you can use them.

To use `CLASS_MAP`, it is suggested that you should place it in `.c` files along with other method/static definitions, which guarantees no symbol is defined twice.

For VS2017 example, see `Example/`

```
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
CLASS_MAP(Dog) // Maps object of class Dog

class Cat : public Pet
{
public:
	virtual const char * whoami() { return "cat"; }
};
CLASS_MAP(Cat) // Maps object of class Cat

class Kitty : public Cat
{
	const char * color;
public:
	Kitty(const char * color) : color(color) {}
	virtual const char * whoami() { return "kitty"; }
};
CLASS_MAP(Kitty, "black") // You can also map with static parameters.

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
```

```
dog
cat
kitty
```


