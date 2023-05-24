#include <iostream>
#include <string>

template<class...> struct Tuple{};
template<class T1, class T2> struct Pair{};

template<class ...Args1>
struct zip{
	template<class ...Args2>
	struct with{
		typedef Tuple<Pair<Args1,Args2>...> type;
	};
};

template<class ...Args> void foo(Args ...args){
	

	(std::cout << ... << args) << std::endl;
	
	
}

template<class ...Args> 
class bar
{
	public:
	bar(Args ...args)
	{
		auto lm = [args...]{		foo(args...);};
		lm();
	}
};

void test(int a,int b,int c)
{
	std::cout <<"sum:" << a+b+c << std::endl;
}

template<class F,class ...Args>
auto delay_invoke(F f,Args... args){
	return [f,args...]() -> decltype(auto) {
		return std::invoke(f,args...);
	};
}


template<class ...Args> void foo1(Args... args)
{
	std::cout <<"foo1(Args... args)" << std::endl;
}

template<class T1, class... Args> void foo1(T1 a1,Args... args)
{
	std::cout << " foo(T1 a1, Args... args):" << a1 <<" " ;
	(std::cout <<...<<args) << std::endl;
}

template<class T1, class T2> void foo1(T1 a,T2 b)
{
	std::cout <<"foo1(T1 a,T2 b)" << std::endl;
}

int main()
{
	zip<short,int>::with<unsigned short,unsigned>::type t1;
	//zip<short>::with<unsigned short,unsigned>::type t2; 编译失败，形参数量不匹配
	
	bar<int,double> b2(5,2.22);
	
	
	auto di = delay_invoke(test,23,32,2);
	di();
	{
		foo1();
		foo1(1,2,3);
		foo1(1,42.033);
	}
	return 0;
}