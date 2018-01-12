#include <iostream>
#include <string>
#include <sstream>

using namespace std;
int main()
{
	
	stringstream ss;
	int a = 234;
	string b = "test stream！";
	ss<<"123" << a << b;
	cout<<ss.str();


	return 0;
}

