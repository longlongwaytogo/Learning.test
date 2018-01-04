#include<iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future> 

int g_int = 1;

void thread_task() 
{
	 
	std::cout<< "hello thread :" << g_int++ << std::endl;
}

int main () 
{
	for(int i = 0; i < 10; ++i)
	{
		std::thread t(thread_task);
	
		t.join();
	}
	
	return 0;
}