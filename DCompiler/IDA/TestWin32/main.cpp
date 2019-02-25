#include <iostream>
#include <string>
#include <vector>
#include "lib.h"



void main()
{

        TestA a;
        for(int i = 0; i <10; i++)
        {
            int* data = new int;
            *data = i;
            a.add(data);

        }

        int dd;
      /*  std::cin >>dd;*/
        a.clearAll();

		std::cout << "test win32 " << std::endl;
		
		std::vector<std::string> infos;
		for(int i = 0; i < 20; i++)
		{
			infos.push_back(std::to_string(Add(i,+100)));
		}
		
		std::cout << "output info" << std::endl;

        std::string str = a.getInfo(15,100,"abceefgh");
        std::cout <<str<< std::endl;
}