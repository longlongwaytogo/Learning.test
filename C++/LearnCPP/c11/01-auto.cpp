#include <iostream>
/*
* *特性名称:auto与decltype
* 所属:c++11
* -------------------------------------------------
* [what]
* auto 让编译器根据初始值或表达式自动推到类型
* decltype:在不求值的请情况下,推到表达式类型,用于定义变量类型和返回值类型
* -------------------------------------------------
* [why]
* 减少重复代码,提高可读性,简化代码类型声明,同时保持类型安全
* [note]
* - auto 会忽略顶层const 和引用,需要时须显示添加auto& /const auto&
* - decltype: 可以保留表达式的完整类型
* - 尾置返回值类型,配合decltype推到返回值类型
* - auto 不能用于函数参数(c++11)和静态变量成员

-------------------------------------------------------
* auto : 自动推到变量类型
* decltype: 根据表达式获取类型,可用于定义变量类型
*/

#include <vector>
#include <map>
#include <string>
#include <typeinfo>

/// <summary>
/// 辅助: 尾置返回类型
/// </summary>
template <typename T, typename U>
auto add(T a, U b) -> decltype(a + b)
{
	return a + b;
}

void basic_usage()
{
	std::cout << "-- 基础用法--" << std::endl;
	// 1. auto 推到类型
	auto i = 42;
	auto d = 3.24;
	auto s = std::string("符号");
	
	std::cout << "i = " << i << ",type:" << typeid(i).name() << std::endl;
	std::cout << "d = " << d << ",type:" << typeid(d).name() << std::endl;
	std::cout << "s = " << s << ",type:" << typeid(s).name() << std::endl;
	std::cout << "------------------------------------------------" << std::endl;

	// 2. auto 简化迭代器,这是auto经典用法
	std::map<std::string, std::vector<int>> data;
	data["one"] = { 1,2,3 };

	for (auto it = data.begin(); it != data.end(); ++it)
	{
		std::cout << "key:" << it->first << ":";
		for (auto i : it->second)
		{
		std::cout << i << " ";
		}
		std::cout <<std::endl;
	}

	// 3. decltype 推到表达式类型
	int x = 10;
	decltype(x) y = 20;
	decltype(x + 0.5) z = 1.5;
	std::cout <<"y=" << y << ",z=" << z << std::endl;

	// 4 尾置返回值类型
	auto result = add(1, 2.5);
	std::cout << "result=" << result << std::endl;

}

// 进阶用法
void advanced_usage()
{
	std::cout << "-- 进阶用法--" << std::endl;

	// 1. auto 与 const / &
	int value = 100;
	const int& ref = value;
	auto a = ref;
	auto& b = ref;
	const auto& c = value;
	a = 999;// a 是 int（顶层const和引用被丢弃）
	//b = 222; // b 是 const int&（保留引用和底层const）
	std::cout << "a=" << a << std::endl;

	// 2 decltype 对佐治表达式添加过好推到为引用
	int x = 432;
	decltype(x) d1 = x;
	decltype((x)) d2 = x;

	d2 = 100;
    std::cout << "d1=" << d1 << std::endl;
	std::cout << "d2=" << d2 << std::endl;

	// 3 decltype推到容器元素类型
    std::vector<int> vec{ 1,2,3,4,5 };
	decltype(vec)::value_type elm = 10;
    std::cout << "elm=" << elm << std::endl;

	// 4 auto 配合 new 
	auto ptr = new std::vector<std::string>{ "甲", "乙", "丙" };
	for (const auto& s : *ptr)
	{
		std::cout << s << std::endl;

	}
	std::cout << std::endl;
    delete ptr;


}

// 易错点与陷阱
void pitfalls()
{
	std::cout << "\n===== 易错点与陷阱 =====" << std::endl;
	// 陷阱1 auto遇到花括号初始化-> 为参数初始化列表
	auto il = { 1,2,3 }; // il 是 std::initializer_list<int>
    std::cout << "il=" << il.size() << std::endl;
	std::cout << "type:" << typeid(il).name() << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	// 陷阱2 auto 推到代理对象
	std::vector<bool> flags = { true,false,true };
	auto flag = flags[0]; // flags[0] 是 std::vector<bool>::reference 不是bool
	std::cout << "flag=" << flag << std::endl;
	std::cout << "type:" << typeid(flag).name() << std::endl;

	// 正确用法
    std::vector<bool> flags2 = { true,false,true };
    bool flag2 = flags2[0];
    std::cout << "flag2=" << flag2 << std::endl;
    std::cout << "type:" << typeid(flag2).name() << std::endl;


	// 陷阱3 decltype 对比变量名和表达式的行为不同
	int arr[5] = { 1, 2, 3, 4, 5 };
	// decltype(arr) 是 int[5]
	// decltype(arr + 0) 是 int*   （数组退化为指针）

	// 陷阱4: auto 不能用于未初始化的变量
	// auto x;  // 编译错误! auto必须有初始化表达式

	// 陷阱5: 不要滥用auto导致可读性下降
	// auto result = doSomething(); // 读者不知道result是什么类型
	// 建议: 当类型不明显时，显式写出类型更好

	std::cout << "提示: auto是工具，不是万能药。类型不清晰时请显式声明。" << std::endl;
}
int main()
{
	std::cout << "======================================" << std::endl;
	std::cout <<"c++11 特性：auto与decltype "<<std::endl;
	std::cout << "======================================" << std::endl;
	basic_usage();

	advanced_usage();

	pitfalls();
	return 0;
}
//https://tskysheep.github.io/LearnModernCpp/docs/cpp11/01-auto-and-decltype/