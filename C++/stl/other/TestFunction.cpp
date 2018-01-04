//////////////////////////////////////////
// TestFunction.cpp
// 测试字符串大小写转换
// 2018/01/04
// szh

#include <stdio.h>
#include <ctype.h>

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

char Toupper(char c)
{
	if('a' <= c && c <= 'z')
		c = c +  'A' - 'a';
	return c;
}

void Convert_toUpper(char* s)
{
	//char* p = s;
	int i = 0;
	while(*s !='\0')
	{
		if(*s >= 'a' && *s <= 'z')
			*s = *s + 'A' - 'a';
		s++;
		i++;
	}
}
	
	/*
		大概明白了，写一下 
		a 0110 0001 
		A 0100 0001 
		只有第6位是不一样的，所以，如果想把小写转换成大写，只需要将第6位改成0，也就是-32。这样直接和 
		1101 1111 
		进行与操作，这样就保证了其他位不变，将第6位变成了0 
		同样，如果要将大写转换成小写，需要将第6为改为1。 
		直接和 
		0010 0000 
		进行或运算，就可以完成。 
		还有一个比较更简单的是直接和 
		0010 0000 
		进行异或运算，就ok了
	*/
void ToUpper_1(char* s) 
{ 
	char* p = s;
	while(*s !='\0')
	{
		std::cout<< *s;
		if(*s >= 'a' && *s <= 'z')
		 *s &= 0xDF;   // 11011111B 
		s++;
	}
	std::cout << p << std::endl;
	std::cout<<std::endl;
}

// 仿函数
struct convert {
   void operator()( char& c) { c = toupper((unsigned char)c); }
};

int main()
{
	std::cout<< "foreach test" << std::endl;
	std::string str ="12342453453fdsAAAAodfj";
	str+='\0';

	
	for_each(str.begin(),str.end(),convert());
	std::cout << "convert string upper:" << str << std::endl;
	
	transform(str.begin(), str.end(),str.begin(), ::tolower);
	//transform(str.begin(),str.end(),str.begin(),tolower);
	std::cout << " convert string lower:" << str << std::endl;
	
	std::transform(str.begin(), str.end(), str.begin(),Toupper);
	std::cout << "convert string upper:" << str << std::endl;
  
	
	char  str1[14] = {"hello world"};
	Convert_toUpper(str1);
	std::cout << "--convert str1 upper:" << str1 << std::endl;
	
	char str2[14] = {"hello world1"};
	ToUpper_1(str2);
	std::cout << "--convert str2 upper:" << str2 << std::endl;
	return 0;
}
