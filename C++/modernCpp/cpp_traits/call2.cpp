//call2
#include <iostream>

template<typename T>
void func(T const& v)
{
	std::cout <<"func2:" << v << std::endl;
}
void call2()
{
	func(2);
	func(0.2f);
	func(0.3);
}