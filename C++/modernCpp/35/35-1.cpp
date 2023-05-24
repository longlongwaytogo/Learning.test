#include <iostream>

template<class ...Args>
void foo(Args ...args)
{
	(std::cout <<... << args) <<std::endl; 
}

template<class ...Args>
class bar {
	public:
	bar()
	{}
	bar(Args ...args){
		foo(args...);
	}
};


int main()
{
	bar("test 35!",20,230,300);
	bar<int,int> b1(20,30);
	bar<float,double,int> b2(20.0f,322.023,3);
	bar<int,int> b3;
	bar<float,double,int> b4;
	
	
	std::cout <<"test" << std::endl;
}