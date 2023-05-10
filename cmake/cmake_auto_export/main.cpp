#include <iostream>
#include "comm.h"

int main()
{
	std::cout <<" app start!"<< std::endl;
	std::cout <<"sqrt(100.0f):"<< comm::sqrt(100.0f)<<std::endl;
	std::cout << "current system info:" <<GetSystemName()<<std::endl;
	
	comm c;
	c.setValue(102.0f);
	std::cout << "c.getValue:" << c.getValue() << std::endl;
	comm::s_val = 505.0f;
	std::cout << "comm::s_val:" << comm::s_val << std::endl;
	std::cout << "s_cval:" << s_cval << std::endl;

	//std::cout << "current system info:" << GetSystemNum()<<std::endl;

	return 0;
}
