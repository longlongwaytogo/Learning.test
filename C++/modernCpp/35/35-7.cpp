#include <iostream>

int add(int a,int b)
{
	return a + b;
}
int sub(int a, int b)
{
	return a - b;
}

// 传递多组指针类型参数的函数模板
template <class ...Args>
void foo(Args (*...args)(int,int))
{
	int tmp[] = { (std::cout << args(7,5)<<std::endl, 0) ...};
}

 

int main()
{
	foo(add,sub);
	
	return 0;
}