// 35-3 
template<class ...Args>
class bar{};

#include <iostream>

int main()
{
	bar<> b1;
	bar<int> b2;
	bar<int,double> b3;
	bar<int,double, unsigned int> b4;
	bar<double,float> b5;
	
}