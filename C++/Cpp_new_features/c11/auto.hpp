#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <algorithm>
#include <math.h>
#include <tuple>
#include <numeric>
#include <memory>
#include <array>
#include <regex>


void test_auto()
{
    // auto 
    auto i = 1;
    auto i1 = 1.0;
    auto str = "hello";
    auto ch = 'a';
    auto func = std::less<int>();
    auto p = new int();

    int arr[10] = { 0 };
    auto auto_arr = arr;

    for (auto ii : arr)
    {
        std::cout << ii << std::endl;
    }
   /* for (auto ii : auto_arr)        // error use
    {
        std::cout << ii << std::endl;
    }*/

    for (int i = 0; i < 10; i++)
    {
        std::cout << " auto_arr:" << auto_arr[i] << std::endl;
        //std::cout << "auto_arr:" << *i << std::endl;
    }

    delete p;
}
template<typename T, typename U>
auto add(T x, U y) -> decltype(x + y) {
    return x + y;
};

template<typename T, typename U>
auto add2(T x, U y)
{
    return x + y;
};



void test_decltype()
{
    int x = 3;
    decltype(x) y = x;
   
    std::cout << add(x, y);
    std::cout << add2(x, y);
}

void test_null()
{
    // NULL 实际上是0，在参数传递中，可能存在二义性，
    // 如F(int), F(int*),调用F(int),到底调用那个函数
    int *p = nullptr;

}

void test_For()
{
    std::map<std::string, int> m{ {"a",1 }, {"b",2},{"c",3} };
    for (auto p : m)
    {
        std::cout << p.first << ":" << p.second << std::endl;
    }
}

/*
[]内的参数指的是Lambda表达式可以取得的全局变量。(1)函数中的b就是指函数可以得到在Lambda表达式外的全局变量，如果在[]中传入=的话，即是可以取得所有的外部变量，如（2）和（3）Lambda表达式
()内的参数是每次调用函数时传入的参数。
->后加上的是Lambda表达式返回值的类型，如（3）中返回了一个int类型的变量
下面是各种变量截取的选项：
[] 不截取任何变量
[&} 截取外部作用域中所有变量，并作为引用在函数体中使用
[=] 截取外部作用域中所有变量，并拷贝一份在函数体中使用
[=, &foo]   截取外部作用域中所有变量，并拷贝一份在函数体中使用，但是对foo变量使用引用
[bar]   截取bar变量并且拷贝一份在函数体重使用，同时不截取其他变量
[this]            截取当前类中的this指针。如果已经使用了&或者=就默认添加此选项。

*/
void test_lambda()
{
    std::cout << "test lambda" << std::endl;
    std::vector<int> iv{ 5,4,3,2,1 };
    int a = 2, b = 1;
    std::cout << "test1" << std::endl;
    for_each(iv.begin(), iv.end(), [b](int&x) {std::cout << (x + b) << std::endl; });
    std::cout << "test2" << std::endl;
    for_each(iv.begin(), iv.end(), [=](int&x)->int {return x * (a + b); });
    for_each(iv.begin(), iv.end(), [=](int&x) { std::cout << x << std::endl; });
}

//template <typename Head,typename Tail>
//void Print(Head head, Tail... tail)
//{
//    std::cout << head << std::endl;
//    Print(tail...);
//}
void test_tuple()
{
    auto t2 = std::make_tuple(1, 2.0, "C++ 11", 23);


    auto tup1 = std::make_tuple(3.14, 1, 'a');
    double a;
    int b;
    char c;
    std::tie(a, b, c) = tup1;

    std::tie(std::ignore, b, c);
    std::cout << b << "," << c << std::endl;

    std::cout << std::get<0>(tup1) << std::endl;
    std::cout << std::get<1>(tup1) << std::endl;
    std::cout << std::get<2>(tup1) << std::endl;

}


class Tracker
{
public:
    Tracker(char* text) 
    {
        m_text = text;
    }

    Tracker(Tracker& rhs)          // 拷贝构造
    {
        if (rhs.m_text != nullptr)
        {
            int len = strlen(rhs.m_text) + 1;
            m_text = new char[len];
            strcpy(m_text, rhs.m_text);
        }

    }
    Tracker(Tracker&& rhs)  noexcept      // 移动构造      
    {
        if (rhs.m_text != nullptr)
        {
            m_text = rhs.m_text;
            rhs.m_text = nullptr;
        }
    }
    Tracker& operator=(const Tracker& rhs)     // 赋值
    {
        if (this != &rhs)
        {
            //free();
            if (rhs.m_text != nullptr)
            {
                int len = strlen(rhs.m_text);
                m_text = new char[len + 1];
                strcpy(m_text, rhs.m_text);
            }
          }
        return *this;
    }
    Tracker& operator=( Tracker&& rhs) noexcept  // 移动赋值 
    {
        if (rhs.m_text != nullptr)
        {
            m_text = rhs.m_text;
            rhs.m_text = nullptr;
        }
        return *this;
    }
private:

    char* m_text;
};
void test_rvalue()
{   // 一个左值表达式代表的是对象本身，而右值表达式代表的是对象的值；变量也是左值。
    //   为了支持移动操作（包括移动构造函数和移动赋值函数），
    // C++才引入了一种新的引用类型——右值引用，可以自由接管右值引用的对象内容。
    //std::move()
    // 右值引用

    Tracker src[4] ={ "How","are","you","!" };
    std::allocator<Tracker> alloc;
    auto dest = alloc.allocate(4);
    std::uninitialized_copy(std::make_move_iterator(std::begin(src)),
                        std::make_move_iterator(std::end(src)), dest);
    int a = 42;
    int &a1 = a;
   // int && a11 = a; 
   // int &a2 = a * 42;
    const int & a3 = a * 42;
    int && aa2 = a * 42;

    int i = 42;
    int &r = i;  // 正确：r 引用 i
   // int &&rr = i;  // 错误：不能将一个右值引用绑定到一个左值上
    //int &r2 = i * 42;  // 错误：i * 42 是右值
    const int &r3 = i * 42;  // 正确：可以将 const 引用绑定到右值上
    int &&rr2 = i * 42;  // 正确：将 rr2 绑定到乘法结果上
    std::cout << "right value r3: " << r3 << std::endl;
    int &&rr1 = 42;  //  字面值常量是右值
    int &&rr3 = std::move(rr1);  // ok

    //    -------------------- -
    //    作者：小小池鱼儿
    //    来源：CSDN
    //    原文：https ://blog.csdn.net/u011221820/article/details/80171149 
    //版权声明：本文为博主原创文章，转载请附上博文链接！

}

void test_begin_end_itr()
{
    double data[] = { 2.5,3.3, 1.6, 3.3, 8.2};
    std::cout << "The Array contains:" << std::endl;
  
    for (auto itr = std::begin(data); itr != std::end(data); ++itr)
    {
        std::cout << "data:" << *itr << std::endl;
    }
    double total = std::accumulate(std::begin(data), std::end(data), 0.0);
    std::cout << "totoal:" << total << std::endl;

}

void test_array()
{
    std::array<int, 4> arr1 = { 2,3,5,6 };
    const int len = 4;
    std::array<int, len> arr = { 1,2,3,4 }; // 非法, 数组大小参数必须是常量表达式
    std::sort(arr1.begin(), arr1.end());
}

void test_regex()
{
    std::string fnames[] = { "foo.txt", "bar.txt" , "text", "a0.txt", "AAA.txt" };
    std::regex txt_regex("[a-z]+\\.txt");
    for (const auto& fname : fnames)
        std::cout << fname << ":" << std::regex_match(fname, txt_regex) << std::endl;
}

#include <future>
#include <thread>
#include <type_traits>
void test_thread()
{
    std::promise<int> promiseParam;
    std::thread t([](std::promise<int>& p){
        std::this_thread::sleep_for(std::chrono::seconds(2));
        p.set_value_at_thread_exit(4);

        }, std::ref(promiseParam));

    std::future<int> futureParam = promiseParam.get_future();
    auto r = futureParam.get();
    std::cout << r << std::endl;
}