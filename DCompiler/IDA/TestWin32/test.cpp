#include <iostream>
class TestA
{
	public:
int a1;
int a2;
double a3;

int getA1()
{
	return a1;
}
int getA2()
{
	return a2;
}

};

void main()
{
	TestA a;
	a.a1 = 10;
	a.a2 =32;
	a.a3 = 2.2;
	std::cout << "this is test" << std::endl;
}