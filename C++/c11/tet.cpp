#include <iostream>
#include <vector>
using namespace std;

int main()
{
	
	
	
	struct S 
	{
		
		int c = '\0';
		int i;
		
		S():c('c'),i(3)
		{
			c = 'x';
			i = 5;
		}
	};
	
	S s;
	cout << s.c << endl;
	cout << s.i << endl;

	return 0;
}