
#include "lib.h"
#include <iostream>
#include <vector>
#include <sstream>
int Add(int a, int b)
{	
	int c = a + b;
	std::cout << " a + b ="  << c << std::endl;
	return c;
}

TestA::TestA()
{

}

TestA::~TestA()
{


}

void TestA::add(int* i)
{
    _list.push_back(i);
}

bool TestA::clearAll()
{
   for(std::vector<int*>::iterator itr = _list.begin(); itr != _list.end(); ++itr)
      delete (*itr) ;

    _list.clear();
    return 0;
}

void TestA::setName(const std::string& name)
{
    _name = name;
}

std::string  TestA::getInfo(int a, int b, const std::string& info)
{
    std::stringstream os;
    os << "a:" << a << "b:" <<b << info;
    std::string str = os.str();

    return str;

}
