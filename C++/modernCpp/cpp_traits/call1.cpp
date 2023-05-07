//call1.cpp
#include <iostream>

template<typename T>
void func(T const& v)
{
	std::cout <<"func1:" << v << std::endl;
}

void call1()
{
	func(1);
	func(0.1);
}
