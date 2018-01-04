#include <iostream>
#include <chrono>
#include <ctime>

long fibonacci(unsigned int n)
{
	if(n < 2) return n;
	return fibonacci(n-1) + fibonacci(n-2);
}
using namespace std;




const std::string getCurrentSystemTime()
{
	auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	char date[60] = {0};
	sprintf(date,"%d-%02d-%02d    %02d:%02d:%02d",
	(int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int) ptm->tm_mday,
	(int)ptm->tm_hour,(int)ptm->tm_min,(int)ptm->tm_sec);
	return std::string(date);
}
int main()
{

	cout<< getCurrentSystemTime() << endl;
	
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	fibonacci(42);
	end = std::chrono::system_clock::now();
	
	std::chrono::duration<double> elapsed_seconds = end - start;
	
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	
	std::cout << "finished compution at: " << std::ctime(&end_time) << "elapsed time:"  << elapsed_seconds.count() << "s\n";
	
	std::time_t ht = std::chrono::high_resolution_clock::to_time_t(std::chrono::high_resolution_clock::now());
	std::cout<< "high time:" << std::ctime(&ht) << std::endl;
	 
	return 0;
}