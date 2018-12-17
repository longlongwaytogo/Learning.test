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
    // NULL ʵ������0���ڲ��������У����ܴ��ڶ����ԣ�
    // ��F(int), F(int*),����F(int),���׵����Ǹ�����
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
[]�ڵĲ���ָ����Lambda���ʽ����ȡ�õ�ȫ�ֱ�����(1)�����е�b����ָ�������Եõ���Lambda���ʽ���ȫ�ֱ����������[]�д���=�Ļ������ǿ���ȡ�����е��ⲿ�������磨2���ͣ�3��Lambda���ʽ
()�ڵĲ�����ÿ�ε��ú���ʱ����Ĳ�����
->����ϵ���Lambda���ʽ����ֵ�����ͣ��磨3���з�����һ��int���͵ı���
�����Ǹ��ֱ�����ȡ��ѡ�
[] ����ȡ�κα���
[&} ��ȡ�ⲿ�����������б���������Ϊ�����ں�������ʹ��
[=] ��ȡ�ⲿ�����������б�����������һ���ں�������ʹ��
[=, &foo]   ��ȡ�ⲿ�����������б�����������һ���ں�������ʹ�ã����Ƕ�foo����ʹ������
[bar]   ��ȡbar�������ҿ���һ���ں�������ʹ�ã�ͬʱ����ȡ��������
[this]            ��ȡ��ǰ���е�thisָ�롣����Ѿ�ʹ����&����=��Ĭ����Ӵ�ѡ�

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

    Tracker(Tracker& rhs)          // ��������
    {
        if (rhs.m_text != nullptr)
        {
            int len = strlen(rhs.m_text) + 1;
            m_text = new char[len];
            strcpy(m_text, rhs.m_text);
        }

    }
    Tracker(Tracker&& rhs)  noexcept      // �ƶ�����      
    {
        if (rhs.m_text != nullptr)
        {
            m_text = rhs.m_text;
            rhs.m_text = nullptr;
        }
    }
    Tracker& operator=(const Tracker& rhs)     // ��ֵ
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
    Tracker& operator=( Tracker&& rhs) noexcept  // �ƶ���ֵ 
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
{   // һ����ֵ���ʽ������Ƕ���������ֵ���ʽ������Ƕ����ֵ������Ҳ����ֵ��
    //   Ϊ��֧���ƶ������������ƶ����캯�����ƶ���ֵ��������
    // C++��������һ���µ��������͡�����ֵ���ã��������ɽӹ���ֵ���õĶ������ݡ�
    //std::move()
    // ��ֵ����

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
    int &r = i;  // ��ȷ��r ���� i
   // int &&rr = i;  // ���󣺲��ܽ�һ����ֵ���ð󶨵�һ����ֵ��
    //int &r2 = i * 42;  // ����i * 42 ����ֵ
    const int &r3 = i * 42;  // ��ȷ�����Խ� const ���ð󶨵���ֵ��
    int &&rr2 = i * 42;  // ��ȷ���� rr2 �󶨵��˷������
    std::cout << "right value r3: " << r3 << std::endl;
    int &&rr1 = 42;  //  ����ֵ��������ֵ
    int &&rr3 = std::move(rr1);  // ok

    //    -------------------- -
    //    ���ߣ�СС�����
    //    ��Դ��CSDN
    //    ԭ�ģ�https ://blog.csdn.net/u011221820/article/details/80171149 
    //��Ȩ����������Ϊ����ԭ�����£�ת���븽�ϲ������ӣ�

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
    std::array<int, len> arr = { 1,2,3,4 }; // �Ƿ�, �����С���������ǳ������ʽ
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