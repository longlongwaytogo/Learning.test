#include <iostream>

#include <string>

template<class T,class U>T sum(T t,U u)
{
	return t + u;
}

template<class R,class T,class U> R sum(T t,U u)
{
	return static_cast<R>(t + u);
}

template<class T1,class T2,class T3> T3 alternative_sum(T2 t2,T1 t1)
{
	T3 r = t2 + t1;
	return r;
}
int main()
{
	std::cout << "Test" << std::endl;
	std::cout<<	sum(10.0,10);

	short ii = 2;
	float rr = sum<float>(20,ii);
	std::cout << std::endl;
   
	std::cout<<rr<<std::endl;
	long ll = 223;
	long val2 = alternative_sum<long,short,long>(ii,ll);
	std::cout<<val2<<std::endl;
	
	int maxInt = std::max<int>(20,2);
	
	std::string str = "s2323";
	std::cout << str << std::endl;
	
	return 0;
}