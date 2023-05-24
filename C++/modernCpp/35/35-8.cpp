#include <iostream>

class base1
{
	public:
	base1(){
		
		std::cout<<"construct base1:"<<std::endl;
	};
	base1(const base1&){
		
		std::cout<<"construct base1:---"<<std::endl;
	};
};

class base2
{
	public:
	base2(){
		
		std::cout<<"construct base2:"<<std::endl;
	}
	base2(const base2&){
		
		std::cout<<"construct base2:---"<<std::endl;
	}
};


template<class ...Args>
class derived :public Args...
{
	public:
	derived(const Args ...args):Args(args) ...{}
	
};

// 可变参数为类模板的模板函数
template<template<class ...> class ...Args>
class bar : public Args<int,double>...
{
	public:
	bar(const Args<int,double>...args):Args<int,double>(args)...{}
};

template<class ...Args>
class f1
{
	public:
	f1(Args ...args)
	{
		std::cout<<"f1:"<<std::endl;
	}
};

template<class ...Args>
class f2
{
	public:
	f2(Args ...args)
	{
		std::cout<<"f2:"<<std::endl;
	}
};
int main()
{
	base1 a;
	base2 b;
	
	derived<base1,base2> d1(a,b);
	
	
	
	f1 d(20,30.0);
	f2 e(40,40.0);
	bar<f1,f2>(d,e);
	
	return 0;
}