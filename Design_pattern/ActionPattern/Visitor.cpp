// Visitor.cpp
/*
������ģʽ
�ڷ�����ģʽ��Visitor Pattern���У�����ʹ����һ���������࣬���ı���Ԫ�����ִ���㷨��ͨ�����ַ�ʽ��Ԫ�ص�ִ���㷨�������ŷ����߸ı���ı䡣�������͵����ģʽ������Ϊ��ģʽ������ģʽ��Ԫ�ض����ѽ��ܷ����߶������������߶���Ϳ��Դ���Ԫ�ض����ϵĲ�����
����
��ͼ����Ҫ�����ݽṹ�����ݲ������롣
��Ҫ������ȶ������ݽṹ���ױ�Ĳ���������⡣
��ʱʹ�ã���Ҫ��һ������ṹ�еĶ�����кܶ಻ͬ�Ĳ��Ҳ���صĲ���������Ҫ��������Щ����"��Ⱦ"��Щ������࣬ʹ�÷�����ģʽ����Щ��װ�����С�
��ν�����ڱ����ʵ��������һ�������ṩ�Ӵ������ߵĽӿڡ�
�ؼ����룺�����ݻ�����������һ���������ܷ����ߣ����������ô�������ߡ�
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