#include<iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future> 


void thread_task() 
{
	std::cout<< "hello thread ." << std::endl;
}

int main () 
{

	std::thread t(thread_task);
	t.join();
	
	return 0;
}