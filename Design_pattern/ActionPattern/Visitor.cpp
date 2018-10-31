// Visitor.cpp
/*
访问者模式
在访问者模式（Visitor Pattern）中，我们使用了一个访问者类，它改变了元素类的执行算法。通过这种方式，元素的执行算法可以随着访问者改变而改变。这种类型的设计模式属于行为型模式。根据模式，元素对象已接受访问者对象，这样访问者对象就可以处理元素对象上的操作。
介绍
意图：主要将数据结构与数据操作分离。
主要解决：稳定的数据结构和易变的操作耦合问题。
何时使用：需要对一个对象结构中的对象进行很多不同的并且不相关的操作，而需要避免让这些操作"污染"这些对象的类，使用访问者模式将这些封装到类中。
如何解决：在被访问的类里面加一个对外提供接待访问者的接口。
关键代码：在数据基础类里面有一个方法接受访问者，将自身引用传入访问者。
*/
#include <iostream>
#include <string>

using namespace std;

class Visitor;

class Element {
public:
	virtual ~Element(){}
	virtual void Accept(Visitor* visitor) = 0;
};

class Visitor
{
public:
	virtual ~Visitor() {}
	virtual void VisitConcreteElementA(Element* element) = 0;
	virtual void VisitConcreteElementB(Element* element) = 0;
protected:
	void visitor(){}
};

class ConcreteVisitorA :public Visitor {
public:
    void VisitConcreteElementA(Element* elm)
	{
		 cout << "ConcreteVisitorA:i will visit ConcreteElementA..." << endl;
	}
    void VisitConcreteElementB(Element* elm)
	{
		 cout << "ConcreteVisitorA:i will visit ConcreteElementB..." << endl;
	}
};

class ConcreteVisitorB :public Visitor {
public:
    void ConcreteVisitorA(Element* elm)
	{
		 cout << "VisitConcreateElementB:i will visit ConcreteElementA..." << endl;
	}
    void VisitConcreteElementB(Element* elm)
	{
		   cout << "VisitConcreateElementB:i will visit ConcreteElementB..." << endl;
	}
};

class ConcreteElementA :public Element
{
public:
	void Accept(Visitor* visitor)
	{
		visitor->VisitConcreteElementA(this);
		cout << "visiting ConcreteElementA..." << endl;
	}
};

class ConcreteElementB :public Element
{
public:
	void Accept(Visitor* visitor)
	{
		visitor->VisitConcreteElementB(this);
		cout << "visiting ConcreteElementA..." << endl;
	}
};

int main()
{
	Visitor* visitor = new ConcreteVisitorA();
	Element* element = new ConcreteElementA();
	
	element->Accept(visitor);
	
	delete element;
	delete visitor;
	
	return 0;
}