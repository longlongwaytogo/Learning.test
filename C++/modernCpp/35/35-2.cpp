//35-2
#include <iostream>

template<class ...Args>
void foo(Args ...arg){
    (std::cout <<... << arg) <<std::endl; 
}

int main()

{
	unsigned int x = 8;
	foo(); //
	foo(1);//
	foo(1,11.7);
	foo(1,11.7,x);
	
	
}