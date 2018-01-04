#include <iostream>
#include <cassert>
using namespace std;

// C++ NULL的二义性
void F(int a) 
{
	cout << a << endl;
}

void F(int *p){  
    assert(p != NULL);  
 
    cout<< p <<endl;  
}  
 
int main() 
{
	 
	int* p = nullptr;
	int* q = NULL;
	bool equal = (p == q);// true 
	cout << "equal = (p == q):" << equal << endl;
	//int a = nullptr; // 编译失败，nullptr 不能转换为int
	F(0);
	F(NULL);
	//F(nullptr);
	return 0;
}