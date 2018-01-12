#include <iostream>
#include <ctype.h>

int main()
{
 
	// isalnum
	// Check if character is alphanumeric (function )
	{
		std::cout<<"is alphanumeric:"<<std::endl;
		int c1 = 'd';
		std::cout<< isalnum(c1) <<std::endl;
	}
	
	// isalpha
	// Check if character is alphabetic (function )
	{
		std::cout<<" is alphabetic:" << std::endl;
		std::cout<< isalpha(1) <<" " << isalpha('a') <<std::endl;
		
	}
	// isblank 
	// Check if character is blank (function )
	{
		std::cout<<" is isblank:" << std::endl;
		std::cout<< isblank(' ') <<" " << isblank('	') << " " << isblank('a') << std::endl;
	}
	
	// iscntrl
	// Check if character is a control character (function )
	{
		std::cout<<" is iscntrl:" << std::endl;
		std::cout<< iscntrl(255)  <<" " << iscntrl(0x0a) <<" " << iscntrl(0x0d) << std::endl;
	}
	// isdigit
	// Check if character is decimal digit (function )
	{
		std::cout<<" is isdigit:" << std::endl;
		std::cout<< isdigit(1) << " " << isdigit('1') << std::endl;
	}
	// isgraph 测试字符是否为可打印字符
	// Check if character has graphical representation (function )
	{
		std::cout<<" is isgraph:" << std::endl;
		std::cout<< isgraph(4) << " " << isgraph('4') <<" " << isgraph(0x0a) <<"empty character:" <<isgraph(' ') << std::endl;
	}
	// islower
	// Check if character is lowercase letter (function )
	{
		std::cout<<" is islower:" << std::endl;
		std::cout<< islower('a') << " " << islower('A')  << std::endl;
	}
	// isprint 和isgraph 差别在于 对于 空格可以被输出
	// Check if character is printable (function )
	{
		std::cout<<" is isprint:" << std::endl;
		std::cout<< isprint(4) << " " << isprint('4') <<" " << isprint(0x0a) <<"empty character:" <<isprint(' ') << std::endl;
	}
	// ispunct 如果参数是除字母，数字和空格外可打印字符，函数返回非零值，否则返回零值。
	// Check if character is a punctuation character (function ) 126  波浪号 ~
	{
		std::cout<<" is ispunct:" << std::endl;
		std::cout<< ispunct(4) << " " << ispunct('4') <<" " << ispunct(0x0a) <<"empty character:" <<ispunct(' ')  <<" " << "波浪线：" << ispunct(126) << std::endl;
	}
	// isspace  若判断字符ch为空空格、制表符或换行符，函数返回非零值，否则返回零值。
	// Check if character is a white-space (function )
	{
		std::cout<<" is isspace:" << std::endl;
		std::cout<< isspace(4) << " " << isspace('4') <<" " << isspace(0x0a)  <<" " << isspace(' ') <<  " " << isspace('\t') <<"波浪线：" << ispunct(126) << std::endl;
	}
	// isupper
	// Check if character is uppercase letter (function )
	{
		std::cout<<" is isspace:" << std::endl;
		std::cout<< isupper('a') << " " << isupper('A') << std::endl;
	}
	// isxdigit
	// Check if character is hexadecimal digit (function )
	{
		char a[]="0xE";
		std::cout<<" is isxdigit:" << std::endl;
		std::cout<< isxdigit(0x11) << " " << isxdigit(004) <<  " " << isxdigit(a[0]) << std::endl;
	}

	return 0;
}