#include <iostream>
#include <map>
#include <string>
#include <functional>

using namespace std;

void func(int i)
{
	std::cout <<" this is func(int i):" << i <<std::endl;
}

void func1(int& i)
{
	std::cout <<" this is func1(int& i):" << i <<std::endl;
}

class biggerthanzero
{
	public: 
	biggerthanzero(int i)
	{
		std::cout <<"biggerthanzero construct" << std::endl;
	}
	int operator()(int value) const 
	{
		std::cout <<"value:" << value <<endl;
		if(value < 0) return 0;
		return value;
	}
	
};

int echovalue(int value)
{
	std::cout << value << std::endl;
	return value;
}

int max(int a, int b)
{
	if( a > b)
		return a;
	else 
		return b;
}

int main()
{
	func(10);
	//func1(10); // int 无法转换为 int&
	int a = 20;
	func1(a);
	biggerthanzero big(a);
	std::cout << big(120) << std::endl;
	
	echovalue(2001);
	
	int (*p)(int x, int y);
	p = max;
	int c = (*p)(5,20);
	std::cout << "c=" << c << endl;
	map<string, int(*)(int)> myoper;
	
	myoper.insert({"ev",echovalue});
	myoper["ev"](12);
	biggerthanzero obj(2);
	// myoper.insert({"bt",biggerthanzero(2)});
	// myoper.insert({"bt",obj});
	
	function<int(int)> f1 = echovalue;
	function<int(int)> f2 = obj;
	function<int(int)> f3 = biggerthanzero(2);
	f1(2);
	f2(3);
	f3(4);
	
	return 0;
}