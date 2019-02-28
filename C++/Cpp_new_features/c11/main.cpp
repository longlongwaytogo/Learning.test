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

C++11 ����
1. NULL-Nullptr
2. auto/decltype
3. for(auto& i: array)
4. ��ʼ���б�  struct A{ int a,b,c;}; A a= { x,y,z}
5. ģ��ǿ����ǿ��
    template class std::vector<bool>;            // ǿ��ʵ����
    extern template class std::vector<double>;  // ���ڸñ����ļ���ʵ����ģ��
 6. ģ��������֣� >>   std::vector<std::vector<int>> wow;
 7. ���ͱ���ģ��
    template <typename T>
    using NewType = SuckType<int, T, 1>;    // �Ϸ�
8 . Ĭ��ģ�������
    template<typename T = int, typename U = int>
    auto add(T x, U y) -> decltype(x+y) {
        return x+y;
    }
9 ���캯��
9.1 ί�й���
    C++11 ������ί�й���ĸ����ʹ�ù��캯��������ͬһ������һ�����캯��������һ�����캯�����Ӷ��ﵽ�򻯴����Ŀ�ģ�
    class Base {
    public:
        int value1;
        int value2;
        Base() {
            value1 = 1;
        }
        Base(int value) : Base() {  // ί�� Base() ���캯��
            value2 = 2;
        }
    };
 9.2 �̳й���

    �ڼ̳���ϵ�У������������Ҫʹ�û���Ĺ��캯������Ҫ�ڹ��캯������ʽ������
    ��������ӵ��Ϊ���ڶ�Ĳ�ͬ�汾�Ĺ��캯�������������������е�д�ܶ��Ӧ�ġ�͸�������캯�������£�

    struct A
    {
      A(int i) {}
      A(double d,int i){}
      A(float f,int i,const char* c){}
      //...�ȵ�ϵ�еĹ��캯���汾
    }��
    struct B:A
    {
      B(int i):A(i){}
      B(double d,int i):A(d,i){}
      B(folat f,int i,const char* c):A(f,i,e){}
      //......�ȵȺö���ͻ��๹�캯����Ӧ�Ĺ��캯��
    }��

    C++11�ļ̳й��죺

    struct A
    {
      A(int i) {}
      A(double d,int i){}
      A(float f,int i,const char* c){}
      //...�ȵ�ϵ�еĹ��캯���汾
    }��
    struct B:A
    {
      using A::A;
      //���ڻ�������캯���ļ̳�һ�仰�㶨
      //......
    }��

10: Lambda ���ʽ
    [ caputrue ] ( params ) opt -> ret { body; };
1) capture�ǲ����б�
2) params�ǲ�����(ѡ��)
3) opt�Ǻ���ѡ�������mutable,exception,attribute��ѡ�
mutable˵��lambda���ʽ���ڵĴ�������޸ı�����ı��������ҿ��Է��ʱ�����Ķ����non-const������
exception˵��lambda���ʽ�Ƿ��׳��쳣�Լ������쳣��
attribute�����������ԡ�
4) ret�Ƿ���ֵ���ͣ���β�������ͣ���(ѡ��)
5) body�Ǻ����塣
---------------------

11. �������� 
    std::array
    std::forward_list
    std::unordered_map/std::unordered_multimap �� std::unordered_set/std::unordered_multiset��
12: Ԫ�� std::tuple
    std::make_tuple: ����Ԫ��
    std::get: ���Ԫ��ĳ��λ�õ�ֵ
    std::tie: Ԫ����
13 ������ʽ

    std::regex (������ std::basic_regex)���г�ʼ����
    ͨ�� std::regex_match ����ƥ�䣬�Ӷ����� std::smatch �������� std::match_results ���󣩡�
 14 ���Լ��߳�֧��:
    std::thread
    std::mutex/std::unique_lock
    std::future/std::packaged_task
    std::condition_variable
    std::promise
    ��Ҫʹ��-pthread ѡ��
15 �����޶��� & 
// �ɱ�׼�л��������ֵ��ֵ�����
string s1 = "a value", s2 = "another";
s1 + s2 = "wow!";
// �±�׼��ͨ�������޶��������������
class Foo{
    public:
        Foo &operator=(const Foo&) &;  // ֻ������޸ĵ���ֵ��ֵ
        // ... Foo ����������
        Foo someMem() & const;  // ����const�޶���������ǰ
        Foo anotherMem() const &;  // ��ȷ
        Foo sorted() &&;  // ���ڿɸı����ֵ������ԭַ����
        Foor sorted() const &;  // ����Ϊconst ����ֵ��������������ܽ���ԭַ����
};
Foo &Foo::operator=(const Foo &rhs) &
{
    // ��������
    return *this;
}
 
 16: ��ֵ���ã� 
 https://blog.csdn.net/jiange_zh/article/details/79356417
 ---------------------
���ߣ�jiange_zh
��Դ��CSDN
ԭ�ģ�https://blog.csdn.net/jiange_zh/article/details/79356417
��Ȩ����������Ϊ����ԭ�����£�ת���븽�ϲ������ӣ�
*/