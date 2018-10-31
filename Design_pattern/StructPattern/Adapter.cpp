// Adapter.cpp 
/*
适配器模式（Adapter Pattern）是作为两个不兼容的接口之间的桥梁。这种类型的设计模式属于结构型模式，它结合了两个独立接口的功能。
这种模式涉及到一个单一的类，该类负责加入独立的或不兼容的接口功能。举个真实的例子，读卡器是作为内存卡和笔记本之间的适配器。您将内存卡插入读卡器，再将读卡器插入笔记本，这样就可以通过笔记本来读取内存卡。

意图：将一个类的接口转换成客户希望的另外一个接口。适配器模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。
主要解决：主要解决在软件系统中，常常要将一些"现存的对象"放到新的环境中，而新环境要求的接口是现对象不能满足的。

*/

#include <iostream>
#include <string>
using namespace std;

class Target	// 目标
{
public:
	virtual void Request() {
		cout << "Target Request..." << endl;
	}
	virtual ~Target() {}
};

class Adaptee { // 被适配者
public:
	void SpecificRequest() {
		cout << "Adaptee:SpecificRequest..." << endl;
	}
};

class Adapter: public Target,private Adaptee {
public:
	Adapter(Adaptee* ade) {
		_ade = ade;
	}
	
	void Request()
	{
		_ade->SpecificRequest();
	}
	
private:
	Adaptee* _ade;
};

int main()
{
	Adaptee* adaptee = new Adaptee();
	Target* adapter = new Adapter(adaptee);
	adapter->Request();
	
	delete adaptee;
	delete adapter;
	
	return 0;
}