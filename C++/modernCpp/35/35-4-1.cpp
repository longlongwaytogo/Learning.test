//35-4
#include <iostream>
<<<<<<< HEAD
template<class T,class ...Args>
class bar{};

bar<int,double, unsigned int> b1; // error , args not last 
=======

>>>>>>> f1f49ab1628c29a170737b076239f892af645890


// 35-3 
template<class T,class ...Args>
class bar1{};


bar1<int,double, unsigned int> b2; // ok

template<class ...Args, class T, class U = double>
void foo1( T t, U u,Args ...args)
{
	std::cout << "call foo1 " <<std::endl;
}
 
<<<<<<< HEAD
 
 // 非类型模板参数
 template<int ...Args>
 void make()
 {};
 
 
 template<int ...Args>
 class makeInt
 {
 };
  makeInt<20,3,33,34,22> mk1;
	 
 int main()
 {
	 foo1(20,32.0f,2,3,4,4,4,20.023);
	 make<1,3,3,3,20>();
	
	 return 0;
=======
 template<class T,class ...Args>
class bar{};

bar<int,double, unsigned int> b1; // error , args not last 

// template<class ...Args,class T>
 template<class T,class ...Args>
 void foo(T a, Args ...args)
 {
   (std::cout <<...<< args) <<std::endl; 

    std::cout << a << std::endl;
 }

 int main()
 {
    foo(20,2);
    return 0;
>>>>>>> f1f49ab1628c29a170737b076239f892af645890
 }