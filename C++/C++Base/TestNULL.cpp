#include <iostream>
using namespace std;
void f(int i)
{
cout << "f(int i)" << endl;
}

void f(char* a)
{
cout << "f(char* a)" << endl;
}

//#define NULL 0
int main()
{
f(NULL);

return 0;
}
