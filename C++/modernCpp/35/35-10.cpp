#include <iostream>
// size...

template<class ...Args> void foo(Args ...args)
{
	std::cout <<"foo sizeof...(args)=" << sizeof...(args) << std::endl;
}

template <class ...Args>
class bar
{
	public:
	bar(){
		std::cout << "bar sizeof...(args)=" << sizeof...(Args) << std::endl;
	}
};
	
	
template<class T>
T sum(T arg)
{
	return arg;
	
}

template<class T1, class ...Args>
auto sum(T1 arg1, Args... args)
{
		return arg1 + sum(args...);
}

int main()
{
	foo();
	foo(1,3,3);
	bar b1;
	bar<int,double>b2;
	
	std::cout << "sum:" << sum(1,30,50.0) << std::endl;
	return 0;
	
}