// template.cpp
/*
1.定义一个模板结构，将具体内容延迟到子类去实现。
2.主要作用:在不改变模板结构的前提下在子类中重新定义模板中的内容。模板方法模式是基于”继承“的；
3.解决的问题:
	提高代码复用性 
	将相同部分的代码放在抽象的父类中，而将不同的代码放入不同的子类中
	实现了反向控制 
	通过一个父类调用其子类的操作，通过对子类的具体实现扩展不同的行为，实现了反向控制 & 符合“开闭原则”
*/

#include<iostream>
using namespace std;

class AbstractClass {
public:
	virtual void TemplateMethod() {
		PrimitiveOperation1();
		PrimitiveOperation2();
	}
	virtual ~AbstractClass(){}
protected:
	virtual void PrimitiveOperation1() = 0;
	virtual void PrimitiveOperation2() = 0;
	AbstractClass() {}
};

class ConcreateClass1 :public AbstractClass
{
public: 
	void PrimitiveOperation1() {
		cout << "ConcreateClass1: PrimitiveOperation1" << endl;
	}
	
	void PrimitiveOperation2() {
		cout << "ConcreateClass1: PrimitiveOperation2" << endl;
	}
};

class ConcreateClass2 :public AbstractClass
{
public: 
	void PrimitiveOperation1() {
		cout << "ConcreateClass2: PrimitiveOperation1" << endl;
	}
	
	void PrimitiveOperation2() {
		cout << "ConcreateClass2: PrimitiveOperation2" << endl;
	}
};

int main()
{
	AbstractClass* p1 = new ConcreateClass1();
	AbstractClass* p2 = new ConcreateClass2();
	
	p1->TemplateMethod();
	p2->TemplateMethod();
	
	delete p1;
	delete p2;
	
	return 0;
}