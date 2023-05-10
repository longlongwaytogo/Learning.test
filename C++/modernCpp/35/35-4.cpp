//35-4
#include <iostream>



// 35-3 
template<class T,class ...Args>
class bar1{};

bar1<int,double, unsigned int> b2; // ok

 
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
 }