#include <cstdio>
#include <csignal>
#include <iostream>

using namespace std;

class Tester {
	public:
		Tester(const char* name) 
		{
			this->name = name;
			std::cout << name << " Tester ctor\n"; }
		~Tester() { std::cout << name << " Tester dtor\n"; }
	private:
	const char* name;	
};

Tester static_tester("static_tester"); // 不调用析构函数

void signal_handler(int signal)
{
	if(signal == SIGABRT) {
		std::cerr << "SIGABRT received\n";
	} else {
		std::cerr << "Unexpected signal " << signal << "received\n";
	}
	std::_Exit(EXIT_FAILURE);
}
int main()
{
	
	// file test
	{
		FILE *fp = NULL;
		fp = fopen("vec.txt","w+");
		if(fp != NULL)
		{
			for(char i = 'a'; i <= 'z'; ++i)
				fwrite(&i,1,sizeof(char),fp);
			fclose(fp);
		}
		
		FILE* fop = NULL;
		fop = fopen("vec.txt" ,"r");
		if(fop != NULL)
		{
			 while(!feof(fop))
			 {
				 printf("%c", fgetc(fop));
			 }
		}
		std::cout<< "\n";
	}
	
	
	// test abort 
	std::cout << "Test abort function\n";
	Tester automatic_tester("automatic_tester"); // 不调用析构函数
	
	// 安装处理函数
	auto previous_handler = std::signal(SIGABRT,signal_handler);
	if(previous_handler == SIG_ERR) {
		std::cerr << "Setup failed \n";
		return EXIT_FAILURE;
	}
	
	//std::abort(); // 引发SIGABRT
	std::exit(0); // 正常函数退出
	std::cout << "This code is unreachable\n";
	
	
	
	
	
	return 0;
}