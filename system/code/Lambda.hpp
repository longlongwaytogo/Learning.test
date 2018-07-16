// test for lambda
#ifndef __LAMBDA_INC_H__
#define __LAMBDA_INC_H__

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <boost\function.hpp>

class Test_Lambda

{
public:
	Test_Lambda()
	{
		Test();
	}
	~Test_Lambda()
	{

	}

	void Test()
	{
		std::vector<int> c{ 1,2,3,4,5,6,7 };
		int x = 5;
		c.erase(std::remove_if(c.begin(), c.end(), [x](int n) { return  n > x; }), c.end());
		//c.erase(std::remove_if(c.begin(), c.end(), [x](int n) { return n < x; }), c.end());

		std::cout << "c: ";
		for (auto i : c) {
			std::cout << i << ' ';
		}
		std::cout << '\n';

		// the type of a closure cannot be named, but can be inferred with auto
		auto func1 = [](int i) { return i + 4; };
		auto func11 = [](int i) { return i + 5;  };
		std::cout << "func1: " << func1(6) << '\n';
		std::cout << "func11: " << func11(7) << '\n';

		// like all callable objects, closures can be captured in std::function
		// (this may incur unnecessary overhead)
		boost::function<int(int)> func2 = [](int i) { return i + 4; };
		std::cout << "func2: " << func2(6) << '\n';
	
		int first = 10;
		int second = 20;
		/*auto y = [](int first, int second)
		{
			return first + second;
		};*/

		//std::cout <<"y:" <<  y << std::endl;
		//std::cout << [&first,&second](int first, int second) { return first + second; } << std::endl;
		int b = 2;
		int a = 3;
		auto func = [=, &b,&a](int c)->int {return b += a + c; };
		std::cout << func(20) << std::endl;
	/*	std::cout << func(3,2) << std::endl;*/
		{ 
			//[]() throw() { throw 5; }();
			auto x1 = [](int i) { return i; }; // OK: return type is int  
			//auto x2 = [] { return{ 1, 2 }; };  // ERROR: return type is void, deducing   
											   // return type from braced-init-list is not valid  

			int m = 0;
			int n = 0;
			[&, n](int a) mutable { m = ++n + a; }(41);
			std::cout << "m:" << m << std::endl <<"m:" << n << std::endl;

		}
	}
};
static Test_Lambda test;
#endif // __LAMBDA_INC_H__