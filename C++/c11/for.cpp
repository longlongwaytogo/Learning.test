#include <iostream>
#include <map>
#include <cassert>
using namespace std;

int main()
{
	map<string,int> m{{"a",1},{"b",2},{"c",3}};
	for(auto p : m)
	{
		cout << p.first << ":" << p.second << endl;
	}
	
	return 0;
}