#include <iostream> 
using namespace std;
int main() 
{
	
	int x = 3;
	decltype(x)y = x;
	cout << y << endl;
	
	return 0;
}