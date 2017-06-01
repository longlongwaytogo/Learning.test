#include "hello.h"
void hello()
{
	std::cout<<"hello 123!"<<std::endl;
	std::string  projectName = "testCmake";
	std::cout<<" project name:"<<projectName<<std::endl;
}

void hello(const char* name)
{

#ifdef ENALBE_DEBUG
	std::cout << " Enable debug:hello_DLL: name 23423" << ":" << name << std::endl;
#else
	std::cout<< "hello_DLL: name 23423" <<":"<<name<<std::endl;
#endif
}