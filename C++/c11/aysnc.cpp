#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <cmath>

#include <future>
#include <chrono>


using namespace std;

int main() 
{
	
	auto begin = std::chrono::steady_clock::now();
	
	// std::future<double>
	auto f(std::async(std::launch::async,[](int n) { 
		std::cout << std::this_thread::get_id() << "start computing..." << std::endl;
		
		double ret = 0;
		for(int i = 0; i <= n; i++)
		{
			ret += std::sin(i);
		}
	},10000000));
	
	
	while(f.wait_for(std::chrono::seconds(1)) != std::future_status::ready) 
	{
		std::cout << "task is running ..." << endl;
	}
	
	auto end = std::chrono::steady_clock::now();
	
	auto diff = end - begin;
	
	std::cout << "async_task result:" << f.get() << std::endl;
	std::cout << std::chrono::duration<double,std:: std::milli> (diff).count() << " ms" << std::endl;
	
	return 0;
}