#include <iostream>

template<class ...Args>
void foo(Args ...args)
{
	
}

template<class ...Args>
class bar {
	bar(Args ...args){
		foo(args...);
	}
};


int main()
{
	std::cout <<"test 35!" << std::endl;
}