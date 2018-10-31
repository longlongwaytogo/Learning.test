// Observe.cpp

/*
问题：
在软件系统开发中经常需要为某些对象建立一些依赖关系,而这些依赖于该对象的依赖者会根据该对象的状态变化，触发某些事件或方法也做出相应的改变，我们怎么样建立这种依赖关系，并做到当对象状态发生变化时对依赖对象的通知？
定义：
观察者模式是对象的行为模式，又叫发布-订阅(Publish/Subscribe)模式、模型-视图(Model/View)模式、源-监听器(Source/Listener)模式或从属者(Dependents)模式。
观察者模式定义了一种一对多的依赖关系，让多个观察者对象同时监听某一个主题对象。这个主题对象在状态上发生变化时，会通知所有观察者对象，使它们能够自动更新自己。
意图：
提供一个目标(Subject)对象，他提供依赖于它的观察者Observer的注册（Attach：将Observer注册到Subject中，Subject将Observer一个Container中。）和注销（Detach：Observer告诉Subject要撤销观察，被观察者从Container中将观察者去除。）操作，并且提供了使得依赖于它的所有观察者的通知操作（Notify），当Subject目标状态发生改变后Subject对象发出Notify通知所有Observer进行修改（调用Update）。

*/
#include <iostream>
#include <list>
#include <string>
using namespace std;

class Observer;

class Subject {
public:
	virtual void SetState(const string st) = 0;
	virtual string GetState() = 0;
	virtual void Attach(Observer* obv);
	virtual void Detach(Observer* obv);
	virtual	void Notify();
	virtual ~Subject(){}
protected:
	Subject(){}
private:
	list<Observer*> _obvs;
};

class ConcreteSubject :public Subject {
public:
	string GetState()
	{
		return _st;
	}
	void SetState(const string st)
	{
		_st = st;
	}
private:
	string _st;
};


 


////////////////////////////////////
// observer
class Observer
{
public:
	virtual void Update(Subject* sub) = 0;
	virtual void PrintInfo() = 0;
	virtual ~Observer() {}
protected:
	Observer(){}
	string _st;
};

void Subject::Attach(Observer* obv)
{
	_obvs.push_front(obv);
}

void Subject::Detach(Observer* obv)
{
	if(obv != nullptr)
		_obvs.remove(obv);
}

void Subject::Notify()
{
	for( auto obv : _obvs) 
	{
		obv->Update(this);
	}
}


class ConcreteObserver : public Observer
{
public:
	virtual Subject* GetSubject()
	{
		return _subject;
	}
	ConcreteObserver(Subject* sub)
	{
		_subject = sub;
		_subject->Attach(this);
	}
	~ConcreteObserver()
	{
		_subject->Detach(this);
	}
	
	void Update(Subject* sub)
	{
		_st = sub->GetState();
		PrintInfo();
		
	}
	
	void PrintInfo()
	{
		cout << "ConcreteObserver::printInfo\t" <<  _subject->GetState() << endl;
	}

private:
	Subject* _subject;
};


int main()
{
	Subject* sub = new ConcreteSubject();
	Observer* o1 = new ConcreteObserver(sub);
	Observer* o2 = new ConcreteObserver(sub);
	
	sub->SetState(string("old"));
	sub->Notify();
	sub->SetState(string("new"));
	sub->Notify();
	
	delete o1;
	delete o2;
	delete sub;
	
	return 0;
}
