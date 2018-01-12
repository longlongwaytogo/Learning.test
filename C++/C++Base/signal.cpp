#include <iostream>
#include <csignal>
#include <unistd.h>
 
using namespace std;
 
void signalHandler( int signum )
{
    cout << "Interrupt signal (" << signum << ") received.\n";
 
    // 清理并关闭
    // 终止程序  
 
   exit(signum);  
 
}
 
int main ()
{
    // 注册信号 SIGINT 和信号处理程序
    signal(SIGINT, signalHandler);  
	int i = 1;
    while(++i){
       cout << "Going to sleep...." << endl;
       sleep(1);
	   
	   if(i > 5)
		raise(SIGINT);
    }
 
    return 0;
}