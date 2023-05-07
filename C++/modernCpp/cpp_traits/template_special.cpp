//模板特化
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

template<class T>
int compare(const T left, const T right)
{
	std::cout << "in template<class T>..." << std::endl;
	cout<<typeid(T).name()<<endl;
	cout<<typeid(left).name()<<endl;
	cout<<typeid(right).name()<<endl;
 
	return (left-right);
}

// 函数模板特化
 template<>
 int compare<const char*>(const char*left, const char* right)
{
	 std::cout << "in special template<>..." << std::endl;
	 return strcmp(left,right);
 }

// template<>
// int compare<int>(int a,int b)
// {
	 // std::cout << "in special compare<int>..." << std::endl;
	// return 0;
// }

template<>
 int compare<const int>(const int a,const int b)
 {
     cout<<"template<>:const int"<<endl;
     return a>b;
 }
 
 




// template<>
// int compare(const char* left, const char* right)
// {
    // std::cout <<"in special template< >..." <<std::endl;

    // return strcmp(left, right);
// }
 


//函数模板
template<class T>
bool IsEqual(T t1,T t2){
    return t1==t2;
}

template<> //函数模板特化
bool IsEqual(char *t1,char *t2){
	std::cout<<"str isEual"<<endl;
    return strcmp(t1,t2)==0;
}

// class template 
template<class T>
class Compare
{
	public:
		static bool IsEqual(const T& lhs,const T& rhs)
		{
			std::cout<<" in the general class ..." <<endl;
			return lhs == rhs;
		}
};

// specialize for float
template<>
class Compare<float>
{
	public:
	static bool IsEqual(const float& lhs,const float& rhs)
	{
		std::cout <<" in the float special class ..." << endl;
		return std::abs(lhs - rhs) < 10e-3;
	}
};

// specialize for float
template<>
class Compare<double>
{
	public:
	static bool IsEqual(const double& lhs,const double& rhs)
	{
		std::cout <<" in the double special class ..." << endl;
		return std::abs(lhs - rhs) < 10e-6;
	}
};
// specialize for T*
template<class T>
class Compare<T*>
{
public:
    static bool IsEqual(const T* lh, const T* rh)
    {
        return Compare<T>::IsEqual(*lh, *rh);
    }
};

// specialize for vector<T>
template<class T>
class Compare<vector<T> >
{
public:
    static bool IsEqual(const vector<T>& lh, const vector<T>& rh)
    {
        if(lh.size() != rh.size()) return false;
        else
        {
            for(int i = 0; i < lh.size(); ++i)
            {
                if(lh[i] != rh[i]) return false;
            }
        }
        return true;
    }
};


 // 半特化
 // specialize for any template class type
template <class T1> 
struct SpecializedType
{
    T1 x1;
    T1 x2;
};

template <class T>
class Compare<SpecializedType<T> >
{
public:
    static bool IsEqual(const SpecializedType<T>& lh, const SpecializedType<T>& rh)
    {
        return Compare<T>::IsEqual(lh.x1 + lh.x2, rh.x1 + rh.x2);
    }
};

 // 偏特化
 template<class T1, class T2>
class A
{
	public:
	
	A()
	{
		std::cout <<"A"<<endl;
	}
};

template<class T1>
class A<T1, int>
{
	public:
	A()
	{
		std::cout <<"A<T1, int>"<<endl;
	}
};

int main()
{
	{
		  // int
		int i1 = 10;
		int i2 = 10;
		bool r1 = Compare<int>::IsEqual(i1, i2);

		// float
		float f1 = 10;
		float f2 = 10;
		bool r2 = Compare<float>::IsEqual(f1, f2);

		// double
		double d1 = 10;
		double d2 = 10;
		bool r3 = Compare<double>::IsEqual(d1, d2);

		// pointer
		int* p1 = &i1;
		int* p2 = &i2;
		bool r4 = Compare<int*>::IsEqual(p1, p2);

		// vector<T>
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);

		vector<int> v2;
		v2.push_back(1);
		v2.push_back(2);
		bool r5 = Compare<vector<int> >::IsEqual(v1, v2);

		// custom template class 
		SpecializedType<float> s1 = {10.1f,10.2f};
		SpecializedType<float> s2 = {10.3f,10.0f};
		bool r6 = Compare<SpecializedType<float> >::IsEqual(s1, s2);
 
	}
	{
		A<double,int>a;
		A<double,float>b;
	}
	return 0;
	{
		Compare<int> comp1;
		std::cout <<comp1.IsEqual(3, 4) <<std::endl;
		std::cout <<comp1.IsEqual(3, 3) <<std::endl;

		Compare<float> comp2;
		std::cout <<comp2.IsEqual(3.14, 4.14) <<std::endl;
		std::cout <<comp2.IsEqual(3, 3) <<std::endl;

		Compare<double> comp3;
		std::cout <<comp3.IsEqual(3.14159, 4.14159) <<std::endl;
		std::cout <<comp3.IsEqual(3.14159, 3.14159) <<std::endl;
		std::cout<<"----------------------------------"<<endl;
	}
	
	{
		std::cout << "test isEqual!"<<std::endl;
		char str1[]="abc";
		char str2[]="abc";
		 
		cout<<IsEqual(1,1)<<std::endl;
		cout<<IsEqual(str1,str2)<<endl;
	}
	
	compare(1,4);
	const int a = 1;
	const int b = 2;
	std::cout <<"const int:call" << std::endl;
	compare<const int>(a,b);
	std::cout <<"compare(a,b);" << std::endl;
	compare(a,b);
	
	 
	const char *left = "gatieme";
    const char *right = "jeancheng";
    compare(left, right);
	 compare<const char*>("hello","world");
	return 0;
}