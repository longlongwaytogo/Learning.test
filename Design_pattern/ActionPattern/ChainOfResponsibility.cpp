//ChainOfResponsibility.cpp
/*
Chain of Responsibility（CoR）模式也叫职责链模式或者职责连锁模式，是行为模式之一，该模式构造一系列分别担当不同的职责的类的对象来共同完成一个任务，这些类的对象之间像链条一样紧密相连，所以被称作职责链模式。 
例1：比如客户Client要完成一个任务，这个任务包括a,b,c,d四个部分。 
　　首先客户Client把任务交给A，A完成a部分之后，把任务交给B，B完成b部分，…，直到D完成d部分。 
---------------------
优缺点 
优点： 
责任的分担。每个类只需要处理自己该处理的工作（不该处理的传递给下一个对象完成），明确各类的责任范围，符合类的最小封装原则。各司其职！ 
可以根据需要自由组合工作流程。如工作流程发生变化，可以通过重新分配对象链便可适应新的工作流程。流程可以自由组合！ 
类与类之间可以以松耦合的形式加以组织。低耦合！ 
缺点： 
　　因为处理时以链的形式在对象间传递消息，根据实现方式不同，有可能会影响处理的速度。 
--------------------- 
作者：秋刀鱼之味 
来源：CSDN 
原文：https://blog.csdn.net/saizo123/article/details/77455487 
版权声明：本文为博主原创文章，转载请附上博文链接！

*/

#include <iostream>
using namespace std;

class Handle
{
public:
	virtual ~Handle() {}
	virtual void HandleRequest() = 0;
	void SetSucessor(Handle* succ) // 设置后继处理对象
	{
		_succ = succ;
	}
	Handle* GetSuccessor() const {
		return _succ;
	}
protected:
	Handle(){ _succ = nullptr;}
	Handle(Handle* succ):_succ(succ){}
private:
	Handle* _succ;
};

class ConcreteHandeA :public Handle {
public:
	ConcreteHandeA(){}
	ConcreteHandeA(Handle* succ):Handle(succ){	
	}
	
	void HandleRequest() {
		if(this->GetSuccessor() != 0) 
		{
			cout << "ConcreteHandleA--succer" <<endl;
			GetSuccessor()->HandleRequest();
		}
		else
		{
			cout << "ConcreteHandleA:HandleRequest" << endl;
		}
	}
};

class ConcreteHandeB :public Handle {
public:
	ConcreteHandeB(){}
	ConcreteHandeB(Handle* succ):Handle(succ){	
	}
	
	void HandleRequest() {
		if(this->GetSuccessor() != 0) 
		{
			cout << "ConcreteHandleB--succer" <<endl;
			GetSuccessor()->HandleRequest();
		}
		else
		{
			cout << "ConcreteHandleB:HandleRequest" << endl;
		}
	}
};

int main()
{
	Handle* h1 = new ConcreteHandeA();
	Handle* h2 = new ConcreteHandeB(h1);
	h2->HandleRequest();
	
	delete h1;
	delete h2;
	
	return 0;
}