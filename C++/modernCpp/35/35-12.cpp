#include <iostream>

template<class ...Args>
auto sum(Args ...agrs)
{
	return (agrs + ...);
}


int main()
{
	std::cout << sum(20,3.3,33,20) << std::endl;
	return 0;
}