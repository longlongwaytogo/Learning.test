#include <iostream>
//#include <algorithm>
#include <algorithm>
#include <vector> 
#include <functional>
using namespace std;


template <class T, class U>  
void Multiply(T t, U u)  
{  
	auto v = t * u;  
	cout << "Multiply:" << t << "*" << u << "=" << v << endl;
}
		

int main()
{
	// auto 变量
	// auto a; err
	cout << "auto  变量测试：" << endl;
	auto i = 1;
	std::cout << i << std::endl;
	
	auto d = 1.0;
	std::cout << d << std::endl;

	auto str = "Hello Auto!";
	std::cout << str << std::endl;
	
	// auto 容器元素
	vector<int> iv;
	iv.push_back(12);
	auto ite = iv.begin();
	cout << ite[0] <<endl;
	
	// auto 函数指针	
	cout << "auto 函数指针测试:" << endl;
	{
		auto funcLess = less<int>();
		vector<int> ar{23,34,3,6,2};
		// less
		cout << "less of array:" << endl;
		sort (ar.begin(),ar.end(),funcLess);
		for(auto i:ar) 
		{
			cout << i << endl;
		}
		 
		// greater
		cout << "greater of array:" << endl;
		sort( ar.begin(),ar.end(),greater<int>());
		for(auto i:ar) 
		{
			cout << i << endl;
		}
	}
	 
	
	 cout << "auto template 测试:" << endl;
	 {
		 // template 
		 Multiply(2,23);
		
	 }
	 
	 
	return 0;
}