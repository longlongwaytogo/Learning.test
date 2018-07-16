
// test dbgview use

#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>

int main()
{
	std::cout<< "start to test dbgView:"<<"..."<< std::endl;
	
	
	int i = 0;
	while(1)
	{
		i++;
		std::cout<<"num: -" << i << std::endl;
		OutputDebugStringA("11111111111111111sss\n");
	
	
	}

	
}