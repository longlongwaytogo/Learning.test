#include <iostream>

template <class T, class U>
T baz(T t,U u)
{
	std::cout << t << ": " << u << std::endl;
	return t;
}

template<class ...Args>
void foo(Args... args)
{
	
}
template<class ...Args>
class Bar
{
public:
	Bar(Args ...args)
	{
		foo(baz(&args,args) ...);
	}
};

int main()
{
	Bar<int,double,unsigned int> b(20,302.0,30);

	return 0;
}