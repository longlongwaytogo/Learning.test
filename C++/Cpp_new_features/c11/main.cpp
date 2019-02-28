#include<iostream>
#include <functional>
#include "auto.hpp"
int main(int argc, char** agrv)
{
    test_auto();
    test_decltype();
    test_null();
    test_For();
    test_lambda();
    test_tuple();
    test_begin_end_itr();
    test_array();
    test_regex();
    test_rvalue();
    test_thread();

    std::cout << "end test" << std::endl;
    return 0;
}
 


/*

C++11 特性
1. NULL-Nullptr
2. auto/decltype
3. for(auto& i: array)
4. 初始化列表  struct A{ int a,b,c;}; A a= { x,y,z}
5. 模板强制增强：
    template class std::vector<bool>;            // 强行实例化
    extern template class std::vector<double>;  // 不在该编译文件中实例化模板
 6. 模板允许出现： >>   std::vector<std::vector<int>> wow;
 7. 类型别名模板
    template <typename T>
    using NewType = SuckType<int, T, 1>;    // 合法
8 . 默认模板参数：
    template<typename T = int, typename U = int>
    auto add(T x, U y) -> decltype(x+y) {
        return x+y;
    }
9 构造函数
9.1 委托构造
    C++11 引入了委托构造的概念，这使得构造函数可以在同一个类中一个构造函数调用另一个构造函数，从而达到简化代码的目的：
    class Base {
    public:
        int value1;
        int value2;
        Base() {
            value1 = 1;
        }
        Base(int value) : Base() {  // 委托 Base() 构造函数
            value2 = 2;
        }
    };
 9.2 继承构造

    在继承体系中，如果派生类想要使用基类的构造函数，需要在构造函数中显式声明。
    假若基类拥有为数众多的不同版本的构造函数，这样，在派生类中得写很多对应的“透传”构造函数。如下：

    struct A
    {
      A(int i) {}
      A(double d,int i){}
      A(float f,int i,const char* c){}
      //...等等系列的构造函数版本
    }；
    struct B:A
    {
      B(int i):A(i){}
      B(double d,int i):A(d,i){}
      B(folat f,int i,const char* c):A(f,i,e){}
      //......等等好多个和基类构造函数对应的构造函数
    }；

    C++11的继承构造：

    struct A
    {
      A(int i) {}
      A(double d,int i){}
      A(float f,int i,const char* c){}
      //...等等系列的构造函数版本
    }；
    struct B:A
    {
      using A::A;
      //关于基类各构造函数的继承一句话搞定
      //......
    }；

10: Lambda 表达式
    [ caputrue ] ( params ) opt -> ret { body; };
1) capture是捕获列表；
2) params是参数表；(选填)
3) opt是函数选项；可以填mutable,exception,attribute（选填）
mutable说明lambda表达式体内的代码可以修改被捕获的变量，并且可以访问被捕获的对象的non-const方法。
exception说明lambda表达式是否抛出异常以及何种异常。
attribute用来声明属性。
4) ret是返回值类型（拖尾返回类型）。(选填)
5) body是函数体。
---------------------

11. 新增容器 
    std::array
    std::forward_list
    std::unordered_map/std::unordered_multimap 和 std::unordered_set/std::unordered_multiset。
12: 元组 std::tuple
    std::make_tuple: 构造元组
    std::get: 获得元组某个位置的值
    std::tie: 元组拆包
13 正则表达式

    std::regex (本质是 std::basic_regex)进行初始化，
    通过 std::regex_match 进行匹配，从而产生 std::smatch （本质是 std::match_results 对象）。
 14 语言级线程支持:
    std::thread
    std::mutex/std::unique_lock
    std::future/std::packaged_task
    std::condition_variable
    std::promise
    需要使用-pthread 选项
15 引用限定符 & 
// 旧标准中会出现向右值赋值的情况
string s1 = "a value", s2 = "another";
s1 + s2 = "wow!";
// 新标准可通过引用限定符解决上述问题
class Foo{
    public:
        Foo &operator=(const Foo&) &;  // 只能像可修改的左值赋值
        // ... Foo 的其他参数
        Foo someMem() & const;  // 错误：const限定符必须在前
        Foo anotherMem() const &;  // 正确
        Foo sorted() &&;  // 用于可改变的右值，可以原址排序
        Foor sorted() const &;  // 对象为const 或左值，两种情况都不能进行原址排序
};
Foo &Foo::operator=(const Foo &rhs) &
{
    // 其它工作
    return *this;
}
 
 16: 右值引用： 
 https://blog.csdn.net/jiange_zh/article/details/79356417
 ---------------------
作者：jiange_zh
来源：CSDN
原文：https://blog.csdn.net/jiange_zh/article/details/79356417
版权声明：本文为博主原创文章，转载请附上博文链接！
*/