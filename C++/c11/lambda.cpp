#include <iostream>
#include <vector>
#include <algorithm>

#include <cassert>
using namespace std;

int main()
{
	vector<int> iv{4,3,2,1,0};
	
	
	int a = 2,b = 1;
	
	for_each(iv.begin(),iv.end(),[b](int&x){cout << (x + b) << endl;});
	cout<<"---------------------------------------------"<<endl;
	for_each(iv.begin(),iv.end(),[=](int&x){x *= a + b;cout << x << endl;});
	cout<<"---------------------------------------------"<<endl;
	for_each(iv.begin(), iv.end(), [=](int &x)->int{return x * (a + b);});// (3) 
	for_each(iv.begin(),iv.end(),[=](int &x)->int{return x/(a+b); });
	cout<<"---------------------------------------------"<<endl;
	for(auto i : iv) { cout << i << endl;}
	
	return 0;
}